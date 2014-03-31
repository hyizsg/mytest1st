//
//  HDungeon.h
//  card
//
//  Created by zhou gang on 13-8-28.
//
//

#ifndef __card__HDungeon__
#define __card__HDungeon__

class HDungeon  {
    
    
public:
    int id;
    int uid;
    const char* name;
    const char* suit_lv;
    int diff;
    int diff_index;
    int diff_num;
    int reset_num;
    int limt_lv;
    int reward_id;
    int speed;
    int max_speed;
    int active_cost;
    int type;
    int to_end;
    int continue_time;
    const char* start_time;
    int battle_type;
    int monster_id;
    const char* pass_info;
    int win_type;
    int win_args;
    int sub_coin;
    int sub_exp;
    int sub_drop_num;
    const char* sub_drop_args;
    const char* sub_drop_prop;
    int pass_all_coin;
    int pass_all_exp;
    int pass_all_drop_num;
    const char*  pass_all_drop_args;
    const char*  pass_all_drop_prop;
    const char*  pass_all_drop_prop_ex;
    
public:
    
    static vector<string> strings;
    static int load();
    static const HDungeon* dungeonById(int id, int diff, int speed);
    static const HDungeon* dungeonById(int id);
    static map<int, const HDungeon*> dungeons;
};

#endif /* defined(__card__HDungeon__) */
