//
//  HExchange.cpp
//  card
//
//  Created by bo wei on 13-7-16.
//
//


#include "../../headers.h"

using namespace std;

vector<HFragExchange*> HFragExchange::exchangeList;
vector<string> HFragExchange::strings;
vector<HPvpExchange*> HPvpExchange::exchangeList;
vector<string> HPvpExchange::strings;

int HFragExchange::load()
{
    LOAD_STRING("config/card_exchange.txt");
    
    exchangeList.clear();
    
    for (int i = 0; i<strings.size();)
    {
        HFragExchange *item = new HFragExchange();
        item->fragID = atoi(strings[i++].c_str());
        item->count = atoi(strings[i++].c_str());
        item->ItemID = atoi(strings[i++].c_str());
        exchangeList.push_back(item);
    }
    return exchangeList.size();
}

int HPvpExchange::load()
{
    LOAD_STRING("config/forever_exchange.txt");
    
    exchangeList.clear();
    
    for (int i = 0; i<strings.size();)
    {
        HPvpExchange *item = new HPvpExchange();
        item->pvplevel = atoi(strings[i++].c_str());
        item->exchangeid = atoi(strings[i++].c_str());
        item->tid = atoi(strings[i++].c_str());
        item->itemType = atoi(strings[i++].c_str());
        item->itemid = atoi(strings[i++].c_str());
        item->itemCount = atoi(strings[i++].c_str());
        item->needScore = atoi(strings[i++].c_str());
        
        exchangeList.push_back(item);
    }
    return exchangeList.size();
}

HPvpExchange* HPvpExchange::getItemByID(int exid)
{
    for(int i=0;i<exchangeList.size();i++)
    {
        HPvpExchange *item = exchangeList[i];
        if (item->exchangeid == exid)
            return item;
    }
    return NULL;
}

