*Date:* Sep 2017

*Version:* 2.15

Cordova Transmit Security SDK
=============================
Cordova plugin for integrating the Transmit Security SDK. Supports iOS and Android.

## Installation

The plugin is, currently, not distributed through a repository, thus it resides locally on the developrs file system.

	cordova plugin add <path to plugin location>/cordova-plugin-transmit-sdk

### Installing with Cordova 7.0.1+

Plugin installation mechanism has changed in cordova release 7.0.1. The flag '--nofetch' is now required when adding the plugin.

    cordova plugin add <path to plugin location>/cordova-plugin-transmit-sdk --nofetch

### Specific platform notes

#### Android

In order to allow the plugin usage of the actaul SDK artifacts the following steps should be taken:

- Save the SDK bundle (uncompressed) at some location on the file system (which will serve as a "local" maven repository.
- Add the following property to the `gradle.properties` file (which usually resides at `~/.gradle/`):
	
	`local_ts_repo_path = <full path to transmit SDK containing folder>`
	
##### External biometric authenticators

The SDK supports integration with "external" biometric authenticators (for more details refer to the android SDK integration guide).
This may be done by adding a dependency specifiaction at the `transmit-security.gradle` file which resides under the plugin's `src/android` folder (this may require re-adding the plugin into the project).

**IMPORTANT**: On OS Marashmallow (6.0) and above permissions are required to use the microphone (voice) and camera (face and eye). The hosting application is responsible for handling the required permissions.

###### EyeVerify

In orfder to support eyeprint verification (by EyeVerify) add the following to the dependencies section:

```
dependencies {
	...
    compile('com.eyeverify:srvc-ifc:3.2@aar') {
        transitive = true
    }
   ...
}
```

###### Cognitec Face Recognition

In order to support face recognition by Cognitec add add the following to the dependencies section:

```
dependencies {
	...
    compile('com.cognitec:sdk:9.1.4@aar') {
        transitive = true
    }
   ...
}
```

###### Transmit Security Face Recognition Engine

In order to support face recognition by the Transmit Security engine add the following to the dependencies section:

```
dependencies {
    ...
    compile ('com.ts.common:zannah-android:1.5@aar') {
        transitive=true
    }
    ...
}
```
## Usage

This plugin registers a `transmitsdk` globally. All exported properties and methods may be accessed in the from of `transmitsdk.some_property`.

For any specific details regarding functionality and behavior, refer to the relevant documents for the SDK (Android or iOS).

## Arguments

Some of the arguments expected by the SDK methods are in a form of "simple" objects while others are in form of composite objects.
In order to ease the usage the following properties is provided:

	transmitsdk.argNames

The following sections provide documentation regarding the SDK operations which demonstrate the usage of the `argNames`.

	/**
	 * Argument keys to ease construction of expected object in API calls
	 */
	argNames = {
	    // connection details
	    ARG_SERVER_URI : "uri",
	    ARG_SERVER_PORT : "port",
	    ARG_SERVER_IS_SECURE : "is_secure",
	
	    // API token
	    ARG_API_TOKEN_NAME : "api_token_name",
	    ARG_API_TOKEN : "api_token",
	
	    // authentication related
	    ARG_USERNAME : "username",
	    ARG_REQUEST_ID : "request_id",
	    ARG_TOKEN : "token",
	    ARG_REQUEST_PARAMS : "request_params",
	    ARG_FORCE_MENU : "force_menu"
	
	}

## SDK Initialization

The SDK should be initialized only once in an application lifecycle (any further initializations will have no effect).

	/**
	 * Initializes the SDK.
	 * @param connectionDetails A JSON object composed of 3 fields defined in {@link exports#arguments}: ARG_SERVER_URI, ARG_SERVER_PORT, ARG_SERVER_IS_SECURE.
	 * @param apiToken A JSON object composed of 2 fields defined in {@link exports#arguments}: ARG_API_TOKEN_NAME, ARG_API_TOKEN.
	 * @param appId The application name as defined in the Authentication Control Server.
	 */
	initSDK = function(connectionDetails, apiToken, appId, success, error)

Initialization may be done in the following manner:

    var connectionDetails = {};
    connectionDetails[transmitSDK.argNames.ARG_SERVER_URI] = "http://<TS server uri>";
    connectionDetails[transmitSDK.argNames.ARG_SERVER_PORT] = 80;
    connectionDetails[transmitSDK.argNames.ARG_SERVER_IS_SECURE] = false;

    var apiToken = {};
    apiToken[transmitSDK.argNames.ARG_API_TOKEN_NAME] = "<TS_API_TOKEN_NAME>";
    apiToken[transmitSDK.argNames.ARG_API_TOKEN] = "<TS_API_TOKEN">;

    transmitSDK.initSDK(connectionDetails, apiToken, "mobile_app",
                        function() { console.log("SDK init success");
                            ...
                            // do some SDK stuff
                            ...
                        },
                        function(error) { console.error("SDK init failed: " + error.code)});

## Authentication

	/**
	 * @param arguments A JSON object composed of any of the following optional fields defined in {@link exports#arguments}: 
	 * ARG_USERNAME, ARG_REQUEST_ID, ARG_REQUEST_PARAMS, ARG_FORCE_MENU. 
	 * In case username isn't provided the last logged user (or the one recived from then UI) is used.
	 *
	 * The success callback should expect a string argument, holding the authentication token.
	 */
	authenticate = function(arguments, success, error)

Invocation of the authentication UI may be performed in the following manner:

    var authArguments = {};
    //authArguments[transmitSDK.argNames.ARG_USERNAME] = "<TS_USERNAME>";
    //authArguments[transmitSDK.argNames.ARG_REQUEST_ID] = "<POLICY_NAME>";

    transmitSDK.authenticate(authArguments,
                             function(result) {
                                 alert("Login succesful");
                                 // You're logged in                                                   
                             },
                             function(error) {
                                 alert("Authentication failed: " + error.code)
                             }
                         );

## Placeholder authenticator

In case a "placeholder" authenticator is defined by the policy, a placeholder callback should be set as follows:

	transmitSDK.setPlaceholderCallback(placeholderCallback);
	
Where `placeholderCallback` should access the app backend server and produce an appropriate token (uaully by requesting it from the TS server).

An example for this callback implementation may be:

    invokePlaceholder : function(context, purpose, type, completionCallback) {
        alert("Invoking placeholder: " + type);
        console.log("context: " + context);
        console.log("purpose: " + purpose);
        
        document.all('continueButton').style.display = "block";
                
        document.all('continueButton').onclick = function() {
            HTTP.setHeader("Authorization", "TSToken <token>; tid=<token name>");
            
            HTTP.postJson(app.getPlaceholderTokenURI(),
                                 { context_data: context, "purpose": purpose },
                                 { },
                                 function(response) {
                                 try {
                                 jsonResponse = JSON.parse(response.data);
                                 document.all('continueButton').style.display="none";
                                 completionCallback({ token: jsonResponse.data.token })
                                 }
                                 catch (e) {
                                 alert("Failed to parse reponse: " + e.message);
                                 }
                                 },
                                 function(response) {
                                 alert("Token request failed: " + response.error);
                                 });
        };

## Authenticators registration

	/**
	 * @param arguments A JSON object composed of 2 of the following optional fields defined in {@link exports#argNames}: 
	 * ARG_USERNAME, ARG_TOKEN. 
	 * The token is relevant only in cases where registration is perfromed with no authentication preceding (e.g. fetching a configuration token from the app backend server by requesting it from the TS server).
	 * In case username isn't provided the last logged user (or the one recived from then UI) is used.
	 */
	configure = function(arguments, success, error)

Invocation of the configuration (registration) UI may be performed in the following manner:

        var args = {};
        //args[transmitSDK.argNames.ARG_TOKEN] = "...";

        transmitSDK.configure(args,
                            function() { alert("Enrollment succesful"); },
                            function(error) {
                                if (error.code == transmitSDK.errors.TS_ERR_CANCELED) {
                                    alert("Enrollment canceled/done");
                                }
                                else { 
                                    alert("Enrollment failure: " + error.code); 
                                } 
                            });

## Users management

	/**
	 * Invokes the users management UI. Success callback should expect a string argument holding the selected username.
	 */
	manageUsers = function(success, error)

Invocation of the users management UI may be performed in the following manner:

	/**
	 * Invokes the users management UI. Success callback should expect a string argument holding the selected username.
	 */
	manageUsers = function(success, error)
	
## Manipulating location services requirement

/**
 * Enables/disables location collection by the SDK. Default is disabled.
 * (On Android, the calling application is responsible for handling permissions, the SDK will follow according to the permissions settings.
 *  Thus, this methos always reports success on Android but does nothing).
 * @param enabled Boolean value for location collection state.
 */
 setLocationCollection = function(enabled, success, error)

## Error handling

All error calbacks should expect an object, which has two properties, `code` and `message` and on **optional** property 'serviceProviderFailureData'.
`serviceProviderFailureData` - a string value configured on the TS server (relevant for error code 'ERR_REJECTED_BY_SERVER')
`message` - may contain a debug description of the error.
`code` - is one of the following:

	errors = {
	    ERR_SERVER_NOT_REACHABLE : 1000,
	    ERR_API_TOKEN : 1001,
	    ERR_DEVICE_NOT_BOUND : 1002,
	    ERR_INVALID_TOKEN : 1003,
	    ERR_CANCELED : 1004,
	    ERR_REJECTED_BY_SERVER : 1005,
	    ERR_APPROVAL_EXPIRED : 1006,
	    ERR_DATA_PROCESSING : 1007,
	    ERR_NO_VALID_AUTHENTICATORS : 1008,
	    ERR_SDK_VERSION_OLD : 1009,
	    ERR_TERMS_OF_USAGE_REJECTED : 1010,
	    ERR_ALL_AUTHENTICATORS_LOCKED : 1011,
	    ERR_SESSION_EXPIRED : 1012,
	    ERR_NOT_PLACEHOLDER : 1013,
	    ERR_INVALID_POLICY : 1014,
	    ERR_INVALID_APP : 1015
	}

For the meaning of each error code, please refer to the specific SDK documentation.

## Additional services

SDK version:

	/**
	 * The success calback should expect a string argument, holding the version.
	 */
	version = function(success, error)
	

	transmitSDK.version (function (version) {
                            document.all('sdkVersion').innerText = "SDK version: " + version;
                        },
                        function (error) {
                            console.error("should not get here");
                        });

-

Application session expiry:


    /**
     * Clears transmit SDK plugin state. Only success returned with no_result command status value.
     */

    transmitSDK.expirePluginState(  function() {
                                        alert("Session expired");
                                    },
                                    function(error) {
                                        alert("Session expired error" + error); 
                                    });

-

Current user:

	/**
	 * The success calback should expect a string argument, holding the username.
	 */
	currentUsername = function(success, error)


    transmitSDK.currentUsername(function(username) { 
                                    document.all('welcomeTitle').innerText = "Welcome " + username;
                                },
                                function(error) { console.error("should not get here / canceled") }
                                );

-

Last successfully logged user

	/**
	 * The success calback should expect a string argument, holding the username.
	 */
	lastLoggedUsername = function(success, error)
	
	
	transmitSDK.lastLoggedUsername (function(username) {
                                        document.all('lastLoggedUser').innerText = "Last logged user: " + username;
                                    },
                                    function (error) { console.error("should not get here") }
    );

-

List of users who successfully logged in:
	
	/**
	 * The success calback should expect an array argument, holding the usernames.
	 */
	listLastLoggedUsernames = function(success, error)

	
	transmitSDK.listLastLoggedUsernames (function(usernames) { console.log("Last logged users: " + usernames) },
                                                                          function(errors) { console.error ("Should not be called") } );

-

Clearing (resetting all SDK proeprties and storage):

	/**
	 * Clears all in SDK related internal storage.
	 */
	 clearAll = function(success, error)

-

Ending session and invalidating the current authentication token:

	/**
	 * @param arguments A JSON object composed of the following optional field defined in {@link exports#argNames}: ARG_TOKEN.
	 * In case token is provided it'll be sent to the server and invalidated.
	 */
	logout = function(arguments, success, error)
		
	var args = {};
	//args[transmitSDK.argNames.ARG_TOKEN] = "...";
	
	transmitSDK.logout(args,
	                    function() {
	                        alert("Logout succesful");
	                   },
	                   function(error) {
	                        alert("Logout error: " + error.code);
	                   });
