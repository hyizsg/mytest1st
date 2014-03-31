//
//  HHero.h
//  card
//
//  Created by zhou gang on 13-4-9.
//
//

#ifndef __card__HHero__
#define __card__HHero__

#include <map>
using namespace std;

class HHero
{
public:
    int level;
    int exp;
    int hp;
    int lead_power;
    int energy;
    int giveenergy;
    int card_num;
    int magic_num;
    int card_group_num;
    int friend_num;
    int card_max_num;
    int magic_max_num;
    int open_item;
    
public:
    
    static vector<string> strings;
	static map<int, const HHero*> heros;
    
	static int load()
	{
        LOAD_STRING("config/hero_base.txt");
        
        heros.clear();
		for (int i = 0; i < strings.size(); )
		{
			HHero * c = new HHero();
            c->level = atoi(strings[i++].c_str());
			c->exp = atoi(strings[i++].c_str());
            c->hp = atoi(strings[i++].c_str());
            c->lead_power = atoi(strings[i++].c_str());
            c->energy = atoi(strings[i++].c_str());
            c->giveenergy = atoi(strings[i++].c_str());
            c->card_num = atoi(strings[i++].c_str());
            c->magic_num = atoi(strings[i++].c_str());
            c->card_group_num = atoi(strings[i++].c_str());
            c->friend_num = atoi(strings[i++].c_str());
            c->card_max_num = atoi(strings[i++].c_str());
            c->magic_max_num = atoi(strings[i++].c_str());
            c->open_item = atoi(strings[i++].c_str());
			heros[c->level] = c;
		}
        
        HHero* c = new HHero; memset(c, 0, sizeof(HHero));
        heros[-1] = c; heros[0] = c;
        
        return heros.size();
	}
};




#endif /* defined(__card__HHero__) */
