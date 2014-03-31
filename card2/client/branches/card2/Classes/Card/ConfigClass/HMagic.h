//
//  HMagic.h
//  card
//
//  Created by zhou gang on 13-4-11.
//
//

#ifndef __card__HMagic__
#define __card__HMagic__

class HMagic : public HKey {
public:
//    int id;
//    const char* icon;
//    const char* name;
//    const char* description;
    const char* fire_condition;
//    char star_num;
//    char race;
    char level;
//    char level_max;
    
    int skill_id;
    char fire_times;
    const char* fire_anima;
    
public:
    
    static vector<string> strings;
    static map<int, vector<const HMagic*> > magics;
    
	static int load()
	{
        LOAD_STRING("config/fabao_base.txt");
    
        magics.clear();
        for (int i=0; i<strings.size(); ) {
            HMagic* m = new HMagic();
            m->id = atoi(strings[i++].c_str());
            m->icon = strings[i++].c_str();
            m->name = strings[i++].c_str();
            m->description = strings[i++].c_str();
            m->fire_condition = strings[i++].c_str();
            m->star_num = atoi(strings[i++].c_str());
            m->race = atoi(strings[i++].c_str());
            m->level = atoi(strings[i++].c_str());
            m->level_max = atoi(strings[i++].c_str());
            i+=3;
            
            m->skill_id = atoi(strings[i++].c_str());
            m->fire_times = atoi(strings[i++].c_str());
            m->fire_anima = strings[i++].c_str();
            
            magics[m->id].push_back(m);
        }
        
        return magics.size();
    }
    
};


#endif /* defined(__card__HMagic__) */
