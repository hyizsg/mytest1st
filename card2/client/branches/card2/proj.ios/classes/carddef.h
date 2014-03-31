//
// carddef.h
// card
//
// Created by bo wei on 13-8-13.
//
//

#ifndef card_carddef_h
#define card_carddef_h

#define APPSTORE_ID 676013354
#define APPURL "https://itunes.apple.com/cn/app/xi-you-ji-online/id676013354"
#define APP_VERSION "1.3"

#define quickSupportUrl "http://news.xyj-ol.com/support/quick/index.php?aut=%s&tem=cn&tem=%d"
#define checkVersionUrl "http://update.xyj-ol.com/version/url.php"
//#define checkVersionUrl "http://192.168.1.235/card/version/url.php"


#define GC_APP 0
#define GC_91 2
#define GC_PP 11
#define GC_TW 17

//kLanguageEnglish = 0,
//kLanguageChinese,
//kLanguageFrench,
//kLanguageItalian,
//kLanguageGerman,
//kLanguageSpanish,
//kLanguageRussian,
//kLanguageKorean,
//kLanguageJapanese,
//kLanguageHungarian,
//kLanguagePortuguese,
//kLanguageArabic

#define kLanguageLocal kLanguageChinese
#define kIsTaiWanChinese false

#define CURR_GCTYPE GC_APP
#define CURR_DEVICETYPE 1
#define CURR_PLATFORM 0


//
// 正式版
//
#if CURR_GCTYPE == GC_APP

#define kHMNewsUrl ("http://news1.xyj-ol.com/card/news.php?gid=HAYPI_CARD&lan=%@&ver=%d&server=%d&deviceid=%@&host_appid=com.games.west.ol&df=%d")
#define kHMSmallNewsUrl "http://news1.haypi.mobi/index.php?action=categories&tem=gettankuangmeg&value1=1&value3=cn&value2=%d"
#define kGameCommentUrl "https://itunes.apple.com/cn/app/xi-you-ji-online/id676013354"

#ifdef Special_Edition
#undef Special_Edition
#endif

#define Enabel_Admob
#define Enable_OU
#define Enable_Tapjoy
#define Enable_TalkingData
#define Enable_chartboost
#define Enable_Inmob
//#define Enable_Facebook
//#define Enable_PartyTrack
//#define Enable_Vpon
//#define Enable_Inmedia
//#define Enable_Free4u


#define HCardAdmobID "982809738"
#define HCardAdmobLabel "5w1CCKbtpQcQivnR1AM"
#define HCardAdmobValue "0"

#define HCardTapJoyID "eca3a64e-1cd0-41d9-93bb-6d0f63d8cea3"
#define HCardTapJoyKey "CvYgOsHs0GV2nVQcVDiQ"

#define HCardChartBoostID "5253b8ab17ba47dd74000005"
#define HCardChartBoostKey "01089f793e2f995c22382d4af2ad58cc270a5019"

#define HCardInmoKey "55702f3d8ae94c4b8c77e1953eb84744"

#define HCardFlurryKey "N8P6YPPY2S5ZHK8XGYYZ"
#define HCardTalkDataKey "530a634f6d084a2ea3d288db7abca25b"

#define HCardFree4uID "7e0a41c5-b32b-4dd6-86d0-f3e1842d4726"

//
// 91合作平台
//
#elif CURR_GCTYPE == GC_91

#define kHMNewsUrl ("http://news1.xyj-ol.com/card/news.php?gid=HAYPI_CARD&lan=%@&ver=%d&server=%d&deviceid=%@&host_appid=com.games.west.ol&df=%d")
#define kHMSmallNewsUrl "http://news1.haypi.mobi/index.php?action=categories&tem=gettankuangmeg&value1=1&value3=cn&value2=%d"
#define kGameCommentUrl "https://itunes.apple.com/cn/app/xi-you-ji-online/id676013354"

#ifndef Special_Edition
#define Special_Edition
#endif

#define PLATFORM_NAME "91"
#define kAppIdFor91 106650
#define kAppKeyFor91 "f3c9cf0f272b8014ef68a908aacda136a5c8d9809ef42eab"

#define Enabel_Admob


#define HCardAdmobID "982809738"
#define HCardAdmobLabel "5w1CCKbtpQcQivnR1AM"
#define HCardAdmobValue "0"

#define HCardTapJoyID "eca3a64e-1cd0-41d9-93bb-6d0f63d8cea3"
#define HCardTapJoyKey "CvYgOsHs0GV2nVQcVDiQ"

#define HCardChartBoostID "5253b8ab17ba47dd74000005"
#define HCardChartBoostKey "01089f793e2f995c22382d4af2ad58cc270a5019"

#define HCardInmoKey "55702f3d8ae94c4b8c77e1953eb84744"

#define HCardFlurryKey "N8P6YPPY2S5ZHK8XGYYZ"
#define HCardTalkDataKey "530a634f6d084a2ea3d288db7abca25b"

//
// PP合作平台
//
#elif CURR_GCTYPE == GC_PP

#ifndef Special_Edition
#define Special_Edition
#endif

#define PLATFORM_NAME "PP"
#define kAppIdForPP 1239
#define kAppKeyForPP @"aeaddb0449febeb0b14a471ad1cc8c13"

#define kHMNewsUrl ("http://news1.xyj-ol.com/cardpp/news.php?gid=HAYPI_CARD&lan=%@&ver=%d&server=%d&deviceid=%@&host_appid=com.games.west.ol&df=%d")
#define kHMSmallNewsUrl "http://news1.haypi.mobi/index.php?action=categories&tem=gettankuangmeg&value1=1&value3=cn&value2=%d"
#define kGameCommentUrl "http://www.25pp.com/ipad/game/info_1059993.html"

//
// 昆仑合作平台
//
#elif CURR_GCTYPE == GC_TW

#define kHMNewsUrl ("http://news1.xyj-ol.com/card/news.php?gid=HAYPI_CARD&lan=%@&ver=%d&server=%d&deviceid=%@&host_appid=com.games.west.ol&df=%d")
#define kHMSmallNewsUrl "http://news1.haypi.mobi/index.php?action=categories&tem=gettankuangmeg&value1=1&value3=cn&value2=%d"
#define kGameCommentUrl "https://itunes.apple.com/cn/app/xi-you-ji-online/id676013354"

#ifndef Special_Edition
#define Special_Edition
#endif

#define PLATFORM_NAME "91"

#define Enabel_Admob
#define Enable_Facebook
#define Enable_PartyTrack
#define Enable_Vpon
#define Enable_Inmedia
#define Enable_Free4u

#define HCardAdmobID "1005338770"
#define HCardAdmobLabel "W6aECK7RzQkQkoGx3wM"
#define HCardAdmobValue "0"

#define HCardFlurryKey "N8P6YPPY2S5ZHK8XGYYZ"
#define HCardTalkDataKey "530a634f6d084a2ea3d288db7abca25b"

#define HCardDmobID "56OJzOxouNMVwm56oQ"

#define HCardTapJoyID "eca3a64e-1cd0-41d9-93bb-6d0f63d8cea3"
#define HCardTapJoyKey "CvYgOsHs0GV2nVQcVDiQ"

#define HCardChartBoostID "5253b8ab17ba47dd74000005"
#define HCardChartBoostKey "01089f793e2f995c22382d4af2ad58cc270a5019"

#define HCardInmoKey "55702f3d8ae94c4b8c77e1953eb84744"

#define HCardFacebookAppID "1390167037897070"
#define HCardFacebookAppSecret "ce0b6a7fbbeb674511ff5cf023366c9c"

#define HCardPartytrackAppID 1328
#define HCardPartytrackAppKey "b5e4233812561d200a4e4db43a6d93f1"
#define HCardPartytrackEventID 7001

#define HCardVponGoalID "5457a1369f57327e454a918c902d03eee4c6"

#define HCardInmediaPixelURL "http://mt.adtrackserv.com/tracking/sdkpixel/"
#define HCardInmediaAdID "advertiserId"
#define HCardInmediaAppID "1031"
#define HCardInmediaReferral false

#define HCardFree4uID "8747adcc-ef42-4a5f-9b01-0f583790a7c7"
//#define HCardFree4youHK "bc8898b0-6e26-45bb-b25b-5b64dbe2f698"

#endif



#define OU_APPID "113580122111289660"

#define helpUrl "http://www.xyj-ol.com/helpmb/index.php"
#define mainurl "http://www.xyj-ol.com"


#define HPASSPORTURL "http://passport.xyj-ol.com/passport/passport.php"
#define HLOCALPASSPORTURL "http://192.168.1.235/card/passport/passport.php"
#define HGAME_ID "com.games.west.ol"
#define HSOCKETIP "SocketIP"
#define HSOCKETPORT "SocketPort"

#define HVISIT_WEBSITE "http://www.xyj-ol.com"



#endif
