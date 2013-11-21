#import "TiModule.h"
#import <SinglySDK/SinglySDK.h>

#import "TiApp+Singly.h"


@interface SinglyModule : TiModule <SinglyServiceDelegate, NSURLConnectionDataDelegate>
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
