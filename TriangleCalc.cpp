#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>
using namespace std;

double pi = 3.14159;

void radianDegrees(double &ansReference, double calcOutput){
    ansReference = (calcOutput * 180) / pi;
}

int main(){
    double A = 0, B = 0, C = 0, Ar = 0, Br = 0, Cr = 0, a = 0, b = 0, c = 0, ans = 0, inf_angle[3], inf_angle_radian[3], inf_side[3];
    int i = 0, inf_angles_present = 0, inf_sides_present = 0, inf_values_present = 0;
    string x;

    cout << "Please input corresponding angle and side value's. Enter 0 if no value present" << "\n";
    cout << "(Capital=Angle, Lowercase=Side.)" << "\n" << "\n";

    cout << "\t" << "A = ";
    cin >> A;
    inf_angle[0] = A;
    Ar = A * pi / 180;
    inf_angle_radian[0] = Ar;

    cout << "\t" << "B = ";
    cin >> B;
    inf_angle[1] = B;
    Br = B * pi / 180;
    inf_angle_radian[1] = Br;

    cout << "\t" << "C = ";
    cin >> C;
    inf_angle[2] = C;
    Cr = C * pi / 180;
    inf_angle_radian[2] = Cr;

    cout << "\t" << "a = ";
    cin >> a;
    inf_side[0] = a;

    cout << "\t" << "b = ";
    cin >> b;
    inf_side[1] = b;

    cout << "\t" << "c = ";
    cin >> c;
    inf_side[2] = c;

    cout << "\n";

    //input check
    if (A + B + C != 180 && A != 0 && B != 0 && C != 0){
        cout << "Please enter valid angle's (must add to 180 degree's)." << "\n" << "\n";
        main();
    }

    cout << "Angle's: " << A << ", " << B << ", " << C << "\n";
    cout << "Radian's: " << Ar << ", " << Br << ", " << Cr << "\n";
    cout << "Side's: " << a << ", " << b << ", " << c << "\n";

    //error - inf_values_present always = 0
    for (i = 0; i < 3; i++){
        if (inf_angle[i] != 0){
            ++inf_angles_present;
        }
        if (inf_side[i] != 0){
            ++inf_sides_present;
        }
    }
    
    inf_values_present = inf_angles_present + inf_sides_present;
    cout << "No. of value's present: "<< inf_values_present << "\n" << "\n";

    cout << "What would you like to calculate (capital=angle, lowercase=side): ";
    cin >> x;
    cout << "\n";

    //Main calculations
    //Calc. angle's when 2 angle's known - 180 degree's in tirangle
    if (x == "A" && B != 0 && C != 0){
        ans = 180 - B - C;
    }
    else if (x == "B" && A != 0 && C != 0){
        ans = 180 - A - C;
    }
    else if (x == "C" && B != 0 && A != 0){
        ans = 180 - B - A;
    }
    else if (A == 90 || B == 90 || C == 90){
        //Calc. side's when 2 side's known - pyth
        if ((x == "a" || x == "b" || x == "c") && inf_sides_present == 2){
            if (A == 90){
                if (x == "a" && b != 0 && c != 0){
                    ans = sqrt(b * b + c * c);
                }
                else if (x == "b" && a != 0 && c != 0){
                    ans = sqrt(a * a - c * c);
                }
                else if (x == "c" && a != 0 && b != 0){
                    ans = sqrt(a * a - b * b);
                }
            }
            else if (B == 90){
                if (x == "a" && b != 0 && c != 0){
                    ans = sqrt(b * b - c * c);
                }
                else if (x == "b" && a != 0 && c != 0){
                    ans = sqrt(a * a + c * c);
                }
                else if (x == "c" && a != 0 && b != 0){
                    ans = sqrt(b * b - a * a);
                }
            }
            else if (C == 90){
                if (x == "a" && b != 0 && c != 0){
                    ans = sqrt(c * c - b * b);
                }
                else if (x == "b" && a != 0 && c != 0){
                    ans = sqrt(c * c - a * a);
                }
                else if (x == "c" && a != 0 && b != 0){
                    ans = sqrt(a * a + b * b);
                }
            }
        }
        //Calc. side's when 1 side and 1 >= angle known (1 must be 90) - trig (functions)
        else if ((x == "a" || x == "b" || x =="c") && inf_angles_present >= 1 && inf_sides_present == 1){
            if (A == 90){
                if (x == "a"){
                    if (B != 0){
                        if (b != 0){
                            ans = b / sin(Br);
                        }
                        else if (c != 0){
                            ans = c / cos(Br);
                        }
                    }
                    else if (C != 0){
                        if (c != 0){
                            ans = c / sin(Cr);
                        }
                        else if (b != 0){
                            ans = b / cos(Cr);
                        }
                    }
                }
                else if (x == "b"){
                    if (B != 0){
                        if (a != 0){
                            ans = sin(Br) * a;
                        }
                        else if (c != 0){
                            ans = tan(Br) * c;
                        }
                    }
                    else if (C != 0){
                        if (a != 0){
                            ans = cos(Cr) * a;
                        }
                        else if (c != 0){
                            ans = c / tan(Cr);
                        }
                    }
                }
                else if (x == "c"){
                    if (B != 0){
                        if (a != 0){
                            ans = cos(Br) * a;
                        }
                        else if (b != 0){
                            ans = b / tan(Br);
                        }
                    }
                    else if (C != 0){
                        if (a != 0){
                            ans = sin(Cr) * a;
                        }
                        else if (b != 0){
                            ans = tan(Cr) * b;
                        }
                    }
                }
            }
            else if (B == 90){
                if (x == "a"){
                    if (A != 0){
                        if (b != 0){
                            ans = sin(Ar) * b;
                        }
                        else if (c != 0){
                            ans = tan(Ar) * c;
                        }
                    }
                    else if (C != 0){
                        if (c != 0){
                            ans = c / tan(Cr);
                        }
                        else if (b != 0){
                            ans = cos(Cr) * b;
                        }
                    }
                }
                else if (x == "b"){
                    if (A != 0){
                        if (a != 0){
                            ans = a / sin(Ar);
                        }
                        else if (c != 0){
                            ans = c / cos(Ar);
                        }
                    }
                    else if (C != 0){
                        if (a != 0){
                            ans = a / cos(Cr);
                        }
                        else if (c != 0){
                            ans = c / sin(Cr);
                        }
                    }
                }
                else if (x == "c"){
                    if (A != 0){
                        if (a != 0){
                            ans = a / tan(Ar);
                        }
                        else if (b != 0){
                            ans = cos(Br) * b;
                        }
                    }
                    else if (C != 0){
                        if (a != 0){
                            ans = tan(Cr) * a;
                        }
                        else if (b != 0){
                            ans = sin(Cr) * b;
                        }
                    }
                }
            }
            else if (C == 90){
                if (x == "a"){
                    if (A != 0){
                        if (b != 0){
                            ans = tan(Br) * b;
                        }
                        else if (c != 0){
                            ans = sin(Br) * c;
                        }
                    }
                    else if (B != 0){
                        if (b != 0) {
                            ans = b / sin(Br);
                        }
                        else if (c != 0) {
                            ans = cos(Br) * c;
                        }
                    }
                }
                else if (x == "b"){
                    if (A != 0){
                        if (a != 0){
                            ans = a / tan(Ar);
                        }
                        else if (c != 0){
                            ans = cos(Ar) * c;
                        }
                    }
                    else if (B != 0) {
                        if (a != 0) {
                            ans = tan(Br) * a;
                        }
                        else if (c != 0) {
                            ans = sin(Br) * c;
                        }
                    }
                }
                else if (x == "c"){
                    if (A != 0){
                        if (a != 0){
                            ans = a / sin(Ar);
                        }
                        else if (b != 0){
                            ans = b / cos(Ar);
                        }
                    }
                    else if (B != 0){
                        if (a != 0){
                            ans = a / cos(Br);
                        }
                        else if (b != 0){
                            ans = b / sin(Br);
                        }
                    }
                }
            }
        }
        //Calc. angle's when 2 sides known and 90 angle known - trig (functions)
        else if ((A == 90 || B == 90 || C == 90) && inf_sides_present == 2){
            //Hyp = opp of 90 degree angle, Opp = opp of angle to be calculated, Adj = other side
            if (A == 90){
                if (x == "B"){
                    if (a != 0 && b != 0){
                        radianDegrees(ans, asin(b / a));
                    }
                    else if (a != 0 && c != 0){
                        radianDegrees(ans, acos(c / a));
                    }
                    else if (b != 0 && c != 0){
                        radianDegrees(ans, atan(b / c));
                    }
                }
                else if (x == "C"){
                    if (a != 0 && c != 0){
                        radianDegrees(ans, asin(c / a));
                    }
                    else if (a != 0 && b != 0){
                        radianDegrees(ans, acos(b / a));
                    }
                    else if (b != 0 && c != 0){
                        radianDegrees(ans, atan(c / b));
                    }
                }
            }
            else if (B == 90){
                if (x == "A"){
                    if (a != 0 && b != 0){
                        radianDegrees(ans, asin(a / b));
                    }
                    else if (a != 0 && c != 0){
                        radianDegrees(ans, acos(c / a));
                    }
                    else if (b != 0 && c != 0){
                        radianDegrees(ans, atan(b / c));
                    }
                }
                else if (x == "C"){
                    if (c != 0 && b != 0){
                        radianDegrees(ans, asin(c / b));
                    }
                    else if (a != 0 && b != 0){
                        radianDegrees(ans, acos(b / a));
                    }
                    else if (b != 0 && c != 0){
                        radianDegrees(ans, atan(c / b));
                    }
                }
            }
            else if (C == 90){
                if (x == "A")
                {
                    if (a != 0 && c != 0){
                        radianDegrees(ans, asin(a / c));
                    }
                    else if (b != 0 && c != 0){
                        radianDegrees(ans, acos(b / c));
                    }
                    else if (a != 0 && b != 0){
                        radianDegrees(ans, atan(a / b));
                    }
                }
                else if (x == "B"){
                    if (b != 0 && c != 0){
                        radianDegrees(ans, asin(b / c));
                    }
                    else if (a != 0 && c != 0){
                        radianDegrees(ans, acos(a / c));
                    }
                    else if (a != 0 && b != 0){
                        radianDegrees(ans, atan(b / a));
                    }
                }
            }
        }
    }
    //Sine and cosine rule's can also be used for right angled triangle's but I see no reason to do that and so haven't programmed that functionality in, I will if I discover a use later down the line
    else if (A != 90 && B != 90 && C != 90){
        //Calc. angle's when 2 side's & 1 angle known - trig (sine rule)
        if (x == "A" && a != 0 && B != 0 && b != 0){
            radianDegrees(ans, asin(a* sin(Br) / b));
        }
        else if (x == "A" && a != 0 && C != 0 && c != 0){
            radianDegrees(ans, asin(a* sin(Cr) / c));
        }
        else if (x == "B" && b != 0 && A != 0 && a != 0){
            radianDegrees(ans, asin(b* sin(Ar) / a));
        }
        else if (x == "B" && a != 0 && B != 0 && b != 0){
            radianDegrees(ans, asin(b* sin(Cr) / c));
        }
        else if (x == "C" && a != 0 && B != 0 && b != 0){
            radianDegrees(ans, asin(c* sin(Ar) / a));
        }
        else if (x == "C" && a != 0 && B != 0 && b != 0){
            radianDegrees(ans, asin(c* sin(Br) / b));
        }
        //Calc. side's when 1 angle & 2 side's known - trig (sine rule)
        else if (x == "a" && A != 0 && B != 0 && b != 0){
            ans = sin(Ar) * b / sin(B);
        }
        else if (x == "a" && A != 0 && C != 0 && c != 0){
            ans = sin(Ar) * b / sin(B);
        }
        else if (x == "b" && B != 0 && A != 0 && a != 0){
            ans = sin(Ar) * b / sin(B);
        }
        else if (x == "b" && B != 0 && C != 0 && c != 0){
            ans = sin(Ar) * b / sin(B);
        }
        else if (x == "c" && C != 0 && A != 0 && a != 0){
            ans = sin(Ar) * b / sin(B);
        }
        else if (x == "c" && C != 0 && B != 0 && b != 0){
            ans = sin(Ar) * b / sin(B);
        }
        //Calc. angle's when 1 angle and 2 side's known - trig (cosine rule)
        else if (x == "A" && a != 0 && b != 0 && c != 0){
            radianDegrees(ans, acos(((b* b) + (c * c) - (a * a)) / 2 * b * c));
        }
        else if (x == "B" && a != 0 && b != 0 && c != 0){
            radianDegrees(ans, acos(((a* a) + (c * c) - (b * b)) / 2 * a * c));
        }
        else if (x == "C" && a != 0 && b != 0 && c != 0){
            radianDegrees(ans, acos(((a* a) + (b * b) - (c * c)) / 2 * a * b));
        }
        //Calc. side's when 1 angle and 2 side's known - trig (cosine rule)
        else if (x == "a" && A != 0 && b != 0 && c != 0){
            ans = sqrt((b * b) + (c * c) - (2 * b * c * cos(Ar)));
        }
        else if (x == "b" && B != 0 && a != 0 && c != 0){
            ans = sqrt((a * a) + (c * c) - (2 * a * c * cos(Br)));
        }
        else if (x == "c" && C != 0 && a != 0 && b != 0){
            ans = sqrt((a * a) + (b * b) - (2 * a * b * cos(Cr)));
        }
    }
    else{
        cout << x << " is uncalculabe with information provided." << "\n";
    }

    cout << x << " = " << ans << "\n";
    return 1;
}