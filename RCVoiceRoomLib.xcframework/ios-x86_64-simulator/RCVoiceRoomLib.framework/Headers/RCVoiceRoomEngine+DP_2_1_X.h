//
//  RCVoiceRoomEngine+DP_2_1_X.h
//  RCVoiceRoomLib
//
//  Created by shaoshuai on 2022/9/30.
//

#import <RCVoiceRoomLib/RCVoiceRoomEngine.h>

NS_ASSUME_NONNULL_BEGIN

/// 本文件相关接口，只能在 2.1.x 版本及以下版本可用，之后版本可能将不起作用

@class RCMessageContent;

@interface RCVoiceRoomEngine (DP_2_1_X)

/// 发送信息
/// @param message 融云消息实体
/// @param successBlock 发送成功
/// @param errorBlock 发送失败
- (void)sendMessage: (RCMessageContent *)message
            success:(RCVoiceRoomSuccessBlock)successBlock
              error:(RCVoiceRoomErrorBlock)errorBlock DEPRECATED_MSG_ATTRIBUTE("use IMLib/IMKit sendMessage instead");

@end

NS_ASSUME_NONNULL_END
