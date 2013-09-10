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

#import "MSSharedKeyTests.h"

@implementation MSSharedKeyTests

- (void)setUp
{
    [super setUp];
    
    _subject = [[MSSharedKey alloc] initWithAccount: @"devstoreaccount1" AndAccessKey: @"Eby8vdM02xNOcqFlqUwJPLlmEtlCDXJ1OUzFT50uSRZ6IFsuFq2UVErCz4I6tq/K1SZFPTOtr/KBHBeksoGMGw=="];
    STAssertNotNil(_subject, @"Could not create MSSharedKey.");
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testGetCanonicalizedHeaders
{
    MSWebResource* webResource = [[MSWebResource alloc] init];
    [webResource->headers setObject:@"value1" forKey:@"x-ms-header"];
    [webResource->headers setObject:@"value2" forKey:@"Content-Type"];

    NSString *canonicalizedResources = [_subject getCanonicalizedHeaders: webResource];

    STAssertEqualObjects(@"x-ms-header:value1\n", canonicalizedResources, @"the canonicalized headers did not match");
}

- (void)testGetCanonicalizedResource
{
    
}

- (void)testSignRequest
{
    MSWebResource* webResource = [[MSWebResource alloc] init];
    webResource->httpVerb = @"GET";
    webResource->path = @"container";
    [webResource->queryString setObject:@"container" forKey:@"restype"];
    [webResource->headers setObject:@"" forKey:@"content-type"];
    [webResource->headers setObject:@"2011-08-18" forKey:@"x-ms-version"];
    [webResource->headers setObject:@"Fri, 23 Sep 2011 01:37:34 GMT" forKey:@"x-ms-date"];

    [_subject signRequest:webResource];
    
    STAssertEqualObjects(@"SharedKey devstoreaccount1:Y5R86+6XE5MH602SIyjeTwlJuQjbawv20PT4kb/F/04=", [webResource->headers objectForKey:@"authorization"], @"the authorization header is not valid");
}

@end