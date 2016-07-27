#ifndef _GRAPHICS_CPP
#define _GRAPHICS_CPP

#include "graphics.h"

using namespace std;

int button_quantity, window_id, parent_id;
long button_alignment, icon_id, default_button;
string button_1_string, button_2_string, button_3_string;
string default_path;
string frame_image_file_name;
string message_string, message_title;
wxString window_title;

int Graphics::Parent( )
    {
    return this->parent_id;
    }
void Graphics::Parent( const int given_id )
    {
    this->parent_id = given_id;
    }

int Graphics::ID( )
    {
    return this->window_id;
    }
void Graphics::ID( const int given_id )
    {
    this->window_id = given_id;
    }

string Graphics::MessageString( )
    {
    return this->message_string;
    }
void Graphics::MessageString( const string ms )
    {
    this->message_string = ms;
    }

string Graphics::MessageTitle( )
    {
    return this->message_title;
    }
void Graphics::MessageTitle( const string ms )
    {
    this->message_title = ms;
    }

string Graphics::Title( )
    {
    return string( this->window_title.ToAscii( ));
    }
void Graphics::Title( const string ms )
    {
    this->window_title.FromAscii( ms.c_str( ));
    }

int Graphics::Icon( )
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
bool Graphics::Icon( const int ms )
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

void Graphics::ProgramImage( const string name )
    {
    wxString FileName = name;
    wxIcon ImageFile( FileName, wxBITMAP_TYPE_JPEG, -1 );
    }

string Graphics::ButtonText( const int ms )
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
bool Graphics::ButtonText( const int num, const string ms )
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

char Graphics::ButtonAlign( )
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
bool Graphics::ButtonAlign( const char ms )
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

int Graphics::DefaultButton( )
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
bool Graphics::DefaultButton( const int ms )
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

int Graphics::ButtonQuantity( )
    {
    return this->button_quantity;
    }
bool Graphics::ButtonQuantity( const int ms )
    {
    if( ms >= 1 && ms <= 3 )
        {
        this->button_quantity = ms;
        return true;
        }
    return false;
    }

string Graphics::Path( )
    {
    return this->default_path;
    }
void Graphics::Path( const string ms )
    {
    this->default_path = ms;
    }


int Graphics::ShowMessage( )
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

bool Graphics::GetDirectory( string new_path )
    {
    wxDirDialog DD(
        NULL,
        this->message_string.c_str( ),
        this->default_path.c_str( ),
        wxDD_DEFAULT_STYLE );
    if( DD.ShowModal( ) == wxID_OK )
        {
        new_path = DD.GetPath( ).ToAscii( );
        return true;
        }
    return false;
    }

void Graphics::Redraw( )
    {
    // Put code here
    }


// =================================================================================
// Class constructor
Graphics::Graphics( )
    {
    OS Disk;
    this->button_alignment = wxCENTER;
    this->button_1_string = "Yes";
    this->button_2_string = "No";
    this->button_3_string = "Cancel";
    this->button_quantity = 1;
    this->default_button = 0;
    this->default_path = Disk.GetUserDataDir( );
    this->icon_id = wxICON_NONE;
    this->message_string = "";
    this->message_title = "";
    this->window_id = 0;
    this->window_title = "";
    };

#endif
