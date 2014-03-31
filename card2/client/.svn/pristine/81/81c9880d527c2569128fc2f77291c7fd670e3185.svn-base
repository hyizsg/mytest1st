//
//  Haypi-JSBObject.m
//  MoonWarriors
//
//  Created by jim kaden on 13-4-27.
//
//
#include "Haypi-JSBObject.h"


static HaypiNetCallback theNetCallback;

void* HaypiNetCallback_routine(void* param);

HaypiNetCallback* HaypiNetCallback::sharedInstance()
{
    return &theNetCallback;
}

HaypiNetCallback::HaypiNetCallback()
{
//    pthread_rwlock_init(&_rwLock,NULL);
//    pthread_create(&_thread, NULL, HaypiNetCallback_routine, this);
}

HaypiNetCallback::~HaypiNetCallback()
{
//    pthread_rwlock_destroy(&_mapLock);
}

bool HaypiNetCallback::addCallback(std::string key, GS_Func obj)
{
    if ( _netCallbackMap.find(key) != _netCallbackMap.end() )
        return false;
    _netCallbackMap.insert(NetCallbackPair(key, obj));
    return true;
}

bool HaypiNetCallback::setCommonhandler(HaypiJSBCmd* cmd)
{
    if ( _commandHandler )
    {
        // to do: notify
        _commandHandler = cmd;
    }
    else
    {
        _commandHandler = cmd;
    }
    return true;
}

bool HaypiNetCallback::removeCallback(std::string  key)
{
    NetCallbackMap::iterator it = _netCallbackMap.find(key);
    if ( it == _netCallbackMap.end())
        return false;
    _netCallbackMap.erase(it);
    return true;
}


GS_Func HaypiNetCallback::getCallback(std::string  key)
{
    NetCallbackMap::iterator it = _netCallbackMap.find(key);
    if ( it == _netCallbackMap.end())
        return NULL;
    return it->second;
}

void* HaypiNetCallback_routine(void* param)
{
    HaypiNetCallback* haypiNet = (HaypiNetCallback*)param;
    haypiNet->routine();
    return NULL;
}

void HaypiNetCallback::routine()
{
    while(0)
    {
        
    }
}

long long HaypiNetCallback::getHashCode()
{
//    return Helper_getSocketHashCode();
    return 0LL;
}

long long HaypiNetCallback::getMemberID()
{
//    return Helper_getSocketMemberID();
    return 0LL;
}

static bool isJSBCMD(int action)
{
    return false;
}

bool callback_JSB(int actionkey, int action, CCDictionary* response)
{
    if ( isJSBCMD(action) )
    {
        HaypiJSBCmd* jsbCmd = theNetCallback.getCommonHandler();
        if ( jsbCmd )
        {
            jsbCmd->callback(response);
            return true;
        }
    }
    return false;
}
