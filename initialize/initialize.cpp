////////////////////////////////////////////////////////////////////////////////////
int check_directory_structure( Configuration config_db )
    {
    // This routine checks for proper directory structure

    char *test_directory;
    int i, return_code = 0;


    // The "letters" directory should hold original documents
    if( return_code == 0 )
        {
        return_code = make_directory( config_db.base_path, "letters" );
        }

    // The "envelopes" directory should hold unused envelopes
    if( return_code == 0 )
        {
        return_code = make_directory( config_db.base_path, "envelopes" );
        }

    // The "working" directory should hold anything in the process of going out
    if( return_code == 0 )
        {
        return_code = make_directory( config_db.base_path, "working" );
        }

    // The "outgoing" directory should hold things ready to send
    if( return_code == 0 )
        {
        return_code = make_directory( config_db.base_path, "outgoing" );
        }

    // The "incoming" directory should hold things received but not processed
    if( return_code == 0 )
        {
        return_code = make_directory( config_db.base_path, "incoming" );
        }

    // The "opened" directory should hold things received and processed
    if( return_code == 0 )
        {
        return_code = make_directory( config_db.base_path, "opened" );
        }

    return return_code;
    }

////////////////////////////////////////////////////////////////////////////////////
int initialize( char *base_directory, Configuration config_db )
    {

    char *test_string;
    int i, return_code = 0, divider_point = 0, base_file_pointer = 0;

    test_string = malloc( sizeof( base_directory ));

    // Step through the directory given and separate the path from the program file name
    base_file_pointer = 0;
    for( i = 0; i < strlen( base_directory ); i++ )
        {
        if( base_directory[i] == PATH_SEPARATOR )
            {
            base_file_pointer = 0;
            strncpy( config_db.base_path, base_directory, i + 1 );
            }
        else
            {
            test_string[base_file_pointer] = base_directory[i];
            test_string[++base_file_pointer] = 0;
            }
        }

    // Step through the base file name to get any file extension
    for( i = 0; i < strlen( test_string ); i++ )
        {
        if( test_string[i] == '.' )
            {
            base_file_pointer = 0;
            strncpy( config_db.base_file, test_string, i );
            }
        }

    // Get the configuration values
    return_code = read_configuration( config_db );

    // Check the directory structure
    if( return_code == 0 )
        {
        return_code = check_directory_structure( config_db );
        }

    free( test_string );

    return return_code;
    }

////////////////////////////////////////////////////////////////////////////////////
int make_directory( char *base_path, char *directory_name )
    {
    // Make the indicated directory structure

    char *test_directory;
    int return_code = 0;
    struct stat test_result;

    test_directory = malloc( sizeof( base_path ) + sizeof( directory_name ) + 2 );

    if( strlen( base_path ) > 0 )
        {
        // If the base_path is not empty, we need to add the character between the path and the directory name
        sprintf( test_directory, "%s%c%s", base_path, PATH_SEPARATOR, directory_name );
        }
    else
        {
        sprintf( test_directory, "%s", directory_name );
        }
    if( stat( test_directory, &test_result ) < 0 )
        {
        if( mkdir( test_directory, 0777 ) != 0 )
            {
            return_code = error_list( 1, test_directory );
            }
        }
    else
        {
        if( !( S_ISDIR( test_result.st_mode )))
            {
            return_code = error_list( 2, test_directory );
            }
        }

    free( test_directory );
    return return_code;
    }

////////////////////////////////////////////////////////////////////////////////////
int read_configuration( Configuration config_data )
    {
    // Make and/or read the configuration file/data

    char *db_name, *sql_statement;
    const char *remaining_sql;
    int rc, return_code = 0, found_key_file_location = 0;
    sqlite3 *db;
    sqlite3_stmt *compiled_sql;
    struct stat test_result;

    // Allocate memory for the strings
    db_name = malloc( sizeof( config_data.base_path ) + sizeof( config_data.base_file ) + 6 );
    sprintf( db_name, "%s%s.ini", config_data.base_path, config_data.base_file );
    sql_statement = malloc( sizeof( char ) * 1024 );

    // Open (or create) the database
    rc = sqlite3_open( db_name, &db );
    if( rc != SQLITE_OK )
        {
        return_code = sql_error( rc );
        }
    else
        {
        strcpy( sql_statement, "CREATE TABLE IF NOT EXISTS configuration ( parameter TEXT, value TEXT )" );
        rc = sqlite3_prepare_v2( db, sql_statement, -1, &compiled_sql, &remaining_sql );
        if( rc != SQLITE_OK && rc != SQLITE_DONE )
            {
            return_code = sql_error( rc );
            }
        else
            {
            rc = sqlite3_step( compiled_sql );
            if( rc != SQLITE_OK && rc != SQLITE_DONE )
                {
                return_code = sql_error( rc );
                }
            }
        rc = sqlite3_finalize( compiled_sql );
        if( return_code == 0 && rc != SQLITE_OK && rc != SQLITE_DONE )
            {
            return_code = sql_error( rc );
            }
        }

    // Read the table and put it in the configuration struct
    if( return_code == 0 )
        {

        strcpy( sql_statement, "SELECT value FROM configuration WHERE parameter = 'key_file_location'" );
        rc = sqlite3_prepare_v2( db, sql_statement, -1, &compiled_sql, &remaining_sql );

        // Look for the location of the key file
        found_key_file_location = 1;
        do
            {
            rc = sqlite3_step( compiled_sql );
            if( rc == SQLITE_ROW )
                {
                strcpy( config_data.key_file_location, sqlite3_column_text( compiled_sql, 0 ));
                found_key_file_location = 0;
                }
            else
                {
                strcpy( config_data.key_file_location, config_data.base_path );
                }
            } while( rc == SQLITE_ROW );
        if( rc != SQLITE_OK && rc != SQLITE_DONE )
            {
            return_code = sql_error( rc );
            }
        rc = sqlite3_finalize( compiled_sql );
        if( return_code == 0 && rc != SQLITE_OK && rc != SQLITE_DONE )
            {
            return_code = sql_error( rc );
            }

        // Write the key file location to the configuration file
        if( found_key_file_location == 0 )
            {
            sprintf( sql_statement, "UPDATE configuration SET value='%s' WHERE parameter = 'key_file_location';", config_data.key_file_location );
            }
        else
            {
            sprintf( sql_statement, "INSERT INTO configuration ( parameter, value ) VALUES ( 'key_file_location', '%s' );", config_data.key_file_location );
            }
        rc = sqlite3_prepare_v2( db, sql_statement, -1, &compiled_sql, &remaining_sql );

        if( rc == SQLITE_OK || rc == SQLITE_DONE )
            {
            rc = sqlite3_step( compiled_sql );
            }
        if( rc != SQLITE_OK && rc != SQLITE_DONE )
            {
            return_code = sql_error( rc );
            }
        rc = sqlite3_finalize( compiled_sql );
        if( return_code == 0 && rc != SQLITE_OK && rc != SQLITE_DONE )
            {
            return_code = sql_error( rc );
            }
        }
    sqlite3_close( db );

    free( sql_statement );
    free( db_name );

    return return_code;
    }


