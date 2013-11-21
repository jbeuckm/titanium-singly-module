//
//  TiApp+Singly.m
//  singly
//
//  Created by joe on 11/20/13.
//
//

#import "TiApp+Singly.h"
#import <SinglySDK/SinglySDK.h>

@implementation TiApp (Singly)

- (BOOL)application:(UIApplication *)application
openURL:(NSURL *)url
sourceApplication:(NSString *)sourceApplication
annotation:(id)annotation
{
    return [SinglySession.sharedSession handleOpenURL:url];
}

@end

