//
//  HBuilding.h
//  card
//
//  Created by zhou gang on 13-8-1.
//
//

#ifndef __card__HBuilding__
#define __card__HBuilding__

class HBuilding  {
public:
    int id;
    const char* name;
    const char* txt;
    int open_type;
    int open_args;
    string effect;
    string locked_eff;
    
public:
    static vector<string> strings;
    static map<int, const HBuilding*> buildings;
    
	static int load();
};

static inline const HBuilding* getBuildingById(int id)
{
    return HBuilding::buildings[id];
}

static inline bool isBuildingOpened(int id)
{
    const HBuilding* build = HBuilding::buildings[id];
    if (build == NULL) {
        
    }else if (build->open_type == 0) {
        return true;
    }else if(build->open_type == 1){
        return getCurrPlayer()->getLevel() >= build->open_args;
    }else if(build->open_type == 2) {
        return getCurrMap()->isMapIdPassed(build->open_args);
    }
    
    return true;
}


//#include "HFactionDefine.h"

class HFcBuilding  {
public:
    int id;
    const char* name;
    const char* txt;
    int open_type;
    int open_args;
    const char* locked_eff;
    
public:
    static vector<string> strings;
    static map<int, const HFcBuilding*> buildings;
    
	static int load();
};

static inline const HFcBuilding* getFcBuildingById(int id)
{
    return HFcBuilding::buildings[id];
}

static inline bool isFcBuildingOpened(int id)
{
    const HFcBuilding* build = HFcBuilding::buildings[id];
    if (build == NULL) {
        
    }else if (build->open_type == 0) {
        return true;
    }else {
//        const HFcTechInfo* tech = HFaction::getTechInfoByID(build->open_type) ;
//        return tech && tech->level >= build->open_args;
        return false;
    }
    
    return true;
}

#endif /* defined(__card__HBuilding__) */
