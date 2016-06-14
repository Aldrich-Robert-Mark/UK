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

// Initialize the application
bool MainProgram::OnInit( )
    {

    wxInitialize();

    const char *offical_program_name = "1840";

    // Check the setup
    if( !configuration( ))
        {
        return false;
        }

    // Create the main application window
    PrimaryWindow *main_frame = new PrimaryWindow( _( "1840" ));

    // Show it
    main_frame->Show( true );

    wxUninitialize();

    // Start the event loop
    return true;
    }

GlobalVariables::GetProgramName( char *name )
    {
    strcpy( *name, official_program_name );
    }

GlobalVariables::GlobalVariables( )
    {
    char official_program_name[5];
    strcpy( official_program_name, "1840" );
    }

// Give wxWidgets the means to create a MainProgram object
IMPLEMENT_APP( MainProgram )
