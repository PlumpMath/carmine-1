/** \file 		demo.h
 *  \author  	Anup Jayapal Rao
 *  \author  	Work derived from code examples by NeHe Productions
 *  \date		25 Feb 2009
 * 
 * Declaration for the class used to demonstrate the OpenGL feature(s).
 * 
 * This file lists the definitions for the set up of the OpenGL demonstration and runs the animation.
 */

#ifndef _DEMO
#define _DEMO

// Important comment mentioned by NeHe.
// We need to include window first because GLee needs to be included before GL.h
extern "C" 
{
	#include "carmine_defs.h"
	#include "carmine_addons.h"
}
#include <FTGL/ftgl.h> 

#include "app.h"
#include "mainpage.h"

/// Width of the OpenGL screen surface
#define WIDTH		640
/// Height of the OpenGL screen surface
#define HEIGHT		360
/// Colour depth of the OpenGL screen surface
#define BITDEPTH	16

using namespace FTGL;

/** 
 * \namespace	NeHe
 * \brief		The global namespace in which the application classes exist.
 * 
 * The NeHe namespace contains all the classes responsible for setting up the OpenGL in an SDL environment
 * using C++ with GLee included. Please look at http://nehe.gamedev.net for OpenGL tutorials and other related material.
 */
namespace NeHe 
{
	/** 
	 * \class	Demo
	 * \brief	Class used to demonstrate the OpenGL feature(s).
	 * 
	 * This class is responsible for setting up the OpenGL demonstration.
	 * This class was created using the CPP classes provided by NeHe Productions.
	 */	
	class Demo : public App
	{
		public:
		
			/// Constructor.
			Demo();
			
			/// Destructor.
			virtual ~Demo();
			
			/// Initialiser.
			virtual bool init();
			
			/// Key press handler.
			virtual void handleKeyPress();
			
			/// Key release handler.
			virtual void handleKeyRelease();
			
			/// Resets current camera to default camera.
			virtual void resetCameraToDefault();	
			
			/// Activates the current camera by applying its parameters.
			virtual void activateCamera();
			
			/// Switches current camera through array of cameras defined in the scene.
			virtual void switchCamera(fScene* pScene);
					
		private:
		
			/// Rendering routine that is repeatedly called for every frame of the animation
			virtual void draw();
			
			/// Method that called upon resizing the OpenGL window
			virtual void resize(int x, int y);
				
			///	Displays the application specific information on the rendered scene
			void showInfo();
			
			/// Creates the 3D scene
			void create3DScene();
			
			/// Deletes the 3D scene
			void delete3DScene();
				
			/// Texture for the application Logo
			GLuint texLogo;
			
			/// Font used for rendering large text
			FTGLfont* m_pfontBig;
			
			/// Font used for rendering normal text
			FTGLfont* m_pfontMedium;
			
			/// The default camera used initially and in the absence of any additional cameras
			fCamera	m_oDefaultCamera;
			
			/// Pointer to the current camera
			const fCamera* m_pCurrCamera;			
			
			/// Index to the current camera
			int m_nCameraIndex;
			
			/// Boolean to indicate of lighting must be enabled
			int m_bLighting;
			
			/// Angle of rotation used to rotate the scene during demonstration
			float m_RotationAngle; 
	};
};

#endif // _DEMO
