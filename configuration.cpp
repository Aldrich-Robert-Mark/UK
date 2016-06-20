#include "configuration.h"







bool CreateFolder( wxString working_path )
    {
    if( !wxDirExists( working_path ))
        {
        wxMkDir( working_path, wxPOSIX_USER_READ | wxPOSIX_USER_WRITE | wxPOSIX_USER_EXECUTE );
        if( !wxDirExists( working_path ))
            {
            // Problem creating the default directory
            wxString message_string = message_string.Format( _( "Problem creating the directory\n%s\nYou need to investigate and then retry." ), working_path );
            wxMessageDialog check_installation(
                NULL,
                message_string,
                _( "Directory creation problem" ),
                wxCENTER | wxOK | wxICON_EXCLAMATION, wxDefaultPosition );
            check_installation.ShowModal( );
            return false;
            }
        }
    return true;
    }







bool CreateSubFolders( wxString base_path )
    {
    wxString working_path;

    working_path = base_path;
    working_path.append( wxFileName::GetPathSeparator( ));
    working_path.append( "outgoing" );
    if( !CreateFolder( working_path ))
        {
        return false;
        }
    working_path = base_path;
    working_path.append( wxFileName::GetPathSeparator( ));
    working_path.append( "letters" );
    if( !CreateFolder( working_path ))
        {
        return false;
        }
    working_path = base_path;
    working_path.append( wxFileName::GetPathSeparator( ));
    working_path.append( "envelopes" );
    if( !CreateFolder( working_path ))
        {
        return false;
        }
    working_path = base_path;
    working_path.append( wxFileName::GetPathSeparator( ));
    working_path.append( "addressing" );
    if( !CreateFolder( working_path ))
        {
        return false;
        }
    working_path = base_path;
    working_path.append( wxFileName::GetPathSeparator( ));
    working_path.append( "incoming" );
    if( !CreateFolder( working_path ))
        {
        return false;
        }
    working_path = base_path;
    working_path.append( wxFileName::GetPathSeparator( ));
    working_path.append( "received" );
    if( !CreateFolder( working_path ))
        {
        return false;
        }
    working_path = base_path;
    working_path.append( wxFileName::GetPathSeparator( ));
    working_path.append( "outarchive" );
    if( !CreateFolder( working_path ))
        {
        return false;
        }
    working_path = base_path;
    working_path.append( wxFileName::GetPathSeparator( ));
    working_path.append( "inarchive" );
    if( !CreateFolder( working_path ))
        {
        return false;
        }
    return true;
    }







bool InstallConfiguration( const char *ProgramName, char *DefaultPath )
    {
    // Install the configuration files
    wxChar slash = wxFileName::GetPathSeparator( );
    wxStandardPaths StandardPaths = wxStandardPaths::Get( );

    wxString working_path = StandardPaths.GetUserDataDir( );
    wxString message_string = _( "Are you (re-)installing the program in the standard location?" );
    wxMessageDialog check_installation(
        NULL,
        message_string,
        _( "New Installation" ),
        wxCENTER | wxYES | wxNO | wxCANCEL | wxYES_DEFAULT,
        wxDefaultPosition );
        check_installation.SetYesNoLabels( _( "Standard" ), _( "Custom" ));

    switch( check_installation.ShowModal( ))
        {
        case wxID_YES:
            {
            // Do the install to the standard directory
            if( !wxDirExists( working_path ))
                {
                if( !CreateFolder( working_path ))
                    {
                    return false;
                    }
                }
            if( !CreateSubFolders( working_path ))
                {
                return false;
                }
            }
        case wxID_NO:
            {
            message_string = message_string.Format( _( "Select the directory where the configuration file \"%s.ini\" should be:" ), ProgramName );
            wxDirDialog dir_dialog(
                NULL,
                message_string,
                working_path,
                wxDD_DEFAULT_STYLE );
            if ( dir_dialog.ShowModal( ) == wxID_OK )
                {
                working_path = dir_dialog.GetPath( );
                if( !CreateSubFolders( working_path ))
                    {
                    return false;
                    }
                }
            else
                {
                return false;
                }
            break;
            }
        case wxID_CANCEL:
            {
            return false;
            break;
            }
        default:
            {
std::cout << "default\n";
            break;
            }
        }
    // Now build the default configuration file
    sqlite3 *ConfigurationFile;
    int return_code = 0;
    working_path.append( slash );
    working_path.append( ProgramName );
    working_path.append( ".ini" );
    return_code = sqlite3_open( working_path, &ConfigurationFile );
    if( return_code )
        {
        // Problem creating and opening the configuration file
        wxString message_string = message_string.Format( _( "Problem opening/creating the configuration file\n%s\nError ID # %d\nYou need to investigate and then retry." ), working_path, return_code );
        wxMessageDialog installation(
            NULL,
            message_string,
            _( "Configuration file open/creation problem" ),
            wxCENTER | wxCANCEL | wxICON_EXCLAMATION, wxDefaultPosition );
        check_installation.ShowModal( );
        return false;
        }
    sqlite3_close( ConfigurationFile );
    return true;
    }






bool configuration( const char *ProgramName, char *DefaultPath )
    {
    // Initialize variables
    char program_name[256];
    strcpy( program_name, ProgramName );
    wxStandardPaths StandardPaths = wxStandardPaths::Get( );

    wxFileName config_file;

    wxString split_volume, *p_split_volume = &split_volume;
    wxString split_path, *p_split_path = &split_path;
    wxString split_name, *p_split_name = &split_name;
    wxString split_ext, *p_split_ext = &split_ext;
    bool split_has_ext, *p_split_has_ext = &split_has_ext;

    wxChar slash = wxFileName::GetPathSeparator( );

    wxString working_path = StandardPaths.GetUserDataDir( );;
    wxString user_data_path = StandardPaths.GetUserDataDir( );
    wxString ini_file = user_data_path;
    ini_file.append( slash );
    ini_file.append( split_name );
    ini_file.append( ProgramName );
    ini_file.append( ".ini" );

    // Check if the data directory is in the standard designated location
    while( !wxFileExists( ini_file ))
        {
        // The configuration file does not exist in the primary location
        wxString message_string = message_string.Format( _( "The %s data files are not found in the normal directory.\n" ), ProgramName );
        message_string.append( _( "If you have the files in a custom location, select \"Other directory\", " ));
        message_string.append( _( "if you are (re-)installing the program, select \"Install\"." ));
        wxMessageDialog check_installation(
            NULL,
            message_string,
            _( "Missing the data files" ),
            wxCENTER | wxYES | wxNO | wxCANCEL | wxYES_DEFAULT,
            wxDefaultPosition );
        check_installation.SetYesNoLabels( _( "Other directory" ), _( "Install" ));

        switch( check_installation.ShowModal( ))
            {
            case wxID_YES:
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
                    user_data_path = dir_dialog.GetPath( );
                    user_data_path.append( slash );
                    user_data_path.append( ProgramName );
                    user_data_path.append( ".ini" );
                    }
                else
                    {
                    return false;
                    }
                break;
                }
            case wxID_NO:
                {
                // Re-installing the program
                if( !InstallConfiguration( ProgramName, DefaultPath ))
                    {
                    return false;
                    };
                break;
                }
            case wxID_CANCEL:
                {
                return false;
                break;
                }
            default:
                {
                break;
                }
            }
        }

    return true;
    };


