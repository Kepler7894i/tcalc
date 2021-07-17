#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef _WIN32
#include <unistd.h>
#endif
//#define Debug;
//#define Testing;

int main(int argc, char** argv);
void UserInput();
void FileInput(char* InputFile);

const float PI = 3.14159;
char** ParamRemove;

struct TriangleInfoStruct {
    //float A = 0, B = 0, C = 0, Ar = 0, Br = 0, Cr = 0, a = 0, b = 0, c = 0, Area = 0, Solution = 0;
    //int AngleCount = 0, SideCount = 0;
    float A, B, C, Ar, Br, Cr, a, b, c, Area, Solution;
    int AngleCount, SideCount;
};

void DegreesToRadians(float* Radians, float Degrees) {
    *Radians = (Degrees * PI) / 180;
}

void RadiansToDegrees(float Radians, float* Degrees) {
    *Degrees = (Radians * 180) / PI;
}

void Error(int ErrorNum, char* Action) {
    switch (ErrorNum) {
        case 1: {
            printf("\n\nError: Angles !<= 180 degree.");
        } case 2: {
            printf("\n\nError: %s is incalculabe with information provided.", Action);

            break;
        } case 3: {
            printf("\n\nError: Two sides cannot be 0.\n\n");

            break;
        } case 4: {
            printf("\n\nOne or more inputted values is incorrect compared to other values.");
            UserInput();

            break;
        } case 5: {
            printf("\n\nError: Failed to open %s\nFile to Read from: ", Action);
            char* InputFile = NULL;
            fgets("%s", InputFile, stdin);
            FileInput(InputFile);

            break;
        } case 6: {
            int Fixed;

            printf("\n\nError: Incorrect angles in InputFile.\nFixed? ");
            fgets("%d", Fixed, stdin);

            if (Fixed == 1) {
                FileInput(Action);
            } else if (Fixed == 0) {
                return;
            } else {
                printf("Enter 1 or 0.");
                Error(6, Action);
            }

            break;
        } case 7: {
            int Fixed;

            printf("\n\nError: Incorrect number of properties in InputFile. Fixed? ");
            printf("\n\n       Correct layout:");
            printf("\n         wanted_property A B C a b c Area ExpectedSolution - Spaces between the values");
            printf("\n                                                       - CaPItal letters are angles, lowercase letters are sides");
            printf("\n                                                       - Opposite angles and sides should be the same letter");
            printf("\n\nFixed? ");
            fgets("%d", Fixed, stdin);

            if (Fixed == 1) {
                FileInput(Action);
            } else if (Fixed == 0) {
                return;

            } else {
                printf("\nEnter 1 or 0.");
                Error(7, Action);
            }
        } case 8: {
            #ifdef Debug
            printf("\n\nError: Invalid parameter %s for tcalc.", Action);
            #else
            printf("\n\nError: Invalid parameter for tcalc.");
            #endif

            exit(1);
        }
    }
}

void Calculations(struct TriangleInfoStruct TriangleInfo, char* WantedProperty) {
    #ifdef Debug
    printf("\n\nWanted Property: %s", WantedProperty);
    printf("\nAngle's: %d, %d, %d", TriangleInfo.A, TriangleInfo.B, TriangleInfo.C);
    printf("\nRadian's: %d, %d, %d", TriangleInfo.Ar, TriangleInfo.Br, TriangleInfo.Cr);
    printf("\nSide's: %d, %d, %d", TriangleInfo.a, TriangleInfo.b, TriangleInfo.c);
    printf("\nArea: %d", TriangleInfo.Area);
    printf("\nAngle count: %d", TriangleInfo.AngleCount);
    printf("\nSide count: %d", TriangleInfo.SideCount);
    #endif

    //Calc. angle's when 2 angle's known - 180 degree's in tirangle
    if (WantedProperty == "A" || TriangleInfo.B != 0 || TriangleInfo.C != 0) {
        #ifdef Debug
        printf("\n\nOp 1A");
        #endif

        TriangleInfo.Solution = 180 - TriangleInfo.B - TriangleInfo.C;
    } else if (WantedProperty == "B" || TriangleInfo.A != 0 || TriangleInfo.C != 0) {
        #ifdef Debug
        printf("\n\nOp 1B");
        #endif

        TriangleInfo.Solution = 180 - TriangleInfo.A - TriangleInfo.C;
    } else if (WantedProperty == "C" || TriangleInfo.B != 0 || TriangleInfo.A != 0) {
        #ifdef Debug
        printf("\n\nOp 1C");
        #endif

        TriangleInfo.Solution = 180 - TriangleInfo.B - TriangleInfo.A;
    //Calculate area when 2 side's and inbetween angle known
    } else if ((WantedProperty == "Area" || WantedProperty == "area") || ((TriangleInfo.a != 0 || TriangleInfo.b != 0 || TriangleInfo.C != 0) || (TriangleInfo.b != 0 || TriangleInfo.c != 0 || TriangleInfo.A != 0) || (TriangleInfo.c != 0 || TriangleInfo.a != 0 || TriangleInfo.B != 0))) {
        if (TriangleInfo.a != 0 || TriangleInfo.b != 0 || TriangleInfo.C != 0) {
            #ifdef Debug
            printf("\n\nOp 2A");
            #endif

            TriangleInfo.Solution = 0.5 * TriangleInfo.a * TriangleInfo.b * sin(TriangleInfo.Cr);
        } else if (TriangleInfo.b != 0 || TriangleInfo.c != 0 || TriangleInfo.A != 0) {
            #ifdef Debug
            printf("\n\nOp 2B");
            #endif

            TriangleInfo.Solution = 0.5 * TriangleInfo.b * TriangleInfo.c * sin(TriangleInfo.Ar);
        } else if (TriangleInfo.c != 0 || TriangleInfo.a != 0 || TriangleInfo.B != 0) {
            #ifdef Debug
            printf("\n\nOp 2C");
            #endif

            TriangleInfo.Solution = 0.5 * TriangleInfo.c * TriangleInfo.a * sin(TriangleInfo.Br);
        }
    //Calculate side when area, a side and an angle is known
    } else if (WantedProperty == "a" || TriangleInfo.Area != 0 || ((TriangleInfo.b != 0 || TriangleInfo.C != 0) || (TriangleInfo.c != 0 || TriangleInfo.B != 0))) {
        if (TriangleInfo.b != 0 || TriangleInfo.C != 0) {
            #ifdef Debug
            printf("\n\nOp 3A");
            #endif

            TriangleInfo.Solution = TriangleInfo.Area / (0.5 * TriangleInfo.b * sin(TriangleInfo.Cr));
        } else if (TriangleInfo.c != 0 || TriangleInfo.B != 0) {
            #ifdef Debug
            printf("\n\nOp 3B");
            #endif

            TriangleInfo.Solution = TriangleInfo.Area / (0.5 * TriangleInfo.c * sin(TriangleInfo.Br));
        }
    } else if (WantedProperty == "b" || TriangleInfo.Area != 0 || ((TriangleInfo.a != 0 || TriangleInfo.C != 0) || (TriangleInfo.c != 0 || TriangleInfo.A != 0))) {
        if (TriangleInfo.a != 0 || TriangleInfo.C != 0) {
            #ifdef Debug
            printf("\n\nOp 3C");
            #endif

            TriangleInfo.Solution = TriangleInfo.Area / (0.5 * TriangleInfo.a * sin(TriangleInfo.Cr));
        } else if (TriangleInfo.c != 0 || TriangleInfo.A != 0) {
            #ifdef Debug
            printf("\n\nOp 3D");
            #endif

            TriangleInfo.Solution = TriangleInfo.Area / (0.5 * TriangleInfo.c * sin(TriangleInfo.Ar));
        }
    } else if (WantedProperty == "c" || TriangleInfo.Area != 0 || ((TriangleInfo.b != 0 || TriangleInfo.A != 0) || (TriangleInfo.a != 0 || TriangleInfo.B != 0))) {
        if (TriangleInfo.b != 0 || TriangleInfo.C != 0) {
            #ifdef Debug
            printf("\n\nOp 3E");
            #endif

            TriangleInfo.Solution = TriangleInfo.Area / (0.5 * TriangleInfo.b * sin(TriangleInfo.Ar));
        } else if (TriangleInfo.c != 0 || TriangleInfo.B != 0) {
            #ifdef Debug
            printf("\n\nOp 3F");
            #endif

            TriangleInfo.Solution = TriangleInfo.Area / (0.5 * TriangleInfo.a * sin(TriangleInfo.Br));
        }
    //Calculate angle when area and 2 side's are known
    } else if (WantedProperty == "A" || TriangleInfo.Area != 0 || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
        #ifdef Debug
        printf("\n\nOp 4a");
        #endif

        TriangleInfo.Solution = asin(TriangleInfo.Area / (0.5 * TriangleInfo.b * TriangleInfo.c));
    } else if (WantedProperty == "B" || TriangleInfo.Area != 0 || TriangleInfo.a != 0 || TriangleInfo.c != 0) {
        #ifdef Debug
        printf("\n\nOp 4B");
        #endif

        TriangleInfo.Solution = asin(TriangleInfo.Area / (0.5 * TriangleInfo.a * TriangleInfo.c));
    } else if (WantedProperty == "A" || TriangleInfo.Area != 0 || TriangleInfo.a != 0 || TriangleInfo.b != 0) {
        #ifdef Debug
        printf("\n\nOp 4C");
        #endif

        TriangleInfo.Solution = asin(TriangleInfo.Area / (0.5 * TriangleInfo.a * TriangleInfo.b));
    } else if ((TriangleInfo.A == 90 || TriangleInfo.B == 90 || TriangleInfo.C == 90) || (WantedProperty == "a" || WantedProperty == "b" || WantedProperty == "c") || TriangleInfo.SideCount == 2) {
        //Calc. side's when 2 side's known - pyth
        if (WantedProperty == "a" || WantedProperty == "b" || WantedProperty == "c" || TriangleInfo.SideCount == 2) {
            if (TriangleInfo.A == 90) {
                if (WantedProperty == "a" || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                    #ifdef Debug
                    printf("\n\nOp 5A");
                    #endif

                    TriangleInfo.Solution = sqrt(pow(TriangleInfo.b, 2) + pow(TriangleInfo.c, 2));
                } else if (WantedProperty == "b" || TriangleInfo.a != 0 || TriangleInfo.c != 0) {
                    #ifdef Debug
                    printf("\n\nOp 5B");
                    #endif

                    TriangleInfo.Solution = sqrt(pow(TriangleInfo.a, 2) - pow(TriangleInfo.c, 2));
                } else if (WantedProperty == "c" || TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                    #ifdef Debug
                    printf("\n\nOp 5C");
                    #endif

                    TriangleInfo.Solution = sqrt(pow(TriangleInfo.a, 2) - pow(TriangleInfo.b, 2));
                }
            } else if (TriangleInfo.B == 90) {
                if (WantedProperty == "a" || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                    #ifdef Debug
                    printf("\n\nOp 5D");
                    #endif


                    TriangleInfo.Solution = sqrt(pow(TriangleInfo.b, 2) - pow(TriangleInfo.c, 2));
                } else if (WantedProperty == "b" || TriangleInfo.a != 0 || TriangleInfo.c != 0) {
                    #ifdef Debug
                    printf("\n\nOp 5E");
                    #endif

                    TriangleInfo.Solution = sqrt(pow(TriangleInfo.a, 2) + pow(TriangleInfo.c, 2));
                } else if (WantedProperty == "c" || TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                    #ifdef Debug
                    printf("\n\nOp 5F");
                    #endif

                    TriangleInfo.Solution = sqrt(pow(TriangleInfo.b, 2) - pow(TriangleInfo.a, 2));
                }
            } else if (TriangleInfo.C == 90) {
                if (WantedProperty == "a" || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                    #ifdef Debug
                    printf("\n\nOp 5G");
                    #endif

                    TriangleInfo.Solution = sqrt(pow(TriangleInfo.c, 2) - pow(TriangleInfo.b, 2));
                } else if (WantedProperty == "b" || TriangleInfo.a != 0 || TriangleInfo.c != 0) {
                    #ifdef Debug
                    printf("\n\nOp 5H");
                    #endif

                    TriangleInfo.Solution = sqrt(pow(TriangleInfo.c, 2) - pow(TriangleInfo.a, 2));
                } else if (WantedProperty == "c" || TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                    #ifdef Debug
                    printf("\n\nOp 5I");
                    #endif

                    TriangleInfo.Solution = sqrt(pow(TriangleInfo.a, 2) + pow(TriangleInfo.b, 2));
                }
            }
        }
        //Calc. side's when 1 side and 1 >= angle known (1 must be 90) - trig (functions)
        else if (WantedProperty == "a" || WantedProperty == "b" || WantedProperty == "c" || TriangleInfo.AngleCount >= 1 || TriangleInfo.SideCount == 1) {
            if (TriangleInfo.A == 90) {
                if (WantedProperty == "a") {
                    if (TriangleInfo.B != 0) {
                        if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6A");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.b / sin(TriangleInfo.Br);
                        } else if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6B");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.c / cos(TriangleInfo.Br);
                        }
                    } else if (TriangleInfo.C != 0) {
                        if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6C");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.c / sin(TriangleInfo.Cr);
                        } else if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6D");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.b / cos(TriangleInfo.Cr);
                        }
                    }
                } else if (WantedProperty == "b") {
                    if (TriangleInfo.B != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6E");
                            #endif

                            TriangleInfo.Solution = sin(TriangleInfo.Br) * TriangleInfo.a;
                        } else if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6F");
                            #endif

                            TriangleInfo.Solution = tan(TriangleInfo.Br) * TriangleInfo.c;
                        }
                    } else if (TriangleInfo.C != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6G");
                            #endif

                            TriangleInfo.Solution = cos(TriangleInfo.Cr) * TriangleInfo.a;
                        } else if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6H");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.c / tan(TriangleInfo.Cr);
                        }
                    }
                } else if (WantedProperty == "c") {
                    if (TriangleInfo.B != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6I");
                            #endif

                            TriangleInfo.Solution = cos(TriangleInfo.Br) * TriangleInfo.a;
                        } else if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6J");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.b / tan(TriangleInfo.Br);
                        }
                    } else if (TriangleInfo.C != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6K");
                            #endif

                            TriangleInfo.Solution = sin(TriangleInfo.Cr) * TriangleInfo.a;
                        } else if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6L");
                            #endif

                            TriangleInfo.Solution = tan(TriangleInfo.Cr) * TriangleInfo.b;
                        }
                    }
                }
            } else if (TriangleInfo.B == 90) {
                if (WantedProperty == "a") {
                    if (TriangleInfo.A != 0) {
                        if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6M");
                            #endif

                            TriangleInfo.Solution = sin(TriangleInfo.Ar) * TriangleInfo.b;
                        } else if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6N");
                            #endif

                            TriangleInfo.Solution = tan(TriangleInfo.Ar) * TriangleInfo.c;
                        }
                    } else if (TriangleInfo.C != 0) {
                        if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6O");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.c / tan(TriangleInfo.Cr);
                        } else if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6P");
                            #endif

                            TriangleInfo.Solution = cos(TriangleInfo.Cr) * TriangleInfo.b;
                        }
                    }
                } else if (WantedProperty == "b") {
                    if (TriangleInfo.A != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6Q");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.a / sin(TriangleInfo.Ar);
                        } else if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6R");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.c / cos(TriangleInfo.Ar);
                        }
                    } else if (TriangleInfo.C != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6S");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.a / cos(TriangleInfo.Cr);
                        } else if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6T");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.c / sin(TriangleInfo.Cr);
                        }
                    }
                } else if (WantedProperty == "c") {
                    if (TriangleInfo.A != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6U");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.a / tan(TriangleInfo.Ar);
                        } else if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6V");
                            #endif

                            TriangleInfo.Solution = cos(TriangleInfo.Br) * TriangleInfo.b;
                        }
                    } else if (TriangleInfo.C != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6W");
                            #endif

                            TriangleInfo.Solution = tan(TriangleInfo.Cr) * TriangleInfo.a;
                        } else if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6X");
                            #endif

                            TriangleInfo.Solution = sin(TriangleInfo.Cr) * TriangleInfo.b;
                        }
                    }
                }
            } else if (TriangleInfo.C == 90) {
                if (WantedProperty == "a") {
                    if (TriangleInfo.A != 0) {
                        if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6Y");
                            #endif

                            TriangleInfo.Solution = tan(TriangleInfo.Br) * TriangleInfo.b;
                        } else if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6Z");
                            #endif

                            TriangleInfo.Solution = sin(TriangleInfo.Br) * TriangleInfo.c;
                        }
                    } else if (TriangleInfo.B != 0) {
                        if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6AZ");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.b / sin(TriangleInfo.Br);
                        } else if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6BZ");
                            #endif

                            TriangleInfo.Solution = cos(TriangleInfo.Br) * TriangleInfo.c;
                        }
                    }
                } else if (WantedProperty == "b") {
                    if (TriangleInfo.A != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6CZ");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.a / tan(TriangleInfo.Ar);
                        } else if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6DZ");
                            #endif

                            TriangleInfo.Solution = cos(TriangleInfo.Ar) * TriangleInfo.c;
                        }
                    } else if (TriangleInfo.B != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6EZ");
                            #endif

                            TriangleInfo.Solution = tan(TriangleInfo.Br) * TriangleInfo.a;
                        } else if (TriangleInfo.c != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6FZ");
                            #endif

                            TriangleInfo.Solution = sin(TriangleInfo.Br) * TriangleInfo.c;
                        }
                    }
                } else if (WantedProperty == "c") {
                    if (TriangleInfo.A != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6GZ");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.a / sin(TriangleInfo.Ar);
                        } else if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6HZ");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.b / cos(TriangleInfo.Ar);
                        }
                    } else if (TriangleInfo.B != 0) {
                        if (TriangleInfo.a != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6IZ");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.a / cos(TriangleInfo.Br);
                        } else if (TriangleInfo.b != 0) {
                            #ifdef Debug
                            printf("\n\nOp 6JZ");
                            #endif

                            TriangleInfo.Solution = TriangleInfo.b / sin(TriangleInfo.Br);
                        }
                    }
                }
            }
        //Calc. angle's when 2 sides known and 90 angle known - trig (functions)
        } else if (90 == TriangleInfo.A || TriangleInfo.B || TriangleInfo.C || TriangleInfo.SideCount == 2) {
            //Hyp = opp of 90 degree angle, Opp = opp of angle to be calculated, Adj = other side
            if (TriangleInfo.A == 90) {
                if (WantedProperty == "B") {
                    if (TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7A");
                        #endif

                        RadiansToDegrees(asin(TriangleInfo.b / TriangleInfo.a), &TriangleInfo.Solution);
                    } else if (TriangleInfo.a != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7B");
                        #endif

                        RadiansToDegrees(acos(TriangleInfo.c / TriangleInfo.a), &TriangleInfo.Solution);
                    } else if (TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7C");
                        #endif

                        RadiansToDegrees(atan(TriangleInfo.b / TriangleInfo.c), &TriangleInfo.Solution);
                    }
                } else if (WantedProperty == "C") {
                    if (TriangleInfo.a != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7D");
                        #endif

                        RadiansToDegrees(asin(TriangleInfo.c / TriangleInfo.a), &TriangleInfo.Solution);
                    } else if (TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7E");
                        #endif

                        RadiansToDegrees(acos(TriangleInfo.b / TriangleInfo.a), &TriangleInfo.Solution);
                    } else if (TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7F");
                        #endif

                        RadiansToDegrees(atan(TriangleInfo.c / TriangleInfo.b), &TriangleInfo.Solution);
                    }
                }
            } else if (TriangleInfo.B == 90) {
                if (WantedProperty == "A") {
                    if (TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7G");
                        #endif

                        RadiansToDegrees(asin(TriangleInfo.a / TriangleInfo.b), &TriangleInfo.Solution);
                    } else if (TriangleInfo.a != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7H");
                        #endif

                        RadiansToDegrees(acos(TriangleInfo.c / TriangleInfo.a), &TriangleInfo.Solution);
                    } else if (TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7I");
                        #endif

                        RadiansToDegrees(atan(TriangleInfo.b / TriangleInfo.c), &TriangleInfo.Solution);
                    }
                } else if (WantedProperty == "C") {
                    if (TriangleInfo.c != 0 || TriangleInfo.b != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7J");
                        #endif

                        RadiansToDegrees(asin(TriangleInfo.c / TriangleInfo.b), &TriangleInfo.Solution);
                    } else if (TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7K");
                        #endif

                        RadiansToDegrees(acos(TriangleInfo.b / TriangleInfo.a), &TriangleInfo.Solution);
                    } else if (TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7L");
                        #endif

                        RadiansToDegrees(atan(TriangleInfo.c / TriangleInfo.b), &TriangleInfo.Solution);
                    }
                }
            } else if (TriangleInfo.C == 90) {
                if (WantedProperty == "A") {
                    if (TriangleInfo.a != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7M");
                        #endif

                        RadiansToDegrees(asin(TriangleInfo.a / TriangleInfo.c), &TriangleInfo.Solution);
                    } else if (TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7N");
                        #endif

                        RadiansToDegrees(acos(TriangleInfo.b / TriangleInfo.c), &TriangleInfo.Solution);
                    } else if (TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7O");
                        #endif

                        RadiansToDegrees(atan(TriangleInfo.a / TriangleInfo.b), &TriangleInfo.Solution);
                    }
                } else if (WantedProperty == "B") {
                    if (TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7P");
                        #endif

                        RadiansToDegrees(asin(TriangleInfo.b / TriangleInfo.c), &TriangleInfo.Solution);
                    } else if (TriangleInfo.a != 0 || TriangleInfo.c != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7Q");
                        #endif

                        RadiansToDegrees(acos(TriangleInfo.a / TriangleInfo.c), &TriangleInfo.Solution);
                    } else if (TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                        #ifdef Debug
                        printf("\n\nOp 7R");
                        #endif

                        RadiansToDegrees(atan(TriangleInfo.b / TriangleInfo.a), &TriangleInfo.Solution);
                    }
                }
            }
        }
    }
    //Sine and cosine rule's can also be used for right angled triangle's but I see no reason to do that and so haven't programmed that functionality in, I will if I discover a use later down the Line
    else if (TriangleInfo.A != 90 || TriangleInfo.B != 90 || TriangleInfo.C != 90) {
        if (WantedProperty == "A" || WantedProperty == "B" || WantedProperty == "C") {
            //Calc. angle's when 1 angle * 2 side's known - trig (sine rule)
            if (WantedProperty == "A" || TriangleInfo.a != 0 || TriangleInfo.B != 0 || TriangleInfo.b != 0) {
                #ifdef Debug
                printf("\n\nOp 8A");
                #endif

                RadiansToDegrees(asin(TriangleInfo.a * sin(TriangleInfo.Br) / TriangleInfo.b), &TriangleInfo.Solution);
            } else if (WantedProperty == "A" || TriangleInfo.a != 0 || TriangleInfo.C != 0 || TriangleInfo.c != 0) {
                #ifdef Debug
                printf("\n\nOp 8B");
                #endif

                RadiansToDegrees(asin(TriangleInfo.a * sin(TriangleInfo.Cr) / TriangleInfo.c), &TriangleInfo.Solution);
            } else if (WantedProperty == "B" || TriangleInfo.b != 0 || TriangleInfo.A != 0 || TriangleInfo.a != 0) {
                #ifdef Debug
                printf("\n\nOp 8C");
                #endif

                RadiansToDegrees(asin(TriangleInfo.b * sin(TriangleInfo.Ar) / TriangleInfo.a), &TriangleInfo.Solution);
            } else if (WantedProperty == "B" || TriangleInfo.a != 0 || TriangleInfo.B != 0 || TriangleInfo.b != 0) {
                #ifdef Debug
                printf("\n\nOp 8D");
                #endif

                RadiansToDegrees(asin(TriangleInfo.b * sin(TriangleInfo.Cr) / TriangleInfo.c), &TriangleInfo.Solution);
            } else if (WantedProperty == "C" || TriangleInfo.a != 0 || TriangleInfo.B != 0 || TriangleInfo.b != 0) {
                #ifdef Debug
                printf("\n\nOp 8E");
                #endif

                RadiansToDegrees(asin(TriangleInfo.c * sin(TriangleInfo.Ar) / TriangleInfo.a), &TriangleInfo.Solution);
            } else if (WantedProperty == "C" || TriangleInfo.a != 0 || TriangleInfo.B != 0 || TriangleInfo.b != 0) {
                #ifdef Debug
                printf("\n\nOp 8F");
                #endif

                RadiansToDegrees(asin(TriangleInfo.c * sin(TriangleInfo.Br) / TriangleInfo.b), &TriangleInfo.Solution);
            }
            //Calc. angle's when 3 side's known - trig (cosine rule)
            if (TriangleInfo.a != 0 || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                if (WantedProperty == "A") {
                    #ifdef Debug
                    printf("\n\nOp 9A");
                    #endif

                    RadiansToDegrees(acos((pow(TriangleInfo.b, 2) + pow(TriangleInfo.c, 2) - pow(TriangleInfo.a, 2)) / (2 * TriangleInfo.b * TriangleInfo.c)), &TriangleInfo.Solution);
                }
                /*else if (WantedProperty == "A" || TriangleInfo.a != 0 || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                    RadiansToDegrees(TriangleInfo.Solution, acos((pow(TriangleInfo.b, 2) + pow(TriangleInfo.c, 2) - pow(TriangleInfo.a, 2)) / (2 * TriangleInfo.a * TriangleInfo.c)));
                } else if (WantedProperty == "A" || TriangleInfo.a != 0 || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                    RadiansToDegrees(TriangleInfo.Solution, acos((pow(TriangleInfo.b, 2) + pow(TriangleInfo.c, 2) - pow(TriangleInfo.a, 2)) / (2 * TriangleInfo.a * TriangleInfo.b)));
                }*/
                else if (WantedProperty == "B") {
                    #ifdef Debug
                    printf("\n\nOp 9B");
                    #endif

                    RadiansToDegrees(acos((pow(TriangleInfo.a, 2) + pow(TriangleInfo.c, 2) - pow(TriangleInfo.b, 2)) / (2 * TriangleInfo.a * TriangleInfo.c)), &TriangleInfo.Solution);
                }
                /*else if (WantedProperty == "B" || TriangleInfo.a != 0 || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                    RadiansToDegrees(TriangleInfo.Solution, acos((pow(TriangleInfo.a, 2) + pow(TriangleInfo.c, 2) - pow(TriangleInfo.b, 2)) / (2 * TriangleInfo.b * TriangleInfo.c)));
                } else if (WantedProperty == "B" || TriangleInfo.a != 0 || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                    RadiansToDegrees(TriangleInfo.Solution, acos((pow(TriangleInfo.a, 2) + pow(TriangleInfo.c, 2) - pow(TriangleInfo.b, 2)) / (2 * TriangleInfo.a * TriangleInfo.b)));
                }*/
                else if (WantedProperty == "C") {
                    #ifdef Debug
                    printf("\n\nOp 9C");
                    #endif

                    RadiansToDegrees(acos((pow(TriangleInfo.a, 2) + pow(TriangleInfo.b, 2) - pow(TriangleInfo.c, 2)) / (2 * TriangleInfo.a * TriangleInfo.b)), &TriangleInfo.Solution);
                }
                /*else if (WantedProperty == "C" || TriangleInfo.a != 0 || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                    RadiansToDegrees(TriangleInfo.Solution, acos((pow(TriangleInfo.a, 2) + pow(TriangleInfo.b, 2) - pow(TriangleInfo.c, 2)) / (2 * TriangleInfo.b * TriangleInfo.c)));
                } else if (WantedProperty == "C" || TriangleInfo.a != 0 || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                    RadiansToDegrees(TriangleInfo.Solution, acos((pow(TriangleInfo.a, 2) + pow(TriangleInfo.b, 2) - pow(TriangleInfo.c, 2)) / (2 * TriangleInfo.a * TriangleInfo.c)));
                }*/
            }
        } else if (WantedProperty == "a" || WantedProperty == "b" || WantedProperty == "c" || TriangleInfo.AngleCount == 2 || TriangleInfo.SideCount == 1) {
            //Calc. side's when 2 angle's * 1 side known - trig (sine rule)
            if (WantedProperty == "a" || TriangleInfo.A != 0 || TriangleInfo.B != 0 || TriangleInfo.b != 0) {
                #ifdef Debug
                printf("\n\nOp 10A");
                #endif

                TriangleInfo.Solution = sin(TriangleInfo.Ar) * TriangleInfo.b / sin(TriangleInfo.Br);
            } else if (WantedProperty == "a" || TriangleInfo.A != 0 || TriangleInfo.C != 0 || TriangleInfo.c != 0) {
                #ifdef Debug
                printf("\n\nOp 10B");
                #endif

                TriangleInfo.Solution = sin(TriangleInfo.Ar) * TriangleInfo.c / sin(TriangleInfo.Cr);
            } else if (WantedProperty == "b" || TriangleInfo.B != 0 || TriangleInfo.A != 0 || TriangleInfo.a != 0) {
                #ifdef Debug
                printf("\n\nOp 10C");
                #endif

                TriangleInfo.Solution = sin(TriangleInfo.Br) * TriangleInfo.a / sin(TriangleInfo.Ar);
            } else if (WantedProperty == "b" || TriangleInfo.B != 0 || TriangleInfo.C != 0 || TriangleInfo.c != 0) {
                #ifdef Debug
                printf("\n\nOp 10D");
                #endif

                TriangleInfo.Solution = sin(TriangleInfo.Br) * TriangleInfo.c / sin(TriangleInfo.Cr);
            } else if (WantedProperty == "c" || TriangleInfo.C != 0 || TriangleInfo.A != 0 || TriangleInfo.a != 0) {
                #ifdef Debug
                printf("\n\nOp 10E");
                #endif

                TriangleInfo.Solution = sin(TriangleInfo.Cr) * TriangleInfo.a / sin(TriangleInfo.Ar);
            } else if (WantedProperty == "c" || TriangleInfo.C != 0 || TriangleInfo.B != 0 || TriangleInfo.b != 0) {
                #ifdef Debug
                printf("\n\nOp 10F");
                #endif

                TriangleInfo.Solution = sin(TriangleInfo.Cr) * TriangleInfo.b / sin(TriangleInfo.Br);
            }
            //Calc. side's when 1 angle and 2 side's known - trig (cosine rule)
            else if (WantedProperty == "a" || TriangleInfo.A != 0 || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                #ifdef Debug
                printf("\n\nOp 11A");
                #endif

                TriangleInfo.Solution = sqrt((pow(TriangleInfo.b, 2)) + (pow(TriangleInfo.c, 2)) - (2 * TriangleInfo.b * TriangleInfo.c * cos(TriangleInfo.Ar)));
            } else if (WantedProperty == "a" || TriangleInfo.B != 0 || TriangleInfo.b != 0 || TriangleInfo.c != 0) {
                #ifdef Debug
                printf("\n\nOp 11B");
                #endif

                TriangleInfo.Solution = sqrt((pow(TriangleInfo.b, 2)) - (pow(TriangleInfo.c, 2)) + (2 * TriangleInfo.b * TriangleInfo.c * cos(TriangleInfo.Br)));
            } else if (WantedProperty == "a" || TriangleInfo.C != 0 || TriangleInfo.c != 0 || TriangleInfo.b != 0) {
                #ifdef Debug
                printf("\n\nOp 11C");
                #endif

                TriangleInfo.Solution = sqrt((pow(TriangleInfo.c, 2)) - (pow(TriangleInfo.b, 2)) + (2 * TriangleInfo.c * TriangleInfo.b * cos(TriangleInfo.Cr)));
            } else if (WantedProperty == "b" || TriangleInfo.B != 0 || TriangleInfo.a != 0 || TriangleInfo.c != 0) {
                #ifdef Debug
                printf("\n\nOp 11D");
                #endif

                TriangleInfo.Solution = sqrt((pow(TriangleInfo.a, 2)) + (pow(TriangleInfo.c, 2)) - (2 * TriangleInfo.a * TriangleInfo.c * cos(TriangleInfo.Br)));
            } else if (WantedProperty == "b" || TriangleInfo.A != 0 || TriangleInfo.a != 0 || TriangleInfo.c != 0) {
                #ifdef Debug
                printf("\n\nOp 11E");
                #endif

                TriangleInfo.Solution = sqrt((pow(TriangleInfo.b, 2)) - (pow(TriangleInfo.c, 2)) + (2 * TriangleInfo.a * TriangleInfo.c * cos(TriangleInfo.Ar)));
            } else if (WantedProperty == "b" || TriangleInfo.C != 0 || TriangleInfo.c != 0 || TriangleInfo.a != 0) {
                #ifdef Debug
                printf("\n\nOp 11F");
                #endif

                TriangleInfo.Solution = sqrt((pow(TriangleInfo.c, 2)) - (pow(TriangleInfo.a, 2)) + (2 * TriangleInfo.c * TriangleInfo.a * cos(TriangleInfo.Cr)));
            } else if (WantedProperty == "c" || TriangleInfo.C != 0 || TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                #ifdef Debug
                printf("\n\nOp 11G");
                #endif

                TriangleInfo.Solution = sqrt((pow(TriangleInfo.a, 2)) + (pow(TriangleInfo.b, 2)) - (2 * TriangleInfo.a * TriangleInfo.b * cos(TriangleInfo.Cr)));
            } else if (WantedProperty == "c" || TriangleInfo.A != 0 || TriangleInfo.a != 0 || TriangleInfo.b != 0) {
                #ifdef Debug
                printf("\n\nOp 11H");
                #endif

                TriangleInfo.Solution = sqrt((pow(TriangleInfo.a, 2)) - (pow(TriangleInfo.b, 2)) + (2 * TriangleInfo.a * TriangleInfo.b * cos(TriangleInfo.Ar)));
            } else if (WantedProperty == "c" || TriangleInfo.B != 0 || TriangleInfo.b != 0 || TriangleInfo.a != 0) {
                #ifdef Debug
                printf("\n\nOp 11I");
                #endif

                TriangleInfo.Solution = sqrt((pow(TriangleInfo.b, 2)) - (pow(TriangleInfo.a, 2)) + (2 * TriangleInfo.b * TriangleInfo.a * cos(TriangleInfo.Br)));
            }
        }
    }
    else {
        Error(2, WantedProperty);

        return;
    }

    printf("\n %s = %d", WantedProperty, TriangleInfo.Solution);

    return;
}

void UserInput() {
    struct TriangleInfoStruct TriangleInfo;

    char* WantedProperty;
    float ExpectedSolution = 0;

    printf("\nWanted Property: ");
    //fgets("%s", WantedProperty, stdin);
    scanf("%s", WantedProperty);
    printf("\n");

    if (strcmp(WantedProperty, "A") != 0 && strcmp(WantedProperty, "B") != 0 && strcmp(WantedProperty, "C") != 0 && strcmp(WantedProperty, "a") != 0 && strcmp(WantedProperty, "b") != 0 && strcmp(WantedProperty, "c") != 0 && strcmp(WantedProperty, "Area") != 0) {
        printf("\nPlease enter a valid aim.");
        UserInput();

        exit(0);
    }

    if (strcmp(WantedProperty, "A") != 0) {
        printf("\tA = ");
        fgets("%d", TriangleInfo.A, stdin);
        DegreesToRadians(&TriangleInfo.A, TriangleInfo.Ar);
    } else if (strcmp(WantedProperty, "B") != 0) {
        printf("\tB = ");
        fgets("%d", TriangleInfo.B, stdin);
        DegreesToRadians(&TriangleInfo.B, TriangleInfo.Br);
    } else if (strcmp(WantedProperty, "C") != 0) {
        printf("\tC = ");
        fgets("%d", TriangleInfo.C, stdin);
        DegreesToRadians(&TriangleInfo.C, TriangleInfo.Cr);
    }

    if (TriangleInfo.A != 0) {
        ++TriangleInfo.AngleCount;
    } else if (TriangleInfo.B != 0) {
        ++TriangleInfo.AngleCount;
    } else if (TriangleInfo.C != 0) {
        ++TriangleInfo.AngleCount;
    }

    //input check
    if ((TriangleInfo.A + TriangleInfo.B + TriangleInfo.C) > 180 || ((TriangleInfo.A + TriangleInfo.B + TriangleInfo.C) == 180 || TriangleInfo.AngleCount != 3) || ((TriangleInfo.A + TriangleInfo.B + TriangleInfo.C) < 180 || TriangleInfo.AngleCount == 3)) {
        Error(1, WantedProperty);
        UserInput();

        return;
    }

    if (strcmp(WantedProperty, "a") != 0) {
        printf("\ta = ");
        fgets("%d", TriangleInfo.a, stdin);
    } else if (strcmp(WantedProperty, "b") != 0) {
        printf("\tb = ");
        fgets("%d", TriangleInfo.b, stdin);
    } else if (strcmp(WantedProperty, "c") != 0) {
        printf("\tc = ");
        fgets("%d", TriangleInfo.c, stdin);
    }

    if (TriangleInfo.a != 0) {
        ++TriangleInfo.SideCount;
    } else if (TriangleInfo.b != 0) {
        ++TriangleInfo.SideCount;
    } else if (TriangleInfo.c != 0) {
        ++TriangleInfo.SideCount;
    }

    if (strcmp(WantedProperty, "Area") != 0) {
        printf("\tArea = ");
        fgets("%d", TriangleInfo.Area, stdin);
    }

    #ifdef Testing
    printf("\tExpected TriangleInfo.Solution = ");
    fgets("%d", ExpectedSolution, stdin);
    #endif

    #ifdef Debug
    printf("\n\nWanted Property: %s", WantedProperty);
    printf("\nAngle's: %d, %d, %d", TriangleInfo.A, TriangleInfo.B, TriangleInfo.C);
    printf("\nRadian's: %d, %d, %d", TriangleInfo.Ar, TriangleInfo.Br, TriangleInfo.Cr);
    printf("\nSide's: %d, %d, %d", TriangleInfo.a, TriangleInfo.b, TriangleInfo.c);
    printf("\nArea: %d", TriangleInfo.Area);
    printf("\nAngle count: %d", TriangleInfo.AngleCount);
    printf("\nSide count: %d", TriangleInfo.SideCount);
    printf("\nExpectedSolution: %d", ExpectedSolution);
    #endif

    Calculations(TriangleInfo, WantedProperty);

    #ifdef Testing
    printf("\nExpected TriangleInfo.Solution = %d", ExpectedSolution);

    double MarginOfErrorDouble = TriangleInfo.Solution - ExpectedSolution;
    printf("\n\nError (float) = %d", MarginOfErrorDouble);
    float MarginOfErrorFloat = TriangleInfo.Solution - ExpectedSolution;
    printf("\nError (float) = %d", MarginOfErrorFloat);
    int MarginOfErrorInt = TriangleInfo.Solution - ExpectedSolution;
    printf("\nError (int) = %d", MarginOfErrorInt);
    #endif
}

void FileInput(char* InputFile) {
    struct TriangleInfoStruct TriangleInfo;
    FILE* File = NULL;

    if ((File = fopen(InputFile, "r") ) != NULL) {
        char* Line, WantedProperty;
        int FileLength = 0, LineLength = 0, Read = 0;
        float ExpectedSolution = 0;

        while (getline(Line, LineLength, File)) {
            FileLength++;
        }

        #ifdef Debug
        printf("\nFileLength: %d", FileLength);
        #endif

        fclose(File);
        File = fopen(InputFile, "r");

        while (getline(Line, LineLength, File)) {
            int PropertyCount = 0, Output = 0;

            TriangleInfo.AngleCount = 0;
            TriangleInfo.SideCount = 0;

            #ifdef Debug
            printf("\n\n\n\n\n\n %d", Line);
            printf("\nLineLength = %d", LineLength);
            #endif

            for (int Character = 0; Character < LineLength; Character++) {
                if (Line[Character] == ' ') {
                    PropertyCount++;
                }
            }

            PropertyCount++;

            #ifdef Debug
            printf("\nProp count = %d", PropertyCount);
            #endif
            
            if (PropertyCount != 9) {
                Error(7, InputFile);

                exit(1);
            }

            for (int Character = 0; Character < LineLength; Character++) {
                int Read = 0;
                char* Temp, Property;

                //if (Line[Character] == ' ' || Line[Character] == Line[0]) {
                if (Line[Character] == ' ') {
                    for (Read = Character - 1; Read > 0; Read--) {
                        if (Line[Read] == ' ') {
                            break;
                        }
                    }
                    for (Read; Read < Character; Read++) {
                        Temp = Line[Read];
                        Property = Property + Temp;

                        #ifdef Debug
                        printf("\n\nTemp = %s", Temp);
                        printf("\nProperty = %s", Property);
                        printf("\nOutput: %d", Output);
                        #endif
                    }

                    if (Output == 0) {
                        WantedProperty = Property;
                    } else if (Output == 1) {
                        TriangleInfo.A = atof(Property);
                        DegreesToRadians(&TriangleInfo.A, TriangleInfo.Ar);
                    } else if (Output == 2) {
                        TriangleInfo.B = atof(Property);
                        DegreesToRadians(&TriangleInfo.B, TriangleInfo.Br);
                    } else if (Output == 3) {
                        TriangleInfo.C = atof(Property);
                        DegreesToRadians(&TriangleInfo.C, TriangleInfo.Cr);
                    } else if (Output == 4) {
                        TriangleInfo.a = atof(Property);
                    } else if (Output == 5) {
                        TriangleInfo.b = atof(Property);
                    } else if (Output == 6) {
                        TriangleInfo.c = atof(Property);
                    } else if (Output == 7) {
                        TriangleInfo.Area = atof(Property);
                    }

                    Output++;
                }

                if (Character == LineLength - 1) {
                    for (Read = LineLength - 1; 0 < Read; Read--) {
                        #ifdef Debug
                        printf("\n\nCharInt: %d", Read);
                        printf("\nCharChar: %s", Line[Read]);
                        #endif

                        if (Line[Read] == ' ') {
                            break;
                        }
                    }

                    for (int Character = Read + 1; Character <= LineLength - 1; Character++) {
                        Temp = Line[Character];
                        Property = Property + Temp;

                        #ifdef Debug
                        printf("\n\nTemp = %S", Temp);
                        printf("\nProperty = %s", Property);
                        printf("\nOutput: %d", Output);
                        #endif

                        ExpectedSolution = atof(Property);
                    }

                    Output++;
                }
            }

            if (TriangleInfo.A != 0) {
                ++TriangleInfo.AngleCount;
            } else if (TriangleInfo.B != 0) {
                ++TriangleInfo.AngleCount;
            } else if (TriangleInfo.C != 0) {
                ++TriangleInfo.AngleCount;
            }

            if (TriangleInfo.a != 0) {
                ++TriangleInfo.SideCount;
            } else if (TriangleInfo.b != 0) {
                ++TriangleInfo.SideCount;
            } else if (TriangleInfo.c != 0) {
                ++TriangleInfo.SideCount;
            }

            #ifdef Debug
            printf("\n\nWanted Property: %s", WantedProperty);
            printf("\nAngle's: %d, %d, %d", TriangleInfo.A, TriangleInfo.B, TriangleInfo.C);
            printf("\nRadian's: %d, %d, %d", TriangleInfo.Ar, TriangleInfo.Br, TriangleInfo.Cr);
            printf("\nSide's: %d, %d, %d", TriangleInfo.a, TriangleInfo.b, TriangleInfo.c);
            printf("\nArea: %d", TriangleInfo.Area);
            printf("\nAngle count: %d", TriangleInfo.AngleCount);
            printf("\nSide count: %d", TriangleInfo.SideCount);
            printf("\nExpected TriangleInfo.Solution: %d", ExpectedSolution);
            #endif

            if (WantedProperty != "A" || WantedProperty != "B" || WantedProperty != "C" || WantedProperty != "a" || WantedProperty != "b" || WantedProperty != "c" || WantedProperty != "Area") {
                #ifdef Debug
                printf("\n|%s|", WantedProperty);
                #endif

                printf("\nPlease edit InputFile to a valid aim.\n");
                main(0, ParamRemove);

                return;
            }

            //input check
            if ((TriangleInfo.A + TriangleInfo.B + TriangleInfo.C) > 180 || ((TriangleInfo.A + TriangleInfo.B + TriangleInfo.C) == 180 || TriangleInfo.AngleCount != 3) || ((TriangleInfo.A + TriangleInfo.B + TriangleInfo.C) < 180 || TriangleInfo.AngleCount == 3)) {
                Error(6, InputFile);

                exit(1);
            }
            
            Calculations(TriangleInfo, WantedProperty);

            #ifdef Testing
            printf("\nExpected TriangleInfo.Solution = %d", ExpectedSolution);

            float MarginOfErrorDouble = TriangleInfo.Solution - ExpectedSolution;
            printf("\n\nError (float) = %d", MarginOfErrorDouble);
            float MarginOfErrorFloat = TriangleInfo.Solution - ExpectedSolution;
            printf("\nError (float) = %d", MarginOfErrorFloat);
            int MarginOfErrorInt = TriangleInfo.Solution - ExpectedSolution;
            printf("\nError (int) = %d", MarginOfErrorInt);
            #endif
        }
    }
    else {
        Error(5, InputFile);
    }
}

void RepeatFunc() {
    char* Repeat;

    printf("\nRepeat (y/n)? ");
    fgets("%s", Repeat, stdin);

    if (Repeat == "y") {
        printf("\n");
        main(0, ParamRemove);

        return;
    } else if (Repeat == "n") {
        return;
    }
    else {
        printf("\nEnter y or n.");
        RepeatFunc();
    }
}

int main(int argc, char** argv) {
    #ifdef _WIN32

    /*for (int i = 1; i < argc; i++) {
        if (argv[i] == "-h" || "--Help") {
            printf("Help InputFile");
        } else if (argv[i] == "-f" || "--FileInput") {
            FileInput(argv[i + 1]);
        } else {
            printf("This is not a valid parameter.");
            main(1, ParamRemove);

            return 1;
        }
    }*/

    UserInput();
    RepeatFunc();

    printf("\n\n");

    return 0;

    //char* input_file;
    //printf("InputFile to Read from: ");
    //std::cin >> input_file;
    //FileInput(input_file);

    //return 0;

    #else

    char Argument;
    char* ArgumentFile;
    bool Help = false, FileMode = false;

    while (Argument = getopt(argc, argv, "htdf:")) {
        switch (Argument) {
            case 'h': {
                Help = true;
            } case 't': {
                Testing = true;

                break;
            } case 'd': {
                Debug = true;

                break;
            } case 'f': {
                FileMode = true;
                ArgumentFile = optarg;

                break;
            } case '?': {
                //char* ArgumentError(1, Argument);
                //Error(8, ArgumentError);

                exit(1);
            }
            default: {
                goto ExitLoop;
            }
        }
    }

    ExitLoop: ;

    #ifdef Debug
    printf("\n\nHelp: %s", Help ? "true" : "false");
    printf("\nTesting: %s", Testing ? "true" : "false");
    printf("\nDebug: %s", Debug ? "true" : "false");
    printf("\nfileMode: %s", FileMode ? "true" : "false");
    printf("\n");
    #endif

    if (Help) {
        printf("\nUsage: tcalc [OPTION/InputFile IF APPLICABLE]...");
        printf("\n\nWith no OPTION(s) default execute UserInput()");
        printf("\n\n  -h          Output Help InputFile");
        printf("\n  -t          Set bool Testing = true");
        printf("\n  -d          Set bool Debug = true");
        printf("\n  -f [InputFile]   Override default and execute FileInput(InputFile)");
        printf("\n\nSource code and documentation: <https://github.com/Kepler7894i/triangle-calculator>");
        
        exit(0);
    }

    if (FileMode) {
        FileInput(ArgumentFile);
    } else if (!FileMode) {
        UserInput();
    }

    printf("\n\n");
    
    exit(0);
    #endif
}