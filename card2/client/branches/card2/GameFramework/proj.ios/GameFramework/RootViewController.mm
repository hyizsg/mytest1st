
#import "RootViewController.h"
#include "cocos2dxframework.h"

static int giScreenOrientation = HORIENTATION_LANDSCAPE;
void setScreenOrientation(int orientation) {
    giScreenOrientation = orientation;
}

@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
 
*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    switch (giScreenOrientation) {
        case HORIENTATION_LANDSCAPE:
            return UIInterfaceOrientationIsLandscape(interfaceOrientation);
            break;
        case HORIENTATION_PORTRAIT:
            return UIInterfaceOrientationIsPortrait(interfaceOrientation);
            break;
    }
    return true;
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
//#ifdef __IPHONE_6_0
    switch (giScreenOrientation) {
        case HORIENTATION_LANDSCAPE:
            return UIInterfaceOrientationMaskLandscape;
            break;
        case HORIENTATION_PORTRAIT:
            return UIInterfaceOrientationMaskPortrait;
            break;
    }
    return UIInterfaceOrientationMaskAll;
//#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


@end
