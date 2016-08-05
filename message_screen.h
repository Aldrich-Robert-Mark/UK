#ifndef _MESSAGE_SCREEN_H
#define _MESSAGE_SCREEN_H

#include <string>
#include <wx/wx.h>

#include "os.h"
#include "point_def.h"

using namespace std;


class MessageScreen : public wxFrame
    {
    public:
        MessageScreen( );

        string Message( );
        void Message( const string ms );

        string Title( );
        void Title( const string ms );

        int Icon( );
        bool Icon( const int ms );

        string ButtonText( const int ms );
        bool ButtonText( const int num, const string ms );

        char ButtonAlign( );
        bool ButtonAlign( const char ms );

        int DefaultButton( );
        bool DefaultButton( const int ms );

        int ButtonQuantity( );
        bool ButtonQuantity( const int ms );

        void ProgramImage( const string ms );

        int ShowMessage( );

        string Path( );
        void Path( const string ms );

        wxWindowID ID( );
        void ID( const wxWindowID given_id );

        string GetDirectory( );

        // Event handlers
        void OnQuit( wxCommandEvent& event );

    private:
        // Variables
        int button_quantity;
        long button_alignment, icon_id, default_button;
        string button_1_string, button_2_string, button_3_string;
        string default_path;
        string message_string, message_title;
        wxString window_title;

        // Methods
        Point Position( );
        void Position( const Point ip );
        Point Size( );
        void Size( const Point ip );

        // This class handles events
        DECLARE_EVENT_TABLE( );
    };

#endif

