/*Below is a simple C program that demonstrates how to use the C/C++ interface to SQLite.
The name of a database is given by the first argument and the second argument is one or more
SQL statements to execute against the database. The function calls to pay attention to here
are the call to sqlite3_open() on line 28 which opens the database, sqlite3_exec() on line
34 that executes SQL commands against the database, and sqlite3_close() on line 39
that closes the database connection.*/
#include <stdio.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(int argc, char **argv){
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	if( argc!=3 ){
		fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
		return(1);
	}
	rc = sqlite3_open(argv[1], &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}
	rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	sqlite3_close(db);
	return 0;
}
