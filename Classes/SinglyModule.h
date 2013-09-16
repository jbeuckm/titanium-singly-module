#import "TiModule.h"
#import <SinglySDK/SinglySDK.h>

@interface SinglyModule : TiModule <SinglyServiceDelegate, NSURLConnectionDelegate>
{
    SinglySession *session;
    
    KrollCallback *progressCallback;
    KrollCallback *successCallback;
    KrollCallback *errorCallback;
    KrollCallback *cancelCallback;

    NSMutableData *_responseData;
}

-(id)profiles;

@end
