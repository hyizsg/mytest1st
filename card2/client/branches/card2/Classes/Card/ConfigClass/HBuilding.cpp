//
//  HBuilding.cpp
//  card
//
//  Created by zhou gang on 13-8-1.
//
//

#include "../../headers.h"
#include "HBuilding.h"

vector<string> HBuilding::strings;
map<int, const HBuilding*> HBuilding::buildings;

int HBuilding::load()
{
    LOAD_STRING("config/function.txt");
    
    buildings.clear();
    
    for (int i = 0; i<strings.size();)
    {
        HBuilding* bld = new HBuilding;
        bld->id = atoi(strings[i++].c_str());
        bld->name = strings[i++].c_str();
        bld->txt = strings[i++].c_str();
        bld->open_type = atoi(strings[i++].c_str());
        bld->open_args = atoi(strings[i++].c_str());
        bld->effect = strings[i++];
        if (bld->id == 110) {
            bld->effect = "qizhi_a0";
        }
        bld->locked_eff = strings[i++];
        buildings[bld->id] = bld;
    }
    
    return buildings.size();
}


vector<string> HFcBuilding::strings;
map<int, const HFcBuilding*> HFcBuilding::buildings;

int HFcBuilding::load()
{
    LOAD_STRING("config/gongnengbase.txt");
    
    buildings.clear();
    
    for (int i = 0; i<strings.size();)
    {
        HFcBuilding* bld = new HFcBuilding;
        bld->id = atoi(strings[i++].c_str());
        bld->name = strings[i++].c_str();
        bld->txt = strings[i++].c_str();
        bld->open_type = atoi(strings[i++].c_str());
        bld->open_args = atoi(strings[i++].c_str());
        bld->locked_eff = strings[i++].c_str();
        buildings[bld->id] = bld;
    }
    
    return buildings.size();
}