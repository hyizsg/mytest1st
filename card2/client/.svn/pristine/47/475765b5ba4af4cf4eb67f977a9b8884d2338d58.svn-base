
#include "cocos2dxframework.h"
#include "MusicManager.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

HNAMESPACE_BEGIN

HSINGLETON_OBJECT_IMP(HMusicManager);

HMusicManager::HMusicManager(): m_fBGMusicVolume(0.5f), m_fSoundEffectVolume(0.5f) {
    m_pMusics = new CCDictionary();
    
    load();
    
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m_fBGMusicVolume);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_fSoundEffectVolume);
}

HMusicManager::~HMusicManager() {
    delete m_pMusics;
}

void HMusicManager::setBGMusicVolume(float volume) {
    if (m_fBGMusicVolume != volume) {
        m_fBGMusicVolume = volume;
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m_fBGMusicVolume);
        save();
    }
}

float HMusicManager::getBGMusicVolume() {
    return m_fBGMusicVolume;
}

void HMusicManager::setSoundEffectVolume(float volume) {
    if (m_fSoundEffectVolume != volume) {
        m_fSoundEffectVolume = volume;
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_fSoundEffectVolume);
        save();
    }
}

float HMusicManager::getSoundEffectVolume() {
    return m_fSoundEffectVolume;
}

void HMusicManager::addMusic(CCString *musicFile, int musicID) {
    m_pMusics->setObject(musicFile, musicID);
}

void HMusicManager::addMusic(CCString *musicFile) {
    m_pMusics->setObject(musicFile, musicFile->getCString());
}

void HMusicManager::playMusic(int musicID, bool loop) {
    CCString *music = (CCString *)m_pMusics->objectForKey(musicID);
    if (music) {
//        std::string filename = HFileUtils::getLocalPath();
//        filename += music->getCString();
//        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(filename.c_str(), loop);
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(music->getCString(), loop);
    }
}

void HMusicManager::playMusic(CCString* musicFile, bool loop) {

    if (musicFile){
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(musicFile->getCString(), loop);
    }
    
}

int HMusicManager::playSoundEffect(CCString* effectFile, bool loop) {
    int retID = -1;
    
    if (effectFile) {
        retID = SimpleAudioEngine::sharedEngine()->playEffect(effectFile->getCString(), loop);
    }
    return retID;
}

int HMusicManager::playSoundEffect(int effectID, bool loop) {
    int retID = -1;
    CCString *effect = (CCString *)m_pMusics->objectForKey(effectID);
    if (effect) {
        retID = SimpleAudioEngine::sharedEngine()->playEffect(effect->getCString(), loop);
    }
    
    return retID;
}

void HMusicManager::stopSoundEffect(int nSoundId) {
    SimpleAudioEngine::sharedEngine()->stopEffect(nSoundId);
}

void HMusicManager::stopBackgroundMusic(bool bReleaseData) {
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(bReleaseData);
}

//private
void HMusicManager::load() {
    //delete by zg
    CCDictionary *dict = NULL; //HFileUtils::loadFromLocal("settings");
    if (dict) {
        m_fBGMusicVolume = dict->valueForKey("musicVolume")->floatValue();
        m_fSoundEffectVolume = dict->valueForKey("effectsVolume")->floatValue();
    }
}

void HMusicManager::save() {
    CCDictionary *dict = CCDictionary::create();
    dict->setObject(CCString::createWithFormat("%f", m_fBGMusicVolume), "musicVolume");
    dict->setObject(CCString::createWithFormat("%f", m_fSoundEffectVolume), "effectsVolume");
     //delete by zg
//    HFileUtils::saveToLocal(dict, "settings");
}

HNAMESPACE_END
