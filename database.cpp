#include "database.h"

using namespace std;

Point sql_results_p;
string error_message, file_name, sql_results_s;
typedef struct sqlite3_stmt sqlite3_statement;
sqlite3_statement *compiled_sql;
typedef struct sqlite3 sqlite3;
sqlite3 *DataFile;
char sql_statement[1024];
const char *sql_remaining;

// =================================================================================
string Data::Error( )
    {
    return this->error_message;
    }

// =================================================================================
bool Data::Open( )
    {
    if( RunSQL( OPEN ))
        {
        sqlite3_extended_result_codes( this->DataFile, 1 );
        return true;
        }
    else
        {
        return false;
        }
    }

// =================================================================================
bool Data::Get( const string parameter, string value )
    {
    // Open the database
    if( !Open( ))
        {
        return false;
        }
    // Prepare the SQL command
    sprintf( this->sql_statement, "SELECT * FROM one WHERE parameter = \"%s\"", parameter.c_str( ));
    if( !RunSQL( PREPARE ))
        {
        return false;
        }
    // Send the SQL command to the database engine
    if( !RunSQL( RUN ))
        {
        return false;
        }
    value = sql_results_s;
    // Finalize the SQL statement
    if( !RunSQL( FINALIZE ))
        {
        return false;
        }
    return true;
    }
bool Data::Get( const string parameter, const Point value )
    {
    return true;
    }

// =================================================================================
bool Data::Save( const string parameter, const string value )
    {
    // Open the database
    if( !Open( ))
        {
        return false;
        }
    // Prepare the SQL command to delete any previous values
    sprintf( this->sql_statement, "DELETE FROM one WHERE parameter = \"%s\"", parameter.c_str( ));
    if( !RunSQL( PREPARE ))
        {
        return false;
        }
    // Send the SQL command to the database engine
    if( !RunSQL( RUN ))
        {
        return false;
        }
    // Finalize the SQL statement
    if( !RunSQL( FINALIZE ))
        {
        return false;
        }

    // Prepare the SQL command, i.e. compile it
    sprintf( this->sql_statement, "INSERT INTO one ( parameter, value ) VALUES ( \"%s\", \"%s\" )", parameter.c_str( ), value.c_str( ));
    if( !RunSQL( PREPARE ))
        {
        return false;
        }
    // Send the SQL command to the database engine
    if( !RunSQL( RUN ))
        {
        return false;
        }
    // Finalize the SQL statement
    if( !RunSQL( FINALIZE ))
        {
        return false;
        }

    // Close the database
    if( !Close( ))
        {
        return false;
        }
    return true;
    }

// =================================================================================
bool Data::RunSQL( const int function_type )
    {
    this->error_message = "";
    time_features Clock;
    int return_code, time_out = 60;
    do
        {
        return_code = SQLFunction( function_type );
        if( return_code == SQLITE_BUSY )
            {
            time_out -= 1;
            Clock.pause( 1 );
            }
        if( return_code == SQLITE_ROW )
            {
            switch( sqlite3_column_count( this->compiled_sql ))
                {
                case 2:
                    {
                    char *holdthis = (char *)sqlite3_column_text( this->compiled_sql, 1 );
                    this->sql_results_s = string( holdthis );
                    break;
                    }
                case 3:
                    {
                    this->sql_results_p.x = sqlite3_column_int( this->compiled_sql, 1 );
                    this->sql_results_p.y = sqlite3_column_int( this->compiled_sql, 2 );
                    break;
                    }
                }
            return_code = SQLITE_BUSY;
            time_out = 60;
            }
        } while ( return_code == SQLITE_BUSY && time_out > 0 );
    if( return_code != SQLITE_OK &&
            return_code != SQLITE_DONE )
        {
        this->error_message = string( sqlite3_errmsg( this->DataFile ));
        return false;
        }
    return true;
    }

// =================================================================================
int Data::SQLFunction( const int function_type )
    {
    // OpenFunction
    switch( function_type )
        {
        case OPEN:
            return sqlite3_open_v2(
                this->file_name.c_str( ),
                &this->DataFile,
                SQLITE_OPEN_READWRITE,
                NULL
                );
        case CLOSE:
            return sqlite3_close( this->DataFile );
        case PREPARE:
            return sqlite3_prepare_v2( this->DataFile, this->sql_statement, 1024, &this->compiled_sql, &this->sql_remaining );
        case RUN:
            return sqlite3_step( this->compiled_sql );
        case FINALIZE:
            return sqlite3_finalize( this->compiled_sql );
        default:
            {
            return -1;
            }
        }
    }

// =================================================================================
bool Data::Close( )
    {
    return RunSQL( CLOSE );
    }

// =================================================================================
// Class constructor
Data::Data( const string filename )
    {
    // This is the interface between the database and other programs
    // The reason this was separated is to keep the database format separate from the data

    this->file_name = filename;
    this->error_message = "";
    };
