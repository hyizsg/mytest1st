//
//  HThreadSprite.m
//  card
//
//  Created by zhou gang on 13-5-24.
//
//

#include "../../../headers.h"

#ifdef CC_TARGET_OS_IPHONE

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "UpdateManager.h"

string HThreadTextureCache::fullPathFromRelativePath(const char *pszRelativePath)
{
    @autoreleasepool {
        return CCFileUtils::sharedFileUtils()->fullPathForFilename(pszRelativePath).c_str();
    }
}

CCTexture2D* HThreadTextureCache::addImage(const char *path, CCImage::EImageFormat eFmt, HThreadData *tData)
{
    unsigned long nSize = 0;
    unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(path, "rb", &nSize);
    
    clock.load_file_data = getCurrentTime();
    
    CCTexture2D* texture = NULL;
    
    @autoreleasepool {
        CCImage* image = new CCImage;
        if (! image->initWithImageData((void*)pBuffer, nSize, eFmt))
        {
            image->release();
            return NULL;
        }
        
        clock.create_tmp_image = getCurrentTime();
        
        CCArray* array = new CCArray(2);
        array->addObject(image);
        array->addObject(tData);
        
        HTimerManager::getInstance()->processOnMainThread(HInvocation::create(this, hinvocation_selector(HThreadTextureCache::onMainThreadCreateTexture), 0, array), true);
        
        texture = tData->getTexture();
        
#if CC_ENABLE_CACHE_TEXTURE_DATA
        // cache the texture file name
        VolatileTexture::addImageTexture(texture, path, eFmt);
#endif
        
        image->release();
        array->release();
        
    }
    
    CC_SAFE_DELETE_ARRAY(pBuffer);
    
    return texture;
}

CCObject* HThreadTextureCache::onMainThreadCreateTexture(int command, CCObject* obj)
{
    clock.wait_main_thread = getCurrentTime();
    
    CCArray* array = (CCArray*)obj;
    CCImage* image = dynamic_cast<CCImage*>(array->objectAtIndex(0));
    HThreadData* tData = dynamic_cast<HThreadData*>(array->objectAtIndex(1));
    
    CCTexture2D * texture = new CCTexture2D();
    
    if( texture && texture->initWithImage((image)))
    {
        clock.create_texture = getCurrentTime();
        
        tData->setTexture(texture);
        texture->release();
        
        onMainThreadSetting(0, tData);
    }
    
    return texture;
}
 
 

#endif
