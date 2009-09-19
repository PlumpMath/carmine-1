/** \file window.cpp
 *  \author  	Anup Jayapal Rao
 *  \author  	Work derived from code examples by NeHe Productions
 *  \date		25 Feb 2009
 * 
 * Definitions for the application window class.
 * 
 * This file lists the definitions for the application window class.
 * It creates the window using SDL with an OpenGL surface. 
 */
#include "window.h"

namespace NeHe
{
	/*!
	 *	\brief Constructor.
	 */	
	Window::Window():
		m_Width(0),
		m_Height(0),
		m_Bpp(0),
		m_Fullscreen(false)
	{

	}
	
	/*!
	 *	\brief Destructor.
	 */		
	Window::~Window()
	{
		SDL_Quit();
	}
	
	/*!
	 *	\brief Creates the application window using SDL.
	 *	\param width Width of the application window.
	 *	\param height Height of the application window.
	 *	\param bpp Colour depth of the application window.
	 *	\param fullscreen 	true, if application must be fullscreen.
	 * 						false, if it must be windowed.
	 *	\param title Reference to string containing the intended title of the application window.
	 *	\return true, if initialization succeeds.
	 * 			false, otherwise.
	 */	
	bool Window::createWindow(int width, int height, int bpp, bool fullscreen, const string& title)
	{
		if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) 
		{		
			return false;
		}
		
		//Copy the values incase we need them
		m_Height = height;
		m_Width = width;
		m_Title = title;
		m_Fullscreen = fullscreen;
		m_Bpp = bpp;
		
		//all values are "at least"!	
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		
		//AntiAliasing
		//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);	
		//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);	
		
		// Set the title.
		SDL_WM_SetCaption(title.c_str(), title.c_str());

		// Flags tell SDL about the type of window we are creating.
		int flags = SDL_OPENGL;
		
		if(fullscreen == true)
		{
			flags |= SDL_FULLSCREEN;
		}

		// Create the window
		SDL_Surface * screen = SDL_SetVideoMode( width, height, bpp, flags );
		
		if(screen == 0)
		{
			return false;
		}
		
		//SDL doesn't trigger off a ResizeEvent at startup, but as we need this for OpenGL, we do this ourself
		SDL_Event resizeEvent;
		resizeEvent.type = SDL_VIDEORESIZE;
		resizeEvent.resize.w = width;
		resizeEvent.resize.h = height;
		
		SDL_PushEvent(&resizeEvent);

		return true;
	}
	
	/*!
	 *	\brief Sets the size attributes of the application window. It does not change the visual size.
	 *	\param width Width of the application window.
	 *	\param height Height of the application window.
	 */		
	void Window::setSize(int width, int height)
	{
		m_Height = height;
		m_Width = width;
	}
	
	/*!
	 *	\brief Returns the height of the application window.
	 *	\return The height of the application window.
	 */		
	int Window::getHeight()
	{
		return m_Height;
	}
	
	/*!
	 *	\brief Returns the width of the application window.
	 *	\return The width of the application window.
	 */			
	int Window::getWidth()
	{
		return m_Width;
	}
};
