#include <string>
using namespace std;

#ifndef COORDINATE_CONVERSION_H
#define COORDINATE_CONVERSION_H
void polar_to_cartesian(double radius, double angle, double& xCoord, double& yCoord);
void cartesian_to_polar(double xCoord, double yCoord, double& radius, double& angle);
void getInput(string prompt1, string prompt2, double& input1, double& input2);

#endif
