//
//  HFcMember.cpp
//  card
//
//  Created by zhou gang on 13-12-25.
//
//

#include "headers.h"
#include "HFcMember.h"

vector<string> HFcMember::strings;
map<int, const HFcMember*> HFcMember::members;

int HFcMember::load()
{
    LOAD_STRING("config/member.txt");
    
    members.clear();
    for (int i = 0; i<strings.size();)
    {
        HFcMember * c = new HFcMember();
        c->jobId = atoi(strings[i++].c_str());
        c->lvup_point = atoi(strings[i++].c_str());
        c->shop_discount = atoi(strings[i++].c_str());
        c->fyg_gain_timer = nextint();
        c->rank_point = nextint();
        c->rank_killed_point = nextint();
        c->prv_kick = nextint();
        c->prv_add = nextint();
        
        members[c->jobId] = c;
    }
    
    return members.size();
}


vector<string> HFcIcon::strings;
map<int, const HFcIcon*> HFcIcon::icons;

int HFcIcon::load()
{
    LOAD_STRING("config/tubiao.txt");
    
    icons.clear();
    for (int i = 0; i<strings.size();)
    {
        HFcIcon * c = new HFcIcon();
        c->id = nextint();
        c->icon = nextstr();
        
        icons[c->id] = c;
    }
    
    return icons.size();
}



