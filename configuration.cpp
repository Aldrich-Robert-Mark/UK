#include "configuration.h"

#include "os.h"
#include "database.h"
#include "graphics.h"

bool    config_ok = true;
string  config_program_name = "";
string  config_base_path = "";
string  config_database = "";
string  config_folder_names[ 9 ];
string  config_program_image = "";
Point   config_origin[ 9 ];
Point   config_size[ 9 ];

// =================================================================================
string Configuration::BasePath( )
    {
    return config_base_path;
    }

// =================================================================================
string Configuration::FolderName( const int level )
    {
    return config_folder_names[ level ];
    }
void Configuration::FolderName( const int level, const string folder_name )
    {
    config_folder_names[ level ] = folder_name;
    }

// =================================================================================
bool Configuration::OK( )
    {
    return config_ok;
    }

// =================================================================================
Point Configuration::Origin( const FrameTitle frame_id )
    {
    return config_origin[ frame_id ];
    }
void Configuration::Origin( const FrameTitle frame_id, const Point point )
    {
    config_origin[ frame_id ] = point;
    }

// =================================================================================
string Configuration::ProgramImage( )
    {
    return config_program_image;
    }
void Configuration::ProgramImage( const string name )
    {
    this->config_program_image = name;
    }

// =================================================================================
string Configuration::ProgramName( )
    {
    return config_program_name;
    }

// =================================================================================
// Set all frames to the default settingss
void Configuration::DefaultFrames()
    {
    // Reset the origin points
    Point pt;
    pt.x = 0.0;
    pt.y = 50.0;
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
Point Configuration::Size( const FrameTitle frame_id )
    {
    return config_size[ frame_id ];
    }
void Configuration::Size( const FrameTitle frame_id, const Point point )
    {
    config_size[ frame_id ] = point;
    }

// =================================================================================
// Class constructor
Configuration::Configuration( string program_name )
    {
    OS Disk;
    Graphics Screen;

    // Initialize variables
    char slash = Disk.Slash( );
    string message_string;

    this->config_program_name = program_name;
    this->config_ok = true;
    this->config_folder_names[ TOPLEVEL ] = ".";
    this->config_folder_names[ LETTERS ] = "letters";
    this->config_folder_names[ ENVELOPES ] = "envelopes";
    this->config_folder_names[ ADDRESSING ] = "addressing";
    this->config_folder_names[ OUTGOING ] = "outgoing";
    this->config_folder_names[ INCOMING ] = "incoming";
    this->config_folder_names[ RECEIVED ] = "received";
    this->config_folder_names[ ARCHIVE_LOCAL_ORIGIN ] = "archive_local_origin";
    this->config_folder_names[ ARCHIVE_REMOTE_ORIGIN ] = "archive_remote_origin";

//    this->ResetFrames( );
    // working_path may be adjusted to find the configuration file
    this->config_base_path = Disk.GetUserDataDir( );

    this->config_database = this->config_base_path + slash + this->config_program_name + ".ini";

    // Check if the data directory is in the standard designated location

    if( !Disk.FileExists( this->config_database ))
        {
        // The configuration file does not exist in the primary location

        Screen.MessageTitle( "Missing the data files" );
        message_string = "The ";
        message_string += this->config_program_name;
        message_string += " data files have not found.\n";
        message_string += "If the files are in a custom location, select \"Other directory\", ";
        Screen.MessageString( message_string );
        Screen.ButtonAlign( 'C' );
        Screen.Icon( 0 );
        Screen.ButtonText( 1, "Other directory" );
        Screen.ButtonText( 2, "Cancel" );
        Screen.DefaultButton( 1 );
        Screen.ButtonQuantity( 2 );

        if( Screen.ShowMessage( ) == 1 )
            {
            // Have not found the configuration directory, so ask for it
            do
                {
                Graphics Dir;
                message_string = "Select the directory where the configuration file \"";
                message_string += this->config_program_name;
                message_string += ".ini\" is:";
                Dir.MessageString( message_string );
                Dir.Path( this->config_base_path );
                if( Dir.GetDirectory( this->config_base_path ))
                    {
                    this->config_database = this->config_base_path + slash + this->config_program_name + ".ini";
                    }
                else
                    {
                    this->config_ok = false;
                    }
                } while( !Disk.FileExists( this->config_database ) && this->config_ok );
            }
        else
            {
            this->config_ok = false;
            }
        }

    if( this->config_ok )
        {
        // Name the image file used for the windows
        ProgramImage( this->config_base_path + slash + this->config_program_name + ".jpg" );
        Screen.ProgramImage( ProgramImage( ));
        }

    if( this->config_ok )
        {
        // The ini file has been found. Check for proper directories.
        for( string folder_name : this->config_folder_names )
            {
            if( !Disk.DirExists( this->config_base_path + slash + folder_name ))
                {
                // Missing subfolder
                Screen.MessageTitle( "Missing the data files" );
                message_string = "Missing data directory:\n";
                message_string += this->config_base_path + slash + folder_name;
                Screen.MessageString( message_string );
                Screen.ButtonAlign( 'C' );
                Screen.Icon( 0 );
                Screen.ButtonText( 1, "OK" );
                Screen.DefaultButton( 1 );
                Screen.ButtonQuantity( 1 );
                Screen.ShowMessage( );
                this->config_ok = false;
                }
            }
        }

    if( this->config_ok )
        {
        // The ini file and directories exist.
        // Open the configuration file and update the default directory.
        Data ConfigurationFile( this->config_database );

        // Write the directory to the configuration file.
        if( !ConfigurationFile.Save( string( "base_path" ), this->config_base_path ))
            {
            Screen.MessageTitle( "Configuration file problem" );
            message_string = "Could not update the configuration file.\n";
            message_string += "Trying to save the \"base_path\" to \"";
            message_string += this->config_base_path;
            message_string += ".\nThe error message is \"";
            message_string += ConfigurationFile.Error( );
            message_string += "\".";
            Screen.MessageString( message_string );
            Screen.ButtonQuantity( 1 );
            Screen.ButtonText( 1, "OK" );
            Screen.Icon( 1 );
            Screen.ShowMessage( );
            }

        // Read the saved data points for the frames
        for( int i = 0; i < 9; i++ )
            {
            // Read the origin points for the frames
            string parameter_name = "origin_" + config_folder_names[i];
            if( !ConfigurationFile.Get( parameter_name, &this->config_origin[i] ))
                {
                Screen.MessageTitle( "Configuration file problem" );
                message_string = "Could not read the configuration file.\n";
                message_string += "Trying to get the \"config_origin[";
                message_string += config_folder_names[i];
                message_string += "]\".\nThe error message is \"";
                message_string += ConfigurationFile.Error( );
                message_string += "\".";
                Screen.MessageString( message_string );
                Screen.ButtonQuantity( 1 );
                Screen.ButtonText( 1, "OK" );
                Screen.Icon( 1 );
                Screen.ShowMessage( );
                this->config_ok = false;
                }
            }
        for( int i = 0; i < 9; i++ )
            {
            // Read the origin points for the frames
            string parameter_name = "size_" + config_folder_names[i];
            if( !ConfigurationFile.Get( parameter_name, &this->config_size[i] ))
                {
                Screen.MessageTitle( "Configuration file problem" );
                message_string = "Could not read the configuration file.\n";
                message_string += "Trying to get the \"config_origin[";
                message_string += config_folder_names[i];
                message_string += "]\".\nThe error message is \"";
                message_string += ConfigurationFile.Error( );
                message_string += "\".";
                Screen.MessageString( message_string );
                Screen.ButtonQuantity( 1 );
                Screen.ButtonText( 1, "OK" );
                Screen.Icon( 1 );
                Screen.ShowMessage( );
                this->config_ok = false;
                }
            }
        }
    };
