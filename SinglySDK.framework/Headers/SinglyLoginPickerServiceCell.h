//
//  SinglyLoginPickerServiceCell.h
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

#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>

/*!
 *
 * A custom table view cell implementation for the display of service state.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@interface SinglyLoginPickerServiceCell : UITableViewCell
    <NSURLConnectionDelegate,
    NSURLConnectionDataDelegate>

/// ----------------------------------------------------------------------------
/// @name Configuring the Service Cell
/// ----------------------------------------------------------------------------

/*!
 *
 * Information from the Singly API about to the service.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSDictionary *serviceInfoDictionary;

/*!
 *
 * The service identifier of the service being displayed.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
@property (copy) NSString *serviceIdentifier;

/*!
 *
 * Whether or not the service is currently authenticated.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property BOOL isAuthenticated;

@end
