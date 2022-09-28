//
//  RCVoiceRoomEngine+Plugin.h
//  RCVoiceRoomLib
//
//  Created by johankoi on 2022/9/27.
//

#import "RCVoiceRoomEngine.h"

NS_ASSUME_NONNULL_BEGIN

@class RCVoiceSeatInfo;

@interface RCVoiceRoomEngine (Plugin)
/// 用户主动上麦
/// @param seatIndex 麦位序号
/// @param info 麦位信息(mute extra)
/// @param successBlock 上麦成功
/// @param errorBlock 上麦失败
- (void)enterSeat:(NSUInteger)seatIndex
         seatInfo:(nullable RCVoiceSeatInfo *)info
          success:(RCVoiceRoomSuccessBlock)successBlock
            error:(RCVoiceRoomErrorBlock)errorBlock;

/// 更新某个麦位上的信息
/// @param index 麦位序号
/// @param info 麦位信息(mute extra)
/// @param successBlock 更新成功回调
/// @param errorBlock 更新失败回调
- (void)updateSeatInfo:(NSUInteger)index
              seatInfo:(nullable RCVoiceSeatInfo *)info
               success:(RCVoiceRoomSuccessBlock)successBlock
                 error:(RCVoiceRoomErrorBlock)errorBlock;

/// 用户跳麦，在用户已经在麦位想切换麦位时调用
/// @param seatIndex 需要跳转的麦位序号
/// @param preSeat 更新旧麦位信息
/// @param targetSeat 更新新麦位信息
/// @param successBlock 跳麦成功
/// @param errorBlock 跳麦失败
- (void)switchSeatTo:(NSUInteger)seatIndex
             preSeat:(nullable RCVoiceSeatInfo *)preSeat
          targetSeat:(nullable RCVoiceSeatInfo *)targetSeat
             success:(RCVoiceRoomSuccessBlock)successBlock
               error:(RCVoiceRoomErrorBlock)errorBlock;

/// 用户跳麦，在用户已经在麦位想切换麦位时调用
/// @param seatIndex 需要跳转的麦位序号
/// @param switchMute 跳麦携带mute，被携带后的麦位mute会被置为false； false: 不携带mute
/// @param switchExtra 跳麦携带extra，被携带后的麦位extra会被置为null； false: 不携带extra
/// @param successBlock 跳麦成功
/// @param errorBlock 跳麦失败
- (void)switchSeatTo:(NSUInteger)seatIndex
          switchMute:(BOOL)switchMute
         switchExtra:(BOOL)switchExtra
             success:(RCVoiceRoomSuccessBlock)successBlock
               error:(RCVoiceRoomErrorBlock)errorBlock;
@end

NS_ASSUME_NONNULL_END
