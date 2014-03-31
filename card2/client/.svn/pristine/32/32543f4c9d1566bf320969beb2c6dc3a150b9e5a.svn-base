//
//  HPvp.h
//  card
//
//  Created by zhou gang on 13-6-24.
//
//

#ifndef __card__HPvp__
#define __card__HPvp__

class HPvp  {
    
    
public:
    int id;
    int cost_type;
    int cost;
    int hero_lv;
    int hero_lead;
    
public:
    
    static vector<string> strings;
    static map<int, const HPvp* > pvps;
    
	static int load()
    {
        LOAD_STRING("config/dalundou.txt");
        
        pvps.clear();
        for (int i=0; i<strings.size();) {
            HPvp* pvp = new HPvp;
            pvp->id = atoi(strings[i++].c_str());
            
            pvp->cost_type = atoi(strings[i].substr(0,1).c_str());
            pvp->cost = atoi(strings[i++].substr(2).c_str());
            
            pvp->hero_lv = atoi(strings[i++].c_str());
            pvp->hero_lead = atoi(strings[i++].c_str());
            
            i+= 4;
            
            pvps[pvp->id] = pvp;
        }
        
        return pvps.size();
    }

    
};

class HFcPvp  {
    
    
public:
    int id;
    int cost_type;
    int cost;
    int hero_lv;
    int hero_lead;
    
public:
    
    static vector<string> strings;
    static map<int, const HFcPvp* > pvps;
    
	static int load()
    {
        LOAD_STRING("config/paihangqianzhan.txt");
        
        pvps.clear();
        for (int i=0; i<strings.size();) {
            HFcPvp* pvp = new HFcPvp;
            pvp->id = atoi(strings[i++].c_str());
            
            pvp->cost_type = atoi(strings[i].substr(0,1).c_str());
            pvp->cost = atoi(strings[i++].substr(2).c_str());
            
            pvp->hero_lv = atoi(strings[i++].c_str());
            pvp->hero_lead = atoi(strings[i++].c_str());
            
            i+= 4;
            
            pvps[pvp->id] = pvp;
        }
        
        return pvps.size();
    }
    
    
};

#endif /* defined(__card__HPvp__) */
