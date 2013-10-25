//
//  SinglyService+Delegate.h
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

@class SinglyService;

/*!
 *
 * A protocol that delegates of a SinglyService may implement to provide custom
 * behavior at various points of the authorization workflow.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@protocol SinglyServiceDelegate <NSObject>

@optional

/*!
 *
 * Delegate method that is called after the user has been successfully
 * authorized for the given service.
 *
 * @param service The service instance that handled the authorization.
 *
 * @see singlyService:didFailWithError:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)singlyServiceDidAuthorize:(SinglyService *)service;

/*!
 *
 * Delegate method that is called when an error occurs while logging into a
 * service. Errors can include service, network, parse and any other errors that
 * might arise during the authorization process.
 *
 * @param service The service instance that was in the process of authorizing
 *                the user when the error occurred.
 *
 * @param error The actual error object instance that was detected during the
 *              authorization process.
 *
 * @see singlyService:didFailWithError:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later. This method is
 *            **deprecated** and will be removed in a future release. Please use
 *            singlyService:didFailWithError: instead.
 *
**/
- (void)singlyServiceDidFail:(SinglyService *)service
                   withError:(NSError *)error DEPRECATED_ATTRIBUTE;

/*!
 *
 * Delegate method that is called when an error occurs while logging into a
 * service. Errors can include service, network, parse and any other errors that
 * might arise during the authorization process.
 *
 * @param service The service instance that was in the process of authorizing
 *                the user when the error occurred.
 *
 * @param error The actual error object instance that was detected during the
 *              authorization process.
 *
 * @available Available in Singly iOS SDK 1.3.0 and later.
 *
**/
- (void)singlyService:(SinglyService *)service
    didFailWithError:(NSError *)error;

@end

