#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h>

using namespace std;

bool file_exists(string file_path) {
    struct stat buffer;
    return (stat(file_path.c_str(), &buffer) == 0);
}

void show_data(string path) {
    // check if a file exists at the given path or not.
    if (!file_exists(path)) {
        cout << "[ERROR] File doesn't exists at the given path - RESTARTING\n";
        return;
    }
    string f;
    ifstream ifs(path, ios::binary);
    // read line by line until you find the first line starting with --s
    int i = 1;
    bool any_data_found = false;
    while (getline(ifs, f)) {
        if (f.find("--s") != string::npos) {
            any_data_found = true;
            f = f.substr(3);
            cout << "[YOUR SECRET DATA] >> " << f;
            cout << '\n';
            cout << "-------------\n";
        }
    }
    if (!any_data_found) {
        cout << "[NO SECRET DATA FOUND - RESTARTING]\n";
    }
}

void hide_data(string path, string data) {
    if (file_exists(path)) {
        ofstream of(path, ios_base::app);
        // start hiding the data by using --s at the starting;
        of << "\n--s" + data;
        of.close();
        cout << "[SUCCESS] Stored your secret data in file successfully";
    }
    else {
        cout << "[ERROR] File doesn't exists at the given path - RESTARTING";
    }
}

int main() {
    while (true) {
        cout << "Welcome to Steganography program.\n";
        cout << "Choose the type of operation\n";
        cout << "1. Hide data.\n";
        cout << "2. Extract your hidden data.\n";
        cout << "3. Exit application.\n";
        cout << "Enter input >> ";

        string ans;
        getline(cin, ans);

        if (ans.size() > 0) {
            // Get only the first character if user accidently wrote multiple characters.
            ans = ans[0];
        }

        if (ans == "1") {
            string file_loc;
            cout << "Enter the location of the image file(png preffered) >> ";
            getline(cin, file_loc);
            string input;
            cout << "Enter the text which you want to store in this file >> ";
            getline(cin, input);



            // now call the hide_data function to hide data in image.
            hide_data(file_loc, input);
        }
        else if (ans == "2") {
            string file_loc;
            cout << "Enter the location of the image file >> ";
            getline(cin, file_loc);
            show_data(file_loc);
        }
        else if (ans == "3") {
            cout << "[THANK YOU - BREKING OUT]\n";
            break;
        }
        else {
            cout << "[INVALID INPUT - RESTARTING]\n";

        }

        cout << "\n\n=========== EOP ===========\n\n";
    }

    return 0;
}

