
#import "AppController.h"

#include "cocos2dxframework.h"

#import "EAGLView.h"
#import "cocos2d.h"
#import "GameScene.h"
#import "AppDelegate.h"
#import "RootViewController.h"

#import "haypi/net.h"

#include <sys/sysctl.h>

extern void informSocketState(AS_STATE state);

@interface UICustomRootView : UINavigationController
{
}
@end

@implementation UICustomRootView

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    switch (HORIENTATION_LANDSCAPE) {
        case HORIENTATION_LANDSCAPE:
            return UIInterfaceOrientationIsLandscape(interfaceOrientation);
            break;
        case HORIENTATION_PORTRAIT:
            return UIInterfaceOrientationIsPortrait(interfaceOrientation);
            break;
    }
    return true;
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
    //#ifdef __IPHONE_6_0
    switch (HORIENTATION_LANDSCAPE) {
        case HORIENTATION_LANDSCAPE:
            return UIInterfaceOrientationMaskLandscape;
            break;
        case HORIENTATION_PORTRAIT:
            return UIInterfaceOrientationMaskPortrait;
            break;
    }
    return UIInterfaceOrientationMaskAll;
    //#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

@end

@implementation AppController

@synthesize window;
@synthesize viewController;
@synthesize userDelegate;

#pragma mark -
#pragma mark Application lifecycle


// cocos2d application instance
static AppDelegate s_sharedApplication;

- (id)init
{
    if ([super init]) {
        userDelegate = nil;
    }
    
    return self;
}

#define GL_DEPTH_COMPONENT24_OES                                0x81A6
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    setScreenOrientation(requestScreenOrientation());
    
    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the EAGLView
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT24_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];
    [__glView setMultipleTouchEnabled:YES];

    // Use RootViewController manage EAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    //UINavigationController *navClr = [[UICustomRootView alloc] initWithRootViewController:viewController];
    //[navClr setNavigationBarHidden:YES];
    
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
        //[window addSubview: navClr.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
        //[window setRootViewController:navClr];
    }
    
    [window makeKeyAndVisible];    
    
    
    [[UIApplication sharedApplication] setStatusBarHidden:YES];
    
//    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString *documentsDirectory = [paths objectAtIndex:0];
//    haypi::HFileUtils::setLocalPath([documentsDirectory UTF8String]);
    
//    size_t size = sizeof(int);
//	int results;
//	int mib[2] = {CTL_HW, HW_PHYSMEM};
//	sysctl(mib, 2, &results, &size, NULL, 0);
//    HLOGI("totleMem: %d", results);
    
    NSArray *arLanguages = [NSLocale preferredLanguages];
    NSString *strLang = [arLanguages objectAtIndex:0];
    if ([strLang isEqualToString:@"zh-Hans"]) strLang = @"zh_cn";
    else if ([strLang isEqualToString:@"zh-Hant"]) strLang = @"zh_tw";
    
    haypi::setLocaleCode([strLang UTF8String]);
    
    bool bInRetinaMode = (int)[[EAGLView sharedEGLView] contentScaleFactor] == 2;
//    bInRetinaMode = (int)[[UIScreen mainScreen] scale] == 1;
    AppDelegate::getInstance()->setRetinaScreen(bInRetinaMode);
    cocos2d::CCApplication::sharedApplication()->run();
    
    if ([userDelegate respondsToSelector:@selector(application:didFinishLaunchingWithOptions:)]) {
        [userDelegate application:application didFinishLaunchingWithOptions:launchOptions];
    }

    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
//    cocos2d::CCDirector::sharedDirector()->pause();
    
    if ([userDelegate respondsToSelector:@selector(applicationWillResignActive:)]) {
        [userDelegate applicationWillResignActive:application];
    }
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
//    cocos2d::CCDirector::sharedDirector()->resume();
    
    if ([userDelegate respondsToSelector:@selector(applicationDidBecomeActive:)]) {
        [userDelegate applicationDidBecomeActive:application];
    }
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    informSocketState(AS_Background);
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
    
    if ([userDelegate respondsToSelector:@selector(applicationDidEnterBackground:)]) {
        [userDelegate applicationDidEnterBackground:application];
    }
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
    
    [viewController.view layoutSubviews];
    
    if ([userDelegate respondsToSelector:@selector(applicationWillEnterForeground:)]) {
        [userDelegate applicationWillEnterForeground:application];
    }
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
    
    if ([userDelegate respondsToSelector:@selector(applicationWillTerminate:)]) {
        [userDelegate applicationWillTerminate:application];
    }
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    
    if ([userDelegate respondsToSelector:@selector(application:didRegisterForRemoteNotificationsWithDeviceToken:)]) {
        [userDelegate application:application didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
    }
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
 
    if ([userDelegate respondsToSelector:@selector(application:didReceiveRemoteNotification:)]) {
        [userDelegate application:application didReceiveRemoteNotification:userInfo];
    }
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
    cocos2d::CCDirector::sharedDirector()->purgeCachedData();
    haypi::HSourceCache::getInstance()->forceReleaseTextures();
}

- (void)dealloc {
//    [window release];
    [super dealloc];
}


@end
