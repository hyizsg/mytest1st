//
//  HMonster.h
//  card
//
//  Created by zhou gang on 13-7-2.
//
//

#ifndef __card__HMonster__
#define __card__HMonster__

class HMonster {
    
    
public:
    int id;
    int icon;
    const char* name;
    int level;
    const char* four_symbol;
    vector<int> monster;
    
public:
    
    static vector<string> strings;
    static map<int, const HMonster*> monsters;
    
	static int load()
    {
        LOAD_STRING("config/monster.txt");
        
        monsters.clear();
        for (int i=0; i<strings.size();) {
            HMonster* gd = new HMonster;
            gd->id = atoi(strings[i++].c_str());
            gd->icon = atoi(strings[i++].c_str());
            gd->name = strings[i++].c_str();
            gd->level = atoi(strings[i++].c_str());
            gd->four_symbol = strings[i++].c_str();
            
            for (int j=0; j<10; j++) {
                gd->monster.push_back(atoi(strings[i++].c_str()));
                i+=2;
            }
            
            i += 8;
            
            monsters[gd->id] = (gd);
        }
        
        return monsters.size();
    }
};

#endif /* defined(__card__HMonster__) */
