#import "TiModule.h"
#import <SinglySDK/SinglySDK.h>

@interface SinglyModule : TiModule <SinglyServiceDelegate, NSURLConnectionDataDelegate>
{
    SinglySession *session;
    
    NSMutableDictionary *progressCallbacks;
    NSMutableDictionary *errorCallbacks;
    NSMutableDictionary *successCallbacks;

    NSMutableData *_responseData;
}

-(id)profiles;

@end
