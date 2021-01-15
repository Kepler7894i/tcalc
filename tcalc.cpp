#include <iostream>
#include <math.h>
#include <fstream>
#include <string>

#ifndef _WIN32
#include <unistd.h>
#endif

int main(int argc, char** argv);
void userInput();
void fileInput(std::string file);

const double pi = 3.14159;
char** param_remove;

bool debug = false, testing = false, right_angled = false;

class Triangle {
    public:
        double A = 0, B = 0, C = 0, Ar = 0, Br = 0, Cr = 0, a = 0, b = 0, c = 0, Area = 0;
        int angle_count = 0, side_count = 0;
};

double ans = 0;

void degrees_radians(double& degrees, double& radians) {
    radians = (degrees * pi) / 180;
}

void radians_degrees(double radians, double& degrees) {
    degrees = (radians * 180) / pi;
}

void error(int error_num, std::string action) {
    switch (error_num) {
        case 1: {
            std::cout << "\n\nError: Angles !<= 180 degree.";
        }
        case 2: {
            std::cout << "\n\nError: " << action << " is incalculabe with information provided.";
            break;
        }
        case 3: {
            std::cout << "\n\nError: Two sides cannot be 0.\n\n";
            break;
        }
        case 4: {
            std::cout << "\n\nOne or more inputted values is incorrect compared to other values.";
            userInput();
            break;
        }
        case 5: {
            std::cout << "\n\nError: Failed to open " << action << "\nFile to read from: ";
            std::string file;
            std::cin >> file;
            fileInput(file);
            break;
        }
        case 6: {
            int fixed;

            std::cout << "\n\nError: Incorrect angles in file." << "\nFixed? ";
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

            std::cout << "\n\nError: Incorrect number of properties in file. Fixed? ";
            std::cout << "\n\n       Correct layout:";
            std::cout << "\n         wanted_property A B C a b c Area expected_ans - Spaces between the values";
            std::cout << "\n                                                       - Capital letters are angles, lowercase letters are sides";
            std::cout << "\n                                                       - Opposite angles and sides should be the same letter";
            std::cout << "\n\nFixed? ";
            std::cin >> fixed;

            if (fixed == 1) {
                fileInput(action);
            }
            else if (fixed == 0) {
                return;
            }
            else {
                std::cout << "\nEnter 1 or 0.";
                error(7, action);
            }
        }
        case 8: {
            if (debug) {
                std::cout << "\n\nError: Invalid parameter " << action << " for tcalc.";
            }
            else {
                std::cout << "\n\nError: Invalid parameter for tcalc.";
            }

            exit(1);
        }
    }
}

void calculations(Triangle& Info, std::string x) {
    if (debug) {
        std::cout << "\n\nWanted prop: " << x;
        std::cout << "\nAngle's: " << Info.A << ", " << Info.B << ", " << Info.C;
        std::cout << "\nRadian's: " << Info.Ar << ", " << Info.Br << ", " << Info.Cr;
        std::cout << "\nSide's: " << Info.a << ", " << Info.b << ", " << Info.c;
        std::cout << "\nArea: " << Info.Area;
        std::cout << "\nAngle count: " << Info.angle_count;
        std::cout << "\nSide count: " << Info.side_count;
    }

    //Calc. angle's when 2 angle's known - 180 degree's in tirangle
    if (x == "A" && Info.B != 0 && Info.C != 0) {
        if (debug) {
            std::cout << "\n\nOp 1A";
        }

        ans = 180 - Info.B - Info.C;
    }
    else if (x == "B" && Info.A != 0 && Info.C != 0) {
        if (debug) {
            std::cout << "\n\nOp 1B";
        }

        ans = 180 - Info.A - Info.C;
    }
    else if (x == "C" && Info.B != 0 && Info.A != 0) {
        if (debug) {
            std::cout << "\n\nOp 1C";
        }

        ans = 180 - Info.B - Info.A;
    }
    //Calculate area when 2 side's and inbetween angle known
    else if ((x == "Area" || x == "area") && ((Info.a != 0 && Info.b != 0 && Info.C != 0) || (Info.b != 0 && Info.c != 0 && Info.A != 0) || (Info.c != 0 && Info.a != 0 && Info.B != 0))) {
        if (Info.a != 0 && Info.b != 0 && Info.C != 0) {
            if (debug) {
                std::cout << "\n\nOp 2A";
            }

            ans = 0.5 * Info.a * Info.b * sin(Info.Cr);
        }
        else if (Info.b != 0 && Info.c != 0 && Info.A != 0) {
            if (debug) {
                std::cout << "\n\nOp 2B";
            }

            ans = 0.5 * Info.b * Info.c * sin(Info.Ar);
        }
        else if (Info.c != 0 && Info.a != 0 && Info.B != 0) {
            if (debug) {
                std::cout << "\n\nOp 2C";
            }

            ans = 0.5 * Info.c * Info.a * sin(Info.Br);
        }
    }
    //Calculate side when area, a side and an angle is known
    else if (x == "a" && Info.Area != 0 && ((Info.b != 0 && Info.C != 0) || (Info.c != 0 && Info.B != 0))) {
        if (Info.b != 0 && Info.C != 0) {
            if (debug) {
                std::cout << "\n\nOp 3A";
            }

            ans = Info.Area / (0.5 * Info.b * sin(Info.Cr));
        }
        else if (Info.c != 0 && Info.B != 0) {
            if (debug) {
                std::cout << "\n\nOp 3B";
            }

            ans = Info.Area / (0.5 * Info.c * sin(Info.Br));
        }
    }
    else if (x == "b" && Info.Area != 0 && ((Info.a != 0 && Info.C != 0) || (Info.c != 0 && Info.A != 0))) {
        if (Info.a != 0 && Info.C != 0) {
            if (debug) {
                std::cout << "\n\nOp 3C";
            }

            ans = Info.Area / (0.5 * Info.a * sin(Info.Cr));
        }
        else if (Info.c != 0 && Info.A != 0) {
            if (debug) {
                std::cout << "\n\nOp 3D";
            }

            ans = Info.Area / (0.5 * Info.c * sin(Info.Ar));
        }
    }
    else if (x == "c" && Info.Area != 0 && ((Info.b != 0 && Info.A != 0) || (Info.a != 0 && Info.B != 0))) {
        if (Info.b != 0 && Info.C != 0) {
            if (debug) {
                std::cout << "\n\nOp 3E";
            }

            ans = Info.Area / (0.5 * Info.b * sin(Info.Ar));
        }
        else if (Info.c != 0 && Info.B != 0) {
            if (debug) {
                std::cout << "\n\nOp 3F";
            }

            ans = Info.Area / (0.5 * Info.a * sin(Info.Br));
        }
    }
    //Calculate angle when area and 2 side's are known
    else if (x == "A" && Info.Area != 0 && Info.b != 0 && Info.c != 0) {
        if (debug) {
            std::cout << "\n\nOp 4a";
        }

        ans = asin(Info.Area / (0.5 * Info.b * Info.c));
    }
    else if (x == "B" && Info.Area != 0 && Info.a != 0 && Info.c != 0) {
        if (debug) {
            std::cout << "\n\nOp 4B";
        }

        ans = asin(Info.Area / (0.5 * Info.a * Info.c));
    }
    else if (x == "A" && Info.Area != 0 && Info.a != 0 && Info.b != 0) {
        if (debug) {
            std::cout << "\n\nOp 4C";
        }

        ans = asin(Info.Area / (0.5 * Info.a * Info.b));
    }
    else if ((Info.A == 90 || Info.B == 90 || Info.C == 90) && (x == "a" || x == "b" || x == "c") && Info.side_count == 2) {
        //Calc. side's when 2 side's known - pyth
        if (x == "a" || x == "b" || x == "c" && Info.side_count == 2) {
            if (Info.A == 90) {
                if (x == "a" && Info.b != 0 && Info.c != 0) {
                    if (debug) {
                        std::cout << "\n\nOp 5A";
                    }

                    ans = sqrt(pow(Info.b, 2) + pow(Info.c, 2));
                }
                else if (x == "b" && Info.a != 0 && Info.c != 0) {
                    if (debug) {
                        std::cout << "\n\nOp 5B";
                    }

                    ans = sqrt(pow(Info.a, 2) - pow(Info.c, 2));
                }
                else if (x == "c" && Info.a != 0 && Info.b != 0) {
                    if (debug) {
                        std::cout << "\n\nOp 5C";
                    }

                    ans = sqrt(pow(Info.a, 2) - pow(Info.b, 2));
                }
            }
            else if (Info.B == 90) {
                if (x == "a" && Info.b != 0 && Info.c != 0) {
                    if (debug) {
                        std::cout << "\n\nOp 5D";
                    }


                    ans = sqrt(pow(Info.b, 2) - pow(Info.c, 2));
                }
                else if (x == "b" && Info.a != 0 && Info.c != 0) {
                    if (debug) {
                        std::cout << "\n\nOp 5E";
                    }

                    ans = sqrt(pow(Info.a, 2) + pow(Info.c, 2));
                }
                else if (x == "c" && Info.a != 0 && Info.b != 0) {
                    if (debug) {
                        std::cout << "\n\nOp 5F";
                    }

                    ans = sqrt(pow(Info.b, 2) - pow(Info.a, 2));
                }
            }
            else if (Info.C == 90) {
                if (x == "a" && Info.b != 0 && Info.c != 0) {
                    if (debug) {
                        std::cout << "\n\nOp 5G";
                    }

                    ans = sqrt(pow(Info.c, 2) - pow(Info.b, 2));
                }
                else if (x == "b" && Info.a != 0 && Info.c != 0) {
                    if (debug) {
                        std::cout << "\n\nOp 5H";
                    }

                    ans = sqrt(pow(Info.c, 2) - pow(Info.a, 2));
                }
                else if (x == "c" && Info.a != 0 && Info.b != 0) {
                    if (debug) {
                        std::cout << "\n\nOp 5I";
                    }

                    ans = sqrt(pow(Info.a, 2) + pow(Info.b, 2));
                }
            }
        }
        //Calc. side's when 1 side and 1 >= angle known (1 must be 90) - trig (functions)
        else if (x == "a" || x == "b" || x == "c" && Info.angle_count >= 1 && Info.side_count == 1) {
            if (Info.A == 90) {
                if (x == "a") {
                    if (Info.B != 0) {
                        if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6A";
                            }

                            ans = Info.b / sin(Info.Br);
                        }
                        else if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6B";
                            }

                            ans = Info.c / cos(Info.Br);
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6C";
                            }

                            ans = Info.c / sin(Info.Cr);
                        }
                        else if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6D";
                            }

                            ans = Info.b / cos(Info.Cr);
                        }
                    }
                }
                else if (x == "b") {
                    if (Info.B != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6E";
                            }

                            ans = sin(Info.Br) * Info.a;
                        }
                        else if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6F";
                            }

                            ans = tan(Info.Br) * Info.c;
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6G";
                            }

                            ans = cos(Info.Cr) * Info.a;
                        }
                        else if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6H";
                            }

                            ans = Info.c / tan(Info.Cr);
                        }
                    }
                }
                else if (x == "c") {
                    if (Info.B != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6I";
                            }

                            ans = cos(Info.Br) * Info.a;
                        }
                        else if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6J";
                            }

                            ans = Info.b / tan(Info.Br);
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6K";
                            }

                            ans = sin(Info.Cr) * Info.a;
                        }
                        else if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6L";
                            }

                            ans = tan(Info.Cr) * Info.b;
                        }
                    }
                }
            }
            else if (Info.B == 90) {
                if (x == "a") {
                    if (Info.A != 0) {
                        if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6M";
                            }

                            ans = sin(Info.Ar) * Info.b;
                        }
                        else if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6N";
                            }

                            ans = tan(Info.Ar) * Info.c;
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6O";
                            }

                            ans = Info.c / tan(Info.Cr);
                        }
                        else if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6P";
                            }

                            ans = cos(Info.Cr) * Info.b;
                        }
                    }
                }
                else if (x == "b") {
                    if (Info.A != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6Q";
                            }

                            ans = Info.a / sin(Info.Ar);
                        }
                        else if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6R";
                            }

                            ans = Info.c / cos(Info.Ar);
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6S";
                            }

                            ans = Info.a / cos(Info.Cr);
                        }
                        else if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6T";
                            }

                            ans = Info.c / sin(Info.Cr);
                        }
                    }
                }
                else if (x == "c") {
                    if (Info.A != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6U";
                            }

                            ans = Info.a / tan(Info.Ar);
                        }
                        else if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6V";
                            }

                            ans = cos(Info.Br) * Info.b;
                        }
                    }
                    else if (Info.C != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6W";
                            }

                            ans = tan(Info.Cr) * Info.a;
                        }
                        else if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6X";
                            }

                            ans = sin(Info.Cr) * Info.b;
                        }
                    }
                }
            }
            else if (Info.C == 90) {
                if (x == "a") {
                    if (Info.A != 0) {
                        if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6Y";
                            }

                            ans = tan(Info.Br) * Info.b;
                        }
                        else if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6Z";
                            }

                            ans = sin(Info.Br) * Info.c;
                        }
                    }
                    else if (Info.B != 0) {
                        if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6AZ";
                            }

                            ans = Info.b / sin(Info.Br);
                        }
                        else if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6BZ";
                            }

                            ans = cos(Info.Br) * Info.c;
                        }
                    }
                }
                else if (x == "b") {
                    if (Info.A != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6CZ";
                            }

                            ans = Info.a / tan(Info.Ar);
                        }
                        else if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6DZ";
                            }

                            ans = cos(Info.Ar) * Info.c;
                        }
                    }
                    else if (Info.B != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6EZ";
                            }

                            ans = tan(Info.Br) * Info.a;
                        }
                        else if (Info.c != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6FZ";
                            }

                            ans = sin(Info.Br) * Info.c;
                        }
                    }
                }
                else if (x == "c") {
                    if (Info.A != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6GZ";
                            }

                            ans = Info.a / sin(Info.Ar);
                        }
                        else if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6HZ";
                            }

                            ans = Info.b / cos(Info.Ar);
                        }
                    }
                    else if (Info.B != 0) {
                        if (Info.a != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6IZ";
                            }

                            ans = Info.a / cos(Info.Br);
                        }
                        else if (Info.b != 0) {
                            if (debug) {
                                std::cout << "\n\nOp 6JZ";
                            }

                            ans = Info.b / sin(Info.Br);
                        }
                    }
                }
            }
        }
        //Calc. angle's when 2 sides known and 90 angle known - trig (functions)
        else if (90 == Info.A || Info.B || Info.C && Info.side_count == 2) {
            //Hyp = opp of 90 degree angle, Opp = opp of angle to be calculated, Adj = other side
            if (Info.A == 90) {
                if (x == "B") {
                    if (Info.a != 0 && Info.b != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7A";
                        }

                        radians_degrees(asin(Info.b / Info.a), ans);
                    }
                    else if (Info.a != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7B";
                        }

                        radians_degrees(acos(Info.c / Info.a), ans);
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7C";
                        }

                        radians_degrees(atan(Info.b / Info.c), ans);
                    }
                }
                else if (x == "C") {
                    if (Info.a != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7D";
                        }

                        radians_degrees(asin(Info.c / Info.a), ans);
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7E";
                        }

                        radians_degrees(acos(Info.b / Info.a), ans);
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7F";
                        }

                        radians_degrees(atan(Info.c / Info.b), ans);
                    }
                }
            }
            else if (Info.B == 90) {
                if (x == "A") {
                    if (Info.a != 0 && Info.b != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7G";
                        }

                        radians_degrees(asin(Info.a / Info.b), ans);
                    }
                    else if (Info.a != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7H";
                        }

                        radians_degrees(acos(Info.c / Info.a), ans);
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7I";
                        }

                        radians_degrees(atan(Info.b / Info.c), ans);
                    }
                }
                else if (x == "C") {
                    if (Info.c != 0 && Info.b != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7J";
                        }

                        radians_degrees(asin(Info.c / Info.b), ans);
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7K";
                        }

                        radians_degrees(acos(Info.b / Info.a), ans);
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7L";
                        }

                        radians_degrees(atan(Info.c / Info.b), ans);
                    }
                }
            }
            else if (Info.C == 90) {
                if (x == "A") {
                    if (Info.a != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7M";
                        }

                        radians_degrees(asin(Info.a / Info.c), ans);
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7N";
                        }

                        radians_degrees(acos(Info.b / Info.c), ans);
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7O";
                        }

                        radians_degrees(atan(Info.a / Info.b), ans);
                    }
                }
                else if (x == "B") {
                    if (Info.b != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7P";
                        }

                        radians_degrees(asin(Info.b / Info.c), ans);
                    }
                    else if (Info.a != 0 && Info.c != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7Q";
                        }

                        radians_degrees(acos(Info.a / Info.c), ans);
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        if (debug) {
                            std::cout << "\n\nOp 7R";
                        }

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
                if (debug) {
                    std::cout << "\n\nOp 8A";
                }

                radians_degrees(asin(Info.a * sin(Info.Br) / Info.b), ans);
            }
            else if (x == "A" && Info.a != 0 && Info.C != 0 && Info.c != 0) {
                if (debug) {
                    std::cout << "\n\nOp 8B";
                }

                radians_degrees(asin(Info.a * sin(Info.Cr) / Info.c), ans);
            }
            else if (x == "B" && Info.b != 0 && Info.A != 0 && Info.a != 0) {
                if (debug) {
                    std::cout << "\n\nOp 8C";
                }

                radians_degrees(asin(Info.b * sin(Info.Ar) / Info.a), ans);
            }
            else if (x == "B" && Info.a != 0 && Info.B != 0 && Info.b != 0) {
                if (debug) {
                    std::cout << "\n\nOp 8D";
                }

                radians_degrees(asin(Info.b * sin(Info.Cr) / Info.c), ans);
            }
            else if (x == "C" && Info.a != 0 && Info.B != 0 && Info.b != 0) {
                if (debug) {
                    std::cout << "\n\nOp 8E";
                }

                radians_degrees(asin(Info.c * sin(Info.Ar) / Info.a), ans);
            }
            else if (x == "C" && Info.a != 0 && Info.B != 0 && Info.b != 0) {
                if (debug) {
                    std::cout << "\n\nOp 8F";
                }

                radians_degrees(asin(Info.c * sin(Info.Br) / Info.b), ans);
            }
            //Calc. angle's when 3 side's known - trig (cosine rule)
            if (Info.a != 0 && Info.b != 0 && Info.c != 0) {
                if (x == "A") {
                    if (debug) {
                        std::cout << "\n\nOp 9A";
                    }

                    radians_degrees(acos((pow(Info.b, 2) + pow(Info.c, 2) - pow(Info.a, 2)) / (2 * Info.b * Info.c)), ans);
                }
                /*else if (x == "A" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radians_degrees(ans, acos((pow(Info.b, 2) + pow(Info.c, 2) - pow(Info.a, 2)) / (2 * Info.a * Info.c)));
                }
                else if (x == "A" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radians_degrees(ans, acos((pow(Info.b, 2) + pow(Info.c, 2) - pow(Info.a, 2)) / (2 * Info.a * Info.b)));
                }*/
                else if (x == "B") {
                    if (debug) {
                        std::cout << "\n\nOp 9B";
                    }

                    radians_degrees(acos((pow(Info.a, 2) + pow(Info.c, 2) - pow(Info.b, 2)) / (2 * Info.a * Info.c)), ans);
                }
                /*else if (x == "B" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radians_degrees(ans, acos((pow(Info.a, 2) + pow(Info.c, 2) - pow(Info.b, 2)) / (2 * Info.b * Info.c)));
                }
                else if (x == "B" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radians_degrees(ans, acos((pow(Info.a, 2) + pow(Info.c, 2) - pow(Info.b, 2)) / (2 * Info.a * Info.b)));
                }*/
                else if (x == "C") {
                    if (debug) {
                        std::cout << "\n\nOp 9C";
                    }

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
        else if (x == "a" || x == "b" || x == "c" && Info.angle_count == 2 && Info.side_count == 1) {
            //Calc. side's when 2 angle's & 1 side known - trig (sine rule)
            if (x == "a" && Info.A != 0 && Info.B != 0 && Info.b != 0) {
                if (debug) {
                    std::cout << "\n\nOp 10A";
                }

                ans = sin(Info.Ar) * Info.b / sin(Info.Br);
            }
            else if (x == "a" && Info.A != 0 && Info.C != 0 && Info.c != 0) {
                if (debug) {
                    std::cout << "\n\nOp 10B";
                }

                ans = sin(Info.Ar) * Info.c / sin(Info.Cr);
            }
            else if (x == "b" && Info.B != 0 && Info.A != 0 && Info.a != 0) {
                if (debug) {
                    std::cout << "\n\nOp 10C";
                }

                ans = sin(Info.Br) * Info.a / sin(Info.Ar);
            }
            else if (x == "b" && Info.B != 0 && Info.C != 0 && Info.c != 0) {
                if (debug) {
                    std::cout << "\n\nOp 10D";
                }

                ans = sin(Info.Br) * Info.c / sin(Info.Cr);
            }
            else if (x == "c" && Info.C != 0 && Info.A != 0 && Info.a != 0) {
                if (debug) {
                    std::cout << "\n\nOp 10E";
                }

                ans = sin(Info.Cr) * Info.a / sin(Info.Ar);
            }
            else if (x == "c" && Info.C != 0 && Info.B != 0 && Info.b != 0) {
                if (debug) {
                    std::cout << "\n\nOp 10F";
                }

                ans = sin(Info.Cr) * Info.b / sin(Info.Br);
            }
            //Calc. side's when 1 angle and 2 side's known - trig (cosine rule)
            else if (x == "a" && Info.A != 0 && Info.b != 0 && Info.c != 0) {
                if (debug) {
                    std::cout << "\n\nOp 11A";
                }

                ans = sqrt((pow(Info.b, 2)) + (pow(Info.c, 2)) - (2 * Info.b * Info.c * cos(Info.Ar)));
            }
            else if (x == "a" && Info.B != 0 && Info.b != 0 && Info.c != 0) {
                if (debug) {
                    std::cout << "\n\nOp 11B";
                }

                ans = sqrt((pow(Info.b, 2)) - (pow(Info.c, 2)) + (2 * Info.b * Info.c * cos(Info.Br)));
            }
            else if (x == "a" && Info.C != 0 && Info.c != 0 && Info.b != 0) {
                if (debug) {
                    std::cout << "\n\nOp 11C";
                }

                ans = sqrt((pow(Info.c, 2)) - (pow(Info.b, 2)) + (2 * Info.c * Info.b * cos(Info.Cr)));
            }
            else if (x == "b" && Info.B != 0 && Info.a != 0 && Info.c != 0) {
                if (debug) {
                    std::cout << "\n\nOp 11D";
                }

                ans = sqrt((pow(Info.a, 2)) + (pow(Info.c, 2)) - (2 * Info.a * Info.c * cos(Info.Br)));
            }
            else if (x == "b" && Info.A != 0 && Info.a != 0 && Info.c != 0) {
                if (debug) {
                    std::cout << "\n\nOp 11E";
                }

                ans = sqrt((pow(Info.b, 2)) - (pow(Info.c, 2)) + (2 * Info.a * Info.c * cos(Info.Ar)));
            }
            else if (x == "b" && Info.C != 0 && Info.c != 0 && Info.a != 0) {
                if (debug) {
                    std::cout << "\n\nOp 11F";
                }

                ans = sqrt((pow(Info.c, 2)) - (pow(Info.a, 2)) + (2 * Info.c * Info.a * cos(Info.Cr)));
            }
            else if (x == "c" && Info.C != 0 && Info.a != 0 && Info.b != 0) {
                if (debug) {
                    std::cout << "\n\nOp 11G";
                }

                ans = sqrt((pow(Info.a, 2)) + (pow(Info.b, 2)) - (2 * Info.a * Info.b * cos(Info.Cr)));
            }
            else if (x == "c" && Info.A != 0 && Info.a != 0 && Info.b != 0) {
                if (debug) {
                    std::cout << "\n\nOp 11H";
                }

                ans = sqrt((pow(Info.a, 2)) - (pow(Info.b, 2)) + (2 * Info.a * Info.b * cos(Info.Ar)));
            }
            else if (x == "c" && Info.B != 0 && Info.b != 0 && Info.a != 0) {
                if (debug) {
                    std::cout << "\n\nOp 11I";
                }

                ans = sqrt((pow(Info.b, 2)) - (pow(Info.a, 2)) + (2 * Info.b * Info.a * cos(Info.Br)));
            }
        }
    }
    else {
        error(2, x);
        return;
    }

    std::cout << "\n" << x << " = " << ans;

    return;
}

void userInput() {
    Triangle Info;

    std::string x;
    double expected_ans = 0;

    std::cout << "\nWanted prop: ";
    std::cin >> x;
    std::cout << "\n";

    if (x != "A" && x != "B" && x != "C" && x != "a" && x != "b" && x != "c" && x != "Area" && x != "area") {
        std::cout << "\nPlease enter a valid aim.";
        userInput();
        exit(0);
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
    if (x != "C") {
        std::cout << "\tC = ";
        std::cin >> Info.C;
        degrees_radians(Info.C, Info.Cr);
    }

    if (Info.A != 0) {
        ++Info.angle_count;
    }
    if (Info.B != 0) {
        ++Info.angle_count;
    }
    if (Info.C != 0) {
        ++Info.angle_count;
    }

    //input check
    if ((Info.A + Info.B + Info.C) > 180 || ((Info.A + Info.B + Info.C) == 180 && Info.angle_count != 3) || ((Info.A + Info.B + Info.C) < 180 && Info.angle_count == 3)) {
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
        ++Info.side_count;
    }
    if (Info.b != 0) {
        ++Info.side_count;
    }
    if (Info.c != 0) {
        ++Info.side_count;
    }

    if (x != "Area" && x != "area") {
        std::cout << "\tArea = ";
        std::cin >> Info.Area;
    }

    if (testing) {
        std::cout << "\tExpected ans = ";
        std::cin >> expected_ans;
    }

    if (debug) {
        std::cout << "\n\nWanted prop: " << x;
        std::cout << "\nAngle's: " << Info.A << ", " << Info.B << ", " << Info.C;
        std::cout << "\nRadian's: " << Info.Ar << ", " << Info.Br << ", " << Info.Cr;
        std::cout << "\nSide's: " << Info.a << ", " << Info.b << ", " << Info.c;
        std::cout << "\nArea: " << Info.Area;
        std::cout << "\nAngle count: " << Info.angle_count;
        std::cout << "\nSide count: " << Info.side_count;
        std::cout << "\nExpected ans: " << expected_ans;
    }

    calculations(Info, x);

    if (testing) {
        std::cout << "\nExpected ans = " << expected_ans;

        double margin_of_error_double = ans - expected_ans;
        std::cout << "\n\nError (double) = " << margin_of_error_double;
        float margin_of_error_float = ans - expected_ans;
        std::cout << "\nError (float) = " << margin_of_error_float;
        int margin_of_error_int = ans - expected_ans;
        std::cout << "\nError (int) = " << margin_of_error_int;
    }
}

void fileInput(std::string file) {
    Triangle Info;

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
            int prop_count = 0, output = 0;

            Info.angle_count = 0;
            Info.side_count = 0;

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
                exit(1);
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
                        Info.A = stod(prop);
                        degrees_radians(Info.A, Info.Ar);
                    }
                    else if (output == 2) {
                        Info.B = stod(prop);
                        degrees_radians(Info.B, Info.Br);
                    }
                    else if (output == 3) {
                        Info.C = stod(prop);
                        degrees_radians(Info.C, Info.Cr);
                    }
                    else if (output == 4) {
                        Info.a = stod(prop);
                    }
                    else if (output == 5) {
                        Info.b = stod(prop);
                    }
                    else if (output == 6) {
                        Info.c = stod(prop);
                    }
                    else if (output == 7) {
                        Info.Area = stod(prop);
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

                        expected_ans = stod(prop);
                    }

                    output++;
                }
            }

            if (Info.A != 0) {
                ++Info.angle_count;
            }
            if (Info.B != 0) {
                ++Info.angle_count;
            }
            if (Info.C != 0) {
                ++Info.angle_count;
            }

            if (Info.a != 0) {
                ++Info.side_count;
            }
            if (Info.b != 0) {
                ++Info.side_count;
            }
            if (Info.c != 0) {
                ++Info.side_count;
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
                std::cout << "\nAngle count: " << Info.angle_count;
                std::cout << "\nSide count: " << Info.side_count;
                std::cout << "\nExpected ans: " << expected_ans;
            }

            if (x != "A" && x != "B" && x != "C" && x != "a" && x != "b" && x != "c" && x != "Area" && x != "area") {
                if (debug) {
                    std::cout << "\n" << "|" << x << "|";
                }

                std::cout << "\nPlease edit file to a valid aim.\n";
                main(0, param_remove);
                return;
            }

            //input check
            if ((Info.A + Info.B + Info.C) > 180 || ((Info.A + Info.B + Info.C) == 180 && Info.angle_count != 3) || ((Info.A + Info.B + Info.C) < 180 && Info.angle_count == 3)) {
                error(6, file);
                exit(1);
            }
            
            calculations(Info, x);

            if (testing) {
                std::cout << "\nExpected ans = " << expected_ans;

                double margin_of_error_double = ans - expected_ans;
                std::cout << "\n\nError (double) = " << margin_of_error_double;
                float margin_of_error_float = ans - expected_ans;
                std::cout << "\nError (float) = " << margin_of_error_float;
                int margin_of_error_int = ans - expected_ans;
                std::cout << "\nError (int) = " << margin_of_error_int;
            }
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

void hi() {
    std::cout << "hi";
}

int main(int argc, char** argv) {
    #ifdef _WIN32

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

    userInput();
    repeatFunc();

    std::cout << "\n\n";

    return 0;

    //std::string input_file;
    //std::cout << "File to read from: ";
    //std::cin >> input_file;
    //fileInput(input_file);
    //return 0;

    #else

    char argument;
    std::string argument_file;
    bool help = false, fileMode = false;

    while (argument = getopt(argc, argv, "htdf:")) {
        switch (argument) {
            case 'h': {
                help = true;
            }
            case 't': {
                testing = true;
                break;
            }
            case 'd': {
                debug = true;
                break;
            }
            case 'f': {
                fileMode = true;
                argument_file = optarg;
                break;
            }
            case '?': {
                std::string argument_error(1, argument);
                error(8, argument_error);
                exit(1);
            }
            default: {
                goto exit_loop;
            }
        }
    }

    exit_loop: ;

    if (debug) {
        std::cout << "\n\nHelp: " << help;
        std::cout << "\nTesting: " << testing;
        std::cout << "\nDebug: " << debug;
        std::cout << "\nfileMode: " << fileMode;
        std::cout << "\n";
    }

    if (help) {
        std::cout << "\nUsage: tcalc [OPTION/FILE IF APPLICABLE]...";
        std::cout << "\n\nWith no OPTION(s) default execute userInput()";
        std::cout << "\n\n  -h          Output help file";
        std::cout << "\n  -t          Set bool testing = true";
        std::cout << "\n  -d          Set bool debug = true";
        std::cout << "\n  -f [file]   Override default and execute fileInput(file)";
        std::cout << "\n\nSource code and documentation: <https://github.com/Kepler7894i/triangle-calculator>";
        exit(0);
    }

    if (fileMode) {
        fileInput(argument_file);
    }
    else if (!fileMode) {
        userInput();
    }

    std::cout << "\n\n";
    exit(0);

    #endif
}