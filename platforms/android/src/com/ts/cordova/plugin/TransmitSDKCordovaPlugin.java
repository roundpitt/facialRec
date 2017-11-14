package com.ts.cordova.plugin;

import android.support.annotation.NonNull;
import android.app.Fragment;
import android.text.TextUtils;
import android.view.ViewGroup;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaArgs;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.ts.common.api.SDKBase;
import com.ts.common.api.TSLog;
import com.ts.common.api.core.Error;
import com.ts.common.api.core.PlaceholderData;
import com.ts.common.api.core.UserData;
import com.ts.common.api.core.authenticator.PlaceholderAuthenticatorBase;
import com.ts.common.api.ui.OperationListener;
import com.ts.common.internal.core.logger.Log;
import com.ts.sdk.api.SDK;
import com.ts.sdk.api.ui.UserManagementListener;
import com.ts.sdk.api.ui.fragments.CancelableFragment;
import com.ts.sdk.api.ui.fragments.ConfigurationFragment;
import com.ts.sdk.api.ui.fragments.PlaceholderFragment;
import com.ts.sdk.api.ui.fragments.AuthenticationFragment;
import com.ts.sdk.api.ui.AuthenticationListener;
import com.ts.sdk.api.ui.ConfigurationListener;
import com.ts.sdk.api.ui.fragments.UserManagementFragment;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

public class TransmitSDKCordovaPlugin extends CordovaPlugin {

    private final static String TAG = TransmitSDKCordovaPlugin.class.getCanonicalName();

    private final static String ARG_SERVER_URI = "uri";
    private final static String ARG_SERVER_PORT = "port";
    private final static String ARG_SERVER_IS_SECURE = "is_secure";

    private final static String ARG_API_TOKEN_NAME = "api_token_name";
    private final static String ARG_API_TOKEN = "api_token";

    private final static String ARG_USERNAME = "username";
    private final static String ARG_REQUEST_ID = "request_id";
    private final static String ARG_TOKEN = "token";
    private final static String ARG_REQUEST_PARAMS = "request_params";
    private final static String ARG_FORCE_MENU = "force_menu";

    private final static String RESULT_TAG_ERROR_CODE = "code";
    private final static String RESULT_TAG_ERROR_MESSAGE = "message";
    private final static String RESULT_TAG_FAILURE_DATA = "serviceProviderFailureData";
    private final static String RESULT_TAG_RESULT = "result";
    private final static String RESULT_TAG_TOKEN = "token";

    private final static String RESULT_VALUE_SUCCESS = "success";
    private final static String RESULT_VALUE_CANCEL = "cancel";
    private final static String RESULT_VALUE_DONE = "done";
    private final static String RESULT_VALUE_PLACEHOLDER = "placeholder";

    private static boolean sInitialized = false;

    final static private String SDK_FRAG_TAG = "SDK_FRAG_TAG";

    private CordovaWebView mWebView;

    private Fragment mPlaceholderFragment;
    private CallbackContext mCurrentCallbackContext;

    // Used when instantiated via reflection by PluginManager
    public TransmitSDKCordovaPlugin() {

    }

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);

        mWebView = webView;
    }

    @Override
    public boolean execute(String action, CordovaArgs args, final CallbackContext callbackContext) throws JSONException {
        if (action.equals("authenticate")) {
            Log.d(TAG, "authenticate");

            authenticate(args, callbackContext);

            return true;
        }
        else if (action.equals("configure")) {
            Log.d(TAG, "configure");

            configure(args, callbackContext);

            return true;
        }
        else if (action.equals("resumeFromPlaceholder")) {
            Log.d(TAG, "resumeFromPlaceholder");

            resumeFromPlaceholder(args, callbackContext);

            return true;
        }
        else if (action.equals("initSDK")) {
            Log.d(TAG, "initSDK");

            initSDK(args, callbackContext);

            return true;
        }
        else if (action.equals("manageUsers")) {
            Log.d(TAG, "manageUsers");

            manageUsers(callbackContext);

            return true;
        }
        else if (action.equals("logout")) {
            Log.d(TAG, "logout");

            logout(args, callbackContext);

            return true;
        }
        else if (action.equals("version")) {
            Log.d(TAG, "version");

            getVersion(callbackContext);

            return true;
        }
        else if (action.equals("currentUsername")) {
            Log.d(TAG, "currentUsername");

            getCurrentUsername (callbackContext);

            return true;
        }
        else if (action.equals("lastLoggedUsername")) {
            Log.d(TAG, "lastLoggedUsername");

            getLastLoggedUsername(callbackContext);

            return true;
        }
        else if (action.equals("listLastLoggedUsernames")) {
            Log.d(TAG, "listLastLoggedUsernames");

            getLastLoggedUsernames (callbackContext);

            return true;
        }
        else if (action.equals("clearAll")) {
            Log.d(TAG, "clearAll");

            clearAll(callbackContext);

            return true;
        }
        else if (action.equals("setLocationCollection")) {
            Log.d(TAG, "setLocationCollection");

            setLocationCollection(callbackContext);

            return true;
        }
        else if (action.equals("expirePluginState")) {
            Log.d(TAG, "expirePluginState");

            expirePluginState(callbackContext);

            return true;
        }
        else {
            Log.e(TAG, "Unhandled action: " + action);
        }

        return false;
    }
    
    /*
     API METHODS
     */

    private void initSDK (CordovaArgs _args, final CallbackContext callbackContext) throws JSONException {
        if (sInitialized) {
            Log.w(TAG, "SDK may be initialized only once.");

            callbackContext.success(new JSONObject(new HashMap<String, String>(1) {{
                put(RESULT_TAG_RESULT, RESULT_VALUE_SUCCESS);
            }}));
            
            return;
        }

        JSONObject jsonConnectionDetails = _args.getJSONObject(0);
        JSONObject jsonAPIToken = _args.getJSONObject(1);
        String appId = _args.getString(2);

        SDKBase.ConnectionDetails connectionDetails = new SDKBase.ConnectionDetails(jsonConnectionDetails.getString(ARG_SERVER_URI),
                jsonConnectionDetails.getString(ARG_SERVER_PORT),
                jsonConnectionDetails.getString(ARG_SERVER_PORT),
                jsonConnectionDetails.getBoolean(ARG_SERVER_IS_SECURE));

        SDKBase.AuthenticatorsProperties authProperties = new SDKBase.AuthenticatorsProperties(null, "ATSS8V");

        SDK.getInstance().initialize(cordova.getActivity().getApplication(), appId,
                jsonAPIToken.getString(ARG_API_TOKEN_NAME), jsonAPIToken.getString(ARG_API_TOKEN),
                connectionDetails, authProperties, new SDKBase.InitializationListener() {
                    @Override
                    public void initialized() {
                        Log.d(TAG, "initialized()");
                        sInitialized = true;
                        callbackContext.success(new JSONObject(new HashMap<String, String>(1) {{
                            put(RESULT_TAG_RESULT, RESULT_VALUE_SUCCESS);
                        }}));
                    }

                    @Override
                    public void failedToInitialize(final int _errorCode) {
                        Log.e(TAG, "failedToInitialize()");
                        callbackContext.error(new JSONObject(new HashMap<String, Object>(2) {{
                            put(RESULT_TAG_ERROR_CODE, _errorCode);
                            put(RESULT_TAG_ERROR_MESSAGE, "error");
                        }}));
                    }
                }, null, null, null);

        SDK.getInstance().setLogLevel(TSLog.LOG_LEVEL_VERBOSE);
    }

    private void getVersion(CallbackContext callbackContext) {
        callbackContext.success(SDK.getInstance().getVersion());
    }

    private void getCurrentUsername (CallbackContext callbackContext) {
        callbackContext.success(SDK.getInstance().getCurrentUsername());
    }

    private void getLastLoggedUsername (CallbackContext callbackContext) {
        UserData userData = SDK.getInstance().getLastLoggedUserData();
        callbackContext.success(null != userData ? userData.getUsername() : null);
    }

    private void getLastLoggedUsernames (CallbackContext callbackContext) {
        List<UserData> usersDatas = SDK.getInstance().getUsersData();

        JSONArray userNames = new JSONArray();

        for (UserData userData : usersDatas) {
            userNames.put(userData.getUsername());
        }

        callbackContext.success(userNames);
    }

    private void clearAll (CallbackContext callbackContext) {
        SDK.getInstance().clearAll();

        callbackContext.success();
    }

    private void setLocationCollection (CallbackContext callbackContext) {
        Log.w(TAG, "setLocationCollection(): is ignored, returning 'success'");

        callbackContext.success();
    }

    private void manageUsers (final CallbackContext callbackContext) {
        final Fragment frag = SDK.getInstance().getUserManagementLegacyFragment(cordova.getActivity());
        ((UserManagementFragment)frag).setListener(new UserManagementListener() {
            @Override
            public void changeUserDone() {
                Log.d(TAG, "changeUserDone()");

                removeFragment(frag);

                callbackContext.success(SDK.getInstance().getCurrentUsername());
            }

            @Override
            public void changeUserCanceled() {
                Log.d(TAG, "changeUserCanceled()");

                removeFragment(frag);

                callbackContext.error(new JSONObject(new HashMap<String, String>(1) {{
                    put(RESULT_TAG_ERROR_CODE, RESULT_VALUE_CANCEL);
                    put(RESULT_TAG_ERROR_MESSAGE, "canceled");
                }}));
            }
        });

        addFragment(frag);
    }

    private void resumeFromPlaceholder (CordovaArgs _args, CallbackContext callbackContext) throws JSONException {
        String token = _args.getString(0);

        beginContext(callbackContext);

        ((PlaceholderFragment) mPlaceholderFragment).placeholderSuccess(token, new OperationListener() {
            @Override
            public void operationSuccess() {
                Log.d(TAG, "operationSuccess()");
                mPlaceholderFragment = null;
            }

            @Override
            public void operationFailure(final int _errorCode, final Error _error) {
                Log.e(TAG, "operationFailure(): " + _error);
                removeFragment(mPlaceholderFragment);
                mPlaceholderFragment = null;

                endContextWithError(_error);
            }
        });

        addFragment(mPlaceholderFragment);
    }

    private void authenticate (CordovaArgs _args, CallbackContext callbackContext) throws JSONException {
        JSONObject jsonArgs = _args.getJSONObject(0);

        String username = null;
        String requestID = null;
        String token = null;
        boolean forceMenu = false;
        HashMap<String, Object> params = null;

        if (jsonArgs.has(ARG_USERNAME)) {
            username = jsonArgs.getString(ARG_USERNAME);
        }
        if (jsonArgs.has(ARG_REQUEST_ID)) {
            requestID = jsonArgs.getString(ARG_REQUEST_ID);
        }
        if (jsonArgs.has(ARG_TOKEN)) {
            token = jsonArgs.getString(ARG_TOKEN);
        }
        if (!TextUtils.isEmpty(token)) {
            Log.w(TAG, "'token' has no effect here");
        }
        if (jsonArgs.has(ARG_FORCE_MENU)) {
            forceMenu = jsonArgs.getBoolean(ARG_FORCE_MENU);
        }
        if (jsonArgs.has(ARG_REQUEST_PARAMS)) {
            JSONObject jsonParams = jsonArgs.getJSONObject(ARG_REQUEST_PARAMS);

            params = new HashMap<String, Object>(1);

            Iterator<String> keys = jsonParams.keys();

            while (keys.hasNext()) {
                String key = keys.next();
                params.put(key, jsonArgs.get(key));
            }
        }

        beginContext(callbackContext);

        final Fragment frag = SDK.getInstance().getAuthenticationLegacyFragment(cordova.getActivity(), username, null, forceMenu, requestID, params);

        ((AuthenticationFragment)frag).setListener(new AuthenticationListener() {
            @Override
            public void authenticationComplete(@NonNull final String _token) {
                Log.d(TAG, "authenticationComplete(): " + _token);

                removeFragment(frag);

                endContext(new JSONObject(new HashMap<String, String>(2) {{
                    put(RESULT_TAG_RESULT, RESULT_VALUE_SUCCESS);
                    put(RESULT_TAG_TOKEN, _token);
                }}));
            }

            @Override
            public void authenticationFailed(final int _errorCode, final Error _error) {
                Log.e(TAG, "authenticationFailed(): " + _error);

                removeFragment(frag);

                endContextWithError(_error);
            }

            @Override
            public void authenticationCanceled() {
                Log.d(TAG, "authenticationCanceled()");

                removeFragment(frag);

                endContextWithCancel(false);
            }

            @Override
            public void forgotPassword() {
                Log.d(TAG, "forgotPassword()");

                removeFragment(frag);

                endContext(new JSONObject(new HashMap<String, String>(1) {{
                    put(RESULT_TAG_RESULT, "forgot_password");
                }}));
            }

            @Override
            public void performAuthentication(@NonNull final PlaceholderAuthenticatorBase _placeholderAuthenticator, @NonNull final PlaceholderData _placeholderData) {
                Log.d(TAG, "auth: performAuthentication()");

                mPlaceholderFragment = frag;

                removeFragment(frag);

                endContext(new JSONObject(new HashMap<String, String>(4) {{
                    put(RESULT_TAG_RESULT, RESULT_VALUE_PLACEHOLDER);
                    put("data", _placeholderData.encode());
                    put("purpose", _placeholderData.getPurpose());
                    put("type", _placeholderAuthenticator.getDisplayTypeName().toLowerCase());
                }}));
            }

            @Override
            public void onJSONDataReceived(JSONObject _data) {
                Log.e(TAG, "onJSONDataReceived(): not implemented");
            }
        });

        addFragment(frag);
    }

    private void configure (CordovaArgs _args, CallbackContext callbackContext) throws JSONException {
        JSONObject jsonArgs = _args.getJSONObject(0);

        String username = null;
        String token = null;

        if (jsonArgs.has(ARG_USERNAME)) {
            username = jsonArgs.getString(ARG_USERNAME);
        }
        if (jsonArgs.has(ARG_TOKEN)) {
            token = jsonArgs.getString(ARG_TOKEN);
        }

        beginContext(callbackContext);

        final Fragment frag = SDK.getInstance().getConfigurationLegacyFragment(cordova.getActivity(), username, token);
        ((ConfigurationFragment)frag).setListener(new ConfigurationListener() {
            @Override
            public void performConfiguration(PlaceholderAuthenticatorBase _placeholderAuthenticator) {
                Log.d(TAG, "performConfiguration()");

                removeFragment(frag);

                throw new UnsupportedOperationException("Placeholder configuration is not implemented yet");
            }

            @Override
            public void performUnregistration(PlaceholderAuthenticatorBase _placeholderAuthenticator) {
                Log.d(TAG, "performUnregistration()");

                removeFragment(frag);

                throw new UnsupportedOperationException("Placeholder configuration is not implemented yet");
            }

            @Override
            public void configurationSuccess(@NonNull String _typeName) {
                Log.d(TAG, "configurationSuccess()");
            }

            @Override
            public void configurationFailed(final int _errorCode, final Error _error) {
                Log.e(TAG, "configurationFailed(): " + _error);

                removeFragment(frag);

                endContextWithError(_error);
            }

            @Override
            public void configurationCanceled() {
                removeFragment(frag);

                endContextWithCancel(false);
            }

            @Override
            public void configurationDone() {
                removeFragment(frag);

                endContextWithCancel(true);
            }

            @Override
            public void performAuthentication(@NonNull final PlaceholderAuthenticatorBase _placeholderAuthenticator, @NonNull final PlaceholderData _placeholderData) {
                Log.d(TAG, "config: performAuthentication()");

                mPlaceholderFragment = frag;

                removeFragment(frag);

                endContext(new JSONObject(new HashMap<String, String>(4) {{
                    put(RESULT_TAG_RESULT, RESULT_VALUE_PLACEHOLDER);
                    put("data", _placeholderData.encode());
                    put("purpose", _placeholderData.getPurpose());
                    put("type", _placeholderAuthenticator.getDisplayTypeName().toLowerCase());
                }}));
            }
        });

        addFragment(frag);
    }

    private void logout (CordovaArgs _args, final CallbackContext callbackContext) throws JSONException {
        JSONObject jsonArgs = _args.getJSONObject(0);

        String token = null;

        if (jsonArgs.has(ARG_TOKEN)) {
            token = jsonArgs.getString(ARG_TOKEN);
        }

        SDK.getInstance().logout(token, new OperationListener() {
            @Override
            public void operationSuccess() {
                Log.d(TAG, "logout: operationSuccess()");

                callbackContext.success(new JSONObject(new HashMap<String, String>(1) {{
                    put(RESULT_TAG_RESULT, RESULT_VALUE_SUCCESS);
                }}));
            }

            @Override
            public void operationFailure(final int _errorCode, final Error _error) {
                Log.e(TAG, "logout: operationFailure(): " + _error);

                callbackContext.error(new JSONObject(new HashMap<String, Object>(2) {{
                    put(RESULT_TAG_ERROR_CODE, _error.getErrorCode());
                    put(RESULT_TAG_ERROR_MESSAGE, _error.getMessage());
                }}));
            }
        });
    }

    private void expirePluginState (CallbackContext callbackContext) {
        mCurrentCallbackContext = null;

        Fragment frag = cordova.getActivity().getFragmentManager().findFragmentByTag(SDK_FRAG_TAG);

        if (null != frag && frag.isAdded()) {
            ((CancelableFragment)frag).cancel();
            removeFragment(frag);
        }

        callbackContext.success();
    }

    /*
     PRIVATE HELPER METHODS
     */

    private void addFragment (Fragment _frag) {
        cordova.getActivity().getFragmentManager().beginTransaction()
        .setCustomAnimations(android.R.animator.fade_in, android.R.animator.fade_out)
        .replace(((ViewGroup) mWebView.getView().getParent()).getId(), _frag, SDK_FRAG_TAG)
        .commit();
    }

    private void removeFragment (Fragment _frag) {
        cordova.getActivity().getFragmentManager().beginTransaction()
        .setCustomAnimations(android.R.animator.fade_in, android.R.animator.fade_out)
        .remove(_frag)
        .commit();
    }

    private void beginContext (@NonNull CallbackContext _context) { mCurrentCallbackContext = _context; }

    private void endContext (JSONObject _result) {
        if (null == mCurrentCallbackContext) {
            Log.w(TAG, "currentCallbackContext is 'null'");
            return;
        }

        mCurrentCallbackContext.success(_result);
        mCurrentCallbackContext = null;
    }

    private void endContextWithError (final Error _error) {
        if (null == mCurrentCallbackContext) {
            Log.w(TAG, "currentCallbackContext is 'null'");
            return;
        }

        JSONObject jsonError = new JSONObject(new HashMap<String, Object>(2) {{
            put(RESULT_TAG_ERROR_CODE, _error.getErrorCode());
            put(RESULT_TAG_ERROR_MESSAGE, _error.getMessage());

            if (null != _error.getServiceProviderFailureData()) {
                put(RESULT_TAG_FAILURE_DATA, _error.getServiceProviderFailureData());
            }
        }});

        mCurrentCallbackContext.error(jsonError);
        mCurrentCallbackContext = null;
    }

    private void endContextWithCancel (final boolean _isDone) {
        if (null == mCurrentCallbackContext) {
            Log.w(TAG, "currentCallbackContext is 'null'");
            return;
        }

        JSONObject jsonError = new JSONObject(new HashMap<String, String>(2) {{
            put(RESULT_TAG_ERROR_CODE, _isDone ? RESULT_VALUE_DONE : RESULT_VALUE_CANCEL);
            put(RESULT_TAG_ERROR_MESSAGE, "canceled");
        }});

        mCurrentCallbackContext.error(jsonError);
        mCurrentCallbackContext = null;
    }

}
