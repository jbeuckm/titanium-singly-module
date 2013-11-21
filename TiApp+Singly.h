//
//  TiApp+Singly.h
//  singly
//
//  Created by joe on 11/20/13.
//
//

#import "TiApp.h"

#ifndef singly_TiApp_Singly_h
#define singly_TiApp_Singly_h

@interface TiApp (Singly)

- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation;

@end

#endif
