/* BUS_ADMITTANCE_MATRIX_GENERATOR.cpp :
@author - Yawar Badri (c) copyright 2019
@version - 0.6/2019
@Title - BUS ADMITTANCE MATRIX GENERATOR

!NOTE - The program uses vectors to create a matrix at run time thus for
		large matrix sizes memory allocation may go unchecked and might lead
		to unknown behaviour of the program. For efficiency reasons keep the
		matrix size below 1000.

		! - this program basic error handling, however a lot of scenarios are
		still not implemented and might thus lead to unknown behaviour which
		might cause harm to your system.

		Some of the known issues are;
		1. if a alphanumeric input is given where the program asks for a number,
				the program becomes unstable and goes into a uncontrolled loop..
*/

//#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <new>
#include <complex>
#include <stdlib.h>
//PROTOTYPES
void init();
//void bdiag(int dim, std::vector<double> bus_matrix);


//#GLOBALS
std::string str;		//input buffer variable hold


//CLASSES
class bvec
{
public:
	std::complex<double> val ;					//implement complex number handling 21-04-2019||2100
	unsigned int n1 = 0, n2 = 0;
};



int main()
{

	//#LOCALS
	bvec vect;

	init();

	//OBTAIN THE SIZE OF THE BUS MATRIX----------------------------------------------------------
	int size_b = 2; //basic default value
	while (true) {
		std::cout << "enter the number of junctions' = ";
		std::cin >> size_b;

		//error handling
		if (size_b >= 2) {
			break;
		}
		std::cout << "\n\t/!\\ - invalid input\n";
		if (size_b < 2)
		{
			std::cout << "/x\\ terminating program - unhandled exception !\n \a\a ";
			exit(0);
		}
	}
	//std::cout << "\nprogram flow after matrix size";				//debug 1 

	//---------------------Generate Dynamic Array------------------------------------------------
	std::vector<std::vector<std::complex<double>> > bam(size_b, std::vector<std::complex<double>>(size_b));		// update modded the complex definition of the bam
	for (int i = 0; i < size_b; i++)																			// it works | still write a test for it
	{
		for (size_t j = 0; j < size_b; j++)
		{
			bam[i][j] = 0;
		}
	}		//initialise the BAM to zero 
	//std::cout << "\nprogram flow after array-dyn creation";		//debug 2

	//--------------------Main Program Flow------------------------------------------------------
	std::cout << "\nenter admittance as per the mentioned format!\n";
	bool index = true;
	while (true)
	{
		/*
		PROGRAM LOOP

		Do not alter.
		*/
#pragma region Reg_tst



		////test code
		//	// write element
		//for (int i = 0; i < size_b; i++)
		//{
		//	for (int j = 0; j < size_b; j++)
		//	{
		//		bam[i][j] = i;
		//	}
		//}
		////array[0][0] = 3.5;
		//// output element
		//for (int i = 0; i < size_b; i++)
		//{
		//	for (int j = 0; j < size_b; j++)
		//	{
		//		std::cout << bam[i][j] << "\t";
		//	}
		//	std::cout << std::endl;
		//}

#pragma endregion

		//debug - print error
	/*	for (int i = 0; i < size_b; i++)
		{
			for (int j = 0; j < size_b; j++)
			{
				std::cout << bam[i][j] << "\t";
			}
			std::cout << std::endl;
		}*/
		std::cout << "\t\t\n\a MAIN - Enter command\n";
		std::cin >> str;
		if (str == "start")
		{
			while (index)
			{

				std::cout << "enter the element value, node 1 and node 2\n";
				std::cin >> vect.val >> vect.n1 >> vect.n2;
				std::cin.clear();
				//std::cout << "val " << vect.val << "\nn1 " << vect.n1 << "\nn2 " << vect.n2;		//debug 4
				if ((vect.n1 > size_b) || (vect.n2 > size_b))
				{
					//std::cout << "\nprogram flow in <if> test";		//debug 3
					std::cout << "\nunhandled exception! - terminating program\n";
					exit(0);
				}
				else
				{
					std::cout << "------------------\n";
					//handle buses with a common reference | ie with either node = 0
					if (vect.n1 == 0)
					{
						bam[vect.n2 - 1][vect.n2 - 1] += vect.val;
					}
					else if (vect.n2 == 0)
					{
						bam[vect.n1 - 1][vect.n1 - 1] += vect.val;
					}
					else
					{
						bam[vect.n1 - 1][vect.n2 - 1] -= vect.val;
					}
					//handle case: for buses not connected to reference the values are added to both indices
					//also replicate the admittance as reverse
					if ((vect.n1 != 0 && vect.n2 != 0) && (vect.n1 != vect.n2))
					{
						bam[vect.n1 - 1][vect.n1 - 1] += vect.val;
						bam[vect.n2 - 1][vect.n2 - 1] += vect.val;
						bam[vect.n2 - 1][vect.n1 - 1] -= vect.val;						// implemented inherent negative non-diagonal elements

					}

				}


				//print the vector back
				std::cout << "\n\t vector[ " << vect.val << ", " << vect.n1 << ", " << vect.n2 << " ]\n\n";

				//check if the input is terminated by user
				std::cin >> str;
				if (str == "end")
				{
					index = false;
					break;
				}

			}
		}
		//reset start condition
		index = true;
		
		//std::cout << "\nprogram flow after input while test";		//debug 5

		//terminate program loop by entering exit in console
		std::cin >> str;
		if (str == "exit")
			exit(0);
		//exit the program flow input section | this will termonate the program
		if (str == "all")
			break;
		//print the bus matrix if the following command is entered
		if (str == "print_bm")
		{
			for (int i = 0; i < size_b; i++)
			{
				for (int j = 0; j < size_b; j++)
				{
					std::cout << bam[i][j] << "\t";
				}
				std::cout << std::endl;
			}
		}
		//print help if the following command is entered
		if (str == "help")
		{
			using namespace std;
			cout << "\a\t\t\n\n"
				"\t\t\tHELP\n\n"
				"\t\tThis is the help section of the program\n\n"
				"Start by entering the number of buses as asked\n"
				"Then to start feeding elements into the program matrix"
				"; Enter the following command\n\t'start'.This will bring up "
				"the vector input system.\n Enter the individual bus component parameters as per the "
				"following scheme\n\n"
				"<value> then press enter\n"
				"node 1 then press enter\n"
				"node 2 then press enter\n\n Now a dash line indicating that the parameters have been\n"
				"recorded shows on the next line, to continue the process of feeding elements press '-' \n"
				"and then press enter.\n"
				"\n\n\t To exit the element entering mode, enter 'end' command after the dash line\n"
				"and press enter. This will make the program exit to main level\n"
				"\n\n At main level the following commands are present;\n\n"
				"\t'exit'\t\t-terminates the program and exits the flow\n"
				"\t'all'\t\t-exits the program control loop, used for debugging purpose\n"
				"\t'print_bm'\t\t-prints the BUS ADMITTANCE MATRIX JUST ENTERED\n\n"
				" webpage - https://github.com/wayri/bus_matrix \n";
		}
		if (str == "about")
		{
			init();
		}

	}

	//--------------------------------------------------------------------------------------------

}

void init()
{
	//init intro print statements
	std::cout << "\t\tBUS ADMITTANCE MATRIX GENERATOR\n"
					"\t\t\nCopyright (c) Yawar Badri - 2019";
	std::cout << "This program generates a bus admittance matric based on user input\n"
				"\nThis is a console application : For help enter \"help\" , \"exit\" to exit the program, \"about\" for about\n"
				"These commands should be entered twice to work. ";

	std::cout << "\n\n-->Enter the element data in the following format\n"
				"-->[val, node1, node2]\nPress 'Enter'\n Keep filling the entries until all of the elements"
				" are included\n\n";
	return;
}


