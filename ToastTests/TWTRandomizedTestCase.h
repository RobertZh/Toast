//
//  TWTRandomizedTestCase.h
//  Toast
//
//  Created by Prachi Gauriar on 1/13/14.
//  Copyright (c) 2015 Ticketmaster
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import <XCTest/XCTest.h>
#import <URLMock/UMKTestUtilities.h>

/*!
 TWTRandomizedTestCases simply override +setUp to call srandomdev() and -setUp to generate and log a
 random seed value before calling srandom(). Subclasses that override +setUp or -setUp should invoke
 the superclass implementation.
 */
@interface TWTRandomizedTestCase : XCTestCase
@end


/*!
 @abstract XCTAsserts that the given expression evaluates to YES before the given timeout interval elapses.
 @param timeoutInterval An NSTimeInterval containing the amount of time to wait for the expression to evaluate to YES.
 @param expression The boolean expression to evaluate.
 @param format An NSString object that contains a printf-style string containing an error message describing the failure
     condition and placeholders for the arguments.
 @param ... The arguments displayed in the format string.
 */
#define UMKAssertTrueBeforeTimeout(timeoutInterval, expression, format...) \
    XCTAssertTrue(UMKWaitForCondition((timeoutInterval), ^BOOL{ return (expression); }), ## format)
