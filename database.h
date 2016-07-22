#ifndef _DATABASE_H
#define _DATABASE_H

#include <iostream>
#include <string>
#include <functional>

#include "time_features.h"
#include "point_def.h"
#include "sqlite3.h"
#include "identifications.h"

using namespace std;

class Data
    {
    public:
        // Functions
        Data( const string filename );
        string Error( );
        bool Get( const string parameter, const string value );
        bool Get( const string parameter, const Point value );
        bool Save( const string parameter, const string value );

    private:
        // Functions
        int SQLFunction( const int function_type );
        bool RunSQL( const int function_type );
        bool Open( );
        bool Close( );

        // Variables
        Point sql_results_p;
        string error_message, file_name, sql_results_s;
        typedef struct sqlite3_stmt sqlite3_statement;
        sqlite3_statement *compiled_sql;
        typedef struct sqlite3 sqlite3;
        sqlite3 *DataFile;
        char sql_statement[1024];
        const char *sql_remaining;
    };

#endif
