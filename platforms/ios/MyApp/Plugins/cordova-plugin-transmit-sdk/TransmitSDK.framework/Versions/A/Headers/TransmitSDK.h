//
//  TransmitSDK.h
//  TransmitSDK
//
//  Created by Eran Berkovitz on 11/12/14.
//  Copyright (c) 2015 TransmitSecurity. All rights reserved.
//

#ifndef TransmitSDK_TransmitSDK_h
#define TransmitSDK_TransmitSDK_h

/**
 *  \mainpage
 *  In oredr to use the graphical classes of this framework, <b>TransmitSecurityResources.bundle</b> (which resides in the TransmitSDK.framework) <b>MUST</b> be added to the project.
 *  In addition (though this should happen implicitly), its important to make sure that <b>TransmitSecurityResources.bundle</b> has been added to the
 *  <b>"Copy Bundle Resources"</b> phase in the project's settings <b>"Build Phases"</b>.
 *  In case the above isn't respected, an runtime exception will be raised.
 *
 *  In order to localize (or customize) the texts deployed by this framework, please refer to the comment at the head of the <b>en.lproj/Localizable.strings</b>
 *  file in <b>TransmitSecurityResources.bundle</b>.
 *
 *  In order to customize (brand) UI resources (as in PNGs), resources with the same file names should be placed in the app main bundle.
 *
 *  For more details refer to "getting started" guide.
 */

#import "TSConfigurationAPI.h"
#import "TransmitSDK_API.h"
#import "TSPolicyManagers.h"
#import "TSUserDeviceAPI.h"
#import "TransmitSDKErrors.h"
#import "TSApprovalAPI.h"
#import "TSPolicyAPI.h"
#import "TSActionAPI.h"
#import "TSPolicyInfo.h"
#import "TSAuthenticatorAPI.h"

#endif
