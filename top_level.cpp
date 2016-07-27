#include "top_level.h"

using namespace std;

void TopLevel::OnQuit( wxCommandEvent& event )
    {
    // Destroy the level
    Close( );
    }

// Construct top level object (CONSTRUCTOR)
TopLevel::TopLevel( Configuration *config )
    {
    OS Disk;
    Graphics *Screen = new Graphics( );

    // Get configuration information
    Screen->Title( config->ProgramName( ));
    string program_name = config->ProgramName( );
    wxString title;
    title.FromAscii( program_name.c_str( ));

    Create( NULL, wxID_ANY, title );
    Show( true );
    }


// Event table for TopLevel
BEGIN_EVENT_TABLE( TopLevel, wxFrame )
    EVT_MENU( wxID_EXIT, TopLevel::OnQuit )
END_EVENT_TABLE( )

