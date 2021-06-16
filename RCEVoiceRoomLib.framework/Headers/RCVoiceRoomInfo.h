//
//  RCVoiceRoomConfig.h
//  RCVoiceRoomEngine
//
//  Created by zang qilong on 2021/4/14.
//

#import <Foundation/Foundation.h>
#import <RongRTCLib/RongRTCLib.h>

NS_ASSUME_NONNULL_BEGIN

@class RCVoiceSeatInfo;

@interface RCVoiceRoomInfo : NSObject<NSCopying>

@property (nonatomic, copy) NSString *roomName;
@property (nonatomic, assign) NSInteger seatCount;
@property (nonatomic, assign) RCRTCAudioQuality audioQuality;
@property (nonatomic, assign) BOOL isFreeEnterSeat;
@property (nonatomic, assign) BOOL isMuteAll;
@property (nonatomic, assign) BOOL isLockAll;
@property (nonatomic, assign) RCRTCAudioScenario scenario;
@property (nonatomic, copy, nullable) NSString *extra;

- (NSString *)jsonString;

- (NSDictionary<NSString *, NSString *> *)createRoomKV;

@end

NS_ASSUME_NONNULL_END
