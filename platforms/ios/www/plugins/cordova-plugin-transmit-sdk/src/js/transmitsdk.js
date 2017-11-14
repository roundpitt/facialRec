cordova.define("cordova-plugin-transmit-sdk.TransmitSDKCordovaPlugin", function(require, exports, module) {
/*
 * Copyright (C) Transmit Security, LTD - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

var exec = require('cordova/exec');
var placeholderCallback = null;

exports.errors = {
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

// !!! THIS CODE IS FOR INTERNAL PLUGIN USAGE ONLY AND WILL BE REMOVED IN THE FUTURE !!!
function platformErrorResolver(error) {
    var errorHandlerWrapper = function (result) {
        if(result.result == "success")
        {
            error();
            return;
        }
        
        if (exports.platform == "ios") {
          // TODO: translate from iOS
          console.log ("Received ios error: " + result);
            switch(result.code) {
                case exports.ts_ios_errors.TS_ERR_SERVER_NOT_REACHABLE:
                    result.code = exports.errors.ERR_SERVER_NOT_REACHABLE;
                    break;
                case exports.ts_ios_errors.TS_ERR_BAD_CUSTOMER_ID:
                    result.code = exports.errors.ERR_API_TOKEN;
                    break;
                case exports.ts_ios_errors.TS_ERR_USER_DEVICE_UNKNOWN:
                    result.code = exports.errors.ERR_DEVICE_NOT_BOUND;
                    break;
                case exports.ts_ios_errors.TS_ERR_USER_NOT_AUTHENTICATED:
                    result.code = exports.errors.ERR_INVALID_TOKEN;
                    break;
                case exports.ts_ios_errors.TS_ERR_AUTH_USER_OPTED_OUT:
                    result.code = exports.errors.ERR_CANCELED;
                    break;
                case exports.ts_ios_errors.TS_ERR_AUTH_USER_REJECTED:
                    result.code = exports.errors.ERR_REJECTED_BY_SERVER;
                    break;
                case exports.ts_ios_errors.TS_ERR_APPROVALS_EXPIRED:
                    result.code = exports.errors.ERR_APPROVAL_EXPIRED;
                    break;
                case exports.ts_ios_errors.TS_ERR_DATA_PROCESSING:
                    result.code = exports.errors.ERR_DATA_PROCESSING;
                    break;
                case exports.ts_ios_errors.TS_ERR_AUTH_NO_VALID_AUTHENTICATORS:
                    result.code = exports.errors.ERR_NO_VALID_AUTHENTICATORS;
                    break;
                case exports.ts_ios_errors.TS_ERR_SDK_VERSION_OLD:
                    result.code = exports.errors.ERR_SDK_VERSION_OLD;
                    break;
                case exports.ts_ios_errors.TS_ERR_REGISTRATION_PERMISSION:
                    result.code = exports.errors.ERR_TERMS_OF_USAGE_REJECTED;
                    break;
                case exports.ts_ios_errors.TS_ERR_AUTH_ALL_LOCKED:
                    result.code = exports.errors.ERR_ALL_AUTHENTICATORS_LOCKED;
                    break;
                case exports.ts_ios_errors.TS_ERR_POLICY_INVALID:
                    result.code = exports.errors.ERR_SESSION_EXPIRED;
                    break;
                case exports.ts_ios_errors.TS_ERR_POLICY_AUTHETNICATOR_NOT_PLACEHOLDER:
                    result.code = exports.errors.ERR_NOT_PLACEHOLDER;
                    break;
                default:
                    console.log("Unhandled error code: " + result.code);
                    result.code = exports.errors.ERR_DATA_PROCESSING;
            }
          error(result);
        }
        else if (exports.platform == "android") {
          console.log ("Received android error: " + result.code);
          // TODO: what about forgot pasword?
          if (result.code === "done" || result.code === "cancel") {
              result.code = exports.errors.ERR_CANCELED;
          }
          else {
            switch(result.code) {
              case exports.ts_android_errors.NETWORK_ERROR:
                  result.code = exports.errors.ERR_SERVER_NOT_REACHABLE;
                  break;
              case exports.ts_android_errors.AUTHORIZATION_ERROR:
              case exports.ts_android_errors.BAD_API_TOKEN:
                  result.code = exports.errors.ERR_API_TOKEN;
                  break;
              case exports.ts_android_errors.DEVICE_NOT_FOUND:
                  result.code = exports.errors.ERR_DEVICE_NOT_BOUND;
                  break;
              case exports.ts_android_errors.ACCESS_REJECTED:
                  result.code = exports.errors.ERR_REJECTED_BY_SERVER;
                  break;
              case exports.ts_android_errors.APPROVAL_EXPIRED:
                    result.code = exports.errors.ERR_APPROVAL_EXPIRED;
                    break;
              case exports.ts_android_errors.DATA_PROCESSING_ERROR:
                  result.code = exports.errors.ERR_DATA_PROCESSING;
                  break;
              case exports.ts_android_errors.NO_REGISTERED_AUTHENTICATORS:
                    result.code = exports.errors.ERR_NO_VALID_AUTHENTICATORS;
                    break;
              case exports.ts_android_errors.VERSION_NOT_SUPPORTED:
                    result.code = exports.errors.ERR_SDK_VERSION_OLD;
                    break;
              case exports.ts_android_errors.NO_PERMISSION:
                    result.code = exports.errors.ERR_TERMS_OF_USAGE_REJECTED;
                    break;
              case exports.ts_android_errors.ALL_AUTHENTICATORS_LOCKED:
                    result.code = exports.errors.ERR_ALL_AUTHENTICATORS_LOCKED;
                    break;
              case exports.ts_android_errors.POLICY_NOT_AVAILABLE:
                    result.code = exports.errors.ERR_INVALID_POLICY;
                    break;
              default:
                  console.log("Unhandled error code: " + result.code);
                  result.code = exports.errors.ERR_DATA_PROCESSING;
            }
          }
          error(result);
        }
        else {
          // TODO: ??? return some special error code ???
          console.log ("Unsupported platform: " + exports.platform);
          error(0xFFFFFFFF);
        }
    }

    return errorHandlerWrapper;
}

function wrapCallbackWithPlaceholderHandler(success, error)
{
       var successHandlerWrapper = function(result) {               
       if(result.result == "success")
       {
           success(result.token);
       } else
       if(result.result == "placeholder")
       {
           placeholderCallback( result.data, result.purpose, result.type, function (responseFromPlaceholderCallback) {
                                    if(responseFromPlaceholderCallback.token) {
                                        exec(successHandlerWrapper, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "resumeFromPlaceholder", [responseFromPlaceholderCallback.token]);
                                    }
                                   });
       }
   }
               
   return successHandlerWrapper;
}

/*
API CONSTANTS
*/

/**
 * Argument keys to ease construction of expected object in API calls
 */
exports.argNames = {
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

/*
API METHODS
*/

/**
 * Should be set in case the authentication policy is expected to include a placeholder authenticator.
 */
exports.setPlaceholderCallback = function(callback) {
    placeholderCallback = callback;
}

/**
 * Initializes the SDK.
 * @param connectionDetails A JSON object composed of 3 fields defined in {@link exports#argNames}: ARG_SERVER_URI, ARG_SERVER_PORT, ARG_SERVER_IS_SECURE.
 * @param apiToken A JSON object composed of 2 fields defined in {@link exports#argNames}: ARG_API_TOKEN_NAME, ARG_API_TOKEN.
 * @param appId The application name as defined in the Authentication Control Server.
 */
exports.initSDK = function(connectionDetails, apiToken, appId, success, error) {
  exec(success, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "initSDK", [connectionDetails, apiToken, appId]);
}

/**
 * The success calback should expect a string argument, holding the version.
 */
exports.version = function(success, error) {
    exec(success, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "version");
}

/**
 * Enables/disables location collection by the SDK. Default is disabled.
 * (On Android, the calling application is responsible for handling permissions, the SDK will follow according to the permissions settings.
 *  Thus, this methos always reports success on Android but does nothing).
 * @param enabled Boolean value for location collection state.
 */
exports.setLocationCollection = function(enabled, success, error) {
    exec(success, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "setLocationCollection", [enabled]);
}

// Authentication and Authenticators management

/**
 * @param arguments A JSON object composed of any of the following optional fields defined in {@link exports#argNames}: 
 * ARG_USERNAME, ARG_REQUEST_ID, ARG_REQUEST_PARAMS, ARG_FORCE_MENU. 
 * In case username isn't provided the last logged user (or the one recived from then UI) is used.
 *
 * The success callback should expect a string argument, holding the authentication token.
 */
exports.authenticate = function(arguments, success, error) {
    exec(wrapCallbackWithPlaceholderHandler(success, platformErrorResolver(error)), platformErrorResolver(error), "TransmitSDKCordovaPlugin", "authenticate", [arguments]);
}

/**
 * @param arguments A JSON object composed of 2 of the following optional fields defined in {@link exports#argNames}: 
 * ARG_USERNAME, ARG_TOKEN. 
 * The token is relevant only in cases where registration is perfromed with no authentication preceding (e.g. fetching a configuration token from the app backend server by requesting it from the TS server).
 * In case username isn't provided the last logged user (or the one recived from then UI) is used.
 */
exports.configure = function(arguments, success, error) {
    exec(wrapCallbackWithPlaceholderHandler(success, platformErrorResolver(error)), platformErrorResolver(error), "TransmitSDKCordovaPlugin", "configure", [arguments]);
}

/**
 * @param arguments A JSON object composed of the following optional field defined in {@link exports#argNames}: ARG_TOKEN.
 * In case token is provided it'll be sent to the server and invalidated.
 */
exports.logout = function(arguments, success, error) {
  exec(success, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "logout", [arguments]);
}

exports.expirePluginState = function(success, error) {
    exec(success, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "expirePluginState");
}

// User management

/**
 * The success calback should expect a string argument, holding the username.
 */
exports.currentUsername = function(success, error) {
    exec(success, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "currentUsername");
}

/**
 * The success calback should expect a string argument, holding the username.
 */
exports.lastLoggedUsername = function(success, error) {
    exec(success, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "lastLoggedUsername");
}

/**
 * The success calback should expect an array argument, holding the usernames.
 */
exports.listLastLoggedUsernames = function(success, error) {
    exec(success, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "listLastLoggedUsernames");
}

/**
 * Invokes the users management UI. Success callback should expect a string argument holding the selected username.
 */
exports.manageUsers = function(success, error) {
    exec(success, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "manageUsers");
}

/**
 * Clears all in SDK related internal storage.
 */
 exports.clearAll = function(success, error) {
    exec(success, platformErrorResolver(error), "TransmitSDKCordovaPlugin", "clearAll");
 }

});
