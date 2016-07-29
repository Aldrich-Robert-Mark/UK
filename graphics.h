#ifndef _GRAPHICS_INTERFACE_H
#define _GRAPHICS_INTERFACE_H

#include <string>
#include <wx/wx.h>

#include "os.h"

using namespace std;


class Graphics : public wxFrame
    {
    public:
        Graphics( );

        int Parent( );
        void Parent( const int given_id );

        string MessageString( );
        void MessageString( const string ms );

        string MessageTitle( );
        void MessageTitle( const string ms );

        int Icon( );
        bool Icon( const int ms );

        void ProgramImage( const string ms );

        string ButtonText( const int ms );
        bool ButtonText( const int num, const string ms );

        char ButtonAlign( );
        bool ButtonAlign( const char ms );

        int DefaultButton( );
        bool DefaultButton( const int ms );

        int ButtonQuantity( );
        bool ButtonQuantity( const int ms );

        string Path( );
        void Path( const string ms );

        int ID( );
        void ID( const int given_id );

        string Title( );
        void Title( const string given_title );

        int ShowMessage( );
        bool GetDirectory( const string ms );

        void Redraw( );

    private:
        int button_quantity, window_id, parent_id;
        long button_alignment, icon_id, default_button;
        string button_1_string, button_2_string, button_3_string;
        string default_path;
        string frame_image_file_name;
        string message_string, message_title;
        wxString window_title;
    };

#endif

