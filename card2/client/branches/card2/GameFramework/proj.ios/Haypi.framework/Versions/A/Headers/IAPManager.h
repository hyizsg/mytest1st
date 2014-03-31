//
//  IAPManager.h
//  
//
//  Created by Royal on 11-5-9.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import "net.h"

//用户认证错误
#define ERROR_CODE_NOT_AUTHORIZED                   1
//Game服务器返回错误
#define ERROR_CODE_GAMESERVER                       2

// do not modified
#define REQUEST_IAP_ITEM_LIST                   1701
#define REQUEST_IAP_MADE_PAYMENT                1702
#define REQUEST_IAP_PAYMENT_COMPLETED           1703
#define REQUEST_IAP_PAYMENT_FAILED              1704
#define REQUEST_IAP_MAKE_PAYMENT                1705

@protocol IAPManagerProtocol <NSObject>
@required
- (void)onIAPErrorWithCode:(int)code message:(NSString *)message;

@optional
// 开始向苹果请求 IAP Item 信息
// 可以开始转菊花了
- (void)requestIAPListFromApple;

// 从苹果获取IAP Item信息
// 可以通过 getItemCount，getItemByIndex 等函数，刷新金币商店的TableView
// 如果 ［array count］ != 0，说明有无效的IAP Item Key，被苹果返回了
- (void)receiveIAPListFromAppleWithInvalidateProductArray:(NSArray *)invalidateArray;

// 购买流程结束
// result : 0 = OK, 1 = failed , 2 canceled
- (void)onIAPPurchaseFinished:(int)result;

// 购买流程结束, 如果需要知道具体那个单，则实现此回调
// result : 0 = OK, 1 = failed , 2 canceled
- (void)onIAPPurchaseFinished:(int)result productID:(NSString*)productID;

// 本地处理金币购买流程结束
// result : 0 = OK, 1 = failed , 2 canceled
- (void)onIAPPurchaseFinished:(int)result itemID:(int)itemID itemToken:(NSString*)itemToken;

@end

@interface IAPItem : NSObject

// ID,内部使用
@property (nonatomic, assign) int ID;
@property (nonatomic, assign) double price;                     // 基于本地币种的价格
@property (nonatomic, assign) int discount;                     // 增加的金币数量
@property (nonatomic, assign) int count;                        // 基础金币数量
@property (nonatomic, copy) NSString * key;                     // iap product id
@property (nonatomic, copy) NSString * localizedTitle;          // Apple给出的本地化包名
@property (nonatomic, copy) NSString * localizedDescription;    // Apple给出的本地化描述
@property (nonatomic, copy) NSString * priceSymbol;             // 本地币种的货币符号
@property (nonatomic, copy) NSString * discountString;          // 打折短语，类似于 "50% Off"
@property (nonatomic, copy) NSString * iapEnString;             // iap server 给出的英文描述
@property (nonatomic, copy) NSString * iapCnString;             // iap server 给出的中文描述
#ifdef OBJC_ARC_ENABLED
@property (strong, nonatomic) SKProduct *product;
#else
@property (retain, nonatomic) SKProduct *product;
#endif
@end

@interface IAPManager : NSObject<SKProductsRequestDelegate , SKPaymentTransactionObserver, NetReceiveDelegate>
{
    NSTimer* iapTimer;
    NSMutableDictionary* iapKeyChain;
    NSMutableArray * itemArray;
    NSMutableArray * paymentQueue;
}

#ifdef OBJC_ARC_ENABLED
@property (strong, nonatomic) SKProductsRequest *request;
#else
@property (retain, nonatomic) SKProductsRequest *request;
#endif
//<-----------------------------UI调用-----------------------------
// 程序启动后调用
+ (void)startWithDelegate:(NSObject<IAPManagerProtocol> *)delegate;
// 停止IAP处理
+ (void)stop;
// 获取IAP项目数量
+ (int)getItemCount;
// 通过索引查找IAP项目
+ (IAPItem *)getItemByIndex:(int)index;
// 通过ID查找IAP项目
+ (IAPItem *)getItemByID:(int)ID;
// 购买IAP项目
+ (bool)buyItemByIndex:(int)index;
// 检查本地保存的记录，未被服务器接收的，则重新发送
+ (void)checkAndSendPayment;
//------------------------------UI调用---------------------------->
// 设置Game ID
+ (void)setGameID:(int)GameID;
@end
