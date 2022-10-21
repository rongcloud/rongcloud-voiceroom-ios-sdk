//
//  RCVoiceRoomError.h
//  RCVoiceRoomLib
//
//  Created by xuefeng on 2022/7/15.
//

#import <RCVoiceRoomLib/RCVoiceRoomErrorCode.h>

@protocol RCVoiceRoomError <NSObject>

/// 错误信息
@property (nonatomic, copy, readonly, nonnull)          NSString *message;

/// 补充信息
@property (nonatomic, copy, nullable)                   NSString *messageSupplement;

/// 当前错误的解决方法
@property (nonatomic, copy, readonly, nullable)         NSArray<NSString *> *solutions;

/// Error convert to Json
@property (nonatomic, copy, readonly, nullable)         NSString *jsonString;

/// 错误 RCVoiceRoomErrorCode
@property (nonatomic, assign, readonly)                 NSInteger code;

/// 出错 API 的相关参数
@property (nonatomic, copy, nullable)                   NSDictionary<NSString *, NSDictionary*> *param;

/// 底层 IM  RTC 报错信息
@property (nonatomic, copy, readonly, nullable)         NSString *nativeErrorMessage;

/// 底层错误类型
@property (nonatomic, copy, nonnull)                    NSString *nativeErrorType;

/// 底层错误 Code
@property (nonatomic, assign, readonly)                 NSInteger nativeErrorCode;

/// 获取格式化后的 log 字符串
- (nonnull NSString *)logString;

@end

