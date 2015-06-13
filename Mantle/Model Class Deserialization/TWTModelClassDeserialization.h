//
//  TWTModelClassDeserialization.h
//  Toast
//
//  Created by Andrew Hershberger on 6/4/14.
//  Copyright (c) 2015 Ticketmaster Entertainment, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


/*!
 The error domain for deserialization errors generated by -twt_modelOfClass:error:
 */
extern NSString *const kTWTModelClassDeserializationErrorDomain;

typedef NS_ENUM(NSInteger, TWTModelClassDeserializationError) {

    /*!
     This error is generated by -[NSDictionary(TWTModelClassDeserialization) twt_modelOfClass:error:] if an
     error occurs during deserialization. The userInfo dictionary will contain an object for the key
     NSUnderlyingErrorKey
     */
    TWTModelClassDeserializationErrorModelObjectCreation,

    /*!
     This error is always generated by -[NSObject(TWTModelClassDeserialization) twt_modelOfClass:error:]. The
     userInfo dictionary will contain an object for the key
     kTWTModelClassDeserializationErrorUnexpectedObjectKey
     */
    TWTModelClassDeserializationErrorUnexpectedObject,

    /*!
     This error is generated by -[NSArray(TWTModelClassDeserialization) twt_modelOfClass:error:] if an error
     occurs during deserialization. The userInfo dictionary will contain an object for the key
     kTWTModelClassDeserializationErrorUnderlyingErrorsKey
     */
    TWTModelClassDeserializationErrorArrayElementsError
};

/*!
 The value for this userInfo key is the object which could not be deserialized.
 */
extern NSString *const kTWTModelClassDeserializationErrorUnexpectedObjectKey;

/*!
 The value for this userInfo key is an array of underlying errors that occurred when deserializing elements in
 an array
 */
extern NSString *const kTWTModelClassDeserializationErrorUnderlyingErrorsKey;


/*!
 @brief This protocol unifies deserialization of JSON objects into Mantle model objects.

 @description TWTModelClassDeserialization eliminates the need for class checking during deserialization by
 relying on dynamic dispatch in the runtime. Without this approach, you might write something like this:

 @code
 id resultObject = nil;
 if ([object isKindOfClass:[NSDictionary class]]) {
     resultObject = [MTLJSONAdapter modelOfClass:modelClass fromJSONDictionary:object error:NULL];
 }
 else if ([object isKindOfClass:[NSArray class]]) {
     NSMutableArray *results = [[NSMutableArray alloc] init];
     for (id element in object) {
         id result = [MTLJSONAdapter modelOfClass:modelClass fromJSONDictionary:element error:NULL];
         if (result) {
             [results addObject:result];
         }
     }
     resultObject = results;
 }
 else {
     // handle this error
 }
 @endcode

 TWTModelClassDeserialization transforms this problem into:

 @code
 id resultObject = [object twt_modelOfClass:modelClass error:NULL];
 @endcode

 NSObject, NSArray, and NSDictionary conform to this protocol, so there should not be any need to make other
 classes conform.
 */
@protocol TWTModelClassDeserialization <NSObject>

/*!
 Returns deserialized object(s) of the specified modelClass.
 @param modelClass Some subclass of MTLModel that is the top-level class to generate.
 @param error An out error. This parameter may be NULL.
 @returns deserialized object(s) of the specified modelClass or nil if an error occurred.
 */
- (id)twt_modelOfClass:(Class)modelClass error:(NSError *__autoreleasing *)error;

@end


/*!
 This base implementation of the TWTModelClassDeserialization protocol always returns nil and sets the error
 parameter accordingly
 */
@interface NSObject (TWTModelClassDeserialization) <TWTModelClassDeserialization>
@end


/*!
 NSArray's implementation returns the array that results by mapping each element in self to a result object by
 calling -twt_modelOfClass:error:. If any errors are encountered, it returns nil and sets the error parameter
 accordingly.
 */
@interface NSArray (TWTModelClassDeserialization) <TWTModelClassDeserialization>
@end


/*!
 NSDictionary's implementation uses MTLJSONAdapter to create a single instance of modelClass given self. If an
 error occurrs, it returns nil and sets the error parameter accordingly.
 */
@interface NSDictionary (TWTModelClassDeserialization) <TWTModelClassDeserialization>
@end
