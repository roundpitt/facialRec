//
//  TSPolicyAPI.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 03/02/2016.
//  Copyright © 2016 TransmitSecurity. All rights reserved.
//

#ifndef TSPolicyAPI_h
#define TSPolicyAPI_h

#import "TSActionAPI.h"
#import "TSPolicyInfo.h"

@class TSPolicyManager;
@class TSAuthenticationRejectionInfo;

#pragma mark - Policy API

/**
 *  TSPolicy instance interface, holds a complete policy created
 *  by the policy manager. Commonly completing the policy returns
 *  is rewarded with Authentication Server Token.
 */
@interface TSPolicy : NSObject

/**
 *  Policy Request Id used to create policy
 */
@property (nonatomic, readonly, nullable) NSString* requestId;
/**
 *  Application params set on creation
 */
@property (nonatomic, readonly, nullable) NSDictionary* params;

/**
 *  Current action in policy
 */
@property (nonatomic, readonly, nullable) id<TSAction> currentAction;
/**
 *  Policy summary informative object
 */
@property (nonatomic, readonly, nonnull) TSPolicyInfo* info;

/**
 *  Unretained pointer to the owning manager
 */
@property (nonatomic, readonly, nullable) TSPolicyManager* manager;

/**
 *  Checks availablility of policy
 *
 *  @return Returns true if the policy have actions left to run, if no acions available or the policy have previously failed, returns false.
 */
-(BOOL)isComplete;

/**
 *  Reason for policy failure, when completed with error.
 */
@property (nonatomic, readonly, nullable) NSError* completionError;

/**
 *  When the policy has failed due to server deliberate rejection. A rejection data is available 
 *  for building an explanation screen for the user.
 */
@property (nonatomic, readonly, nullable) TSAuthenticationRejectionInfo* rejectionData;

/**
 Application bound failure data from a server side service provider.
 */
@property (nonatomic, readonly, nullable) NSString* serverSideServiceProviderFailureData;

@end

#pragma mark - Policy Classes
/**
 *  TSPolicyAuthenticate instance interface. Created by TSAuthenticationPolicyManager
 *  in authentication flows.
 */
@interface TSPolicyAuthenticate : TSPolicy
@end

/**
 *  TSPolicyRegistration instance interface. Created by TSRegistrationPolicyManager
 *  in configuration menu request, registration and unregistration flows.
 */
@interface TSPolicyRegistration : TSPolicy
@end

/**
 *  TSApprovalPolicy instance interface. Created by TSApprovalPolicyManager
 *  in authentication flows.
 */
@interface TSPolicyApproval : TSPolicy
@end


#pragma mark - Rejection Info
/**
 *  Rejection information class encapsulating data received from server about a session rejection.
 *  The data can be used to construct a rejection message for the user.
 */
@interface TSAuthenticationRejectionInfo : NSObject

/**
 *  Rejection message title
 */
@property (nonatomic, readonly, nullable) NSString* title;
/**
 *  Rejection message text
 */
@property (nonatomic, readonly, nullable) NSString* text;
/**
 *  Rejection user confirmation button text
 */
@property (nonatomic, readonly, nullable) NSString* buttonText;

@end

#endif /* TSPolicyAPI_h */
