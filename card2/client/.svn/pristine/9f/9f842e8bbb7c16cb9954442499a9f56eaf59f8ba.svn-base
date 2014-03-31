//
//  HaypiJSBSocket.m
//  MoonWarriors
//
//  Created by jim kaden on 13-4-28.
//
//

#include "Haypi-JSBObject.h"
#include <sys/stat.h>
char* Helper_createJsonWithAction(int action)
{
//    HaypiJson json = createJsonOnlyWithAction(action, getLastGameMode());
//    char* ret = strdup((char*) jsonToStr(json));
//    deleteJson(json);
//    return ret;
}

extern int Helper_getSocketHashCode()
{
//    return [[HaypiJSBSocket sharedInstance] getHashCode];
}

extern int Helper_getSocketMemberID()
{
//    return [[HaypiJSBSocket sharedInstance] getMemberID];
}

extern bool Helper_sendCmd(const char* request)
{
//    return [[HaypiJSBSocket sharedInstance] send:request];
}

void Helper_createDir(char* path)
{
#ifdef HOS_APPLE
    NSFileManager* fm = [NSFileManager defaultManager];
    [fm createDirectoryAtPath:[NSString stringWithUTF8String:path] withIntermediateDirectories:YES attributes:nil error:nil];
#elif HOS_LINUX
    mkdir( path, S_IRWXU);
#else
    mkdir( path);
#endif
}

std::string Helper_getPathForName(char* path)
{
#ifdef HOS_APPLE
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSFileManager* fm = [NSFileManager defaultManager];
    NSString* releaseDir = [NSString stringWithFormat:@"%@/release", documentsDirectory];
    [fm createDirectoryAtPath:releaseDir withIntermediateDirectories:YES attributes:nil error:nil];
    
    NSString *pathStr = [NSString stringWithFormat:@"%@/release/%s", documentsDirectory, path];
    return std::string((char*)[pathStr UTF8String]);
#elif HOS_LINUX
    std::string str = CCFileUtils::sharedFileUtils()->getWriteablePath();
    str += "release/";
    Helper_createDir(str.c_str());
    str += path;
    Helper_createDir(str.c_str());
    return ret;
#else
#endif
}

std::string Helper_downloadFromUrl(char* url)
{
    // 不在主线程调用
#ifdef HOS_APPLE    
    @try
    {
        char* pos = strrchr(url, '.');
        char* path = NULL;
        if ( pos == NULL )
            path = (char*)[[[NSDate date] description] UTF8String];
        else
            path = (char*)[[[[NSDate date] description] stringByAppendingString:[NSString stringWithUTF8String:pos]] UTF8String];
        NSString *pathStr = [NSString stringWithUTF8String:Helper_getPathForName(path).c_str()];
        NSString *hostUrl = [NSString stringWithUTF8String:url];
        NSData* data = [NSData dataWithContentsOfURL:[NSURL URLWithString:hostUrl]];
        [data writeToFile:pathStr atomically:YES];
        return std::string((char*)[pathStr UTF8String]);
    }
    @catch (NSException *exception)
    {
        return std::string("");
    }
#elif HOS_LINUX
    try
    {
        /*
        time_t curtime;
        time(&curtime);
        char* pos = strrchr(url, '.');
        char path[260];
        if ( pos == NULL )
            sprintf(path, "%d", curtime);
        else
            sprintf(path, "%d%s", curtime, pos);
        
        std::string realPath = Helper_getPathForName(path);
        
        cocos2d::CCHttpRequest* request = new cocos2d::CCHttpRequest();
        request->setRequestType(cocos2d::CCHttpRequest::kHttpGet);
        request->setUrl((const char*)url);
        cocos2d::CCHttpClient::getInstance()->send(request);
        */
        // to be continue
        
        
    }
    catch (...)
    {
    
    }
    
    return std::string("");
#else
#endif
}