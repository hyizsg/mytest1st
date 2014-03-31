//
//  UIDefine.h
//  card
//
//  Created by zhou gang on 13-3-14.
//
//

#ifndef __card__UIDefine__
#define __card__UIDefine__

#include <vector>

#define CCBI(__CCBI__) #__CCBI__".ccbi"
#define PLIST(__PLIST__) "ui/"#__PLIST__".plist",
#define PLIST2(__PLIST__) "ui2/"#__PLIST__".plist",
#define CLICK_SEL_DELARE(__SEL__) virtual void __SEL__(CCObject* sender, CCControlEvent event)

#define _T(__FORMAT__, ...) (CCString::createWithFormat(__FORMAT__,##__VA_ARGS__)->getCString())
#define _M(__PNG__) (HPlistManager::getInstance()->spriteFrameWithName(__PNG__))
//#define _M(__PNG__) (CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(__PNG__))
#define _U(__IMG__) (getCurrBag()->textureWithName(__IMG__))

#define CONFIG(txt) "config/"txt".txt"

#define __retain
#define __assign
#define __copy__


template <class T1, class T2>static inline void
__hc_set(T1& id, T2 v)
{
    CC_SAFE_RETAIN((T1)v);
    CC_SAFE_RELEASE(id);
    (id)=(T1)(v);
}

template <class T1, class T2>static inline void
__hc_copy(T1& id, T2 v) { CC_SAFE_RELEASE(id); (id)=(T1)(v)->copy(); ;}


#define HC_SET(id, v)           __hc_set(id, v)
#define HC_COPY(id, v)          __hc_copy(id, v)
#define ISKIND_OF_CLASS(id, class) (dynamic_cast<class>(id) != NULL)

#define LOAD_STRING(config_txt)       \
    {HTextReader* reader = new HTextReader(config_txt);\
    char buff[512] = {0}; strings.clear(); \
    while (reader->getNext(buff)) {\
        strings.push_back(buff);\
    } reader->release();} \

#define LOAD_STRING_NOCLEAN(config_txt)       \
{HTextReader* reader = new HTextReader(config_txt);\
char buff[512] = {0}; \
while (reader->getNext(buff)) {\
strings.push_back(buff);\
} reader->release();} \

#define nextstr() (strings[i++].c_str())
#define nextint() (atoi(strings[i++].c_str()))

//
// HUICLASS_DELARE
#define HUICLASS_DELARE(__CLASS__, __SUPERCLASS__) \
\
    HCLASSTYPE(__CLASS__, __SUPERCLASS__); \
protected:\
    __CLASS__(); \
public: \
    typedef __CLASS__ theClass; \
    typedef __SUPERCLASS__ super; \
    virtual ~__CLASS__(); \
\
    static __CLASS__* create() {    \
        __CLASS__ * pclass = new __CLASS__();  \
        if (pclass->loadPlistCCBI(getCCBI()) && pclass->init()){} \
        CC_AUTO_RELEASE(pclass);  \
        return pclass;  \
    }   \
\
    static const char* getCCBI() { return CCBI(__CLASS__); } \
    virtual void loadPlist() { LOAD_PLISTS(); super::loadPlist(); } \
    virtual void disposPlist() { DISPOSE_PLISTS(); super::disposPlist(); } \
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);     \
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);   \
\
    static __CLASS__* current() { return (__CLASS__*)HRootScene::currentWindowByType(#__CLASS__); } \
\
private: \
    static const char* s_plist[];  \


#define INIT_PLISTS_CCBI(ccbi)  do{\
    this->loadPlist();  \
    if(ccbi){ readNodeGraphFromFile(ccbi); \
    HFontManager::getInstance()->replaceFont(this); \
    HLocalString::getInstance()->replaceString(this); }}while(0)

#define LOAD_PLISTS() do{\
    for (int i=0; s_plist[i][0];i++) { \
        HPlistManager::getInstance()->addPlist(s_plist[i]);  \
    }}while(0) \

#define DISPOSE_PLISTS()  do{\
    for (int i=0; s_plist[i][0]; i++) { \
        HPlistManager::getInstance()->removePlist(s_plist[i]);   \
    }}while(0)


//
// BEGIN_PLIST
#define BEGIN_PLIST(__CLASS__)  const char* __CLASS__::s_plist[] = {
#define END_PLIST()             ""};


//
// BEGIN_CLICK_MAP
#define BEGIN_CLICK_MAP(__CLASS__)  \
SEL_CCControlHandler __CLASS__::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) { \
\
    SEL_CCControlHandler pRet = NULL;   \
    if (pSelectorName) {\
        if (0 == strcmp(pSelectorName, "")) {   \
            pRet = NULL;    \
        }


// ON_BTN_CLICK
#define CLICK(__SEL__) \
    else if (0 == strcmp(pSelectorName, #__SEL__)) {  \
        pRet = cccontrol_selector(theClass::__SEL__); \
    }\


// END_CLICK_MAP
#define END_CLICK_MAP()  \
        else { \
            pRet = super::onResolveCCBCCControlSelector(pTarget, pSelectorName); \
        } \
    }\
    return pRet;    \
}\


//
// BEGIN_MEMBER_MAP
#define BEGIN_MEMBER_MAP(__CLASS__) \
bool __CLASS__::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) { \
    bool bRet = false;  \
    if (pMemberVariableName) {  \
        if (0 == strcmp(pMemberVariableName, "")) { \
            bRet = true;    \
        }


// MEMBER_EXCHANGE
#define MEMBER(__MEMBER__) \
    else if (0 == strcmp(pMemberVariableName, #__MEMBER__)) {  \
        bRet = ccmember_assgin(__MEMBER__, pNode);    \
    }


#define MEMBER_NODE(__MEMBER__) \
    else if (0 == strcmp(pMemberVariableName, #__MEMBER__)) {  \
        bRet = __MEMBER__->initWithNode(pNode);    \
    }

#define MEMBER_NODE_ARR(__MEMBER__) \
    else if(0 == strcmp(pMemberVariableName, #__MEMBER__)) {    \
        bRet = __MEMBER__[pNode->getTag()]->initWithNode(pNode); \
    }


// END_MEMBER_MAP
#define END_MEMBER_MAP() \
        else { \
            bRet = super::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode); \
        } \
    }\
    return bRet; \
}


//
template <class T1, class T2> static inline bool
ccmember_assgin(T1*& t1, T2* t2) {  return (t1 = dynamic_cast<T1*>(t2)) != NULL; }

template <class T1, class T2> static inline bool
ccmember_assgin(T1* t1[], T2* t2) {  return (t1[t2->getTag()] = dynamic_cast<T1*>(t2)) != NULL; }

template <class T1, class T2> static inline bool
ccmember_assgin(map<int, T1*>& t1, T2* t2) {  return (t1[t2->getTag()] = dynamic_cast<T1*>(t2)) != NULL; }

static inline const char*
itoa(int n) {return CCString::createWithFormat("%d", n)->getCString();}

static inline std::vector<char*>
split(char* src, const char* c)
{
    std::vector<char*> lp;
    char *tokenPtr =strtok(src, c);
    while(tokenPtr!=NULL)
    {
        lp.push_back(tokenPtr);
        tokenPtr=strtok(NULL,c);
    }
    return lp;
}

template<typename _T>
inline typename _T::iterator
find(_T& __vec, const typename _T::value_type& __val){
    typename _T::value_type val = __val;
    return find(__vec.begin(), __vec.end(), val);
}

template<typename _T>
inline typename _T::iterator
find(_T& __vec, typename _T::value_type& __val){
    return find(__vec.begin(), __vec.end(), __val);
}

template<typename _T>
inline bool
exist(_T& __vec, typename _T::value_type& __val){
    return find(__vec.begin(), __vec.end(), __val) != __vec.end();
}

template<typename _T>
inline bool
exist(_T& __vec, const typename _T::value_type& __val){
    return find(__vec.begin(), __vec.end(), __val) != __vec.end();
}

template <typename T> inline T
lerp(T from, T to, float t)
{
    t = clampf(t, 0.f, 1.f);
    return (T)(from * (1-t) + to * t);
}

#define  IN
#define  in

#define FOREACH(__type__, __object__, __array__)                                                                         \
if ((__array__) && (__array__)->data->num > 0)                                                                     \
for(__type__* __arr__ = (__type__*)(__array__)->data->arr, **__end__ = (__type__*)(__array__)->data->arr + (__array__)->data->num-1, *__object__=NULL;    \
__arr__ <= __end__ && (((__object__) = (__type__)*__arr__) != NULL/* || true*/);                                             \
__arr__++)


#define FORORDER(i, first, end) \
for(int i=first<end?first:end-1; (first<end && i<end) || (first>=end && i>=end); i+=first<end?1:-1)

#define FORUP(i, n) \
for (int i=0; i<n; ++i)



#define PARSE_STR(dic, key)     ((CCString*)((CCDictionary*)dic)->valueForKey(key))
#define PARSE_INT(dic, key)     (((CCDictionary*)dic)->valueForKey(key)->intValue())
#define PARSE_ARR(dic, key)     ((CCArray*)((CCDictionary*)dic)->objectForKey(key))
#define PARSE_DIC(dic, key)     ((CCDictionary*)((CCDictionary*)dic)->objectForKey(key))

#define FORDOWN(i, n)   \
for (int i=n-1; i>=0; --i)

#define RET_VOID

#define CHECK_ACTION_DIC(result)     \
int errorcode = 0;\
if (result == NULL) {   \
    setNotifyError(true); \
    errorcode = ERROR_TIMEOUT;\
}else if (PARSE_INT(result, "ACTION_COM") != 0) {   \
    setNotifyError(true); \
    CCLOGERROR("Action %d error: %s", PARSE_INT(result, "ACTION"), PARSE_STR(result, "ExtraInfo")->getCString());   \
    errorcode = PARSE_INT(result, "ACTION_COM"); \
    HMessageBox::show(errorcode, PARSE_STR(result, "ExtraInfo")->getCString()); \
}else setNotifyError(false);


#define NOTIFY_ADD_OBSERVER(sel, name) CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(sel), name, NULL)
#define NOTIFY_REMOVE_OBSERVER(name) CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, name);


#define CHECK_REQUEST(request) \
    HDataRequest* request = dynamic_cast<HDataRequest*>(obj);   \
    if (request == NULL || request->isNotifyError()) {  \
    \
    }else


#define REGISTER_CCNODE_LOADER(pClassName, pCCNodeLoader) CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader(#pClassName, pCCNodeLoader)

template <typename T1, typename T2, typename ConventFun>
static inline std::vector<T2>
conventVector(const std::vector<T1>& vsrc, ConventFun conventFun) {
    std::vector<T2> vret(vsrc.size());
    for(int i=0; i<vsrc.size(); i++) {
        vret.push_back(conventFun(vsrc[i]));
    }
}

template <typename T>
struct default_fun{ T operator ()(T item) { return item; } };

struct cstring_int_fun { int operator ()(CCObject* str) {return ((CCString*)str)->intValue(); } };

template<typename Fun = cstring_int_fun>
static inline void ccarray2vector(vector<int>& vec, CCArray* arr, Fun fun = cstring_int_fun()) {
    vec.resize(arr->count());
    for (int i=0; i<arr->count(); i++) {
        vec[i] = fun(arr->objectAtIndex(i));
    }
}

template<typename Fun = cstring_int_fun>
static inline vector<int> ccarray2vector(CCArray* arr, Fun fun = cstring_int_fun())
{
    vector<int> vec;
    ccarray2vector(vec, arr, fun);
    return vec;
}

static inline void vector2ccarray(CCArray* arr, vector<int>& vec){
    arr->removeAllObjects();
    for (int i=0; i<vec.size(); i++) {
        arr->addObject(HString::createWithInteger(vec[i]));
    }
}

static inline CCArray* vector2ccarray(vector<int>& vec){
    CCArray* arr = CCArray::createWithCapacity(vec.size());
    for (int i=0; i<vec.size(); i++) {
        arr->addObject(HString::createWithInteger(vec[i]));
    }
    
    return arr;
}

static inline bool isTouchInside(CCTouch *pTouch, CCNode* pNode)
{
    if (pNode->getParent()) {
        CCPoint touchLocation = pTouch->getLocation(); // Get the touch position
        touchLocation = pNode->getParent()->convertToNodeSpace(touchLocation);
        CCRect bBox= pNode->boundingBox();
        return bBox.containsPoint(touchLocation);
    }else{
        CCPoint touchpoint = pTouch->getLocation();
        CCRect rect = pNode->boundingBox();
        return rect.containsPoint(touchpoint);
    }
}


#endif /* defined(__card__UIDefine__) */
