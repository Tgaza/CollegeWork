#include <fstream>
#include <iostream>
#include "ppm_functions.h"
#include <iomanip>
#include <string>

using namespace std;

int print_file_options(){
    cout << "Which image do you want to load?" << endl;
    cout << "  1. Brick" << endl;
    cout << "  2. Wallpaper" << endl;
    cout << "  3. Private" << endl;
    return 3;
}
int print_operation_options(){
    cout << "Which operation do you want to run?" << endl;
    cout << "  1. Grayscale" << endl;
    cout << "  2. Inversion" << endl;
    cout << "  3. Mirror" << endl;
    return 3;
}

int get_user_input(int maxVal){
    int userInput;
    while(true){
        cout << "Enter ";
        for(int i = 1; i < maxVal; i++){
            cout << i << ", ";
        }
        cout << "or " << maxVal << ": ";
        cin >> userInput;
        if(cin.fail() || (userInput < 1 || userInput > maxVal)){
            cin.clear();
            char badChar;
            do{badChar = cin.get();} while(badChar != '\n');
            cout << "Invalid input." << endl;
            continue;
        }else{
            break;
        }
    }
    return userInput;
}

bool open_files(ifstream& inFile, ofstream& outFile, int fileNum, int operationNum){
    string file;
    if(fileNum == 1){
        file = "brick";
        inFile.open("input/" + file + ".ppm");
    }else if(fileNum == 2){
        file = "wallpaper";
        inFile.open("input/" + file + ".ppm");
    }else{
        file = "private";
        inFile.open("input/" + file + ".ppm");
    }
    if(operationNum == 1){
        outFile.open("output/" + file + "_grayscale.ppm");
    }else if(operationNum == 2){
        outFile.open("output/" + file + "_inversion.ppm");
    }else{
        outFile.open("output/" + file + "_mirror.ppm");
    }
    if(inFile.fail() || outFile.fail()){
        return false;
    }else{
        return true;
    }
}

bool read_header_information(ifstream& inFile, int& width, int& height, int& maxVal){
    string test;
    inFile >> test;
    if(test != "P3"){
        return false;
    }
    inFile >> width >> height >> maxVal;
    return true;
}

void write_header_information(ofstream& outFile, int width, int height, int maxVal){
    outFile << "P3" << "\n" << width << " " << height << "\n" << maxVal << endl;
}

void read_and_write_modified_pixels(ifstream& inFile, ofstream& outFile, int operation, int width, int height, int maxVal){
    int red = 0, green = 0, blue = 0;
    int temp = 0, indexW = 0;
    string line;
    inFile >> red;
    inFile >> green;
    inFile >> blue;
    if (operation == 1) {
        while(!inFile.eof()){
            temp = 0.2989 * red + 0.5870 * green + 0.1140 * blue;
            outFile << temp << " " << temp << " " << temp << " ";
            indexW += 3;
            if (indexW >= width * 3) {
                indexW = 0;
                outFile << endl;
                cout << line;
            }
            inFile >> red;
            inFile >> green;
            inFile >> blue;
        }
    }else if(operation == 2){
        while (!inFile.eof()) {
            red = maxVal - red;
            green = maxVal - green;
            blue = maxVal - blue;
            outFile << red << " " << green << " " << blue << " ";
            indexW += 3;
            if (indexW >= width * 3) {
                indexW = 0;
                outFile << endl;
            }
            inFile >> red;
            inFile >> green;
            inFile >> blue;
        }
    }else {
        while (!inFile.eof()) {
            line = to_string(red) + " " + to_string(green) + " " + to_string(blue) + " " + line;
            indexW += 3;
            if (indexW >= width * 3) {
                indexW = 0;
                outFile << line << endl;
                line = "";
            }
            inFile >> red;
            inFile >> green;
            inFile >> blue;
        }
    }
}