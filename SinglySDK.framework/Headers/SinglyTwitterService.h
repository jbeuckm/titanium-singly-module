//
//  SinglyTwitterService.h
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
#import "SinglyTwitterService+Delegate.h"

/*!
 *
 * A subclass of `SinglyService` that adds support for authorization using
 * the native support available on iOS 5+. If native support is not available,
 * the standard web-based workflow will be attempted.
 *
 * Instances of this service requires that you set a delegate that adheres to
 * the `SinglyTwitterServiceDelegate` protocol.
 *
 * ### Choosing the Twitter Account to Authorize
 *
 * The user may have multiple Twitter accounts authorized on their device. When
 * integrated authorization is available, you will need to prompt the user for
 * which account they wish to authorize using the
 * [accountForTwitterAuthorization:]([SinglyTwitterServiceDelegate accountForTwitterAuthorization:])
 * delegate method.
 *
 *     	- (ACAccount *)accountForTwitterAuthorization:(NSArray *)availableAccounts
 *     	{
 *     	    // Present the list of accounts to the user and allow them to
 *     	    // decide which account to use...
 *     	
 *     	    return theChosenAccount;
 *     	}
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
@interface SinglyTwitterService : SinglyService

/*!
 *
 * Determines whether or not the current device is signed into Twitter (in
 * Settings) using the native support offered in iOS 5 and higher.
 *
 * @returns `YES` if the device is configured for native authorization.
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (BOOL)isNativeAuthorizationConfigured;

/*!
 *
 * The object that acts as the delegate of the service.
 *
 * The delegate must adopt the SinglyServiceDelegate protocol.
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
@property (weak) id <SinglyTwitterServiceDelegate> delegate;

@end
