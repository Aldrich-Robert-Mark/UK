#include <wx/wx.h>

#include "primary.h"

void PrimaryWindow::OnQuit( wxCommandEvent& event ) {
    // Destroy the frame
    Close( );
    }

// Construct frame object (CONSTRUCTOR)
PrimaryWindow::PrimaryWindow( const wxString& title ) : wxFrame( NULL, wxID_ANY, title ) {
    // Set the frame icon
    SetIcon( wxIcon( mondrian_xpm ));

    // Create a menu bar
    wxMenu *file_menu = new wxMenu;

    file_menu->Append( wxID_EXIT, wxT( "E&xit\tAlt-X" ), wxT( "Quit this program" ));

    // Now append the freshly created menu to the menu bar...
    wxMenuBar *MainMenuBar = new wxMenuBar( );
    MainMenuBar->Append( file_menu, wxT( "&File" ));

    // ... and attach this menu bar to the frame
    SetMenuBar( MainMenuBar );

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add( new wxButton( this, -1, "A Really Really Big Button" ), 0, 0,        0 );
    sizer->Add( new wxButton( this, -1, "Tiny Button"                ), 0, wxSHAPED, 0 );
    sizer->SetSizeHints( this );
    SetSizer( sizer );

    }


// Event table for PrimaryWindow
BEGIN_EVENT_TABLE( PrimaryWindow, wxFrame )
    EVT_MENU( wxID_EXIT, PrimaryWindow::OnQuit )
END_EVENT_TABLE( )

