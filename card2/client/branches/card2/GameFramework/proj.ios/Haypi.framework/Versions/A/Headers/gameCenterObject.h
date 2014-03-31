//
//  GameCenterObject.h
//  Bolt
//
//  Created by jim kaden on 11-6-8.
//  Copyright 2011年 n/a. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>
#import <UIKit/UIKit.h>
#import "net.h"

#define MAX_RETRY                   5
typedef enum
{
    UN_SUBMITTED = -1,
    SUBMIT_FAILED = 0,
    SUBMIT_OK = 1,
}
SUBMIT_STATE;
@class GameCenterManager;
@protocol GameCenterManagerDelegate;
@protocol GameCenterObjectDelegate <NSObject>
@optional
-(void)gamecenterWindowPopup:(UIViewController*)vc;
-(void)userLoggedIn:(NSString*)userID;
-(void)scoreLoaded:(GKLeaderboard*)leaderboard Result:(BOOL)result;
-(void)achievementsLoaded:(BOOL)result;
-(void)scoreReportResult:(NSString*)category Result:(BOOL)result;
-(void)achievementSubmitResult:(NSString*)category Result:(BOOL)result;
/*
 array: FriendScore的数组
 */
-(void)friendScoreLoaded:(NSArray*)array forCategory:(NSString*)leaderboard;
@end

@interface AchievementData : NSObject 
{
}
@property ( copy, nonatomic) NSString* identifier;
@property ( assign, nonatomic) double percent;
@property ( assign, nonatomic) BOOL completed;
@property ( assign, nonatomic) int retry;
@property ( assign, nonatomic) SUBMIT_STATE submitted;

+(AchievementData*)achievement:(NSString*)aid Percent:(double)per;

@end

@interface FriendScore : NSObject
{
    NSMutableDictionary* dictScores;
}
@property (copy, nonatomic) NSString* identifier;
@property (copy, nonatomic) NSString* alias;
/*
 -1 为无此分数
 */
-(int64_t)scoreForCategory:(NSString*)category;
-(void)setScore:(int64_t)score forCategory:(NSString*)category;
@end

@interface GameCenterObject : NSObject<GameCenterManagerDelegate, GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate> 
{
    GameCenterManager* gameCenter;
    NSMutableArray* arrayAchievementData;
    BOOL invalid;
    NSLock* dataLock;
}
@property (copy, nonatomic) NSString* defaultScoreCategory;
@property (assign, nonatomic, readwrite) BOOL reporting;

#ifdef OBJC_ARC_ENABLED
@property (strong, nonatomic) id<GameCenterObjectDelegate> resultDelegate;
#else
@property (retain, nonatomic) id<GameCenterObjectDelegate> resultDelegate;
#endif
+(GameCenterObject*)shareInstance;
-(void)showLeaderBoard:(UIViewController*)viewController;
-(void)showAchievements:(UIViewController*)viewController;
// login
-(void)login;
-(NSString*)localPlayerID;
-(NSString*)localPlayerName;
// achievement
-(void)setAchievementData:(AchievementData*)data;
-(void)setAchievement:(double)percent forCategory:(NSString*)aid;
-(void)startReportingAchievements;
-(GKAchievement*)getAchievement:(NSString*)category;

// score
-(void)reportScore:(int64_t)score forCategory:(NSString *)category;
/*
 在主线程中回调friendScoreLoaded，告知最新分数列表
 */
-(void)loadFriendScoresForCategory: (NSString*) category;
-(void)loadScoresForCategory: (NSString*) category range:(NSRange)range;
-(void)loadScoresForCategory: (NSString*) category range:(NSRange)range scoreType:(GKLeaderboardTimeScope) ps;
-(NSArray*)friends;
@end
