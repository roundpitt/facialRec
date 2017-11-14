//
//  TSTOtpGenerator.h
//  TransmitSDK
//
//  Created by Eldan Ben Haim on 10/01/2017.
//  Copyright © 2017 TransmitSecurity. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * TOTP Generator -- represents a TOTP token capable of providing the "current" OTP.
 */
@interface TSTOtpGenerator : NSObject {
    NSString * _Nonnull _username; /**< user name **/
}

/**
 * Username to which this generator is bound.
 */
@property(nonatomic, readonly, nonnull) NSString *username;

/**
 * Value of current OTP password.
 */
@property(nonatomic, readonly, nullable) NSString *currentOtp;

/**
 * Time left until the current OTP password expires.
 */
@property(nonatomic, readonly) NSTimeInterval currentOtpTtl;

@end
