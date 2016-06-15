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

#include "configuration.cpp"
#include "primary.cpp"

using namespace std;

GlobalVariables GV;

// Initialize the application
bool MainProgram::OnInit( )
    {

    wxInitialize();

    // Check the setup
    char path[256];
    if( !configuration( GV.GetProgramName( ), path ))
        {
        return false;
        }
    else
        {
        GV.SetDefaultPath( path );
        }

    // Create the main application window
    PrimaryWindow *main_frame = new PrimaryWindow( _( GV.GetProgramName( )));

    // Show it
    main_frame->Show( true );

    wxUninitialize();

    // Start the event loop
    return true;
    }

// Give wxWidgets the means to create a MainProgram object
IMPLEMENT_APP( MainProgram )
