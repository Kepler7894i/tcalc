#include <iostream>

#ifndef _WIN32
#include <unistd.h>
#endif

int main(int argc, char** argv);
void userInput();
void fileInput(std::string file);

const double pi = 3.14159;
bool debug = false, right_angled = false;

int i, angle_count = 0, side_count = 0;
double ans = 0, inf_angle[3], inf_side[3];

std::string x;
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

void error(int error, std::string x) {
    switch (error) {
        case 1:
            std::cout << "\n\nError: Angles !> 180 degree.\n\n";
            break;
        case 2:
            std::cout << "Error: " << x << " is incalculabe with information provided.\n\n";
            break;
        case 3:
            std::cout << "Error: Two sides cannot be 0.\n\n";
            break;
        case 4:
            std::cout << "One or more inputted values is incorrect compared to other values.\n\n";
            userInput();
            break;
    }
}

void calculations(Triangle& Info, int angle_count, int side_count) {
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

    std::cout << x << " = " << ans << "\n";
}

void userInput() {
    Triangle Info;

    std::cout << "Wanted property: ";
    std::cin >> x;
    std::cout << "\n";

    if (x != "A" && x != "B" && x != "C" && x != "a" && x != "b" && x != "c" && x != "Area" && x != "area") {
        std::cout << "\nPlease enter a valid property.";
        userInput();
    }
    if (x != "A") {
        std::cout << "\tA = ";
        std::cin >> Info.A;
        degrees_radians(Info.Ar, Info.A);
    }
    if (x != "B") {
        std::cout << "\tB = ";
        std::cin >> Info.B;
        inf_angle[1] = Info.B;
        degrees_radians(Info.Br, Info.B);
    }
    if (x != "B") {
        std::cout << "\tC = ";
        std::cin >> Info.C;
        inf_angle[2] = Info.C;
        degrees_radians(Info.Cr, Info.C);
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
        inf_side[0] = Info.a;
    }
    if (x != "b") {
        std::cout << "\tb = ";
        std::cin >> Info.b;
        inf_side[1] = Info.b;
    }
    if (x != "c") {

        std::cout << "\tc = ";
        std::cin >> Info.c;
        inf_side[2] = Info.c;
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

    if (x != "Area" && "area") {
        std::cout << "\tArea = ";
        std::cin >> Info.Area;
    }

    std::cout << "\n";

    if (debug == true) {
        std::cout << "Angle's: " << Info.A << ", " << Info.B << ", " << Info.C << "\n";
        std::cout << "Radian's: " << Info.Ar << ", " << Info.Br << ", " << Info.Cr << "\n";
        std::cout << "Side's: " << Info.a << ", " << Info.b << ", " << Info.c << "\n";
        std::cout << "Area: " << Info.Area << "\n";
    }

    calculations(Info, angle_count, side_count);
}

//Implement automated testing from file
void fileInput(std::string file) {
    std::cout << file;
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
    userInput();
    #else
    switch (getopt(argc, argv, "hfd:")) {
        case 'h':
            std::cout << "Help file";
        case 'f':
            //Change to whatver should be passed after -f
            fileInput(optarg);
        case 'd':
            debug = true;
        default:
            std::cout << "hi";
            userInput();
            repeatFunc();
    }
    #endif
}
