//
//  HChallenge.h
//  card
//
//  Created by zhou gang on 13-7-2.
//
//

#ifndef __card__HChallenge__
#define __card__HChallenge__

class HChallenge {
public:
    int id, cg_id, monster;
    
public:
    
    static vector<string> strings;
    static map<int, vector<const HChallenge* > > challenges;
    
	static int load()
    {
        LOAD_STRING("config/tianti_jinjie.txt");
        
        challenges.clear();
        for (int i=0; i<strings.size();) {
            HChallenge* gd = new HChallenge;
            gd->id = atoi(strings[i++].c_str());
            gd->cg_id = atoi(strings[i++].c_str());
            gd->monster = atoi(strings[i++].c_str());
            challenges[gd->id].push_back(gd);
        }
        
        return challenges.size();
    }

};

#endif /* defined(__card__HChallenge__) */
