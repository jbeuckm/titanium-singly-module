//
//  SinglySession.h
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

#import <Foundation/Foundation.h>

@class SinglyService;

/*!
 *
 * Notification raised when a session's profiles have been updated.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
static NSString *kSinglySessionProfilesUpdatedNotification = @"com.singly.notifications.SessionProfilesUpdatedNotification";

/*!
 *
 * Notification raised when a service has been applied to the Singly API.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
static NSString *kSinglyServiceAppliedNotification = @"com.singly.notifications.ServiceAppliedNotification";

/*!
 *
 * Manages the current session state.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@interface SinglySession : NSObject

/// ----------------------------------------------------------------------------
/// @name Accessing the Shared Session
/// ----------------------------------------------------------------------------

/*!
 *
 * Access the shared session object
 *
 * This is the preferred way to use the SinglySession and you should only create
 * a new instance if you must use multiple sessions inside one app.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
+ (SinglySession *)sharedSession;

/*!
 *
 * Get the session in a state that is ready to make API calls.
 *
 * @param completionHandler  The block to run when the check is complete. It
 *                           will be passed a `BOOL` stating whether or not the
 *                           the session is ready.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)startSessionWithCompletionHandler:(void (^)(BOOL))completionHandler;

/// ----------------------------------------------------------------------------
/// @name Configuring the Session
/// ----------------------------------------------------------------------------

/*!
 *
 * The client ID to be used while authenticating against the Singly API.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *clientID;

/*!
 *
 * The client secret to be used while authenticating against the Singly API.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *clientSecret;

/// ----------------------------------------------------------------------------
/// @name Accessing the Session Credentials
/// ----------------------------------------------------------------------------

/*!
 *
 * The access token that will be used for all Singly API requests.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *accessToken;

/*!
 *
 * The account ID associated with the current access token.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *accountID;

/// ----------------------------------------------------------------------------
/// @name Managing Session Profiles
/// ----------------------------------------------------------------------------

/*!
 *
 * Profiles of the services that the account has connected. Will return until
 * there is a valid session.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (readonly) NSDictionary *profiles;

/*!
 *
 * Updates the profiles by connecting to the Singly API and fetching the latest
 * version.
 *
 * A notification (`kSinglySessionProfilesUpdatedNotification`) is posted once
 * the update has completed.
 *
 * @see updateProfilesWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)updateProfiles;

/*!
 *
 * Updates the profiles by connecting to the Singly API and fetching the latest
 * version and call the specified `completionHandler` once the update has
 * completed.
 *
 * In addition to calling the specified completion handler, a notification
 * (`kSinglySessionProfilesUpdatedNotification`) is posted once the update has
 * completed.
 *
 * @param completionHandler  The block to call once the profiles have been
 *                           udpated.
 *
 * @see updateProfiles
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)updateProfilesWithCompletion:(void (^)(BOOL))completionHandler;

/// ----------------------------------------------------------------------------
/// @name Managing Services
/// ----------------------------------------------------------------------------

/*!
 *
 * Allows you to associate a service with an existing access token to the Singly
 * session.
 *
 * @param serviceIdentifier  The identifier of the service (e.g. "facebook",
 *                           "twitter", etc).
 *
 * @param token              The access token to associate with the session.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)applyService:(NSString *)serviceIdentifier withToken:(NSString *)token;

/// ----------------------------------------------------------------------------
/// @name Handling App Launches by URL
/// ----------------------------------------------------------------------------

/*!
 *
 * The service the is currently being authorized. This is necessary for
 * integration with 3rd party apps installed on the device so that we know which
 * service has been authorized after our app is relaunched by the authorizing
 * app.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (nonatomic, strong) SinglyService *authorizingService;

/*!
 *
 * Handles app launches by oauth redirection requests and maps them appropriately
 * based on the service.
 *
 * @param url The redirection URL that should be handled
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (BOOL)handleOpenURL:(NSURL *)url;

@end
