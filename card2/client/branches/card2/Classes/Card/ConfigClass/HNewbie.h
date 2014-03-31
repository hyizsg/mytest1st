//
//  HNewbie.h
//  card
//
//  Created by zhou gang on 13-7-4.
//
//

#ifndef __card__HNewbie__
#define __card__HNewbie__

class HNewbie {
    
public:
    int id;
    int step;
    int type;
    const char* name;
    const char* condition;
    const char* args;
    int person;
    int icon;
    const char* msg;
    const char* arrow;
    const char* tipbox;
    const char* reward;
    
public:
    static vector<string> strings;
    static map<int, vector<const HNewbie* > > newbies;
    
	static int load()
    {
        LOAD_STRING("config/Beginners_guide.txt");
        
        newbies.clear();
        for (int i=0; i<strings.size();) {
            HNewbie* gd = new HNewbie;
            gd->id = atoi(strings[i++].c_str());
            gd->step = atoi(strings[i++].c_str());
            gd->type = atoi(strings[i++].c_str());
            gd->name = strings[i++].c_str();
            gd->condition = strings[i++].c_str();
            gd->args = strings[i++].c_str();
            gd->person = atoi(strings[i++].c_str());
            gd->icon = atoi(strings[i++].c_str());
            gd->msg = strings[i++].c_str();
            gd->arrow = strings[i++].c_str();
            gd->tipbox = strings[i++].c_str();
            gd->reward = strings[i++].c_str();            
            
            newbies[gd->id].push_back(gd);
        }
        
        return 0;
    }
};

#endif /* defined(__card__HNewbie__) */
