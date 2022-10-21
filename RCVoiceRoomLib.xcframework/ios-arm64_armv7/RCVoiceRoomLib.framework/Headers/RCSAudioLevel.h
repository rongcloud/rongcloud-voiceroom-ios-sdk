//
//  RCSAudioLevel.h
//  RCVoiceRoomLib
//
//  Created by shaoshuai on 2022/9/30.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCSAudioLevel : NSObject

@property (nonatomic, copy) NSString *roomId;

@property (nonatomic, copy) NSString *userId;

@property (nonatomic, assign) NSInteger level;

@end

NS_ASSUME_NONNULL_END
