//
//  SinglyLoginViewController.h
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

#import "SinglyLoginViewController+Delegate.h"
#import "SinglySession.h"

/*!
 *
 * A view controller for performing login workflows to supported services via a
 * web view.
 *
 * @note You should use the SinglyService class to invoke login requests instead
 * of creating an instance of this view controller directly. However, if you
 * need to accomplish something that is not supported by SinglyService, this
 * view controller is a good place to start.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@interface SinglyLoginViewController : UIViewController <UIWebViewDelegate>

/// ----------------------------------------------------------------------------
/// @name Initializing a Login View Controller
/// ----------------------------------------------------------------------------

/*!
 *
 * Initialize with a service identifier.
 *
 * @param serviceIdentifier  The identifier of the service (e.g. "facebook",
 *                           "twitter", etc).
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (id)initWithServiceIdentifier:(NSString *)serviceIdentifier;

/// ----------------------------------------------------------------------------
/// @name Configuring the Login View Controller
/// ----------------------------------------------------------------------------

/*!
 *
 * Identifier of the service to login to. For a list of supported services, see
 * the [Services Overview](https://singly.com/docs/services_overview).
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *serviceIdentifier;

/*!
 *
 * The brand name of the service which is properly capitalized and punctuated.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *serviceName;

/*!
 *
 * Custom scope to send to the service with the login request.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSArray *scopes;

/*!
 *
 * Optional flag to send to the service with the login request. Some services,
 * such as Twitter, require additional options which may be specified here.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *flags;

/// ----------------------------------------------------------------------------
/// @name Managing the Delegate
/// ----------------------------------------------------------------------------

/*!
 *
 * The object that acts as the delegate of the login view controller.
 *
 * The delegate must adopt the SinglyLoginViewControllerDelegate protocol.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (strong) id <SinglyLoginViewControllerDelegate> delegate;

@end
