//
//  TSAuthenticatorAPI.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 03/01/2016.
//  Copyright © 2016 TransmitSecurity. All rights reserved.
//

#ifndef TSAuthenticatorAPI_h
#define TSAuthenticatorAPI_h

#import "TSDefs.h"


@class UIView;
@protocol TSAction;
@protocol TSAuthenticatorDelegate;

/**
 * A notification which is posted whenever the when a user wishes to start a password restoration procedure.
 * The application may use this notification in order to remove any SDK UI and start a password restoration procedure.
 */
extern NSString* _Nonnull const TSNotificationUserForgotPassword;

/**
 * \enum TSAuthenticatorType Authenticator types
 * @file TSAuthenticatorAPI.h
 */
typedef enum : NSUInteger {
    TS_AUTHENTICATOR_PASSWORD = 0,  /**< Password Authenticator */
    TS_AUTHENTICATOR_FINGERPRINT,   /**< Fingerprint Authenticator */
    TS_AUTHENTICATOR_PINCODE,       /**< PIN code Authenticator */
    TS_AUTHENTICATOR_PATTERN,       /**< Pattern Authenticator */
    TS_AUTHENTICATOR_OTP,           /**< One Time Password (OTP) Authenticator */
    TS_AUTHENTICATOR_FACE,          /**< Face recognition Authenticator */
    TS_AUTHENTICATOR_VOICE,         /**< Voice passphrase Authenticator */
    TS_AUTHENTICATOR_EYE,           /**< Eye identification Authenticator */
    TS_AUTHENTICATOR_EMOJI,         /**< Emoji password Authenticator */
    TS_AUTHENTICATOR_QUESTIONS,     /**< User Knowledge Questions Authenticator */
} TSAuthenticatorType;

extern NSString * _Nonnull const tsAuthenticatorIdFingerNative; /**< Native Fingerprint Authenticator implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdPINNative; /**< Native PIN code Authenticator implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdPatternNative; /**< Native Pattern Authenticator implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdPasswordNative; /**< Native Password Authenticator implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdPINCentralizedNative; /**< Native PIN code Authenticator on server implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdPatternCentralizedNative; /**< Native Pattern Authenticator on server implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdOTPNative; /**< Native OTP Authenticator implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdFaceNative; /**< Native Face recognition Authenticator implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdFaceCentralizedNative; /**< Native Face recognition Authenticator using server registration implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdVoiceServerNative; /**< Native Voice passphrase Authenticator using Nuance Voice Server implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdEyeNative; /**< Native Eye identification Authenticator implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdEmojiNative; /**< Native Emoji Authenticator implementation Id */
extern NSString * _Nonnull const tsAuthenticatorIdQuestionsNative; /**< Native Questions Authenticator implementation Id */

#pragma mark Authentication callback block

#pragma mark - TSAuthenticator
/*! \protocol TSAuthenticator TSAuthenticatorAPI.h
 *  \brief Common authenticator API.
 *
 * Common protocol to all TSAuthenticator classes.
 */
@protocol TSAuthenticator <NSObject>

/**
 *  Enumerated value of Authenticator type
 */
@property (nonatomic, readonly) TSAuthenticatorType type;

/**
 * Unique identifier for a certain Authentication method.
 */
@property (nonatomic, readonly, nonnull) NSString* authenticatorId;

/**
 *  Authenticator type name in string
 */
@property (nonatomic, readonly, nonnull) NSString* name;

/**
 *  Authenticator type name in string
 */
+(nonnull NSString*)name;

/**
 *  Authenticator name in string
 */
@property (nonatomic, readonly, nonnull) NSString* localizedName;

/**
 *  Delegate to authenticator
 */
@property (nonatomic,weak, nullable) id<TSAuthenticatorDelegate> delegate;

/**
 *  Unretained pointer to the owning action
 */
@property (nonatomic, weak, nullable) id<TSAction> action;

/**
 *  Is Authenticator replaced by a placeholder on behalf of the application.
 */
-(BOOL)isPlaceholder;

/**
 *  Is the Authenticator in a locked state and cannot be used for authentication.
 */
-(BOOL)isLocked;

/**
 *  How many retries are left before locking the authenticator. 
 *
 *  @return NSNumber with retries left integer value, or nil if no lock rule defined.
 */
-(nullable NSNumber*)retriesLeft;

/**
 *  Has the Authenticator registration expired and after authentication it will
 *  require a new registration to complete the operation.
 */
-(BOOL)isExpired;

/**
 *  Does the authenticator requires regisrtation to authenticate.
 */
-(BOOL)hasRegistration;

/**
 *  Is the authenticator registered by the user
 */
-(BOOL)isRegistered;

/**
 *  Time when the authenticator registration will be expired.
 *
 *  @return NSDate object with future expiration time.
 */
-(nullable NSDate*)expirationTime;

/**
 *  Time when the authenticator was last registered.
 *
 *  @return NSDate object with last registration time.
 */
-(nullable NSDate*)registrationTime;

/**
 *  Time when the authenticator was last used for authentication with success.
 *
 *  @return NSDate object with last successful authentication time.
 */
-(nullable NSDate*)lastUsed;

/**
 Fallback authenticator, when configured on the server, triggers a replacement of the presented 
 Authenticator when a soft threshold of number of failed authentication attempts is reached.

 @return Authenticator Id of the Fallback Authenticator
 */
-(nullable NSString*)fallbackAuthenticatorId;

/**
 Fallback authenticator, when configured on the server, triggers a replacement of the presented
 Authenticator when a soft threshold of number of failed authentication attempts is reached.

 @return Number of failed attempts allowed before fallback error is returned.
 */
-(nullable NSNumber*)fallbackThreshold;

/**
 *  Change current authentication method to fallback method if available
 */
-(void)changeToFallbackAuthenticator;

/**
 *  Can the Authenticator be used on the current device.
 *
 *  @return TRUE if it can be used on the device, otherwise FALSE.
 */
-(BOOL)isSupportedOnDevice;

/**
 *  Check if device configuration prerequisites are met for authenticator operation. 
 *  Request users permission if device resource access has not been determined by the user yet.
 *  In Fingerprint: passcode is set and there are fingerprints registered in iOS TouchID system.
 *  In Voice: Microphone premitted by user.
 *  In Face: Camera permitted by user.
 *  In Eye print: Camera permitted by user.
 */
-(void)isConfiguredOnDevice:(nullable void (^) (BOOL configured, NSError* _Nullable error))callback;

/** 
 *  Validates the user's new secret for registration complies to
 *  server side defined rules.
 */
-(nullable NSError*)validateNewSecret:(nullable id)userSecret;

/**
 *  Unregister a registered Authenticator. No UI provided.
 */
-(void)unregister:(nullable void (^) (NSError* _Nullable error))completionBlock;

/**
 *  Complete authentication with success (error is nil) or failure with NSError with reason
 */
-(void)completeAuthenticationWithOptionalError:(nullable NSError*)error;
/**
 *  Complete registration with success (error is nil) or failure with NSError with reason
 */
-(void)completeRegistrationWithOptionalError:(nullable NSError *)error;
/**
 *  Complete unregistration with success (error is nil) or failure with NSError with reason
 */
-(void)completeUnregistrationWithOptionalError:(nullable NSError*)error;

@end


#pragma mark TSAutenticatorMultiStepRegistration

/**
 *  currentStep dictionary fields
 */
extern NSString * _Nonnull const kRegistrationStepName; /**< Step name field in current step dictionary */
extern NSString * _Nonnull const kRegistrationStepInstructions; /**< User instructions text field in current step dictionary */
extern NSString * _Nonnull const kRegistrationStepImageName; /**< User image name in current step dictionary */

/*! \protocol TSAutenticatorMultiStepRegistration TSAuthenticatorAPI.h
 *  \brief Additional state management for multistep authenticators.
 *
 * Protocol for number of steps and current step in multistep authenticators.
 * Currently Face and Voice.
 */
@protocol TSAutenticatorMultiStepRegistration <TSAuthenticator>

@property (nonatomic, readonly) NSUInteger numberOfStepsIfAvailable; /**< Number of steps in registration */

@property (nonatomic, readonly, nullable) NSDictionary* currentStep; /**< Dictrionay holding name and user instructions for current registration step */

@end

/*! \protocol TSAuthenticatorMultiStepAuthentication TSAuthenticatorAPI.h
 *  \brief Additional state management for multistep authenticators.
 *
 * Protocol for restarting a multi step authentication session, unless locked.
 */
@protocol TSAuthenticatorMultiStepAuthentication <TSAuthenticator>

/**
 Restart an authentication attempt if the last one failed and the Authenticator
 has not been locked. This option is available only after failing to answer all
 of the challenges in the last set, and getting as a result an TS_ERR_AUTHENTICATOR_ERROR error code.
 
 @param block Callback block. Error is nil on success, otherwise contains the failure reason.
 */
-(void)restartFailedAuthenticationWithCompletion:(nullable void (^) (NSError* _Nullable error))block;

/**
 Authenticator state indicating if the authenticator requires a restart before next attempt to authenticate.
 */
@property (nonatomic, readonly) BOOL requiresRestart;

@end

#pragma mark - TSAuthenticatorBiometric
/*! \protocol TSAuthenticatorBiometric TSAuthenticatorAPI.h
 *  \brief Biometric Authenticator sub protocol.
 *
 * Exposes user hints for improved biometric data sampling.
 */
@protocol TSAuthenticatorBiometric <TSAuthenticator>

/**
 * User facing guidance message to improve sampling biometric information.
 * May refresh only after failed sampling.
 * Relevant error codes for failed sampling: TS_ERR_AUTHENTICATOR_SAMPLING_REPEAT, TS_ERR_SECRET_AGAIN.
 * Not part of live guidance in front of camera (See TSAuthenticatorCameraDetectionDelegate).
 */
-(nullable NSString*)userHint;

@end

#endif /* TSAuthenticatorAPI_h */


#pragma mark - TSAuthenticatorPlaceholder
/*! \protocol TSAuthenticatorPlaceholder TSAuthenticatorAPI.h
 *  \brief Authenticator additional properties API.
 *
 * TSAuthenticatorPlaceholder is an authenticator that is not implemented by the SDK.
 * It still being refered by the SDK as any of the known types of Authenticators, thus
 * it still possesses a type and name that define it name and symbols on full UI tables.
 */
@protocol TSAuthenticatorPlaceholder <TSAuthenticator>

/**
 *  Signed data object for placeholder session registration.
 *  If not nill, add this data to the server token request body:
 *  {
 *      "purpose”:  …
 *      “context_data”: “<placeholderData>"
 *  }
 *  @return placeholder data object
 */
@property (nonatomic, readonly, nonnull) id data;

/**
 * Placeholder configuration, any structure that contains data relevant for running the placeholder
 * in the application context. Not used by the SDK.
 */
@property (nonatomic, strong, nullable) id configuration;

/**
 *  Invoke placeholder authenticator for authentication
 */
-(void)invokeAuthentication;

/**
 *  Invoke placeholder authenticator for registration
 */
-(void)invokeRegistration;

/**
 *  Invoke placeholder authenticator for registration
 */
-(void)invokeUnregistration;

/**
 *  Return to policy from a placeholder authenticator call, provide token or error to complete the policy,
 *  or none of them to cancel placeholder and go back to last action in policy.
 *  When returning from registration/unregistration pass nil token and error.
 *
 *  @param token TSAuthToken received from client Server
 *  @param code  NSNumber with value of one of TransmitSDKErrors error codes to terminate the policy
 *  @param block Callback block with error on deliberate or unexpected failure, otherwise nil.
 */
-(void)resumeWithToken:(nonnull TSAuthToken*)token error:(nullable NSNumber*)code completion:(nullable void (^) (NSError* _Nullable error))block;

/**
 * Mark Authenticator as locked. Has no implications on SDK or TS server side, can be used
 * for application internal use.
 *  @param locked Is locked state
 *  @param num Number of retries left, optional.
 */
-(void)markLockState:(BOOL)locked retriesLeft:(nullable NSNumber*)num;

@end
