//
//  GenericView.h
//  TransmitSecurity
//
//  Created by Renana Alexandron on 9/11/14.
//  Copyright (c) 2014 TransmitSecurity. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TSUICustomizationPlugin.h"

@interface GenericView : UIView

+(instancetype)initWithCustomViewType:(TSCustomizedUIViewType)viewType withServicingVc:(UIViewController*)viewController;
+(instancetype)initWithCustomViewType:(TSCustomizedUIViewType)viewType ownedBy:(id)owner withServicingVc:(UIViewController*)viewController;
+(UIView*)viewWithCustomViewType:(TSCustomizedUIViewType)viewType owner:(id)owner context:(NSDictionary*)contextAttributes servicingVc:(UIViewController*)viewController;

-(void)setup;
-(void)nibDidLoad;

@end
