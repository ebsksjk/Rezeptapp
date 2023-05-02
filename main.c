#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s:\n", (const char*)data);

   printf("Rezept für: %s\n", argv[0]);

   
   for(i = 1; i<argc; i++){
      printf("%s\t", azColName[i]);
   }

   printf("\n");

   for(i = 1; i<argc; i++){
      printf("%s\t", argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("Rezepte.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "SELECT r.Name, i.Name, z.Amount, u.Name from Zusammensetzung AS z \
   INNER JOIN Rezept AS r ON z.RID=r.ID \
   INNER JOIN Ingriedient AS i ON z.IID=i.ID \
   INNER JOIN Unit AS u ON z.UID=u.ID;";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}