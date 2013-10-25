//
//  SinglyService.h
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

#import <UIKit/UIKit.h>

#import "SinglyLoginViewController.h"
#import "SinglyService+Delegate.h"

/*!
 *
 * Completion handler that is called after the user authorizes with a service
 * or when the authorization attempt has failed.
 *
 * @available Available in Singly iOS SDK 1.3.0 and later.
 *
**/
typedef void (^SinglyServiceAuthorizationCompletionHandler)(BOOL isSuccessful, NSError *error);

/*!
 *
 * Completion handler that is called after the user has disconnected from a
 * service or the disconnection attempt has failed.
 *
 * @available Available in Singly iOS SDK 1.3.0 and later.
 *
**/
typedef void (^SinglyServiceDisconnectionCompletionHandler)(BOOL isSuccessful, NSError *error);

/*!
 *
 * Notification raised when a service is authorizing. This notification is only
 * raised for native authorizations (i.e. Twitter and Facebook) as the web-based
 * workflow provides its own status indication.
 *
 * @available Available in Singly iOS SDK 1.2.2 and later.
 *
 **/
static NSString * const kSinglyServiceIsAuthorizingNotification = @"com.singly.notifications.isAuthorizingNotification";

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
 * @param serviceIdentifier The identifier of the service (e.g. "facebook",
 *                          "twitter", etc).
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
+ (id)serviceWithIdentifier:(NSString *)serviceIdentifier;

/*!
 *
 * Initializes with serviceIdentifier.
 *
 * @param serviceIdentifier The identifier of the service (e.g. "facebook",
 *                          "twitter", etc).
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
@property (copy) NSString *serviceIdentifier;

/*!
 *
 * The client identifier for the service. This will be requested from the Singly
 * API automatically, unless it has been explicitly provided.
 *
 * @see clientIdentifier
 *
 * @available Available in Singly iOS SDK 1.0.0 and later. This property is
 *            **deprecated** and will be removed in a future release. Please use
 *            `clientIdentifier` instead.
 *
 *
**/
@property (copy) NSString *clientID DEPRECATED_ATTRIBUTE;

/*!
 *
 * The client identifier for the service. This will be requested from the Singly
 * API automatically, unless it has been explicitly provided.
 *
 * @available Available in Singly iOS SDK 1.3.0 and later.
 *
**/
@property (copy) NSString *clientIdentifier;

/// ----------------------------------------------------------------------------
/// @name Requesting Authorization
/// ----------------------------------------------------------------------------

/*!
 *
 * Requests authorization from the user through any means possible, falling back
 * from integrated auth, app-based auth then Singly auth via our standard
 * login web view.
 *
 * @param viewController The view controller instance that is presenting the
 *                       authorization request.
 *
 * @see requestAuthorizationFromViewController:withScopes:
 * @see requestAuthorizationFromViewController:completion:
 * @see requestAuthorizationFromViewController:withScopes:completion:
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
 * @param viewController The view controller instance that is presenting the
 *                       authorization request.
 *
 * @param completionHandler The block to run when the request is complete. It
 *                          will be passed a `BOOL` stating whether or not the
 *                          operation succeeded.
 *
 * @see requestAuthorizationFromViewController:
 * @see requestAuthorizationFromViewController:withScopes:
 * @see requestAuthorizationFromViewController:withScopes:completion:
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (void)requestAuthorizationFromViewController:(UIViewController *)viewController
                                    completion:(SinglyServiceAuthorizationCompletionHandler)completionHandler;

/*!
 *
 * Requests authorization from the user through any means possible, falling back
 * from integrated auth, app-based auth then Singly auth via our standard
 * login web view.
 *
 * @param viewController The view controller instance that is presenting the
 *                       authorization request.
 *
 * @param scopes The scope(s) to request from the service. If you are requesting
 *               scopes from Facebook and wish for native authorization to
 *               succeed, you must only request read or write permissions in
 *               your request (you cannot ask for read and write simultaneously).
 *
 * @see requestAuthorizationFromViewController:
 * @see requestAuthorizationFromViewController:completion:
 * @see requestAuthorizationFromViewController:withScopes:completion:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)requestAuthorizationFromViewController:(UIViewController *)viewController
                                    withScopes:(NSArray *)scopes;

/*!
 *
 * Requests authorization from the user through any means possible, falling back
 * from integrated auth, app-based auth then Singly auth via our standard
 * login web view.
 *
 * This method should be overridden by subclasses that wish to implement their
 * own workflow for authorization.
 *
 * @param viewController The view controller instance that is presenting the
 *                       authorization request.
 *
 * @param scopes The scope(s) to request from the service. If you are requesting
 *               scopes from Facebook and wish for native authorization to
 *               succeed, you must only request read or write permissions in
 *               your request (you cannot ask for read and write simultaneously).
 *
 * @param completionHandler The block to run when the request is complete. It
 *                          will be passed a `BOOL` stating whether or not the
 *                          operation succeeded.
 *
 * @see requestAuthorizationFromViewController:
 * @see requestAuthorizationFromViewController:completion:
 * @see requestAuthorizationFromViewController:withScopes:
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (void)requestAuthorizationFromViewController:(UIViewController *)viewController
                                    withScopes:(NSArray *)scopes
                                    completion:(SinglyServiceAuthorizationCompletionHandler)completionHandler;

/// ----------------------------------------------------------------------------
/// @name Disconnecting from the Service
/// ----------------------------------------------------------------------------

/*!
 *
 * Disconnects from the service.
 *
 * @see disconnect:
 * @see disconnectWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.1.0 and later. This method is
 *            **deprecated** and will be removed in a future release. Please use
 *            disconnect: instead.
 *
**/
- (void)disconnect DEPRECATED_ATTRIBUTE;

/*!
 *
 * Disconnects from the service.
 *
 * @param error Out parameter used if an error occurs while disconnceting from
 *              the service. May be `NULL`.
 *
 * @returns `YES` if the operation was successful.
 *
 * @see disconnectWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (BOOL)disconnect:(NSError **)error;

/*!
 *
 * Disconnects from the service. Calls the specified block once the operation
 * has completed.
 *
 * @param completionHandler The block to run when the check is complete. It will
 *                          be passed a `BOOL` stating whether or not the
 *                          operation succeeded.
 *
 * @see disconnect:
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
- (void)disconnectWithCompletion:(SinglyServiceDisconnectionCompletionHandler)completionHandler;

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
@property (weak) id <SinglyServiceDelegate> delegate;

@end
