#ifndef _GRAPHICS_INTERFACE_H
#define _GRAPHICS_INTERFACE_H

#include <string>
#include <wx/wx.h>
#include <wx/gbsizer.h>

#include "identifications.h"
#include "point_def.h"
#include "configuration.h"

using namespace std;


class Graphics : public wxFrame
    {
    public:
        Graphics( Configuration *Config );
        Graphics( const FrameTitle frame_id, wxFrame *parent_window, Configuration *Config );

        string Icon( );
        void Icon( const string file_name );

        wxWindowID ID( );
        void ID( const wxWindowID given_id );

        void Menu( const FrameTitle frame_id );

        string Title( );
        void Title( const string given_title );

        wxPoint P2wxP( const Point ip );
        wxSize P2wxS( const Point ip );

        Point Position( );
        void Position( const Point ip );

        void Redraw( );

        Point Size( );
        void Size( const Point ip );

        // Event handlers
        void OnQuit( wxCommandEvent& event );

    private:
        // Variables
        FrameTitle frame_id;
        string frame_image, window_title;
        wxWindowID window_id, parent_id;

        // Methods

        // This class handles events
        DECLARE_EVENT_TABLE( );
    };

#endif

