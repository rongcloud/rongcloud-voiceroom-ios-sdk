//
//  RCSMicrophoneState.h
//  RCVoiceRoomLib
//
//  Created by shaoshuai on 2022/10/14.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCSMicrophoneState : NSObject

@property (nonatomic, copy) NSString *roomId;

@property (nonatomic, copy) NSString *userId;

@property (nonatomic, assign) BOOL disable;

@end

NS_ASSUME_NONNULL_END
