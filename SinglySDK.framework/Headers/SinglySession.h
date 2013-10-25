//
//  SinglySession.h
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

#import <Foundation/Foundation.h>

@class SinglyService;

/*!
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
typedef void (^SinglyAccessTokenCompletionBlock)(NSString *accessToken, NSError *error);

/*!
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
typedef void (^SinglySessionCompletionBlock)(BOOL isReady, NSError *error);

/*!
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
typedef void (^SinglyUpdateProfilesCompletionBlock)(BOOL isSuccessful, NSError *error);

/*!
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
typedef void (^SinglyApplyServiceCompletionBlock)(BOOL isSuccessful, NSError *error);

/*!
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
typedef void (^SinglyContactsSyncCompletionBlock)(BOOL isSuccessful, NSError *error);

/*!
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
typedef void (^SinglyRemoveAccountCompletionBlock)(BOOL isSuccessful, NSError *error);

/*!
 *
 * Notification raised when the session has been started.
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
static NSString * const kSinglySessionStartedNotification = @"com.singly.notifications.SessionStartedNotification";

/*!
 *
 * Notification raised when the session has been reset.
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
static NSString * const kSinglySessionResetNotification = @"com.singly.notifications.SessionResetNotification";

/*!
 *
 * Notification raised when a session's profiles have been updated.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
static NSString * const kSinglySessionProfilesUpdatedNotification = @"com.singly.notifications.SessionProfilesUpdatedNotification";

/*!
 *
 * Notification raised when a service has been applied to the Singly API.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
static NSString * const kSinglyServiceAppliedNotification = @"com.singly.notifications.ServiceAppliedNotification";

/*!
 *
 * Notification raised when the device contacts have been synced with the
 * Singly API.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
static NSString * const kSinglyContactsSyncedNotification = @"com.singly.notifications.ContactsSyncedNotification";

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
 * Access the shared session object. If a shared session has not yet been
 * initialized, this method will initialize and return the shared instance.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
+ (SinglySession *)sharedSession;

/// ----------------------------------------------------------------------------
/// @name Configuring the Session
/// ----------------------------------------------------------------------------

/*!
 *
 * The base URL of the Singly API to use for the session. Defaults to
 * `https://api.singly.com`.
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
@property (copy) NSString *baseURL;

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

/*!
 *
 * The access token that will be used for all Singly API requests. This property
 * will be set automatically when authorizing against a supported service, but
 * you may also set it manually if your use case requires it.
 *
 * @see requestAccessTokenWithCode:
 * @see requestAccessTokenWithCode:completion:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *accessToken;

/*!
 *
 * The account ID associated with the current access token. This property will
 * be set automatically when authorizing against a supported service.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *accountID;

/// ----------------------------------------------------------------------------
/// @name Managing the Session
/// ----------------------------------------------------------------------------

/*!
 *
 * Requests your Access Token from the Singly API for the given code. The code
 * is returned in the Redirect URI after you have successfully authenticated
 * with a service via Singly.
 *
 * @param code The code to use.
 *
 * @see requestAccessTokenWithCode:error:
 * @see requestAccessTokenWithCode:completion:
 *
 * @available Available in Singly iOS SDK 1.1.0 and later. This method is
 *            **deprecated** and will be removed in a future release. Please use
 *            requestAccessTokenWithCode:error: instead.
 *
 *
**/
- (void)requestAccessTokenWithCode:(NSString *)code DEPRECATED_ATTRIBUTE;

/*!
 *
 * Requests your Access Token from the Singly API for the given code. The code
 * is returned in the Redirect URI after you have successfully authenticated
 * with a service via Singly.
 *
 * @param code The code to use.
 *
 * @param error Out parameter used if an error occurs while requesting the
 *              access token. May be `NULL`.
 *
 * @returns The retrieved access token, if no errors occurred (otherwise nil).
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (NSString *)requestAccessTokenWithCode:(NSString *)code
                                   error:(NSError **)error;

/*!
 *
 * Requests your Access Token from the Singly API for the given code. The code
 * is returned in the Redirect URI after you have successfully authenticated
 * with a service via Singly. Once complete, the given completion handler will
 * be called.
 *
 * @param code The code to use.
 *
 * @param completionHandler The block to call once the operation has completed.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
- (void)requestAccessTokenWithCode:(NSString *)code
                        completion:(SinglyAccessTokenCompletionBlock)completionHandler;

/*!
 *
 * Denotes whether or not the session is in a ready state (i.e. authorized and
 * valid).
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
@property (readonly) BOOL isReady;

/*!
 *
 * Gets the session into a state that is ready for your application to make API
 * calls.
 *
 * This method will execute synchronously, waiting for each operation to
 * complete before returning. In most cases, you will actually want to call
 * startSessionWithCompletion: to perform these steps asyncronously.
 *
 * A notification (`kSinglySessionStartedNotification`) is posted once the
 * session has been started.
 *
 * @param error Out parameter used if an error occurs while starting the
 *              session. May be `NULL`.
 *
 * @returns `YES` if the session was started, otherwise `NO`.
 *
 * @see startSessionWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (BOOL)startSession:(NSError **)error;

/*!
 *
 * Gets the session into a state that is ready for your application to make API
 * calls. Once the steps have finished, the provided completion block will be
 * called.
 *
 * A notification (`kSinglySessionStartedNotification`) is posted once the
 * session has been started.
 *
 * @param completionHandler  The block to run when the check is complete. It
 *                           will be passed a `BOOL` stating whether or not the
 *                           the session is ready.
 *
 * @see startSession:
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
- (void)startSessionWithCompletion:(SinglySessionCompletionBlock)completionHandler;

/*!
 *
 * Gets the session into a state that is ready for your application to make API
 * calls. Once the steps have finished, the provided completion block will be
 * called.
 *
 * A notification (`kSinglySessionStartedNotification`) is posted once the
 * session has been started.
 *
 * @param completionHandler  The block to run when the check is complete. It
 *                           will be passed a `BOOL` stating whether or not the
 *                           the session is ready.
 *
 * @see startSessionWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later. This method is
 *            **deprecated** and will be removed in a future release. Please use
 *            startSessionWithCompletion: instead.
 *
**/
- (void)startSessionWithCompletionHandler:(SinglySessionCompletionBlock)completionHandler DEPRECATED_ATTRIBUTE;

/*!
 *
 * Resets the current session by clearing the access token, account id and the
 * loaded profiles.
 *
 * @returns `YES` if the session was successfully reset.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
- (BOOL)resetSession;

/*!
 *
 * Completely removes (destroys) the account on Singly for the current session
 * and resets the session state to a blank slate. Use with caution!
 *
 * @param error Out parameter used if an error occurs while removing the
 *              account. May be `NULL`.
 *
 * @returns `YES` if the account was successfully removed.
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (BOOL)removeAccount:(NSError **)error;

/*!
 *
 * Completely removes (destroys) the account on Singly for the current session
 * and resets the session state to a blank slate. Use with caution! Calls the
 * `completionHandler` when the operation has completed.
 *
 * @param completionHandler The block to run once the request to remove the
 *                          account has been removed. It will be passed a
 *                          `BOOL` denoting whether or not the operation
 *                          succeeded and an NSError object if one is available.
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (void)removeAccountWithCompletion:(SinglyRemoveAccountCompletionBlock)completionHandler;

/// ----------------------------------------------------------------------------
/// @name Managing Session Profiles
/// ----------------------------------------------------------------------------

/*!
 *
 * A combined profile for the user derived from normalized data from all of the
 * services to which they are connected.
 *
 * This property is populated while updating profiles.
 *
 * @see updateProfiles:
 * @see updateProfilesWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
@property (readonly) NSDictionary *profile;

/*!
 *
 * Profiles of the services that the account has connected. Will return until
 * there is a valid session.
 *
 * This property is populated while updating profiles.
 *
 * @see updateProfiles:
 * @see updateProfilesWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
 * TODO Rename profiles to serviceProfiles
 *
**/
@property (readonly) NSDictionary *profiles;

/*!
 *
 * Updates the profiles by connecting to the Singly API and fetching the latest
 * version. This method is called synchronously.
 *
 * A notification (`kSinglySessionProfilesUpdatedNotification`) is posted once
 * the update has completed.
 *
 * @param error Out parameter used if an error occurs while starting the
 *              session. May be `NULL`.
 *
 * @see updateProfilesWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (BOOL)updateProfiles:(NSError **)error;

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
 *                           updated.
 *
 * @see updateProfiles:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)updateProfilesWithCompletion:(SinglyUpdateProfilesCompletionBlock)completionHandler;

/*!
 *
 * Resets the loaded profiles.
 *
 * @returns `YES` if the profiles were reset.
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (BOOL)resetProfiles;

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
 * @param accessToken        The access token to associate with the session.
 *
 * @see applyService:withToken:error:
 * @see applyService:withToken:completion:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later. This method is
 *            **deprecated** and will be removed in a future release. Please use
 *            applyService:withToken:error: instead.
 *
**/
- (void)applyService:(NSString *)serviceIdentifier
           withToken:(NSString *)accessToken DEPRECATED_ATTRIBUTE;

/*!
 *
 * Allows you to associate a service with an existing access token to the Singly
 * session.
 *
 * @param serviceIdentifier The identifier of the service (e.g. "facebook",
 *                          "twitter", etc).
 *
 * @param accessToken The access token to associate with the session.
 *
 * @param error Out parameter used if an error occurs while starting the
 *              session. May be `NULL`.
 *
 * @returns `YES` if the operation was successful.
 *
 * @see applyService:withToken:completion:
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (BOOL)applyService:(NSString *)serviceIdentifier
           withToken:(NSString *)accessToken
               error:(NSError **)error;

/*!
 *
 * Allows you to associate a service with an existing access token to the Singly
 * session.
 *
 * @param serviceIdentifier The identifier of the service (e.g. "facebook",
 *                          "twitter", etc).
 *
 * @param accessToken The access token to associate with the session.
 *
 * @param completionHandler The block to call once the service has been applied.
 *
 * @see applyService:withToken:error:
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (void)applyService:(NSString *)serviceIdentifier
           withToken:(NSString *)accessToken
          completion:(SinglyApplyServiceCompletionBlock)completionHandler;

/*!
 *
 * Allows you to associate a service with an existing access token to the Singly
 * session.
 *
 * @param serviceIdentifier The identifier of the service (e.g. "facebook",
 *                          "twitter", etc).
 *
 * @param accessToken The access token to associate with the session.
 *
 * @param tokenSecret The token secret, for OAuth 1.
 *
 * @param error Out parameter used if an error occurs while starting the
 *              session. May be `NULL`.
 *
 * @returns `YES` if the operation was successful.
 *
 * @see applyService:withToken:completion:
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (BOOL)applyService:(NSString *)serviceIdentifier
           withToken:(NSString *)accessToken
         tokenSecret:(NSString *)tokenSecret
               error:(NSError **)error;

/*!
 *
 * Allows you to associate a service with an existing access token to the Singly
 * session.
 *
 * @param serviceIdentifier The identifier of the service (e.g. "facebook",
 *                          "twitter", etc).
 *
 * @param accessToken The access token to associate with the session.
 *
 * @param tokenSecret The token secret, for OAuth 1.
 *
 * @param completionHandler The block to call once the service has been applied.
 *
 * @see applyService:withToken:error:
 *
 * @available Available in Singly iOS SDK 1.2.0 and later.
 *
**/
- (void)applyService:(NSString *)serviceIdentifier
           withToken:(NSString *)accessToken
         tokenSecret:(NSString *)tokenSecret
          completion:(SinglyApplyServiceCompletionBlock)completionHandler;

/// ----------------------------------------------------------------------------
/// @name Handling App Launches by URL
/// ----------------------------------------------------------------------------

/*!
 *
 * Handles app launches by oauth redirection requests and maps them appropriately
 * based on the service.
 *
 * @param url The URL to be handled.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (BOOL)handleOpenURL:(NSURL *)url;

@end
