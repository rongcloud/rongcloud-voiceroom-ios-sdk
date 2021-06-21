# 融云语聊房SDK介绍



## 概述

语聊房SDK为用户提供了一套便捷，有效的针对语聊房场景的SDK。可以让用户在短时间内搭建一套完整的语聊房系统。

## 基础架构

语聊房SDK基于融云的IMLib和RTCLib, 利用IMLib强大的KV和信令管理来完成对语聊房中的麦位管理和各种通知信息，既可以在短时间内同步所有麦位信息也可以基于麦位信息自由切换和订阅不同用户的音频流，内部自动化的处理使用户无需关心角色切换等语聊房常见事件。

## 语聊房使用简介

### 语聊房房间类 RCVoiceRoomInfo

```objective-c

@interface RCVoiceRoomInfo : NSObject<NSCopying>

/// 房间名称，不可为空
@property (nonatomic, copy) NSString *roomName;

/// 房间麦位数量，不可为空
@property (nonatomic, assign) NSInteger seatCount;

/// 房间音质
@property (nonatomic, assign) RCRTCAudioQuality audioQuality;

/// 房间场景
@property (nonatomic, assign) RCRTCAudioScenario scenario;

/// 是否自由上麦
@property (nonatomic, assign) BOOL isFreeEnterSeat;

/// 是否将所有麦位静音
@property (nonatomic, assign) BOOL isMuteAll;

/// 是否将所有麦位关闭
@property (nonatomic, assign) BOOL isLockAll;

/// 自定义属性，可以传入json等
@property (nonatomic, copy, nullable) NSString *extra;

- (instancetype)init;

/// 类方法，根据jsonString生成一个RCVoiceRoomInfo实例
/// @param jsonSting RCVoiceRoomInfo的jsonSting
+ (RCVoiceRoomInfo *)modelWithJSON:(NSString *)jsonSting;

/// 自动生成该类的json字符串
- (NSString *)jsonString;

/// 后端传入初始化语聊房信息需要附带的kv信息。
- (NSDictionary<NSString *, NSString *> *)createRoomKV;
```

由于目前SDK不支持直接创建房间，所以需要后端配合处理语聊房的初始化。

现简述创建一个语聊房流程。

1. 后端可设置一个post接口，如`http://localhost/room/create`
2. 初始化一个`RCVoiceRoomInfo`实例，其中`roomName` 和 `seatCount` 不可为空。
3. 在post接口的body中，通过实例的 `createRoomKV` 方法传入后端room的kv信息，后端在创建房间时，初始化房间的kv信息。

### 语聊房麦位类  RCVoiceSeatInfo

```objective-c
typedef NS_ENUM(NSUInteger, RCSeatStatus) {
    RCSeatStatusEmpty = 0,
    RCSeatStatusUsed = 1,
    RCSeatStatusLock = 2,
};

@interface RCVoiceSeatInfo : NSObject<NSCopying>

/// 麦位状态，分为空置，有人使用，被锁定三种状态
@property (nonatomic, assign) RCSeatStatus status;

/// 是否静音
@property (nonatomic, assign, getter=isMuted) BOOL mute;

/// 若麦位被人使用，则userId为使用麦味的用户id
@property (nonatomic, copy, nullable) NSString *userId;

/// 其他信息
@property (nonatomic, copy, nullable) NSString *extra;

- (instancetype)init;

/// 类方法，根据jsonString生成一个RCVoiceSeatInfo实例
/// @param jsonSting RCVoiceSeatInfo的jsonSting
+ (RCVoiceSeatInfo *)modelWithJSON:(NSString *)jsonSting;

/// 自动生成该类对应的json字符串
- (NSString *)jsonString;

@end
```

麦位类 `RCVoiceSeatInfo` 包含了语聊房通用的麦位信息。

具体描述可看头文件中的注释。

### 核心类 RCVoiceRoomEngine 和对应的回调类 RCVoiceRoomDelegate

```objective-c
//
//  RCVoiceRoomEngine.h
//  RCVoiceRoomEngine
//
//  Created by zang qilong on 2021/4/13.
//

#import <Foundation/Foundation.h>
#import <RongRTCLib/RongRTCLib.h>
#import "RCVoiceRoomInfo.h"
#import "RCVoiceRoomDelegate.h"

NS_ASSUME_NONNULL_BEGIN

typedef void(^RCVoiceRoomSuccessBlock)(void);
typedef void(^RCVoiceRoomErrorBlock)(NSInteger code, NSString *msg);

@interface RCVoiceRoomEngine : NSObject

/// 语聊房SDK的单例
+ (RCVoiceRoomEngine *)sharedInstance;

/// 设置语聊房的Delegate
/// @param delegate 语聊房delegate
- (void)setDelegate:(id<RCVoiceRoomDelegate>)delegate;

/// 增加其他消息监听Delegate
/// @param delegate RCMicMessageHandleDelegate
- (void)addMessageReceiveDelegate:(id<RCIMClientReceiveMessageDelegate>)delegate;

/// 删除某个消息监听Delegate
/// @param delegate RCMicMessageHandleDelegate
- (void)removeMessageReceiveDelegate:(id<RCIMClientReceiveMessageDelegate>)delegate;

/// 初始化AppKey, 如果已初始化RCCoreClient可以不掉用此方法
/// @param appKey 在融云系统中申请的key
- (void)initWithAppkey:(NSString *)appKey;

/// 连接融云服务器，如果使用RCCoreClient连接过服务可不用调用此方法
/// @param appToken 从服务器中获取的token
/// @param successBlock 连接成功回调
/// @param errorBlock 连接失败回调
- (void)connectWithToken:(NSString *)appToken
                 success:(RCVoiceRoomSuccessBlock)successBlock
                   error:(RCVoiceRoomErrorBlock)errorBlock;

/// 断开连接
- (void)disconnect;

/// 用户根据roomId加入一个语聊房
/// @param roomId 房间id
/// @param successBlock 加入成功回调
/// @param errorBlock 加入失败回调
- (void)joinRoom:(NSString *)roomId
         success:(RCVoiceRoomSuccessBlock)successBlock
           error:(RCVoiceRoomErrorBlock)errorBlock;

/// 离开房间
/// @param successBlock 离开房间成功
/// @param errorBlock 离开房间失败
- (void)leaveRoom:(RCVoiceRoomSuccessBlock)successBlock
                   error:(RCVoiceRoomErrorBlock)errorBlock;

/// 用户主动上麦
/// @param seatIndex 麦位序号
/// @param successBlock 上麦成功
/// @param errorBlock 上麦失败
- (void)enterSeat:(NSUInteger)seatIndex
                   success:(RCVoiceRoomSuccessBlock)successBlock
                     error:(RCVoiceRoomErrorBlock)errorBlock;

/// 用户主动下麦
/// @param seatIndex 麦位序号
/// @param successBlock 下麦成功
/// @param errorBlock 下麦失败
- (void)leaveSeat:(NSUInteger)seatIndex
                   success:(RCVoiceRoomSuccessBlock)successBlock
                     error:(RCVoiceRoomErrorBlock)errorBlock;

/// 用户跳麦，在用户已经在麦位想切换麦位时调用
/// @param seatIndex 需要跳转的麦位序号
/// @param successBlock 跳麦成功
/// @param errorBlock 跳麦失败
- (void)switchSeatTo:(NSUInteger)seatIndex
                  success:(RCVoiceRoomSuccessBlock)successBlock
                    error:(RCVoiceRoomErrorBlock)errorBlock;

/// 抱用户上麦
/// @param userId 用户id
/// @param successBlock 抱麦成功
/// @param errorBlock 抱麦失败
- (void)pickSeat:(NSString *)userId
                   success:(RCVoiceRoomSuccessBlock)successBlock
                     error:(RCVoiceRoomErrorBlock)errorBlock;

/// 将某个麦位的用户下麦
/// @param userId 下麦的用户id
/// @param successBlock 下麦成功
/// @param errorBlock 下麦失败
- (void)kickSeat:(NSString *)userId
         success:(RCVoiceRoomSuccessBlock)successBlock
           error:(RCVoiceRoomErrorBlock)errorBlock;

/// 将某个用户踢出房间
/// @param userId 踢出房间的userId
/// @param successBlock 成功回调
/// @param errorBlock 失败回调
- (void)kickOutRoom:(NSString *)userId
                      success:(RCVoiceRoomSuccessBlock)successBlock
                        error:(RCVoiceRoomErrorBlock)errorBlock;

/// 锁定某个麦位
/// @param seatIndex 麦位序号
/// @param isLocked 是否锁麦位
/// @param successBlock 锁麦成功
/// @param errorBlock 锁麦失败
- (void)lockSeat:(NSUInteger)seatIndex
            lock:(BOOL)isLocked
         success:(RCVoiceRoomSuccessBlock)successBlock
           error:(RCVoiceRoomErrorBlock)errorBlock;

/// 将某个麦位静音
/// @param seatIndex 麦位序号
/// @param isMute 是否静音
/// @param successBlock 静音成功
/// @param errorBlock 静音失败
- (void)muteSeat:(NSUInteger)seatIndex
            mute:(BOOL)isMute
         success:(RCVoiceRoomSuccessBlock)successBlock
           error:(RCVoiceRoomErrorBlock)errorBlock;

/// 将所有麦位静音打开或者关闭
/// @param isMute 是否静音
- (void)muteOtherSeats:(BOOL)isMute;

/// 静音所有远程音频流
/// @param isMute 是否静音所有远程音频流
- (void)muteAllRemoteStreams:(BOOL)isMute;

/// 将所有麦位锁麦或者解除锁麦
/// @param isLock 是否锁麦
- (void)lockOtherSeats:(BOOL)isLock;

/// 发送信息
/// @param message 融云消息实体
/// @param successBlock 发送成功
/// @param errorBlock 发送失败
- (void)sendMessage: (RCMessageContent *)message
            success:(RCVoiceRoomSuccessBlock)successBlock
              error:(RCVoiceRoomErrorBlock)errorBlock;

/// 设置房间信息，房间的id必须与当前房间id一致
/// @param roomInfo 修改的房间信息
/// @param successBlock 设置成功
/// @param errorBlock 设置失败
- (void)setRoomInfo:(RCVoiceRoomInfo *)roomInfo
            success:(RCVoiceRoomSuccessBlock)successBlock
              error:(RCVoiceRoomErrorBlock)errorBlock;

/// 停止本地麦克风收音
/// @param isDisable 是否停止
- (void)disableAudioRecording:(BOOL)isDisable;

/// 设置房间音频质量和场景
/// @param quality 音频质量
/// @param scenario 音频场景
- (void)setAudioQuality:(RCRTCAudioQuality)quality
               scenario:(RCRTCAudioScenario)scenario;

/// 设置是否使用扬声器
/// @param isEnable 是否使用
- (void)enableSpeaker:(BOOL)isEnable;

/// 请求排麦
/// @param successBlock 请求排麦发送成功
/// @param errorBlock 请求排麦发送失败
- (void)requestSeat:(RCVoiceRoomSuccessBlock)successBlock
                         error:(RCVoiceRoomErrorBlock)errorBlock;

/// 取消排麦请求
/// @param successBlock 取消排麦成功
/// @param errorBlock 取消排麦失败
- (void)cancelRequestSeat:(RCVoiceRoomSuccessBlock)successBlock
                               error:(RCVoiceRoomErrorBlock)errorBlock;

/// 同意用户排麦请求
/// @param userId 请求排麦的用户id
/// @param successBlock 同意请求成功
/// @param errorBlock 同意请求失败
- (void)acceptRequestSeat:(NSString *)userId
                            success:(RCVoiceRoomSuccessBlock)successBlock
                              error:(RCVoiceRoomErrorBlock)errorBlock;



/// 获取当前排麦的用户列表
/// @param successBlock 成功获取回调
/// @param errorBlock 获取失败回调
- (void)getRequestSeatUserIds:(void (^)(NSArray<NSString *>*))successBlock
                                       error:(RCVoiceRoomErrorBlock)errorBlock;

/// 发送请求
/// @param content 发送请求的内容
- (void)sendInvitation:(NSString *)content
                          success:(void (^)(NSString *))successBlock
                            error:(RCVoiceRoomErrorBlock)errorBlock;

/// 拒绝请求
/// @param invitationId 请求id
- (void)rejectInvitation:(NSString *)invitationId
                 success:(RCVoiceRoomSuccessBlock)successBlock
                   error:(RCVoiceRoomErrorBlock)errorBlock;

/// 同意请求
/// @param invitationId 请求id
- (void)acceptInvitation:(NSString *)invitationId
                 success:(RCVoiceRoomSuccessBlock)successBlock
                   error:(RCVoiceRoomErrorBlock)errorBlock;

/// 取消自己发出的请求
/// @param invitationId 请求id
- (void)cancelInvitation:(NSString *)invitationId
                 success:(RCVoiceRoomSuccessBlock)successBlock
                   error:(RCVoiceRoomErrorBlock)errorBlock;

/// 通知房间所有用户执行某个刷新操作
/// @param name 刷新操作的名称
/// @param content 刷新操作的内容
- (void)notifyVoiceRoom:(NSString *)name content:(NSString *)content;

@end

NS_ASSUME_NONNULL_END

```

`RCVoiceRoomEngine` 是整个SDK的核心类。所有麦位管理和房间管理的操作都由此类执行。

```objective-c
//
//  RCVoiceRoomDelegate.h
//  RCVoiceRoomEngine
//
//  Created by zang qilong on 2021/4/15.
//

#import <Foundation/Foundation.h>
#import "RCVoiceRoomInfo.h"
#import "RCVoiceSeatInfo.h"

NS_ASSUME_NONNULL_BEGIN

@protocol RCVoiceRoomDelegate <NSObject>

/// 房间的信息和麦位信息初始化完成回调，用户可在此执行关于房间的其他初始化操作
- (void)roomKVDidReady;

/// 房间信息变更回调
/// @param roomInfo 房间信息
- (void)roomInfoDidChanged:(RCVoiceRoomInfo *)roomInfo;

/// 房间座位变更回调，包括自身上麦或下麦也会触发此回调
/// @param seatInfolist 座位列表信息
- (void)seatInfoDidChanged:(NSArray<RCVoiceSeatInfo *> *)seatInfolist;

/// 某个主播上麦回调，包含自己上麦也会触发此回调
/// @param seatIndex 麦位号
/// @param userId 用户Id
- (void)userDidEnterSeat:(NSInteger)seatIndex
                   user:(NSString *)userId;

/// 某个主播下麦回调，包含自己下麦也会触发此回调
/// @param seatIndex 麦位号
/// @param userId 用户Id
- (void)userDidLeaveSeat:(NSInteger)seatIndex
                   user:(NSString *)userId;

/// 座位静音状态回调
/// @param index 座位号
/// @param isMute 静音状态
- (void)seatDidMute:(NSInteger)index
            isMute:(BOOL)isMute;

/// 座位关闭回调
/// @param index 座位号
/// @param isLock 是否关闭
- (void)seatDidLock:(NSInteger)index
            isLock:(BOOL)isLock;

/// 观众进房回调
/// @param userId 观众Id
- (void)audienceDidEnter:(NSString *)userId;

/// 观众退房回调
/// @param userId 观众Id
- (void)audienceDidExit:(NSString *)userId;

/// 用户音量变动回调
/// @param seatIndex 麦位序号
/// @param isSpeaking 是否正在说话
- (void)speakingStateDidChanged:(NSUInteger)seatIndex
                                  speakingState:(BOOL)isSpeaking;

/// 收取信息回调
/// @param message 收到的消息
- (void)messageDidReceived:(RCMessage *)message;

/// 收到房间的广播信息
- (void)roomNotificationDidReceived:(NSString *)name content:(NSString *)content;

/// 收到自己被抱上麦的请求
- (void)pickSeatDidReceivedFrom:(NSString *)userId;

/// 收到自己被下麦的通知
- (void)kickSeatDidReceived:(NSUInteger)seatIndex;

/// 发送的排麦请求得到房主或管理员同意
- (void)requestSeatDidAccepted;

/// 发送的排麦请求被房主或管理员拒绝
- (void)requestSeatDidRejected;

/// 排麦列表发生变化
- (void)requestSeatListDidChanged;

/// 接受邀请
/// @param invitationId 邀请的Id
/// @param userId 发送邀请的用户
/// @param content 邀请内容，用户可以自定义
- (void)invitationDidReceived:(NSString *)invitationId
                          from:(NSString *)userId
                       content:(NSString *)content;

/// 邀请被接受回调
/// @param invitationId 邀请Id
- (void)invitationDidAccepted:(NSString *)invitationId;

/// 邀请被拒绝回调
/// @param invitationId 邀请Id
- (void)invitationDidRejected:(NSString *)invitationId;

/// 邀请被取消回调
/// @param invitationId 邀请Id
- (void)invitationDidCancelled:(NSString *)invitationId;


/// 用户被踢出房间的回调
/// @param targetId 被踢出房间的用户id
/// @param userId 执行踢某人出房间的用户id
- (void)userDidReceiveKickoutRoom:(NSString *)targetId byUserId:(NSString *)userId;

@end

NS_ASSUME_NONNULL_END

```

`RCVoiceRoomDelegate` 是 `RCVoiceRoomEngine` 对应的回调。例如房间信息的更新，麦位信息的变化等，都会通过回调的形式同步给所有加入房间的用户。

现简述SDK工作流程。

1. 通过后端创建完一个语聊房并设置kv后。用户可在进入房间时，调用 `joinRoom` 加入房间。
2. 加入房间成功后，engine 会通过kv同步房间的各种状态，在同步完成后，回调中的 `- (void)roomKVDidReady` 会触发。用户可在此方法中执行其他初始化操作，例如，房主在进入房间后需要自动上麦，那么可在此方法中让房主执行 `enterSeat` 操作。
3. 进入房间后，有两个回调也会触发。

```objective-c
/// 房间信息变更回调
/// @param roomInfo 房间信息
- (void)roomInfoDidChanged:(RCVoiceRoomInfo *)roomInfo;

/// 房间座位变更回调，包括自身上麦或下麦也会触发此回调
/// @param seatInfolist 座位列表信息
- (void)seatInfoDidChanged:(NSArray<RCVoiceSeatInfo *> *)seatInfolist;

```

用户可在此房间中同步最新的麦位信息和房间信息。执行刷新UI的操作。同时，这两个回调也是触发频次最高的回调，你通常应该在这两个方法中执行所有关于麦位和房间的UI操作。例如房主将8号麦位锁定之后，那么 `seatInfoDidChanged`  就会触发，如果你是通过 `UICollectionView` 来绘制麦位UI， 那么你可能需要 `reloadData`从而使麦位的Cell显示最新的UI。

4. 此刻，你的语聊房就正式初始化完成了。其他方法和对应回调可通过注释了解。

## 安装

推荐使用Pod安装。
在Podfile中，加入 pod 'RCVoiceRoomLib'
然后执行pod install 即可。
