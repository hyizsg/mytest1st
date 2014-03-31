//
//  HAchieve.h
//  card
//
//  Created by bo wei on 13-7-8.
//
//

#ifndef card_HAchieve_h
#define card_HAchieve_h

using namespace std;

class HAchieve {
public:
    int id;
    int aid;
    const char *name;
    const char *desc;
    int type;
    int condition;
    const char *param;
    int money;
    int exp;
    int stone;
    int coin;
    int moneytype;
    int moneycount;
    int itemid;
    int itemcount;
    int showtype;
    
public:
    static vector<string> strings;
    static map<int, const HAchieve*> achieves;
    static vector<const HAchieve*> achievelist;
    
	static int load()
    {
        LOAD_STRING("config/achievement.txt");
        
        achieves.clear();
        achievelist.clear();
        
        for (int i=0; i<strings.size();) {
            HAchieve* gd = new HAchieve;
            memset(gd, 0, sizeof(HAchieve));
            gd->id = atoi(strings[i++].c_str());
            gd->aid = atoi(strings[i++].c_str());
            gd->name =strings[i++].c_str();
            
            gd->desc = strings[i++].c_str();
            gd->type = atoi(strings[i++].c_str());
            gd->condition = atoi(strings[i++].c_str());
            gd->param = strings[i++].c_str();
            gd->coin = atoi(strings[i++].c_str());
            gd->money = atoi(strings[i++].c_str());
            gd->exp = atoi(strings[i++].c_str());
            gd->stone = atoi(strings[i++].c_str());
            vector<char*> pl = split((char*)(strings[i++].c_str()), ";");
            if (pl.size() >= 2) {
                gd->itemid = atoi(pl[0]);
                gd->itemcount = atoi(pl[1]);
            } else {
                gd->itemid = 0;
                gd->itemcount = 0;
            }
            
            if (gd->coin > 0)
            {
                gd->moneytype = 2;
                gd->moneycount = gd->coin;
            }
            
            if (gd->money > 0)
            {
                gd->moneytype = 1;
                gd->moneycount = gd->money;
            }
            
            if (gd->stone > 0)
            {
                gd->moneytype = 3;
                gd->moneycount = gd->stone;
            }
            
            gd->showtype = atoi(strings[i++].c_str());
            achieves[gd->id] = gd;
            achievelist.push_back(gd);
        }
        
        return 0;
    }
};

#endif
