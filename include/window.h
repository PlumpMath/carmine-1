/** \file 		window.h
 *  \author  	Anup Jayapal Rao
 *  \author  	Work derived from code examples by NeHe Productions
 *  \date		25 Feb 2009
 * 
 * Declaration for the class used to setup the application window.
 * 
 * This file lists the definitions for the set up of the application window using SDL.
 */

#ifndef _NEHE_WINDOW
#define _NEHE_WINDOW

#include <string>
#include <iostream>

#include "carmine_opengl.h"

using std::string;

namespace NeHe
{
	/** 
	 * \class	Window
	 * \brief	Class used to setup the application window.
	 * 
	 * This class is responsible for setting up the application window using SDL.
	 * This class was created using the CPP classes provided by NeHe Productions.
	 */		
	class Window
	{
		public:
		
			/// Constructor.		
			Window();
			
			/// Destructor.			
			~Window();
			
			/// Method to create the application window with specified parameters.
			bool createWindow(int width, int height, int bpp, bool fullscreen, const string& title);
			
			/// Method to set the size of the application window.
			void setSize(int width, int height);
			
			/// Get Height accessor.
			int getHeight();
			
			/// Get Width accessor.
			int getWidth();
					
		private:
		
			/// Width of the application visual
			int m_Width;
			
			/// Height of the application visual
			int m_Height;
			
			/// Colour Depth of the application visual
			int m_Bpp;
			
			/// Boolean to set full screen visual
			bool m_Fullscreen;
			
			/// Title of the application window
			string m_Title;
	};
};

#endif	// _NEHE_WINDOW

