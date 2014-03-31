//
//  HFcMember.h
//  card
//
//  Created by zhou gang on 13-12-25.
//
//

#ifndef __card__HFcMember__
#define __card__HFcMember__

class HFcMember {
    
    
public:
    int jobId;
    int lvup_point;
    int shop_discount;
    int fyg_gain_timer;
    int rank_point;
    int rank_killed_point;
    int prv_kick;
    int prv_add;
    
    static vector<string> strings;
    static map<int, const HFcMember*> members;
    
    
    static const HFcMember* memberById(int id)
    {
        return members[id];
    }
    
	static int load();
    
};

class HFcIcon {
    
    
public:
    int id;
    const char* icon;
    
    static vector<string> strings;
    static map<int, const HFcIcon*> icons;
    
    
    static const HFcIcon* iconById(int id)
    {
        return icons[id];
    }
    
	static int load();
};

#endif /* defined(__card__HFcMember__) */
