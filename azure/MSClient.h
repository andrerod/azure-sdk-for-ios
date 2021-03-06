/**
 * Copyright (c) Microsoft.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MSError.h"
#import "MSFilter.h"
#import "MSLoginController.h"

@class MSTable;
@class MSUser;


#pragma mark * Block Type Definitions

/// Callback for invokeAPI method that expects a JSON result.
typedef void (^MSAPIBlock)(id result, NSHTTPURLResponse *response, NSError *error);

/// Callback for the invokeAPI method that can return any media type.
typedef void (^MSAPIDataBlock)(NSData *result,
                               NSHTTPURLResponse *response,
                               NSError *error);

#pragma  mark * MSClient Public Interface

/// The MSClient class is the starting point for working with a Windows Azure
/// Mobile Service on a client device. An instance of the *MSClient* class is
/// created with a URL pointing to a Windows Azure Mobile Service. The *MSClient*
/// allows the developer to get MSTable instances, which are used to work with
/// the data of the Windows Azure Mobile Service, as well as login and logout an
/// end user.
@interface MSClient : NSObject <NSCopying>

#pragma mark * Public Readonly Properties

/// @name Properties
/// @{

/// The URL of the Windows Azure Mobile Service associated with the client.
@property (nonatomic, strong, readonly)     NSURL *applicationURL;

/// The application key for the Windows Azure Mobile Service associated with
/// the client if one was provided in the creation of the client and nil
/// otherwise. If non-nil, the application key will be included in all requests
/// made to the Windows Azure Mobile Service, allowing the client to perform
/// all actions on the Windows Azure Mobile Service that require application-key
/// level permissions.
@property (nonatomic, copy, readonly)     NSString *applicationKey;

/// A collection of MSFilter instances to apply to use with the requests and
/// responses sent and received by the client. The property is readonly and the
/// array is not-mutable. To apply a filter to a client, use the withFilter:
/// method.
@property (nonatomic, strong, readonly)         NSArray *filters;

#pragma mark * Public ReadWrite Properties


/// The currently logged in user. While the currentUser property can be set
/// directly, the login* and logout methods are more convenient and
/// recommended for non-testing use.
@property (nonatomic, strong)               MSUser *currentUser;

/// @}

#pragma  mark * Public Static Constructor Methods

/// @name Initializing the MSClient Object
/// @{

/// Creates a client with the given URL for the Windows Azure Mobile Service.
+(MSClient *)clientWithApplicationURLString:(NSString *)urlString;

/// Creates a client with the given URL and application key for the Windows Azure
/// Mobile Service.
+(MSClient *)clientWithApplicationURLString:(NSString *)urlString
                             applicationKey:(NSString *)key;

/// Old method to create a client with the given URL and application key for the
/// Windows Azure Mobile Service. This has been deprecated. Use
/// clientWithApplicationURLString:applicationKey:
/// @deprecated
+(MSClient *)clientWithApplicationURLString:(NSString *)urlString
                         withApplicationKey:(NSString *)key __deprecated;

/// Creates a client with the given URL for the Windows Azure Mobile Service.
+(MSClient *)clientWithApplicationURL:(NSURL *)url;

/// Creates a client with the given URL and application key for the Windows Azure
/// Mobile Service.
+(MSClient *)clientWithApplicationURL:(NSURL *)url
                       applicationKey:(NSString *)key;

#pragma  mark * Public Initializer Methods

/// Initializes a client with the given URL for the Windows Azure Mobile Service.
-(id)initWithApplicationURL:(NSURL *)url;

/// Initializes a client with the given URL and application key for the Windows
/// Azure Mobile Service.
-(id)initWithApplicationURL:(NSURL *)url applicationKey:(NSString *)key;

#pragma mark * Public Filter Methods

/// Creates a clone of the client with the given filter applied to the new client.
-(MSClient *)clientWithFilter:(id<MSFilter>)filter;

///@}

#pragma mark * Public invokeAPI Methods

/// @name Invoking Custom APIs
/// @{

/// Invokes a user-defined API of the Mobile Service.  The HTTP request and
/// response content will be treated as JSON.
-(void)invokeAPI:(NSString *)APIName
            body:(id)body
      HTTPMethod:(NSString *)method
      parameters:(NSDictionary *)parameters
         headers:(NSDictionary *)headers
      completion:(MSAPIBlock)completion;

/// Invokes a user-defined API of the Mobile Service.  The HTTP request and
/// response content can be of any media type.
-(void)invokeAPI:(NSString *)APIName
            data:(NSData *)data
      HTTPMethod:(NSString *)method
      parameters:(NSDictionary *)parameters
         headers:(NSDictionary *)headers
      completion:(MSAPIDataBlock)completion;

/// @}

@end