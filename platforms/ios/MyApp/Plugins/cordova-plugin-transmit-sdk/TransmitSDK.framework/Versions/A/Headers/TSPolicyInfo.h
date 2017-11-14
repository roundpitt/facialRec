//
//  TSPolicyInfo.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 31/12/2015.
//  Copyright © 2015 TransmitSecurity. All rights reserved.
//

#ifndef TSPolicyInfo_h
#define TSPolicyInfo_h

#import "TSActionAPI.h"

/**
 *  Informative object with single authenticator state.
 */
@interface TSAuthenticatorInfo : NSObject
/**
 *  Authenticator type.
 */
@property (nonatomic, readonly) TSAuthenticatorType type;
/**
 *  True if the authenticator is a placeholder, otherwide false.
 */
@property (nonatomic, readonly) BOOL placeholder;
/**
 * Authenticator lock state.
 */
@property (nonatomic, readonly) BOOL isLocked;
/**
 * Authenticator registration state. Authenticator without registration is marked registered (TRUE).
 */
@property (nonatomic, readonly) BOOL isRegistered;
/**
 *  Is the authenticator expired and requires a registration.
 */
@property (nonatomic, readonly) BOOL expired;
@end

/**
 *  Informative object with single action.
 */
@interface TSActionInfo : NSObject
/**
 *  Action type.
 */
@property (nonatomic, readonly) TSActionClass type;
@end

/**
 *  Informative object with single authenticator menu action (either for authentication or for registration).
 */
@interface TSAuthenticatorsMenuInfo : TSActionInfo
/**
 *  List of authenticators available in the menu.
 */
@property (nonatomic, strong, readonly) NSArray<TSAuthenticatorInfo*>* authenticators;
@end

/**
 *  Informative object with policy.
 */
@interface TSPolicyInfo : NSObject
/**
 *  List of actions available in the policy.
 */
@property (nonatomic, strong, readonly) NSArray<TSActionInfo*>* actions;
@end

#endif /* TSPolicyInfo_h */

