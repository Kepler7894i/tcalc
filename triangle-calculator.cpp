#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>
using namespace std;

double pi = 3.14159;

void radianDegrees(double& ansReference, double calcOutput) {
    ansReference = (calcOutput * 180) / pi;
}

void error(int error, string x) {
    switch (error) {
        case 1:
            cout << "\n\n" << "Error: Invalid angle input" << "\n";
            cout << "Please enter valid angle's (must add to 180 degree's)." << "\n\n";
        case 2:
            cout << "Error: " << x << " is incalculabe with information provided." << "\n\n";
    }
}

int main() {
    int i, inf_angles_present = 0, inf_sides_present = 0, inf_values_present = 0;
    double ans = 0, inf_angle[3], inf_radian[3], inf_side[3];
    string x;

    class Triangle
    {
    public:
        double A = 0, B = 0, C = 0;
        double Ar = 0, Br = 0, Cr = 0;
        double a = 0, b = 0, c = 0;
        double area = 0;

        void degreesRadians(double& radians, double& radians_array, double& degrees)
        {
            radians = (degrees * pi) / 180;
            radians_array = radians;
        }
    };

    Triangle Info;

    cout << "Please input corresponding angle and side value's. Enter 0 if no value present" << "\n";
    cout << "(Capital=Angle, Lowercase=Side.)" << "\n" << "\n";

    cout << "\t" << "A = ";
    cin >> Info.A;
    Info.degreesRadians(Info.Ar, inf_radian[0], Info.A);

    cout << "\t" << "B = ";
    cin >> Info.B;
    inf_angle[1] = Info.B;
    Info.degreesRadians(Info.Br, inf_radian[1], Info.B);

    cout << "\t" << "C = ";
    cin >> Info.C;
    inf_angle[2] = Info.C;
    Info.degreesRadians(Info.Cr, inf_radian[2], Info.C);

    //input check
    if ((Info.A + Info.B + Info.C) > 180) {
        error(1, x);
        main();
        return 1;
    }

    cout << "\t" << "a = ";
    cin >> Info.a;
    inf_side[0] = Info.a;

    cout << "\t" << "b = ";
    cin >> Info.b;
    inf_side[1] = Info.b;

    cout << "\t" << "c = ";
    cin >> Info.c;
    inf_side[2] = Info.c;

    cout << "\t" << "area = ";
    cin >> Info.area;

    cout << "\n";

    cout << "Angle's: " << Info.A << ", " << Info.B << ", " << Info.C << "\n";
    cout << "Radian's: " << Info.Ar << ", " << Info.Br << ", " << Info.Cr << "\n";
    cout << "Side's: " << Info.a << ", " << Info.b << ", " << Info.c << "\n";

    //error - inf_values_present always = 0
    for (i = 0; i < 3; i++) {
        if (inf_angle[i] != 0) {
            ++inf_angles_present;
        }
        if (inf_side[i] != 0) {
            ++inf_sides_present;
        }
    }

    inf_values_present = inf_angles_present + inf_sides_present;
    cout << "No. of value's present: " << inf_values_present << "\n" << "\n";

    cout << "What would you like to calculate (capital=angle, lowercase=side): ";
    cin >> x;
    cout << "\n";

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
    else if (x == "area" && ((Info.a != 0 && Info.b != 0 && Info.C != 0) || (Info.b != 0 && Info.c != 0 && Info.A != 0) || (Info.c != 0 && Info.a != 0 && Info.B != 0))) {
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
    else if (x == "a" && Info.area != 0 && ((Info.b != 0 && Info.C != 0) || (Info.c != 0 && Info.B != 0))) {
        if (Info.b != 0 && Info.C != 0) {
            ans = Info.area / (0.5 * Info.b * sin(Info.Cr));
        }
        else if (Info.c != 0 && Info.B != 0) {
            ans = Info.area / (0.5 * Info.c * sin(Info.Br));
        }
    }
    else if (x == "b" && Info.area != 0 && ((Info.a != 0 && Info.C != 0) || (Info.c != 0 && Info.A != 0))) {
        if (Info.a != 0 && Info.C != 0) {
            ans = Info.area / (0.5 * Info.a * sin(Info.Cr));
        }
        else if (Info.c != 0 && Info.A != 0) {
            ans = Info.area / (0.5 * Info.c * sin(Info.Ar));
        }
    }
    else if (x == "c" && Info.area != 0 && ((Info.b != 0 && Info.A != 0) || (Info.a != 0 && Info.B != 0))) {
        if (Info.b != 0 && Info.C != 0) {
            ans = Info.area / (0.5 * Info.b * sin(Info.Ar));
        }
        else if (Info.c != 0 && Info.B != 0) {
            ans = Info.area / (0.5 * Info.a * sin(Info.Br));
        }
    }
    //Calculate angle when area and 2 side's are known
    else if (x == "A" && Info.area != 0 && Info.b != 0 && Info.c != 0) {
        ans = asin(Info.area / (0.5 * Info.b * Info.c));
    }
    else if (x == "B" && Info.area != 0 && Info.a != 0 && Info.c != 0) {
        ans = asin(Info.area / (0.5 * Info.a * Info.c));
    }
    else if (x == "A" && Info.area != 0 && Info.a != 0 && Info.b != 0) {
        ans = asin(Info.area / (0.5 * Info.a * Info.b));
    }
    else if (Info.A == 90 || Info.B == 90 || Info.C == 90) {
        //Calc. side's when 2 side's known - pyth
        if ((x == "a" || x == "b" || x == "c") && inf_sides_present == 2) {
            if (Info.A == 90) {
                if (x == "a" && Info.b != 0 && Info.c != 0) {
                    ans = sqrt(pow(Info.b, 2) + pow(Info.c, 2));
                }
                else if (x == "b" && Info.a != 0 && Info.c != 0) {
                    ans = sqrt(pow(Info.a, 2) - pow(Info.c, 2));
                }
                else if (x == "c" && Info.a != 0 && Info.b != 0) {
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
        else if ((x == "a" || x == "b" || x == "c") && inf_angles_present >= 1 && inf_sides_present == 1) {
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
        else if ((Info.A == 90 || Info.B == 90 || Info.C == 90) && inf_sides_present == 2) {
            //Hyp = opp of 90 degree angle, Opp = opp of angle to be calculated, Adj = other side
            if (Info.A == 90) {
                if (x == "B") {
                    if (Info.a != 0 && Info.b != 0) {
                        radianDegrees(ans, asin(Info.b / Info.a));
                    }
                    else if (Info.a != 0 && Info.c != 0) {
                        radianDegrees(ans, acos(Info.c / Info.a));
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        radianDegrees(ans, atan(Info.b / Info.c));
                    }
                }
                else if (x == "C") {
                    if (Info.a != 0 && Info.c != 0) {
                        radianDegrees(ans, asin(Info.c / Info.a));
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        radianDegrees(ans, acos(Info.b / Info.a));
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        radianDegrees(ans, atan(Info.c / Info.b));
                    }
                }
            }
            else if (Info.B == 90) {
                if (x == "A") {
                    if (Info.a != 0 && Info.b != 0) {
                        radianDegrees(ans, asin(Info.a / Info.b));
                    }
                    else if (Info.a != 0 && Info.c != 0) {
                        radianDegrees(ans, acos(Info.c / Info.a));
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        radianDegrees(ans, atan(Info.b / Info.c));
                    }
                }
                else if (x == "C") {
                    if (Info.c != 0 && Info.b != 0) {
                        radianDegrees(ans, asin(Info.c / Info.b));
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        radianDegrees(ans, acos(Info.b / Info.a));
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        radianDegrees(ans, atan(Info.c / Info.b));
                    }
                }
            }
            else if (Info.C == 90) {
                if (x == "A") {
                    if (Info.a != 0 && Info.c != 0) {
                        radianDegrees(ans, asin(Info.a / Info.c));
                    }
                    else if (Info.b != 0 && Info.c != 0) {
                        radianDegrees(ans, acos(Info.b / Info.c));
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        radianDegrees(ans, atan(Info.a / Info.b));
                    }
                }
                else if (x == "B") {
                    if (Info.b != 0 && Info.c != 0) {
                        radianDegrees(ans, asin(Info.b / Info.c));
                    }
                    else if (Info.a != 0 && Info.c != 0) {
                        radianDegrees(ans, acos(Info.a / Info.c));
                    }
                    else if (Info.a != 0 && Info.b != 0) {
                        radianDegrees(ans, atan(Info.b / Info.a));
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
                radianDegrees(ans, asin(Info.a * sin(Info.Br) / Info.b));
            }
            else if (x == "A" && Info.a != 0 && Info.C != 0 && Info.c != 0) {
                radianDegrees(ans, asin(Info.a * sin(Info.Cr) / Info.c));
            }
            else if (x == "B" && Info.b != 0 && Info.A != 0 && Info.a != 0) {
                radianDegrees(ans, asin(Info.b * sin(Info.Ar) / Info.a));
            }
            else if (x == "B" && Info.a != 0 && Info.B != 0 && Info.b != 0) {
                radianDegrees(ans, asin(Info.b * sin(Info.Cr) / Info.c));
            }
            else if (x == "C" && Info.a != 0 && Info.B != 0 && Info.b != 0) {
                radianDegrees(ans, asin(Info.c * sin(Info.Ar) / Info.a));
            }
            else if (x == "C" && Info.a != 0 && Info.B != 0 && Info.b != 0) {
                radianDegrees(ans, asin(Info.c * sin(Info.Br) / Info.b));
            }
            //Calc. angle's when 3 side's known - trig (cosine rule)
            if (Info.a != 0 && Info.b != 0 && Info.c != 0) {
                if (x == "A") {
                    radianDegrees(ans, acos((pow(Info.b, 2) + pow(Info.c, 2) - pow(Info.a, 2)) / (2 * Info.b * Info.c)));
                }
                /*else if (x == "A" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radianDegrees(ans, acos((pow(Info.b, 2) + pow(Info.c, 2) - pow(Info.a, 2)) / (2 * Info.a * Info.c)));
                }
                else if (x == "A" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radianDegrees(ans, acos((pow(Info.b, 2) + pow(Info.c, 2) - pow(Info.a, 2)) / (2 * Info.a * Info.b)));
                }*/
                else if (x == "B") {
                    radianDegrees(ans, acos((pow(Info.a, 2) + pow(Info.c, 2) - pow(Info.b, 2)) / (2 * Info.a * Info.c)));
                }
                /*else if (x == "B" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radianDegrees(ans, acos((pow(Info.a, 2) + pow(Info.c, 2) - pow(Info.b, 2)) / (2 * Info.b * Info.c)));
                }
                else if (x == "B" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radianDegrees(ans, acos((pow(Info.a, 2) + pow(Info.c, 2) - pow(Info.b, 2)) / (2 * Info.a * Info.b)));
                }*/
                else if (x == "C") {
                    radianDegrees(ans, acos((pow(Info.a, 2) + pow(Info.b, 2) - pow(Info.c, 2)) / (2 * Info.a * Info.b)));
                }
                /*else if (x == "C" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radianDegrees(ans, acos((pow(Info.a, 2) + pow(Info.b, 2) - pow(Info.c, 2)) / (2 * Info.b * Info.c)));
                }
                else if (x == "C" && Info.a != 0 && Info.b != 0 && Info.c != 0) {
                    radianDegrees(ans, acos((pow(Info.a, 2) + pow(Info.b, 2) - pow(Info.c, 2)) / (2 * Info.a * Info.c)));
                }*/
            }
        }
        else if (x == "a" || x == "b" || x == "c") {
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
        return 1;
    }

    cout << x << " = " << ans << "\n";
    return 1;
}