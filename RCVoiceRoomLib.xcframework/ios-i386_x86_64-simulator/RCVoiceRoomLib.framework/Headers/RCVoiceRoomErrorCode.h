//
//  RCVoiceRoomErrorCode.h
//  RCE
//
//  Created by 叶孤城 on 2021/5/26.
//

#import <Foundation/Foundation.h>

#ifndef RCVoiceRoomErrorCode_h
#define RCVoiceRoomErrorCode_h

typedef NS_ENUM(NSInteger, RCVoiceRoomErrorCode) {
    /// 未知错误
    RCVoiceRoomUnknownError = -1,
    /// 操作成功
    RCVoiceRoomSuccess = 70000,
    /// 连接服务器失败
    RCVoiceRoomConnectTokenFailed = 70001,
    /// 麦位序号不对
    RCVoiceRoomSeatIndexOutOfRange = 70002,
    /// 用户已经在麦位上
    RCVoiceRoomUserAlreadyOnSeat = 70003,
    /// 用户不在麦位上
    RCVoiceRoomUserNotOnSeat = 70004,
    /// 用户跳麦的麦位和之前的一样
    RCVoiceRoomJumpIndexEqual = 70005,
    /// 麦位不是空置状态
    RCVoiceRoomSeatNotEmpty = 70006,
    /// 不能抱自己上麦
    RCVoiceRoomPickSelfToSeat = 70007,
    /// 发送抱麦请求失败
    RCVoiceRoomPickUserFailed = 70008,
    /// 不能踢自己下麦
    RCVoiceRoomUserKickSelfFromSeat = 70009,
    /// 加入语聊房失败
    RCVoiceRoomJoinRoomFailed = 70010,
    /// 离开语聊房失败
    RCVoiceRoomLeaveRoomFailed = 70011,
    /// 获取房间信息失败
    RCVoiceRoomGetRoomInfoFailed = 70012,
    /// 已经在排麦列表中了
    RCVoiceRoomAlreadyInRequestList = 70013,
    /// 排麦人数太多
    RCVoiceRoomRequestListFull = 70014,
    /// 排麦请求发送失败
    RCVoiceRoomSendRequestSeatFailed = 70015,
    /// 取消排麦请求发送失败
    RCVoiceRoomCancelRequestSeatFailed = 70016,
    /// 同意排麦请求发送失败
    RCVoiceRoomAcceptRequestSeatFailed = 70017,
    /// 拒绝排麦请求发送失败
    RCVoiceRoomRejectRequestSeatFailed = 70018,
    /// 同步麦位信息失败
    RCVoiceRoomSyncSeatInfoFailed = 70019,
    /// 同步房间信息失败
    RCVoiceRoomSyncRoomInfoFailed = 70020,
    /// 同步排麦相关信息
    RCVoiceRoomSyncRequestSeatFailed = 70021,
    /// 获取排麦请求列表失败
    RCVoiceRoomGetRequestListFailed = 70022,
    /// 发送信息失败
    RCVoiceRoomSendMessageFailed = 70023,
    /// 请求发送失败
    RCVoiceRoomSendInvitationSeatFailed = 70024,
    /// 取消请求发送失败
    RCVoiceRoomCancelInvitationFailed = 70025,
    /// 同意请求发送失败
    RCVoiceRoomAcceptInvitationFailed = 70026,
    /// 拒绝请求发送失败
    RCVoiceRoomRejectInvitationFailed = 70027,
    /// 创建语聊房失败
    RCVoiceRoomCreateRoomFailed = 70028,
    /// 用户ID为空
    RCVoiceRoomUserIdIsEmpty = 70029,
    /// 获取麦位信息失败
    RCVoiceRoomGetLatestSeatInfoFailed = 70030,
    /// 开始PK失败
    RCVoiceRoomBeginPKFailed = 70031,
    /// 退出PK失败
    RCVoiceRoomQuitPKFailed = 70032,
    /// 发送PK邀请失败
    RCVoiceRoomSendPKInviteFaild = 70033,
    /// 取消PK请求失败
    RCVoiceRoomCancelPKFailed = 70034,
    /// 静音PK对象失败
    RCVoiceRoomMutePKUserFailed = 70035,
    /// 创建房间的信息不正确
    RCVoiceRoomCreateRoomInfoNotCorrect = 70036,
    /// 已经在PK中
    RCVoiceRoomAlreadyInPK = 70037,
    /// 切换角色失败
    RCVoiceRoomSwitchRoleFailed = 70038,
    /// 更新麦位信息失败
    RCVoiceRoomUpdateSeatInfoFailed = 70039
};

#endif /* RCVoiceRoomErrorCode_h */
