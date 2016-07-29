#include "top_level.h"

using namespace std;

void TopLevel::OnQuit( wxCommandEvent& event )
    {
    // Destroy the level
    Close( );
    }

Point TopLevel::Size( )
    {
    Point op;
    int *pix = &op.x, *piy = &op.y;
    GetSize( pix, piy );
    return op;
    }
void TopLevel::Size( const Point ip )
    {
    SetSize( ip.x, ip.y );
    }

Point TopLevel::Position( )
    {
    Point op;
    int *pix = &op.x, *piy = &op.y;
    GetPosition( pix, piy );
    return op;
    }
void TopLevel::Position( const Point ip )
    {
    SetPosition( wxPoint( ip.x, ip.y ));
    }

// Construct top level object (CONSTRUCTOR)
TopLevel::TopLevel( Configuration *config )
    {
    // Create the base window
    Create( NULL, TOPLEVEL, _( config->ProgramName( )));

    // Set the options for the window
    wxIcon set_icon;
    set_icon.LoadFile( config->ProgramImage( ), wxBITMAP_TYPE_JPEG, -1, -1 );
    SetIcon( set_icon );
    Position( config->Origin( TOPLEVEL ));
    Size( config->Size( TOPLEVEL ));

    // Set up the menu system
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append( wxID_EXIT, wxT( "E&xit\tAlt-X" ),
            wxT( "Quit this program" ));
    wxMenuBar *menuBar = new wxMenuBar( );
    menuBar->Append( fileMenu, wxT( "&File" ));
    SetMenuBar( menuBar );

    Show( true );
    }


// Event table for TopLevel
BEGIN_EVENT_TABLE( TopLevel, wxFrame )
    EVT_MENU( wxID_EXIT, TopLevel::OnQuit )
END_EVENT_TABLE( )

