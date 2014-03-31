//
//  HExchange.h
//  card
//
//  Created by zhou gang on 13-5-6.
//
//

#ifndef __card__HExchange__
#define __card__HExchange__

#include <algorithm>

class HFragExchange {
public:
    int fragID;
    int count;
    int ItemID;
    
    static vector<string> strings;
    static vector<HFragExchange*> exchangeList;    
    
    static int load();
};

class HPvpExchange {
public:
    int pvplevel;
    int exchangeid;
    int tid;
    int itemType;
    int itemid;
    int itemCount;
    int needScore;
    
    static vector<string> strings;
    static vector<HPvpExchange*> exchangeList;
    static int load();
    static HPvpExchange* getItemByID(int exid);
};

class HExchange {
    
    
public:
    int magic_id;
    int sell;
    int prop_id;
    int num;
    
    static vector<string> strings;
    static map<int, const HExchange*> exchanges;
    static vector<const HExchange*> exchangelist;    
    
	static int load()
	{
        return 0;
        
        LOAD_STRING("config/tongsheng_exchange.txt");
        
        exchangelist.clear();
        exchanges.clear();
        
		for (int i = 0; i<strings.size();)
		{
			HExchange * c = new HExchange();
			c->magic_id = atoi(strings[i++].c_str());
            c->sell = atoi(strings[i++].c_str());
            c->prop_id = atoi(strings[i++].c_str());
            c->num = atoi(strings[i++].c_str());
            
			exchanges[c->magic_id] = c;
            exchangelist.push_back(c);
		}
        
        sort(exchangelist.begin(), exchangelist.end(), HExchange::srotexlist);
        
        return exchanges.size();
	}
    
    const HExchange* getExchangeByID(int magicid)
    {
        map<int, const HExchange*>::iterator it = exchanges.find(magicid);
        if (it != exchanges.end())
            return it->second;
        return NULL;
    }
    
    static void parseInfo(CCArray *arr)
    {
        exchangelist.clear();
        exchanges.clear();
        
        if (arr == NULL)
            return;
        
        int length = arr->count() / 3;
        for(int i = 0; i<length; i++)
        {
            HExchange * c = new HExchange();
            c->magic_id = ((CCString*)(arr->objectAtIndex(3*i)))->intValue();
            c->prop_id = ((CCString*)(arr->objectAtIndex(3*i+1)))->intValue();
            c->num = ((CCString*)(arr->objectAtIndex(3*i+2)))->intValue();
            
            exchanges[c->magic_id] = c;
            exchangelist.push_back(c);
        }
        sort(exchangelist.begin(), exchangelist.end(), HExchange::srotexlist);
    }
    
    static int srotexlist(const HExchange*e1, const HExchange* e2)
    {
        if (e1->magic_id > 9000 && e2->magic_id > 9000) {
            int e100 = (e1->magic_id % 1000) / 100;
            int e200 = (e2->magic_id % 1000) / 100;
            if (e100 == e200) {
                int r1 = HMagic::magics[e1->magic_id][0]->race;
                int r2 = HMagic::magics[e2->magic_id][0]->race;
                if (r1 == r2) {
                    if (e1->num == e2->num) {
                        return e1->magic_id < e2->magic_id;
                    }else{
                        return e1->num < e2->num;
                    }
                }else{
                    return r1 < r2;
                }
            }else{
                return e1->magic_id < e2->magic_id;
            }
        }else{
            return e1->magic_id < e2->magic_id;
        }
    }
};



#endif /* defined(__card__HExchange__) */
