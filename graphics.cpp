#include "graphics.h"
#include <wx/menu.h>
using namespace std;

FrameTitle frame_id;
string frame_image, window_title;
wxWindowID window_id, parent_id;

// =================================================================================
wxWindowID Graphics::ID( )
    {
    return this->window_id;
    }
void Graphics::ID( const wxWindowID given_id )
    {
    this->window_id = given_id;
    }

// =================================================================================
string Graphics::Title( )
    {
    return this->window_title;
    }
void Graphics::Title( const string ms )
    {
    this->window_title = ms;
    wxString title = this->window_title.c_str( );
    SetTitle( title );
    }

// =================================================================================
string Graphics::Icon( )
    {
    return this->frame_image;
    }
void Graphics::Icon( const string file_name )
    {
    this->frame_image = file_name;
    wxString image = this->frame_image.c_str( );
    wxIcon set_icon;
    set_icon.LoadFile( image, wxBITMAP_TYPE_JPEG, -1, -1 );
    SetIcon( set_icon );
    }

void Graphics::Menu( const FrameTitle frame_id )
    {
    // Set up the menu system
    wxMenu *FileMenu = new wxMenu;
    FileMenu->Append( wxID_EXIT, _( "E&xit\tAlt-X" ), _( "Quit this program" ));

    wxMenu *ViewMenu = new wxMenu;
    ViewMenu->Append( ID_LETTERS_WINDOW,        _( "&1. Letters" ),                     _( "Letters window" ));
    ViewMenu->Append( ID_ENVELOPES_WINDOW,      _( "&2. Envelopes" ),                   _( "Envelopes window" ));
    ViewMenu->Append( ID_ADDRESSING_WINDOW,     _( "&3. Addressing" ),                  _( "Addressing window" ));
    ViewMenu->Append( ID_OUTGOING_WINDOW,       _( "&4. Outgoing" ),                    _( "Outgoing window" ));
    ViewMenu->Append( ID_INCOMING_WINDOW,       _( "&5. Incoming" ),                    _( "Incoming window" ));
    ViewMenu->Append( ID_RECEIVED_WINDOW,       _( "&6. Received" ),                    _( "Received window" ));
    ViewMenu->Append( ID_LOCAL_WINDOW,          _( "&7. Archive (local creation)" ),    _( "Archive (local creation) window" ));
    ViewMenu->Append( ID_REMOTE_WINDOW,         _( "&8. Archive (remote creation)" ),   _( "Archive (remote creation) window" ));

    wxMenu *ConfigurationMenu = new wxMenu;
    ConfigurationMenu->Append( RESET_WINDOWS, _( "&Reset Screen" ), _( "Change window layout to factory defaults" ));

    wxMenuBar *TopLevelMenuBar = new wxMenuBar( );
    TopLevelMenuBar->Append( FileMenu, _( "&File" ));
    TopLevelMenuBar->Append( ViewMenu, _( "&View" ));
    TopLevelMenuBar->Append( ConfigurationMenu, _( "&Configure" ));
    SetMenuBar( TopLevelMenuBar );
    }

// =================================================================================
Point Graphics::Size( )
    {
    Point op;
    int *pix = &op.x, *piy = &op.y;
    GetSize( pix, piy );
    return op;
    }
void Graphics::Size( const Point ip )
    {
    SetSize( ip.x, ip.y );
    }

// =================================================================================
Point Graphics::Position( )
    {
    Point op;
    int *pix = &op.x, *piy = &op.y;
    GetPosition( pix, piy );
    return op;
    }
void Graphics::Position( const Point ip )
    {
    SetPosition( wxPoint( ip.x, ip.y ));
    }

// =================================================================================
wxPoint Graphics::P2wxP( const Point ip )
    {
    wxPoint op;
    op.x = ip.x;
    op.y = ip.y;
    return op;
    }
wxSize Graphics::P2wxS( const Point ip )
    {
    wxSize op;
    op.x = ip.x;
    op.y = ip.y;
    return op;
    }

// =================================================================================
void Graphics::Redraw( )
    {
    // Put code here
    }

// =================================================================================
void Graphics::OnQuit( wxCommandEvent& event )
    {
    // Destroy the level
    Close( );
    }

// =================================================================================
// Class constructor
// =================================================================================
Graphics::Graphics( Configuration *Config )
    {
    this->frame_id = TOPLEVEL;

    ID( NewControlId( 1 ));
    Create( NULL, ID( ), this->window_title );

    // Set the options for the frame
    Menu( this->frame_id );

    // Make a panel to cover the entire client area
    wxPanel *TopClientArea = new wxPanel( this, wxID_ANY );
    TopClientArea->SetBackgroundColour( wxColour( wxT( "#44aa44" )));

    // Define a layout in the client area
    wxGridBagSizer* layout = new wxGridBagSizer(0, 0);
    TopClientArea->SetSizer( layout );
    TopClientArea->SetAutoLayout( true );
/*
    Graphics *Letters = new Graphics( LETTERS, this, Config );
    Letters->Title( "Letters" );
    Letters->Icon( Config->ProgramImage( ));
*/
    wxPanel *Letters = new wxPanel( TopClientArea, wxID_ANY, wxDefaultPosition, P2wxS( Config->Size( this->frame_id )));
    Letters->SetBackgroundColour( wxColour( wxT( "#ff0000" )));
    layout->Add( Letters, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    };

Graphics::Graphics( const FrameTitle frame_id, wxFrame *parent_window, Configuration *Config )
    {
    ID( NewControlId( 1 ));
    this->frame_id = frame_id;

    //Create( parent_window, ID( ), this->window_title, P2wxP( Config->Position( this->frame_id )), P2wxS( Config->Size( this->frame_id )));

    // Set the options for the frame
    Position( Config->Position( this->frame_id ));
    Size( Config->Size( this->frame_id ));

/*
    // Set up the menu system
    wxMenu *FileMenu = new wxMenu;
    FileMenu->Append( wxID_CLOSE, _( "&Close\tCtrl-F4" ), _( "Close this window" ));

    wxMenuBar *LevelMenuBar = new wxMenuBar( );
    LevelMenuBar->Append( FileMenu, _( "&File" ));
    SetMenuBar( LevelMenuBar );
*/
    }

// Event table for Graphics
BEGIN_EVENT_TABLE( Graphics, wxFrame )
    EVT_MENU( wxID_EXIT, Graphics::OnQuit )
    EVT_MENU( wxID_CLOSE, Graphics::OnQuit )
END_EVENT_TABLE( )
