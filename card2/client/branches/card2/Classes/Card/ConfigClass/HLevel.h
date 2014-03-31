//
//  HLevel.h
//  card
//
//  Created by zhou gang on 13-4-11.
//
//

#ifndef __card__HLevel__
#define __card__HLevel__


class HLevel
{
public:
    int id;
    const char* name;
    const char* subname;
    int icon;
    const char* description;
    const char* pass_description;
    
    int pre_level;
    int pre_star[2];
    char active;
    char type;
    int monster_id;
    
    int reward;
    int income;
    
public:
    static vector<string> strings;
    static map<int, const HLevel*> levels;
    
    
    static int load()
    {
        LOAD_STRING("config/guanka_base.txt");
        
        char temp[16];
        
        levels.clear();
        
        for (int i=0; i<strings.size(); ) {
            HLevel* level = new HLevel();
            level->id = atoi(strings[i++].c_str());
            level->name = strings[i++].c_str();
            level->subname = strings[i++].c_str();
            level->icon = atoi(strings[i++].c_str());
            level->description = strings[i++].c_str();
            level->pass_description = strings[i++].c_str();
            level->pre_level = atoi(strings[i++].c_str());
            
            strcpy(temp, strings[i++].c_str());
            vector<char*> pl = split(temp, ";");
            
            if (pl.size() == 1) {
                level->pre_star[0] = level->pre_star[1] = 0;
            }else{
                level->pre_star[0] = atoi(pl[0]) - 1;
                level->pre_star[1] = atoi(pl[1]);
            }

            i++;
            
            level->active = atoi(strings[i++].c_str());
            level->type = atoi(strings[i++].c_str());
            level->monster_id = atoi(strings[i++].c_str());
            
            i+=2;
            level->reward = atoi(strings[i++].c_str());
            
            
            i+= 8;
            
            level->income = atoi(strings[i++].c_str());
            
            level->icon = HMonster::monsters[level->monster_id]->icon;
            
            levels[level->id] = level;
        }
        
        return levels.size();
    }
    
};


#endif /* defined(__card__HLevel__) */
