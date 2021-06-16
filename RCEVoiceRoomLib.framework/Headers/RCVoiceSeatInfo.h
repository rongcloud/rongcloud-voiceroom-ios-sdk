//
//  RCSeatInfo.h
//  RCVoiceRoomEngine
//
//  Created by zang qilong on 2021/4/14.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSUInteger, RCSeatStatus) {
    RCSeatStatusEmpty = 0,
    RCSeatStatusUsed = 1,
    RCSeatStatusLock = 2,
};

@interface RCVoiceSeatInfo : NSObject<NSCopying>

@property (nonatomic, assign) RCSeatStatus status;
@property (nonatomic, assign, getter=isMuted) BOOL mute;
@property (nonatomic, copy, nullable) NSString *userId;
@property (nonatomic, copy, nullable) NSString *extra;

@end
NS_ASSUME_NONNULL_END
