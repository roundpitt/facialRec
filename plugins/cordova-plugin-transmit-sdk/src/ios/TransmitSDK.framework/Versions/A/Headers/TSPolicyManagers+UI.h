//
//  TSPolicyManagers+UI.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 19/04/2016.
//  Copyright © 2016 TransmitSecurity. All rights reserved.
//

#ifndef TSPolicyManagerAPI_UI_h
#define TSPolicyManagerAPI_UI_h

#import "TSPolicyManagers.h"
#import <UIKit/UIKit.h>

@protocol TSPolicyUIContainer;

#pragma mark - Policy Manager Base Class UI category
/*! \category TSPolicyManager(TSPolicyManagerUI) TSPolicyManagers+UI.h
 *  \brief Policy Manager UI category.
 *
 * Policy Manager access to policy UI container. Use it to present TSAction native UI.
 */
@interface TSPolicyManager(TSPolicyManagerUI)

/**
 * Container for manager policies. Retained.
 */
@property (nonatomic, strong, nullable) UIViewController<TSPolicyUIContainer>* containerViewController;

@end

#pragma mark - Action View Controller
/*! \protocol TSPolicyUIContainer TSPolicyManagers+UI.h
 *  \brief POlicy Container View Controller
 *
 * Protocl for control flow container view controllers to conform
 */
@protocol TSPolicyUIContainer <NSObject>
/**
 *  Add action view controller as a subview controller and show its view
 *
 *  @param vc View controller to add to hierarchy
 */
-(void) setSubviewController:(nonnull UIViewController*) vc;
/**
 *  Remove action view controller subview controller and remove its view
 *
 *  @param vc View controller to remove from hierarchy
 */
-(void) removeSubviewController:(nonnull UIViewController*) vc;

/**
 Set view controller transition animation options wrapped in a NSNumber.
 Recommended animation style: @(UIViewAnimationOptionTransitionCrossDissolve | UIViewAnimationOptionLayoutSubviews)
 Default: UIViewAnimationOptionTransitionNone
 */
@property (nonatomic, strong, nullable) NSNumber* animationOptions;

/**
 Set view controller transition animation duration.
 Default: 0.2 (seconds)
 */
@property (nonatomic, assign) NSTimeInterval animationDuration;

@optional
/**
 *  A set of accessor to modify authenticators menus that may appear in the container
 */

/**
 * When set, the authenticationm view (if presented) will display this text in its
 * description label (mainly used to explain why (or the usage) is the authentication view displayed (e.g. in an approval flow),
 * confirmation flow);
 */
@property (nonatomic, strong, nullable) NSString* descriptionCaptionForAuthentication;

/**
 *  Show only registered methods on authentication menu
 */
@property (nonatomic, assign) BOOL showOnlyRegisteredAuthenticators;
/**
 *  In authentication, ignore known last used authenticator and show the collection of available authenticators.
 */
@property (nonatomic, assign) BOOL showAuthenticationOptions;
@end

#endif /* TSPolicyManagerAPI_UI_h */
