//
//  HSymbol.h
//  card
//
//  Created by zhou gang on 13-6-20.
//
//

#ifndef __card__HSymbol__
#define __card__HSymbol__

class HSymbol : public HKey{
    
    
public:
    int level;
    int lvup_exp;
    int type;
    int args;
    int factor;
    
public:
    
    static vector<string> strings;
    static map<int, vector<const HSymbol*> > symbols;
    
	static int load()
    {
        LOAD_STRING("config/technology_base.txt");
        
        symbols.clear();
        for (int i=0; i<strings.size();) {
            HSymbol* sy = new HSymbol;
            sy->id = atoi(strings[i++].c_str());
            sy->icon = strings[i++].c_str();
            sy->level = atoi(strings[i++].c_str());
            sy->name = strings[i++].c_str();
            sy->description = strings[i++].c_str();
            sy->lvup_exp = atoi(strings[i++].c_str());
            sy->type = atoi(strings[i++].c_str());
            sy->args = atoi(strings[i++].c_str());
            sy->factor = atoi(strings[i++].c_str());
            
            symbols[sy->id].push_back(sy);
            
            sy->level_max = 50;
        }
        
        return symbols.size();
    }
};

#endif /* defined(__card__HSymbol__) */
