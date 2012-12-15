//
//  SinglyFacebookService.h
//  SinglySDK
//
//  Copyright (c) 2012 Singly, Inc. All rights reserved.
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
 * A custom implementation of a service specifically for Facebook that adds
 * support for authorization via the integrated support on iOS 6+. If integrated
 * support is not available, the installed Facebook app is tried. If neither
 * integrated authorization is available or the native app is not installed,
 * the standard Singly login workflow will be used.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@interface SinglyFacebookService : SinglyService

/*!
 *
 * Determines if the current device can authorize via the installed Facebook
 * app.
 *
 * @returns Whether or not the running app is configured correctly for
 *          authorization via the natively installed app.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (BOOL)isAppAuthorizationConfigured;

/*!
 *
 * Determines whether or not the current device is authenticated with Facebook
 * in the Settings app using the authorization support featured in iOS 6 and
 * higher.
 *
 * This method will query the account store and operates under the following,
 * undocumented assumptions (as of iOS 6.0):
 *
 *  * If the user has not authenticated with Facebook on their device, the
 *    account store will return `nil` when requesting Facebook accounts.
 *
 *  * If the user has authenticated with Facebook, but we are not yet authorized
 *    to use the account, the account store will return an empty array (except
 *    in the simulator, which will return the configured account as the array's
 *    only member).
 *
 *  * If the user has authenticated with Facebook and we are already authorized
 *    to use the account, the account store will return an array with the
 *    authorized account as the only entry.
 *
 * Unfortunately, the above assumptions are the only way to discover what we
 * need to know and quite likely will break in future releases of iOS 6. For
 * that reason, one should keep a close eye on this method to ensure support is
 * maintained throughout future releases.
 *
 * @returns Whether or not the current device is configured for integrated
 *          authorization.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (BOOL)isIntegratedAuthorizationConfigured;

@end
