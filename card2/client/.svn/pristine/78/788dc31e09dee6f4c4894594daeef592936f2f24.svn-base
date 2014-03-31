//
//  HCommodity.cpp
//  card
//
//  Created by bo wei on 13-7-17.
//
//

#include "headers.h"
#include "HCommodity.h"

CCDictionary HCommodity::commodities;
CCArray HCommodity::commoditylist;

int HCommodity::load()
{
    commodities.setObject(HCommodity::create(), 0);
    commodities.removeObjectForKey(0);
    return true;
//    LOAD_STRING("config/commodity_base.txt");
//    
//    commodities.clear();
//    commoditylist.clear();
//    
//    for (int i = 0; i<strings.size();)
//    {
//        HCommodity * c = new HCommodity();
//        c->id = atoi(strings[i++].c_str());
//        c->icon = strings[i++].c_str();
//        c->name = strings[i++].c_str();
//        c->desc = strings[i++].c_str();
//        c->actDesc = strings[i++].c_str();
//        c->firstDesc = strings[i++].c_str();
//        c->extrDesc = strings[i++].c_str();
//        c->type = atoi(strings[i++].c_str());
//        c->time_up = strings[i++].c_str();
//        c->time_down = strings[i++].c_str();
//        c->roundDay = atoi(strings[i++].c_str());
//        c->currStatus = atoi(strings[i++].c_str());
//        c->requireType = atoi(strings[i++].c_str());
//        c->requireParam = atoi(strings[i++].c_str());
//        c->buyLimit = atoi(strings[i++].c_str());
//        c->money_type = atoi(strings[i++].c_str());
//        c->price = atoi(strings[i++].c_str());
//        c->ifDiscount = atoi(strings[i++].c_str());
//        c->discount = atoi(strings[i++].c_str());
//        c->dropnum = atoi(strings[i++].c_str());
//        c->dropParam = strings[i++].c_str();
//        c->dropPerc = strings[i++].c_str();
//        c->moneycount = atoi(strings[i++].c_str());
//        c->goldcount = atoi(strings[i++].c_str());
//        c->stonecount = atoi(strings[i++].c_str());
//        c->firstGift = strings[i++].c_str();
//        c->firstdrop = strings[i++].c_str();
//        c->firstdropparam = strings[i++].c_str();
//        c->sendnum = strings[i++].c_str();
//        c->senddrop = strings[i++].c_str();
//        c->senddropparam = strings[i++].c_str();       
//        
//        if(c->type == COMMODITY_NEWBIE)
//        {
//            char buff[300];
//            strcpy(buff, c->actDesc);
//            vector<char*> p = split(buff, ",");
//            for (int j=0; j<p.size(); j++) {
//                vector<char*> pp = split(p[j], ";");
//                if (pp.size() != 2)
//                    break;
//                c->giftInfo.push_back(atoi(pp[0]));
//                c->giftInfo.push_back(atoi(pp[1]));
//            }
//        }
//        
//        //extra info
//        c->hasbuy = 0;
//        
//        commodities[c->id] = c;
//        commoditylist.push_back(c);
//    }
//    return commodities.size();
}

HCommodity::HCommodity()
:m_desc(NULL)
,m_img(NULL)
,m_actDesc(NULL)
,m_firstDesc(NULL)
,m_extraDesc(NULL)
,m_name(NULL)
,hasbuy(false)
{
    
}

HCommodity* HCommodity::create()
{
    HCommodity* obj = new HCommodity();
//    obj->autorelease();
    CC_AUTO_RELEASE(obj);
    return obj;
}

HCommodity::~HCommodity()
{
    CC_SAFE_RELEASE_NULL(m_img);
    CC_SAFE_RELEASE_NULL(m_desc);
    CC_SAFE_RELEASE_NULL(m_actDesc);
    CC_SAFE_RELEASE_NULL(m_firstDesc);
    CC_SAFE_RELEASE_NULL(m_extraDesc);    
}

void HCommodity::getMainItem(CCArray &vec)
{
    vec.removeAllObjects();
    int count = commoditylist.count();
    for(int i=0;i<count;i++)
    {
        HCommodity *item = (HCommodity *)commoditylist.objectAtIndex(i);
        if (item->type < COMMODITY_NEWBIE)
        {
            vec.addObject(item);
        }
    }
}

void HCommodity::getNewbieItem(CCArray &vec)
{
    vec.removeAllObjects();
    int count = commoditylist.count();
    for(int i=0;i<count;i++)
    {
        HCommodity *item = (HCommodity *)commoditylist.objectAtIndex(i);
        if (item->type >= COMMODITY_NEWBIE)
        {            
            vec.addObject(item);
        }
    }
}

const HCommodity* HCommodity::getCommodityById(int cid)
{
    return (HCommodity*)(commodities.objectForKey(cid));
}

void HCommodity::parseShopInfo(cocos2d::CCDictionary *dic)
{
    CCArray *arr = PARSE_ARR(dic, "MallInfo");
    if (arr == NULL)
        return;
    commodities.removeAllObjects();
    commoditylist.removeAllObjects();
    
    FOREACH(CCDictionary*, dicitem, arr)
    {
        HCommodity* item = HCommodity::create();
        item->id = PARSE_INT(dicitem, "ID");
        item->setName(PARSE_STR(dicitem, "Name"));        
        item->setImage(PARSE_STR(dicitem, "Image"));
        item->setActDesc(PARSE_STR(dicitem, "ActDesc"));
        item->setExtraDesc(PARSE_STR(dicitem, "ExtraDesc"));
        item->type = PARSE_INT(dicitem, "Type");
        item->requireType = PARSE_INT(dicitem, "BuyCond");
        item->requireParam = PARSE_INT(dicitem, "CondParam");
        item->buyLimit = PARSE_INT(dicitem, "BuyLimit");
        
        item->ifDiscount = PARSE_INT(dicitem, "CanDiscount");
        item->discount = PARSE_INT(dicitem, "Discount");
        item->AddTime = PARSE_INT(dicitem, "AddTime");
        item->OffTime = PARSE_INT(dicitem, "OffTime");
        item->money_type = PARSE_INT(dicitem, "CoinType");
        item->price = PARSE_INT(dicitem, "Price");
        
        item->firstRewardID = PARSE_INT(dicitem, "FirstDropID");
        item->dropNum = PARSE_INT(dicitem, "DropNum");
        
        if(item->type == COMMODITY_NEWBIE)
        {
            char buff[300];
            strcpy(buff, item->m_actDesc->getCString());
            vector<char*> p = split(buff, ",");
            for (int j=0; j<p.size(); j++) {
                vector<char*> pp = split(p[j], ";");
                if (pp.size() != 2)
                    break;
                item->giftInfo.push_back(atoi(pp[0]));
                item->giftInfo.push_back(atoi(pp[1]));
            }
        }
        
        CCArray *rewardarr = PARSE_ARR(dicitem, "Gift");
        if (rewardarr != NULL)
        {
            FOREACH(CCString*, tempstr, rewardarr)
            {
                item->rewardInfo.push_back(tempstr->intValue());
            }
        }
        
        commoditylist.addObject(item);
        commodities.setObject(item, item->id);
    }
    
    CCArray* hasbuyarr = PARSE_ARR(dic, "HasBuy");
    {
        FOREACH(CCString*, strItem, hasbuyarr)
        {
            int firtrid = strItem->intValue();
            
            if (firtrid > 0)
            {
                for (int j =0; j<commoditylist.count(); j++) {
                    HCommodity* item2 = (HCommodity*)(commoditylist.objectAtIndex(j));
                    if (item2->firstRewardID == firtrid)
                    {
                        item2->hasbuy = 1;
                    }
                }
            }
        }
    }
}


void HCommodity::setHasBuy(int itemid)
{
    HCommodity *item = (HCommodity *)commodities.objectForKey(itemid);
    if (item != NULL)
    {
        item->hasbuy = 1;       
    }       
}
