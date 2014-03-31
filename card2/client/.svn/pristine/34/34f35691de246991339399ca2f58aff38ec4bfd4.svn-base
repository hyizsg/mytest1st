//
//  HFcCave.h
//  card
//
//  Created by zhou gang on 14-1-2.
//
//

#ifndef __card__HFcCave__
#define __card__HFcCave__

class HFcCave {
    
    
public:
    int id;
    const char* name;
    const char*  icon;
    const char*  reward;
    int member_max;
    int event_max;
    int event;
    const char*  pro;
    const char*  leader_reward;
    const char*  member_reward[2];
    
    static vector<string> strings;
    static map<int, vector<HFcCave*> > caves;
    
    
    static const HFcCave* caveById(int id, int event = 0)
    {
        return caves[id][event];
    }
    
	static int load();
};

class HFcCaveEvent  {
    
    
public:
    int id;
    int type;
    const char*  name;
    const char*  icon;
    const char*  args;
    int monster;
    int atk_up;
    int hp_up;
    int drop_num;
    const char*  drop_args;
    const char*  drop_pro;
    
    static vector<string> strings;
    static map<int, const HFcCaveEvent*> events;
    
    
    static const HFcCaveEvent* eventById(int id)
    {
        return events[id];
    }
    
	static int load();
};

class HFcTech {
    
    
public:
    int id;
    int level;
    int max_lv;
    const char* icon;
    int type;
    const char* name;
    const char* desc;
    int lvup_exp;
    const char* lvup_pre;
    int func;
    int args_type;
    int args;
    
    static vector<string> strings;
    static map<int, vector<HFcTech*> > events;
    
    
    static const HFcTech* techById(int id, int lv)
    {
        return events[id][lv];
    }
    
	static int load();
};

#endif /* defined(__card__HFcCave__) */
