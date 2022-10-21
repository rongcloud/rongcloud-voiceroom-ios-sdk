//
//  RCVoiceRoomDelegate_DP_2_1_X.h
//  RCVoiceRoomLib
//
//  Created by shaoshuai on 2022/9/30.
//

#import <RCVoiceRoomLib/RCVoiceRoomErrorCode.h>

NS_ASSUME_NONNULL_BEGIN

/// 本文件相关接口，只能在 2.1.x 版本及以下版本可用，之后版本可能将不起作用

@class RCMessage;

@protocol RCVoiceRoomDelegate_DP_2_1_X <NSObject>

@optional

/// 房间发生异常问题
- (void)roomDidOccurError:(RCVoiceRoomErrorCode)code __attribute__((deprecated("请使用使用roomDidOccurErrorWithDetails方法")));

/// 麦位麦克风状态变化回调
/// @param speaking 是否正在说话
/// @param index 麦位序号
/// @param level 音量值
- (void)seatSpeakingStateChanged:(BOOL)speaking
                         atIndex:(NSInteger)index
                      audioLevel:(NSInteger)level __attribute__((deprecated("请使用使用audioLevelDidChange:方法")));

/// 用户麦克风状态变化回调
/// @param speaking 是否正在说话
/// @param userId 上麦用户Id
/// @param level 音量值
- (void)userSpeakingStateChanged:(BOOL)speaking
                          userId:(NSString *)userId
                      audioLevel:(NSInteger)level __attribute__((deprecated("请使用使用audioLevelDidChange:方法")));

/// 收取信息回调
/// @param message 收到的消息
- (void)messageDidReceive:(RCMessage *)message;

@end

NS_ASSUME_NONNULL_END
