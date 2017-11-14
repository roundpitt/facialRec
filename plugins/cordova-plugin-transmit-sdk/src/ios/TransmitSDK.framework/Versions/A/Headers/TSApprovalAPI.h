//
//  TSApprovalsAPI.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 24/02/2016.
//  Copyright © 2016 TransmitSecurity. All rights reserved.
//

#ifndef TSApprovalsAPI_h
#define TSApprovalsAPI_h

#import <Foundation/Foundation.h> 

/**
 * \enum TSApprovalStatus Status of approval (OOB request).
 * @file TSApprovalAPI.h
 */
typedef enum : NSUInteger {
    TS_APPROVAL_PENDING,    /**< Pending user's confirmation */
    TS_APPROVAL_APPROVED,   /**< Approved */
    TS_APPROVAL_DENIED,     /**< Denied */
    TS_APPROVAL_EXPIRED,    /**< Request expired */
} TSApprovalStatus;

/*! \protocol TSApproval TSApprovalAPI.h
 *  \brief Protocol for secondary authentication approval Manager
 *
 * Protocol for a single approval data model
 */
@protocol TSApproval <NSObject>
/** Approval Identifier */
@property (nonatomic, readonly, nonnull) NSString* approvalId;
/** Remote source that created the approval */
@property (nonatomic, readonly, nullable) NSString* source;
/** Approval title for the user */
@property (nonatomic, readonly, nullable) NSString* title;
/** Approval text for the user */
@property (nonatomic, readonly, nullable) NSString* details;
/** Creation time */
@property (nonatomic, readonly, nullable) NSDate* creationTime;
/** Completion time */
@property (nonatomic, readonly, nullable) NSDate* finishTime;
/** Expiry time */
@property (nonatomic, readonly, nullable) NSDate* expiresAt;
/** Approval status from TSApprovalStatus options */
@property (nonatomic, assign)           TSApprovalStatus status;
/** Did expire */
-(BOOL)isExpired;

@end


#endif /* TSApprovalsAPI_h */
