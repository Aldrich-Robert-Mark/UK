#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#include <string>

#include "point_def.h"
#include "identifications.h"

using namespace std;

class Configuration
    {
    public:
        Configuration( string program_name );
        bool    OK( );
        string  BasePath( );

        string  FrameName( const int level );
        void    FrameName( const int level, const string folder_name );

        string  FolderName( const int level );
        void    FolderName( const int level, const string folder_name );

        string  ProgramImage( );
        void    ProgramImage( const string file_name );

        string  ProgramName( );
        void    ProgramName( const string program_name );

        void    DefaultFrames( );

        Point   Size( const FrameTitle frame_id );
        void    Size( const FrameTitle frame_id, const Point size );

        Point   Origin( const FrameTitle frame_id );
        void    Origin( const FrameTitle frame_id, const Point point );

    private:
        bool   config_ok;
        string config_program_name;
        string config_base_path;
        string config_database;
        string config_folder_names[ 9 ];
        string config_program_image;
        Point  config_origin[ 9 ];
        Point  config_size[ 9 ];
    };

#endif
