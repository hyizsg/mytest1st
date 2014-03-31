//
//  HaypiJSBFunc
//
//  Created by jim kaden on 13-4-28.
//
//

#include "Haypi-JSBObject.h"
#include <sys/stat.h>
#ifdef HOS_APPLE
#import "Haypi/Haypi.h"
#endif
char* Helper_createJsonWithAction(int action)
{
#ifdef HOS_APPLE
    HaypiJson json = createJsonOnlyWithAction(action, getLastGameMode());
    char* ret = strdup((char*) jsonToStr(json));
    deleteJson(json);
    return ret;
#elif HOS_LINUX
    
#else
    
#endif
}

extern int Helper_getSocketHashCode()
{
    return 0;
}

extern int Helper_getSocketMemberID()
{
    return 0;
}

extern bool Helper_sendCmd(const char* request)
{
    return false;
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
    Helper_createDir((char *)str.c_str());
    str += path;
    Helper_createDir((char *)str.c_str());
    return ret;
#else
#endif
}

std::string Helper_getDeviceID()
{
#ifdef HOS_APPLE
    return std::string(getHaypiDeviceID());
#else
    return std::string("");
#endif
}

std::string Helper_getBundleVersion()
{
#ifdef HOS_APPLE
    NSString* path = [[NSBundle mainBundle] pathForResource:@"ResourceVersion" ofType:nil];
    NSString* content = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    if ( content == nil )
        return std::string("");
    return std::string([content UTF8String]);
#else
    return std::string("");
#endif
}