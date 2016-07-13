#include "database.h"

sqlite3 *configuration_file;
string error_message;
typedef struct sqlite3_stmt sqlite3_statement;
sqlite3_statement *compiled_sql;
char sql_statement[1024], *sql = sql_statement;
char sql_remaining[1024], base_path[64];
const char *remaining = sql_remaining;
const char* sql_next = 0;


// =================================================================================
string Database::DB_Error( )
    {
    return this->error_message;
    }

// =================================================================================
bool Database::DB_Read( const string parameter, const string value )
    {
    return true;
    }
bool Database::DB_Read( const string parameter, const Point value )
    {
    return true;
    }

// =================================================================================
bool Database::DB_Write( const string parameter, const string value )
    {
/*
    // Prepare the SQL command to write to the database
    int return_code;

    sprintf( this->sql_statement, "UPDATE parameters SET value = \"%s\" WHERE parameter = \"%s\"", value.c_str( ), parameter.c_str( ));
    return_code = sqlite3_prepare_v2( this->configuration_file, this->sql_statement, 1024, &this->compiled_sql, &this->remaining );
    if( return_code != SQLITE_OK )
        {
        this->error_message = string( sqlite3_errmsg( this->configuration_file ));
        return false;
        }
    // Send the SQL command to the database engine
    if( sqlite3_step( this->compiled_sql ) != SQLITE_BUSY )
        {
        this->error_message = string( sqlite3_errmsg( this->configuration_file ));
        return false;
        }
    if( sqlite3_finalize( compiled_sql ) != SQLITE_OK )
        {
        this->error_message = string( sqlite3_errmsg( this->configuration_file ));
        return false;
        }
    this->error_message = string( "" );
*/
    return true;
    }

bool Database::DB_Write( const string parameter, const Point value )
    {
    return true;
    }

// =================================================================================
bool Database::DB_Open( const string file_name )
    {
    return true;
/*
        return_code = sqlite3_open( file_name.c_str( ), &this->configuration_file );
        if( return_code != SQLITE_OK || this->configuration_file == string( "" ) )
            {
            error_message = string( sqlite3_errmsg( this->configuration_file ));
            sqlite3_close( this->configuration_file );
            return false;
            }
        error_message = string( "" );
        return true;
*/
    }

// =================================================================================
bool Database::DB_Close( )
    {
    sqlite3_close( this->configuration_file );
    return true;
    }

// =================================================================================
// Class constructor
Database::Database( )
    {
    // This is the interface between the database and other programs
    // The reason this was separated is to keep the database format separate from the data
    };
