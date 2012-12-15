//
//  SinglyService.h
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

#import <UIKit/UIKit.h>

#import "SinglyLoginViewController.h"
#import "SinglyService+Delegate.h"

/*!
 *
 * Authentication and state handling for a service (such as Facebook, Twitter,
 * etc) is managed by a SinglyService instance.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@interface SinglyService : NSObject <SinglyLoginViewControllerDelegate>

/// ----------------------------------------------------------------------------
/// @name Initializing a Service
/// ----------------------------------------------------------------------------

/*!
 *
 * Convenience method that will return an instance of SinglyService initialized
 * by the service identifier.
 *
 * @param serviceIdentifier  The identifier of the service (e.g. "facebook",
 *                           "twitter", etc).
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
+ (id)serviceWithIdentifier:(NSString *)serviceIdentifier;

/*!
 *
 * Initializes with serviceIdentifier.
 *
 * @param serviceIdentifier  The identifier of the service (e.g. "facebook",
 *                           "twitter", etc).
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (id)initWithIdentifier:(NSString *)serviceIdentifier;

/// ----------------------------------------------------------------------------
/// @name Configuring the Service
/// ----------------------------------------------------------------------------

/*!
 *
 * The service identifier (e.g. "facebook", "twitter", etc).
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (nonatomic, strong) NSString *serviceIdentifier;

/*!
 *
 * The client id for the service. This will be requested from the Singly API
 * automatically unless explicitly provided.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (nonatomic, strong) NSString *clientID;

/// ----------------------------------------------------------------------------
/// @name Requesting Authorization
/// ----------------------------------------------------------------------------

/*!
 *
 * Whether or not the service is currently authorized.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (nonatomic, assign) BOOL isAuthorized;

/*!
 *
 * Requests authorization from the user through any means possible, falling back
 * from integrated auth, app-based auth then Singly auth via our standard
 * login web view.
 *
 * @param viewController  The view controller instance that is presenting the
 *                        authorization request.
 *
 * @see requestAuthorizationFromViewController:withScopes:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)requestAuthorizationFromViewController:(UIViewController *)viewController;

/*!
 *
 * Requests authorization from the user through any means possible, falling back
 * from integrated auth, app-based auth then Singly auth via our standard
 * login web view.
 *
 * @param viewController  The view controller instance that is presenting the
 *                        authorization request.
 *
 * @param scopes          The scope(s) to request from the service.
 *
 * @see requestAuthorizationFromViewController:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)requestAuthorizationFromViewController:(UIViewController *)viewController
                                    withScopes:(NSArray *)scopes;

/// ----------------------------------------------------------------------------
/// @name Managing the Delegate
/// ----------------------------------------------------------------------------

/*!
 *
 * The object that acts as the delegate of the service.
 *
 * The delegate must adopt the SinglyServiceDelegate protocol.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (weak, atomic) id<SinglyServiceDelegate> delegate;

@end
