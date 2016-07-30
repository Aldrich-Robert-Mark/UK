/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Local program to handle secure mail
 *
 *        Version:  0.1
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

using namespace std;

// Implements MainProgram GetApp( )
DECLARE_APP( MainProgram )

// Give wxWidgets the means to create a MainProgram object
IMPLEMENT_APP( MainProgram )

// Initialize the application
bool MainProgram::OnInit( )
    {

    Configuration Config( "1840" );

    // Check the setup
    if( !Config.OK( ))
        {
        return false;
        }

    // Create the main application window
    Graphics *Top = new Graphics( &Config );
    //Graphics TopLevel( &Config );

    // Start the event loop
    return true;
    }
