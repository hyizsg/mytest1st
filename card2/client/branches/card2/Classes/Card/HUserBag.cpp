//
//  HBag.cpp
//  card
//
//  Created by zhou gang on 13-5-3.
//
//

#include "../headers.h"

//HActiveInfo::HActiveInfo()
//{
//    m_dailyNum = 0;
//    m_peach = 0;
//    m_treeLv = 0;
//}
//
//HActiveInfo::~HActiveInfo(){
//    int t = 0;
//}
//
//CCDictionary *HActiveInfo::getJson()
//{
//    CCDictionary *dic = CCDictionary::create();
//    dic->setObject(HString::createWithInteger(m_dailyNum), "day");
//    dic->setObject(HString::createWithInteger(m_peach), "peach");
//    dic->setObject(HString::createWithInteger(m_treeLv), "tree");
//    return dic;
//}

compare_card_kid compare_card_kid_obj::cmp_kid;

HSINGLETON_OBJECT_IMP(HUserBag);

#define DEFAULT_CARD    "3023"
#define DEFAULT_MAGIC   "9307"

HUserBag::HUserBag()
{
    m_gold = 0;
    m_coin = 0;
    m_iapFirstGot = 0;
    m_currGroupIndex = 0;    
    m_isActiveBought = false;
    m_monsterAtkListDelta = 1.5f;
    m_wbRid = 0;
    m_wbRun = 0;
}

HUserBag::HUserBag(HPlayer* player)
{
    m_gold = 0;
    m_coin = 0;
    m_iapFirstGot = 0;
    m_currGroupIndex = 0;    
    m_isActiveBought = false;
    
    setPlayer(player);
    if (player) {
        player->setBag(this);
    }
}

HUserBag::~HUserBag()
{
    for (int i=0; i<m_allCardList.size(); i++) {
        CC_SAFE_DELETE(m_allCardList[i]);
    }
    
    for (int i=0; i<m_allMagicList.size(); i++) {
        CC_SAFE_DELETE(m_allMagicList[i]);
    }
}



HUserCard* HUserBag::cardByIndex(int index)
{
    if (index < 0 || index >= m_allCardList.size()){
        return NULL;
    }
    return m_allCardList[index];
}

HUserCard* HUserBag::cardByUId(int id)
{
    if (m_allCardMap.find(id) == m_allCardMap.end()) {
        return NULL;
    }
    return m_allCardMap[id];
}

HUserMagic* HUserBag::magicByUId(int id)
{
    if (m_allMagicMap.find(id) == m_allMagicMap.end()) {
        return NULL;
    }
    return m_allMagicMap[id];
}

vector<int> HUserBag::getCardsInGroup()
{
    vector<int> cards;
    for (int j=0; j<m_cardGroup.size(); j++) {
        for (int k=0; k<m_cardGroup[j].size(); k++) {
            if (!exist(cards, m_cardGroup[j][k])) {
                cards.push_back(m_cardGroup[j][k]);
            }
        }
    }
    return cards;
}

vector<int> HUserBag::getCardsWithoutInGroup()
{
    vector<int> cards;
    for (int i=0; i<m_allCardList.size(); i++) {
        int uid = m_allCardList[i]->getUserId();
        for (int j=0; j<m_cardGroup.size(); j++) {
            if (exist(m_cardGroup[j], uid)) {
                goto NEXT;
            }
        }
        cards.push_back(uid);
    NEXT:
        ;
    }
    return cards;
}


vector<int> HUserBag::getCardsInCurrGroup()
{
    return m_cardGroup.size() > m_currGroupIndex ?  m_cardGroup[m_currGroupIndex] : vector<int>();
}


vector<int> HUserBag::getCardsWithoutInCurrGroup()
{
    vector<int> cards;
    for (int i=0; i<m_allCardList.size(); i++) {
        int uid = m_allCardList[i]->getUserId();
        if (!exist(m_cardGroup[m_currGroupIndex], uid)) {
            cards.push_back(uid);
        }
    }
    return cards;
}

vector<int> HUserBag::getMagicsInCurrGroup()
{
    return m_magicGroup[m_currGroupIndex];;
}

vector<int> HUserBag::getMagicsWithoutInCurrGroup()
{
    vector<int> magics;
    for (int i=0; i<m_allMagicList.size(); i++) {
        int uid = m_allMagicList[i]->getUserId();
        if (!exist(m_magicGroup[m_currGroupIndex], uid)) {
            magics.push_back(uid);
        }
    }
    return magics;
}

vector<int> HUserBag::getMagicsInGroup()
{
    vector<int> magic;
    for (int j=0; j<m_magicGroup.size(); j++) {
        for (int k=0; k<m_magicGroup[j].size(); k++) {
            if (!exist(magic, m_magicGroup[j][k])) {
                magic.push_back(m_magicGroup[j][k]);
            }
        }
    }
    return magic;
}

vector<int> HUserBag::getMagicsWithoutInGroup()
{
    vector<int> magic;
    for (int i=0; i<m_allMagicList.size(); i++) {
        int uid = m_allMagicList[i]->getUserId();
        for (int j=0; j<m_magicGroup.size(); j++) {
            if (exist(m_magicGroup[j], uid)) {
                goto NEXT;
            }
        }
        magic.push_back(uid);
    NEXT:
        ;
    }
    return magic;
}

void HUserBag::parseIntStr(CCString *str, vector<int> &vec)
{
    if (str == NULL)
        return;
    const char *src = str->getCString();
    
    char *end;
    //    CCArray *array = CCArray::create();
    while(true)
    {
        end = strchr(src, ',');
        if (end != NULL)
        {
            vec.push_back(atoi(src));
        } else {
            int length = strlen(src);
            if (length > 0)
            {
                vec.push_back(atoi(src));
            }
            break;
        }
        src = end + 1;
    }
}

void HUserBag::updateCardList(CCObject* cards)
{
    if (!cards) {
        return;
    }
    
    vector<HUserCard*> cardlist;
    bool useZip = dynamic_cast<CCString*>(cards) != NULL;
    if (useZip) {
        vector<int> intvec;
        CCString* cardstr = (CCString*)cards;
        parseIntStr(cardstr, intvec);
        int co = intvec.size();
        for(int i=0;i<co;i+=5)
        {
            HUserCard* card = new HUserCardObject;
            card->setUserId(intvec[i]);
            card->setKeyCard(getCardById(intvec[i+1]));
            card->setLevel(intvec[i+2]);
            card->setExp(intvec[i+3]);
            int feature = intvec[i+4];
            vector<int> ft(3);
            for(int j=0;j<3;j++) {
                ft[j] = (feature & (0x01<<j)) > 0;
            }
            card->setFeature(ft);
            cardlist.push_back(card);
        }
    }else{
        CCArray* cardinfo = (CCArray*)cards;
        FOREACH(CCDictionary*, dic, cardinfo){
            HUserCard* card = new HUserCardObject;
            card->setUserId(PARSE_INT(dic, "CID"));
            card->setKeyCard(getCardById(PARSE_INT(dic, "CardID")));
            card->setLevel(PARSE_INT(dic, "Level"));
            card->setExp(PARSE_INT(dic, "EXP"));
            card->setFeature(ccarray2vector(PARSE_ARR(dic, "Feature")));
            cardlist.push_back(card);
        }
    }
    
    updateCardList(cardlist);
}

void HUserBag::updateCardList(const vector<HUserCard*> & card)
{
    for (int i=0; i<card.size(); i++) {
        ((HUserCardObject*)card[i])->retain();
    }
    
    for (int i=0; i<m_allCardList.size(); i++) {
        ((HUserCardObject*)m_allCardList[i])->release();
    }
    
    m_allCardList = card;
    m_allCardMap.clear();
    
    if (card.size() > 0) {
        _updateMapByArr(m_allCardMap, &card[0], card.size(), usercard_key_fun(), default_fun<HUserCard*>());
    }
}

void HUserBag::updateCurrCardGroup(const vector<int>& cards)
{
    _resizeVectorByIndex(m_cardGroup, m_currGroupIndex);
    if (!cards.empty()) {
        _updateVectorByArr(m_cardGroup[m_currGroupIndex], &cards[0], cards.size(), default_fun<int>());
    }
}

void HUserBag::updateCurrCardGroup(const vector<HUserCard*>& cards)
{
    _resizeVectorByIndex(m_cardGroup, m_currGroupIndex);
    if (!cards.empty()) {
        _updateVectorByArr(m_cardGroup[m_currGroupIndex], &cards[0], cards.size(), usercard_key_fun());
    }
}

void HUserBag::updateCurrMagicGroup(const vector<int>& magics)
{
    _resizeVectorByIndex(m_magicGroup, m_currGroupIndex);
    if (!magics.empty()) {
        _updateVectorByArr(m_magicGroup[m_currGroupIndex], &magics[0], magics.size(), default_fun<int>());
    }
}

void HUserBag::updateCurrMagicGroup(const vector<HUserMagic*>& magics)
{
    _resizeVectorByIndex(m_magicGroup, m_currGroupIndex);
    if (!magics.empty()) {
        _updateVectorByArr(m_magicGroup[m_currGroupIndex], &magics[0], magics.size(), usercard_key_fun());
    }
}

void HUserBag::updateMagicList(const vector<HUserMagic*>& magic)
{
    for (int i=0; i<magic.size(); i++) {
        ((HUserMagicObject*)magic[i])->retain();
    }
    
    for (int i=0; i<m_allMagicList.size(); i++) {
        ((HUserMagicObject*)m_allMagicList[i])->release();
    }
    
    m_allMagicList = magic;
    m_allMagicMap.clear();
    
    if (magic.size() > 0) {
        _updateMapByArr(m_allMagicMap, &magic[0], magic.size(), usermagic_key_fun(), default_fun<HUserMagic*>());
    }
}


void HUserBag::updateCardGroup(CCArray* arr, int index)
{
    _resizeVectorByIndex(m_cardGroup, index);
    if (arr != NULL && arr->count() > 0) {
        _updateVectorByArr(m_cardGroup[index], arr->data->arr, arr->data->num, cstring_int_fun());
    }
}

void HUserBag::updateMagicGroup(cocos2d::CCArray *arr, int index)
{
    _resizeVectorByIndex(m_magicGroup, index);
    if (arr != NULL && arr->count() > 0) {
        _updateVectorByArr(m_magicGroup[index], arr->data->arr, arr->data->num, cstring_int_fun());
    }
}

void HUserBag::updateFragMap(CCArray* arr)
{
    m_allFragMap.clear();
    FOREACH(CCDictionary*, frag, arr) {
        m_allFragMap[PARSE_INT(frag, "Type")] = PARSE_INT(frag, "Num");
    }
}

int HUserBag::getFragNumByType(int type)
{
    HFragInfoMap::iterator it =  m_allFragMap.find(type);
    if (it == m_allFragMap.end())
        return 0;
    return it->second;
}

void HUserBag::updateSymbolMap(CCArray* arr)
{
    m_symbolMap.clear();
    FOREACH(CCDictionary*, info, arr) {
        symbol sy = {
            PARSE_INT(info, "ID"),
            PARSE_INT(info, "Level"),
            PARSE_INT(info, "Exp")
        };
        m_symbolMap[sy.id] = sy;
    }
}

const HUserBag::symbol* HUserBag::symbolById(int id)
{
    return &m_symbolMap[id];
}

int HUserBag::getSymbolHp()
{
    return getSymbolAddedByType(1);
}

int HUserBag::getSymbolAttack()
{
    return getSymbolAddedByType(2);
}

int HUserBag::getSymbolAddedByType(int type)
{
    int hp = 0;
    HSymbolMap::iterator it;
    for (it=m_symbolMap.begin(); it!=m_symbolMap.end(); it++) {
        const HSymbol* sy = getSymbolById(it->first, it->second.level);
        if (sy->type == type) {
            hp+=sy->args;
        }
    }
    
    return hp;
}

template <typename T>
void HUserBag::_resizeVectorByIndex(vector< vector<T> >& vec, int index)
{
    for (int i=vec.size(); i<index+1; i++) {
        vec.push_back(vector<T>());
    }
    
    vec[index].clear();
}

template <typename T, typename P, typename Func>
void HUserBag::_updateVectorByArr(vector<T> & vec, P* begin, int count, Func fun)
{
    for (P* it = begin; it<= begin+count-1; it++) {
        vec.push_back(fun(*it));
    }
}

template <typename T1, typename T2, typename P, typename FuncKey, typename FuncValue>
void HUserBag::_updateMapByArr(map<T1, T2> & tmap, P* begin, int count, FuncKey funKey, FuncValue funValue)
{
    for (P* it = begin; it<= begin+count-1; it++) {
        tmap[funKey(*it)] = funValue(*it);
    }
}

CCTexture2D* HUserBag::textureWithName(const char* name)
{
    return HThreadTextureCache::getInstance()->addImage(name);
}

void HUserBag::removeAllTexture()
{
    recycleCell();
    HThreadTextureCache::getInstance()->removeUnusedTexture();
    
}

const char* HUserBag::getDefaultIcon(const char* icon)
{
    strcpy(m_strBuff, icon);
    if (strstr(icon, "card")) {
        memcpy(strrchr(m_strBuff, '/')+1, DEFAULT_CARD, strlen(DEFAULT_CARD));
    }else if (strstr(icon, "magic")){
        memcpy(strrchr(m_strBuff, '/')+1, DEFAULT_MAGIC, strlen(DEFAULT_MAGIC));
    }
    return m_strBuff;
}

const char* tochinese(long num);

const char* num2cn(int n)
{
    static const char * const cnArr[] =
    {
        "零", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十",
        "十一", "十二", "十三", "十四", "十五", "十六", "十七", "十八", "十九", "二十",
        "二十一", "二十二", "二十三", "二十四", "二十五", "二十六", "二十七", "二十八", "二十九", "三十",
        "三十一", "三十二", "三十三", "三十四", "三十五", "三十六", "三十七", "三十八", "三十九", "四十",
        "四十一", "四十二", "四十三", "四十四", "四十五", "四十六", "四十七", "四十八", "四十九", "五十",
    };
    
    if (n <= 50) {
        return cnArr[n];
    }else{
        return tochinese(n);
    }
    
    return "";
}

void HUserBag::AddIapItem(int itemid)
{
    for(int i=0;i<m_iapHasBuy.size();i++)
    {
        if (m_iapHasBuy[i] == itemid)
            return;
    }
    m_iapHasBuy.push_back(itemid);
}

void HUserBag::updateIapInfo(cocos2d::CCDictionary* dic)
{
    CCArray *arr = PARSE_ARR(dic, "OnceList");
    if (arr != NULL) {
        m_iapHasBuy.clear();
        FOREACH(CCString*, info, arr) {
            AddIapItem(info->intValue());
        }
    }
    
    arr = PARSE_ARR(dic, "IAPFirst");
    if (arr != NULL) {
        m_iapfirstreward.clear();
        FOREACH(CCString*, info, arr) {
            m_iapfirstreward.push_back(info->intValue());
        }
    }
    
    m_iapFirstGot = PARSE_INT(dic, "PayBag");
}

bool HUserBag::CheckCommonHasBuy()
{
    bool hasbuy = false;
    for(int i=1;i<=6;i++)
    {
        if (CheckIapHasBuy(i))
            hasbuy = true;
    }
    return hasbuy;
}

bool HUserBag::CheckIapHasBuy(int itemid)
{
    for(int i=0;i<m_iapHasBuy.size();i++)
    {
        if (m_iapHasBuy[i] == itemid)
            return true;
    }
    return false;
}



void HUserBag::dumpCachedTextureInfo()
{
    unsigned int count = 0;
    unsigned int totalBytes = 0;
    
    CCDictionary* textureCache = HThreadTextureCache::getInstance()->shareTextureChace();
    
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(textureCache, pElement)
    {
        CCTexture2D* tex = (CCTexture2D*)pElement->getObject();
        unsigned int bpp = tex->bitsPerPixelForFormat();
        // Each texture takes up width * height * bytesPerPixel bytes.
        unsigned int bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
        totalBytes += bytes;
        count++;
        CCLOG("HUserBag: \"%s\" rc=%lu id=%lu %lu x %lu @ %ld bpp => %lu KB",
              pElement->getStrKey(),
              (long)tex->retainCount(),
              (long)tex->getName(),
              (long)tex->getPixelsWide(),
              (long)tex->getPixelsHigh(),
              (long)bpp,
              (long)bytes / 1024);
    }
    
    CCLOG("HUserBag: CCTextureCache dumpDebugInfo: %ld textures, for %lu KB (%.2f MB)", (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f*1024.0f));
}

char* strrev(char* str)
{
    reverse(str, str+strlen(str));
    return str;
}

const char* tochinese(long num)
{
	static const char * zw[10]={"零","一","二","三","四","五","六","七","八","九"};
	static const char * jw[9]={"","十","百","千","万","十","百","千","亿"};//个位留一个空字符便于计算
	char temp[128]="";//用于存贮临时的字符串
	int digit=0; //数字位
	int predigit=0; //记录上一位数字位
	int dw=0; //单位
    
	char rev[10]; //记录反转的字符串
	int length=0; //数字的位数
    
	long number=num;
    
	CCLOG("%ld\t",number);
	if(number==0)//等于0的情况
		strcat(temp,zw[0]);
	if(number<0)//小于0的情况
	{
		number=-1*number;
		strcat(temp,"负");
        
	}
    
	strcpy(rev, itoa(number)); //数字转字符串
	length=strlen(rev);//长度
	if(length>9) //大于9位的数不处理
	{
		CCLOG(ccLocalizedString("HCOM_NUM_OUT"));
		return "";
	}
    
	strrev(rev);//字符串反转
    
	number=atoi(rev);//字符串转数字
    
	while(number)
	{
		digit=number%10; //取得最后位的数字
        
		number=number/10; //去除最后一位
        
		if(!(digit==0 && predigit==0)) //连续出现0时只处理第1个
		{
			strcat(temp,zw[digit]);//strcat是字符串连接
			if(digit!=0)
			{
				strcat(temp,jw[length-dw-1]);//是0时不显示单位
			}
            
		}
        
		dw++;
		predigit=digit;
        
	}
	CCLOG("%s\n",temp);
    
    
	return _T("%s", temp);
}
