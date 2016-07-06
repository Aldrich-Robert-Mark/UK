#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#include <ctime>
#include <sqlite3.h>
#include <string>
#include <wx/app.h>
#include <wx/filefn.h>
#include <wx/msgdlg.h>

#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/string.h>
#include <wx/wx.h>

#include "point_def.h"
#include "frame_ids.h"

using namespace std;

class Configuration
    {
    public:
        Configuration( wxString program_name );
        bool OK( );
        bool GetBasePath( string base_path );
        bool GetProgramName( string program_name );
        void ResetFrames( );
        void SetProgramName( const string program_name );
        void SetOrigin( const FrameTitle frame_id, const Point point );
        void SetSize( const FrameTitle frame_id, const Point size );
        Point GetOrigin( const FrameTitle frame_id );
        Point GetSize( const FrameTitle frame_id );

    private:
        bool CheckDirectory( const wxString user_data_path, const string directory_name );
        wxString AddFileToPath( const wxString path, const string file, const string extension );

        bool config_ok;
        const wxUniChar slash;
        string config_program_name;
        string config_base_path;
        Point config_origin[ 9 ];
        Point config_size[ 9 ];
    };

#endif
