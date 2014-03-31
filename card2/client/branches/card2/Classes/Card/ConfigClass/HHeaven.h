//
//  HHeaven.h
//  card
//
//  Created by zhou gang on 13-5-14.
//
//

#ifndef __card__HHeaven__
#define __card__HHeaven__

class HHeaven  {
    
    
public:
    int id;
    int open_id;
    int pre_id;
    int tower;
    int layer;
    int max_layer;
    int max_speed;
    int active;
    
    int reward_coin;
    int reward_exp;
    const char* reward_card;
    
    static vector<string> strings;
    static map<int, const HHeaven*> heavens;
    
    static map<int, vector<const HHeaven*> > heavensList;
    
	static int load()
	{
        LOAD_STRING("config/tiangong_base.txt");
        
        heavens.clear();
		for (int i = 0; i<strings.size();)
		{
			HHeaven * c = new HHeaven();
            c->id = atoi(strings[i++].c_str());
            c->open_id = atoi(strings[i++].c_str());
            c->pre_id = atoi(strings[i++].c_str());
            c->tower = atoi(strings[i++].c_str());
            c->layer = atoi(strings[i++].c_str());
            c->max_layer = atoi(strings[i++].c_str());
            c->max_speed = atoi(strings[i++].c_str());
            c->active = atoi(strings[i++].c_str());
            
            i+=21;
            
            c->reward_coin = atoi(strings[i++].c_str());
            c->reward_exp = atoi(strings[i++].c_str());
            c->reward_card = "1-3星卡片";
            
            i+=2;
            
   
            
            i++;
            i++;
            
            heavens[c->id] = c;
            heavensList[c->tower].push_back(c);
		}
        
        return heavens.size();
	}
    
};

#endif /* defined(__card__HHeaven__) */
