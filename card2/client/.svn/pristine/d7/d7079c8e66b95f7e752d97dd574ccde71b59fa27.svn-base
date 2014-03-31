//
//  HCommodity.h
//  card
//
//  Created by zhou gang on 13-5-7.
//
//

#ifndef __card__HCommodity__
#define __card__HCommodity__

typedef enum {
    COMMODITY_NONE,
    COMMODITY_NORMAL = 1,
    COMMODITY_GOOD = 2,
    COMMODITY_SHENSHI = 3,
    COMMODITY_NEWBIE = 11
} CommodityType;



class HCommodity: public CCObject {
    CC_SYNTHESIZE_RETAIN(CCString*, m_img, Image);
    CC_SYNTHESIZE_RETAIN(CCString*, m_name, Name);
    CC_SYNTHESIZE_RETAIN(CCString*, m_desc, Desc);
    CC_SYNTHESIZE_RETAIN(CCString*, m_actDesc, ActDesc);
    CC_SYNTHESIZE_RETAIN(CCString*, m_firstDesc, FirstDesc);
    CC_SYNTHESIZE_RETAIN(CCString*, m_extraDesc, ExtraDesc);

public:
    HCommodity();
    virtual ~HCommodity();
    
    static HCommodity* create();
    int id;    
    
    int type;
    int requireType;
    int requireParam;
    int buyLimit;    
        
    int money_type;
    int price;
    
    int ifDiscount;
    int discount;
    
    int dropNum;
    int firstRewardID;
    
    int AddTime;
    int OffTime;
    
    vector<int> giftInfo;
    vector<int> rewardInfo;
    
    //extra info
    int hasbuy;
    
public:
    static CCDictionary commodities;
    static CCArray commoditylist;

public:
	static int load();
    static void parseShopInfo(CCDictionary *dic);
    static void getMainItem(CCArray &vec);
    static void getNewbieItem(CCArray &vec);
    static void setHasBuy(int itemid);
    static const HCommodity* getCommodityById(int cid);
};


#endif /* defined(__card__HCommodity__) */
