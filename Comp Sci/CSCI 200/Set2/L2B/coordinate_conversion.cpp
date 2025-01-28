#include "coordinate_conversion.h"
#include <cmath>
#include <iostream>

void cartesian_to_polar(double xCoord, double yCoord, double& radius, double& angle){
    radius = sqrt(pow(radius, 2) + pow(angle, 2));
    angle = atan(yCoord/xCoord);
}
void polar_to_cartesian(double radius, double theta, double& xCoord, double& yCoord){
    xCoord = radius * cos(theta);
    yCoord = radius * sin(theta);
}
void getInput(string prompt1, string prompt2, double& input1, double& input2){
    while(true){
            cout << prompt1;
            cin >> input1;
            if(cin.fail()){
                cin.clear();
                char badChar;
                do{badChar = cin.get();} while(badChar != '\n');
                continue;
            }
            else break;
    }
    while(true){
            cout << prompt2;
            cin >> input2;
            if(cin.fail()){
                cin.clear();
                char badChar;
                do{badChar = cin.get();} while(badChar != '\n');
                continue;
            }
            else break;
    }
}
