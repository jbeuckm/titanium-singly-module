#import "TiModule.h"
#import <SinglySDK/SinglySDK.h>

@interface SinglyModule : TiModule <SinglyServiceDelegate>
{
    SinglySession *session;
    
    KrollCallback *successCallback;
    KrollCallback *cancelCallback;
}

-(id)profiles;

@end
