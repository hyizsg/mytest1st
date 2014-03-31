//
//  HCard.h
//  card
//
//  Created by zhou gang on 13-4-7.
//
//

#ifndef __card__HCard__
#define __card__HCard__

#include <map>
using namespace std;

class HCard : public HKey
{
public:
//    int id;
//    const char* icon;
//    const char* name;
//    const char* description;
//    char star_num;
//    char race;
    int type;
//    char level_max;
    int attack;
    int atk_acc;
    int hp;
    int hp_acc;
    int wait_times;
    int leaded;
    int skill[MAX_SKILL];
    const char* skill_tag[MAX_SKILL];
    
    typedef struct {
        const char* name;
        const char* description;
        int frag_id;
        int frag_num;
        int prop_id;
        int prop_level;
        int type;
        int args;
    } t_awake;
    
    const t_awake* awake[3];
    
public:
    
    
    HCard(void) {}
	~HCard(void) {}

    static vector<string> strings;
	static map<int, const HCard*> cards;
    
    static const HCard* cardById(int id)
    {
        return cards[id];
    }
    
    static int load()
    {
        cards.clear();
        strings.clear();
        
        load("config/card_basic.txt");
//        load("config/luxiang.txt");
        
        return cards.size();
    }
    
	static int load(const char* txt)
	{
        LOAD_STRING_NOCLEAN(txt);
        
        char buff[64] = {0};
        
		for (int i = 0; i<strings.size();) 
		{
			HCard * c = new HCard();
			c->id = atoi(strings[i++].c_str());
			c->icon = strings[i++].c_str();
            c->name = strings[i++].c_str();
            c->description = strings[i++].c_str();
			c->star_num = atoi(strings[i++].c_str());
			c->race = atoi(strings[i++].c_str());
            c->type = atof(strings[i++].c_str());
			c->level_max = atoi(strings[i++].c_str());
			c->attack = atoi(strings[i++].c_str());
			c->atk_acc = atoi(strings[i++].c_str());
			c->hp = atoi(strings[i++].c_str());
			c->hp_acc = atoi(strings[i++].c_str());
			c->wait_times = atoi(strings[i++].c_str());
			c->leaded = atoi(strings[i++].c_str());
            
            for (int j=0; j<MAX_SKILL; j++, i++) {
                
                c->skill[j] = atoi(strings[i].c_str()); // (strings[i++]);
                
                string::size_type pos = strings[i].find('_');
                if (pos == string::npos) {
                    c->skill_tag[j] = "";
                }else{
                    c->skill_tag[j] = strings[i][pos+1] == '1' ? "【降临】" : "【死契】";
                }
                
//                CCLOG("%d: %s - %s", c->id, strings[i].c_str(), c->skill_tag[j]);
            }
            
//            c->skill[3] = c->skill[2];
            
            for (int j =0; j<3; j++) {
                t_awake* ta = new t_awake;
                ta->name = strings[i++].c_str();
                ta->description = strings[i++].c_str();
                
                strcpy(buff, strings[i++].c_str());
                vector<char*> pl = split(buff, ";");
                
                if (pl.size() == 1) {
                    ta->frag_id = 0;
                    ta->frag_num = 0;
                }else{
                    ta->frag_id = atoi(pl[0]);
                    ta->frag_num = atoi(pl[1]);
                }
                
                strcpy(buff, strings[i++].c_str());
                pl = split(buff, ";");
                
                if (pl.size() == 1) {
                    ta->prop_id = 0;
                    ta->prop_level = 0;
                }else{
                    ta->prop_id = atoi(pl[0]);
                    ta->prop_level = atoi(pl[1]);
                }
                
                ta->type = atoi(strings[i++].c_str());
                ta->args = atoi(strings[i++].c_str());
                
                c->awake[j] = ta;
                
            }
            
            
//            i+=18;
			
			cards[c->id] = c;
		}
        
        return cards.size();
	}
};

#endif /* defined(__card__HCard__) */
