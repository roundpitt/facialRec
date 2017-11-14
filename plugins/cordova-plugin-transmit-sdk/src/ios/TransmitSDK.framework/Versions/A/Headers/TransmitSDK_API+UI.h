//
//  TransmitSDK+UI.h
//  TransmitSDK
//
//  Created by Eran Berkovitz on 1/11/15.
//  Copyright (c) 2015 TransmitSecurity. All rights reserved.
//

#ifndef TransmitSDK_API_UI_h
#define TransmitSDK_API_UI_h

#import <UIKit/UIKit.h>
#import "TransmitSDK_API.h"
#import "TSUICustomizationPlugin.h"

/*! \protocol TransmitSDKUIDelegate TransmitSDK+UI.h
 *  \brief Base UI handling delegate.
 *
 * Protocol for handling TransmitSDK provided UIViewControllers with the exception of TSPolicyUIContainer.
 */
@protocol TransmitSDKUIDelegate <NSObject>
@optional
/**
 The user has instructed dismissing the view controller.

 @param tsVC View controller to dismiss
 */
-(void)dismissTSViewController:(nonnull UIViewController*)tsVC;

@end


/*! \protocol TSChangeUserFlowDelegate TransmitSDK+UI.h
 *  \brief Common authenticator API.
 *
 * Protocol for TSChangeUserFlowViewController delegate
 */
@protocol TSChangeUserFlowDelegate <TransmitSDKUIDelegate>

/**
 Get user data of the current user from the user management UI.
 @param vc View controller for changing user object with user name
 @param userData TSUserData object with user name
 */
-(void)completed:(nonnull UIViewController*)vc withSelectedUser:(nullable TSUserData*)userData;

/**
 User canceled "change user" process.
 */
-(void)changeUserCanceled:(nonnull UIViewController*)vc;

@optional
/**
 *  Delegate method to validate a new user name entered by the user. Provided error
 *  will be presented to the user.
 *
 *  @param username User name provided by the user
 *  @param error Create an error object and assign to this pointer in case of failed validation.
 */
-(void)validateNewUsername:(nonnull NSString*)username setErrorIfFailed:(NSError* __nullable * __nullable)error;

@end


/**
 View controller protocol for change user flow
 */
@protocol TSChangeUserFlowViewController <NSObject>

/** message to new user on change user flow
Default text: "NOTICE: the entered username will be stored for future usage."
Set nil to remove instructions bar
*/
@property (nonatomic, strong, nullable) NSString* usernameFormNotice;

@end

/*! \protocol TSDeviceManagementDelegate TransmitSDK+UI.h
 *  \brief Device Management UI Delegate.
 *
 * Protocol for Device Management UI delegate.
 */
@protocol TSDeviceManagementDelegate <TransmitSDKUIDelegate>
/**
 *  Delegate method to handle error return from Device Management View Controller
 *
 *  @param deviceManagmentViewController Device Management View Controller delegate method caller.
 *  @param error Error returned during Device Management activity.
 */
-(void) onFetchDevicesError:(nonnull UIViewController*) deviceManagmentViewController error:(nullable NSError*)error;

@end

/**
 View controller protocol for device management
 */
@protocol TSDeviceManagementViewController <NSObject>

/** message to user on devices list view
 Default text: "These are the devices you’ve used to log into our applications. Click on a device for more information and options."
 Set nil to remove instructions bar
 */
@property (nullable, nonatomic, strong) NSString* devicesFormNotice;

@end

/**
 *  API to fetch Transmit SDK view controllers
 */
@interface TransmitSDK (UI)

/**
 UI for user name change by choosing from list of known users.
 Allows entering a new user as well.

 @param delegate Delegate to recieve completion callback
 @return UIViewcontroller object to present to the user
 */
-(nonnull UIViewController<TSChangeUserFlowViewController>*)changeUserFlowWithDelegate:(nullable id<TSChangeUserFlowDelegate>)delegate;

/**
 UI for device management by choosing device from a list of user's devices
 
 
 @param delegate Delegate to recieve completion callback
 @param token   Previously acquired token
 @return UIViewcontroller object to present to the user
 */
-(nonnull UIViewController<TSDeviceManagementViewController>*)deviceManagementWithDelegate:(nullable id<TSDeviceManagementDelegate>)delegate token:(nonnull TSAuthToken*) token;

/**
 * 
 * Return a view controller for showing a TOTP for a user.
 *
 * @param username User for whom TOTP should be generated
 * @param ttl TTL for TOTP
 * @param digits Number of digits in TOTP
 * @param prompt Prompt for obtaining TOTP
 * @param delegate Optional generic TransmitSDK UI delegate
 */
-(nonnull UIViewController*)totpViewControllerForUser:(nonnull NSString*)username ttl:(int)ttl digits:(int)digits
                                       prompt:(nonnull NSString*)prompt delegate:(nullable id<TransmitSDKUIDelegate>)delegate;


/**
 *
 * Connect a UI customization plugin to the SDK.
 *
 * @param plugin A UI customization plugin; this is an object implementing the TSUICustomizationPlugin protocol.
 */
-(void)setUiCustomizationPlugin:(nonnull id<TSUICustomizationPlugin>)plugin;

@end

#endif
