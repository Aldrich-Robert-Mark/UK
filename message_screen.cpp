#include "message_screen.h"

using namespace std;

int button_quantity;
long button_alignment, icon_id, default_button;
string button_1_string, button_2_string, button_3_string;
string default_path;
string message_string, message_title;


// =================================================================================
string MessageScreen::Message( )
    {
    return this->message_string;
    }
void MessageScreen::Message( const string ms )
    {
    this->message_string = ms;
    }

// =================================================================================
string MessageScreen::Title( )
    {
    return this->message_title;
    }
void MessageScreen::Title( const string ms )
    {
    this->message_title = ms;
    }

// =================================================================================
int MessageScreen::Icon( )
    {
    switch( this->icon_id )
        {
        case wxICON_NONE:
            {
            return 0;
            }
        case wxICON_WARNING:
            {
            return 1;
            }
        case wxICON_ERROR:
            {
            return 2;
            }
        case wxICON_QUESTION:
            {
            return 3;
            }
        case wxICON_INFORMATION:
            {
            return 4;
            }
        case wxICON_AUTH_NEEDED:
            {
            return 5;
            }
        }
    return -1;
    }
bool MessageScreen::Icon( const int ms )
    {
    switch( ms )
        {
        case 0:
            {
            this->icon_id = wxICON_NONE;
            return true;
            }
        case 1:
            {
            this->icon_id = wxICON_WARNING;
            return true;
            }
        case 2:
            {
            this->icon_id = wxICON_ERROR;
            return true;
            }
        case 3:
            {
            this->icon_id = wxICON_QUESTION;
            return true;
            }
        case 4:
            {
            this->icon_id = wxICON_INFORMATION;
            return true;
            }
        case 5:
            {
            this->icon_id = wxICON_AUTH_NEEDED;
            return true;
            }
        }
    return false;
    }

// =================================================================================
void MessageScreen::ProgramImage( const string name )
    {
    wxString FileName = name;
    wxIcon ImageFile( FileName, wxBITMAP_TYPE_JPEG, -1 );
    }

// =================================================================================
string MessageScreen::ButtonText( const int ms )
    {
    switch( ms )
        {
        case 1:
            {
            return this->button_1_string;
            }
        case 2:
            {
            return this->button_2_string;
            }
        case 3:
            {
            return this->button_3_string;
            }
        default:
            {
            return "";
            }
        }
    return "";
    }
bool MessageScreen::ButtonText( const int num, const string ms )
    {
    switch( num )
        {
        case 1:
            {
            this->button_1_string = ms;
            return true;
            }
        case 2:
            {
            this->button_2_string = ms;
            return true;
            }
        case 3:
            {
            this->button_3_string = ms;
            return true;
            }
        default:
            {
            return false;
            }
        }
    return false;
    }

// =================================================================================
char MessageScreen::ButtonAlign( )
    {
    switch( this->button_alignment )
        {
        case wxLEFT:
            {
            return 'L';
            }
        case wxRIGHT:
            {
            return 'R';
            }
        case wxCENTER:
            {
            return 'C';
            }
        default:
            {
            return ' ';
            }
        }
    return ' ';
    }
bool MessageScreen::ButtonAlign( const char ms )
    {
    switch( toupper( ms ))
        {
        case 'L':
            {
            this->button_alignment = wxLEFT;
            return true;
            }
        case 'C':
            {
            this->button_alignment = wxCENTER;
            return true;
            }
        case 'R':
            {
            this->button_alignment = wxRIGHT;
            return true;
            }
        default:
            return false;
        }
    return false;
    }

// =================================================================================
int MessageScreen::DefaultButton( )
    {
    switch( this->default_button )
        {
        case -1:
            {
            return -1;
            }
        case wxYES_DEFAULT:
            {
            return 1;
            }
        case wxNO_DEFAULT:
            {
            return 2;
            }
        case wxCANCEL_DEFAULT:
            {
            return 3;
            }
        }
    }
bool MessageScreen::DefaultButton( const int ms )
    {
    switch( ms )
        {
        case -1:
            {
            this->default_button = -1;
            return true;
            }
        case 1:
            {
            this->default_button = wxYES_DEFAULT | wxOK_DEFAULT;
            return true;
            }
        case 2:
            {
            this->default_button = wxNO_DEFAULT;
            return true;
            }
        case 3:
            {
            this->default_button = wxCANCEL_DEFAULT;
            return true;
            }
        }
    return false;
    }

// =================================================================================
int MessageScreen::ButtonQuantity( )
    {
    return this->button_quantity;
    }
bool MessageScreen::ButtonQuantity( const int ms )
    {
    if( ms >= 1 && ms <= 3 )
        {
        this->button_quantity = ms;
        return true;
        }
    return false;
    }

// =================================================================================
string MessageScreen::GetDirectory( )
    {
std::cout << "Start looking at \"" << this->default_path.c_str() << "\"\n";
    wxDirDialog DD(
        NULL,
        this->message_string.c_str( ),
        this->default_path.c_str( ),
        wxDD_DEFAULT_STYLE );
    if( DD.ShowModal( ) == wxID_OK )
        {
        wxString chosen = DD.GetPath( );
        char chosen_char[256];
        strcpy( chosen_char, chosen.ToAscii( ));
        return (string)chosen_char;
        }
    return "";
    }

// =================================================================================
string MessageScreen::Path( )
    {
    return this->default_path;
    }
void MessageScreen::Path( const string ms )
    {
std::cout << "Screen path set to \"" << ms << "\"\n";
    this->default_path = ms;
    }

// =================================================================================
int MessageScreen::ShowMessage( )
    {
    long attributes = this->button_alignment | this->icon_id;
    switch( this->button_quantity )
        {
        case 1:
            {
            attributes = attributes | wxOK;
            break;
            }
        case 2:
            {
            attributes = attributes | wxYES_NO;
            break;
            }
        case 3:
            {
            attributes = attributes | wxCANCEL;
            break;
            }
        }
    if( this->default_button != -1 )
        {
        attributes = attributes | this->default_button;
        }

    wxMessageDialog MD(
        NULL,
        this->message_string.c_str( ),
        this->message_title.c_str( ),
        attributes,
        wxDefaultPosition );
    switch( this->button_quantity )
        {
        case 1:
            {
            MD.SetOKLabel( this->button_1_string.c_str( ));
            }
        case 2:
            {
            MD.SetYesNoLabels( this->button_1_string.c_str( ), this->button_2_string.c_str( ));
            }
        case 3:
            {
            MD.SetYesNoCancelLabels( this->button_1_string.c_str( ), this->button_2_string.c_str( ), this->button_3_string.c_str( ));
            }
        }
    switch( MD.ShowModal( ))
        {
        case wxID_OK:
        case wxID_YES:
            {
            return 1;
            }
        case wxID_NO:
            {
            return 2;
            }
        case wxID_CANCEL:
            {
            return 3;
            }
        }
    return -1;
    };

// =================================================================================
void MessageScreen::OnQuit( wxCommandEvent& event )
    {
    // Destroy the level
    Close( );
    }

// =================================================================================
// Class constructor
MessageScreen::MessageScreen( )
    {
    OS Disk;
    this->button_alignment = wxCENTER;
    this->button_1_string = "Yes";
    this->button_2_string = "No";
    this->button_3_string = "Cancel";
    this->button_quantity = 1;
    this->default_button = 0;
    this->default_path = Disk.UserDataDir( );
    this->icon_id = wxICON_NONE;
    this->message_string = "";
    this->message_title = "";
    };

// Event table for MessageScreen
BEGIN_EVENT_TABLE( MessageScreen, wxFrame )
    EVT_MENU( wxID_EXIT, MessageScreen::OnQuit )
END_EVENT_TABLE( )
