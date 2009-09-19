/** \file 		main.cpp
 *  \author  	Anup Jayapal Rao
 *  \author  	Work derived from code examples by NeHe Productions
 *  \date		25 Feb 2009
 * 
 * Definitions for the main application.
 * 
 * This file lists the definitions for the main application. It creates a demo object
 * and upon successful initialization calls the run method on it. Cleanup is performed
 * upon exiting the demo.
 */

#include <string>
#include <iostream>

#include "demo.h"

using namespace NeHe;

/*!
 *	\brief The main application routine.
 *	\param argc Number of command line parameters.
 *	\param argv Pointer to array of command line parameters.
 *	\return Exit status.
 */
int main(int argc, char **argv)
{
	// Create a demo instance
	Demo* demo = new Demo();

	// If we can initialize the demo
	if(demo->init())
	{
		// Then we run it
		demo->run();
	}
	else 
	{
		// Throw error message
		std::cout << "Initialization failed!" << std::endl;
	}
	
	// If we can't initialize, or the demo has quit we delete the instance
	delete demo;
		
	return 0;
};
