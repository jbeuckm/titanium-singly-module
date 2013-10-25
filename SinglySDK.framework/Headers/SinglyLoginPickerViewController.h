//
//  SinglyLoginPickerViewController.h
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

#import "SinglyLoginPickerViewController+Delegate.h"
#import "SinglyLoginViewController.h"
#import "SinglyService.h"
#import "SinglySession.h"
#import "SinglyTwitterService.h"

/*!
 *
 * Displays a list of services that can be authenticated against in a list view
 * with the option to log in to any supported services.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@interface SinglyLoginPickerViewController : UITableViewController
    <SinglyLoginViewControllerDelegate,
     SinglyServiceDelegate,
     SinglyTwitterServiceDelegate,
     UIActionSheetDelegate>

/// ----------------------------------------------------------------------------
/// @name Managing Available Services
/// ----------------------------------------------------------------------------

/*!
 *
 * The services that should be displayed in the picker. This defaults to all of
 * the available services as returned by servicesDictionary, but can be
 * set to just the services you require.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (strong) NSArray *services;

/*!
 *
 * A dictionary containing metadata describing all of the supported services.
 * The dictionary is automatically populated from the Singly API.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (strong, readonly) NSDictionary *servicesDictionary;

/// ----------------------------------------------------------------------------
/// @name Managing the Delegate
/// ----------------------------------------------------------------------------

/*!
 *
 * The object that acts as the delegate of the login picker view controller.
 *
 * The delegate must adopt the SinglyLoginPickerViewControllerDelegate protocol.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (weak) id <SinglyLoginPickerViewControllerDelegate> delegate;

@end
