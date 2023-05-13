#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite/sqlite3.h"
#include <cstring>
#include <set>
#include <vector>

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
    char *sql;
    int rc;



    sqlite3_open("ex1.db", &db);



    sql = "CREATE TABLE anime(" \
            "ID            INT PRIMARY KEY     NOT NULL," \
            "TITLE         TEXT                NOT NULL," \
            "AUTHOR_NAME   TEXT                NOT NULL," \
            "GENRE         TEXT                NOT NULL);";
    sqlite3_exec(db, sql, callBack, 0, &zErrMsg);



    set<string> myset;
    myset.insert("Slice Of Life");
    myset.insert("Shonen");
    myset.insert("Comedy");
    myset.insert("Romance");
    myset.insert("Drama");
    myset.insert("Isekai");
    myset.insert("Action");
    myset.insert("Martial Arts");

    string genres;
    cout << "Choose from the following genres:" << endl;
    for (const auto& g : myset) {
        cout << g << endl;
    }
    cout << "Enter the name of the genre you want to see animes from: " << endl;
    getline(cin,genres);

    if (myset.find(genres) != myset.end()) {
        string query = "SELECT * FROM anime WHERE GENRE='" + genres + "';";
        sqlite3_exec(db, query.c_str(), callBack, 0, &zErrMsg);


        string tempName;
        string tempAuthor;
        string answer;
        string tempGenre;
        cout << "To add in a new anime, type in the following information:" << endl;
        cout << "Name: " << endl;
        getline(cin,tempName);

        cout << "Author: " << endl;
        getline(cin,tempAuthor);

        cout <<"Genre: " << endl;
        getline(cin,tempGenre);

        if (myset.find(tempGenre) != myset.end()) {
            cout << "\nInsert " << tempName << " by " << tempAuthor << " into the database?" << endl;
            cout << "Answer yes or no" << endl;
            cin >> answer;
            if (answer == "yes") {
                int tempId;
                int lowerBound = 10000;
                int upperBound = 10000000;
                bool idExists = true;
                while(idExists){
                    tempId = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
                    string id_str = to_string(tempId);
                    query = "INSERT INTO anime(ID, TITLE, AUTHOR_NAME, GENRE) VALUES (" + id_str + ",'" + tempName + "','" +
                            tempAuthor + "','" + genres + "');";
                    rc = sqlite3_exec(db, query.c_str(), callBack, 0, &zErrMsg);
                    if (rc != SQLITE_OK) {
                        cerr << "SQL error: " << zErrMsg << endl;
                        sqlite3_free(zErrMsg);
                    } else {
                        // If query returns 0 rows, ID is unique
                        idExists = false;
                    }
                }
            }
        }
    } else {
        cout << "Invalid genre" << endl;
    }
    return 0;
}
