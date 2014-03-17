
#include "HpCharaInst.h"

#include "HpAnimate.h"
#include "HpCharactorManager.h"
#include "HpAnimRenderVisitor.h"
#include "HpAnimBuildVisitor.h"
#include "HpImageKeyframe.h"
#include "HpAnimaKeyframe.h"
#include "HpAnimaStatus.h"
#include "HpTextureAtlasShader.h"

#include "Hpheaders.h"


NS_HPAM_BEGIN

const double HpCharaInst::s_default_fps = 30;

HpCharaInst::HpCharaInst()
: CCNodeRGBA()
, m_bClippingToBounds(false)
, m_bScissorRestored(false)
{
    m_charator = NULL;
    m_cur_anima = NULL;
    m_atlas_list = new CCArray;
    m_local_anims = new CCDictionary;
    m_cur_anima_name = NULL;
    m_delegate = NULL;
    m_flipx = false;
    m_anima_status = HpCharactorManager::sharedManager()->requestAS();
    m_attach_list = new CCArray;
    m_opacity = 255;
    m_dirty = false;
    
    // set CCNodeRGBA prop to effect its childern
    _cascadeColorEnabled = true;
    _cascadeOpacityEnabled = true;
}

HpCharaInst::~HpCharaInst(){
    HpCharactorManager::sharedManager()->recycleAS(m_anima_status);
    
    for(int i = getAtlases()->count() - 1; i >=0;  --i){
        HpCharactorManager::sharedManager()->freeAtlas(getAtlases()->objectAtIndex(i));
    }
    
    CC_SAFE_RELEASE(m_local_anims);
    CC_SAFE_RELEASE(m_atlas_list);
    CC_SAFE_RELEASE(m_attach_list);
    CC_SAFE_RELEASE(m_cur_anima_name);
}

HpCharaInst* HpCharaInst::create()
{
    HpCharaInst *inst = new HpCharaInst();
    if(inst && inst->init()){
        HP_AUTO_RELEASE(inst);
    }
    return inst;
}

/************ private function ************/
HpAnimation* HpCharaInst::getAnimationByName(CCString* p_ani)
{
    HpAnimation* ani = static_cast<HpAnimation*>(m_local_anims->objectForKey(p_ani->getCString()));
    if(ani) return ani;
    return static_cast<HpAnimation*>(m_charator->getAnimas()->objectForKey(p_ani->getCString()));
}

HpLayer* HpCharaInst::getlayerWhile(bool caring_dst_l, CCString* p_dst_layer, CCString* p_dst_ani, CCString* p_src_layer, CCString* p_src_ani, CCString* p_src_chr){
    
    if(caring_dst_l && p_dst_layer == NULL) return NULL;
    if(p_dst_ani){
        HpAnimation* dst_ani = this->getAnimationByName(p_dst_ani);
        if(dst_ani == NULL)
            return NULL;
        
        if(caring_dst_l && dst_ani->getLayerByName(p_dst_layer) == NULL)
            return NULL;
    }
    
    if(p_src_chr) {
        HpCharactor*c = HpCharactorManager::sharedManager()->getCharactorById(p_src_chr->getCString());
        if(c == NULL)
            return NULL;
        HpAnimation* a = dynamic_cast<HpAnimation*>(c->getAnimas()->objectForKey(p_src_ani->getCString()));
        if(a == NULL){
            return NULL;
        }
        
        return a->getLayerByName(p_src_layer);
    }
    
    return NULL;
}

void HpCharaInst::ensureLocalAnimation(){
    if(m_local_anims->count() == 0)
        this->createLocalAnimation();
    HPLOG("Test...");
    CCAction* action = this->getActionByTag(HPANIMATION_ACTION_TAG);
    HpAnimate* anim_action = NULL;
    if(action){
        if(dynamic_cast<HpAnimate*>(action) != NULL){
            anim_action = dynamic_cast<HpAnimate*>(action);
        } else {
            CCRepeatForever* _action = dynamic_cast<CCRepeatForever*>(action);
            anim_action = dynamic_cast<HpAnimate*>(_action->getInnerAction());
        }
        
        if(anim_action)
            anim_action->setAnima(this->getAnimationByName(this->getCurrentAnimationName()));
    }
    
    this->updateAttaches();
}

void HpCharaInst::createLocalAnimation(){
    CCAssert(m_local_anims->count() == 0, "local animation have been created");
    if(m_local_anims->count()) return;
    
    CCDictElement* element = NULL;
    {
        CCDictionary* tmp = m_charator->getAnimas();
        CCDICT_FOREACH(tmp, element) {
            HpAnimation* src_ani = dynamic_cast<HpAnimation*>(element->getObject());
            HpAnimation* ani = src_ani->clone();
            m_local_anims->setObject(ani, element->getStrKey());
        }
    }
    
    HpAnimBuildVisitor* visitor = HpCharactorManager::sharedManager()->getBuilder();
    
    visitor->begin(m_local_anims);
    
    {
        CCDICT_FOREACH(m_local_anims, element) {
            HpAnimation* ani = dynamic_cast<HpAnimation*>(element->getObject());
            
            visitor->visitAnima(ani, true, 0);
        }
    }
    
    visitor->end();
}



void HpCharaInst::replaceContent(CCString *p_content, CCString *p_layer, CCString *p_ani, HpContentKeyframe* p_ckf){
    
    if(p_ani){
        HpAnimation* ani = dynamic_cast<HpAnimation*>(m_local_anims->objectForKey(p_ani->getCString()));
        ani->replaceContent(p_content, p_layer, p_ckf);
    } else {
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(m_local_anims, pElement) {
            HpAnimation* a = dynamic_cast<HpAnimation*>(pElement->getObject());
            a->replaceContent(p_content, p_layer, p_ckf);
        }
    }
}

void HpCharaInst::updateAttaches()
{
    
    CCObject* arrayItem = NULL;
    CCARRAY_FOREACH(m_attach_list, arrayItem){
        HpAttachPoint* ap = dynamic_cast<HpAttachPoint*> (arrayItem);
        
        ap->setAnimaName(this->getCurrentAnimationName());
        ap->setLayerInst(this->getAnimationByName(this->getCurrentAnimationName())->getLayerByName(ap->getLayerName()));
    }
}

/************ public function ************/

void HpCharaInst::playAniByName(const char* p_ani_name, float start_time, int fps, unsigned int num, bool auto_destroy, float delaytime)
{
    HpAnimation* anim = HpCharactorManager::sharedManager()->charaAnimaByName(p_ani_name, &m_charator);
    if(anim == NULL) {
        return;
    }
    
    this->m_cur_anima = NULL;
    this->setCurrentAnimationName(CCString::create(p_ani_name));
    this->setFirstAnimationFrame(true);
    this->stopActionByTag(HPANIMATION_ACTION_TAG);
    this->updateAttaches();
    
    setFps(fps);
    
    HpAnimate* anim_action = new HpAnimate(anim, start_time, fps);
    
    anim_action->setRepeatNumber(num);
    anim_action->setAutoDestroy(auto_destroy);
    
    if(num == 1){
        anim_action->setTag(HPANIMATION_ACTION_TAG);
        
        if (delaytime != 0.0f) {
            CCDelayTime *delayAction = CCDelayTime::create(delaytime);
            this->runAction(CCSequence::createWithTwoActions(delayAction, anim_action));
        } else {
            this->runAction(anim_action);
        }
    } else {
        CCRepeatForever* repeat = new CCRepeatForever;
        repeat->initWithAction(anim_action);
        repeat->setTag(HPANIMATION_ACTION_TAG);
        if (delaytime != 0.0f) {
            CCDelayTime *delayAction = CCDelayTime::create(delaytime);
            this->runAction(CCSequence::createWithTwoActions(delayAction, anim_action));
        } else {
            this->runAction(repeat);
        }
        repeat->release();
    }
    anim_action->release();
}

void HpCharaInst::playAniByName(const char *p_ani_name, float start_time, int fps, bool forever_repeat)
{
    this->playAniByName(p_ani_name, start_time, fps, forever_repeat ? 0 : 1, false);
}

void HpCharaInst::playAniByName(const char *p_ani_name, bool forever_repeat)
{
    this->playAniByName(p_ani_name, 0, s_default_fps, forever_repeat);
}

void HpCharaInst::playAniByName(const char *p_ani_name, float frm)
{
    HpAnimation* anim = HpCharactorManager::sharedManager()->charaAnimaByName(p_ani_name, &m_charator);
    if(anim == NULL){
        return;
    }
    
    this->m_cur_anima = NULL;
    this->setCurrentAnimationName(CCString::create(p_ani_name));
    this->setFirstAnimationFrame(true);
    this->stopActionByTag(HPANIMATION_ACTION_TAG);
    this->updateAttaches();
    
    setFps(s_default_fps);
    
    this->setAni(anim, frm);
}

void HpCharaInst::playEffectByName(const char *p_ani_name)
{
    this->playAniByName(p_ani_name, 0, s_default_fps, 1, true);
}

void HpCharaInst::draw()
{
    if(m_dirty && m_cur_anima){
        HpAnimRenderVisitor* visitor = HpCharactorManager::sharedManager()->getRender();
        visitor->begin(this);
        visitor->visitAnima(m_cur_anima, this->getFirstAnimationFrame(), m_cur_frame);
        visitor->end();
        m_dirty = false;
    }
    
    if(m_atlas_list->count() == 0)
        return;
    
    CCObject* arrayItem = NULL;
    {
        CCARRAY_FOREACH(m_atlas_list, arrayItem){
            HpTextureAtlas* atlas = static_cast<HpTextureAtlas*>(arrayItem);
            if(atlas->getTexture()->hasPremultipliedAlpha())
                ccGLBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            else
                ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            atlas->drawQuads();
        }
    }
}


float HpCharaInst::getDuration()
{
    HpAnimation* anim = HpCharactorManager::sharedManager()->charaAnimaByName(getCurrentAnimationName()->getCString(), NULL);
    return anim ? anim->getLength() / m_fps : 0.f;
}

void HpCharaInst::setLight(const ccColor3B& light)
{
    HpLightObject::setLight(light);
    m_dirty = true;
}

void HpCharaInst::setAni(HpAnimation* p_ani, float frm)
{
    CCAssert(p_ani != NULL, "Null animation)");
    if(m_cur_anima != p_ani){
        m_cur_anima = p_ani;
        m_dirty = true;
    }
    
    if(m_cur_frame != frm){
        m_cur_frame = frm;
        m_dirty = true;
    }
}

void HpCharaInst::applyAttath(HpLayer* layer, const CCAffineTransform& m, const ccColor4F& color)
{
    CCObject* arrayItem = NULL;
    CCARRAY_FOREACH(m_attach_list, arrayItem){
        HpAttachPoint* ap = static_cast<HpAttachPoint*>(arrayItem);
        if (ap->getLayerInst() == layer) {
            ap->apply(m, color);
        }
    }
}

void HpCharaInst::beforeDraw()
{
    if (m_bClippingToBounds)
    {
		m_bScissorRestored = false;
        CCRect frame = getViewRect();
        if (CCEGLView::sharedOpenGLView()->isScissorEnabled()) {
            m_bScissorRestored = true;
            m_tParentScissorRect = CCEGLView::sharedOpenGLView()->getScissorRect();
            //set the intersection of m_tParentScissorRect and frame as the new scissor rect
            if (frame.intersectsRect(m_tParentScissorRect)) {
                float x = MAX(frame.origin.x, m_tParentScissorRect.origin.x);
                float y = MAX(frame.origin.y, m_tParentScissorRect.origin.y);
                float xx = MIN(frame.origin.x+frame.size.width, m_tParentScissorRect.origin.x+m_tParentScissorRect.size.width);
                float yy = MIN(frame.origin.y+frame.size.height, m_tParentScissorRect.origin.y+m_tParentScissorRect.size.height);
                CCEGLView::sharedOpenGLView()->setScissorInPoints(x, y, xx-x, yy-y);
            }
        }
        else {
            glEnable(GL_SCISSOR_TEST);
            CCEGLView::sharedOpenGLView()->setScissorInPoints(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
        }
    }
}

/**
 * retract what's done in beforeDraw so that there's no side effect to
 * other nodes.
 */
void HpCharaInst::afterDraw()
{
    if (m_bClippingToBounds)
    {
        if (m_bScissorRestored) {//restore the parent's scissor rect
            CCEGLView::sharedOpenGLView()->setScissorInPoints(m_tParentScissorRect.origin.x, m_tParentScissorRect.origin.y, m_tParentScissorRect.size.width, m_tParentScissorRect.size.height);
        }
        else {
            glDisable(GL_SCISSOR_TEST);
        }
    }
}

void HpCharaInst::visit()
{
	// quick return if not visible
	if (!isVisible())
    {
		return;
    }
    
	kmGLPushMatrix();
	
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        this->transformAncestors();
    }
    
	this->transform();
    this->beforeDraw();
    
	if(m_pChildren)
    {
		ccArray *arrayData = m_pChildren->data;
		unsigned int i=0;
		
		// draw children zOrder < 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode *child =  (CCNode*)arrayData->arr[i];
			if ( child->getZOrder() < 0 )
            {
				child->visit();
			}
            else
            {
				break;
            }
		}
		
		// this draw
		this->draw();
		
		// draw children zOrder >= 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode* child = (CCNode*)arrayData->arr[i];
			child->visit();
		}
        
	}
    else
    {
		this->draw();
    }
    
    this->afterDraw();
	if ( m_pGrid && m_pGrid->isActive())
    {
		m_pGrid->afterDraw(this);
    }
    
	kmGLPopMatrix();
}

CCRect HpCharaInst::getViewRect()
{
    CCPoint screenPos = this->convertToWorldSpace(CCPointZero);
    
    float scaleX = this->getScaleX();
    float scaleY = this->getScaleY();
    
    for (CCNode *p = m_pParent; p != NULL; p = p->getParent()) {
        scaleX *= p->getScaleX();
        scaleY *= p->getScaleY();
    }
    
    // Support negative scaling. Not doing so causes intersectsRect calls
    // (eg: to check if the touch was within the bounds) to return false.
    // Note, CCNode::getScale will assert if X and Y scales are different.
    if(scaleX<0.f) {
        screenPos.x += m_obContentSize.width*scaleX;
        scaleX = -scaleX;
    }
    if(scaleY<0.f) {
        screenPos.y += m_obContentSize.height*scaleY;
        scaleY = -scaleY;
    }
    
    return CCRectMake(screenPos.x, screenPos.y, m_obContentSize.width*scaleX, m_obContentSize.height*scaleY);
}


void HpCharaInst::appendLayer(CCString* p_src_layer, CCString* p_src_ani, CCString* p_char, CCString* p_dst_ani){
    HpLayer* src_layer = this->getlayerWhile(false, NULL, p_dst_ani, p_src_layer, p_src_ani, p_char);
    
    if(src_layer) {
        this->ensureLocalAnimation();
        
        if(p_dst_ani == NULL){
            CCDictElement* pElement = NULL;
            CCDICT_FOREACH(m_local_anims, pElement) {
                HpAnimation* a = dynamic_cast<HpAnimation*>(pElement->getObject());
                HpLayer* l = src_layer->clone();
                a->getLayers()->addObject(l);
            }
            
            
        } else {
            HpAnimation* dst_ani = dynamic_cast<HpAnimation*>(m_local_anims->objectForKey(p_dst_ani->getCString()));
            HpLayer* l = src_layer->clone();
            dst_ani->getLayers()->addObject(l);
        }
    }
}

void HpCharaInst::insertLayer(CCString* p_src_layer, CCString* p_src_ani, CCString* p_char, CCString* p_dst_ani, CCString* p_dst_layer){
    HpLayer* src_layer = this->getlayerWhile(true, p_dst_layer, p_dst_ani, p_src_layer, p_src_ani, p_char);
    
    if(src_layer){
        this->ensureLocalAnimation();
        
        if(p_dst_ani == NULL){
            CCDictElement* pElement = NULL;
            CCDICT_FOREACH(m_local_anims, pElement) {
                HpAnimation* a = dynamic_cast<HpAnimation*>(pElement->getObject());
                HpLayer* l = src_layer->clone();
                a->insertLayer(l, p_dst_layer);
            }
            
        } else {
            HpAnimation* dst_ani = dynamic_cast<HpAnimation*>(m_local_anims->objectForKey(p_dst_ani->getCString()));
            HpLayer* l = src_layer->clone();
            dst_ani->insertLayer(l, p_dst_layer);
        }
    }
}

void HpCharaInst::replaceLayer(CCString* p_dst_layer, CCString* p_dst_ani, CCString* p_src_layer, CCString* p_src_ani, CCString* p_char){
    HpLayer* src_layer = this->getlayerWhile(true, p_dst_layer, p_dst_ani, p_src_layer, p_src_ani, p_char);
    if(src_layer){
        this->ensureLocalAnimation();
        
        if(p_dst_ani == NULL){
            CCDictElement* pElement = NULL;
            CCDICT_FOREACH(m_local_anims, pElement) {
                HpAnimation* a = dynamic_cast<HpAnimation*>(pElement->getObject());
                HpLayer* l = src_layer->clone();
                a->replaceLayer(p_dst_layer, l);
            }
            
        } else {
            HpAnimation* dst_ani = dynamic_cast<HpAnimation*>(m_local_anims->objectForKey(p_dst_ani->getCString()));
            HpLayer* l = src_layer->clone();
            dst_ani->replaceLayer(p_dst_layer, l);
        }
    }
}

void HpCharaInst::replaceContent(CCString* p_content, CCString* p_layer, CCString* p_ani, CCString* p_image){
    if(p_image == NULL){
        return;
    }
    CCSpriteFrame* sf = HpCharactorManager::sharedManager()->getSpriteFrameCache()->spriteFrameByName(p_image->getCString());
    this->replaceContent(p_content, p_layer, p_ani, sf);
}

void HpCharaInst::replaceContent(CCString *p_content, CCString *p_layer, CCString *p_ani, CCSpriteFrame* p_sprite){
    if(p_sprite == NULL){
        return;
    }
    
    if(p_ani){
        HpAnimation* a = this->getAnimationByName(p_ani);
        if(a == NULL){
            return;
        }
        if(p_layer && a->getLayerByName(p_layer) == NULL){
            return;
        }
    }
    this->ensureLocalAnimation();
    
    HpImageKeyframe* ikf = new HpImageKeyframe;
    ikf->setSpriteFrame(p_sprite);
    this->replaceContent(p_content, p_layer, p_ani, ikf);
    CC_SAFE_RELEASE(ikf);
}

void HpCharaInst::replaceContent(CCString *p_content, CCString *p_layer, CCString *p_ani, CCString* p_anima, CCString* p_char){
    do{
        if(p_char == NULL || p_anima == NULL)
            break;
        
        HpCharactor* c = dynamic_cast<HpCharactor*>(HpCharactorManager::sharedManager()->getCharactorById(p_char->getCString()));
        if(c == NULL)
            break;
        
        HpAnimation* src_ani = dynamic_cast<HpAnimation*>(c->getAnimas()->objectForKey(p_anima->getCString()));
        if(src_ani == NULL)
            break;
        
        if(p_ani){
            HpAnimation* a = this->getAnimationByName(p_ani);
            if(a == NULL)
                break;
            if(p_layer && a->getLayerByName(p_layer) == NULL)
                break;
        }
        
        this->ensureLocalAnimation();
        
        HpAnimaKeyframe* akf = new HpAnimaKeyframe;
        akf->setAnima(src_ani);
        this->replaceContent(p_content, p_layer, p_ani, akf);
        CC_SAFE_RELEASE(akf);
    } while(0);
    
}

void HpCharaInst::onAnimationEnd(bool destroy){
    if(m_delegate){
        m_delegate->actionOnAnimationEnd(m_cur_anima, this);
    }
    
    if(destroy){
        this->removeFromParent();
    }
}

void HpCharaInst::onCustomEvent(CCString* p_event){
    
    if(m_delegate){
        m_delegate->actionOnCustomEvent(p_event, this);
    }
}

void HpCharaInst::attach(CCNode* p_child, CCString* p_layer){
    if(p_child == NULL || p_layer == NULL) return;
    
    HpAttachPoint* ap_speicfied = NULL;
    for(int i = 0; i < m_attach_list->count(); i ++){
        HpAttachPoint* ap = static_cast<HpAttachPoint*> (m_attach_list->objectAtIndex(i));
        if(ap->getAnimaName()->isEqual(getCurrentAnimationName()) && ap->getLayerName()->isEqual(p_layer)){
            ap_speicfied = ap;
            break;
        }
    }
    
    if(ap_speicfied == NULL){
        ap_speicfied = new HpAttachPoint;
        ap_speicfied->setLayerName(p_layer);
        if (getCurrentAnimationName() != NULL) {
            ap_speicfied->setAnimaName(getCurrentAnimationName());
            ap_speicfied->setLayerInst(this->getAnimationByName(this->getCurrentAnimationName())->getLayerByName(p_layer));
        }
        m_attach_list->addObject(ap_speicfied);
        CC_SAFE_RELEASE(ap_speicfied);
    }
    
    ap_speicfied->attach(p_child);
    if (p_child->getParent() == NULL) {
        this->addChild(p_child);
    }
    
}

void HpCharaInst::unattach(CCNode* p_child){
    if(p_child == NULL) return;
    
    for(int i = 0; i < m_attach_list->count(); i ++){
        HpAttachPoint* ap = static_cast<HpAttachPoint*>(m_attach_list->objectAtIndex(i));
        ap->remove(p_child);
    }
    this->removeChild(p_child, false);
}

bool HpCharaInst::hasContent(CCString *contentName){
    bool hasContent = false;
    
    unsigned int animationNum = m_charator->getAnimas()->count();
    for(unsigned int animationIndex = 0; animationIndex < animationNum; ++animationIndex)
    {
        CCString *key = static_cast<CCString *>(m_charator->getAnimas()->allKeys()->objectAtIndex(animationIndex));
        HpAnimation *ani = static_cast<HpAnimation *>(m_charator->getAnimas()->objectForKey(key->getCString()));
        unsigned int layerNum = ani->getLayers()->count();
        for(unsigned int layerIndex = 0; layerIndex < layerNum; ++layerIndex)
        {
            HpLayer *layer = static_cast<HpLayer *>(ani->getLayers()->objectAtIndex(layerIndex));
            
            unsigned int contentNum = layer->getContentKeys()->count();
            for(unsigned int contentIndex = 0; contentIndex < contentNum; ++contentIndex)
            {
                HpContentKeyframe *ck = static_cast<HpContentKeyframe *>(layer->getContentKeys()->objectAtIndex(contentIndex));
                if(0 == ck->getContentName()->compare(contentName->getCString()))
                {
                    hasContent = true;
                    break;
                }
            }
            
            if(hasContent)
                break;
        }
        
        if(hasContent)
            break;
    }
    
    return hasContent;
}



NS_HPAM_END


