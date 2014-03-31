//
//  Haypi-Wrapper.mm
//  Haypi-JSB
//
//  Created by jim kaden on 13-4-25.
//
//
#ifndef __HAYPI_WRAPPER_H__
#define __HAYPI_WRAPPER_H__
#include <string>
//#ifdef __cplusplus
//extern "C" {
//#endif

    int HaypiWrapper_sendCmd(char* context, JSObject* callbackPtr, const char* funcName);
    int HaypiWrapper_setCommandHandler(JSObject* callbackPtr);
    char* HaypiWrapper_createJsonWithAction(int action);
    char* HaypiWrapper_getNameByScreen(char* resourceName);
    long long HaypiWrapper_getHashCode();
    long long HaypiWrapper_getMemberID();
//#ifdef __cplusplus
//}
//#endif

#endif