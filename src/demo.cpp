/** \file 		demo.cpp
 *  \author  	Anup Jayapal Rao
 *  \author  	Work derived from code examples by NeHe Productions
 *  \date		25 Feb 2009
 * 
 * Definitions for the demonstration class.
 * 
 * This file lists the definitions for the demonstration class.
 * It creates the demonstration based around the application class. 
 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include "demo.h"
#include "timer.h"

extern "C" 
{
	#include "carmine_defs.h"
	#include "carmine_addons.h"
}

using namespace std;
using std::stringstream;

/// The demomstration scene.
extern fScene oScene;

/// The object which is controlled by key presses.
extern fObject3D oCentreAnchor;

namespace NeHe
{		
	/*!
	 *	\brief Constructor.
	 */	
	Demo::Demo()
	{
		m_pCurrCamera = NULL;
		m_nCameraIndex = -1;
		m_bLighting = FALSE;
		m_pfontBig = NULL;
		m_pfontMedium = NULL;
		texLogo = 0;
	}
	
	/*!
	 *	\brief Destructor.
	 */	
	Demo::~Demo()
	{
		delete3DScene();
		
		glDeleteTextures(1, &texLogo);
		texLogo = 0;
		
		if(NULL != m_pfontMedium)
		{
			ftglDestroyFont(m_pfontMedium);
			m_pfontMedium = NULL;
		}
				
		if(NULL != m_pfontBig)
		{
			ftglDestroyFont(m_pfontBig);
			m_pfontBig = NULL;
		}
		
		m_nCameraIndex = -1;
		m_pCurrCamera = NULL;		
	}	

	/*!
	 *	\brief Initialises the demonstration.
	 *	\return true, if initialization succeeds.
	 * 			false, otherwise.
	 */
	bool Demo::init()
	{
		if (!App::init(WIDTH, HEIGHT, BITDEPTH, false, "What is a demo for ? Showing Off !"))
		{
			return false;
		}
		
		//glDisable(GL_MULTISAMPLE_ARB);
		glShadeModel(GL_SMOOTH);		// Enable Smooth Shading
		//glClearColor(0.827f,0.827f, 0.827f, 0.0f);	
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Black Background
		glClearDepth(1.0f);			// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);			// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			
		texLogo = loadTexture("Images/carmine_64x16.png",1,0);
		
		m_pfontBig = ftglCreatePixmapFont("Fonts/MgOpenModataOblique.ttf");
		if(!m_pfontBig)
		{
			cout << "Could not load big font"<< endl;
			return false;
		}
		ftglSetFontFaceSize(m_pfontBig, 25, 25);
		
		m_pfontMedium = ftglCreateTextureFont("Fonts/AndikaDesRevG.ttf");
		if(!m_pfontMedium)
		{
			cout << "Could not load medium font"<< endl;
			return false;
		}
		ftglSetFontFaceSize(m_pfontMedium, 14, 14);
		
		m_oDefaultCamera.m_pName = "Default";
		m_oDefaultCamera.fLocX = 0;
		m_oDefaultCamera.fLocY = -16.0;
		m_oDefaultCamera.fLocZ = 16.0;
		m_oDefaultCamera.fRotX = 45.0;//90.0;
		m_oDefaultCamera.fRotY = 0.0;//180.0;
		m_oDefaultCamera.fRotZ = 0.0;
		m_oDefaultCamera.fScaleX = 1.0;
		m_oDefaultCamera.fScaleY = 1.0;
		m_oDefaultCamera.fScaleZ = 1.0;
		m_oDefaultCamera.fClipStart = 0.1;
		m_oDefaultCamera.fClipEnd = 100.0;
		m_oDefaultCamera.fLens = 34.0;
		m_oDefaultCamera.m_parrParentIndices = NULL;		
		
		resetCameraToDefault();
		
		create3DScene();	
		
		m_RotationAngle = 0.0;	
		
		return true;
	}
	
	/*!
	 *	\brief Resets the camera to the external default camera.
	 */		
	void Demo::resetCameraToDefault()
	{
		m_nCameraIndex = -1;
		m_pCurrCamera = &m_oDefaultCamera;
	}
		
	/*!
	 *	\brief Creates or loads the intended 3D scene(s) and populates it with light setup. 
	 */		
	void Demo::create3DScene()
	{		
		createParent(&oScene);		
		createLights(&oScene);	
	}
	
	/*!
	 *	\brief Deletes the 3D scene(s) that were previously loaded in the demonstration.
	 */		
	void Demo::delete3DScene()
	{
		deleteParent(&oScene);		
	}	
	
	/*!
	 *	\brief  Activates the currently selected camera by applying the viewport properties
	 *			based on the camera parameters.
	 */		
	void Demo::activateCamera()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(m_pCurrCamera->fLens,(GLfloat)m_Width/(GLfloat)m_Height,
						m_pCurrCamera->fClipStart,m_pCurrCamera->fClipEnd);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();		
	}
	
	/*!
	 *	\brief Iterates through the cameras in the provided scene including the external default camera.
	 *	\param pScene Pointer to the scene to be rendered.
	 */		
	void Demo::switchCamera(fScene* pScene)
	{
		if(pScene)
		{
			m_nCameraIndex++;
			fCamera* pCamera = pScene->m_parrpCameras[m_nCameraIndex];
			if(pCamera)
			{
				m_pCurrCamera = pCamera;
				activateCamera();
			}
			else
			{
				resetCameraToDefault();
			}
		}
	}	
	
	/*!
	 *	\brief Handles key press events encountered by the demonstration during animation.
	 */				
	void Demo::handleKeyPress()
	{
		//cout << "handleKeyPress "<< endl;
		if(m_Keys[SDLK_TAB])
		{
			//cout << "Switching camera to " << m_nCameraIndex << endl;
			switchCamera(&oScene);
		}
		
		if(m_Keys[SDLK_w])
		{
			oCentreAnchor.fLocY -= 0.1;			
		}
		
		if(m_Keys[SDLK_l])
		{
			m_bLighting = !m_bLighting;
			if ( m_bLighting )
			{
				cout << "Lighting ON" << endl;
			}
			else
			{
				cout << "Lighting OFF" << endl;
			}
		}				
	}
	
	/*!
	 *	\brief Handles key release events encountered by the demonstration during animation.
	 */	
	void Demo::handleKeyRelease()
	{
				
	}	

	/*!
	 *	\brief Resizes the OpenGL surface. 
	 *	\param width Width of the OpenGL surface.
	 *	\param height Height of the OpenGL surface.
	 */
	void Demo::resize(int width, int height)
	{
		cout << "Resizing Window to " << width << "x" << height << endl;
		
		if (height <= 0)
		{
			height = 1;
		}

		glViewport(0,0,width,height);
		
		activateCamera();
	}
	
	/*!
	 *	\brief Rendering routine that is repeatedly called for every frame of the animation
	 */		
	void Demo::draw()
	{	
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		glMatrixMode(GL_MODELVIEW);
		
		if ( m_bLighting )
		{
			glEnable( GL_LIGHTING );
		}
					
		glLoadIdentity();
				
		positionCamera(m_pCurrCamera, &oScene);
		
		glRotatef(m_RotationAngle, 0.0, 0.0, 1.0);
		
		//glEnable(GL_MULTISAMPLE_ARB);
		renderParent(&oScene);
		//glDisable(GL_MULTISAMPLE_ARB);
		
		if ( m_bLighting )
		{
			glDisable( GL_LIGHTING );
		}				
		
		m_RotationAngle += 0.04; //increase the angle so the cube keeps spinning
		//m_RotationAngle += 1.0;
		if(m_RotationAngle > 360.0) //prevent from having an angle greater than a float value can store ^^
		{	m_RotationAngle -= 360.0;	}
		
		//cout << "see me3" << endl;
		
		DrawTexture_2D( texLogo, 10, 334, 64, 16);
		showInfo();		
	}
	
	/*!
	 *	\brief Displays demonstration specific information such as frame rate. It is used here to render the rotation
	 * 		   value of the demonstration scene.
	 */			
	void Demo::showInfo()
	{
		static timer otimer;
		static int count = 0;
		static stringstream ss;
		static stringstream srot;
		double elapsedTime;

		// update fps every second
		elapsedTime = otimer.getElapsedTime();
		if(elapsedTime < 1.0)
		{
			++count;
		}
		else
		{
			ss.str("");
			ss << std::fixed << std::setprecision(0);
			ss << (count / elapsedTime) << " FPS" << ends; // update fps string
			//ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
			count = 0;			// reset counter
			otimer.start();     // restart timer
		}
			
		srot.str("");
		srot << std::fixed << std::setprecision(0);
		
		srot << "[Camera : " << m_pCurrCamera->m_pName << "][Rotation : " << m_RotationAngle << " degs]" <<ends;
		
		Begin_Font2D();
			glColor4f(1.0, 1.0, 1.0, 1.0);
			RenderFont(m_pfontMedium, WIDTH-5.0, 5.0, ss.str().c_str(),RIGHT_TOP);					
			RenderFont(m_pfontMedium, WIDTH-5.0, HEIGHT-5.0, srot.str().c_str(),RIGHT_BOTTOM);
		End_Font2D();
		glColor4f(1.0, 1.0, 1.0, 1.0);			
	}	
};
