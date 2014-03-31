//
//  HSkill.h
//  card
//
//  Created by zhou gang on 13-4-7.
//
//

#ifndef __card__HSkill__
#define __card__HSkill__


class HSkill {
    
public:
    int id;
    const char* icon;
    const char* name;
    const char* description;
    
    union {
        struct{const char* anima_attack0, *anima_attack1, *anima_attack2;};
        const char* anima_attack[3];
    };
    
    int type;
    int args;
    
    union {
        struct{const char* anima_stricken0, *anima_stricken1, *anima_stricken2;};
        const char* anima_stricken[3];
    };
    
public:
    
    static vector<string> strings;
    static map<int, const HSkill*> skills;

    
    static const HSkill* skillById(int id) 
    {
        return skills[id];
    }
    
	static int load()
	{
        LOAD_STRING("config/skill.txt");
        
        skills.clear();
        
		for (int i = 0; i<strings.size();)
		{
			HSkill * c = new HSkill();
			c->id = atoi(strings[i++].c_str());
			c->icon = strings[i++].c_str();
            c->name = strings[i++].c_str();
            c->description = strings[i++].c_str();
            i+=6;
            c->anima_attack0 = strings[i++].c_str();
            c->anima_stricken0 = strings[i++].c_str();
            c->type = atoi(strings[i++].c_str());
            c->args = atoi(strings[i++].c_str());
            i+=5;
            c->anima_attack1 = strings[i++].c_str();
            c->anima_stricken1 = strings[i++].c_str();
            i+=7;
            c->anima_attack2 = strings[i++].c_str();
            c->anima_stricken2 = strings[i++].c_str();
            
			skills[c->id] = c;
//            CCLOG("%d\t%d\t%d", i, c->id, skills.size());
		}
        return skills.size();
	}
};


#endif /* defined(__card__HSkill__) */
