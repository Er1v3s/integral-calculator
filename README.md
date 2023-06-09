## x86 Assembly (FASM) Program: Integration of 2cos(3x) ##

This program, written in x86 assembly (FASM), calculates the integral value of the function 2cos(3x). It utilizes a numerical method, specifically the rectangle method (midpoint rule), to approximate the integral value.

### Function ###

The program computes the integral of the function 2cos(3x), where 'cos' represents the cosine function, and 'x' is the independent variable. This function is used as an example, but the program can be modified to calculate integrals of other functions.

### Input ###

The program takes the following input from the user:
1. Starting point of the integration range (a)
2. Ending point of the integration range (b)
3. Number of divisions (n) to control the accuracy of the approximation. A higher number of divisions leads to a more accurate result.

### Algorithm ###

1. The program divides the integration range [a, b] into n equal subintervals.
2. For each subinterval, the program calculates the midpoint as the x-value to evaluate the function.
3. It then computes the function value 2cos(3x) at each midpoint.
4. The program multiplies each function value by the width of the subinterval.
5. Finally, it sums up all the products to approximate the integral value.

### Requirements ###

To compile and run this program, the following are required:
- FASM assembler compiler
- x86 runtime environment (e.g., an operating system compatible with the x86 architecture)