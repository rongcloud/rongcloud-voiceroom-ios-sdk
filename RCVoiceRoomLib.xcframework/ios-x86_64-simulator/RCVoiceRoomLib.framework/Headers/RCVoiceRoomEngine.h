//
//  RCVoiceRoomEngine.h
//  RCVoiceRoomEngine
//
//  Created by zang qilong on 2021/4/13.
//

#import <Foundation/Foundation.h>

#import "RCVoiceRoomErrorCode.h"
#import "RCVoiceRoomDefine.h"

NS_ASSUME_NONNULL_BEGIN

@class RCVoiceRoomInfo, RCMessageContent, RCVoiceSeatInfo, RCVoicePKInfo;
@protocol RCVoiceRoomDelegate, RCIMClientReceiveMessageDelegate;


typedef void(^RCVoiceRoomSuccessBlock)(void);
typedef void(^RCSVoiceClearCompletion)(NSArray<NSString *> *clearKeys);
typedef void(^RCVoiceRoomErrorBlock)(RCVoiceRoomErrorCode code, NSString *msg);

/// PK回复类别
typedef NS_ENUM(NSUInteger, RCPKResponseType) {
    RCPKResponseAgree = 0,
    RCPKResponseReject = 1,
    RCPKResponseIgnore = 2
};

@interface RCVoiceRoomEngine : NSObject

/// 语聊房SDK的单例
+ (RCVoiceRoomEngine *)sharedInstance;

/// 设置语聊房的Delegate
/// @param delegate 语聊房delegate
- (void)setDelegate:(id<RCVoiceRoomDelegate>)delegate;

- (void)setSeatPlaceHolderStateEnable:(BOOL)seatPlaceHolderStateEnable;

@end

@interface RCVoiceRoomEngine (Room)

/// 创建并加入语聊房
/// @param roomId 语聊房Id
/// @param roomInfo 语聊房信息，语聊房名字和麦位数量不可为空
/// @param successBlock 创建成功回调
/// @param errorBlock 创建失败回调
- (void)createAndJoinRoom:(NSString *)roomId
                     room:(RCVoiceRoomInfo *)roomInfo
                  success:(RCVoiceRoomSuccessBlock)successBlock
                    error:(RCVoiceRoomErrorBlock)errorBlock;

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

/// 设置房间信息，房间的id必须与当前房间id一致
/// @param roomInfo 修改的房间信息
/// @param successBlock 设置成功
/// @param errorBlock 设置失败
- (void)setRoomInfo:(RCVoiceRoomInfo *)roomInfo
            success:(RCVoiceRoomSuccessBlock)successBlock
              error:(RCVoiceRoomErrorBlock)errorBlock;

/// 当前所在房间
- (nullable NSString *)roomId;

@end

@interface RCVoiceRoomEngine (Seat)

/// 获取最新的麦位信息
/// @param successBlock 麦位信息列表回调
/// @param errorBlock 失败回调
- (void)getLatestSeatInfo:(void (^)(NSArray<RCVoiceSeatInfo *>*))successBlock
                    error:(RCVoiceRoomErrorBlock)errorBlock;

/// 用户主动上麦
/// @param seatIndex 麦位序号
/// @param successBlock 上麦成功
/// @param errorBlock 上麦失败
- (void)enterSeat:(NSUInteger)seatIndex
          success:(RCVoiceRoomSuccessBlock)successBlock
            error:(RCVoiceRoomErrorBlock)errorBlock;

/// 用户主动下麦
/// @param successBlock 下麦成功
/// @param errorBlock 下麦失败
- (void)leaveSeatWithSuccess:(RCVoiceRoomSuccessBlock)successBlock
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
- (void)pickUserToSeat:(NSString *)userId
               success:(RCVoiceRoomSuccessBlock)successBlock
                 error:(RCVoiceRoomErrorBlock)errorBlock;

/// 将某个麦位的用户下麦
/// @param userId 下麦的用户id
/// @param successBlock 下麦成功
/// @param errorBlock 下麦失败
- (void)kickUserFromSeat:(NSString *)userId
                 success:(RCVoiceRoomSuccessBlock)successBlock
                   error:(RCVoiceRoomErrorBlock)errorBlock;

/// 清理麦位锁状态
/// @param clearCompletion 成功回调
/// @param errorBlock 失败回调
- (void)clearSeatState:(RCSVoiceClearCompletion)clearCompletion
                 error:(RCVoiceRoomErrorBlock)errorBlock;

/// 将某个用户踢出房间
/// @param userId 踢出房间的userId
/// @param successBlock 成功回调
/// @param errorBlock 失败回调
- (void)kickUserFromRoom:(NSString *)userId
                 success:(RCVoiceRoomSuccessBlock)successBlock
                   error:(RCVoiceRoomErrorBlock)errorBlock;

/// 锁定某个麦位，如果该麦位有人，会将用户强制下麦
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

/// 更新麦位extra属性
/// @param index 麦位序号
/// @param extra 更新的extra
/// @param successBlock 更新成功回调
/// @param errorBlock 更新失败回调
- (void)updateSeatInfo:(NSUInteger)index
             withExtra:(NSString *)extra
               success:(RCVoiceRoomSuccessBlock)successBlock
                 error:(RCVoiceRoomErrorBlock)errorBlock;

/// 将除了自身所在麦位的其余所有麦位静音或者取消静音
/// @param isMute 是否静音
- (void)muteOtherSeats:(BOOL)isMute;

/// 静音所有远程音频流
/// @param isMute 是否静音所有远程音频流
- (void)muteAllRemoteStreams:(BOOL)isMute;

/// 将所有麦位锁麦或者解除锁麦
/// 该方法不会锁定有人的麦位
/// @param isLock 是否锁麦
- (void)lockOtherSeats:(BOOL)isLock;

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


/// 拒绝用户排麦请求
/// @param userId 请求排麦的用户id
/// @param successBlock 拒绝请求成功
/// @param errorBlock  拒绝请求失败
- (void)rejectRequestSeat:(NSString *)userId
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
- (void)notifyVoiceRoom:(NSString *)name
                content:(NSString *)content;

@end

@interface RCVoiceRoomEngine (Control)

/// 停止本地麦克风收音
/// @param isDisable 是否停止
- (void)disableAudioRecording:(BOOL)isDisable;

/// 获取麦克风状态
- (BOOL)isDisableAudioRecording;

/// 设置房间音频质量和场景
/// @param quality 音频质量
/// @param scenario 音频场景
- (void)setAudioQuality:(RCVoiceRoomAudioQuality)quality
               scenario:(RCVoiceRoomAudioScenario)scenario;

/// 设置是否使用扬声器
/// @param isEnable 是否使用
- (void)enableSpeaker:(BOOL)isEnable;

@end

@interface RCVoiceRoomEngine (PK)

/// 发送PK邀请
/// @param inviteeRoomId 被邀请用户所在的房间id
/// @param inviteeUserId 被邀请人的用户id
/// @param successBlock 邀请发送成功回调
/// @param errorBlock 邀请发送失败回调
- (void)sendPKInvitation:(NSString *)inviteeRoomId
                 invitee:(NSString *)inviteeUserId
                 success:(RCVoiceRoomSuccessBlock)successBlock
                   error:(RCVoiceRoomErrorBlock)errorBlock;

/// 撤回已发送的PK邀请
/// @param inviteeRoomId 被邀请用户所在的房间id
/// @param inviteeUserId 被邀请人的用户id
/// @param successBlock 邀请撤回发送成功
/// @param errorBlock 邀请撤回发送失败
- (void)cancelPKInvitation:(NSString *)inviteeRoomId
                   invitee:(NSString *)inviteeUserId
                   success:(RCVoiceRoomSuccessBlock)successBlock
                     error:(RCVoiceRoomErrorBlock)errorBlock;

/// 回复邀请人是否接受邀请
/// @param inviterRoomId 邀请人所在的房间id
/// @param inviterUserId 邀请人的用户id
/// @param type 回应邀请者的类型，接受，拒绝或者忽略
/// @param successBlock 回复发送成功
/// @param errorBlock 回复发送失败
- (void)responsePKInvitation:(NSString *)inviterRoomId
                     inviter:(NSString *)inviterUserId
                responseType:(RCPKResponseType)type
                     success:(RCVoiceRoomSuccessBlock)successBlock
                       error:(RCVoiceRoomErrorBlock)errorBlock;

/// 屏蔽PK对象的语音
/// @param isMute 是否屏蔽
/// @param successBlock 调用成功
/// @param errorBlock 调用失败
- (void)mutePKUser:(BOOL)isMute
           success:(RCVoiceRoomSuccessBlock)successBlock
             error:(RCVoiceRoomErrorBlock)errorBlock;

/// 恢复跨房间 PK
/// @param info PK 的信息
/// @param successBlock 恢复成功
/// @param errorBlock 恢复失败
- (void)resumePKWithPKInfo:(RCVoicePKInfo *)info
                   success:(RCVoiceRoomSuccessBlock)successBlock
                     error:(RCVoiceRoomErrorBlock)errorBlock;

/// 退出PK
/// @param successBlock 退出成功
/// @param errorBlock 退出失败
- (void)quitPK:(RCVoiceRoomSuccessBlock)successBlock
         error:(RCVoiceRoomErrorBlock)errorBlock;

@end

@interface RCVoiceRoomEngine (Analysis)

+ (NSString *)getVersion;

@end

@interface RCVoiceRoomEngine (Deprecated)

/// 发送信息
/// @param message 融云消息实体
/// @param successBlock 发送成功
/// @param errorBlock 发送失败
- (void)sendMessage: (RCMessageContent *)message
            success:(RCVoiceRoomSuccessBlock)successBlock
              error:(RCVoiceRoomErrorBlock)errorBlock DEPRECATED_MSG_ATTRIBUTE("use IMLib/IMKit sendMessage instead");

@end

NS_ASSUME_NONNULL_END
