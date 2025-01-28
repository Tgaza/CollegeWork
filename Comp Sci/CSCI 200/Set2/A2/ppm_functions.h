#include <fstream>
using namespace std;

#ifndef PPM_FUNCTIONS_H
#define PPM_FUNCTIONS_H

int print_file_options();
int print_operation_options();
int get_user_input(int maxVal);
bool open_files(ifstream& inFile, ofstream& outFile, int fileNum, int operationNum);
bool read_header_information(ifstream& inFile, int& width, int& height, int& maxVal);
void write_header_information(ofstream& outFile, int width, int height, int maxVal);
void read_and_write_modified_pixels(ifstream& inFile, ofstream& outFile, int operation, int width, int height, int maxVal);

#endif