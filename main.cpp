#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite/sqlite3.h"
#include <cstring>
#include <set>
#include <vector>

using namespace std;
/*
 * processes the current row of the query
 * data points to arbitrary data
 * argc is number of columns
 * argv is value of each column in current row
 * azColName contains the name of each column in query
 */
static int callBack(void *data, int argc, char **argv, char **azColName){
    //prints out name of column and corresponding value
    for(int i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}



int main() {
    //varible for database
    sqlite3 *db;
    //variable for error message
    char *zErrMsg = 0;
    //variable for sql query
    char *sql;
    //variable that contains the execute statement's return value
    int rc;


    //opens the database
    sqlite3_open("ex1.db", &db);


    //creates the table
    sql = "CREATE TABLE anime(" \
            "ID            INT PRIMARY KEY     NOT NULL," \
            "TITLE         TEXT                NOT NULL," \
            "AUTHOR_NAME   TEXT                NOT NULL," \
            "GENRE         TEXT                NOT NULL);";
    //executes the sql query
    sqlite3_exec(db, sql, callBack, 0, &zErrMsg);


    //set with all the genres
    set<string> myset;
    myset.insert("Slice Of Life");
    myset.insert("Shonen");
    myset.insert("Comedy");
    myset.insert("Romance");
    myset.insert("Drama");
    myset.insert("Isekai");
    myset.insert("Action");
    myset.insert("Martial Arts");
    //string that will have the genre
    string genres;
    //lists out the genres
    cout << "Choose from the following genres:" << endl;
    for (const auto& g : myset) {
        cout << g << endl;
    }
    //sets the genre the user types in to 'genres'
    cout << "Enter the name of the genre you want to see animes from: " << endl;
    getline(cin,genres);
    //checks if that genre is part of the list
    if (myset.find(genres) != myset.end()) {
        //select query executed to find the list of animes of that genre
        string query = "SELECT * FROM anime WHERE GENRE='" + genres + "';";
        sqlite3_exec(db, query.c_str(), callBack, 0, &zErrMsg);

        //temporary variables
        string tempName;
        string tempAuthor;
        string answer;
        string tempGenre;
        //adds the anime name the user enters to tempName
        cout << "To add in a new anime, type in the following information:" << endl;
        cout << "Name: " << endl;
        getline(cin,tempName);
        //adds the author the user enters to tempAuthor
        cout << "Author: " << endl;
        getline(cin,tempAuthor);
        //adds the genre the user enters to tempGenre
        cout <<"Genre: " << endl;
        getline(cin,tempGenre);
        //checks if tempGenre is in the set
        if (myset.find(tempGenre) != myset.end()) {
            //questions the user if they want the anime added into the database
            cout << "\nInsert " << tempName << " by " << tempAuthor << " into the database?" << endl;
            cout << "Answer yes or no" << endl;
            //sets answer to be the users response
            cin >> answer;
            if (answer == "yes") {
                //temporary id
                int tempId;
                //lower and upper bound for id's
                int lowerBound = 10000;
                int upperBound = 10000000;
                //variable to check if id exists
                bool idExists = true;
                while(idExists){
                    //seta a random number between the lower and upperbound to 'tempId'
                    tempId = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
                    //sets 'tempId' to a string
                    string id_str = to_string(tempId);
                    //sql insert query
                    query = "INSERT INTO anime(ID, TITLE, AUTHOR_NAME, GENRE) VALUES (" + id_str + ",'" + tempName + "','" +
                            tempAuthor + "','" + tempGenre + "');";
                    //executes the insert query and sets the return value to rc
                    rc = sqlite3_exec(db, query.c_str(), callBack, 0, &zErrMsg);
                    //checks if rc does not equal 0 and if so it errors out SQL error otherwise sets idExists to false
                    if (rc != SQLITE_OK) {
                        //cerr << "SQL error: " << zErrMsg << endl;
                        //sqlite3_free(zErrMsg);
                    } else {
                        // If query returns 0 rows, ID is unique
                        idExists = false;
                    }
                }
            }
        }
    } else {
        //if genre is not in the list, "Invalid genre' is printed out
        cout << "Invalid genre" << endl;
    }
    return 0;
}
