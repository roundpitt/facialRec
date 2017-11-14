# Changelog

## 2.15
- Updated iOS SDK to 2.15.3

## 2.13.11
- Updated iOS SDK to 2.13.10
- Added package.json file for cordova 7 support
- Stay on registration menu after register/unregister completion

## 2.13.10
- Updated iOS SDK to 2.13.9

## 2.13.9
- Added expirePluginState API to support application session expiry
- Fixed missing callback on initSDK incase the SDK was already initialized.
- Updated iOS SDK to 2.13.8.

## 2.13.8
- Updated iOS SDK to 2.13.7. Fixes accessibility issues, and handling of TouchID lockout in iOS 10.

## 2.13.7
- Added `setLocationCollection(enabled, success, error)` to manipulate location services requirement.

## 2.13.6
- require Android SDK version 2.13.5
- iOS SDK version updated to 2.13.6
- Bug fix in iOS plugin, placeholder followed by another action in the policy, did not continue to this action.


## 2.13.4
- iOS SDK version updated to 2.13.4
- Bug fix in iOS UI display, facilitate screen rotation. Screen rotation not fully supported.

## 2.13.3
- require Android SDK version 2.13.4
- iOS SDK version updated to 2.13.3

## 2.13.2
- iOS SDK version updated to 2.13.2

## v2.13.1
- iOS SDK version updated to 2.13.1
- Fixed missing placeholder data in iOS plugin.

## v2.13
- Added property `serviceProviderFailureData` to the error object argument passed in the authentication error callback.
- Removed requirement for Zannah framework on iOS.
- Removed authentication token management from plugin (SDK does session management).
