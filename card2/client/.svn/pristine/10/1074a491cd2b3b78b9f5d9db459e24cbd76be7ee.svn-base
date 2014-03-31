//
//  HBuff.h
//  card
//
//  Created by zhou gang on 13-5-2.
//
//

#ifndef __card__HBuff__
#define __card__HBuff__

class HBuff  {
    
    
public:
    int id;
    const char* name;
    const char* icon;
    const char* description;
    int effect_id;
    
    union {
        struct {
            const char* anima_add;
            const char* anima_attack;
            const char* anima_stricken;
            const char* anima_remove;
        };
        const char* anima[4];
    };

    static vector<string> strings;
    static map<int, const HBuff*> buffs;
    
    
    static const HBuff* buffById(int id)
    {
        return buffs[id];
    }
    
	static int load()
	{
        LOAD_STRING("config/BUFF.txt");
        
        buffs.clear();
		for (int i = 0; i<strings.size();)
		{
			HBuff * c = new HBuff();
			c->id = atoi(strings[i++].c_str());
            c->name = strings[i++].c_str();
			c->icon = strings[i++].c_str();
            c->description = strings[i++].c_str();
            i+=6;
            c->effect_id = atoi(strings[i++].c_str());
            c->anima[0] = strings[i++].c_str();
            c->anima[1] = strings[i++].c_str();
            c->anima[2] = strings[i++].c_str();
            c->anima[3] = strings[i++].c_str();
            
			buffs[c->id] = c;
		}
        return buffs.size();
	}
};


#endif /* defined(__card__HBuff__) */
