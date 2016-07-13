/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  This is the first of the files required to build the application
 *
 *        Version:  1.0
 *        Created:  05/29/2016 02:03:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mark Aldrich
 *   Organization:  1840
 *
 * =====================================================================================
 */

#include "main.h"
#include "config.cpp"
/*
#include "top_level.cpp"
*/

using namespace std;


// Initialize the application
bool MainProgram::OnInit( )
    {

    wxInitialize( );

    Configuration Config( "1840" );

    // Check the setup
    if( !Config.OK( ))
        {
        return false;
        }
/*
    // Create the main application window
    TopLevelFrame *main_frame = new TopLevelFrame( &Config );

    // Show it
    main_frame->Show( true );
*/
    wxUninitialize( );

    // Start the event loop
    return true;
    }

// Give wxWidgets the means to create a MainProgram object
IMPLEMENT_APP( MainProgram )
