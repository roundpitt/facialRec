//
//  TSDefs.h
//  TransmitSDK
//
//  Created by Avihai Apatoff on 03/04/2017.
//  Copyright © 2017 TransmitSecurity. All rights reserved.
//

#ifndef tsdefs_h
#define tsdefs_h
#import <Foundation/Foundation.h>

typedef NSString TSAuthToken; /**< Transmit Security Authentication Server token */

/**
 * Types & keys to server as arguments for Login (-connectWithAPIToken:callback:)
 */
typedef NSDictionary TSAPIToken;
extern NSString * const kTSAPITokenName; /**< Token name field for connecting SDK to server */
extern NSString * const kTSAPIToken;     /**< Token value field for connecting SDK to server */

#endif /* tsdefs_h */
