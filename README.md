# BUS ADMITTANCE MATRIX HANDLER

This is a simple C++ console application which generates a bus admittance matrix, from the data of the admittance values and the nodes they are connected to. Each element is only eneterd once and the
rest is handled by the program.

it takes input from user and feeds it into the matrix. The dimensions of the matrix are obtained from the user input. 

The code contains multiple implementations that can be used for purposes other than its own like, generating a 2D vector 
at runtime based on user input, implementing a menu function and the ability of the program to take internally defined
commands into account. 

### Handling Complex Numbers - v0.6/2019
To enter a complex admittance value when asked; enter the data in the
following rectangular format.
for a complex value " x + i*y " where x is the real part and y is the imaginary part of the complex number. enter the data as follows for value section of bus admittance values.

        (x,y)

including the brackets and seperating the real and imaginary values by a comma.