//
//  TSUICustomizationPlugin.h
//  TransmitSDK
//
//  Created by Eldan Ben Haim on 25/03/2017.
//  Copyright © 2017 TransmitSecurity. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// View types

typedef const NSString * TSCustomizedUIViewType;

extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSAuthenticatorsMenuTableViewCell;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSAuthMenuViewController;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSEyeConfirmationView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSEyeScanView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSFaceInstructionsView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSFaceScanView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSOTPTargetTableCellView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSOTPChannelsViewController;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPinView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSImageSampleAcquisitionView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSVoicePassView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPasswordView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPatternView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSTitleInstructionsBaseViewController;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPopupViewCancel;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPopupViewAuthFallback;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPopupViewConfirmationAction;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPopupViewInformationAction;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPopupViewLocalHTMLConfirmation;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPopupViewMenu;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPopupViewRetry;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPopupViewSmallNote;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSPopupViewConfirmDeletion;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSTOtpDisplayViewController;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSUsernameView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeUserNameTableCellView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeUserChangeView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSProgressHUD;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSDevicesListView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSDeviceListCellView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSDeviceDetailsView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSDeviceDetailsTitleValueCellView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSDeviceDetailsRenameCellView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSDeviceDetailsActionView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSQuestionDetailsView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSQuestionTableView;
extern TSCustomizedUIViewType _Nonnull TSCustomizedUIViewTypeTSQuestionTableViewCell;




/*! \protocol TSUICustomization TSUICustomizationPlugin.h
 *  \brief Protocol for custom UI objects passed that replace native view types.
 *
 *  Conform to this protocol to load custom nibs or handle to UIView life cycle events.
 */
@protocol TSUICustomization <NSObject>

@optional

-(nonnull NSString*)customNibName;                              /**< return customized nib name to load */
-(nullable UIView*)loadCustomViewWithOwner:(nullable id)owner;  /**< load custom view, set optional owner */

-(void)viewDidLoad:(nonnull UIView*)loadedView;             /**< Handle viewDidLoad: life cycle event */
-(void)willMoveToWindow:(nullable UIWindow *)newWindow;     /**< Handle willMoveToWindow: life cycle event */
-(void)willMoveToSuperview:(nonnull UIView *)newSuperview;  /**< Handle willMoveToSuperview: life cycle event */
-(void)didMoveToWindow;                                     /**< Handle didMoveToWindow life cycle event */
-(void)didMoveToSuperview;                                  /**< Handle didMoveToSuperview life cycle event */
-(void)layoutSubviews;                                      /**< Handle layoutSubviews life cycle event */

@end

/*! \protocol TSUICustomizationPlugin TSUICustomizationPlugin.h
 *  \brief Protocol for customization plugin object that returns UI customization objects to TransmitSDK
 *
 *  Conform to this protocol to enable UI customization. Send customized UI objects to TransmitSDK.
 */
@protocol TSUICustomizationPlugin <NSObject>

@optional


/**
 Create and return UI customization objects to TransmitSDK to replace the native UI indicated by viewType.

 @param viewType Native UI view type
 @param uiViewOwner Optional view owner
 @param contextAttributes Optional dictionary with UI view context. E.g. UI view configuration or state parameters.
 @param viewController Optional view controller
 @return Customization object
 */
-(nullable id<TSUICustomization>)createCustomizationForViewType:(nonnull TSCustomizedUIViewType)viewType ownedBy:(nullable id)uiViewOwner inContext:(nullable NSDictionary*)contextAttributes withServicingViewController:(nullable UIViewController*)viewController;

@end
