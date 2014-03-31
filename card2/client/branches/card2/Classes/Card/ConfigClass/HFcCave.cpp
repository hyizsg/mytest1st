//
//  HFcCave.cpp
//  card
//
//  Created by zhou gang on 14-1-2.
//
//

#include "headers.h"
#include "HFcCave.h"


vector<string> HFcCave::strings;
map<int, vector<HFcCave*> > HFcCave::caves;

int HFcCave::load()
{
    LOAD_STRING("config/menpaifb.txt");
    
    caves.clear();
    for (int i = 0; i<strings.size();)
    {
        HFcCave * c = new HFcCave();
        c->id = atoi(strings[i++].c_str());
        c->name = strings[i++].c_str();
        c->icon = strings[i++].c_str();
        c->reward = strings[i++].c_str();
        c->member_max = atoi(strings[i++].c_str());
        c->event_max = atoi(strings[i++].c_str());
        c->event = atoi(strings[i++].c_str());
        i++;
        c->pro = strings[i++].c_str();
        c->leader_reward = strings[i++].c_str();
        c->member_reward[0] = strings[i++].c_str();
        c->member_reward[1] = strings[i++].c_str();
        
        caves[c->id].push_back(c);
    }
    
    return caves.size();
}


vector<string> HFcCaveEvent::strings;
map<int, const HFcCaveEvent*> HFcCaveEvent::events;

int HFcCaveEvent::load()
{
    LOAD_STRING("config/menpaisj.txt");
    
    events.clear();
    for (int i = 0; i<strings.size();)
    {
        HFcCaveEvent * c = new HFcCaveEvent();
        c->id = atoi(strings[i++].c_str());
        c->type = atoi(strings[i++].c_str());
        c->name = strings[i++].c_str();
        c->icon = strings[i++].c_str();
        c->args = strings[i++].c_str();
        c->monster = atoi(strings[i++].c_str());
        c->atk_up = atoi(strings[i++].c_str());
        c->hp_up = atoi(strings[i++].c_str());
        c->drop_num = atoi(strings[i++].c_str());
        c->drop_args = strings[i++].c_str();
        c->drop_pro = strings[i++].c_str();
        
        events[c->id] = (c);
    }
    
    return events.size();
}



vector<string> HFcTech::strings;
map<int, vector<HFcTech*> > HFcTech::events;

int HFcTech::load()
{
    LOAD_STRING("config/menpaibase.txt");
    
    events.clear();
    for (int i = 0; i<strings.size();)
    {
        HFcTech * c = new HFcTech();
        c->id = nextint();
        c->level = nextint();
        c->max_lv = nextint();
        c->icon = nextstr();
        c->type = nextint();
        c->name = nextstr();
        c->desc = nextstr();
        c->lvup_exp = nextint();
        c->lvup_pre = nextstr();
        c->func = nextint();
        c->args_type = nextint();
        c->args = nextint();
        
        events[c->id].push_back(c);
    }
    
    return events.size();
}



