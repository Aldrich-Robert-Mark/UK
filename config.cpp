#include "config.h"
#include "graphics.cpp"
#include "os.cpp"

bool config_ok = true;
string config_program_name = "\0";
string config_base_path = "\0";
string ini_file = "\0";
Point config_origin[ 9 ];
Point config_size[ 9 ];

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
bool Configuration::CheckDirectory( const string working_path )
    {
    OS Disk;
    if( !Disk.DirExists( working_path ))
        {
        // Missing subfolder
        Graphics Screen;
        Screen.MessageString( "Missing data directory:\n" + working_path + "\nProgram is going to stop." );
        Screen.MessageTitle( "Missing the data files" );
        Screen.ButtonAlign( 'C' );
        Screen.Icon( 0 );
        Screen.ButtonText( 1, "Other directory" );
        Screen.ButtonText( 2, "Cancel" );
        Screen.DefaultButton( 1 );
        Screen.ButtonQuantity( 2 );
        Screen.ShowMessage( );
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

    }

// =================================================================================
// Class constructor
Configuration::Configuration( string program_name )
    {
    OS Disk;
    Graphics Screen;

    this->config_program_name = program_name;
    slash = Disk.Slash( );

    // Initialize variables
    string folder_names[] = {
    "letters",
    "envelopes",
    "addressing",
    "outgoing",
    "incoming",
    "received",
    "archive_local_origin",
    "archive_remote_origin" };

    this->ResetFrames( );
    Screen.Redraw( );

    // working_path may be adjusted to find the configuration file
    string working_path = Disk.GetUserDataDir( );

    // user_data_path will be the final good path
    string user_data_path = working_path;

    this->ini_file = working_path + slash + config_program_name + ".ini";

    // Check if the data directory is in the standard designated location
    config_ok = true;

    while( !Disk.FileExists( ini_file ) && config_ok )
        {
        // The configuration file does not exist in the primary location

        Screen.MessageString( "The " + this->config_program_name + " data files are not found in the normal directory.\n" + "If you have the files in a custom location, select \"Other directory\", " );
        Screen.MessageTitle( "Missing the data files"  );
        Screen.ButtonAlign( 'C' );
        Screen.Icon( 0 );
        Screen.ButtonText( 1, "Other directory" );
        Screen.ButtonText( 2, "Cancel" );
        Screen.DefaultButton( 1 );
        Screen.ButtonQuantity( 2 );

        if( Screen.ShowMessage( ) == 1)
            {
            // Have not found the configuration directory, so ask for it
            Graphics Dir;
            Dir.MessageString( "Select the directory where the configuration file \"" + this->config_program_name + ".ini\" is:" );
            Dir.Path( working_path );
            if( Dir.GetDirectory( user_data_path ))
                {
                this->ini_file = user_data_path + slash + config_program_name + ".ini";
                }
            else
                {
                config_ok = false;
                }
            break;
            }
        else
            {
            config_ok = false;
            break;
            }
        }
    if( config_ok )
        {
        // The ini file has been found. Check for proper directories.
        this->config_base_path = user_data_path;
        for( string folder_name : folder_names )
            {
            if( folder_name != this->config_program_name && !CheckDirectory( user_data_path + slash + folder_name ))
                {
                config_ok = false;
                }
            }
        }

    if( config_ok )
        {
        // The ini file and directories exist. Open the ini file and update the default directory.
        Database ConfigurationFile;
        if( !ConfigurationFile.DB_Open( this->ini_file ))
            {
            Screen.MessageString( "The configuration file could not be opened.\n" + ConfigurationFile.DB_Error( ) + "\nThe program will stop." );
            Screen.MessageTitle( "Configuration file problem" );
            Screen.ButtonQuantity( 1 );
            Screen.ButtonText( 1, "OK" );
            Screen.Icon( 2 );
            Screen.ShowMessage( );
            }
        else
            {
            // The configuration file is open.
            // Write the directory to the configuration file.
            if( !ConfigurationFile.DB_Write( string( "base_path" ), this->config_base_path ))
                {
                string message_string = "Could not update the configuration file.\n";
                message_string += "Trying to save the \"base_path\" to \"";
                message_string += this->config_base_path;
                message_string += ".\nThe error message is \"";
                message_string += ConfigurationFile.DB_Error( );
                message_string += "\".";
                Screen.MessageString( message_string );
                Screen.MessageTitle( "Configuration file problem" );
                Screen.ButtonQuantity( 1 );
                Screen.ButtonText( 1, "OK" );
                Screen.Icon( 1 );
                Screen.ShowMessage( );
                }

            // Read the saved data points for the frames
            for( int i; i < 9; i++ )
                {
                // Read the origin points and size for the frames
                string parameter_name;
                for( int j = 0 ; j < 2 ; j++ )
                    {
                    if( j == 0 )
                        {
                        parameter_name = "origin_";
                        }
                    else
                        {
                        parameter_name = "size_";
                        }
                    parameter_name += folder_names[i];
                    if( !ConfigurationFile.DB_Read( parameter_name, this->config_origin[i] ))
                        {
                        char substring[256];
                        string message_string = "Could not read the configuration file.\n";
                        message_string += "Trying to get the \"config_origin[";
                        message_string += folder_names[i];
                        message_string += "]\".\nThe error message is \"";
                        message_string += ConfigurationFile.DB_Error( ).c_str( );
                        message_string += "\".";
                        Screen.MessageString( message_string );
                        Screen.MessageTitle( "Configuration file problem" );
                        Screen.ButtonQuantity( 1 );
                        Screen.ButtonText( 1, "OK" );
                        Screen.Icon( 1 );
                        Screen.ShowMessage( );
                        }
                    }
                }
                ConfigurationFile.DB_Close( );
            }

        };
    };
