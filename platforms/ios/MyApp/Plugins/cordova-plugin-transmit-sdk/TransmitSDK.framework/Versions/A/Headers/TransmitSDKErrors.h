//
//  TransmitSDKErrors.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 11/23/15.
//  Copyright © 2015 TransmitSecurity. All rights reserved.
//

#ifndef TS_SDK_ERRORS_H
#define TS_SDK_ERRORS_H
#import <Foundation/Foundation.h>

extern NSString* _Nonnull const tsErrorDomain; /**< Transmit SDK error domain */
extern NSString* _Nonnull const kServerServiceProviderErrorData; /**< Error data from server side service provider */

/**
 * \enum TransmitSDKErrors TransmitSDK error codes.
 * @file TransmitSDKErrors.h
 */
typedef enum : NSUInteger {
#pragma mark Authorization
    // General errors and errors common to all SDKs
    TS_ERR_SERVER_NOT_REACHABLE = 100, /**< denotes a network error */
    TS_ERR_BAD_CUSTOMER_ID = 102, /**< Wrong or missing API token name or secret */
    TS_ERR_USER_DEVICE_UNKNOWN = 103, /**< User not logged in on the device or not registered yet */
    TS_ERR_USER_NOT_AUTHENTICATED = 104, /**< A valid authentication Server token required */
    TS_ERR_AUTH_USER_OPTED_OUT = 105, /**< User canceled authentication/registration. E.g. Declined confirmation action */
    TS_ERR_AUTH_USER_REJECTED = 107, /**< User rejected by server */
    TS_ERR_APPROVALS_EXPIRED = 110, /**< Tried to modify an already expired approval */
    TS_ERR_DATA_PROCESSING = 111, /**< Server response processing failure */
    TS_ERR_AUTH_NO_VALID_AUTHENTICATORS = 112, /**< There's no authenticator to use */
    TS_ERR_SDK_VERSION_OLD = 113, /**< The SDK version is not compatible with the Authentication server, application upgrade is required. */
    TS_ERR_REGISTRATION_PERMISSION = 114, /**< Authenticator registration terms of service declined. */
    TS_ERR_AUTH_ALL_LOCKED = 115,/**< All available Authenticators are now locked, user out of options */
    TS_ERR_APP_IMPLEMENTATION = 116, /**< Application is required to implement a delegate call or provide a missing input */
    
    // Authenticator errors - Partial and No UI SDKs
    TS_ERR_AUTHENTICATOR_LOCKED = 120, /**< Authenticator locked */
    TS_ERR_AUTHENTICATOR_NOT_REGISTERED = 121, /**< Authenticator must be configured first */
    TS_ERR_AUTHENTICATOR_ERROR = 122, /**< User failed to authenticate/enrol */
    TS_ERR_AUTHENTICATOR_EXPIRED = 123, /**< Authentication success, but authenticator expired. Show enrolment. */
    TS_ERR_AUTHETNICATOR_ALREADY_REGISTERED = 124, /**< Request to register denied, authenticator must be unregistered or expired to register */
    TS_ERR_AUTHENTICATOR_NOT_SUPPORTED = 125, /**< Requested authenticator is not supported on current device */
    TS_ERR_AUTHENTICATOR_SAMPLING_REPEAT = 126, /**< Repeat user input for Biometric Authenticator */
    TS_ERR_AUTHENTICATOR_PREREQ_MISSING = 127, /**< Prerequisites for authenticator not filled, cannot use authenticator */
    TS_ERR_AUTHENTICATOR_REGISTRATION_INVALIDATED = 128, /**< In fingerprint, changing passcode or fingerprint set invalidates registration */
    TS_ERR_AUTHENTICATOR_TEMPORARILY_NOT_AVAIL = 129, /**< Some authenticators depends on external resources that may be not available temporarily. User action not required */
    TS_ERR_AUTHENTICATOR_FALLBACK = 140, /**< Server side soft limit for number of failures reached. Switch to menu or fallback Authenticator */
    
    
    // Authenticator validations - No UI
    TS_ERR_SECRET_SEEN_BEFORE = 130, /**< User provided a secret that was used before */
    TS_ERR_SECRET_INVALID = 131, /**< Authenticator input for secret is not of valid type or format */
    TS_ERR_SECRET_TOO_LARGE = 132, /**< Biometric data input too large */
    TS_ERR_SECRET_TOO_SHORT = 133,/**< User provided a new secret that is too short */
    TS_ERR_SECRET_BLACKLISTED = 134, /**< User provided a new secret that appears in a blacklist */
    TS_ERR_SECRET_AGAIN = 135, /**< Multi step authentication (E.g. question). Completed a step successfully, please continue to next step. */
    
    // Policy
    TS_ERR_POLICY_INVALID = 151, /**< Session expired or invalid, please login again */

    // Placeholder flow
    TS_ERR_POLICY_AUTHETNICATOR_NOT_PLACEHOLDER = 152, /**< manual invocation of placeholder failed, the authenticator is not a placeholder */

} TransmitSDKErrors;


#endif
