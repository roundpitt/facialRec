#import "TransmitSDKCordovaPlugin.h"
#import <TransmitSDK/TransmitSDK+UI.h>

#define TS_PLUGIN_ARG_SERVER_URI @"uri"
#define TS_PLUGIN_ARG_SERVER_PORT @"port"
#define TS_PLUGIN_ARG_SERVER_IS_SECURE @"is_secure"

#define TS_PLUGIN_ARG_API_TOKEN_NAME @"api_token_name"
#define TS_PLUGIN_ARG_API_TOKEN @"api_token"

#define TS_PLUGIN_ARG_USERNAME @"username"
#define TS_PLUGIN_ARG_REQUEST_ID @"request_id"
#define TS_PLUGIN_ARG_TOKEN @"token"
#define TS_PLUGIN_ARG_REQUEST_PARAMS @"request_params"
#define TS_PLUGIN_ARG_FORCE_MENU @"force_menu"

NSString* DICT_STRING(id string) {
    if (string) return string;
    return @"";
};

@interface TransmitSDKCordovaPlugin () <TSPolicyManagerDelegate, TSChangeUserFlowDelegate>


@property NSLock *initializationLock;
@property BOOL initialized;

@property TSPolicyManager *runningPolicyManager;
@property UIViewController* runningVC;
@property id<TSAuthenticator> runningPlaceholderAuth;
@property CDVInvokedUrlCommand *command;

@property (nonatomic, strong) NSString* currentUser;


-(void)endCommandWithError:(NSError *)err andPolicy:(TSPolicy*)policy;

@end


@implementation TransmitSDKCordovaPlugin

-(void)pluginInitialize
{
    NSLog(@"Initalizing the TransmitSDK instance");
    
    _initializationLock = [[NSLock alloc] init];
    [_initializationLock lock];
    _initialized = NO;
    
    TransmitSDK* tsSDK = [TransmitSDK sharedInstance];
    tsSDK.configuration.collectorConfiguration.disableCloudCollector = TRUE;
    tsSDK.configuration.collectorConfiguration.disableContextCollector = TRUE;
    tsSDK.configuration.logLevel = TS_LOG_LEVEL_DEBUG;
    
    [_initializationLock unlock];
}

-(void)version:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                             messageAsString:[TransmitSDK sharedInstance].version] callbackId:[command callbackId]];
}

-(void)initSDK:(CDVInvokedUrlCommand*)command
{
    _command = command;
    TransmitSDK* tssdk = [TransmitSDK sharedInstance];
    
    // URI
    NSDictionary* connectionDetails = [command argumentAtIndex:0];
    NSString* urlPrefix = [connectionDetails[TS_PLUGIN_ARG_SERVER_IS_SECURE] boolValue] ? @"https" : @"http";
    NSString* url = [NSString stringWithFormat:@"%@:%@", connectionDetails[TS_PLUGIN_ARG_SERVER_URI], connectionDetails[TS_PLUGIN_ARG_SERVER_PORT]];
    tssdk.configuration.authenticationServerURI = [NSString stringWithFormat:@"%@://%@", urlPrefix, url];
    
    // API Token
    NSDictionary* apiToken = [command argumentAtIndex:1];
    NSString* tokenName = apiToken[TS_PLUGIN_ARG_API_TOKEN_NAME];
    NSString* tokenValue = apiToken[TS_PLUGIN_ARG_API_TOKEN];
    
    NSDictionary* apiTokenDict = @{
                                   kTSAPIToken : DICT_STRING(tokenValue),
                                   kTSAPITokenName : DICT_STRING(tokenName)
                                   };
    // App ID
    tssdk.configuration.appID = [command argumentAtIndex:2];
    
    // Connect
    TransmitSDKCordovaPlugin* __weak weakSelf = self;
    [tssdk connectWithAPIToken:apiTokenDict
                      callback:^(NSError* error) {
                          dispatch_async(dispatch_get_main_queue(), ^{
                              if (error)
                              {
                                  NSLog(@"Failed to connect to Transmit Security server, authentication service not available: %@", error.debugDescription);
                                  [weakSelf endCommandWithError:error andPolicy:nil];
                                  
                              } else
                              {
                                  _initialized = YES;
                                  [weakSelf endCommand:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                                     messageAsDictionary:@{ @"result": @"success"}]];
                                  
                              }
                          });
                      }];
}

- (void)ensureInitialized
{
    BOOL locked = [_initializationLock lockBeforeDate:[NSDate dateWithTimeIntervalSinceNow:10]];
    BOOL ret = _initialized;
    if(locked)
    {
        [_initializationLock unlock];
    }
    
    if(!ret)
    {
        [NSException raise:NSGenericException format:@"Could not initialize TransmitSDK cordova plugin."];
    }
}

-(void)expirePluginState:(CDVInvokedUrlCommand*)command
{
    // Starting a command is a good time to ensure we're initialized.
    [self ensureInitialized];
    [self endRunningUI];

    if (_command)
    {
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT] callbackId:[_command callbackId]];
    }
    
    _command = nil;
}

-(void)setLocationCollection:(CDVInvokedUrlCommand*)command
{
    [self beginCommand:command];
    NSNumber *enabled = [command argumentAtIndex:0];
    [TransmitSDK sharedInstance].configuration.collectorConfiguration.disableContextCollector = (! [enabled boolValue]);
    [self endCommand:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK]];
}

- (void)resumeFromPlaceholder:(CDVInvokedUrlCommand*)command
{
    [self beginCommand:command];
    
    NSString *token = [command argumentAtIndex:0];
    
    [(id<TSAuthenticatorPlaceholder>)self.runningPlaceholderAuth resumeWithToken:token error:nil completion:^(NSError *error) {
        if(error)
        {
            if (TS_ERR_AUTH_USER_OPTED_OUT == error.code)
            {
                [self resumeRunningUI];
                return;
            }
            [self endCommandWithError:error andPolicy:nil];
        }
        else
        {
            self.runningPlaceholderAuth = nil;
            UIViewController<TSPolicyUIContainer>* vc = self.runningPolicyManager.containerViewController;
            if (vc)
                [self showTSViewController:vc];
        }
    }];
}

- (void)authenticate:(CDVInvokedUrlCommand*)command
{
    [self beginCommand:command];
    
    // Analyze arguments
    NSDictionary* arguments = nil;
    NSString *username = self.currentUser;
    if ([command arguments] > 0)
    {
        arguments = [command argumentAtIndex:0];
    }
    
    if ([arguments objectForKey:TS_PLUGIN_ARG_USERNAME])
        username = arguments[TS_PLUGIN_ARG_USERNAME];
    
    if ([arguments objectForKey:TS_PLUGIN_ARG_TOKEN])
        NSLog(@"'token' has no effect for authentication");
    
    BOOL forceMenu = arguments[TS_PLUGIN_ARG_FORCE_MENU] ? [arguments[TS_PLUGIN_ARG_FORCE_MENU] boolValue] : NO;
    
    NSLog(@"Going to login with username %@", username);
    
    TSAuthenticationPolicyManager *policyManager = (TSAuthenticationPolicyManager*)[[TransmitSDK sharedInstance] authenticationManagerForUser:username delegate:self];
    self.runningPolicyManager = policyManager;
    
    [policyManager authenticate:arguments[TS_PLUGIN_ARG_REQUEST_ID]
                     withParams:arguments[TS_PLUGIN_ARG_REQUEST_PARAMS]
                     completion:^(TSPolicy* policy, NSError* error) {
                         //                      if(error)
                         //                      {
                         //                          // This command may have actually ended in error by the delegate
                         //                          if(self.command)
                         //                          {
                         //                              [self endCommandWithError:error.localizedDescription andPolicy:nil];
                         //                          }
                         //                          return;
                         //                      }
                         
                         
                         if (policy == nil)
                         {
                             NSLog(@"No control flow received. Wait for completion call");
                             return;
                         }
                         
                         UIViewController<TSPolicyUIContainer>* vc = policyManager.containerViewController;
                         vc.showAuthenticationOptions = forceMenu;
                         [self showTSViewController:vc];
                     }];
}


- (void)configure:(CDVInvokedUrlCommand*)command
{
    [self beginCommand:command];
    
    // Analyze arguments
    
    NSDictionary* arguments = nil;
    NSString *username = self.currentUser;
    if ([command arguments] > 0)
    {
        arguments = [command argumentAtIndex:0];
    }
    
    // Analyze arguments
    if ([arguments objectForKey:TS_PLUGIN_ARG_USERNAME])
        username = arguments[TS_PLUGIN_ARG_USERNAME];
    
    TSAuthToken* token = nil;
    if ([arguments objectForKey:TS_PLUGIN_ARG_TOKEN])
        token = arguments[TS_PLUGIN_ARG_TOKEN];
    
    
    TSRegistrationPolicyManager *policyManager = (TSRegistrationPolicyManager*)[[TransmitSDK sharedInstance] registrationManagerForUser:self.currentUser delegate:self];
    
    self.runningPolicyManager = policyManager;
    
    [policyManager registrationMenuWithParams:arguments[TS_PLUGIN_ARG_REQUEST_PARAMS] token:token completion:^(TSPolicy* policy, NSError* error) {
        if(error)
        {
            // This command may have actually ended in error by the delegate
            if(self.command)
            {
                [self endCommandWithError:error andPolicy:nil];
            }
            return;
        }
        
        if (policy == nil)
        {
            NSLog(@"No control flow received. Wait for completion call");
            return;
        }
        
        [self showTSViewController:policyManager.containerViewController];
    }];
}

-(void)logout:(CDVInvokedUrlCommand*)command
{
    [self beginCommand:command];
    
    // Analyze arguments
    NSDictionary* arguments = nil;
    NSString *username = self.currentUser;
    if ([command arguments] > 0)
    {
        arguments = [command argumentAtIndex:0];
    }
    
    // Analyze arguments
    if ([arguments objectForKey:TS_PLUGIN_ARG_USERNAME])
        username = arguments[TS_PLUGIN_ARG_USERNAME];
    
    TSAuthToken* token = nil;
    if ([arguments objectForKey:TS_PLUGIN_ARG_TOKEN])
        token = arguments[TS_PLUGIN_ARG_TOKEN];
    
    TransmitSDKCordovaPlugin* __weak weakSelf = self;
    [[TransmitSDK sharedInstance] logout:self.currentUser token:token params:nil completion:^(NSError *error) {
        
        if (error)
        {
            [weakSelf endCommandWithError:error andPolicy:nil];
            return;
        }
        
        [self endCommand:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                       messageAsDictionary:@{ @"result": @"success"}]];
        
        weakSelf.currentUser = nil;
        //        weakSelf.lastAuthenticatedUser = nil;
    }];
}


-(void)manageUsers:(CDVInvokedUrlCommand*)command
{
    [self beginCommand:command];
    [self showTSViewController:[[TransmitSDK sharedInstance] changeUserFlowWithDelegate:self]];
}

-(void)currentUsername:(CDVInvokedUrlCommand*)command
{
    [self beginCommand:command];
    [self endCommand:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                       messageAsString: DICT_STRING( [TransmitSDK sharedInstance].userId) ]];
}

-(void)lastLoggedUsername:(CDVInvokedUrlCommand*)command
{
    [self beginCommand:command];
    [self endCommand:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                       messageAsString:DICT_STRING( [TransmitSDK sharedInstance].lastLoggedUser.username) ]];
}

-(void)listLastLoggedUsernames:(CDVInvokedUrlCommand*)command
{
    [self beginCommand:command];
    NSArray<TSUserData*>* users = [TransmitSDK sharedInstance].allLoggedUsers;
    NSMutableArray* array = [[NSMutableArray alloc] initWithCapacity:[users count]];
    for (TSUserData* user in users)
    {
        [array addObject:user.username];
    }
    [self endCommand:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                        messageAsArray:array ]];
}

-(void)clearAll:(CDVInvokedUrlCommand*)command
{
    [self beginCommand:command];
    [[TransmitSDK sharedInstance] clearAllUsers:^(NSError* error) {
        
        if (error)
        {
            [self endCommandWithError:error andPolicy:nil];
            return;
        }
        [self endCommand:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK]];
    }];
}

#pragma mark Running policy management

-(void)showTSViewController:(UIViewController*)vc
{
    self.runningVC = vc;
    
    [self.viewController addChildViewController:self.runningVC];
    [self.viewController.view addSubview:self.runningVC.view];
    [self.runningVC didMoveToParentViewController:self.viewController];
    [self setHorizontalPinsBetweenSubview:self.runningVC.view andContainerView:self.viewController.view options:0 leftPadding:0.0 rightPadding:0.0];
    [self setVerticalPinsBetweenSubview:self.runningVC.view andContainerView:self.viewController.view options:0 topPadding:0.0 bottomPadding:0.0];
}

-(void)setHorizontalPinsBetweenSubview:(UIView*)subView andContainerView:(UIView*)view options:(NSLayoutFormatOptions)options leftPadding:(CGFloat)leftP rightPadding:(CGFloat)rightP
{
    
    @try {
        subView.translatesAutoresizingMaskIntoConstraints = NO;
        
        NSDictionary *viewsDictionary = NSDictionaryOfVariableBindings(subView);
        NSDictionary* metrics = @{ @"leftPadding": @(leftP), @"rightPadding": @(rightP)};
        NSArray *horizontalConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|-leftPadding-[subView]-rightPadding-|" options:options metrics:metrics views:viewsDictionary];
        [view addConstraints:horizontalConstraints];
    } @catch (NSException *exception) {
        NSLog(@"%@", exception.debugDescription);
    }
}

-(void)setVerticalPinsBetweenSubview:(UIView*)subView andContainerView:(UIView*)view options:(NSLayoutFormatOptions)options topPadding:(CGFloat)topP bottomPadding:(CGFloat)bottomP
{
    @try {
        subView.translatesAutoresizingMaskIntoConstraints = NO;
        
        NSDictionary *viewsDictionary = NSDictionaryOfVariableBindings(subView);
        NSDictionary* metrics = @{ @"topPadding": @(topP), @"bottomPadding": @(bottomP)};
        NSArray *verticalConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|-topPadding-[subView]-bottomPadding-|" options:options metrics:metrics views:viewsDictionary];
        [view addConstraints:verticalConstraints];
    } @catch (NSException *exception) {
        NSLog(@"%@", exception.debugDescription);
    }
}

-(void)suspendRunningUI
{
    [self.runningVC.view removeFromSuperview];
    [self.runningVC removeFromParentViewController];
    
}

-(void)resumeRunningUI
{
    [self.viewController.view addSubview:self.runningVC.view];
    [self.viewController addChildViewController:self.runningVC];
    [self.runningVC didMoveToParentViewController:self.viewController];
}

-(void)endRunningUI
{
    [self suspendRunningUI];
    
    self.runningVC = nil;
    self.runningPolicyManager = nil;
    self.runningPlaceholderAuth = nil;
}

#pragma mark Command stack management

-(void)beginCommand:(CDVInvokedUrlCommand*)command
{
    // Starting a command is a good time to ensure we're initialized.
    [self ensureInitialized];
    
    // One day this will have to be replaced with a stack of commands.
    if(_command)
    {
        [NSException raise:NSGenericException format:@"Attempt to issue a cordova command <%@> to the TransmitSDK while another one is executing.", command];
    }
    
    _command = command;
}


-(void)endCommand:(CDVPluginResult*)result
{
    if(!_command)
    {
        [NSException raise:NSGenericException format:@"Attempt to end a command with result <%@> while no command is in progress.", result];
    }
    
    [self.commandDelegate sendPluginResult:result callbackId:[_command callbackId]];
    
    _command = nil;
}

-(void)endCommandWithError:(NSError *)err andPolicy:(TSPolicy*)policy
{
    NSMutableDictionary* errDict = [NSMutableDictionary dictionaryWithDictionary:@{@"code" : [NSNumber numberWithLong:err.code],
                                                                                   @"message" : err.localizedDescription,
                                                                                   }];
    
    if (nil != policy && nil != policy.serverSideServiceProviderFailureData) {
        errDict[@"serviceProviderFailureData"] = policy.serverSideServiceProviderFailureData;
    }
    
    CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:errDict];
    [self endCommand:result];
}

-(void)endCommandWithCancelation
{
    NSDictionary* errDict = @{@"code" : @(TS_ERR_AUTH_USER_OPTED_OUT),
                              @"message" : NSLocalizedString(@"Canceled", nil),
                              };
    
    CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:errDict];
    [self endCommand:result];
}


#pragma mark Policy manager delegate

-(void)policyManager:(TSPolicyManager*)manager policy:(TSPolicy*)policy failedWithError:(NSError*)error
{
    switch(error.code)
    {
            // handle session expiration
        case TS_ERR_USER_NOT_AUTHENTICATED:
        case TS_ERR_POLICY_INVALID:
            break;
        default:
            break;
    }
    
    [self endRunningUI];
    [self endCommandWithError:error andPolicy:policy];
}

-(void)policyManager:(TSPolicyManager*)manager policy:(TSPolicy*)policy completeWithToken:(TSAuthToken*)token pendingApprovals:(BOOL)hasPendingApprovals
{
    if ([policy isKindOfClass:[TSPolicyRegistration class]])
        return;
    
    [self endRunningUI];
    
    NSMutableDictionary* dict = [NSMutableDictionary dictionaryWithObjectsAndKeys:@"success", @"result", nil];
    if (token)
        dict[@"token"] = token;
    CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                            messageAsDictionary:dict];
    [self endCommand:result];
    
    if([manager isKindOfClass:[TSAuthenticationPolicyManager class]])
    {
        //        self.lastAuthenticatedUser = manager.username;
        self.currentUser = manager.username;
    }
}

-(void)policyManager:(TSPolicyManager*)manager policy:(TSPolicy*)policy performAuthentication:(id<TSAuthenticator>)authenticator
{
    [self suspendRunningUI];
    
    self.runningPlaceholderAuth = authenticator;
    
    CDVPluginResult* result = [CDVPluginResult
                               resultWithStatus:CDVCommandStatus_OK
                               messageAsDictionary:@{ @"result": @"placeholder",
                                                      @"data": ((id<TSAuthenticatorPlaceholder>)authenticator).data,
                                                      @"purpose": @"pld",
                                                      @"type": authenticator.name }];
    [self endCommand:result];
}

-(void)validateUsername:(NSString *)username forPolicyManager:(TSPolicyManager *)manager setErrorIfFailed:(NSError *__autoreleasing *)error
{
    [self validateNewUsername:username setErrorIfFailed:error];
    
}

#pragma mark - TSChangeUserFlowDelegate

-(void)completed:(UIViewController*)vc withSelectedUser:(TSUserData*)userData
{
    [self endRunningUI];
    self.currentUser = userData.username;
    [self endCommand:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                       messageAsString: userData.username ]];
}

-(void)changeUserCanceled:(UIViewController*)vc
{
    [self endRunningUI];
    [self endCommandWithCancelation];
}

-(void)validateNewUsername:(NSString*)username setErrorIfFailed:(NSError**)error
{
    NSString *trimmedString = username;
    NSCharacterSet *trim = [NSCharacterSet characterSetWithCharactersInString:@"!@#$%^&*()[]_ "];
    trimmedString = [[trimmedString componentsSeparatedByCharactersInSet:trim] componentsJoinedByString:@""];
    if (trimmedString.length != username.length)
    {
        *error = [NSError errorWithDomain:@"TSCordovaPlugin" code:-1 userInfo:@{
                                                                                NSLocalizedDescriptionKey : @"User name failed validation"
                                                                                }];
    }
}

@end
