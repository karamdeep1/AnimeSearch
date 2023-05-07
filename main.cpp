#include <iostream>
#include <string>

using namespace std;
int main() {
    string genre = "";
    cout << "Pick a genre from the list:" << std::endl;
    string listOfGenres[] = {"Slice Of Life", "Shonen", "Comedy", "Romance", "Drama", "Shoujo", "Isekai"};
    for(string s: listOfGenres) {
        cout << s << endl;
    }
    cin>>genre;

    return 0;
}
