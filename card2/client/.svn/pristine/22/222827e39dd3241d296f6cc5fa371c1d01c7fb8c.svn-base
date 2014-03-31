//
//  HaypiJSBSocket.m
//  MoonWarriors
//
//  Created by jim kaden on 13-4-28.
//
//

#include "Haypi-JSBObject.h"
#include <sys/stat.h>
#include "../NetManager.h"

char* Helper_createJsonWithAction(int action)
{
    const char *json = haypi::HNetManager::getInstance()->createJsonWithAction(action);
    char* ret = strdup(json);
    return ret;
//	return strdup("{}");
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
    std::string str = CCFileUtils::sharedFileUtils()->getWritablePath();
    str += "release/";
    Helper_createDir((char *)str.c_str());
    str += path;
    return str;
#else
#endif
}

std::string Helper_getDeviceID()
{
#ifdef HOS_APPLE
    return std::string(getHaypiDeviceID());
#else
    return std::string((char*)haypi::HNetManager::getInstance()->getDeviceID()->getCString());
#endif
}

extern char *loadFileFromAssets(char* filename, int& len);
std::string Helper_getBundleVersion()
{
#ifdef HOS_APPLE
    NSString* path = [[NSBundle mainBundle] pathForResource:@"ResourceVersion" ofType:nil];
    NSString* content = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    if ( content == nil )
        return std::string("");
    return std::string([content UTF8String]);
#else
    int len;
    char* ch = loadFileFromAssets("ResourceVersion", len);
    std::string str = std::string(ch);
    delete[] ch;
    return str;
#endif
}
