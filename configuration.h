#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#include <string>

#include "os.h"
#include "database.h"
#include "graphics.h"

#include "point_def.h"
#include "identifications.h"

using namespace std;

class Configuration
    {
    public:
        Configuration( string program_name );
        bool OK( );
        string BasePath( );

        string ProgramName( );
        void ProgramName( const string program_name );

        string ProgramImage( );
        void ProgramImage( const string file_name );

        void ResetFrames( );

        void Size( const FrameTitle frame_id, const Point size );
        Point Size( const FrameTitle frame_id );

        void Origin( const FrameTitle frame_id, const Point point );
        Point Origin( const FrameTitle frame_id );

    private:
        bool config_ok;
        string config_program_name;
        string config_base_path;
        string config_database;
        string config_folder_names[ 9 ];
        string config_program_image;
        Point config_origin[ 9 ];
        Point config_size[ 9 ];
    };

#endif
