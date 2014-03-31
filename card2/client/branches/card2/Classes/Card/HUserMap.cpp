//
//  HUserMap.cpp
//  card
//
//  Created by zhou gang on 13-6-4.
//
//

#include "../headers.h"

HSINGLETON_OBJECT_IMP(HUserMap);

HUserMap::HUserMap()
: m_player(NULL)
{
    
}

HUserMap::~HUserMap()
{
    
}

void HUserMap::updateMapLevel(cocos2d::CCArray *arr)
{
    m_mapLevel.clear();
    m_mapList.clear();

    if (arr != NULL && arr->count() > 0) {
        _updateVectorByArr(m_mapList, arr->data->arr, arr->data->num, cstring_int_fun());
        _updateSetByArr(m_mapLevel, arr->data->arr, arr->data->num, cstring_int_fun());
    }
}

const char* HUserMap::getMapFile(int idx)
{
#ifdef ANDROID
    return idx == 0 ? "game/img/gk_paper.pkm" : "game/img/gk_paper2.pkm";
#else
    return idx == 0 ? "game/img/gk_paper.jpg" : "game/img/gk_paper2.png";
#endif
}

bool HUserMap::isMapIdPassed(int mapId)
{
    return mapId == 0 || m_mapLevel.find(mapId) != m_mapLevel.end();
}

bool HUserMap::isMapIdOpened(int mapId)
{
    const HLevel* level = getLevelById(mapId);
    return isMapIdPassed(mapId) || (level != NULL && isMapIdPassed(level->pre_level) && (level->pre_star[0] == 0 || starOpenedCount(level->pre_star[0]) >= level->pre_star[1]));
}

bool HUserMap::isChapterOpened(int chapterIndex)
{
    return isMapIdOpened(indexToMapId(chapterIndex, 0, 0));
}

bool HUserMap::isLevelOpened(int chapterIndex, int levelIndex)
{
    return isMapIdOpened(indexToMapId(chapterIndex, levelIndex, 0));
}

bool HUserMap::isMapOpened(int chapterIndex, int levelIndex, int diffIndex)
{
    return isMapIdOpened(indexToMapId(chapterIndex, levelIndex, diffIndex));
}

bool HUserMap::isMapPassed(int chapterIndex, int levelIndex, int diffIndex)
{
    return isMapIdPassed(indexToMapId(chapterIndex, levelIndex, diffIndex));
}

int HUserMap::indexToMapId(int chapterIndex, int lvIndex, int diffIndex)
{
    return (chapterIndex+1)*1000 + (lvIndex+1)*10 + diffIndex+1;
}

int HUserMap::mapIdToChapterIndex(int mapId)
{
    return mapId / 1000 - 1;
}

int HUserMap::mapIdToLevelIndex(int mapId)
{
    return (mapId / 10) % 100 - 1;
}

int HUserMap::mapIdToDiffIndex(int mapId)
{
    return mapId % 10 - 1;
}

int HUserMap::levelCount(int chapterIndex)
{
    int lvcount = 0;
    
    for (int i=0; ; i++) {
        if (getLevelById(indexToMapId(chapterIndex, i, 0)) != NULL) {
            lvcount++;
        }else
            break;
    }
    
    return lvcount;
}

int HUserMap::levelPassedCount(int chapterIndex)
{
    int lvcount = 0;
    for (int i=0; ; i++) {
        if (isMapIdPassed(indexToMapId(chapterIndex, i, 0))) {
            lvcount++;
        }else{
            break;
        }
    }
    
    return lvcount;
}

int HUserMap::levelOpenedCount(int chapterIndex)
{
    int lvcount = 0;
    int nMax = levelCount(chapterIndex);
    for (int i=0; i<nMax ; i++) {
        if (isMapIdOpened(indexToMapId(chapterIndex, i, 0))) {
            lvcount++;
        }else{
            break;
        }
    }
    
    return lvcount;
}

int HUserMap::levelLastOpenedIndex(int chapterIndex)
{
    return levelOpenedCount(chapterIndex) - 1;
}

int HUserMap::subDiffCount(int chapterIndex, int levelIndex)
{
    int subcount = 0;
    
    for (int i=0; ; i++) {
        if (getLevelById(indexToMapId(chapterIndex, levelIndex, i)) != NULL) {
            subcount++;
        }else
            break;
    }
    
    return subcount;
    return 3; // config the max is 3; fuck lai xue modify it
}

int HUserMap::subDiffPassedCount(int chapterIndex, int levelIndex)
{
    int dicount = 0;
    int nMax = subDiffCount(chapterIndex, levelIndex);
    for (int i=0; i< nMax;i++) {
        if (isMapIdPassed(indexToMapId(chapterIndex, levelIndex, i))) {
            dicount++;
        }else{
            break;
        }
    }
    
    return dicount;
}

int HUserMap::subDiffOpenedCount(int chapterIndex, int levelIndex)
{
    int dicount = 0;
    int nMax = subDiffCount(chapterIndex, levelIndex);
    for (int i=0; i<nMax ;i++) {
        if (isMapIdOpened(indexToMapId(chapterIndex, levelIndex, i))) {
            dicount++;
        }else{
            break;
        }
    }
    
    return dicount;
}

int HUserMap::subDiffOpenedLastIndex(int chapterIndex, int levelIndex)
{
    return subDiffOpenedCount(chapterIndex, levelIndex) - 1;
}

int HUserMap::starCount(int chapterIndex)
{
    int count = 0;
    
    int lvcount = levelCount(chapterIndex);
    for (int i=0; i<lvcount; i++) {
        count += subDiffCount(chapterIndex, i);
    }
    
    return count;
}

int HUserMap::starOpenedCount(int chapterIndex)
{
    int starNum = 0;
    
    int lvopened = levelPassedCount(chapterIndex);
    for (int j=0; j<lvopened; j++) {
        starNum += subDiffPassedCount(chapterIndex, j);
    }
    
    return starNum;
}

int HUserMap::hideLevelCount(int chapterIndex)
{
    int count = 0;
    
    int lvcount = levelCount(chapterIndex);
    for (int i=0; i<lvcount; i++) {
        const HLevel* level = getLevelById(indexToMapId(chapterIndex, i, 0));
        if (level->pre_star[0] > 0) {
            count++;
        }
    }
    
    return count;
}

template <typename T1, typename P, typename FuncValue>
void HUserMap::_updateSetByArr(set<T1> & tset, P* begin, int count, FuncValue funValue)
{
    for (P* it = begin; it<= begin+count-1; it++) {
        tset.insert(funValue(*it));
    }
}

template <typename T, typename P, typename Func>
void HUserMap::_updateVectorByArr(vector<T> & vec, P* begin, int count, Func fun)
{
    for (P* it = begin; it<= begin+count-1; it++) {
        vec.push_back(fun(*it));
    }
}

void HUserMap::updateHeaven(CCArray* arr)
{
    m_heaven.clear();
    FOREACH(CCDictionary*, heaven, arr) {
        HTower tower;
        tower.id = PARSE_INT(heaven, "ID");
        tower.tower = PARSE_INT(heaven, "Tower");
        tower.layer = PARSE_INT(heaven, "CurLayer");
        tower.max_layer = PARSE_INT(heaven, "MaxLayer");
        tower.speed = PARSE_INT(heaven, "Speed")+0;
        tower.max_speed = PARSE_INT(heaven, "MaxSpeed");
        tower.challenge = PARSE_INT(heaven, "Challenge");
        tower.buy_num = PARSE_INT(heaven, "BuyNum");
        tower.max_buy_num = PARSE_INT(heaven, "MaxBuyNum");
        tower.reset_gold = PARSE_INT(heaven, "ResetGold");
        m_heaven.push_back(tower);
    }
}

const HUserMap::HTower* HUserMap::getTowerByLayer(int layer)
{
    if (m_heaven.size() >= layer) {
        return & (m_heaven[layer-1]);
    }
    
    return NULL;
}




