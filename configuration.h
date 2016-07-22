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
        string GetBasePath( );
        string GetProgramName( );
        string GetProgramImage( );
        void ResetFrames( );
        void SetProgramName( const string program_name );
        void SetOrigin( const FrameTitle frame_id, const Point point );
        void SetSize( const FrameTitle frame_id, const Point size );
        void SetProgramImage( const string file_name );
        Point GetOrigin( const FrameTitle frame_id );
        Point GetSize( const FrameTitle frame_id );

    private:
        bool config_ok;
        string config_program_name;
        string config_base_path;
        string config_database;
        string folder_names[ 8 ];
        string program_image;
        Point config_origin[ 9 ];
        Point config_size[ 9 ];
    };

#endif
