# triangle-calculator

This repository is for a C++ program that uses logic to find the best equation & calculate requested property of the triangle using it based off of known properties of the triangle. Designed to be as automated as possible.

This program is in stable currently as all known bugs fixed (report any as an issue) and all wanted functionality implemented (more may come later).  

### Downloads:  
Windows 32-bit - Download tcalc-windows-x86.exe  
Windows 64-bit - Download tcalc-windows-x64.exe  
Linux 32-bit - Download tcalc-linux-x86  
Linux 64 bit - Download tcalc-linux-x64  

If you don't know what instruction set your computer used download the corresponding x86 file for your OS.

### To run:  
Windows will allow you to run the program by double clicking on it as an exe  
Linux will allow you to run the program with ./(downloaded file name)  

### To compile:  
Download triangle-calculator.cpp and then you can compile this given you OS and instruction set  
Windows 32-bit - Use an IDE
Windows 64-bit - Use an IDE
Linux 32-bit - g++ -m32 tcalc.cpp -o tcalc-x86  
Linux 64-bit - g++ -m64 tcalc.cpp -o tcalc-x64  

### Use:  
When the program load's enter in any known value's for angle's or side's on the triangle as well the side or angle to be calculated. If it is possible based off of that information it will calculate the side or angle specified by working out the equation to use and then entering value's into the formula.  
Note - This program cannot calculate the value of a side or angle that is required to have the right information to calculate the requested side or angle.
