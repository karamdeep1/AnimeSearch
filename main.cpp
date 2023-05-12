#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite/sqlite3.h"
#include <cstring>

using namespace std;

static int callBack(void *data, int argc, char **argv, char **azColName){
    fprintf(stderr, "%s: ", (const char*)data);
    for(int i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    //const char* data = "Callback function called";



    rc = sqlite3_open("ex1.db", &db);
    /*
    if(rc){
        fprintf(stderr, "Cant open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else{
        fprintf(stderr, "Opened database successfully\n");
    }
*/



    sql = "CREATE TABLE anime(" \
            "ID            INT PRIMARY KEY     NOT NULL," \
            "TITLE         TEXT                NOT NULL," \
            "AUTHOR_NAME   TEXT                NOT NULL," \
            "GENRE         TEXT                NOT NULL);";
    rc = sqlite3_exec(db, sql, callBack, 0, &zErrMsg);
    /*
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }
*/



    sql = "INSERT INTO anime (ID, TITLE, AUTHOR_NAME, GENRE)" \
            "VALUES (58395829, 'Hajime no Ippo', 'George Morikawa', 'Martial Arts');"
            "INSERT INTO anime (ID, TITLE, AUTHOR_NAME, GENRE)" \
            "VALUES (10582945, 'The Rising of Shield Hero', 'Aneko Yusagi', 'Isekai');"
            "INSERT INTO anime (ID, TITLE, AUTHOR_NAME, GENRE)" \
            "VALUES (2948294, 'Vinland Saga', 'Makoto Yukimura', 'Drama');"
            "INSERT INTO anime (ID, TITLE, AUTHOR_NAME, GENRE)" \
            "VALUES (0194902, 'Darling in the Franxx', 'Kentaro Yabuki', 'Romance');"
            "INSERT INTO anime (ID, TITLE, AUTHOR_NAME, GENRE)" \
            "VALUES (12314, 'Gintama', 'Hideaki Sorachi', 'Comedy');"
            "INSERT INTO anime (ID, TITLE, AUTHOR_NAME, GENRE)" \
            "VALUES (72341514, 'Your Lie in April', 'Naoshi Arakawa', 'Slice of Life');"
            "INSERT INTO anime (ID, TITLE, AUTHOR_NAME, GENRE)" \
            "VALUES (8235611, 'One Piece', 'Eiichiro Oda', 'Action');"
            "INSERT INTO anime (ID, TITLE, AUTHOR_NAME, GENRE)" \
            "VALUES (12345567, 'Naruto', 'Masashi Kishimoto', 'Shonen');" \
            "INSERT INTO anime (ID, TITLE, AUTHOR_NAME, GENRE)" \
            "VALUES (7654312, 'Dragon Ball', 'Akira Toriyama', 'Action');";
    rc = sqlite3_exec(db, sql, callBack, 0, &zErrMsg);
    /*
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
     */




    char* genre;
    cout << "Pick a genre from the list:" << std::endl;
    string listOfGenres[] = {"Slice Of Life", "Shonen", "Comedy", "Romance", "Drama", "Isekai", "Action", "Martial Arts"};
    for (string s: listOfGenres) {
        cout << s << endl;
    }
    cin.getline(genre, 100);
    char* query = "SELECT * FROM anime WHERE GENRE = '";
    sql = new char[strlen(query)+strlen(genre)];
    strcpy(sql,query);
    strcat(sql,genre);
    strcat(sql,"'");
    rc = sqlite3_exec(db, sql, callBack, 0, &zErrMsg);
    /*
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
     */
    string tempId;
    string tempName;
    string tempAuthor;
    string tempGenre;
    string answer;
    cout<<"To add in a new anime type in the following information:"<<endl;
    cout<<"Name: " <<endl;
    cin>>tempName;

    cout<<"Author: "<<endl;
    cin>>tempAuthor;

    cout<<"Genre: "<<endl;
    cin>>tempGenre;

    cout<<"\nInsert " + tempName + " by " + tempAuthor + " into the database?"<<endl;
    cout<<"Answer yes or no"<<endl;
    cin>>answer;
    if(answer == "yes"){

        cout<<"Successfully added, restart the program to see the new list"<<endl;
    }
    else{
        cout<<tempName + " by " + tempAuthor + " was not added"<<endl;

    }
    sqlite3_close(db);

    return 0;
}