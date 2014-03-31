//
//  HUpgrade.h
//  card
//
//  Created by zhou gang on 13-7-1.
//
//

#ifndef __card__HUpgrade__
#define __card__HUpgrade__

class HUpgrade {
    
    
public:
    int id;
    const char* name;
    int gdup_rank;
    int gdup_point;
    int reward_id;
    
public:
    
    static vector<string> strings;
    static map<int, const HUpgrade* > grades;
    
	static int load()
    {
        LOAD_STRING("config/once_exchange.txt");
        
        grades.clear();
        for (int i=0; i<strings.size();) {
            HUpgrade* gd = new HUpgrade;
            gd->id = atoi(strings[i++].c_str());
            gd->name = strings[i++].c_str();
            gd->gdup_rank = atoi(strings[i++].c_str());
            gd->gdup_point = atoi(strings[i++].c_str());
            gd->reward_id = atoi(strings[i++].c_str());
            
            grades[gd->id] = gd;
        }
        
        return grades.size();
    }

};

class HUgExchange {
    
    
public:
    int id;
    int gd_id;
    int type;
    int prop_type;
    int prop_id;
    int exh_num;
    int exh_point;
    
public:
    
    static vector<string> strings;
    static map<int, vector<const HUgExchange*> > exchanges;
    
	static int load()
    {
        LOAD_STRING("config/forever_exchange.txt");
        
        exchanges.clear();
        for (int i=0; i<strings.size();) {
            HUgExchange* gd = new HUgExchange;
            gd->gd_id = atoi(strings[i++].c_str());
            gd->id = atoi(strings[i++].c_str());
            gd->type = atoi(strings[i++].c_str());
            gd->prop_type = atoi(strings[i++].c_str());
            gd->prop_id = atoi(strings[i++].c_str());
            gd->exh_num = atoi(strings[i++].c_str());
            gd->exh_point = atoi(strings[i++].c_str());
            
            exchanges[gd->id].push_back(gd);
        }
        
        return exchanges.size();
    }
    
};

#endif /* defined(__card__HUpgrade__) */
