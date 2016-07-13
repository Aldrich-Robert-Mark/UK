#ifndef _DATABASE_H
#define _DATABASE_H

#include <sqlite3.h>
#include <string>

#include "point_def.h"

using namespace std;

class Database
    {
    public:
        Database( );
        string DB_Error( );
        bool DB_Read( const string parameter, const string value );
        bool DB_Read( const string parameter, const Point value );
        bool DB_Write( const string parameter, const string value );
        bool DB_Write( const string parameter, const Point value );
        bool DB_Open( const string file_name );
        bool DB_Close( );

    private:
        sqlite3 *configuration_file;
        string error_message;
        typedef struct sqlite3_stmt sqlite3_statement;
        sqlite3_statement *compiled_sql;
        char sql_statement[1024], *sql = sql_statement;
        char sql_remaining[1024], base_path[64];
        const char *remaining = sql_remaining;
        const char* sql_next = 0;
    };

#endif
