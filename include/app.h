/** \file 		app.h
 *  \author  	Anup Jayapal Rao
 *  \author  	Work derived from code examples by NeHe Productions
 *  \date		25 Feb 2009
 * 
 * Declaration for the class used to setup the OpenGL application.
 * 
 * This file lists the definitions for the set up of the OpenGL application
 */

#ifndef _SCENE
#define _SCENE

#include "window.h"

extern "C" 
{
	#include "carmine_defs.h"
	#include "carmine_addons.h"
}

#include <FTGL/ftgl.h> 

using namespace FTGL;

namespace NeHe 
{
	/// Enumeration specifying the anchor position of the text
	typedef enum 
	{ 
		/// The text is drawn with the specified anchor at the Left Top corner.
		LEFT_TOP,
		
		/// The text is drawn with the specified anchor at the Right Top corner.
		RIGHT_TOP,
		
		/// The text is drawn with the specified anchor at the Left Bottom corner.
		LEFT_BOTTOM,
		
		/// The text is drawn with the specified anchor at the Right Bottom corner.
		RIGHT_BOTTOM	
			
	} enumTextAnchor;
	
	/** 
	 * \class	App
	 * \brief	Class used to setup the OpenGL application.
	 * 
	 * This class is responsible for setting up the OpenGL application.
	 * This class was created using the CPP classes provided by NeHe Productions.
	 */		
	class App 
	{
		public:
		
			/// Constructor.
			App();
			
			/// Destructor.
			virtual ~App();
						
			/// Initialiser.
			virtual bool init(int width, int height, int bpp, bool fullscreen, const string& title);
			
			/// Application starter (after initialization)
			virtual void run();
			
			/// Key press handler.
			virtual void handleKeyPress();
			
			/// Key release handler.
			virtual void handleKeyRelease();
			
			/// Get Height accessor.
			virtual int getHeight();
			
			/// Get Width accessor.
			virtual int getWidth();
			
			/// Enables 2D drawing mode.
			virtual void Enable2D();
			
			/// Renders a 2D texture.
			virtual void DrawTexture_2D(GLuint texImage, int nX, int nY, int sX, int sY);
			
			/// Disables 2D drawing mode.
			virtual void Disable2D();		
			
			/// Begin 2D Font drawing mode
			virtual void Begin_Font2D();
			
			/// Render 2D Font
			virtual void RenderFont(FTGLfont*	pfont, float x, float y, const char* str, enumTextAnchor eAnchor);
			
			/// End 2D Font drawing mode
			virtual void End_Font2D();	
					
		protected:
			
			/// Rendering routine that is repeatedly called for every frame of the animation
			virtual void draw();
			
			/// Method that called upon resizing the OpenGL window
			virtual void resize(int x, int y);
			
			/// Event handler for the application
			virtual bool processEvents();
						
			/// Width of the application visual
			int 	m_Width;
			
			/// Height of the application visual
			int 	m_Height;
			
			/// Application window object
			Window 	m_Window; 
			
			/// Array to record key strokes
			unsigned int m_Keys[SDLK_LAST]; 
	};
};

#endif //_SCENE

