#ifndef _MUSIC_MANAGER_H_
#define _MUSIC_MANAGER_H_

HNAMESPACE_BEGIN

class CC_DLL HMusicManager {
    HSINGLETON_OBJECT(HMusicManager);
    CC_PROPERTY(float, m_fBGMusicVolume, BGMusicVolume);
    CC_PROPERTY(float, m_fSoundEffectVolume, SoundEffectVolume);
public:
    void addMusic(CCString *musicFile, int musicID);
    void addMusic(CCString *musicFile);
    
    void playMusic(int musicID, bool loop = true);
    void playMusic(CCString *musicFile, bool loop = true);
    
    int playSoundEffect(int effectID, bool loop = false);
    int playSoundEffect(CCString *effectFile, bool loop = true);
    
    void stopSoundEffect(int soundID);
    void stopBackgroundMusic(bool bReleaseData = true);
private:
    CCDictionary *m_pMusics;
    void load();
    void save();
};

HNAMESPACE_END

#endif // _MUSIC_MANAGER_H_
