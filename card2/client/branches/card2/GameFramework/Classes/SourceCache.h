#ifndef _SOURCE_CACHE_H__
#define _SOURCE_CACHE_H__

HNAMESPACE_BEGIN

class HPListInfo: public CCObject {
    CC_SYNTHESIZE_RETAIN(CCString *, m_pTextureFile, TextureFile);
    CC_SYNTHESIZE_RETAIN(CCArray *, m_pSpriteFrames, SpriteFrames);
public:
    HPListInfo(): m_pTextureFile(NULL), m_pSpriteFrames(NULL) {}
    virtual ~HPListInfo() { setTextureFile(NULL); setSpriteFrames(NULL); }
    static HPListInfo *create() {
        HPListInfo *info = new HPListInfo();
//        info->autorelease();
        CC_AUTO_RELEASE(info);
        return info;
    }
    CCTexture2D *getTexture() {
        if (m_pSpriteFrames && (m_pSpriteFrames->count() > 0)) {
            HSpriteFrame *frame = (HSpriteFrame *)m_pSpriteFrames->objectAtIndex(0);
            return frame->getTextureEx();
        }
        return NULL;
    }
};

class CC_DLL HSourceCache: public HObject, public HTimerDelegate {
    HSINGLETON_OBJECT(HSourceCache);
    CC_SYNTHESIZE(bool, m_bAntiAliasTexture, AntiAliasTexture);
    CC_SYNTHESIZE(bool, m_bUsePVR, UsePVR);
public:
    void convertScaleToNode(float &scaleX, float &scaleY, CCNode *node, CCNode *toNode = NULL);
    
    const char *image2pvr(const char *filename);
    CCObject *createTexture(int command, CCObject *param);
    CCTexture2D *textureWithFile(const char *fileName);
    void removeTexture(const char *filename);
    CCSprite *spriteWithFile(const char *fileName);
    CCTexture2D *textureForKey(const char *key);
    HSpriteFrame *spriteFrameWithFilename(const char *filename);
    HSpriteFrame *spriteFrameWithName(const char *name);
    CCSprite *spriteWithFrameName(const char *frameName);
    
    CCRect clickRectForSpriteFrame(HSpriteFrame *spriteFrame, bool flipX, bool flipY);
    CCRect clickRectWithName(const char *frameName, bool flipX, bool flipY);
    
    CCSpriteFrame *spriteFrameAndClickRectWithSpriteFrameName(const char *frameName, CCRect &clickRect,  bool flipX = false, bool flipY = false);
    CCSprite *spriteAndClickRectWithSpriteFrameName(const char *frameName, CCRect &clickRect,  bool flipX = false, bool flipY = false);
    
    virtual void clear();
    void addSpriteFramesWithPList(const char *plist, FuncOnPercent onPercent = NULL, bool bNoTexture = false, bool bIgnoreTexture = false);
    void removeSpriteFramesWithPList(const char *plist);
    
    void loadTextureWithPList(const char *plist);
    void releaseTextureWithPList(const char *plist);
    
    void addToAutoManager(HSpriteFrame *spriteFrame);
    
    void forceReleaseTextures();
    void enableAutoreleaseTextures(float interval = 5.0f);
    void disableAutoreleaseTextures();
    virtual void onTimeOut(int gid, int count);
private:
    CCArray *m_pAutoManagedSpriteFrames;
    CCDictionary *m_pPlists;
    HTimer *m_pTimer;
};

#define HSHADERTYPE_POSITION        1
#define HSHADERTYPE_TEXTURE         2
#define HSHADERTYPE_COLOR           4
#define HSHADERTYPE_POSITIONCOLOR           (HSHADERTYPE_POSITION | HSHADERTYPE_COLOR)
#define HSHADERTYPE_POSITIONTEXTIRE         (HSHADERTYPE_POSITION | HSHADERTYPE_TEXTURE)
#define HSHADERTYPE_POSITIONTEXTIRECOLOR    (HSHADERTYPE_POSITION | HSHADERTYPE_TEXTURE | HSHADERTYPE_COLOR)

class CC_DLL HShaderCache: public HObject {
    HSINGLETON_OBJECT(HShaderCache);
public:
    CCGLProgram *getProgram(const char *key);
    void addProgram(const char *key, const char *vert, const char *frag, int shaderType);
    void removeProgram(const char *key);
    void removeAllPRograms();
    
    void reloadAllPrograms(CCObject *);
private:
    class HProgramData: public CCObject {
        CC_SYNTHESIZE_RETAIN(CCGLProgram *, m_pProgram, Program);
        CC_SYNTHESIZE_RETAIN(CCString *, m_pVertex, Vertex);
        CC_SYNTHESIZE_RETAIN(CCString *, m_pFragment, Fragment);
        CC_SYNTHESIZE(int, m_iShaderType, ShaderType);
    public:
        HProgramData(const char *vert, const char *frag, int shaderType): m_pProgram(NULL),m_pVertex(NULL), m_pFragment(NULL), m_iShaderType(shaderType) {
            setVertex(CCString::create(vert));
            setFragment(CCString::create(frag));
            reloadProgram();
        }
        ~HProgramData() { setProgram(NULL); setVertex(NULL); setFragment(NULL); }
        static HProgramData *create(const char *vert, const char *frag, int shaderType) {
            HProgramData *data = new HProgramData(vert, frag, shaderType);
//            data->autorelease();
            CC_AUTO_RELEASE(data);
            return data;
        }
        void reloadProgram();
    };
    CCDictionary *m_pPrograms;
    CCObject *asyncReloadAllPrograms(int, CCObject *);
};

HNAMESPACE_END

#endif // _SOURCE_CACHE_H__
