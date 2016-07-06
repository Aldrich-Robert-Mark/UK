#include <wx/wx.h>
#include "primary.h"
#include "configuration.h"
#include "frame_ids.h"


void PrimaryFrame::pause( float seconds )
    {
    clock_t end_time = seconds * 1000 + clock( );
    while( clock( ) <= end_time );
    }

void PrimaryFrame::OnQuit( wxCommandEvent& event )
    {
    // Destroy the frame
    Close( );
    }

// Construct frame object (CONSTRUCTOR)
PrimaryFrame::PrimaryFrame( Configuration *config )
    {
    // set up the variables
    wxUniChar uc_slash = wxFileName::GetPathSeparator( );
    char c_slash[2];
    string program_name;
    if( !uc_slash.GetAsChar( c_slash )) std::cout << "Problem converting path symbol to character." << std::endl;
    sqlite3 *configuration_file;
    typedef struct sqlite3_stmt sqlite3_statement;
    sqlite3_statement *compiled_sql;
    char sql_statement[1024], ini_file[256];
    const char *sql = sql_statement;
    char sql_remaining[1024];
    const char *remaining = sql_remaining;
    int return_code;
    char* sql_next = 0;

    // Get configuration information
    config->GetProgramName( program_name )

    // Open the configuration file
    strcpy( ini_file, base_path.c_str( ));
    strcat( ini_file, c_slash );
    strcat( ini_file, program_name.c_str) );
    strcat( ini_file, ".ini" );
    return_code = sqlite3_open( ini_file, &configuration_file );
    if( return_code != SQLITE_OK || configuration_file == NULL )
        {
        wxString message_string = message_string.Format( _( "The configuration file could not be opened.\n%s\nThe program will stop." ), sqlite3_errmsg( configuration_file ));
        wxMessageDialog ErrorMessage(
            NULL,
            message_string,
            _( "Configuration file problem" ),
            wxCENTER | wxOK | wxICON_HAND,
            wxDefaultPosition );

        ErrorMessage.ShowModal( );
        sqlite3_close( configuration_file );
        }

    // Prepare the SQL command to Update the base path in the configuration file
    strcpy( base_path, base_path.ToAscii());
    sprintf( sql_statement, "SELECT value FROM parameters WHERE parameter LIKE \"master_window_origin_coord\"" );
    return_code = sqlite3_prepare_v2( configuration_file, sql_statement, 1024, &compiled_sql, &remaining );
    if( return_code != SQLITE_OK )
        {
        wxString message_string = message_string.Format( _( "SQL statement \"%s\" errored.\nThe error message is \"%s\"\nThe program will stop." ), sql, sqlite3_errmsg( configuration_file ));
        wxMessageDialog ErrorMessage(
            NULL,
            message_string,
            _( "Configuration file problem" ),
            wxCENTER | wxOK | wxICON_HAND,
            wxDefaultPosition );

        ErrorMessage.ShowModal( );
        sqlite3_close( configuration_file );
        return false;
        }

    // Send the SQL command to the database engine
    return_code = SQLITE_BUSY;
    clock_t infinite_loop = 30 * 1000 + clock( );
    while( clock( ) <= infinite_loop )
    switch ( return_code = sqlite3_step( compiled_sql ))
        {
        case SQLITE_BUSY:
            {
            pause( 1.0 );
            breeak;
            }
        case SQLITE_ROW:
            {
            // Point format is (x,y) where x and y are int
            Transer value to string object
            use sqlite3 to get value
        case SQLITE_DONE:
            {
            infinite_loop = clock( );
            break;
            }
        default:
            {
            sql::cout << "SQL problem: " << sql_statement << std::endl;
            break;
            }
        }
    if( return_code != SQLITE_DONE )
        {
        wxString message_string = message_string.Format( _( "SQL statement \"%s\" errored.\nThe error message is \"%s\"\nThe program will stop." ), sql, sqlite3_errmsg( configuration_file ));
        wxMessageDialog ErrorMessage(
            NULL,
            message_string,
            _( "Configuration file problem" ),
            wxCENTER | wxOK | wxICON_HAND,
            wxDefaultPosition );

        ErrorMessage.ShowModal( );
        sqlite3_close( configuration_file );
        return false;
        }

    // Clean up the SQL command
    return_code =  sqlite3_finalize( compiled_sql );
    if( return_code != SQLITE_OK )
        {
        wxString message_string = message_string.Format( _( "SQL statement \"%s\" errored.\nThe error message is \"%s\"\nThe program will stop." ), sql, sqlite3_errmsg( configuration_file ));
        wxMessageDialog ErrorMessage(
            NULL,
            message_string,
            _( "Configuration file problem" ),
            wxCENTER | wxOK | wxICON_HAND,
            wxDefaultPosition );

        ErrorMessage.ShowModal( );
        sqlite3_close( configuration_file );
        return false;
        }


    // Close the configuration file
    sqlite3_close( configuration_file );

    // Set the frame icon
    wxString icon_file_name = wxString::FromAscii( base_path );;
    icon_file_name.append( c_slash );
    icon_file_name.append( program_name );
    icon_file_name.append( ".jpeg" );
    wxIcon icon;
    if( !icon.LoadFile( icon_file_name, wxBITMAP_TYPE_JPEG, -1, -1 )) std::cout << "Icon load error." << std::endl;
    SetIcon( icon );

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


// Event table for PrimaryFrame
BEGIN_EVENT_TABLE( PrimaryFrame, wxFrame )
    EVT_MENU( wxID_EXIT, PrimaryFrame::OnQuit )
END_EVENT_TABLE( )

