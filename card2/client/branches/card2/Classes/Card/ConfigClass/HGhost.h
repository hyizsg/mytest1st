//
//  HGhost.h
//  card
//
//  Created by zhou gang on 13-11-6.
//
//

#ifndef __card__HGhost__
#define __card__HGhost__

class HGhost {
    
    
public:
    int id;
    const char* name;
    
    static vector<string> strings;
    static map<int, const HGhost*> ghosts;
    
    
    static const HGhost* ghostById(int id)
    {
        return ghosts[id];
    }
    
	static int load()
	{
        LOAD_STRING("config/zilei.txt");
        
        ghosts.clear();
		for (int i = 0; i<strings.size();)
		{
			HGhost * c = new HGhost();
			c->id = atoi(strings[i++].c_str());
            c->name = strings[i++].c_str();
            i+=2;
			ghosts[c->id] = c;
		}
        return ghosts.size();
	}
};

#endif /* defined(__card__HGhost__) */
