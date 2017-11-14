cordova.define("cordova-plugin-transmit-sdk.ts_platform", function(require, exports, module) {
/*
 * Copyright (C) Transmit Security, LTD - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

// !!! THIS CODE IS FOR INTERNAL PLUGIN USAGE ONLY AND WILL BE REMOVED IN THE FUTURE !!!
exports.platform =  "android";
exports.ts_android_errors = {
	/** A network connection problem occurred. */
    NETWORK_ERROR : 0x10,
    /** Authorization header is missing or expired. */
    AUTHORIZATION_ERROR : 0x11,
    /** Authentication policy includes only locked and unregistered authenticators. */
    ALL_AUTHENTICATORS_LOCKED : 0x12,
    /** Authentication flow has been rejected. */
    ACCESS_REJECTED : 0x13,
    /** Server failed to produce a valid policy. */
    POLICY_NOT_AVAILABLE : 0x14,
    /** app_id is unrecognized by the server. */
    APPLICATION_NOT_FOUND : 0x15,
    /** API token provided to the SDK is unrecognized by the server. */
    BAD_API_TOKEN : 0x17,
    /** The SDK version is not supported by the server and the hosting up should probably be upgraded */
    VERSION_NOT_SUPPORTED : 0x1A,
    /** Authentication policy includes only unregistered authenticators */
    NO_REGISTERED_AUTHENTICATORS : 0x1B,
    /** No authenticators are available (e.g. registration action is for fingerprint but the device doesn't support fingerprint authentication) */
    NO_AVAILABLE_AUTHENTICATORS : 0x1C,
    /** The device is not recognized by the server, authentication policy should be re-fetched (e.g. device was removed manually using server MNG-UI, while the SDK is logged in). */
    DEVICE_NOT_FOUND : 0x20,
    /** user approval was not given to perform an operation */
    NO_PERMISSION : 0x59,
    /** Approval has expired and can't be declined or approved. */
    APPROVAL_EXPIRED : 0x60,
    /** Approval ID is not recognized by the server. */
    APPROVAL_NOT_FOUND : 0x61,
    /** Authentication process has failed and is terminated (e.g. user has failed to answer all the questions for the questions authenticator) */
    AUTHENTICATION_FAILURE : 0xFFF0,
    /** Server response processing failure or any server failure that is not covered by the errors above. */
    DATA_PROCESSING_ERROR : 0xFFFF
};
});
