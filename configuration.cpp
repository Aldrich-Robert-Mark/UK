#include "configuration.h"

bool config_ok = true;
string config_program_name = "\0";
string config_base_path = "\0";
Point config_origin[ 9 ];
Point config_size[ 9 ];

// =================================================================================
wxString Configuration::AddFileToPath( const wxString path, const string file, const string extension )
    {
    // Start with the directory and add the configuration file name to it
    wxString return_string = path;
    const wxUniChar slash = wxFileName::GetPathSeparator( );
    return_string.Append( slash );
    return_string.Append( file.c_str( ));
    return_string.Append( extension.c_str( ));
    return return_string;
    }

// =================================================================================
bool Configuration::GetProgramName( string program_name )
    {
    bool return_code = false;
    if( config_program_name != "\0" )
        {
        program_name = config_program_name;
        return_code = true;
        }
    return return_code;
    }

// =================================================================================
bool Configuration::OK( )
    {
    return config_ok;
    }

// =================================================================================
Point GetOrigin( const FrameTitle frame_id, const Point point )
    {
    return config_origin[ frame_id ];
    }

// =================================================================================
void SetOrigin( const FrameTitle frame_id, const Point point )
    {
    config_origin[ frame_id ] = point;
    }

// =================================================================================
Point GetSize( const FrameTitle frame_id, const Point point )
    {
    return config_size[ frame_id ];
    }

// =================================================================================
void SetSize( const FrameTitle frame_id, const Point point )
    {
    config_size[ frame_id ] = point;
    }

// =================================================================================
bool Configuration::GetBasePath( string base_path )
    {
    base_path = config_base_path;
    return config_ok;
    }

// =================================================================================
bool Configuration::CheckDirectory( wxString user_data_path, const string directory_name )
    {
    wxString working_path = user_data_path;
    const wxUniChar slash = wxFileName::GetPathSeparator( );
    working_path.append( slash );
    working_path.append( directory_name );
    if( !wxDirExists( working_path ))
        {
        // Missing subfolder
        wxString message_string = message_string.Format( _( "Missing data directory:\n%s\nProgram is going to stop." ), working_path );
        wxMessageDialog MissingDir(
            NULL,
            message_string,
            _( "Missing directory problem" ),
            wxCENTER | wxOK | wxICON_HAND, wxDefaultPosition );
        MissingDir.ShowModal( );
        return false;
        }
    return true;
    };

// =================================================================================
// Set all frames to the default settingss
void Configuration::ResetFrames()
    {
    // Reset the origin points
    Point pt;
    pt.x = 0.0;
    pt.y = 0.0;
    config_origin[ TOPLEVEL ] = pt;
    config_origin[ LETTERS ] = pt;
    pt.y = 200.0;
    config_origin[ ARCHIVE_LOCAL_ORIGIN ] = pt;
    pt.x += 120.0;
    pt.y = 0.0;
    config_origin[ ENVELOPES ] = pt;
    pt.x += 120.0;
    config_origin[ ADDRESSING ] = pt;
    pt.y = 200.0;
    config_origin[ OUTGOING ] = pt;
    pt.x += 120.0;
    pt.y = 0.0;
    config_origin[ INCOMING ] = pt;
    pt.y = 200.0;
    config_origin[ ARCHIVE_REMOTE_ORIGIN ] = pt;
    pt.x += 120.0;
    pt.y = 0.0;
    config_origin[ RECEIVED ] = pt;

    // Reset the sizes
    pt.x = 600.0;
    pt.y = 400.0;
    config_size[ TOPLEVEL ] = pt;
    pt.x = 120.0;
    pt.y = 200.0;
    config_size[ LETTERS ] = pt;
    config_size[ ENVELOPES ] = pt;
    config_size[ ADDRESSING ] = pt;
    config_size[ OUTGOING ] = pt;
    config_size[ INCOMING ] = pt;
    config_size[ RECEIVED ] = pt;
    pt.x += 120.0;
    config_size[ ARCHIVE_LOCAL_ORIGIN ] = pt;
    config_size[ ARCHIVE_REMOTE_ORIGIN ] = pt;

    // This is a good place to tell the frames to redraw
    }

// =================================================================================
// Class constructor
Configuration::Configuration( wxString program_name )
    {
    config_program_name = string( program_name.ToAscii( ));
    const wxUniChar slash = wxFileName::GetPathSeparator( );

    // Initialize variables
    wxStandardPaths StandardPaths = wxStandardPaths::Get( );

    // working_path may be adjusted to find the configuration file
    wxString working_path = StandardPaths.GetUserDataDir( );

    // user_data_path will be the final good path
    wxString user_data_path = working_path;

    ResetFrames( );

    string folder_names[8];
    folder_names[0] = "outgoing";
    folder_names[1] = "letters";
    folder_names[2] = "envelopes";
    folder_names[3] = "archive_local_origin";
    folder_names[4] = "archive_remote_origin";
    folder_names[5] = "addressing";
    folder_names[6] = "received";
    folder_names[7] = "incoming";
    int folder_count = 8;

    wxFileName config_file;

    wxString split_volume, *p_split_volume = &split_volume;
    wxString split_path, *p_split_path = &split_path;
    wxString split_name, *p_split_name = &split_name;
    wxString split_ext, *p_split_ext = &split_ext;
    bool split_has_ext, *p_split_has_ext = &split_has_ext;

    wxString ini_file = AddFileToPath( working_path, config_program_name, ".ini" );

    // Check if the data directory is in the standard designated location
    while( !wxFileExists( ini_file ) && config_ok )
        {
        // The configuration file does not exist in the primary location
        wxString message_string = message_string.Format( _( "The %s data files are not found in the normal directory.\n" ), config_program_name );
        message_string.append( _( "If you have the files in a custom location, select \"Other directory\", " ));
        wxMessageDialog not_standard_directory_dialog(
            NULL,
            message_string,
            _( "Missing the data files" ),
            wxCENTER | wxOK | wxCANCEL | wxYES_DEFAULT,
            wxDefaultPosition );
        not_standard_directory_dialog.SetOKLabel( _( "Other directory" ));

        switch( not_standard_directory_dialog.ShowModal( ))
            {
            case wxID_OK:
                {
                // Have not found the configuration directory, so ask for it
                message_string = message_string.Format( _( "Select the directory where the configuration file \"%s.ini\" is:" ), config_program_name );
                wxDirDialog dir_dialog(
                    NULL,
                    message_string,
                    working_path,
                    wxDD_DEFAULT_STYLE );
                if ( dir_dialog.ShowModal( ) == wxID_OK )
                    {
                    user_data_path = ini_file = dir_dialog.GetPath( );
                    ini_file.append( slash );
                    ini_file.append( config_program_name.c_str( ));
                    ini_file.append( ".ini" );
                    }
                else
                    {
                    config_ok = false;
                    }
                break;
                }
            default:
                {
                config_ok = false;
                break;
                }
            }
        }
    if( config_ok )
        {
        // The ini file has been found. Check for proper directories.
        char directory[32];
        int i;
        for( i = 0; i < folder_count; i++ )
            {
            if( !CheckDirectory( user_data_path, folder_names[i] ))
                {
                config_ok = false;
                }
            }
        }
    // The ini file and directories exist. Open the ini file and update the default directory.
    sqlite3 *configuration_file;
    typedef struct sqlite3_stmt sqlite3_statement;
    sqlite3_statement *compiled_sql;
    char sql_statement[1024], *sql = sql_statement;
    char sql_remaining[1024], base_path[64];
    const char *remaining = sql_remaining;
    int return_code;
    const char* sql_next = 0;

    if( config_ok )
        {
        // Open the configuration file
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
            config_ok = false;
            }
        }

    if( config_ok )
        {
        // Prepare the SQL command to Update the base path in the configuration file
        char temp_data_path[1024];
        strcpy( temp_data_path, user_data_path.ToAscii( ));
        sprintf( sql_statement, "UPDATE parameters SET value = \"%s\" WHERE parameter = \"base_path\"", temp_data_path );
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
            config_ok = false;
            }
        }

    if( config_ok )
        {
        // Send the SQL command to the database engine
        return_code = SQLITE_BUSY;
        while( return_code == SQLITE_BUSY )
            {
            return_code = sqlite3_step( compiled_sql );
            if( return_code == SQLITE_BUSY )
                {
                clock_t end_time = 1000 + clock( );
                while( clock( ) <= end_time );
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
            config_ok = false;
            }
        }

    if( config_ok )
        {
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
            config_ok = false;
            }
        }

    // Close the configuration file
    if( configuration_file )
        {
        sqlite3_close( configuration_file );
        }
    config_base_path = string( user_data_path.ToAscii( ));
    };
