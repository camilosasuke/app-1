//
//  RoundWindowApp.m
//  axis
//
//  Created by Camilo Sasuke Tsumanuma on 27/09/14.
//
//

#import "_mm.h"
bool on_application_menu_action(const char * pszCommand);int file_put_contents_dup(const char * path, const char * contents);
void file_add_contents_raw(const char * path, const char * psz);
i32 defer_run_system();
u32 __start_system_with_file(const char * pszFileName);
i32 defer_run_system(const char * pszFileName);

i32 defer_run_system(char * * psza, int c);

void system_call_update_app_activated();
void macos_on_app_changed_occlusion_state();

void set_apex_system_as_thread();

@implementation RoundWindowApp


@synthesize windowcontroller;
- (id)init
{

   self = [super init];
   
   m_menu = [[NSMenu alloc] initWithTitle:@"menubar_menu"];
   
   m_menuitema = [[NSMutableArray alloc] init];
   
   m_menuida = [[NSMutableArray alloc] init];
   
   //int iCount = pbridge->_get_notification_area_action_count();
   
   int iCount = 1;
   
   for(int i = 0; i < iCount; i++)
   {
      
      //      char * pszName = NULL;
      //      char * pszId = NULL;
      //      char * pszLabel = NULL;
      //      char * pszAccelerator = NULL;
      //      char * pszDescription = NULL;
      //
      //      pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, i);
      
      char * pszName = strdup("TransparentFxxx");
      char * pszId = strdup("transparent_frame");
      char * pszLabel = strdup("TransparentFxxx");
      char * pszAccelerator = strdup("TransparentFxxx");
      char * pszDescription = strdup("TransparentFxxx");
      NSString * strTitle = NULL;
      
      NSString * strId = NULL;
      
      NSMenuItem * item = NULL;
      
      if(strcasecmp(pszName, "separator") == 0)
      {
         
         strTitle = [[NSString alloc] initWithUTF8String: pszName];
         
         strId = [[NSString alloc] initWithUTF8String: pszName];
         
         item = [NSMenuItem separatorItem];
         
      }
      else
      {
         
         strTitle = [[NSString alloc] initWithUTF8String: pszName];
         
         strId = [[NSString alloc] initWithUTF8String: pszId];
         
         item = [[NSMenuItem alloc] initWithTitle:  strTitle action: @selector(play:) keyEquivalent:@"" ];
         
      }
      
      [item setTarget:self];
      
      [m_menu addItem:item];
      
      [m_menuitema addObject: item];
      
      [m_menuida addObject: strId];
      
      if(pszName) free(pszName);
      if(pszId) free(pszId);
      if(pszLabel) free(pszLabel);
      if(pszAccelerator) free(pszAccelerator);
      if(pszDescription) free(pszDescription);
   }
   
   [m_menu setDelegate:self];
   

      [[[NSWorkspace sharedWorkspace] notificationCenter]
       addObserver:self
       selector:@selector(applicationActivity:)
       name:NSWorkspaceActiveSpaceDidChangeNotification
       object:nil];
   
//   
//   [[[NSWorkspace sharedWorkspace] notificationCenter]
//    addObserver:self
//    selector:@selector(applicationDidChangeOcclusionState:)
//    name:NSApplicationDidChangeOcclusionStateNotification
//    object:nil];
   return self;
}

-(void)applicationActivity:(NSNotification *)notification
{
   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
   
   NSString * strName = app.localizedName;
   //if([ isEqualToString:@"ScreenSaverEngine"])
   {
      printf("NOTIFICATION: %s", [strName UTF8String]);

      // Your code here
   }
}


- (void)play:(id)sender
{
   
   NSMenuItem * pitem = (NSMenuItem *) sender;
   
   for(int i = 0; i < [m_menuitema count]; i++)
   {
      
      if(pitem == [m_menuitema objectAtIndex:i])
      {
         
         const char * psz = [[m_menuida objectAtIndex:i] UTF8String];
         
         //m_pbridge->notification_area_action(psz);
         
         on_application_menu_action(psz);
         
         return;
         
      }
      
   }
   
}

- (void)on_command:(id)sender
{
   
   NSMenuItem * pitem = (NSMenuItem *) sender;
   
   NSString * str = (NSString *)[pitem representedObject];
if(str != nil)
{
         const char * psz = [str UTF8String];
         
         //m_pbridge->notification_area_action(psz);
         
         on_application_menu_action(psz);
         
         return;
         
      //}
      
   }
   
}
- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
NSAppleEventManager *appleEventManager = [NSAppleEventManager sharedAppleEventManager];// 1
[appleEventManager setEventHandler:self andSelector:@selector(handleGetURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
   
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
   
   set_apex_system_as_thread();
   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", e_message_box_ok);
   
   defer_run_system();
   
}


- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
{
   
   //MessageBox(NULL, "applicationShouldHandleReopen", "applicationShouldHandleReopen", e_message_box_ok);
   
   system_call_update_app_activated();

   return NO;
   
}

- (void)applicationDidChangeOcclusionState:(NSNotification *)notification
{
   
   //macos_on_app_changed_occlusion_state();
   
}


- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender
{
   
   file_put_contents_dup("/eco/001.txt", "applicationOpenUntitledFile");
   //MessageBox(NULL, "applicationOpenUntitledFile", "applicationOpenUntitledFile", e_message_box_ok);
   
   defer_run_system();
   
   //__start_system_with_file(NULL);
   
   return YES;
   
}



- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
{
   
   file_put_contents_dup("/eco/002.txt", "applicationOpenFile");
   file_put_contents_dup("/eco/003.txt", [filename UTF8String]);

   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   defer_run_system([filename UTF8String]);
   
   return true;
   
}



- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames
{
   
   unsigned long ulCount = [filenames count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      char * psz = strdup([[filenames objectAtIndex:ul] UTF8String]);
      
      psza[ul] = psz;
      
   }
   
   defer_run_system(psza, (int) ulCount);
   
   
}
- (void)application:(NSApplication *)application open:(NSURL * )url
{
   file_put_contents_dup("/eco/006.txt", "open");
   file_add_contents_raw("/eco/006.txt", [[url absoluteString] UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   defer_run_system([[url absoluteString] UTF8String]);
}

- (BOOL)application:(id)sender
  openFileWithoutUI:(NSString *)filename;
{
   file_put_contents_dup("/eco/007.txt", "openFileWithoutUI");
   file_add_contents_raw("/eco/007.txt", [filename UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   defer_run_system([filename UTF8String]);
}

- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls
{
   unsigned long ulCount = [urls count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      char * psz = strdup([[[urls objectAtIndex:ul] absoluteString] UTF8String]);
      
      psza[ul] = psz;
      
   }
   
   defer_run_system(psza, (int) ulCount);
   
   

}


//- (void)sendEvent:(NSEvent *)theEvent
//{
//
//   /*
//   
//   char szEvent[128];
//   
//   ·zero(szEvent);
//   
//   if([theEvent type] == NSLeftMouseDown)
//   {
//   
//      strcpy(szEvent, "NSLeftMouseDown");
//      
//   }
//   else if([theEvent type] == NSLeftMouseUp)
//   {
//     
//      strcpy(szEvent, "NSLeftMouseUp");
//      
//   }
//   
//   if(strlen(szEvent) > 0)
//   {
//   
//      char szEventCopy[128];
//   
//      strcpy(szEventCopy, szEvent);
//      
//      printf("\n%s", szEventCopy);
//      
//   }
//   
//   */
//   
//   [super sendEvent:theEvent];
//   
//}
- (void)handleGetURLEvent:(NSAppleEventDescriptor *)event
           withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
   
   // Extract the URL from the Apple event and handle it here.
   NSString* url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
   
   defer_run_system([url UTF8String]);
   
}
-(NSMenu *) applicationDockMenu:(NSApplication*)sender
{

   
   return m_menu;
   
}

//[appDelegate->m_menu setDelegate:NSApp];


@end


void ns_create_main_menu()
{
   
   
   id menuMain = [NSMenu alloc];
   
   {
      
      id menuitemApp = [NSMenuItem alloc];
      
      [menuMain addItem: menuitemApp];
      
      id menuApp = [NSMenu alloc];
      
      [menuitemApp setSubmenu: menuApp];
      
      id strAppName = [[NSProcessInfo processInfo] processName];
      
      id strQuitTitle = [[_("Quit") stringByAppendingString: @" "] stringByAppendingString: strAppName];
      
      id menuitemQuit = [[NSMenuItem alloc] initWithTitle:strQuitTitle
                                                   action:@selector(terminate:) keyEquivalent:@"q"];
      
      [menuApp addItem: menuitemQuit];
      
   }
   
   {
      
      id menuitemView = [NSMenuItem alloc];
      
      [menuMain addItem: menuitemView];
      
      id menuView = [[NSMenu alloc] initWithTitle:_("View")];
      
      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
      
      [menuitemView setSubmenu: menuView];
      
      id strFxxTitle = _("Trasparentt(snowballeffect_smallerror>>>)Fxx");
      
      NSMenuItem * menuitemFxx = [[NSMenuItem alloc] initWithTitle:strFxxTitle
                                                            action:@selector(on_command:) keyEquivalent:@"f"];
      
      [menuitemFxx setRepresentedObject: @"transparent_frame"];
      
      [menuView addItem: menuitemFxx];
      
   }
   
   [NSApp setMainMenu:menuMain];
   
   
}


void ns_application_main(int argc, char *argv[], const char * pszCommandLine)
{
   
   NSApplication * application = [NSApplication sharedApplication];
   
   RoundWindowApp * appDelegate = [[RoundWindowApp alloc] init];
   
   [application setDelegate:appDelegate];
   
   
   
   //[m_statusitem setEnabled:YES];

   
   [NSApplication sharedApplication];
   
   bool bNoDock = strstr(pszCommandLine, " no_dock") != NULL;
   
   if(bNoDock)
   {
      
      nsapp_activation_policy_accessory();
      
   }
//   else
//   {
//      
//      nsapp_activation_policy_regular();
//      
//   }
   

   [NSApp activateIgnoringOtherApps:YES];
   
   [NSApp run];
   
}

