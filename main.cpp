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

    Configuration *Config = new Configuration( "1840" );

    // Check the setup
    if( !Config->OK( ))
        {
        return false;
        }

    // Create the main application window
    Graphics *Top = new Graphics( Config );
    Top->Title( Config->ProgramName( ));
    Top->Icon( Config->ProgramImage( ));
    Top->Show( true );
    Top->Position( Config->Position( TOPLEVEL ));
    Top->Size( Config->Size( TOPLEVEL ));

/*
    Graphics *Envelopes = new Graphics( ENVELOPES, Top );
    Envelopes->Title( "Envelopes" );
    Envelopes->Icon( Config->ProgramImage( ));
    Envelopes->Show( true );

    Graphics *Addressing = new Graphics( ADDRESSING, Top );
    Addressing->Title( "Addressing" );
    Addressing->Icon( Config->ProgramImage( ));
    Addressing->Show( true );

    Graphics *Outgoing = new Graphics( OUTGOING, Top );
    Outgoing->Title( "Outgoing" );
    Outgoing->Icon( Config->ProgramImage( ));
    Outgoing->Show( true );

    Graphics *Incoming = new Graphics( INCOMING, Top );
    Incoming->Title( "Incoming" );
    Incoming->Icon( Config->ProgramImage( ));
    Incoming->Show( true );

    Graphics *Received = new Graphics( RECEIVED, Top );
    Received->Title( "Received" );
    Received->Icon( Config->ProgramImage( ));
    Received->Show( true );

    Graphics *ArchiveLocal = new Graphics( ARCHIVE_LOCAL, Top );
    ArchiveLocal->Title( "Archive (local creation)" );
    ArchiveLocal->Icon( Config->ProgramImage( ));
    ArchiveLocal->Show( true );

    Graphics *ArchiveRemote = new Graphics( ARCHIVE_REMOTE, Top );
    ArchiveRemote->Title( "Archive (remote creation)" );
    ArchiveRemote->Icon( Config->ProgramImage( ));
    ArchiveRemote->Show( true );
*/

    // Start the event loop
    return true;
    }
