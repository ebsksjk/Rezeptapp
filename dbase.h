///////////////////////////////////////////////////////////////////////////////
// DBASE.H
//
// FUNCTIONS AND UTILITIES FOR AN EVEN CLEANER ACCESS TO A DATABASE
// 
// BGI SAYS: TRANS RIGHTS
///////////////////////////////////////////////////////////////////////////////

#ifndef DBASE
#define DBASE

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////

MYSQL* con = NULL;

void finish_with_error(void);

///////////////////////////////////////
// createConnection
//
// create the connection to the
// database specified by (char*) dbname
///////////////////////////////////////
int createConnection(char* dbname) {
    con = mysql_init(NULL);

    if (con == NULL) finish_with_error();

    if (mysql_real_connect(con, "localhost", "test", "test", dbname, 0, NULL, 0) == NULL)
        finish_with_error();

    return 0;
}

///////////////////////////////////////
// closeConnection
//
// closes the connection to the
// database gracefully
///////////////////////////////////////
int closeConnection(){
    mysql_close(con);

    return 0;
}

///////////////////////////////////////
// createConnection
//
// querys the (char*) query against
// the db; query is expected to not 
// generate any output, as it is
// ignored and immeadiatly discarded
///////////////////////////////////////
void queryConnection(char* query){
    if (mysql_query(con, query)) finish_with_error();

    mysql_free_result(mysql_store_result(con));
}

///////////////////////////////////////
// finish_with_error
//
// a function to be called when we want
// to log an error and kill the program
///////////////////////////////////////
void finish_with_error(void){
  fprintf(stderr, "%s\n", mysql_error(con));
  closeConnection();
  exit(-1);
}


///////////////////////////////////////
// queryDB
//
// querys (char*) query against the db
// returns a pointer to MYSQL_RES, which
// needs to be freed after usage
///////////////////////////////////////
MYSQL_RES* queryDB(char* query) {
    if (mysql_query(con, query)) finish_with_error();

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) finish_with_error();

    return result;
}

#endif