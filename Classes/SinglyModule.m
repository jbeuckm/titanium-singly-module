/**
 * Your Copyright Here
 *
 * Appcelerator Titanium is Copyright (c) 2009-2010 by Appcelerator, Inc.
 * and licensed under the Apache Public License (version 2)
 */
#import "SinglyModule.h"
#import "TiBase.h"
#import "TiHost.h"
#import "TiUtils.h"


@implementation SinglyModule

#pragma mark Internal

-(void)startSession:(id)args
{
    ENSURE_UI_THREAD_1_ARG(args);
    ENSURE_SINGLE_ARG(args,NSDictionary);
    id success = [args objectForKey:@"success"];
    id cancel = [args objectForKey:@"error"];
    RELEASE_TO_NIL(successCallback);
    RELEASE_TO_NIL(cancelCallback);
    successCallback = [success retain];
    cancelCallback = [cancel retain];

    session = [SinglySession sharedSession];

    session.clientID = [TiUtils stringValue:[args objectForKey:@"clientID"]];
    session.clientSecret = [TiUtils stringValue:[args objectForKey:@"clientSecret"]];
    
    [session startSessionWithCompletionHandler:^(BOOL ready) {
        if (ready) {
            NSDictionary *sessionData = [[NSDictionary alloc] initWithObjectsAndKeys:
                session.accessToken, @"accessToken",
                session.accountID, @"accoundID",
                nil
            ];
            // The session is ready to go!
            [self _fireEventToListener:@"success" withObject:sessionData listener:successCallback thisObject:nil];
        } else {
            // You will need to auth with a service...
            [self _fireEventToListener:@"cancel" withObject:nil listener:cancelCallback thisObject:nil];
        }
    }];
}

-(void)requestAuthorization:(id)args
{
    ENSURE_UI_THREAD_1_ARG(args);
    ENSURE_SINGLE_ARG(args,NSDictionary);

    NSString *serviceName = [TiUtils stringValue:[args objectForKey:@"serviceName"]];
    //NSLog([NSString stringWithFormat:@"serviceName: %@", serviceName]);
    
    SinglyService *service = [SinglyService serviceWithIdentifier:serviceName];
    service.delegate = self;
    
    UIViewController *controller = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    
    [service requestAuthorizationFromViewController:controller];
}

- (void)singlyServiceDidAuthorize:(SinglyService *)service
{
    NSLog([NSString stringWithFormat:@"singlyServiceDidAuthorize"]);

    [self fireEvent:@"singlyServiceDidAuthorize" withObject:nil];
}

- (void)singlyServiceDidFail:(SinglyService *)service
                   withError:(NSError *)error
{
    NSLog([NSString stringWithFormat:@"singlyServiceDidFail"]);

    [self fireEvent:@"singlyServiceDidFail" withObject:error];
}



-(void)makeRequest:(id)args
{
    ENSURE_UI_THREAD_1_ARG(args);
    ENSURE_SINGLE_ARG(args, NSDictionary);
    
    id success = [args objectForKey:@"success"];
    RELEASE_TO_NIL(successCallback);
    successCallback = [success retain];
    
    NSString *endPoint = [TiUtils stringValue:[args objectForKey:@"endPoint"]];
    
    NSDictionary *urlParams = [args objectForKey:@"urlParams"];
    NSLog(@"urlParams = %@", urlParams);
    
    SinglyRequest *request = [SinglyRequest requestWithEndpoint:endPoint andParameters:urlParams];

    NSDictionary *postParams = [args objectForKey:@"postParams"];
    if (postParams) {
        
        NSLog(@"makeRequest >> POST");
        [request setHTTPMethod: @"POST"];
        [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];

        NSLog(@"postParams = %@", postParams);
//        NSData *requestData = [self encodeDictionary:postParams];
        NSData *requestData = [NSJSONSerialization dataWithJSONObject:postParams options:kNilOptions error:nil];
        
        NSString *requestString = [[NSString alloc] initWithData:requestData encoding:NSASCIIStringEncoding];
        NSLog(@"requestData = %@", requestString);
        [request setHTTPBody: requestData];
    }
    
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue]
                           completionHandler:^(NSURLResponse *response, NSData *data, NSError *error) {
                               
                               NSArray *responseObject = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:nil];
                               [self _fireEventToListener:@"success" withObject:responseObject listener:successCallback thisObject:nil];
                               
                           }
     ];
}



/**
 * Utility function to encode a dictionary into a querystring
 */
- (NSData*)encodeDictionary:(NSDictionary*)dictionary {
    NSMutableArray *parts = [[NSMutableArray alloc] init];
    for (NSString *key in dictionary) {
        NSString *encodedValue = [[dictionary objectForKey:key] stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        NSString *encodedKey = [key stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        NSString *part = [NSString stringWithFormat: @"%@=%@", encodedKey, encodedValue];
        [parts addObject:part];
    }
    NSString *encodedDictionary = [parts componentsJoinedByString:@"&"];
    NSLog(@"encodedDictionary = %@", encodedDictionary);
    return [encodedDictionary dataUsingEncoding:NSUTF8StringEncoding];
}



// this is generated for your module, please do not change it
-(id)moduleGUID
{
	return @"6cd8c23c-c807-45a8-810a-31fb2b5402ff";
}

// this is generated for your module, please do not change it
-(NSString*)moduleId
{
	return @"singly";
}

#pragma mark Lifecycle

-(void)startup
{
	// this method is called when the module is first loaded
	// you *must* call the superclass
	[super startup];
	
	NSLog(@"[INFO] %@ loaded",self);
}

-(void)shutdown:(id)sender
{
	// this method is called when the module is being unloaded
	// typically this is during shutdown. make sure you don't do too
	// much processing here or the app will be quit forceably
	
	// you *must* call the superclass
	[super shutdown:sender];
}

#pragma mark Cleanup 

-(void)dealloc
{
	// release any resources that have been retained by the module
	[super dealloc];
}

#pragma mark Internal Memory Management

-(void)didReceiveMemoryWarning:(NSNotification*)notification
{
	// optionally release any resources that can be dynamically
	// reloaded once memory is available - such as caches
	[super didReceiveMemoryWarning:notification];
}

#pragma mark Listener Notifications

-(void)_listenerAdded:(NSString *)type count:(int)count
{
	if (count == 1 && [type isEqualToString:@"my_event"])
	{
		// the first (of potentially many) listener is being added 
		// for event named 'my_event'
	}
}

-(void)_listenerRemoved:(NSString *)type count:(int)count
{
	if (count == 0 && [type isEqualToString:@"my_event"])
	{
		// the last listener called for event named 'my_event' has
		// been removed, we can optionally clean up any resources
		// since no body is listening at this point for that event
	}
}

#pragma Public APIs

-(id)example:(id)args
{
	// example method
	return @"hello world";
}

-(id)exampleProp
{
	// example property getter
	return @"hello world";
}

-(void)setExampleProp:(id)value
{
	// example property setter
}

@end
