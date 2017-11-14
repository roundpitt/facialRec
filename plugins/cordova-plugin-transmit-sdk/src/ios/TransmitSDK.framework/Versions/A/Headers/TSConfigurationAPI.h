//
//  TSConfigurationObjectProtocol.h
//  TransmitSDK
//
//  Created by Eran Berkovitz on 12/28/14.
//  Copyright (c) 2015 TransmitSecurity. All rights reserved.
//

#ifndef TSConfiguration_API_h
#define TSConfiguration_API_h
#import "TSDefs.h"

@class TSCustomRequestSerialization;
@class TSCustomResponseSerialization;
@protocol TSCollectorConfiguration;
@protocol TSAsynchActionDelegate;
@protocol TSLogger;
@protocol TSConnectionAuthenticationChallengeDelegate;

/**
 * \enum TSLogLevel Log level for Transmit SDK logs.
 * @file TSConfigurationAPI.h
 */
typedef enum : NSUInteger {
    TS_LOG_LEVEL_OFF        = 0,        /**< No logs */
    TS_LOG_LEVEL_CRITICAL   = 1 << 0,   /**< Critical logs only. May indicate software bugs. */
    TS_LOG_LEVEL_ERROR      = 1 << 1,   /**< Expected errors occured */
    TS_LOG_LEVEL_WARNING    = 1 << 2,   /**< Warnings about optional malfunctions in service */
    TS_LOG_LEVEL_INFO       = 1 << 3,   /**< Successful operations reported */
    TS_LOG_LEVEL_DEBUG      = 1 << 4,   /**< Extensive debug logs */
} TSLogLevel;

/**
 *  Transmit SDK configuration for client App
 */
@protocol TSConfigurationAPI <NSObject>
/**
 *  Authentication server address.
 */
@property (nonatomic, strong) NSString* authenticationServerURI;
/**
 *  License for face recognition API.
 */
@property (nonatomic, strong) NSString* faceRecognitionLicense;

/**
 *  License for eye verification API.
 */
@property (nonatomic, strong) NSString* eyeVerificationLicense;

/**
 *  Add or remove loggers additional loggers.
 */
@property (nonatomic, readonly) NSMutableArray< id<TSLogger> >* loggers;

/**
 *  Maximal SDK log level.
 */
@property (nonatomic, assign) TSLogLevel logLevel;
/**
 *  Client application ID.
 */
@property (nonatomic, strong) NSString* appID;
/**
 *  Device token used for push notifications. Should be set as soon as available in
 *  the AppDelegate application:didRegisterForRemoteNotificationsWithDeviceToken: call.
 */
@property (nonatomic, strong) NSData* deviceAppToken;
/**
 *  Response serializer. See description below.
 */
@property (nonatomic, strong) TSCustomRequestSerialization* customRequestSerializer;
/**
 *  Response serializer. See description below.
 */
@property (nonatomic, strong) TSCustomResponseSerialization* customResponseSerializer;
/**
 *  Configure SDK collectors.
 */
@property (nonatomic, strong) id<TSCollectorConfiguration> collectorConfiguration;
/**
 *  TransmitBlockingActionDelegate that is informed about future and ending of
 *  blocking SDK action. E.g. network call.
 */
@property (nonatomic, weak) id<TSAsynchActionDelegate> blockingActionDelegate;
/**
 *  Set custom number of PBKDF2 iterations in local registration key
 *  stretching algorithm. Default is 10000.
 */
@property (nonatomic, assign) unsigned int nPBKDF2Iterations;
/**
 *  Get expired and completed approvals in approvals list.
 */
@property (nonatomic, assign) BOOL showApprovalsHistory;

/**
 * Delegate for client authentication during SSL handshake.
 */
@property(nonatomic, weak) id<TSConnectionAuthenticationChallengeDelegate> clientAuthenticationDelegate;

@end

#pragma mark - Customized serialization
#pragma mark TSCustomResponseSerialization

/**
 *  Custom request serialization base class allows customization of outgoing
 *  SDK requests to the Authentication Server.
 *  Inherit from the class, override any of the API method.
 */
@interface TSCustomRequestSerialization : NSObject

/**
*  Customize NSURLRequest object created by the SDK.
*
*  @param request    NSURLRequest object created by the SDK
*  @param parameters Dictionary JSON object that comprises the request body
*  @param error      Fill in error that occurred while customizing the request
*
*  @return NSURLRequest object to send
*/
- (NSURLRequest *)requestBySerializingRequest:(NSURLRequest *)request
                                        withParameters:(id)parameters
                                                 error:(NSError * __autoreleasing *)error;
@end

#pragma mark TSCustomResponseSerialization

/**
 *  Custom response serialization base class allows customization of incoming
 *  Authentication Server responses to the SDK.
 *  Response serializers can decodes data into a more useful object representation, according to details in the server response.
 *  Response serializers may additionally perform validation on the incoming response and data.
 *  Inherit from the class, override any of the API method.
 */
@interface TSCustomResponseSerialization : NSObject
/**
 *  Create JSON dictionary object with Transmit Security Server response.
 *
 *  @param response NSURLResponse returned from server
 *  @param data     Data containing Transmit Security server response
 *  @param error    Error object reference to pass in case of failure
 *
 *  @return NSDictionary object with parsed response body
 */
- (NSDictionary*)responseObjectForResponse:(NSURLResponse *)response
                                      data:(NSData *)data
                                     error:(NSError *__autoreleasing *)error;
@end

#pragma mark Important Note
/**
 *  When using custom serialization of server response. Use the error's userInfo structure
 *  to keep a copy of the response body even when receiving an error response. 
 *  Otherwise, essential data will be lost and the process might fail.
 *
 \code{.m}
 - (id)responseObjectForResponse:(NSURLResponse *)response
                            data:(NSData *)data
                           error:(NSError *__autoreleasing *)error
 {
 ...
    NSHTTPURLResponse *httpResp = (NSHTTPURLResponse*) response;
    if (httpResp.statusCode >=400) {
        NSMutableDictionary *mutableUserInfo = [@{
                    NSLocalizedDescriptionKey: [NSString stringWithFormat:@"%@ (%ld)", [NSHTTPURLResponse localizedStringForStatusCode:httpResp.statusCode], (long)httpResp.statusCode],
                    NSURLErrorFailingURLErrorKey:[httpResp URL]
                    } mutableCopy];
 
    if (data) {
        mutableUserInfo[CustomResponseSerializationErrorDataKey] = data;
        if ([contentType rangeOfString:@"text/plain"].length > 0)
        {
            NSString* errorMessage = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            mutableUserInfo[NSLocalizedDescriptionKey] = errorMessage;
        }
    }
    *error = [NSError errorWithDomain:@"Application Custom Serializer" code:NSURLErrorBadServerResponse userInfo:mutableUserInfo];
 ...
 }
 \endcode
 */
extern NSString * const CustomResponseSerializationErrorDataKey; /**< Field to add server error in userInfo structure */

#pragma mark - TSConnectionAuthenticationChallengeDelegate

/*! \protocol TSConnectionAuthenticationChallengeDelegate TSConfigurationAPI.h
 *  \brief SSL handshake client certificate provier protocol
 *
 * Protocol a delegate object that can provide client certifiate for SSL handshake
 * client authentication challenge.
 */
@protocol TSConnectionAuthenticationChallengeDelegate <NSObject>

-(NSURLCredential*)clientCredential; /**< Delegate call for returning the client certificate in NSURLCredential object */

@end


#pragma mark - TSCollectorConfiguration
/*! \protocol TSCollectorConfiguration TSConfigurationAPI.h
 *  \brief Configure SDK collectors.
 *
 * Configure SDK collectors. By default, collectors are enabled.
 */
@protocol TSCollectorConfiguration <NSObject>
/**
 *  Disable Cloud Collector.
 *  When not disabled collects social network accounts, address book statistics
 *  and some device attributes.
 */
@property (nonatomic, assign) BOOL disableCloudCollector;
/**
 *  Disable Network Collector.
 *  When not disabled collects mobile connection details.
 */
@property (nonatomic, assign) BOOL disableNetworkCollector;
/**
 *  Disable Device Collector.
 *  When not disabled collects device hardware and OS details.
 */
@property (nonatomic, assign) BOOL disableDeviceCollector;
/**
 *  Disable Context Collector.
 *  When not disabled collects location and connectivity to other devices.
 */
@property (nonatomic, assign) BOOL disableContextCollector;

@end

#pragma mark - TSAsynchActionDelegate
/*! \protocol TSAsynchActionDelegate TSConfigurationAPI.h
 *  \brief Listen to long asynch actions.
 *
 *  Delegate protocol for informing about upcoming and ending of
 *  blocking SDK action. E.g. network call.
 */
@protocol TSAsynchActionDelegate <NSObject>
/**
 *  Informs delegate of upcoming asynch action.
 */
-(void)asynchActionWillBegin;
/**
 *  Informs delegate of blocking action end.
 */
-(void)asynchActionDidEnd;

@end

#pragma mark - TSLogger
/*! \protocol TSLogger TSConfigurationAPI.h
 *  \brief Add logger to SDK loggers.
 *
 * Logger protocol for adding a loger to SDK loggers.
 */
@protocol TSLogger <NSObject>

/**
 Logging delegate call.

 @param message Log message
 @param level SDK severity level
 */
-(void)log:(NSString*)message severity:(TSLogLevel)level;
@end

#endif
