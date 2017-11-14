//
//  TSImageSampleAcquisitionView.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 29/12/2016.
//  Copyright © 2016 TransmitSecurity. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GenericView.h"

@class TSImageSampleAcquisitionView;
@class ImageSamplerView;

@protocol TSImageSampleAcquisitionViewDelegate
-(void)imageSampleAcquisitionView:(TSImageSampleAcquisitionView*)sender collectedChallengeResponse:(NSData*)response;
-(void)imageSampleAcquisitionView:(TSImageSampleAcquisitionView*)sender finishedWithError:(NSError*)error;
@optional
-(void)imageSampleAcquisitionView:(ImageSamplerView*)view hintsChanged:(NSArray<NSString*> *)hints;
@end

@interface TSImageSampleAcquisitionView : GenericView

@property (weak, nonatomic) id<TSImageSampleAcquisitionViewDelegate> delegate;
@property (nonatomic) NSTimeInterval detectionTimeout;
@property BOOL showIndicators;
@property (nonatomic, weak) UIView* externalView;
@property NSString *localizedHintsContext;

-(void)setupAcquisitionChallengeFromJson:(NSDictionary*)challengeJson;
-(void)restartAfterWrongInput;

-(void)setupWithBrandingWithAuthenticator:(NSUInteger)type;

@end
