//
//  SinglyConstants.h
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

/*!
 *
 * @header SinglyConstants
 *
**/

// Singly SDK Version
static NSString * const kSinglySDKVersion = @"1.3.0";

// Default Base URL
static NSString * const kSinglyBaseURL = @"https://api.singly.com";

// Preference Keys
static NSString * const kSinglyAccessTokenKey = @"com.singly.accessToken";

// Error Domain
static NSString * const kSinglyErrorDomain = @"com.singly.sdk";

// Info Keys
static NSString * const kSinglyResponseKey = @"SinglyResponse";

// Access Token Errors
static NSInteger  const kSinglyInvalidAccessTokenErrorCode = 0;
static NSString * const kSinglyInvalidAccessTokenErrorMessage = @"Singly access token is expired or invalid.";

// Service Errors
static NSInteger  const kSinglyServiceErrorCode = 1;
static NSString * const kSinglyServiceErrorMessage = @"An error occurred while communicating with the Singly service.";

// Login Errors
static NSInteger  const kSinglyLoginAbortedErrorCode = 2;
static NSInteger  const kSinglyLoginFailedErrorCode = 3;

// Credentials Exception
static NSString * const kSinglyCredentialsMissingException = @"SinglyCredentialsMissingException";
