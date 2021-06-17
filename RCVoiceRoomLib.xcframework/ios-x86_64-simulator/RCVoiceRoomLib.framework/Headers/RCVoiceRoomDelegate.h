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
