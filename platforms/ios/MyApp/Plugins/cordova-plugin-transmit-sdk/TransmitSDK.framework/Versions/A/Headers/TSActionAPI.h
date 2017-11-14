//
//  TSActionAPI.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 04/01/2016.
//  Copyright © 2016 TransmitSecurity. All rights reserved.
//

#ifndef TSActionAPI_h
#define TSActionAPI_h

#import "TSAuthenticatorAPI.h"

#pragma mark - Action API

/**
 * \enum TSActionClass Action types Enumeration
 * @file TSActionAPI.h
 */
typedef enum : NSUInteger {
    TS_ACTION_INFORMATION,      /**< Information screen with "OK" button */
    TS_ACTION_CONFIRMATION,     /**< Confirmation screen with "OK" and "Cancel" buttons */
    TS_ACTION_AUTH_MENU,        /**< Authenticators Menu for authentication */
    TS_ACTION_REJECT,           /**< Information screen that leads to policy termination with reject error */
    TS_ACTION_USER_NAME,         /**< Screen to enter user. Available only in full UI implementation. */
    TS_ACTION_JSON_DATA,
} TSActionClass;

@class TSPolicy;

/** @defgroup TSActionAPI Actions
 * @{*/

#pragma mark - Action API

/*! \protocol TSAction TSActionAPI.h
 *  \brief Generic action API.
 *
 * Common protocol to all Action classes. Comfort properties reveal the class type.
 */
@protocol TSAction <NSObject>
/**
 *  Action class enumeration value
 */
@property (nonatomic, readonly) TSActionClass actionClass;

/**
 *  Action name in string
 */
@property (nonatomic, readonly) NSString* name;

/**
 *  Unretained pointer to the owning policy
 */
@property (nonatomic, weak) TSPolicy* policy;

/**
 *  Complete any action with success (error is nil) or failure with NSError with reason
 *  If there are still actions or assertions remaining, the policy will exit with error TS_ERR_AUTH_USER_OPTED_OUT.
 */
-(void)completeActionWithOptionalError:(NSError*)error;

@end

#pragma mark Information Action
/*! \protocol TSActionInformation TSActionAPI.h
 *  \brief Information Action Class Protocol.
 *
 * Protocl to information action. Assert user's information consumption.
 */
@protocol TSActionInformation <TSAction>
/**
 *  Assert Information consumed by user.
 *
 *  @param block Callback block with error if assertion failed.
 */
-(void) assertUserContinuedWithCompletion:(void (^) (NSError* error))block;
@end

#pragma mark Reject Action
/*! \protocol TSActionReject TSActionAPI.h
 *  \brief Reject Action Class Protocol.
 *
 * Protocl to rejection action. Rejects the user.
 */
@protocol TSActionReject <TSAction>
/**
 *  Assert Information consumed by user.
 *
 *  @param block Callback block with error if assertion failed.
 */
-(void) assertUserContinuedWithCompletion:(void (^) (NSError* error))block;
@end

#pragma mark Confirmation Action
/*! \protocol TSActionConfirmation TSActionAPI.h
 *  \brief Confirmation Action Class Protocol.
 *
 * Protocl to confirmation action. Assert user's confirmation choice.
 */
@protocol TSActionConfirmation <TSAction>
/**
 *  Assert confirmation choice made by user.
 *
 *  @param positiveChoice Boolean value for positive (TRUE) or negative choice.
 *  @param block Callback block with error if assertion failed.
 */
-(void)assertUserContinuedWith:(BOOL)positiveChoice completion:(void (^) (NSError* error))block;
@end

#pragma mark JSON Action
/*! \protocol TSActionJSONData TSActionAPI.h
 *  \brief JSON data Action Class Protocol.
 *
 * Protocl to JSON action. An action hold information destined to the application.
 * See TSPolicyManagerDelegate's policyManager:policy:handleJSONData: for more information.

 */
@protocol TSActionJSONData <TSAction>
/**
 JSON object.
 */
@property (nonatomic, strong, readonly) NSDictionary* json;
@end


#pragma mark Authenticators Menu
/*! \protocol TSActionAuthenticatorsMenu TSActionAPI.h
 *  \brief TSActionAuthenticatorsMenu protocol.
 *
 * Authenticators Menu Action protocol. Allows access to
 * TSAuthenticators objects.
 */
@protocol TSActionAuthenticatorsMenu <TSAction>

/**
 *  List all available authenticators in action.
 */
@property (nonatomic, readonly, strong) NSArray< id<TSAuthenticator> >* authenticators;

/**
 *  Sublist of authenticators that comprised of registered authenticators.
 */
@property (nonatomic, readonly) NSArray< id<TSAuthenticator> >* registeredAuthenticators;

/**
 Sublist of registered Authenticators that are not locked.
 */
@property (nonatomic, readonly) NSArray< id<TSAuthenticator> >* validAuthenticators;

/**
 *  Sublist of authenticators that comprised of unregistered authenticators.
 */
@property (nonatomic, readonly, strong) NSArray< id<TSAuthenticator> >* unregisteredAuthenticators;

/**
 * Returns Yes if action belongs to authentication policy, otherwise NO.
 */
-(BOOL)canAuthenticate;

/**
 *  Check if authenticator is available in action.
 *
 *  @param authenticator TSAuthenticatorType enumeration value
 *
 *  @return TRUE if authetnicator is available, otherwise FALSE
 */
-(BOOL)hasAuthenticator:(TSAuthenticatorType) authenticator;

/**
 *  Return Authenticator object if exists in authenticators list. Otherwise returns nil.
 *
 *  @param authenticatorId Authenticator identifier
 *
 *  @return TSAuthenticator of requested type, or nil.
 */
-(id<TSAuthenticator>)getAuthenticatorById:(NSString*)authenticatorId;

@end

/** @}*/

#endif /* TSActionAPI_h */
