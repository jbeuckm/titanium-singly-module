//
//  SinglyFacebookService.h
//  SinglySDK
//
//  Copyright (c) 2012-2013 Singly, Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//

#import <Accounts/Accounts.h>

#import "SinglyLoginViewController.h"
#import "SinglyService.h"

/*!
 *
 * A subclass of `SinglyService` that adds support for authorization using
 * either the native support available on iOS 6+ or the Facebook app that is
 * installed on the user's device. If either of those methods are not available,
 * the standard web-based workflow will be attempted.
 *
 * ### Supporting Native Authorization on iOS 6+
 *
 * Before native authorization can be used, you must first register your app at
 * the [Facebook Developers site](https://developers.facebook.com/apps) as a
 * "Native iOS App". Be sure to set the "Bundle ID" on your Facebook app to the
 * exact bundle identifier that is configured in your `Info.plist` file. You
 * should also [configure your app](https://singly.com/docs/api-keys/facebook)
 * for the standard web-based workflow.
 *
 * ### Supporting Authorization via the Facebook App
 *
 * If the user has the Facebook app installed on their device (and native
 * authorization is not available), the `SinglyFacebookService` will attempt to
 * authorize the user via the installed app. For this to work, you will need to
 * enable your app to handle launches with the Facebook URL scheme.
 *
 * #### Registering Your Facebook URL Scheme
 *
 * Add the following to your `Info.plist` file, replacing the 0's with your
 * actual Facebook App ID (from the
 * [developers site](https://developers.facebook.com/apps)):
 *
 *     	<key>CFBundleURLTypes</key>
 *     	<array>
 *     	  <dict>
 *     	    <key>CFBundleURLSchemes</key>
 *     	    <array>
 *     	      <string>fb000000000000000</string>
 *     	    </array>
 *     	  </dict>
 *     	</array>
 *
 * #### Handling Facebook URLs in Your App
 *
 * Just registering your app to open with your app-specific Facebook URL is not
 * enough to complete the round-trip request. We need to also be able to handle
 * this URL by passing it along to the Singly SDK so that it can complete the
 * authorization workflow. In your application delegate, implement the following
 * method:
 *
 *     	- (BOOL)application:(UIApplication *)application
 *     	            openURL:(NSURL *)url
 *    	  sourceApplication:(NSString *)sourceApplication
 *     	         annotation:(id)annotation
 *     	{
 *     	    return [SinglySession.sharedSession handleOpenURL:url];
 *     	}
 *
 * If you already have this method implemented, you may need to modify it to
 * check for Facebook URLs and pass only those to the Singly SDK.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@interface SinglyFacebookService : SinglyService

/*!
 *
 * Determines whether or not the app can use the installed Facebook app to
 * perform authorization requests.
 *
 * @returns `YES` if the app is configured correctly for authorization via the
 *          installed Facebook app.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (BOOL)isAppAuthorizationConfigured;

/*!
 *
 * Determines whether or not the current device is signed into Facebook (in
 * Settings) using the native support offered in iOS 6 and higher.
 *
 * This method will query the account store and operates under the following,
 * undocumented assumptions (as of iOS 6.0):
 *
 *  * If the user has not signed into Facebook on their device, the account
 *    store will return `nil` when requesting Facebook accounts.
 *
 *  * If the user has signed into Facebook, but the app is not yet authorized
 *    to use the account, the account store will return an empty array (except
 *    in the simulator, which will return the configured account as the array's
 *    only member).
 *
 *  * If the user has signed into Facebook and the app is already authorized
 *    to use the account, the account store will return an array with the
 *    authorized account as the only entry.
 *
 * Unfortunately, the above assumptions are the only way to discover what we
 * need to know and quite likely will break in future releases of iOS. For that
 * reason, one should keep a close eye on this method to ensure support is
 * maintained throughout future releases.
 *
 * @returns `YES` if the device is configured for native authorization.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (BOOL)isNativeAuthorizationConfigured;

/*!
 *
 * If your app requires a URL scheme suffix, set it here before requesting
 * authorization. When authenticating a user via the Facebook app, it will be
 * passed as `local_client_id`.
 *
 * See [this article at the Facebook developer site](https://developers.facebook.com/docs/howtos/share-appid-across-multiple-apps-ios-sdk/)
 * for more.
 *
**/
@property (strong) NSString *urlSchemeSuffix;

@end
