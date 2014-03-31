//
//  HTemple.h
//  card
//
//  Created by zhou gang on 13-6-5.
//
//

#ifndef __card__HTemple__
#define __card__HTemple__

class HTemple {
    
public:
    
    int id;
    int cost;
    
public:
    
    static vector<string> strings;
    static map<int, const HTemple*> temples;
    
	static int load()
	{
        LOAD_STRING("config/tongsheng_base.txt");
        
        temples.clear();
		for (int i = 0; i<strings.size();)
		{
			HTemple * c = new HTemple();
            c->id = atoi(strings[i++].c_str());
            
            i++;
            c->cost = atoi(strings[i++].c_str());
            i+=3;
            
            temples[c->id] = c;
		}
        
        HTemple * c = new HTemple();
        c->id = 0; c->cost = 0;
        
        temples[c->id] = c;
        
        return temples.size();
	}
    
};


#endif /* defined(__card__HTemple__) */
