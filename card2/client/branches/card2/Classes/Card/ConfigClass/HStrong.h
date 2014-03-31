//
//  HStrong.h
//  card
//
//  Created by zhou gang on 13-4-11.
//
//

#ifndef __card__HStrong__
#define __card__HStrong__

class HStrong {
    
public:
    int id;
    int lup_exp;
    int sprice;
    int base_exp;
    char factor;
    int awake_cost[2];
    
public:
    
    static vector<string> strings;
    static map<int, const HStrong*> strongs;
    
	static int load()
	{
        LOAD_STRING("config/card_other.txt");
        
        strongs.clear();
        
        for (int i = 0; i<strings.size();)
		{
			HStrong * s = new HStrong();
            s->id = atoi(strings[i++].c_str()) << 8 ;
            s->id |= (atoi(strings[i++].c_str())) << 4;
            s->id |= (atoi(strings[i++].c_str()));
            s->lup_exp = atoi(strings[i++].c_str());
            s->sprice = atoi(strings[i++].c_str());
            s->base_exp = atoi(strings[i++].c_str());
            s->factor = atoi(strings[i++].c_str());
            s->awake_cost[0] = atoi(strings[i++].c_str());
            s->awake_cost[1] = atoi(strings[i++].c_str());
            
            strongs[s->id] = s;
		}
        
        strings.clear();
        LOAD_STRING("config/fabao_other.txt");
        
        for (int i = 0; i<strings.size();)
		{
			HStrong * s = new HStrong();
            s->id = (0x10 | atoi(strings[i++].c_str())) << 8;
            s->id |= (atoi(strings[i++].c_str())) << 4;
            s->lup_exp = atoi(strings[i++].c_str());
            s->sprice = atoi(strings[i++].c_str());
            s->base_exp = atoi(strings[i++].c_str());
            s->factor = atoi(strings[i++].c_str());
            
            strongs[s->id] = s;
		}
        
        strings.clear();
        
        return strongs.size();
	}
};




#endif /* defined(__card__HStrong__) */
