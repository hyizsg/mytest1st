/*
 *  action_def.h
 *  
 *
 *  Created by jim kaden on 10-5-21.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __ACTION_DEF_H__
#define __ACTION_DEF_H__

#define ACTION_REGISTER							102
#define ACTION_LOGIN							101
#define ACTION_SERVERLIST                       112

#define ACTION_SYSINFO							201
#define ACTION_NOTIFY							202
#define ACTION_CLEAR_NOTIFY						203

#define ACTION_GAMECONFIG						210

#define ACTION_PLAYER_INFO						301
#define ACTION_CLAN_INFO						302
#define ACTION_CLAN_LIST						303
#define ACTION_FACTORY_LIST						304
#define ACTION_HARBOR_LIST						305		//305
#define ACTION_LABOR_LIST						306
#define ACTION_OTHERPLAYER_INFO					307

#define ACTION_UPGRADE_PLAYER					401
#define ACTION_UPGRADE_TECH						402
#define ACTION_UPGRADE_WAREHOUSE				403
#define ACTION_UPGRADE_SHIP						404
#define ACTION_UPGRADE_CAPTAIN					405
#define ACTION_UPGRADE_CLAN						406
#define ACTION_LEARN_CAREER1					407
#define ACTION_LEARN_CAREER2					408
#define ACTION_UPGRADE_CAREER1					409
#define ACTION_UPGRADE_CAREER2					410

#define ACTION_MARKET_GUIDE_PRICE				701
#define ACTION_MARKET_TRADE_LIST				702
#define ACTION_MARKET_SELL_GOODS				703
#define ACTION_MARKET_BUY_GOODS					704
#define ACTION_MARKET_MY_LISTED					705
#define ACTION_MARKET_NPC_PRICE					706
#define ACTION_MARKET_BUYOUT_PRICE				707
#define ACTION_MARKET_CANCEL_MYTRADE			708
#define ACTION_MARKET_SELL_NPC					709
#define ACTION_MARKET_BUY_NPC					710

#define ACTION_CHAT_VERSION						801
#define ACTION_CHAT_INFO						802

#define ACTION_NAMELIST_QUERY					803
#define ACTION_NAMELIST_MODIFY					804
#define ACTION_CHAT_SEND						805
#define ACTION_IMPORTANT_MSG					806

#define ACTION_RANK_QUERY						994
#define ACTION_RANK_USER						995

#define ACTION_SENDMAIL							996
#define ACTION_READMAIL							997
#define ACTION_MAILHEADERS						998
#define ACTION_DELETEMAIL						999

//Create
#define ACTION_CREATEPART						1101
#define ACTION_ASSEMBLESHIP						1102
#define ACTION_MAINTAINSHIP						1103
#define ACTION_REPAIRPART						1104
#define ACTION_REPAIRSHIP						1105

//Ship operation
#define ACTION_SAILTRADESHIP					1106
#define ACTION_CARGOMANAGER						1110

//Unity action
#define ACTION_UNITY_LOADSEADATA				1201
#define ACTION_UNITY_GETTREASUREPOINT			1202
#define ACTION_UNITY_OPENCHEST					1203
#define ACTION_UNITY_GETTREASURE				1204
#define ACTION_UNITY_ENVEVENT					1205
#define ACTION_UNITY_CALLBACKSHIP				1206
#define ACTION_UNITY_SHIPPOSITION				1207
#define ACTION_UNITY_USEPHARMACY				1208
#define ACTION_UNITY_SOLUTION_PUZZLE			1209
#define ACTION_UNITY_GETSCENESTATUS				1210

//Alliance
#define ACTION_ALLIANCE_GETINFO					1301
#define ACTION_ALLIANCE_CREATE					1302
#define ACTION_ALLIANCE_JOIN					1303
#define ACTION_ALLIANCE_APPROVE					1304
#define ACTION_ALLIANCE_DENY					1305
#define ACTION_ALLIANCE_QUIT					1306
#define ACTION_ALLIANCE_DISMIS					1307
#define ACTION_ALLIANCE_MEMBERLIST				1308
#define ACTION_ALLIANCE_UNAPPROVELIST			1309
#define ACTION_ALLIANCE_BID						1310
#define ACTION_ALLIANCE_FINACIALINFO			1311
#define ACTION_ALLIANCE_EVENTLIST				1312
#define ACTION_ALLIANCE_PROMOTEMEMBER			1313
#define ACTION_ALLIANCE_DEGRADEMEMBER			1314
#define ACTION_ALLIANCE_DONATE					1315
#define ACTION_ALLIANCE_KICKOUTMEMBER			1316
#define ACTION_ALLIANCE_MODIFYANNOUCEMENT		1317
#define ACTION_ALLIANCE_GETBIDINFO				1318
#define ACTION_ALLIANCE_SENTLETTER				1319


//Vote
#define ACTION_VOTEUSER							1401

// IAP

#define ACTION_QUERY_IAP						1701
#define ACTION_PROCESS_IAP						1702
#define ACTION_FINISH_IAP						1703
#define ACTION_FAILED_IAP						1704
#define ACTION_UPLOAD_PUSH_TOKEN				1710


// Task
#define ACTION_TASK_LIST						1801
#define ACTION_TASK_APPLY						1802
#define ACTION_TASK_REWARD						1803
#define ACTION_TASK_RENAME						1804

//Captain
#define ACTION_CAPTAIN_LIST						1901
#define ACTION_CAPTAIN_HIRE						1902
#define ACTION_CAPTAIN_ASSIGN					1903
#define ACTION_CAPTAIN_FIRE						1904
#define ACTION_CAPTAIN_ATTRIBUTE				1905
#define ACTION_CAPTAIN_IMPROVELOYALTY			1906
#define ACTION_CAPTAIN_RESETATTR				1907
#define ACTION_CAPTAIN_SPEEDUP_REFRESHLIST		1908

//drift
#define ACTION_DRIFTCHECK						2001
#define ACTION_DRIFTGETGIFT						2002

//Hall
#define ACTION_HALL_ELECTION_RANK				2101

// Common Header

#define kGAMEPLAY_ID							"GAMEPLAY_ID"
#define kACTION									"ACTION"
#define kACTION_KEY								"ACTION_KEY"
#define kAUTH_KEY								"AUTH_KEY"
#define kACTION_CONFIRM							"ACTION_COM"

#define kServerTime                             "CurrentTime"
#define kServerList                             "ServerList"
// Account

#define kUserURL								"Url"
#define kUserName								"Name"
#define kPassword								"Password"
#define kUserID									"MemberID"
#define kUserEMail								"EMail"
#define kUserInvitedBy							"InvitedBy"
#define kUserRegion								"RegionID"
#define kDeviceID								"DeviceID"
#define kExtraInfo								"ExtraInfo"
#define kServerID								"SID"
#define kGameMode								"GameMode"

// player info
#define kPlayerBasic							"Basic"
#define kPlayerFinancial						"Financial"
#define kPlayerShips							"Ships"
#define kPlayerCaptains							"Captains"
#define kPlayerTechnic							"Technic"
#define kPlayerParts							"Parts"
#define kPlayerPharmacy							"Gears"
#define kPlayerIDList							"IDList"
#define kPlayerShipIDs							"ShipIDs"
#define kPlayerCaptainIDs						"CaptainIDs"
#define kPlayerPartIDs							"PartIDs"
#define kPlayerMemberInfo						"MemberInfo"
#define kOtherPlayerInfo						"PlayerInfo"

// basic
#define kHarborID								"HarborID"
#define kCareerID								"CareerID"
#define kShipID									"ShipID"
#define kTradeID								"TradeID"
#define kCaptainID								"CaptainID"
#define kClanID									"ClanID"
#define kCareerID1								"CareerID1"
#define kCareerID2								"CareerID2"
#define kLevel1									"Level1"
#define kLevel2									"Level2"
#define kLevel									"Level"
#define kClanRole								"Role"
#define kMasterID								"MasterID"
#define kAddon									"Addon"
#define kPrestige								"Prestige"
#define kTitleId								"TitleId"
#define kUserStatus								"Status"
#define kUserRank								"Rank"
#define kUserGoodPoint							"GoodPoint"
#define kUserBadPoint							"BadPoint"
#define kUserPoint								"Point"
#define kReqBanTime								"ReqBanTime"
#define kMuteTime								"MuteTime"
#define kRankTime								"RankTime"

// Financial
#define kCapacity								"Capacity"
#define kMoney									"Money"
#define kCoins									"Coins"
#define kEnergyPoint							"EnergyPoint"
#define kFullTime								"FullTime"
#define kTreasures								"Treasures"
#define kGuildUpgradeToken						"Token"

// Ships
#define kType									"Type"

#define kBody									"Body"
#define kEngine									"Engine"
#define kSonar									"Sonar"
#define kWeapon									"Weapon"
#define kAirbag									"Airbag"

#define kBodyID									"BodyID"
#define kEngineID								"EngineID"
#define kSonarID								"SonarID"
#define kWeaponID								"WeaponID"
#define kAirbagID								"AirbagID"
#define kCanvasId								"CanvasID"
#define kSpeed									"Speed"
#define kHardness								"Hardness"
#define kMaxHardness							"MaxHardness"
#define kMaxCapacity							"MaxCapacity"
#define kLossGoodsRate							"LossGoodsRate"
#define kMaxDepth								"MaxDepth"
#define kDefense								"Defense"
#define kStamina								"Stamina"
#define kMaxSonarRange							"MaxRange"
#define kStatus									"Status"
#define kHarborFrom								"HarborFrom"
#define kHarborTo								"HarborTo"
#define kLeaveDate								"StartDate"
#define kArriveDate								"Date"

// Technic
#define kTechType								"Tech"
#define kTechLevel								"Level"
#define kTechUT									"UT"

// Captain
#define kCaptainName							"Name"
#define kCaptainType							"Type"
#define kCaptainCommission						"Commission"
#define kCaptainGrade							"Grade"
#define kCaptainLevel							"Level"
#define kCaptainExp								"Exp"
#define kCaptainLoyalty							"Loyalty"
#define kCaptainStatus							"Status"
#define kCaptainAptitude						"Aptitude"
#define kCaptainTalent							"Talent"
#define kAttrWisdom								"Wisdom"
#define kAttrSail								"Sail"
#define kAttrDefense							"Defense"
#define kAttrDiplomacy							"Diplomacy"
#define kAttrLucky								"Lucky"
#define kAttrAddon								"Addon"
#define kAddLoyalty								"AddLoyalty"
#define kNextTime								"NextTime"

// Part
#define kPartIDs								"PartIDs"
#define kPartID									"PartID"
#define kPartCreator							"Creator"
#define kPartCreatedDate						"CreatedDate"
#define kPartType								"PartType"
#define kPartLevel								"Level"
#define kPartProp								"PartProp"
#define kPartStatus								"Status"
#define kPartHardness							"Hardness"
#define kPartDate								"Date"

// Treasure
//#define kTreasureAllCount						"All"
//#define kTreasurePuton							"On"
#define kTreasurePrice							"P"
#define kTreasureAmount							"N"


// Mail


#define kMailID									"MailID"
#define kMailBody								"MailBody"
#define kMailTo									"MailTo"
#define kMailFrom								"MailFrom"
#define kMailSubject							"MailSubject"
#define kMailTime								"MailTime"
#define kMailHeaders							"MailHeaders"
#define kMailType								"MailType"
#define kMailReadFlag							"HaveRead"
// Rank 

#define kRankUserInfo							"RankUserInfo"
#define kRankInfo								"RankInfo"
#define kRankType								"RankType"
#define kRankPage								"RankPage"
#define kRankPerson								"Person"
#define kRankClan								"Clan"
#define kRankTitle								"Title"
#define kHasMoreData							"HasMoreData"

#define kRankData								"rankData"

#define kRankNumber								"Number"
#define kRankUserName							"Name"
#define kRankUserID								"UserID"
#define kRankLeader								"Leader"
#define kRankPrestige							"Prestige"
#define kRankRich								"Rich"

// chat

#define kChatInfo								"ChatInfo"
#define kChatChannel							"GroupName"
#define kChatVersions							"ChatVersions"
#define kNO										"NO"
#define kFrom									"From"
#define kTo										"To"
#define kStatus1								"ST1"
#define kStatus2								"ST2"
#define kPVPRank1								"PR1"
#define kPVPRank2								"PR2"
#define kChatTime								"Time"
#define kChatData								"Data"
#define kChatMySelf								"Myself"

#define kChatRoom								"ChatRoom"
#define kChatMessage							"Message"
#define kImportantMsg							"ImportantMessage"
// Name list
#define kNameList								"NameList"
#define kOP										"OP"
#define kListType								"ListType"
#define kFriendList								"FriendList"
#define kBlockList								"BlockList"


// market
#define kPrices									"Prices"
#define kGoods									"Goods"
#define kMyGoods								"MyGoods"
#define kGoodsTypeList							"GoodsTypeList"
#define kNPCPrices								"NPCPrices"
#define kBuyoutPrices							"BuyoutPrices"
#define kGoodsType								"GoodsType"
#define kUnitPrice								"UnitPrice"
#define kUnitPriceBase							"UnitPriceBase"
#define kMinPrice								"MinPrice"
#define kMaxPrice								"MaxPrice"
#define kAmount									"Amount"
#define kSubmitDate								"Date"
#define kPageIndex								"PageIndex"
#define kDetail									"Detail"
#define kCreator								"Creator"
#define kCreatedDate							"CreatedDate"
#define kGoodsID								"ID"

// notification
#define kNotification							"Notification"
#define kNotify									"Notify"
#define kNotificationVersion					"Version"
#define kNotifConfirm							"NotifConfirm"
#define kUrgent									"Urgent"
#define kNeedConfirm							"NeedConfirm"
#define kParams									"Params"
#define kNotifCode								"NotifCode"
#define kNotifMsg								"NotifMsg"
#define kNotifExpireTime						"ExpireTime"
#define kNotifStartTime							"StartTime"
#define kNotifData								"Data"
#define kActionKey								"ActionKey"
#define kActionResult							"Result"


// clan
#define kClanMember								"Member"
#define kClanBidInfo							"BidInfo"
#define kClanBidderList							"BidderList"
#define kClanIDList								"IDList"
#define kClanInfo								"ClanInfo"
#define kClanPageIndex							"PageIndex"
#define kClanList								"ClanList"

#define kClanLeader								"Leader"
#define kClanFlagID								"FlagID"
#define kAllianceName							"ClanName"
#define kClanName								"Name"
#define kClanAnnouncement						"Announcement"
#define kClanCreatedDate						"CreatedDate"
#define kClanLevel								"Level"
#define kClanMoney								"Money"
#define kClanPrestige							"Prestige"
#define kClanMembersInfo						"MembersInfo"
#define kClanBidDate							"BidDate"
#define kClanBidPrice							"BidPrice"
#define kClanChangeCount						"ChangeCount"
#define kClanEventList							"EventList"
#define kClanEventType							"Type"
#define kClanEventTime							"Time"
#define kClanEventParam							"Param"
#define kClanEventOpName1						"Name"
#define kClanEventOpName2						"OpName"
#define kClanEventOpTreasure					"Treasure"
#define kClanLetterTitle						"Title"
#define kClanLetterContent						"Content"

// clan members info
#define kClanMembersName						"Name"
#define kClanMembersRole						"Role"
#define kClanMembersJoinDate					"JoinDate"
#define kClanMembersBouns						"Bouns"
#define kClanMembersStatus						"Status"
#define kClanMemberCount						"MemberCount"
#define kClanFactoryInfo						"FactoryInfo"
#define kClanFactoryInfoOwner					"Owner"
#define kClanFactoryInfoRepirer					"Repirer"

// Harbor
#define kHarborIDList							"IDList"
#define kHarborList								"HarborList"
#define kHarborName								"Name"
#define kHarborStatus							"Status"
#define kHarborDescription						"Description"
#define kHarborX								"X"
#define kHarborY								"Y"
#define kHarborNextBidTime						"NextBidTime"

// GameConfig

// Config Group
#define kGameConfigCurrentVersion				"CurrentVersion"
#define kGameConfig								"GameConfig"
#define kGameConfigBuildPart					"BuildPart"
#define kGameConfigPartProp						"PartProp"
#define kGameConfigRepair						"Repair"
#define kGameConfigGoodsGuidePrices				"Market"
#define kGameConfigTechInfo						"TechInfo"
#define kGameConfigGoodsProperties				"GoodsProp"
#define kGameConfigUserProperties				"UserProp"
#define kGameConfigSkillProperties				"CareerProp"
#define kGameConfigSeabedProperties				"SeabedProp"

// Config property
#define kGameConfigSkillID						"SkillID"
#define kGameConfigPartType						"PartType"
#define kGameConfigPartDefDB					"PartDefDB"
#define kGameConfigBuildPartCareerType			"CR"
#define kGameConfigBuildPartCoin				"C"
#define kGameConfigBuildPartMoney				"M"
#define kGameConfigBuildPartEnergy				"ER"
#define kGameConfigBuildPartResources			"TR"
#define kGameConfigRepairNPCRatio				"NPCRatio"
#define kGameConfigRepairBase					"RepairBase"
#define kGameConfigRepairEnergy					"RepairEnergy"
#define kGameConfigNPCSellRatio					"NPCSell"
#define kGameConfigNPCBuyRatio					"NPCBuy"

#define kGameConfigTechResource					"R"
#define kGameConfigTechDepency					"D"
#define kGameConfigTechProperty					"P"

#define kGameConfigMaxEnergy					"MaxEnergy"
#define kGameConfigEnergyChargeSpeed			"EnergySpeed"
#define kGameConfigUserUpgrade					"Upgrade"
#define kGameConfigNeedGoods					"Goods"
#define kGameConfigNeedTech						"NeedTech"

#define kGameConfigCareer1UserLevel				"Career1UserLevel"
#define kGameConfigCareer2UserLevel				"Career2UserLevel"

#define kGameConfigSeabedEvent					"Event"
#define kGameConfigSeabedEventRate				"Rate"
#define kGameConfigSeabedEventAffectPartType	"PartType"
#define kGameConfigSeabedEventAffectValue		"HarmBase"

// Create and Maintain
#define kShipType								"ShipType"
#define kShipName								"Name"
#define kBodyID									"BodyID"
#define kEngineID								"EngineID"
#define kSonarID								"SonarID"
#define kWeaponID								"WeaponID"
#define kAirbagID								"AirbagID"
#define kShipAction								"ShipAction"


// Unity
#define kUnitySeaID								"SeaType"
#define kUnitySeaData							"SeaBed"
#define kUnityToken								"Token"
#define kUnityGridList							"GridList"
#define kUnityChestType							"ConType"
#define kUnityX									"X"
#define kUnityY									"Y"
#define kUnityEventType							"ObjectType"
#define kUnityMapType							"MapType"
#define kUnityShipX								"ShipX"
#define kUnityShipY								"ShipY"
#define kUnityMapWidth							"Width"
#define kUnityMapHeight							"Length"
#define kUnityGridWidth							"GridWidth"
#define kUnityGridHeight						"GridHeight"
#define kUnityDepth								"Depth"
#define kUnityDensity							"Density"
#define kUnityOxgenRatio						"OxgenRatio"
#define kUnityContainerList						"ContainerList"
#define kUnityEnviromentType					"Pattern"
#define kUnityEnvRate							"ObjectRate"
#define kUnityChestActionType					"Action"
#define kUnityMazeType							"MythType"
#define kUnityTreasureNeed						"NeedTr"
#define kUnityTreasureList						"Treasures"
#define kUnityResultType						"ResultType"
#define kUnityDescription						"Description"
#define kUnityAttenuation						"Vlevel"
#define kUnityChestStatus						"Status"
#define kUnitySeaAction							"SeaAction"
#define kUnitySeaActionTime						"ActionTime"
#define kUnitySpeed								"Speed"
#define kUnityDamage							"Harm"
#define kUnityPartID							"PartID"
#define kUnityDesc								"Desc"
#define kUnityLevelInfo							"LevelInfo"
#define kUnityTargetStatus						"TargetStatus"

// Vote
#define kVoteUser								"VoteUser"
#define kVoteType								"VoteType"


// IAP
#define kIAPUser								"IAP_User"
#define kIAPTransID								"TransID"
#define kIAPServerID							"ServerID"
#define kIAPProductID							"PID"
#define kIAPReception							"Reception"
#define kIAPCount								"Count"
#define kIAPList								"IAP_List"
#define kTransList								"TransList"

// Push
#define kPushToken								"PToken"

// Task
#define kTaskList								"TaskList"
#define kTaskType								"TaskType"
#define kTaskCompleteType						"Type"
#define kTaskID									"TaskID"
#define kTaskDesc								"Desc"
#define kTaskName								"Name"
#define kTaskStatus								"Status"
#define kTaskRequirement						"Require"
#define kTaskReward								"Reward"
#define kTaskResult								"Result"

//Speed up
#define kSpeedHours								"Hours"

// Hall
// Election rank
#define kElecID									"EleID"
#define kElecTime								"EleTime"
#define kElecRank								"Rank"
#define kElecName								"Name"
#define kElecPoint								"Point"
#define kElecGoodPoint							"GoodPoint"
#define kElecBadPoint							"BadPoint"

#define objcGAMEPLAY_ID							@"GAMEPLAY_ID"
#define objcACTION								@"ACTION"
#define objcACTION_KEY							@"ACTION_KEY"
#define objcAUTH_KEY							@"AUTH_KEY"
#define objcACTION_CONFIRM						@"ACTION_COM"

// utilities toNSString
#define TO_NS(x)								[NSString stringWithUTF8String:(x)]
#endif
