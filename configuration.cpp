#include "configuration.h"


bool CheckDirectory( wxString user_data_path, const char *directory_name )
    {
    wxChar slash = wxFileName::GetPathSeparator( );

    wxString working_path = user_data_path;
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
    }






bool configuration( const char *ProgramName, char *DefaultPath )
    {
    // Initialize variables
    char program_name[256];
    strcpy( program_name, ProgramName );
    wxStandardPaths StandardPaths = wxStandardPaths::Get( );

    const char *folder_names[8];
    folder_names[0] = "outgoing";
    folder_names[1] = "letters";
    folder_names[2] = "envelopes";
    folder_names[3] = "archive_local";
    folder_names[4] = "archive_remote";
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

    wxChar slash = wxFileName::GetPathSeparator( );

    wxString working_path = StandardPaths.GetUserDataDir( );;
    wxString ini_file = StandardPaths.GetUserDataDir( );
    wxString user_data_path = ini_file;
    ini_file.append( slash );
    ini_file.append( ProgramName );
    ini_file.append( ".ini" );

    // Check if the data directory is in the standard designated location
    while( !wxFileExists( ini_file ))
        {
        // The configuration file does not exist in the primary location
        wxString message_string = message_string.Format( _( "The %s data files are not found in the normal directory.\n" ), ProgramName );
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
                message_string = message_string.Format( _( "Select the directory where the configuration file \"%s.ini\" is:" ), ProgramName );
                wxDirDialog dir_dialog(
                    NULL,
                    message_string,
                    working_path,
                    wxDD_DEFAULT_STYLE );
                if ( dir_dialog.ShowModal( ) == wxID_OK )
                    {
                    user_data_path = ini_file = dir_dialog.GetPath( );
                    ini_file.append( slash );
                    ini_file.append( ProgramName );
                    ini_file.append( ".ini" );
                    }
                else
                    {
                    return false;
                    }
                break;
                }
            default:
                {
                return false;
                break;
                }
            }
        }
    // The ini file has been found. Check for proper directories.
    char directory[32];
    int i;
    for( i = 0; i < folder_count; i++ )
        {
        if( !CheckDirectory( user_data_path, folder_names[i] ))
            {
            return false;
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
        return false;
        }
    strcpy( base_path, user_data_path.ToAscii());
    sprintf( sql_statement, "UPDATE parameters SET value = \"%s\" WHERE parameter = \"base_path\"", base_path );
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
        sqlite3_close(configuration_file);
        return false;
        }
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
        sqlite3_close(configuration_file);
        return false;
        }
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
        sqlite3_close(configuration_file);
        return false;
        }


    sqlite3_close(configuration_file);
    return true;
    };


