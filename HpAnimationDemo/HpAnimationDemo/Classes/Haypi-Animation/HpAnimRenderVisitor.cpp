#include "HpAnimRenderVisitor.h"
#include "Hpheaders.h"


NS_HPAM_BEGIN

HpAnimRenderVisitor::HpAnimRenderVisitor(){
    m_tf_stack = new HpAffineTransformStack(100);
    m_color_stack = new HpColorStack(100);
    m_light_stack = new HpColorStack(100);
    m_status_stack = new HpStack(100);
    
    m_cur_atlas = NULL;
    m_chr_instance = NULL;

    CCSize size = CCEGLView::sharedOpenGLView()->getDesignResolutionSize();
    m_local_scale = 1.0f;
    m_global_scale = ((int)(size.width/480.f)) * 480.f / 960.0;
    m_global_translate = CCPointZero;
    
    m_anim_helper = new CCDictionary();
    m_object_stack = new HpStack();
    s_elapsed = new CCString("s_elapsed");
}

HpAnimRenderVisitor::~HpAnimRenderVisitor(){
    CC_SAFE_RELEASE(m_cur_atlas);
    CC_SAFE_RELEASE(m_chr_instance);
    CC_SAFE_RELEASE(m_tf_stack);
    CC_SAFE_RELEASE(m_color_stack);
    CC_SAFE_RELEASE(m_light_stack);
    CC_SAFE_RELEASE(m_status_stack);
    CC_SAFE_RELEASE(s_elapsed);
    CC_SAFE_RELEASE(m_anim_helper);
    CC_SAFE_RELEASE(m_object_stack);
}

void HpAnimRenderVisitor::begin(CCObject *p_map){
    CCAssert(dynamic_cast<HpCharaInst*> (p_map), "Invalid target-HpAnimRenderVisitor:Begin");
    m_chr_instance = dynamic_cast<HpCharaInst*> (p_map);
    m_cur_atlas_id = -1;
    m_cur_atlas = NULL;
    m_delta_time = m_chr_instance->getDeltaTime();
    
    CCAffineTransform transform;
    transform.b = transform.c = 0.f;

//    CC_CONTENT_SCALE_FACTOR()
    // check cocos2d version refer to ios code
    
#if 1
    transform.a = m_chr_instance->getFlipX() ? -m_global_scale : m_global_scale;
    transform.d = m_global_scale;
    transform.tx = m_global_translate.x;
    transform.ty = m_global_translate.y;
#else 
    transform.a = (m_chr_instance->getFlipX() ? -m_global_scale : m_global_scale) * CC_CONTENT_SCALE_FACTOR();
    transform.d = m_global_scale * CC_CONTENT_SCALE_FACTOR();
    transform.tx = m_global_translate.x * CC_CONTENT_SCALE_FACTOR();
    transform.ty = m_global_translate.y * CC_CONTENT_SCALE_FACTOR();
#endif


    m_tf_stack->push((CCAffineTransform*)&transform);
    ccColor4F color = ccc4FFromccc3B(m_chr_instance->getDisplayedColor());
    color.a = m_chr_instance->getOpacity() / 255.f;
    m_color_stack->push(&color);
    
    ccColor4F light = ccc4FFromccc3B(m_chr_instance->getDisplayedLight());
    light.a = 0;
    m_light_stack->push(&light);
    
    m_status_stack->push(m_chr_instance->getStatus());
    m_object_stack->push(m_chr_instance);
}

void HpAnimRenderVisitor::end(){
    m_status_stack->pop();
    m_tf_stack->pop();
    m_color_stack->pop();
    m_light_stack->pop();
    m_object_stack->pop();

    for(int i = m_chr_instance->getAtlases()->count() - 1; i > m_cur_atlas_id; -- i){
        HpTextureAtlas* atlas = dynamic_cast<HpTextureAtlas*> (m_chr_instance->getAtlases()->objectAtIndex(i));
        HpCharactorManager::sharedManager()->freeAtlas(atlas);
        m_chr_instance->getAtlases()->removeLastObject();
    }

    m_chr_instance->setFirstAnimationFrame(false);
}
    
void HpAnimRenderVisitor::visitAnima(HpAnimation* p_ani, bool p_first, float p_time, bool p_inherited)
{
//    CCLOG(" %d \tauto \t%s\t%f", p_ani->getLength(), p_inherited ? "false" : "true", p_time);
    if (!p_inherited) {
        m_object_stack->push(p_ani);
        
        m_cur_dic = currentDictionaryOfclass<HpAnimation>();
        if(p_first) {setElapsed(p_time / (m_chr_instance->getFps()));}
        double currtime = getElapsed() * (m_chr_instance->getFps());
        
        HpAnimaStatus* status = (HpAnimaStatus*)m_status_stack->peek();
        for(status->setLayerIndex(0); status->getLayerIndex() < p_ani->getLayers()->count(); status->setLayerIndex(status->getLayerIndex() + 1)){
            visitLayer(dynamic_cast<HpLayer*>(p_ani->getLayers()->objectAtIndex(status->getLayerIndex())), p_first, currtime);
        }
        
        double duration = getElapsed() + m_delta_time;
        
        if (currtime >= p_ani->getLength()) {
            duration = 0;
        }
        
        setElapsed(duration);
        
        m_object_stack->pop();
        
    }else{
        visitAnima(p_ani, p_first, p_time);
    }
}

void HpAnimRenderVisitor::visitAnima(HpAnimation *p_ani, bool p_first, float p_frm){
    m_object_stack->push(p_ani);
    HpAnimaStatus* status = dynamic_cast<HpAnimaStatus*>(m_status_stack->peek());
    for(status->setLayerIndex(0); status->getLayerIndex() < p_ani->getLayers()->count(); status->setLayerIndex(status->getLayerIndex() + 1)){
        visitLayer(dynamic_cast<HpLayer*>(p_ani->getLayers()->objectAtIndex(status->getLayerIndex())), p_first, p_frm);
    }
    m_object_stack->pop();
}
    
const CCAffineTransform CCAffineTransformZero = CCAffineTransformMake(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);

void HpAnimRenderVisitor::visitLayer(HpLayer *p_layer, bool p_first, float p_frm){
    m_object_stack->push(p_layer);
    
    HpAnimaStatus* status = dynamic_cast<HpAnimaStatus*>(m_status_stack->peek());
    HpKeyframe* gfrm = p_layer->getKeyframeAt(p_frm);
    HpContentKeyframe* cfrm = p_layer->getContentKeyframeAt(p_frm);
    if(cfrm){
        cfrm->setFirstVisitFlag(p_first || !cfrm->isEqual(status->getLastCKey()));
        if(gfrm){
            if(m_chr_instance->getFirstAnimationFrame()){
                if(gfrm->getEvent() && gfrm->getTime() == p_frm){
                    m_chr_instance->onCustomEvent(gfrm->getEvent());
                }
            } else if (p_first){
                fireEventPassed(p_layer, NULL, gfrm);
            } else {
                fireEventPassed(p_layer, status->getLastGKey(), gfrm);
            }
        }
    }
    
    HPLOG("HpAnimRenderVisitor::visitLayer...%x    %x", gfrm, cfrm);
    status->setLastGKey(gfrm, cfrm);
    if(gfrm && cfrm){
        HPLOG("HpAnimRenderVisitor::visitLayer1    ");
        cfrm->visitBy(this, gfrm, p_frm);
        HPLOG("HpAnimRenderVisitor::visitLayer2    ");
        p_layer->setTransform(this->getLayerTransform());
    }
    
    // applyAttath
    if (m_object_stack->getCount() == 3) {
        if (gfrm && cfrm) {
            if (gfrm->getContentType() != HPCONTENTTYPE_NULL) {
                m_chr_instance->applyAttath(p_layer,
                                            CCAffineTransformScale(getLayerTransform(), 1/m_global_scale, 1/m_global_scale),
                                            this->getLayerColor());
            }
        }else{
            m_chr_instance->applyAttath(p_layer, CCAffineTransformZero, ccWhite4F);
        }
    }
    
    m_object_stack->pop();
}

void HpAnimRenderVisitor::visitImageKey(HpImageKeyframe *p_ikf, HpKeyframe *p_frm, float time){

    HpAnimaStatus* _as = static_cast<HpAnimaStatus*>(m_status_stack->peek());
    _as->clearSubAS();

    if(m_cur_atlas == NULL || m_cur_atlas->getTexture() != p_ikf->getSpriteFrame()->getTexture()){
        ++ m_cur_atlas_id;
        if(m_chr_instance->getAtlases()->count() == m_cur_atlas_id){
            CCObject* obj = HpCharactorManager::sharedManager()->allocAtlas();
            m_chr_instance->getAtlases()->addObject(obj);
        }
        m_cur_atlas = static_cast<HpTextureAtlas*>(m_chr_instance->getAtlases()->objectAtIndex(m_cur_atlas_id));

        m_cur_atlas->setTexture(p_ikf->getSpriteFrame()->getTexture());
        m_cur_atlas->removeAllQuads();
    }

    if(m_cur_atlas->getTotalQuads() == m_cur_atlas->getCapacity())
        m_cur_atlas->resizeCapacity((m_cur_atlas->getCapacity() + 1) * 4 / 3);


    CCAffineTransform matrix = CCAffineTransformConcat(*(makeTransform(&matrix, p_frm, time)), *(m_tf_stack->peek()));
    this->setLayerTransform(matrix);

    CCSpriteFrame* cur_frame = p_ikf->getSpriteFrame();
    CCSize cur_size = cur_frame->getRectInPixels().size;

    float x1 = (cur_frame->getOffsetInPixels().x + (cur_frame->getOriginalSizeInPixels().width - cur_size.width) * 0.5f) * m_local_scale;
    float y1 = (cur_frame->getOffsetInPixels().y + (cur_frame->getOriginalSizeInPixels().height - cur_size.height) * 0.5) * m_local_scale;

    float x2 = x1 + cur_size.width * m_local_scale;
    float y2 = y1 + cur_size.height * m_local_scale;
    float x = matrix.tx;
    float y = matrix.ty;

    float cr = matrix.a;
    float sr = matrix.b;
    float cr2 = matrix.d;
    float sr2 = -matrix.c;
    float ax = x1 * cr - y1 * sr2 + x;
    float ay = x1 * sr + y1 * cr2 + y;

    float bx = x2 * cr - y1 * sr2 + x;
    float by = x2 * sr + y1 * cr2 + y;

    float cx = x2 * cr - y2 * sr2 + x;
    float cy = x2 * sr + y2 * cr2 + y;

    float dx = x1 * cr - y2 * sr2 + x;
    float dy = x1 * sr + y2 * cr2 + y;


    //m_quad.bl.vertices = (ccVertex3F) { RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), 0 };
    //m_quad.br.vertices = (ccVertex3F) { RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), 0 };
    //m_quad.tl.vertices = (ccVertex3F) { RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), 0 };
    //m_quad.tr.vertices = (ccVertex3F) { RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), 0 };
    m_quad.bl.vertices = vertex3(ax, ay, 0);
    m_quad.br.vertices = vertex3(bx, by, 0);
    m_quad.tl.vertices = vertex3(dx, dy, 0);
    m_quad.tr.vertices = vertex3(cx, cy, 0);

    // Atlas: color
    ccColor4F color = cccMult(p_frm->getColorAt(time), *m_color_stack->peek());
    ccColor4F extra = cccAdd(p_frm->getLightAt(time), *m_light_stack->peek());
    this->setLayerColor(color);
    
    if(m_cur_atlas->getTexture()) {
        if (m_cur_atlas->getTexture()->hasPremultipliedAlpha() && color.a != 1.0f) {
            float a = color.a;
            color.a = 1.0f;
            color = cccScale(color, a);
        }
        //设置extra的alpha值为是否预乘，供shader程序使用
        extra.a = m_cur_atlas->getTexture()->hasPremultipliedAlpha();
    }
    
//    CCLOG("hasPremultipliedAlpha: %d, extra: {%.3f, %.3f, %.3f, %.3f}", m_cur_atlas->getTexture()->hasPremultipliedAlpha(), extra.r, extra.g, extra.b, extra.a);
    
    ccColor4B ccc = ccc4(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
    m_quad.bl.colors = ccc;
    m_quad.br.colors = ccc;
    m_quad.tl.colors = ccc;
    m_quad.tr.colors = ccc;
    
    ccColor4B cce = ccc4(extra.r * 255, extra.g * 255, extra.b * 255, extra.a * 255);
    m_quad.bl.extra = cce;
    m_quad.br.extra = cce;
    m_quad.tl.extra = cce;
    m_quad.tr.extra = cce;
    
    
    // Atlas : UV
    float atlasWidth = (float)m_cur_atlas->getTexture()->getPixelsWide();
    float atlasHeight = (float)m_cur_atlas->getTexture()->getPixelsHigh();

    float left,right,top,bottom;

    if(cur_frame->isRotated()){

        left	= cur_frame->getRectInPixels().origin.x/atlasWidth;
        right	= left + cur_size.height/atlasWidth;
        top		= cur_frame->getRectInPixels().origin.y/atlasHeight;
        bottom	= top + cur_size.width/atlasHeight;


        m_quad.bl.texCoords.u = left;
        m_quad.bl.texCoords.v = top;
        m_quad.br.texCoords.u = left;
        m_quad.br.texCoords.v = bottom;
        m_quad.tl.texCoords.u = right;
        m_quad.tl.texCoords.v = top;
        m_quad.tr.texCoords.u = right;
        m_quad.tr.texCoords.v = bottom;

    } else {
        left	= cur_frame->getRectInPixels().origin.x/atlasWidth;
        right	= left + cur_size.width/atlasWidth;
        top		= cur_frame->getRectInPixels().origin.y/atlasHeight;
        bottom	= top + cur_size.height/atlasHeight;

        m_quad.bl.texCoords.u = left;
        m_quad.bl.texCoords.v = bottom;
        m_quad.br.texCoords.u = right;
        m_quad.br.texCoords.v = bottom;
        m_quad.tl.texCoords.u = left;
        m_quad.tl.texCoords.v = top;
        m_quad.tr.texCoords.u = right;
        m_quad.tr.texCoords.v = top;
    }

    m_cur_atlas->updateQuad(&m_quad, m_cur_atlas->getTotalQuads());

}

void HpAnimRenderVisitor::visitAnimaKey(HpAnimaKeyframe *p_akf, HpKeyframe *p_frm, float time){
    CCAffineTransform m = CCAffineTransformConcat(*(this->makeTransform(&m, p_frm, time)), *(m_tf_stack->peek()));
    m_tf_stack->push(&m);

    ccColor4F c = cccMult(p_frm->getColorAt(time), *(m_color_stack->peek()));
    m_color_stack->push(&c);

    HpAnimaStatus* _as = dynamic_cast<HpAnimaStatus*>(m_status_stack->peek());
    CCObject* obj1 = _as->getSubAS();
    if(obj1 == NULL){
        HPLOG("");
    }
    m_status_stack->push(obj1);

    this->visitAnima(p_akf->getAnima(), p_akf->getFirstVisitFlag(), time - p_akf->getTime(), p_akf->getIsTimeInherited());

    m_status_stack->pop();
    this->setLayerTransform(*(m_tf_stack->pop()));
    this->setLayerColor(*m_color_stack->pop());

}
    
void HpAnimRenderVisitor::visitNullKey(HpNullKeyframe *p_nkf, HpKeyframe *p_frm, float time)
{
    this->setLayerTransform(*(m_tf_stack->peek()));
    this->setLayerColor(ccWhite4F);
}


CCAffineTransform* HpAnimRenderVisitor::makeTransform(CCAffineTransform* p_in, HpKeyframe* p_key, float time){
    CCPoint center = p_key->getCenterAt(time);
    CCPoint trans = p_key->getTransAt(time);
    float rot = p_key->getRotAt(time);
    CCPoint skew = p_key->getSkewAt(time);
    CCPoint scale = p_key->getScaleAt(time);

    // CGAffineTransformMakeTranslation
    // t = [ 1 0 0 1 tx ty ] 
    *p_in = CCAffineTransformMake(1.f, 0, 0, 1.f, trans.x + center.x, trans.y + center.y);

    *p_in = CCAffineTransformRotate(*p_in, CC_DEGREES_TO_RADIANS(rot));

    struct CCAffineTransform skew_tf = CCAffineTransformIdentity;
    skew_tf.b = tan(CC_DEGREES_TO_RADIANS(skew.y));
    skew_tf.c = tan(CC_DEGREES_TO_RADIANS(skew.x));

    *p_in = CCAffineTransformConcat(skew_tf, *p_in);

    *p_in = CCAffineTransformScale(*p_in, scale.x, scale.y);
    *p_in = CCAffineTransformTranslate(*p_in, -center.x, -center.y);

    return p_in;

}

void HpAnimRenderVisitor::fireEventPassed(HpLayer* p_layer, HpKeyframe* p_last, HpKeyframe* p_kf){
    CCAssert(p_kf == p_layer->getKeys()->objectAtIndex(p_kf->getArrayIndex()), "p_kf is not belong to the layer");

    if(p_last == NULL){
        for(int i = 0; i <= p_kf->getArrayIndex(); i ++){
            HpKeyframe* _key = dynamic_cast<HpKeyframe*> (p_layer->getKeys()->objectAtIndex(i));
            if(_key->getEvent()){
                m_chr_instance->onCustomEvent(_key->getEvent());
            }
        }
    } else {
        CCAssert(p_last == p_layer->getKeys()->objectAtIndex(p_last->getArrayIndex()), "p_last is not belong to the Layer");
        if(p_kf->getArrayIndex() < p_last->getArrayIndex()){
            for(int i = p_last->getArrayIndex() + 1; i < p_layer->getKeys()->count(); i ++){
                HpKeyframe* _key = dynamic_cast<HpKeyframe*> (p_layer->getKeys()->objectAtIndex(i));
                if(_key->getEvent()){
                    m_chr_instance->onCustomEvent(_key->getEvent());
                }
            }

            for(int i = 0; i <= p_kf->getArrayIndex(); i ++){
                HpKeyframe* _key = dynamic_cast<HpKeyframe*> (p_layer->getKeys()->objectAtIndex(i));
                if(_key->getEvent()){
                    m_chr_instance->onCustomEvent(_key->getEvent());
                }
            }


        } else {
            for(int i = p_last->getArrayIndex() + 1; i <= p_kf->getArrayIndex(); i ++){
                HpKeyframe* _key = dynamic_cast<HpKeyframe*> (p_layer->getKeys()->objectAtIndex(i));
                if(_key->getEvent()){
                    m_chr_instance->onCustomEvent(_key->getEvent());
                }
            }
        }
    }
}
template <class T>    
static bool isKindOfClass(CCObject* obj) { return dynamic_cast<T*>(obj) != NULL; }

template <class T>
CCDictionary* HpAnimRenderVisitor::currentDictionaryOfclass()
{
    CCDictionary* retdic = NULL;
    CCDictionary* dic = m_anim_helper;
    CCObject* obj = NULL;
    CCARRAY_FOREACH(m_object_stack->getArray(), obj)  {
        if (dic->objectForKey((int)obj) == NULL) {
            CCDictionary* newdic = new CCDictionary();
            if (isKindOfClass<T>(obj)) {
                newdic->setObject(CCNumber<double>::create(0), (int)s_elapsed);
            }
            dic->setObject(newdic, (int)obj);
            CC_SAFE_RELEASE(newdic);
        }
        dic = (CCDictionary*)dic->objectForKey((int)obj);
        if (isKindOfClass<T>(obj)) {
            retdic = dic;
        }
    }
    
    return retdic;
}

void HpAnimRenderVisitor::setElapsed(double value)
{
    m_cur_dic->setObject(CCNumber<double>::create(value), (int)s_elapsed);
}

double HpAnimRenderVisitor::getElapsed(void)
{
    CCNumber<double> * elapsed = (CCNumber<double>*)m_cur_dic->objectForKey((int)s_elapsed);
    return elapsed->getValue();
}

NS_HPAM_END
