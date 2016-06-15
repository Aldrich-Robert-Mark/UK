#include "configuration.h"


bool configuration( const char *ProgramName, char *DefaultPath )
    {
    // Initialize variables
    wxStandardPaths StandardPaths = wxStandardPaths::Get( );
    wxString user_data_path = StandardPaths.GetUserDataDir( );

    wxString split_volume, *p_split_volume = &split_volume;
    wxString split_path, *p_split_path = &split_path;
    wxString split_name, *p_split_name = &split_name;
    wxString split_ext, *p_split_ext = &split_ext;
    bool split_has_ext, *p_split_has_ext = &split_has_ext;

    wxChar path_seperator_character = wxFileName::GetPathSeparator( );

    wxFileName working_file;

    wxFileName::SplitPath( user_data_path, p_split_volume, p_split_path, p_split_name, p_split_ext, p_split_has_ext, wxPATH_NATIVE );
    // Check if the data directory is in the standard designated location
    while( !wxDirExists( user_data_path ))
        {
        // The data directory does not exist in the primary location
        wxString message_string = message_string.Format( _( "The %s data files are not found in the normal directory.\n" ), ProgramName );
        message_string.append( _( "If you have the files in a custom location, select \"Other directory\", " ));
        message_string.append( _( "if you are (re-)installing the program, select \"Install\"." ));
        wxMessageDialog chkinstall(
            NULL,
            message_string,
            _( "Missing the data files" ),
            wxCENTRE | wxYES | wxNO | wxCANCEL | wxYES_DEFAULT,
            wxDefaultPosition );
        chkinstall.SetYesNoLabels( _( "Other directory" ), _( "Install" ));

        int process_identification = chkinstall.ShowModal( );

        if( process_identification == wxID_YES )
            {
            // Have not found the configuration directory, so ask for it
            wxString working_path;
            working_path.clear( );
            working_path.append( split_volume );
            working_path.append( split_path );
            working_path.append( wxFILE_SEP_PATH );
            message_string = message_string.Format( _( "Select the directory where the configuration file \"%s.ini\" is:" ), ProgramName );
            wxDirDialog dir_dialog(
                NULL,
                message_string,
                working_path,
                wxDD_DEFAULT_STYLE );
            if ( dir_dialog.ShowModal( ) == wxID_OK )
                {
                wxString path = dir_dialog.GetPath( );
                user_data_path.clear( );
                user_data_path.append( path );
                user_data_path.append( wxFILE_SEP_PATH );
                user_data_path.append( split_name );
wxMessageBox(user_data_path);
                }
            else
                {
                return false;
                }
            }
        if( process_identification == wxID_CANCEL )
            {
            return false;
            }
        }

    return false;
    };
