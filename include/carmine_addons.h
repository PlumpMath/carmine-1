/** \file 		carmine_addons.h
 *  \author  	Anup Jayapal Rao
 *  \date		25 Feb 2009
 * 
 * Additional helper functions commonly used in an OpenGL program.
 * 
 * This file lists helper functions commonly used in OpenGL programs. Currently it supports function to load a texture 
 * in a specified orientation. Similar functions to facilitate OpenGL programs must be added here. 
 * 
 */
#ifndef _CARMINE_ADDONS
#define _CARMINE_ADDONS

#include "carmine_opengl.h"

#include <FreeImage.h>

/// Function to load a texture whose path has been specified and orientation flipped as specified
GLuint loadTexture(const char* pathImagefile, int bVertFlip, int bHorzFlip);

#endif /* _CARMINE_ADDONS */
