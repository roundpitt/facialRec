//
//  TSPolicyManagers.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 8/18/15.
//  Copyright (c) 2015 TransmitSecurity. All rights reserved.
//

#ifndef TransmitSDK_TSPolicyManagers_h
#define TransmitSDK_TSPolicyManagers_h

#import "TSPolicyAPI.h"
#import "TSApprovalAPI.h"

@class TSPolicyManager;

/** @defgroup PolicyManagers Policy Managers
 * @{*/

#pragma mark - Policy Manager Delegate
/*! \protocol TSPolicyManagerDelegate TSPolicyManagers.h
 *  \brief Policy Managers Delegate.
 *
 * Protocol for policy managers delegate. Classes that use policy manager should conform to this protocol.
 */
@protocol TSPolicyManagerDelegate <NSObject>
/**
 *  Handle general failures such as networking problems.
 *
 *  @param manager The calling policy manager
 *  @param policy The policy that failed
 *  @param error         Error object with failure reason string
 */
-(void)policyManager:(nullable TSPolicyManager*)manager policy:(nullable TSPolicy*)policy failedWithError:(nonnull NSError*)error;

@optional
/**
 *  Handle completion of policy with success.
 *
 *  @param manager The calling policy manager
 *  @param policy The policy that completed
 *  @param token User's authentication token when the policy includes user authentication
 *  @param hasPendingApprovals Flag marking if there are pending approvals awaiting the user
 */
-(void)policyManager:(nonnull TSPolicyManager*)manager policy:(nonnull TSPolicy*)policy completeWithToken:(nullable TSAuthToken*)token pendingApprovals:(BOOL)hasPendingApprovals;

/**
 *  Handle next action in control flow instead of the action UI being
 *  sent automatically to the containerViewController.
 *
 *  @param manager The calling policy manager
 *  @param policy The policy owning the action
 *  @param action Action class
 */
-(void)policyManager:(nonnull TSPolicyManager*)manager policy:(nonnull TSPolicy*)policy nextActionToRun:(nonnull id<TSAction>)action;

/**
 *  The user has chosen an external (placeholder) authentication method. The application is
 *  expected to handle the authentication process.
 *  The evaluation of the current policy is terminated and none of the other delegate methods
 *  will be called, thus this will be the last time the delegate is called, regarding the current flow.
 *
 *  @param manager The calling policy manager
 *  @param policy The policy owning the authenticator
 *  @param authenticator TSAuthenticator
 */
-(void)policyManager:(nonnull TSPolicyManager*)manager policy:(nonnull TSPolicy*)policy performAuthentication:(nonnull id<TSAuthenticator>)authenticator;

/**
 *  The user has chosen an external (placeholder) authenticator for configuration. The application
 *  is expected to handle the configuration process.
 *  The evaluation of the current policy is terminated and none of the other delegate methods
 *   will be called, thus this will be the last time the delegate is called, regarding the current flow.
 *
 *  @param manager The calling policy manager
 *  @param policy The policy owning the authenticator
 *  @param authenticator TSAuthenticator
 */
-(void)policyManager:(nonnull TSPolicyManager*)manager policy:(nonnull TSPolicy *)policy performRegistration:(nonnull id<TSAuthenticator>)authenticator;

/**
 *  The user has chosen an external (placeholder) authenticator for configuration. The application
 *  is expected to handle the configuration process.
 *  The evaluation of the current policy is terminated and none of the other delegate methods
 *   will be called, thus this will be the last time the delegate is called, regarding the current flow.
 *
 *  @param manager The calling policy manager
 *  @param policy The policy owning the authenticator
 *  @param authenticator TSAuthenticator
 */
-(void)policyManager:(nonnull TSPolicyManager*)manager policy:(nonnull TSPolicy *)policy performUnregistration:(nonnull id<TSAuthenticator>)authenticator;

/**
 *  Hook method to validate a new user name entered by the user in SDK provided UI.
 *  Any error provided here will be available at the 'policyManager:policy:failedWithError:' delegate callback.
 *  When not implementing this hook. The SDK fails the validation when the username is empty with TS_ERR_USER_DEVICE_UNKNOWN
 *  error code.
 *
 *  @param username User name provided by the user
 *  @param manager The calling policy manager
 *  @param error Create an error object and assign to this pointer in case of failed validation.
 */
-(void)validateUsername:(nonnull NSString*)username forPolicyManager:(nonnull TSPolicyManager*)manager setErrorIfFailed:(NSError * _Nonnull * _Nullable)error;

/**
 Delegate call that requests a handler to process application bound JSON data. 
 The handler is being run synchoneously, and once done, the policy completes or progresses to next action.

 @param manager The calling policy manager
 @param policy The policy owning the authenticator
 @param json the JSON data.
 */
-(void)policyManager:(nonnull TSPolicyManager*)manager policy:(nonnull TSPolicy *)policy jsonData:(nonnull NSDictionary*)json;

@end



#pragma mark - Policy Manager Base Class
/*! \class TSPolicyManager TSPolicyManagers.h
 *  \brief Policy Manager Base Class
 *
 * Policy Manager Base class with common API
 */
@interface TSPolicyManager : NSObject

/**
 Weak pointer to delegate.
 */
@property (nonatomic, weak, readonly, nullable) id<TSPolicyManagerDelegate> delegate;

/**
 A message that appears on new user form UI. This new user UI may
 appear on UI SDK flavors if the policy manager was started without
 a username value.
 Default text: "NOTICE: the entered username will be stored for future usage."
 Set nil to remove instructions bar
 */
@property (nonatomic, strong, nullable) NSString* usernameFormNotice;

/**
 User name entered on Policy Manager creation or by the user in Full UI
 */
@property (nonatomic, readonly, nonnull) NSString* username;


/**
 Checks whether an error received from the SDK is a terminal error, i.e. ends currend SDK UI flow and returns control to the application.

 @param error Error containing TransmitSDKErrors error code
 @return Is the error code is SDK UI flow terminating.
 */
+(BOOL)isTerminalError:(nullable NSError*)error;


@end

#pragma mark - Policy Managers

/**
 *  @relates TSRegistrationPolicyManager
 *  @relates TSAuthenticationPolicyManager
 *
 *  @param authenticators       List of TSAuthenticator objects with configurable authenticators
 *  @param policy               Policy. Needed for placeholder API and in multiple action flows.
 *  @param error                NSError with failure reason or nil for success
 */
typedef void(^authenticators_menu_callback)(NSArray<id<TSAuthenticator>>* _Nullable authenticators, TSPolicy* _Nullable policy, NSError* _Nullable error) DEPRECATED_MSG_ATTRIBUTE("Deprecated in v2.13");

#pragma mark TSAuthenticationPolicyManager
/*! \class TSAuthenticationPolicyManager TSPolicyManagers.h
 *  \brief Authentication Menu Policy Manager
 */
@interface TSAuthenticationPolicyManager : TSPolicyManager

/**
 *  List policy authenticators, provide full authentication policy, or return just an error object in case of failure.
 *
 *  @param requestId Policy Request Id. Policy Id in the Authentication Server side App. Nil for default policy.
 *  @param params  Application parameters to set context of policy
 *  @param block   Authentication policy. Failures are reported in delegate method `policyManager:failedWithError:` and in the callback error object.
 */
-(void)authenticate:(nullable NSString*)requestId withParams:(nullable  NSDictionary*)params completion:(nullable void (^) (TSPolicy* _Nullable policy, NSError* _Nullable error))block;

//! @cond Doxygen_Suppress

/**
 *  List policy authenticators, provide full authentication policy, or return just an error object in case of failure.
 *
 *  @param requestId Policy Request Id. Policy Id in the Authentication Server side App. Nil for default policy.
 *  @param params  Application parameters to set context of policy
 *  @param token   Previously acquired token (optional)
 *  @param block   Authentication policy. Failures are reported in delegate method `policyManager:failedWithError:` and in the callback error object.
 */
-(void)authenticate:(nullable NSString*)requestId withParams:(nullable NSDictionary*)params token:(nullable TSAuthToken*)token completion:(nullable authenticators_menu_callback)block DEPRECATED_MSG_ATTRIBUTE("Deprecated in v2.13, use authenticate:withParams:completion: instead");

/**
 *  Old API. Same as authenticate:withParams:token:completion: call with nil requestId.
 */
-(void)authenticationMenuWithParams:(nullable NSDictionary*)params token:(nullable TSAuthToken*)token completion:(nullable authenticators_menu_callback)block DEPRECATED_MSG_ATTRIBUTE("Deprecated in v2.11, use authenticate:withParams:token:completion: instead");

//! @endcond

@end

#pragma mark TSRegistrationPolicyManager

/*! \class TSRegistrationPolicyManager TSPolicyManagers.h
 *  \brief Registration Menu Policy Manager
 *
 * Extends Policy Manager with access to Registration Menu
 */
@interface TSRegistrationPolicyManager : TSPolicyManager

/**
 *  Base64 encoded data, which is required in generation of Authentication Server token 
 *  for authenticator configuration (==settings).
 *  Add this data to the token request body:
 *  {
 *      “context_data”: “<configurationMenuContextData>"
 *      “purpose”: “cfg"
 *  }
 *  @return String with data for token generation request.
 */
-(nonnull NSString*)configurationMenuContextData;


/**
 *  List configurable authenticators.
 *
 *  @param params Application paramaters to set context of policy
 *  @param token  Previously acquired token (mandatory)
 *  @param block Settings menu policy. Failures are reported in delegate method `policyManager:failedWithError:` and in the callback error object.
 */
-(void)registrationMenuWithParams:(nullable NSDictionary*)params token:(nullable TSAuthToken*)token completion:(nullable void (^) (TSPolicy* _Nullable policy, NSError* _Nullable error))block;

//! @cond Doxygen_Suppress
/**
 *  List configurable authenticators.
 *
 *  @param params Application paramaters to set context of policy
 *  @param token  Previously acquired token (mandatory)
 *  @param block Settings menu policy. Failures are reported in delegate method `policyManager:failedWithError:` and in the callback error object.
 */
-(void)configurationMenuWithParams:(nullable NSDictionary*)params token:(nullable TSAuthToken*)token completion:(nullable authenticators_menu_callback)block DEPRECATED_MSG_ATTRIBUTE("Deprecated in v2.13, use registrationMenuWithParams:token:completion: instead");
//! @endcond

@end


#pragma mark TSApprovalPolicyManager

/*! \class TSApprovalPolicyManager TSPolicyManagers.h
 *  \brief Protocol for secondary authentication approval Manager
 *
 * Policy and Approvals Manager for  class for mobile second authentication
 */
@interface TSApprovalPolicyManager : TSPolicyManager


/**
 * Get all approvals.
 *
 *  @param block Completion block. NSError provided on failure.
 *  Completion block parameters:
 *  - approvals: An array of sorted approvals. First come pending approvals sorted by date, then the rest by date.
 *  - didChange: Reporst TRUE if the list of approvals has changed since the last request.
 *  - error: NSError object with reason on failure.
 */
-(void)getApprovalsWithCompletion:(nullable void (^) (NSArray<id<TSApproval> >* _Nullable approvals, BOOL didChange, NSError* _Nullable error))block;

/**
 *  Request policy for approving an approval. If no policy required and no errors occur, the approval will be approved,
 *  and both returned policy and error will be nil.
 *
 *  @param approvalId approval Id
 *  @param params Application paramaters to set context of policy
 *  @param block Callback block with either new policy or error if failed.  Both nil on automatic success.
 */
-(void)approve:(nonnull NSString*)approvalId params:(nullable NSDictionary*)params completion:(nullable void (^)(TSPolicyApproval* _Nullable policy, NSError* _Nullable error))block;

/**
 *  Request policy for declining an approval. If no policy required and no errors occur, the approval will be declined,
 *  and both returned policy and error will be nil.
 *
 *  @param approvalId approval Id
 *  @param params Application paramaters to set context of policy
 *  @param block Callback block with either new policy or error if failed. Both nil on automatic success.
 */
-(void)decline:(nonnull NSString*)approvalId params:(nullable NSDictionary*)params completion:(nullable void (^)(TSPolicyApproval* _Nullable policy, NSError* _Nullable error))block;

@end

/** @}*/

#endif
