#import "SinglyModule.h"
#import "TiBase.h"
#import "TiHost.h"
#import "TiUtils.h"

<<<<<<< HEAD
=======

>>>>>>> c0bd84c1776fea63d7c5241d3eb5b505109787f0

@implementation SinglyModule

#pragma Public APIs

/**
 * Tell Singly the app's credentials and start the session.
 */
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


-(id)profiles
{
    return [session profiles];
}


/**
 * Submit a request via the Singly API.
 *
 * @param {NSDictionary} args A javascript object from Titanium including the following properties
 *
 *         urlParams: name+value pairs to be appended to the request URL
 *         postParams: name+value pairs to be POSTed in the HTTP body field.
 *                     If there are postParams, the request will be POSTed as JSON with these params
 *         success: function to be called when the response is loaded
 *
 */
-(void)makeRequest:(id)args
{
    ENSURE_UI_THREAD_1_ARG(args);
    ENSURE_SINGLE_ARG(args, NSDictionary);

    
    id progress = [args objectForKey:@"progress"];
    RELEASE_TO_NIL(progressCallback);
    progressCallback = [progress retain];
    
    id success = [args objectForKey:@"success"];
    RELEASE_TO_NIL(successCallback);
    successCallback = [success retain];
    
    id error = [args objectForKey:@"error"];
    RELEASE_TO_NIL(errorCallback);
    errorCallback = [error retain];
    
    NSString *endPoint = [TiUtils stringValue:[args objectForKey:@"endPoint"]];
    
    NSDictionary *urlParams = [args objectForKey:@"urlParams"];
    
    SinglyRequest *request = [SinglyRequest requestWithEndpoint:endPoint andParameters:urlParams];
    
    NSDictionary *postParams = [args objectForKey:@"postParams"];

    TiBlob *blob = [args objectForKey:@"photo"];

    // need multipart to upload photo
    if (blob) {

        UIImage *photo = [blob image];
        NSData *photoData = UIImageJPEGRepresentation(photo, 1.0);

        
        NSString *boundary = @"0xC00Lb0uNdArY";
        NSString *contentType = [NSString stringWithFormat:@"multipart/form-data; boundary=%@",boundary];

        [request setHTTPMethod: @"POST"];
        [request addValue:contentType forHTTPHeaderField: @"Content-Type"];
        
        
        NSMutableData *postData = [[NSMutableData data] retain];

        // opening boundary
        [postData appendData:[[NSString stringWithFormat:@"--%@\r\n", boundary] dataUsingEncoding:NSUTF8StringEncoding]];
        [postData appendData:[self encodeMultipartFileParam:@"photo" data:photoData filename:@"photo.jpg"]];
        

        for (NSString *key in postParams) {
            
            // begin each with a boundary
            [postData appendData:[[NSString stringWithFormat:@"\r\n--%@\r\n", boundary] dataUsingEncoding:NSUTF8StringEncoding]];
            
            NSString *value = [postParams objectForKey:key];
            
            [postData appendData:[self encodeMultipartParam:key data:value]];
        }

        
        // final boundary
        [postData appendData:[[NSString stringWithFormat:@"\r\n--%@--\r\n", boundary] dataUsingEncoding:NSUTF8StringEncoding]];
        

        [request setHTTPBody:postData];
        
        
        int len = [postData length];
        NSLog([NSString stringWithFormat:@"[INFO] Content-Length: %d", len]);
        [request addValue:[NSString stringWithFormat:@"%d", len] forHTTPHeaderField: @"Content-Length"];
        
    }
    else if (postParams) {
        
        [request setHTTPMethod: @"POST"];
        [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
        
        NSData *requestData = [NSJSONSerialization dataWithJSONObject:postParams options:kNilOptions error:nil];
        
        [request setHTTPBody: requestData];
    }
    

    NSURLConnection *conn = [[NSURLConnection alloc] initWithRequest:request delegate:self];

}



#pragma mark Internal



/**
 * Utility function to encode a file for a multipart POST
 */
- (NSData*)encodeMultipartFileParam:(NSString*)param data:(NSData*)fileData filename:(NSString*)filename
{    
    NSMutableData *postData = [NSMutableData data];
    
    
    [postData appendData:[[NSString stringWithFormat:@"Content-Disposition: form-data; name=\"%@\"; filename=\"%@\"\r\n", param, filename] dataUsingEncoding:NSUTF8StringEncoding]];
    
    [postData appendData:[@"Content-Type: application/octet-stream\r\n\r\n" dataUsingEncoding:NSUTF8StringEncoding]];

    [postData appendData:fileData];
    
    return postData;
}



/**
 * Utility function to encode a normal key/val pair for a multipart POST
 */
- (NSData*)encodeMultipartParam:(NSString*)param data:(NSString*)data
{    
    NSMutableData *postData = [NSMutableData data];
    
    [postData appendData:[[NSString stringWithFormat:@"Content-Disposition: form-data; name=\"%@\"\r\n\r\n", param] dataUsingEncoding:NSUTF8StringEncoding]];
    
    [postData appendData:[data dataUsingEncoding:NSUTF8StringEncoding]];
    
    return postData;
}



/**
 * Utility function to encode a dictionary into a querystring
 *
 * @param {NSDictionary} args The object to be converted to JSON string, then NSData
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




#pragma mark NSURLConnection Delegate Methods

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    // A response has been received, this is where we initialize the instance var you created
    // so that we can append data to it in the didReceiveData method
    // Furthermore, this method is called each time there is a redirect so reinitializing it
    // also serves to clear it
    _responseData = [[[NSMutableData alloc] init] retain];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    // Append the new data to the instance variable you declared
    [_responseData appendData:data];
}

- (NSCachedURLResponse *)connection:(NSURLConnection *)connection
                  willCacheResponse:(NSCachedURLResponse*)cachedResponse {
    // Return nil to indicate not necessary to store a cached response for this connection
    return nil;
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
    NSArray *responseObject = [NSJSONSerialization JSONObjectWithData:_responseData options:NSJSONReadingMutableContainers error:nil];
    
    // this was added so that raw array responses make it back into Titanium
    NSDictionary *resp = [[NSDictionary alloc] initWithObjectsAndKeys:responseObject, @"response", nil];
    
    [self _fireEventToListener:@"success" withObject:resp listener:successCallback thisObject:nil];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {

    [self _fireEventToListener:@"error" withObject:error listener:errorCallback thisObject:nil];

}


- (void)connection:(NSURLConnection *)connection didSendBodyData:(NSInteger)bytesWritten totalBytesWritten:(NSInteger)totalBytesWritten totalBytesExpectedToWrite:(NSInteger)totalBytesExpectedToWrite
{
    NSLog(@"[INFO] didSendBodyData %d %d %d", bytesWritten, totalBytesWritten, totalBytesExpectedToWrite)
    
    /*
    NSDictionary *sendStatus = [[NSDictionary alloc] initWithObjectsAndKeys:
                                 totalBytesWritten, @"sent",
                                 totalBytesExpectedToWrite, @"total",
                                 nil
                                 ];
    [self _fireEventToListener:@"progress" withObject:sendStatus listener:progressCallback thisObject:nil];
*/
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


@end
