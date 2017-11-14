//
//  TSUserDeviceAPI.h
//  TransmitSDK
//
//  Created by  InbarSletean on 28/03/2017.
//  Copyright © 2017 TransmitSecurity. All rights reserved.
//

#ifndef TSUserDeviceAPI_h
#define TSUserDeviceAPI_h

#import <CoreLocation/CoreLocation.h>
#import "TSDefs.h"

/**
 * \enum TSUserDeviceStatus device status.
 * @file TSUserDeviceAPI.h
 */
typedef enum : NSUInteger {
    STATUS_RECENTLY_USED, /**< Device was recently used */
    STATUS_NO_RECENT_ACTIVITY, /**< Device wasn't recently used */
    STATUS_LONG_INACTIVITY, /**< Device has been inactive for a long period of time */
    STATUS_DISABLED, /**< Device disabled and cannot be used for login etc */
    STATUS_REMOVED /**< Device has just been removed from service, need to login to re-add the device */
}TSUserDeviceStatus;

/*! \protocol TSUserDevice TSUserDeviceAPI.h
 *  \brief Protocol for secondary authentication approval Manager
 *
 * Protocol for a single approval data model
 */
@protocol TSUserDevice <NSObject>

@property (nonatomic, readonly) TSUserDeviceStatus status;                  /**< Status */
@property (nonatomic, strong, readonly) NSDate *lastAccess;                 /**< Last access time */
@property (nonatomic, readonly) CLLocationCoordinate2D lastAccessLocation;  /**< Last access location */
@property (nonatomic, strong, readonly) NSDate *registered;                 /**< Registration date */
@property (nonatomic, strong, readonly) NSString *deviceModel;              /**< Device model */
@property (nonatomic, strong, readonly) NSString *osType;                   /**< Device OS */
@property (nonatomic, strong, readonly) NSString *osVersion;                /**< OS version on last access */
@property (nonatomic, readonly) NSInteger useCount;                         /**< Usage count. How many times used to access TS service */
@property (nonatomic, readonly) Boolean supportsPush;                       /**< Does support push notifications */
@property (nonatomic, strong, readonly) NSString *name;                     /**< Auto-generated or given name */
@property (nonatomic, readonly) Boolean isCurrentDevice;                    /**< Is accessing device */

/**
 *  Remove device from devices available for access, removes device data on next access.
 *
 *  @param token      TSAPIToken struct
 *  @param block      Block with error object in case of failure, nil on success
 */
-(void) removeUserDevice:(TSAuthToken *)token withCompletion:(void (^) (NSError* error)) block;
/**
 *  Disable device. Reversable, usually transient.
 *
 *  @param token      TSAPIToken struct
 *  @param block      Block with error object in case of failure, nil on success
 */
-(void) disableUserDevice:(TSAuthToken *)token withCompletion:(void (^) (NSError* error)) block;
/**
 *  Enable a disabled device.
 *
 *  @param token      TSAPIToken struct
 *  @param block      Block with error object in case of failure, nil on success
 */
-(void) enableUserDevice:(TSAuthToken *)token withCompletion:(void (^) (NSError* error)) block;
/**
 *  Send push notification to device.
 *
 *  @param token      TSAPIToken struct
 *  @param block      Block with error object in case of failure, nil on success
 */
-(void) notifyUserDevice:(TSAuthToken *)token withCompletion:(void (^) (NSError* error)) block;
/**
 *  Update device name for UX purposes.
 *
 *  @param token      TSAPIToken struct
 *  @param name       Device name to set
 *  @param block      Block with error object in case of failure, nil on success
 */
-(void) updateUserDeviceName:(TSAuthToken *)token name:(NSString*)name withCompletion:(void (^) (NSError* error)) block;

@end

#pragma mark - TSUserDevicesManager

/*! \class TSUserDevicesManager TSUserDeviceAPI.h
 *  \brief Manages user device's flows.
 */
@interface TSUserDevicesManager : NSObject
/**
 *  Get list of user device objects
 *
 *  @param token      TSAPIToken struct
 *  @param block      Block with array of device objects, or error object in case of failure
 */
-(void)getUserDevices:(NSString *)token withCompletion:(void (^) (NSArray<id<TSUserDevice> >* devices, NSError* error))block;
@end

#endif /* TSUserDeviceAPI_h */
