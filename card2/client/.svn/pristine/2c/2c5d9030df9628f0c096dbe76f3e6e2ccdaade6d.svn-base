//
//  HUserMap.h
//  card
//
//  Created by zhou gang on 13-6-4.
//
//

#ifndef __card__HUserMap__
#define __card__HUserMap__

class HUserMap : public CCObject {
    HSINGLETON_OBJECT(HUserMap);
    
public:
    
    typedef struct {
        int tower;
        int id;
        int layer;
        int max_layer;
        int speed;
        int max_speed;
        int challenge;
        int buy_num;
        int max_buy_num;
        int reset_gold;
    } HTower;
    
    CC_SYNTHESIZE(HPlayer*, m_player, Player);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(set<int>, m_mapLevel, MapLevel);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<int>, m_mapList, MapList);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<HTower>, m_heaven, HeavenList);
    
    void updateMapLevel(CCArray* arr);
    void updateHeaven(CCArray* arr);
    
    bool isMapIdPassed(int mapId);
    bool isMapIdOpened(int mapId);
    
    bool isChapterOpened(int chapterIndex);
    bool isLevelOpened(int chapterIndex, int levelIndex);
    bool isMapOpened(int chapterIndex, int levelIndex, int diffIndex);
    bool isMapPassed(int chapterIndex, int levelIndex, int diffIndex);
    

    int indexToMapId(int chapterIndex, int lvIndex, int diffIndex);
    
    int mapIdToChapterIndex(int mapId);
    int mapIdToLevelIndex(int mapId);
    int mapIdToDiffIndex(int mapId);
    
    int levelCount(int chapterIndex);
    int levelPassedCount(int chapterIndex);
    int levelOpenedCount(int chapterIndex);
    int levelLastOpenedIndex(int chapterIndex);
    
    int subDiffCount(int chapterIndex, int levelIndex);
    int subDiffPassedCount(int chapterIndex, int levelIndex);
    int subDiffOpenedCount(int chapterIndex, int levelIndex);
    int subDiffOpenedLastIndex(int chapterIndex, int levelIndex);
    
    int starCount(int chapterIndex);
    int starOpenedCount(int chapterIndex);
    
    int hideLevelCount(int chapterIndex);
    
    const HTower* getTowerByLayer(int layer);
    
    const char* getMapFile(int idx) ;
    
protected:
    
    friend class HPlayer;
    
    
    template <typename T, typename P, typename Func>
    static void _updateVectorByArr(vector<T> & vec, P* begin, int count, Func fun);
    
    template <typename T1, typename P, typename FuncValue>
    static void _updateSetByArr(set<T1> & tset, P* begin, int count, FuncValue funValue);
    
    // 2 01 2
    struct cstring_chapter_fun { int operator()(CCObject* str) { return ((CCString*)str)->intValue() / 1000;} };
    struct cstring_level_fun { int operator()(CCObject* str) { return ((CCString*)str)->intValue() / 10;} };
};

static inline HUserMap* getCurrMap()
{
    return HUserMap::getInstance();
}



#endif /* defined(__card__HUserMap__) */
