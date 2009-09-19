/** \file 		app.cpp
 *  \author  	Anup Jayapal Rao
 *  \author  	Work derived from code examples by NeHe Productions
 *  \date		25 Feb 2009
 * 
 * Definitions for the application class.
 * 
 * This file lists the definitions for the application class.
 * It creates the application based around the window class. 
 */

#include "app.h"

extern "C" 
{
	#include "carmine_addons.h"
}

using namespace std;

namespace NeHe
{	
	/*!
	 *	\brief Constructor.
	 */	
	App::App()
	{
		m_Width = 0;
		m_Height = 0;			
	}

	/*!
	 *	\brief Destructor.
	 */	
	App::~App()
	{
	}

	/*!
	 *	\brief Rendering routine that is repeatedly called for every frame of the animation
	 */	
	void App::draw()
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
	}

	/*!
	 *	\brief Resizes the OpenGL surface. 
	 *	\param width Width of the OpenGL surface.
	 *	\param height Height of the OpenGL surface.
	 */	
	void App::resize(int width, int height)
	{
		cout << "Resizing Window to " << width << "x" << height << endl;
		
		if (height <= 0)
		{
			height = 1;
		}

		glViewport(0,0,width,height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(34.0,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	/*!
	 *	\brief Handles key press events encountered by the application during animation.
	 */	
	void App::handleKeyPress()
	{
		
	}
	
	/*!
	 *	\brief Handles key release events encountered by the application during animation.
	 */		
	void App::handleKeyRelease()
	{
		
	}
		
	/*!
	 *	\brief Processes application events encountered during animation.
	 *	\return true, if the event was processed. false, otherwise.
	 */	
	bool App::processEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))//get all events
		{
			switch (event.type)
			{
				// Quit event
				case SDL_QUIT:
				{
					// Return false because we are quitting.
					return false;
				}

				case SDL_KEYDOWN:
				{
					SDLKey sym = event.key.keysym.sym;
					if(sym == SDLK_ESCAPE) //Quit if escape was pressed
					{
						return false;
					}
					m_Keys[sym] = 1;
					//cout << "handleKeyPress "<< sym << endl;
					handleKeyPress();	
					break;
				}

				case SDL_KEYUP:
				{
					SDLKey sym = event.key.keysym.sym;
					m_Keys[sym] = 0;
					handleKeyRelease();
					break;
				}

				case SDL_VIDEORESIZE:
				{
					//the window has been resized so we need to set up our viewport and projection according to the new size
					resize(event.resize.w, event.resize.h);
					break;
				}
				// Default case
				default:
				{
					break;
				}
			}
		}

		return true;
	}
	
	/*!
	 *	\brief Initialises the application.
	 *	\param width Width of the application window.
	 *	\param height Height of the application window.
	 *	\param bpp Colour depth of the application window.
	 *	\param fullscreen 	true, if application must be fullscreen.
	 * 						false. if it must be windowed.
	 *	\param title Reference to string containing the intended title of the application window.
	 *	\return true, if initialization succeeds.
	 * 			false, otherwise.
	 */	
	bool App::init(int width, int height, int bpp, bool fullscreen, const string& title)
	{
		if(!m_Window.createWindow(width, height, bpp, fullscreen, title))
		{
			return false;
		}
		
		m_Width = width;
		m_Height = height;

		glClearColor(0.0, 0.0, 0.0, 1.0);

		return true;
	}

	/*!
	 *	\brief Performs the application event processing loop.
	 */	
	void App::run()
	{
		while(processEvents())
		{
			draw();
			SDL_GL_SwapBuffers();
		}
	}
	
	/*!
	 *	\brief Get Height accessor.
	 *	\return The height of the application window.
	 */	
	int App::getHeight()
	{
		m_Height = m_Window.getHeight();
		return m_Height;
	}
	
	/*!
	 *	\brief Get Width accessor.
	 *	\return The width of the application window.
	 */	
	int App::getWidth()
	{
		m_Width = m_Window.getWidth();
		return m_Width;
	}
	
	/*!
	 *	\brief	Enables 2D drawing mode in OpenGL. It is intended for 2D geometry as well as
	 *  		2D texture rendering. It must not be mixed with the 2D drawing routine for fonts.
	 */	
	void App::Enable2D()
	{
		glDisable( GL_DEPTH_TEST );

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glOrtho(0, m_Width, m_Height, 0, 0, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();		
	}

	/*!
	 *	\brief	Disables 2D drawing mode in OpenGL. It must not be mixed with the 2D drawing routine for fonts.
	 */
	void App::Disable2D()
	{	
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glEnable(GL_DEPTH_TEST );		
	}
	
	/*!
	 *	\brief	Draws a rectangular 2D texture in OpenGL with ends as specified by the points. It must not be mixed 
	 * 			with the 2D drawing routine for fonts. The calls to this function must be enclosed between calls to
	 * 			Enable2D and Disable2D.
	 *	\param	texImage Texture ID.
	 *	\param	nX Top left X co-ordinate.
	 *	\param	nY Top left Y co-ordinate.
	 *	\param	sX Width of the rectangular area to be rendered.
	 *	\param	sY Height of the rectangular area to be rendered.
	 */
	void App::DrawTexture_2D(GLuint texImage, int nX, int nY, int sX, int sY)
	{
		Enable2D();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, texImage );
		glBegin( GL_QUADS );
			glColor4f(1.0, 1.0, 1.0, 1.0);			
			glTexCoord2d(0.0,0.0);
			glVertex2d(nX, nY);
			glTexCoord2d(1.0,0.0);
			glVertex2d(nX+sX,nY);
			glTexCoord2d(1.0,1.0);
			glVertex2d(nX+sX,nY+sY);
			glTexCoord2d(0.0,1.0);
			glVertex2d(nX,nY+sY);						
		glEnd();
		glDisable( GL_TEXTURE_2D );
		Disable2D();
		glColor4f(1.0, 1.0, 1.0, 1.0);		
	}
	
	/*!
	 *	\brief	Enables 2D font rendering in OpenGL. It must not be mixed with the 2D geometry routines.
	 */	
	void App::Begin_Font2D()
	{
		glDisable( GL_DEPTH_TEST );

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glOrtho(0, m_Width, 0, m_Height, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();		
	}

	/*!
	 *	\brief	Renders a 2D font in OpenGL with the specified point as the anchor. It must not be mixed 
	 * 			with other 2D drawing routines. The calls to this function must be enclosed between calls to
	 * 			Begin_Font2D and End_Font2D.
	 *	\param	pfont Pointer to the font which must be used for rendering text.
	 *	\param	x X co-ordinate of the anchor point.
	 *	\param	y Y co-ordinate of the anchor point.
	 *	\param	str Text string that must be rendered.
	 *	\param	eAnchor Type of anchor point specified.
	 */
	void App::RenderFont(FTGLfont* pfont, float x, float y, const char* str, enumTextAnchor eAnchor)
	{
		static float fBox[6];
		static float value = 0.0;
		
		float ht = ftglGetFontLineHeight(pfont);
		float desc = ftglGetFontDescender(pfont);
				
		ftglGetFontBBox( pfont, str, -1, fBox);	
				
		glPushMatrix();
			
		switch(eAnchor)
		{
			case RIGHT_BOTTOM:
				glTranslatef(x-fBox[3], m_Height-y-desc, 0.0);
				break;
				
			case LEFT_BOTTOM:
				glTranslatef(x-fBox[0], m_Height-y-desc, 0.0);
				break;
							
			case RIGHT_TOP:
				glTranslatef(x-fBox[3], m_Height-y-ht-desc, 0.0);
				break;
				
			case LEFT_TOP:
			default :
				glTranslatef(x-fBox[0], m_Height-y-ht-desc, 0.0);
				break;
		}		
		
		ftglRenderFont(pfont, str, RENDER_ALL);
		glPopMatrix();
	}
	
	/*!
	 *	\brief	Disables 2D font rendering in OpenGL. It must not be mixed with the 2D geometry routines.
	 */	
	void App::End_Font2D()
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glEnable(GL_DEPTH_TEST );	
	}			
};
