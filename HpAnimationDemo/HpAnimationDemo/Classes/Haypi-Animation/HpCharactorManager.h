//
//  HpCharactorManager.h
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-4.
//
//

#ifndef __HpAnimationDemo__HpCharactorManager__
#define __HpAnimationDemo__HpCharactorManager__

#include "cocos2d.h"

#include "HpCharactor.h"
#include "HpAnimation.h"
#include "HpLayer.h"
#include "HpCharaInstObserver.h"
#include "HpAnimaStatus.h"
#include "HpAttachPoint.h"
#include "HpCharactorXmlParser.h"
#include "HpCharactorBinParser.h"
#include "HpAnimBuildVisitor.h"
#include "HpAnimRenderVisitor.h"
#include "HpTextureAtlas.h"
#include "HpPlay.h"
#include "HpShine.h"

USING_NS_CC;

NS_HPAM_BEGIN

class HpCharactorXmlParser;
class HpAnimBuildVisitor;
class HpAnimRenderVisitor;
class HpCharactorBinParser;
class HpLayerStatus;

class HpCharactorManager : public CCObject
{
public:
    /** Returns the shared instance of the Animation manager */
    static HpCharactorManager* sharedManager();
    
    /** Purges the cache. It releases all the Animation and the retained instance. */
    static void purgeManager();
    
    /** Adds multiple Animation from a chr or xml file.
     * Some plists will be loaded automatically.
     */
    void addCharactorsWithFile(const char *pszFile);
    
    /** Removes multiple Animation from a chr or xml file.
     * Animation stored in this file will be removed.
     * Also the plists will removed
     */
    void removeCharactorsFromFile(const char* file);
    
    /** Removes all the Animations in loaded.
     * Animation and plists stored in this file will be removed.
     */
    void removeAllCharactor();
    
    /** Removes Charactor in loaded file. */
    HpCharactor* getCharactorById(const char* file);
    
    /** Returns an Animation that was previously added.
     * If the name is not found it will return nil.
     * You should retain the returned copy if you are going to use it.
     @param p_chara_out is the owner of returned Animation
     */
    HpAnimation* charaAnimaByName(const char *pszName, HpCharactor** p_chara_out = NULL);
    
public:
    /** The chr vistitor */
    CC_SYNTHESIZE_READONLY(HpAnimBuildVisitor*, m_builder, Builder)
    CC_SYNTHESIZE_READONLY(HpAnimRenderVisitor*, m_render, Render)
    
    /** Set a costom SpriteFrameCache for Animation
     * if you wan't use the same SpriteFrameCache with UI
     */
    CC_SYNTHESIZE_RETAIN(CCSpriteFrameCache*, m_spriteFrameCache, SpriteFrameCache);
    
    /** Set a chr or xml file path.
     * But it is ivalid now.
     */
    CC_SYNTHESIZE_RETAIN(CCString*, m_aniFilePath, AniFilePath);
    
    /** Set display mode HD or not */
    CC_SYNTHESIZE(bool, m_hd, HD);
    
    /** Init Custom Shaders, HpCharaInst Loader  */
    bool loadDefaultConfig();
    
    /** Reload Custom Shaders when Back To Foreground  */
    bool reloadDefaultConfig();
    
protected:
    /** Protected for single Instance*/
    HpCharactorManager();
    virtual ~HpCharactorManager();
    
public:
    /** Manager the plists in Animation */
    void loadPlist(const char* p_plist_file);
    void removePlist(const char* p_plist_file);
    
    /** Cache object for recycle used */
    HpTextureAtlas* allocAtlas();
    void freeAtlas(CCObject* p_atlas);
    
    HpLayerStatus* requestLS();
    void recycleLS(CCObject* p_ls);
    
    HpAnimaStatus* requestAS();
    void recycleAS(CCObject* p_as);
    
private:
    CCDictionary* m_charactors;
    HpCharactorXmlParser* m_xml_parser;
    HpCharactorBinParser* m_chr_parser;
    
    HpStack* m_atlas_pool;
    HpStack* m_layer_status_pool;
    HpStack* m_anima_status_pool;
    
    set<string> m_plist_cache;
    CCArray* m_instance_todestory;
};

NS_HPAM_END

#endif /* defined(__HpAnimationDemo__HpCharactorManager__) */
