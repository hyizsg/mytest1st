//
//  HProp.h
//  card
//
//  Created by zhou gang on 13-5-3.
//
//

#ifndef __card__HProp__
#define __card__HProp__

#define PROP_MONEY 1
#define PROP_GOLD 2
#define PROP_STONE 3

class HProp  {
    
    
public:
    int id;
    int type;
    const char* icon;
    const char* name;
    bool can_sell;
    int cost;
    
    static vector<string> strings;
    static map<int, const HProp*> props;
    
	static int load()
	{
        LOAD_STRING("config/item_base.txt");
        
        props.clear();
        
		for (int i = 0; i<strings.size();)
		{
			HProp * c = new HProp();
			c->id = atoi(strings[i++].c_str());
            c->type = atoi(strings[i++].c_str());
			c->icon = strings[i++].c_str();
            c->name = strings[i++].c_str();
            c->can_sell = atoi(strings[i++].c_str());
            c->cost = atoi(strings[i++].c_str());
                        
			props[c->id] = c;
		}
        return props.size();
	}
    static const HProp *getProp(int propid)
    {
        map<int, const HProp*>::iterator it = props.find(propid);
        if (it != props.end())
            return it->second;
        return NULL;
    }
};


#endif /* defined(__card__HProp__) */
