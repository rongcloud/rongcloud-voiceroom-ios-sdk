//
//  RCVoiceRoomConfig.h
//  RCVoiceRoomEngine
//
//  Created by zang qilong on 2021/4/14.
//

#import <Foundation/Foundation.h>
#import <RongRTCLib/RongRTCLib.h>

NS_ASSUME_NONNULL_BEGIN

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

/// 自动生成该类对应的json字符串
- (NSString *)jsonString;

/// 后端传入初始化语聊房信息需要附带的kv信息。
- (NSDictionary<NSString *, NSString *> *)createRoomKV;

@end

NS_ASSUME_NONNULL_END
