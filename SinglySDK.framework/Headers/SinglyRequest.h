//
//  SinglyRequest.h
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

/*!
 *
 * SinglyRequest is a subclass of NSMutableURLRequest provided to aid developers
 * in making requests against the Singly API. Requests are initialized with the
 * relevant credentials for the current SinglySession shared instance
 * automatically.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@interface SinglyRequest : NSMutableURLRequest

/// ----------------------------------------------------------------------------
/// @name Creating Requests
/// ----------------------------------------------------------------------------

/*!
 *
 * Creates and returns a URL request for a specified endpoint of the Singly API.
 * The returned URL request is a subclass of NSMutableURLRequest that has been
 * customized specifically for requests to the Singly API.
 *
 * @param endpoint The endpoint for the new request.
 *
 * @returns The newly created Singly request.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
+ (id)requestWithEndpoint:(NSString *)endpoint;

/*!
 *
 * Creates and returns a URL request for a specified endpoint and parameters for
 * the Singly API. The returned URL request is a subclass of NSMutableURLRequest
 * that has been customized specifically for requests to the Singly API.
 *
 * @param endpoint The endpoint for the new request.
 * @param parameters The parameters for the new request.
 *
 * @returns The newly created Singly request.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
+ (id)requestWithEndpoint:(NSString *)endpoint andParameters:(NSDictionary *)parameters;

/*!
 *
 * Returns a URL request for a specified endpoint of the Singly API. The
 * returned URL request is a subclass of NSMutableURLRequest that has been
 * customized specifically for requests to the Singly API.
 *
 * @param endpoint The endpoint for the new request.
 *
 * @returns The newly created Singly request.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (id)initWithEndpoint:(NSString *)endpoint;

/*!
 *
 * Returns a URL request for a specified endpoint and parameters for the Singly
 * API. The returned URL request is a subclass of NSMutableURLRequest that has
 * been customized specifically for requests to the Singly API.
 *
 * @param endpoint The endpoint for the new request.
 * @param parameters The parameters for the new request.
 *
 * @returns The newly created Singly request.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (id)initWithEndpoint:(NSString *)endpoint andParameters:(NSDictionary *)parameters;

/*!
 *
 * Returns the URL for a specified endpoint that has been customized for making
 * a request to the Singly API (such as the access_token parameter, etc).
 *
 * @param endpoint The endpoint for the new request.
 * @param parameters The parameters for the new request.
 *
 * @returns The URL to use when contacting the Singly API service.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
+ (NSURL *)URLForEndpoint:(NSString *)endpoint withParameters:(NSDictionary *)parameters;

/*!
 *
 * Returns the URL for a specified endpoint that has been customized for making
 * a request to the Singly API, with the option to disable the inclusion of any
 * authorization parameters (e.g. access_token) if your request does not require
 * authorization.
 *
 * @param endpoint The endpoint for the new request.
 * @param parameters The parameters for the new request.
 * @param authorization Whether or not authorization parameters should be included.
 *
 * @returns The URL to use when contacting the Singly API service.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
+ (NSURL *)URLForEndpoint:(NSString *)endpoint withParameters:(NSDictionary *)parameters andAuthorization:(BOOL)authorization;

/// ----------------------------------------------------------------------------
/// @name Configuring the Request
/// ----------------------------------------------------------------------------

/*!
 *
 * The relative endpoint path to access on the Singly API. This path will be
 * appended to the full request URL.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (nonatomic, strong) NSString *endpoint;

/*!
 *
 * The request parameters to use for the request. These will be merged with
 * the access_token and any other required parameters of the Singly API.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (nonatomic, strong) NSDictionary *parameters;

/*!
 *
 * Whether or not the request requires authorization. This defaults to `YES`,
 * however, it can be set to `NO` to prevent the passing of credentials (which
 * may be necessary in case you have an invalidated access token or for requests
 * that do not need authorization).
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (nonatomic, assign) BOOL isAuthorizedRequest;

@end
