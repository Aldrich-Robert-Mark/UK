#ifndef _GRAPHICS_INTERFACE_H
#define _GRAPHICS_INTERFACE_H

#include <string>
#include <wx/wx.h>

#include "os.h"

using namespace std;


class Graphics
    {
    private:
        char button_alignment;
        string message_string, message_title;
        string button_1_string, button_2_string, button_3_string;
        string default_path;
        string frame_image_file_name;
        int icon_id;
        int button_quantity, default_button;

    public:
        Graphics( );
        string MessageString( );
        void MessageString( const string ms );

        string MessageTitle( );
        void MessageTitle( const string ms );

        int Icon( );
        bool Icon( const int ms );

        void SetProgramImage( const string ms );

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

        bool GetDirectory( const string ms );
        int ShowMessage( );

        void Redraw( );
    };

#endif

