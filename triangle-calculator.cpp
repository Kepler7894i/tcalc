//Put angle_count and side_count and expected_ans and x in triangle and just pass that
//Compare expected_ans to ans and log difference

#include <iostream>
#include <fstream>
#include <string>

#ifndef _WIN32
#include <unistd.h>
#endif

int main(int argc, char** argv);
void userInput();
void fileInput(std::string file);

const double pi = 3.14159;
bool debug = false, right_angled = false, testing = false, file = false;


char** param_remove;

class Triangle {
public:
    double A = 0, B = 0, C = 0;
    double Ar = 0, Br = 0, Cr = 0;
    double a = 0, b = 0, c = 0;
    double Area = 0;
};

void degrees_radians(double& degrees, double& radians) {
    radians = (degrees * pi) / 180;
}

void radians_degrees(double radians, double& degrees) {
    degrees = (radians * 180) / pi;
}

void error(int error_num, std::string action) {
    switch (error_num) {
        case 1: {
            std::cout << "\n\nError: Angles !<= 180 degree.\n\n";
        }
        case 2: {
            std::cout << "Error: " << action << " is incalculabe with information provided.\n\n";
            break;
        }
        case 3: {
            std::cout << "Error: Two sides cannot be 0.\n\n";
            break;
        }
        case 4: {
            std::cout << "One or more inputted values is incorrect compared to other values.\n\n";
            userInput();
            break;
        }
        case 5: {
            std::cout << "Error: Failed to open - " << action << "\nFile to read from: ";
            std::string file;
            std::cin >> file;
            fileInput(file);
            break;
        }
        case 6: {
            int fixed;

            std::cout << "\nError: Incorrect angles in file.";
            std::cout << "\nFixed? ";
            std::cin >> fixed;

            if (fixed == 1) {
                fileInput(action);
            }
            else if (fixed == 0) {
                return;
            }
            else {
                std::cout << "Enter 1 or 0.";
                error(6, action);
            }

            break;
        }
        case 7: {
            int fixed;

            std::cout << "\nError: Incorrect number of properties in file. Fixed? ";
            std::cout << "\n\n       Correct layout:";
            std::cout << "\n         wanted_property A B C a b c Area expected_ans - Spaces between the values";
            std::cout << "\n                                                       - Capital letters are angles, lowercase letters are sides";
            std::cout << "\n                                                       - Opposite angles and sides should be the same letter";
            std::cout << "Fixed? ";
            std::cin >> fixed;

            if (fixed == 1) {
                fileInput(action);
            }
            else if (fixed == 0) {
                return;
            }
            else {
                std::cout << "Enter 1 or 0.";
                error(6, action);
            }
        }
    }
}

void calculations(Triangle& Info, int angle_count, int side_count, std::string x) {
    double ans = 0;

    if (debug) {
        std::cout << "\n\nWanted prop: " << x;
        std::cout << "\nAngle's: " << Info.A << ", " << Info.B << ", " << Info.C;
        std::cout << "\nRadian's: " << Info.Ar << ", " << Info.Br << ", " << Info.Cr;
        std::cout << "\nSide's: " << Info.a << ", " << Info.b << ", " << Info.c;
        std::cout << "\nArea: " << Info.Area;
    }

    //Calc. angle's when 2 angle's known - 180 degree's in tirangle
    if (x == "A" && Info.B != 0 && Info.C != 0) {
        ans = 180 - Info.B - Info.C;
    }
    else if (x == "B" && Info.A != 0 && Info.C != 0) {
        ans = 180 - Info.A - Info.C;
    }
    else if (x == "C" && Info.B != 0 && Info.A != 0) {
        ans = 180 - Info.B - Info.A;
    }
    //Calculate area when 2 side's and inbetween angle known
    else if ((x == "Area" || "area") && ((Info.a != 0 && Info.b != 0 && Info.C != 0) || (Info.b != 0 && Info.c != 0 && Info.A != 0) || (Info.c != 0 && Info.a != 0 && Info.B != 0))) {
        if (Info.a != 0 && Info.b != 0 && Info.C != 0) {
            ans = 0.5 * Info.a * Info.b * sin(Info.Cr);
        }
        else if (Info.b != 0 && Info.c != 0 && Info.A != 0) {
            ans = 0.5 * Info.b * Info.c * sin(Info.Ar);
        }
        else if (Info.c != 0 && Info.a != 0 && Info.B != 0) {
            ans = 0.5 * Info.c * Info.a * sin(Info.Br);
        }
    }
    //Calculate side when area, a side and an angle is known
    else if (x == "a" && Info.Area != 0 && ((Info.b != 0 && Info.C != 0) || (Info.c != 0 && Info.B != 0))) {
        if (Info.b != 0 && Info.C != 0) {
            ans = Info.Area / (0.5 * Info.b * sin(Info.Cr));
        }
        else if (Info.c != 0 && Info.B != 0) {
            ans = Info.Area / (0.5 * Info.c * sin(Info.Br));
        }
    }
    else if (x == "b" && Info.Area != 0 && ((Info.a != 0 && Info.C != 0) || (Info.c != 0 && Info.A != 0))) {
        if (Info.a != 0 && Info.C != 0) {
            ans = Info.Area / (0.5 * Info.a * sin(Info.Cr));
        }
        else if (Info.c != 0 && Info.A != 0) {
            ans = Info.Area / (0.5 * Info.c * sin(Info.Ar));
        }
    }
    else if (x == "c" && Info.Area != 0 && ((Info.b != 0 && Info.A != 0) || (Info.a != 0 && Info.B != 0))) {
        if (Info.b != 0 && Info.C != 0) {
            ans = Info.Area / (0.5 * Info.b * sin(Info.Ar));
        }
        else if (Info.c != 0 && Info.B != 0) {
            ans = Info.Area / (0.5 * Info.a * sin(Info.Br));
        }
    }
    //Calculate angle when area and 2 side's are known
    else if (x == "A" && Info.Area != 0 && Info.b != 0 && Info.c != 0) {
        ans = asin(Info.Area / (0.5 * Info.b * Info.c));
    }
    else if (x == "B" && Info.Area != 0 && Info.a != 0 && Info.c != 0) {
        ans = asin(Info.Area / (0.5 * Info.a * Info.c));
    }
    else if (x == "A" && Info.Area != 0 && Info.a != 0 && Info.b != 0) {
        ans = asin(Info.Area / (0.5 * Info.a * Info.b));
    }
    else if (90 == Info.A || Info.B || Info.C && x == "a" || "b" || "c" && side_count == 2) {
        //Calc. side's when 2 side's known - pyth
        if (x == "a" || x == "b" || x == "c" && side_count == 2) {
            if (Info.A == 90) {
                if (x == "a" && Info.b != 0 && Info.c != 0) {
                    ans = sqrt(pow(Info.b, 2) + pow(Info.c, 2));
                }
                else if (x == "b" && Info.a != 0 && Info.c != 0) {
                    ans = sqrt(pow(Info.a, 2) - pow(Info.c, 2));
                }
                else if (x == "c" && Info.a != 0 && Info.b != 0) {
                    std::cout << "hi";
                    ans = sqrt(pow(Info.a, 2) - pow(Info.b, 2));
                }
            }
            else if (Info.B == 90) {
                if (x == "a" && Info.b != 0 && Info.c != 0) {
                    ans = sqrt(pow(Info.b, 2) - pow(Info.c, 2));
                }
                else if (x == "b" && Info.a != 0 && Info.c != 0) {
                    ans = sqrt(pow(Info.a, 2) + pow(Info.c, 2));
                }
                else if (x == "c" && Info.a != 0 && Info.b != 0) {
                    ans = sqrt(pow(Info.b, 2) - pow(Info.a, 2));
                }
            }
            else if (Info.C == 90) {
                if (x == "a" && Info.b != 0 && Info.c != 0) {
                    ans = sqrt(pow(Info.c, 2) - pow(Info.b, 2));
                }
                else if (x == "b" && Info.a != 0 && Info.c != 0) {
                    ans = sqrt(pow(Info.c, 2) - pow(Info.a, 2));
                }
                else if (x == "c" && Info.a != 0 && Info.b != 0) {
                    ans = sqrt(pow(Info.a, 2) + pow(Info.b, 2));
                }
            }
        }
        //Calc. side's when 1 side and 1 >= angle known (1 must be 90) - trig (functions)
        else if (x == "a" || x == "b" || x == "c" && angle_count >= 1 && side_count == 1) {
            if (Info.A == 90) {
                if (x == "a") {
                    if (Info.B != 0) {
                        if (Info.b != 0) {
                            ans = Info.b / sin(Info.Br);
                        }
                        else if (Info.c != 0) {
                            ans = Info.c / cos(Info.Br);
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.c != 0) {
                            ans = Info.c / sin(Info.Cr);
                        }
                        else if (Info.b != 0) {
                            ans = Info.b / cos(Info.Cr);
                        }
                    }
                }
                else if (x == "b") {
                    if (Info.B != 0) {
                        if (Info.a != 0) {
                            ans = sin(Info.Br) * Info.a;
                        }
                        else if (Info.c != 0) {
                            ans = tan(Info.Br) * Info.c;
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.a != 0) {
                            ans = cos(Info.Cr) * Info.a;
                        }
                        else if (Info.c != 0) {
                            ans = Info.c / tan(Info.Cr);
                        }
                    }
                }
                else if (x == "c") {
                    if (Info.B != 0) {
                        if (Info.a != 0) {
                            ans = cos(Info.Br) * Info.a;
                        }
                        else if (Info.b != 0) {
                            ans = Info.b / tan(Info.Br);
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.a != 0) {
                            ans = sin(Info.Cr) * Info.a;
                        }
                        else if (Info.b != 0) {
                            ans = tan(Info.Cr) * Info.b;
                        }
                    }
                }
            }
            else if (Info.B == 90) {
                if (x == "a") {
                    if (Info.A != 0) {
                        if (Info.b != 0) {
                            ans = sin(Info.Ar) * Info.b;
                        }
                        else if (Info.c != 0) {
                            ans = tan(Info.Ar) * Info.c;
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.c != 0) {
                            ans = Info.c / tan(Info.Cr);
                        }
                        else if (Info.b != 0) {
                            ans = cos(Info.Cr) * Info.b;
                        }
                    }
                }
                else if (x == "b") {
                    if (Info.A != 0) {
                        if (Info.a != 0) {
                            ans = Info.a / sin(Info.Ar);
                        }
                        else if (Info.c != 0) {
                            ans = Info.c / cos(Info.Ar);
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.a != 0) {
                            ans = Info.a / cos(Info.Cr);
                        }
                        else if (Info.c != 0) {
                            ans = Info.c / sin(Info.Cr);
                        }
                    }
                }
                else if (x == "c") {
                    if (Info.A != 0) {
                        if (Info.a != 0) {
                            ans = Info.a / tan(Info.Ar);
                        }
                        else if (Info.b != 0) {
                            ans = cos(Info.Br) * Info.b;
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.a != 0) {
                            ans = tan(Info.Cr) * Info.a;
                        }
                        else if (Info.b != 0) {
                            ans = sin(Info.Cr) * Info.b;
                        }
                    }
                }
            }
            else if (Info.C == 90) {
                if (x == "a") {
                    if (Info.A != 0) {
                        if (Info.b != 0) {
                            ans = tan(Info.Br) * Info.b;
                        }
                        else if (Info.c != 0) {
                            ans = sin(Info.Br) * Info.c;
                        }
                    }
                    else if (Info.B != 0) {
                        if (Info.b != 0) {
                            ans = Info.b / sin(Info.Br);
                        }
                        else if (Info.c != 0) {
                            ans = cos(Info.Br) * Info.c;
                        }
                    }
                }
                else if (x == "b") {
                    if (Info.A != 0) {
                        if (Info.a != 0) {
                            ans = Info.a / tan(Info.Ar);
                        }
                        else if (Info.c != 0) {
                            ans = cos(Info.Ar) * Info.c;
                        }
                    }
                    else if (Info.B != 0) {
                        if (Info.a != 0) {
                            ans = tan(Info.Br) * Info.a;
                        }
                        else if (Info.c != 0) {
                            ans = sin(Info.Br) * Info.c;
                        }
                    }
                }
                else if (x == "c") {
                    if (Info.A != 0) {
                        if (Info.a != 0) {
                            ans = Info.a / sin(Info.Ar);
                        }
                        else if (Info.b != 0) {
                            ans = Info.b / cos(Info.Ar);
                        }
                    }
                    else if (Info.B != 0) {
                        if (Info.a != 0) {
                            ans = Info.a / cos(Info.Br);
                        }
                        else if (Info.b != 0) {
                            ans = Info.b / sin(Info.Br);
                        }
                    }
                }
            }
        }
        //Calc. angle's when 2 sides known and 90 angle known - trig (functions)
        else if (90 == Info.A || Info.B || Info.C && side_count == 2) {
            //Hyp = opp of 90 degree angle, Opp = opp of angle to be calculated, Adj = other side
            if (Info.A == 90) {
                if (x == "B") {
                    if (Info.a != 0 && Info.b != 0) {
                        radians_degrees(asin(Info.b / Info.a), ans);
                    }
                    else if (Info.a != 0 && Info.c != 0) {
                        radians_degrees(acos(Info.c / Info.a), ans);
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        radians_degrees(atan(Info.b / Info.c), ans);
                    }
                }
                else if (x == "C") {
                    if (Info.a != 0 && Info.c != 0) {
                        radians_degrees(asin(Info.c / Info.a), ans);
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        radians_degrees(acos(Info.b / Info.a), ans);
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        radians_degrees(atan(Info.c / Info.b), ans);
                    }
                }
            }
            else if (Info.B == 90) {
                if (x == "A") {
                    if (Info.a != 0 && Info.b != 0) {
                        radians_degrees(asin(Info.a / Info.b), ans);
                    }
                    else if (Info.a != 0 && Info.c != 0) {
                        radians_degrees(acos(Info.c / Info.a), ans);
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        radians_degrees(atan(Info.b / Info.c), ans);
                    }
                }
                else if (x == "C") {
                    if (Info.c != 0 && Info.b != 0) {
                        radians_degrees(asin(Info.c / Info.b), ans);
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        radians_degrees(acos(Info.b / Info.a), ans);
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        radians_degrees(atan(Info.c / Info.b), ans);
                    }
                }
            }
            else if (Info.C == 90) {
                if (x == "A") {
                    if (Info.a != 0 && Info.c != 0) {
                        radians_degrees(asin(Info.a / Info.c), ans);
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        radians_degrees(acos(Info.b / Info.c), ans);
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        radians_degrees(atan(Info.a / Info.b), ans);
                    }
                }
                else if (x == "B") {
                    if (Info.b != 0 && Info.c != 0) {
                        radians_degrees(asin(Info.b / Info.c), ans);
                    }
                    else if (Info.a != 0 && Info.c != 0) {
                        radians_degrees(acos(Info.a / Info.c), ans);
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        radians_degrees(atan(Info.b / Info.a), ans);
                    }
                }
            }
        }
    }
    //Sine and cosine rule's can also be used for right angled triangle's but I see no reason to do that and so haven't programmed that functionality in, I will if I discover a use later down the line
    else if (Info.A != 90 && Info.B != 90 && Info.C != 90) {
        if (x == "A" || x == "B" || x == "C") {
            //Calc. angle's when 1 angle & 2 side's known - trig (sine rule)
            if (x == "A" && Info.a != 0 && Info.B != 0 && Info.b != 0) {
                radians_degrees(asin(Info.a * sin(Info.Br) / Info.b), ans);
            }
            else if (x == "A" && Info.a != 0 && Info.C != 0 && Info.c != 0) {
                radians_degrees(asin(Info.a * sin(Info.Cr) / Info.c), ans);
            }
            else if (x == "B" && Info.b != 0 && Info.A != 0 && Info.a != 0) {
                radians_degrees(asin(Info.b * sin(Info.Ar) / Info.a), ans);
            }
            else if (x == "B" && Info.a != 0 && Info.B != 0 && Info.b != 0) {
                radians_degrees(asin(Info.b * sin(Info.Cr) / Info.c), ans);
            }
            else if (x == "C" && Info.a != 0 && Info.B != 0 && Info.b != 0) {
                radians_degrees(asin(Info.c * sin(Info.Ar) / Info.a), ans);
            }
            else if (x == "C" && Info.a != 0 && Info.B != 0 && Info.b != 0) {
                radians_degrees(asin(Info.c * sin(Info.Br) / Info.b), ans);
            }
            //Calc. angle's when 3 side's known - trig (cosine rule)
            if (Info.a != 0 && Info.b != 0 && Info.c != 0) {
                if (x == "A") {
                    radians_degrees(acos((pow(Info.b, 2) + pow(Info.c, 2) - pow(Info.a, 2)) / (2 * Info.b * Info.c)), ans);
                }
                /*else if (x == "A" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radians_degrees(ans, acos((pow(Info.b, 2) + pow(Info.c, 2) - pow(Info.a, 2)) / (2 * Info.a * Info.c)));
                }
                else if (x == "A" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radians_degrees(ans, acos((pow(Info.b, 2) + pow(Info.c, 2) - pow(Info.a, 2)) / (2 * Info.a * Info.b)));
                }*/
                else if (x == "B") {
                    radians_degrees(acos((pow(Info.a, 2) + pow(Info.c, 2) - pow(Info.b, 2)) / (2 * Info.a * Info.c)), ans);
                }
                /*else if (x == "B" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radians_degrees(ans, acos((pow(Info.a, 2) + pow(Info.c, 2) - pow(Info.b, 2)) / (2 * Info.b * Info.c)));
                }
                else if (x == "B" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radians_degrees(ans, acos((pow(Info.a, 2) + pow(Info.c, 2) - pow(Info.b, 2)) / (2 * Info.a * Info.b)));
                }*/
                else if (x == "C") {
                    radians_degrees(acos((pow(Info.a, 2) + pow(Info.b, 2) - pow(Info.c, 2)) / (2 * Info.a * Info.b)), ans);
                }
                /*else if (x == "C" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radians_degrees(ans, acos((pow(Info.a, 2) + pow(Info.b, 2) - pow(Info.c, 2)) / (2 * Info.b * Info.c)));
                }
                else if (x == "C" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radians_degrees(ans, acos((pow(Info.a, 2) + pow(Info.b, 2) - pow(Info.c, 2)) / (2 * Info.a * Info.c)));
                }*/
            }
        }
        else if (x == "a" || x == "b" || x == "c" && angle_count == 2 && side_count == 1) {
            //Calc. side's when 2 angle's & 1 side known - trig (sine rule)
            if (x == "a" && Info.A != 0 && Info.B != 0 && Info.b != 0) {
                ans = sin(Info.Ar) * Info.b / sin(Info.Br);
            }
            else if (x == "a" && Info.A != 0 && Info.C != 0 && Info.c != 0) {
                ans = sin(Info.Ar) * Info.c / sin(Info.Cr);
            }
            else if (x == "b" && Info.B != 0 && Info.A != 0 && Info.a != 0) {
                ans = sin(Info.Br) * Info.a / sin(Info.Ar);
            }
            else if (x == "b" && Info.B != 0 && Info.C != 0 && Info.c != 0) {
                ans = sin(Info.Br) * Info.c / sin(Info.Cr);
            }
            else if (x == "c" && Info.C != 0 && Info.A != 0 && Info.a != 0) {
                ans = sin(Info.Cr) * Info.a / sin(Info.Ar);
            }
            else if (x == "c" && Info.C != 0 && Info.B != 0 && Info.b != 0) {
                ans = sin(Info.Cr) * Info.b / sin(Info.Br);
            }
            //Calc. side's when 1 angle and 2 side's known - trig (cosine rule)
            else if (x == "a" && Info.A != 0 && Info.b != 0 && Info.c != 0) {
                ans = sqrt((pow(Info.b, 2)) + (pow(Info.c, 2)) - (2 * Info.b * Info.c * cos(Info.Ar)));
            }
            else if (x == "a" && Info.B != 0 && Info.b != 0 && Info.c != 0) {
                ans = sqrt((pow(Info.b, 2)) - (pow(Info.c, 2)) + (2 * Info.b * Info.c * cos(Info.Br)));
            }
            else if (x == "a" && Info.C != 0 && Info.c != 0 && Info.b != 0) {
                ans = sqrt((pow(Info.c, 2)) - (pow(Info.b, 2)) + (2 * Info.c * Info.b * cos(Info.Cr)));
            }
            else if (x == "b" && Info.B != 0 && Info.a != 0 && Info.c != 0) {
                ans = sqrt((pow(Info.a, 2)) + (pow(Info.c, 2)) - (2 * Info.a * Info.c * cos(Info.Br)));
            }
            else if (x == "b" && Info.A != 0 && Info.a != 0 && Info.c != 0) {
                ans = sqrt((pow(Info.b, 2)) - (pow(Info.c, 2)) + (2 * Info.a * Info.c * cos(Info.Ar)));
            }
            else if (x == "b" && Info.C != 0 && Info.c != 0 && Info.a != 0) {
                ans = sqrt((pow(Info.c, 2)) - (pow(Info.a, 2)) + (2 * Info.c * Info.a * cos(Info.Cr)));
            }
            else if (x == "c" && Info.C != 0 && Info.a != 0 && Info.b != 0) {
                ans = sqrt((pow(Info.a, 2)) + (pow(Info.b, 2)) - (2 * Info.a * Info.b * cos(Info.Cr)));
            }
            else if (x == "c" && Info.A != 0 && Info.a != 0 && Info.b != 0) {
                ans = sqrt((pow(Info.a, 2)) - (pow(Info.b, 2)) + (2 * Info.a * Info.b * cos(Info.Ar)));
            }
            else if (x == "c" && Info.B != 0 && Info.b != 0 && Info.a != 0) {
                ans = sqrt((pow(Info.b, 2)) - (pow(Info.a, 2)) + (2 * Info.b * Info.a * cos(Info.Br)));
            }
        }
    }
    else {
        error(2, x);
        return;
    }

    std::cout << "\n" << x << " = " << ans;
}

void userInput() {
    Triangle Info;

    int angle_count = 0, side_count = 0;
    std::string x;

    std::cout << "Wanted prop: ";
    std::cin >> x;
    std::cout << "\n";

    if (x != "A" && x != "B" && x != "C" && x != "a" && x != "b" && x != "c" && x != "Area" && x != "area") {
        std::cout << "\nPlease enter a valid aim.";
        userInput();
        exit;
    }
    if (x != "A") {
        std::cout << "\tA = ";
        std::cin >> Info.A;
        degrees_radians(Info.A, Info.Ar);
    }
    if (x != "B") {
        std::cout << "\tB = ";
        std::cin >> Info.B;
        degrees_radians(Info.B, Info.Br);
    }
    if (x != "B") {
        std::cout << "\tC = ";
        std::cin >> Info.C;
        degrees_radians(Info.C, Info.Cr);
    }

    if (Info.A != 0) {
        ++angle_count;
    }
    if (Info.B != 0) {
        ++angle_count;
    }
    if (Info.C != 0) {
        ++angle_count;
    }

    //input check
    if ((Info.A + Info.B + Info.C) > 180 || ((Info.A + Info.B + Info.C) == 180 && angle_count != 3) || ((Info.A + Info.B + Info.C) < 180 && angle_count == 3)) {
        error(1, x);
        userInput();
        return;
    }

    //Change from || to bool
    if (Info.A || Info.B || Info.C == 90) {
        right_angled = true;
    }

    if (x != "a") {
        std::cout << "\ta = ";
        std::cin >> Info.a;
    }
    if (x != "b") {
        std::cout << "\tb = ";
        std::cin >> Info.b;
    }
    if (x != "c") {

        std::cout << "\tc = ";
        std::cin >> Info.c;
    }

    if (Info.a != 0) {
        ++side_count;
    }
    if (Info.b != 0) {
        ++side_count;
    }
    if (Info.c != 0) {
        ++side_count;
    }

    if (x != "Area" && x != "area") {
        std::cout << "\tArea = ";
        std::cin >> Info.Area;
    }

    if (debug) {
        std::cout << "\n\nWanted prop: " << x;
        std::cout << "\nAngle's: " << Info.A << ", " << Info.B << ", " << Info.C;
        std::cout << "\nRadian's: " << Info.Ar << ", " << Info.Br << ", " << Info.Cr;
        std::cout << "\nSide's: " << Info.a << ", " << Info.b << ", " << Info.c;
        std::cout << "\nArea: " << Info.Area;
    }

    calculations(Info, angle_count, side_count, x);
}

void fileInput(std::string file) {
    Triangle Info;

    debug = true;

    if (std::ifstream input_file{ file }) {

        std::string line, x;
        int length = 0, line_length = 0, read = 0;
        double expected_ans = 0;

        while (std::getline(input_file, line)) {
            length++;
        }

        if (debug) {
            std::cout << "\nLines: " << length;
        }

        input_file.close();
        input_file.open(file);

        while (std::getline(input_file, line)) {
            int prop_count = 0, side_count = 0, angle_count = 0, output = 0;

            line_length = line.length();

            if (debug) {
                std::cout << "\n\n\n\n\n\n" << line;
                std::cout << "\nLine length = " << line_length;
            }

            for (int character = 0; character < line_length; character++) {
                if (line[character] == ' ') {
                    prop_count++;
                }
            }

            prop_count++;

            if (debug) {
                std::cout << "\nProp count = " << prop_count;
            }
            
            if (prop_count != 9) {
                error(7, file);
                std::exit(1);
            }

            for (int character = 0; character < line_length; character++) {
                int read = 0;
                std::string temp, prop;

                //if (line[character] == ' ' || line[character] == line[0]) {
                if (line[character] == ' ') {
                    for (read = character - 1; read > 0; read--) {
                        if (line[read] == ' ') {
                            break;
                        }
                    }
                    for (read; read < character; read++) {
                        temp = line[read];
                        prop = prop + temp;

                        if (debug) {
                            std::cout << "\n\nTemp = " << temp;
                            std::cout << "\nProperty = " << prop;
                            std::cout << "\nOutput: " << output;
                        }
                    }

                    if (output == 0) {
                        x = prop;
                    }
                    else if (output == 1) {
                        Info.A = stoi(prop);
                        degrees_radians(Info.A, Info.Ar);
                    }
                    else if (output == 2) {
                        Info.B = stoi(prop);
                        degrees_radians(Info.B, Info.Br);
                    }
                    else if (output == 3) {
                        Info.C = stoi(prop);
                        degrees_radians(Info.C, Info.Cr);
                    }
                    else if (output == 4) {
                        Info.a = stoi(prop);
                    }
                    else if (output == 5) {
                        Info.b = stoi(prop);
                    }
                    else if (output == 6) {
                        Info.c = stoi(prop);
                    }
                    else if (output == 7) {
                        Info.Area = stoi(prop);
                    }

                    output++;
                }

                if (character == line_length - 1) {
                    for (read = line_length - 1; 0 < read; read--) {
                        if (debug) {
                            std::cout << "\n\nCharInt: " << read;
                            std::cout << "\nCharChar: "<< line[read];
                        }

                        if (line[read] == ' ') {
                            break;
                        }
                    }

                    for (int character = read + 1; character <= line_length - 1; character++) {
                        temp = line[character];
                        prop = prop + temp;

                        if (debug) {
                            std::cout << "\n\nTemp = " << temp;
                            std::cout << "\nProperty = " << prop;
                            std::cout << "\nOutput: " << output;
                        }

                        expected_ans = stoi(prop);
                    }

                    output++;
                }
            }

            if (x != "A" && x != "B" && x != "C" && x != "a" && x != "b" && x != "c" && x != "Area" && x != "area") {
                if (debug) {
                    std::cout << "\n" << "|" << x << "|";
                }

                std::cout << "\nPlease edit file to a valid aim.\n";
                main(0, param_remove);
                return;
            }

            if (Info.A != 0) {
                ++angle_count;
            }
            if (Info.B != 0) {
                ++angle_count;
            }
            if (Info.C != 0) {
                ++angle_count;
            }

            //input check
            if ((Info.A + Info.B + Info.C) > 180 || ((Info.A + Info.B + Info.C) == 180 && angle_count != 3) || ((Info.A + Info.B + Info.C) < 180 && angle_count == 3)) {
                error(6, file);
                std::exit(1);
            }

            if (Info.A || Info.B || Info.C == 90) {
                right_angled = true;
            }

            if (debug) {
                std::cout << "\n\nWanted prop: " << x;
                std::cout << "\nAngle's: " << Info.A << ", " << Info.B << ", " << Info.C;
                std::cout << "\nRadian's: " << Info.Ar << ", " << Info.Br << ", " << Info.Cr;
                std::cout << "\nSide's: " << Info.a << ", " << Info.b << ", " << Info.c;
                std::cout << "\nArea: " << Info.Area;
                std::cout << "\nExpected ans: " << expected_ans;
            }
            
            calculations(Info, angle_count, side_count, x);
        }
    }
    else {
        error(5, file);
    }
}

void repeatFunc() {
    std::string repeat;

    std::cout << "\nRepeat (y/n)? ";
    std::cin >> repeat;

    if (repeat == "y") {
        std::cout << "\n";
        main(0, param_remove);
        return;
    }
    else if (repeat == "n") {
        return;
    }
    else {
        std::cout << "\nEnter y or n.";
        repeatFunc();
    }
}

int main(int argc, char** argv) {
    /*for (int i = 1; i < argc; i++) {
        if (argv[i] == "-h" || "--help") {
            std::cout << "Help file";
        }
        else if (argv[i] == "-f" || "--fileInput") {
            fileInput(argv[i + 1]);
        }
        else {
            std::cout << "This is not a valid parameter.";
            main(1, param_remove);
            return 1;
        }
    }*/

    #ifdef _WIN32
    //userInput();

    //std::string input_file;
    //std::cout << "File to read from: ";
    //std::cin >> input_file;
    //fileInput(input_file);
    fileInput("file.txt");
    #else
    switch (getopt(argc, argv, "hfd:")) {
        case 'h':
            std::cout << "Help file";
        case 't':
            testing = true;
        case 'd':
            debug = true;
        case 'f':
            fileInput(optarg);
        default:
            userInput();
            repeatFunc();
    }
    #endif

    std::cout << "\n";
}