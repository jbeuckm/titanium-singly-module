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
    
    NSLog([NSString stringWithFormat:@"clientID: %@", session.clientID]);
    NSLog([NSString stringWithFormat:@"clientSecret: %@", session.clientSecret]);
    
    [session startSessionWithCompletionHandler:^(BOOL ready) {
        if (ready) {
            // The session is ready to go!
            [self _fireEventToListener:@"success" withObject:nil listener:successCallback thisObject:nil];
        } else {
            // You will need to auth with a service...
            [self _fireEventToListener:@"cancel" withObject:nil listener:cancelCallback thisObject:nil];
        }
    }];
}

-(void)requestAuthorization:(id)args
{
    NSString *serviceName = [TiUtils stringValue:[args objectForKey:@"serviceName"]];
    SinglyService *service = [SinglyService serviceWithIdentifier:serviceName];
    service.delegate = self;
    
    UIViewController *controller = [[UIViewController alloc] init];
    
    [service requestAuthorizationFromViewController:controller];
}



- (void)singlyServiceDidAuthorize:(SinglyService *)service
{
    // We're ready to rock!  Go do something amazing!
    
//    NSDictionary *event = [NSDictionary dictionaryWithObjectAndKeys:@"foo",@"name",nil];
    [self fireEvent:@"singlyServiceDidAuthorize" withObject:nil];
}

- (void)singlyServiceDidFail:(SinglyService *)service
                   withError:(NSError *)error
{
    //    NSDictionary *event = [NSDictionary dictionaryWithObjectAndKeys:@"foo",@"name",nil];
    [self fireEvent:@"singlyServiceDidFail" withObject:nil];

    UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"Login Error"
                                                    message:[error localizedDescription]
                                                   delegate:self cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
    [alert show];
    [self dismissModalViewControllerAnimated:YES];
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
