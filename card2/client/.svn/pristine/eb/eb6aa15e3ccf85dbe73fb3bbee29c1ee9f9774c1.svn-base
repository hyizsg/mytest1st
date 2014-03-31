//
//  HDungeon.cpp
//  card
//
//  Created by zhou gang on 13-8-28.
//
//

#include "../../headers.h"
#include "HDungeon.h"

map<int, const HDungeon*> HDungeon::dungeons;
vector<string> HDungeon::strings;

int HDungeon::load()
{
    LOAD_STRING("config/fuben.txt");
    
    dungeons.clear();
    
    for (int i=0; i<strings.size(); ) {
        HDungeon* dun = new HDungeon;
        dun->id = atoi(strings[i++].c_str());
        dun->uid = atoi(strings[i++].c_str());
        dun->name = strings[i++].c_str();
        dun->suit_lv = strings[i++].c_str();
        dun->diff = atoi(strings[i++].c_str());
        dun->diff_index = atoi(strings[i++].c_str());
        dun->diff_num = atoi(strings[i++].c_str());
        dun->reset_num = atoi(strings[i++].c_str());
        dun->limt_lv = atoi(strings[i++].c_str());
        dun->reward_id = atoi(strings[i++].c_str());
        dun->speed = atoi(strings[i++].c_str());
        dun->max_speed = atoi(strings[i++].c_str());
        dun->active_cost = atoi(strings[i++].c_str());
        dun->type = atoi(strings[i++].c_str());
        dun->to_end = atoi(strings[i++].c_str());
        dun->continue_time = atoi(strings[i++].c_str());
        dun->start_time = strings[i++].c_str();
        dun->battle_type = atoi(strings[i++].c_str());
        dun->monster_id = atoi(strings[i++].c_str());
        dun->pass_info = strings[i++].c_str();
        dun->win_type = atoi(strings[i++].c_str());
        dun->win_args = atoi(strings[i++].c_str());
        dun->sub_coin = atoi(strings[i++].c_str());
        dun->sub_exp = atoi(strings[i++].c_str());
        dun->sub_drop_num = atoi(strings[i++].c_str());
        dun->sub_drop_args = strings[i++].c_str();
        dun->sub_drop_prop = strings[i++].c_str();
        dun->pass_all_coin = atoi(strings[i++].c_str());
        dun->pass_all_exp = atoi(strings[i++].c_str());
        dun->pass_all_drop_num = atoi(strings[i++].c_str());
        dun->pass_all_drop_args = strings[i++].c_str();
        dun->pass_all_drop_prop = strings[i++].c_str();
        dun->pass_all_drop_prop_ex = strings[i++].c_str();
        
        dungeons[dun->id << 12 | dun->diff_index << 8 | dun->speed] = dun;
    }
    
    return dungeons.size();
}

const HDungeon* HDungeon::dungeonById(int id, int diff_idx, int speed)
{
    return dungeons[id << 12 | diff_idx << 8 | speed];
}

const HDungeon* HDungeon::dungeonById(int id)
{
    for (map<int, const HDungeon*>::iterator it=dungeons.begin(); it!= dungeons.end(); it++) {
        if (it->second->id == id) {
            return it->second;
        }
    }
    
    return NULL;
}
