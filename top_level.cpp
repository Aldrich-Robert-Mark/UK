#include "top_level.h"

void TopLevel::OnQuit( wxCommandEvent& event )
    {
    // Destroy the level
    Close( );
    }

// Construct top level object (CONSTRUCTOR)
TopLevel::TopLevel( Configuration *config )
    {
    OS Disk;
    Graphics Screen;
    // Get configuration information
    string program_name = config->GetProgramName( );

    // Set the program icon
    Screen.SetProgramImage( config->GetProgramImage( ));

    // Create a menu bar
    wxMenu *file_menu = new wxMenu;

    file_menu->Append( wxID_EXIT, _( "E&xit\tAlt-X" ), _( "Quit this program" ));

    // Now append the freshly created menu to the menu bar...
    wxMenuBar *MainMenuBar = new wxMenuBar( );
    MainMenuBar->Append( file_menu, wxT( "&File" ));

    // ... and attach this menu bar to the frame
    SetMenuBar( MainMenuBar );

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->SetSizeHints( this );
    SetSizer( sizer );

    }


// Event table for TopLevel
BEGIN_EVENT_TABLE( TopLevel, wxFrame )
    EVT_MENU( wxID_EXIT, TopLevel::OnQuit )
END_EVENT_TABLE( )

