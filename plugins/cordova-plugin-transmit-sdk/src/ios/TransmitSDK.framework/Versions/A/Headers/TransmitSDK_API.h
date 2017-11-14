//
//  TransmitSDK.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 8/18/14.
//  Copyright (c) 2015 TransmitSecurity. All rights reserved.
//

#ifndef TransmitSDK_API_h
#define TransmitSDK_API_h

#import "TSConfigurationAPI.h"
#import "TSPolicyManagers.h"
#import "TSTOtpGenerator.h"
#import "TSUserDeviceAPI.h"

#pragma mark - User Data

/**
 User data object.
 */
@interface TSUserData : NSObject
@property (nonatomic, readonly, nonnull) NSString*  username; /**< User Identifier */
-(nonnull NSString*)maskedUsername; /**< masked User Identifier with customized algorithm */
@end

#pragma mark - TransmitSDK

/**
 *  SDK singleton access objects
 */
@interface TransmitSDK : NSObject

/**
 *  Create and get TransmitSDK instance
 *
 *  @return TransmitSDK instance
 */
+(nonnull instancetype)sharedInstance;

/**
 * SDK version
 */
-(nonnull NSString*)version;

#pragma mark User Management

/**
 *  Current user Id
 *
 *  @return User Id
 */
-(nullable NSString*)userId;

/**
 *  Current user in SDK.
 *
 *  @return TSUserData object for current user
 */
-(nullable TSUserData*)currentUser;
/**
 *  Last logged user which is NOT current user, if any.
 *
 *  @return TSUserData object for last logged user or nil if only a single user is known
 */
-(nullable TSUserData*)lastLoggedUser;

/**
 *  List of all users that completed a login (authenticated) with the SDK, including current user if did log before.
 *
 *  @return Array of TSUserData objects for all users that did successful login.
 */
-(nullable NSArray<TSUserData*>*)allLoggedUsers;

/**
 *  Connect to server
 *
 *  @param token      TSAPIToken struct
 *  @param block      Block with error object in case of failure, nil on success
 */
-(void)connectWithAPIToken:(nonnull NSDictionary *)token callback:(nullable void (^)( NSError* __nullable error))block;

/**
 *  Logout from server, revoke token, additional resources to revoke/free should be passed through params.
 *  On success, error is nil, otherwise error specified.
 *
 *  @param username Username  
 *  @param token Transmit SP token to invalidate.
 *  @param params Application paramaters with server side resources to free or revoke
 *  @param callback      Return code of the action
 */
-(void)logout:(nonnull NSString*)username token:(nullable TSAuthToken*)token params:(nullable NSDictionary*)params completion:(nullable void (^) (NSError* __nullable error)) callback;

/**
 *  Check device registration status
 *
 *  @param username Username *
 *  @return TRUE if user was registered with current device, otherwise FALSE
 */
-(BOOL)isDeviceRegisteredForUser:(nonnull NSString*)username;

/**
 *  Base64 encoded data, which is required in generation of Authentication Server token for device
 *  registration in server to server request. See registerDeviceForUser:token:callback: for device
 *  registration request API.
 *  Add this data to the token request body:
 *  {
 *      “context_data”: “<registerDeviceContextData>"
 *      “purpose”: “reg"
 *  }
 *  @return String with data for token generation request.
 */
-(nonnull NSString*)registerDeviceContextData;

/**
 *  Register current device for user
 *  On success, error is nil, otherwise error specified.
 *
 *  @param username Username *  @param token The token received at the end of the authentication process or from server to server request
 *  @param block      Return code of the action
 */
-(void)registerDeviceForUser:(nonnull NSString*)username token:(nonnull TSAuthToken*)token callback:(nullable void (^) (NSError* __nullable error))block;

/**
 *  A central configuration interface
 */
@property (nonatomic, readonly, nonnull) id<TSConfigurationAPI> configuration;

/**
 *  Server reachability status
 */
@property (nonatomic, readonly, getter=isServerReachable) BOOL serverReachability;

/**
 *  Clear all user data and enrolments. For demo purpose only
 *
 *  @param completionBlock completion status callback block
 */
-(void)clearCurrentUserData:(nullable void (^) (NSError* __nullable error))completionBlock;

/**
 *  Clear all user data and enrolments for all users. For demo purpose only
 *
 *  @param completionBlock completion status callback block
 */
-(void)clearAllUsers:(nullable void (^)(NSError* __nullable error)) completionBlock;

/**
 * Lets Transmit SDK do it's part in shutting down functionality when going to background
 */
-(void) applicationWillResignActive;


/**
 * Obtain a TOTP generator for user
 *
 * @param username User for which TOTP should be generated
 * @param ttl      TTL for generated TOTP. Must match policy definition.
 * @param digits   Digits for generated TOTP. Must match policy definition.
 * @param prompt   Prompt for user for obtaining access to shared secret for TOTP
 * @param completion Completion routine for delivering the generator
 */
-(void)totpGeneratorForUser:(nonnull NSString*)username ttl:(int)ttl digits:(int)digits
                prompt:(nonnull NSString*)prompt
                completion:(nonnull void (^)(TSTOtpGenerator* __nullable gen, NSError* __nullable err))completion;

#pragma mark - Policy managers

/**
 *  Generate policy manager for authentication flows
 *
 *  @param username Username
 *  @param delegate          Policy manager delegate
 *
 *  @return Authentication Policy Manager Class or nil if no username could be assigned
 */
-(nullable TSAuthenticationPolicyManager*)authenticationManagerForUser:(nullable NSString*)username delegate:(nullable id<TSPolicyManagerDelegate>)delegate;

/**
 *  Generate settings menu policy manager
 *
 *  @param username Username
 *  @param delegate          Policy manager delegate
 *
 *  @return Registration Policy Manager Class or nil if no username could be assigned
 */
-(nullable TSRegistrationPolicyManager*)registrationManagerForUser:(nullable NSString*)username delegate:(nullable id<TSPolicyManagerDelegate>) delegate;

/**
 *  Generate mobile second authentication approval policy manager
 *
 *  @param username Username
 *  @param delegate          Policy manager delegate
 *
 *  @return Approval Policy Manager Class or nil if no username could be assigned
 */
-(nullable TSApprovalPolicyManager*)approvalManagerForUser:(nullable NSString *)username delegate:(nullable id<TSPolicyManagerDelegate>)delegate;

/**
 *  Generate user devices manager
 *
 *  @return User Devices Manager Class
 */
-(nonnull TSUserDevicesManager*)userDevicesManager;
@end

#endif
