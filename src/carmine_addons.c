/** \file 		carmine_addons.c
 *  \author  	Anup Jayapal Rao
 *  \date		25 Feb 2009
 * 
 * Definitions for the additional helper functions.
 * 
 * This file lists the definitions for the additional helper functions. 
 * 
 * Based on code posted at 
 *		http://www.opengl.org/discussion_boards/ubbthreads.php?ubb=showflat&Number=237270
 */

#include "carmine_addons.h"

/*!
 *	\brief Opens the image file using the FreeImage library in the specified orientation
 * 		   and builds the 2D Texture MipMaps.
 *	\param pathImagefile Path to the image file.
 *	\param bVertFlip	1, if the image texture must be vertically flipped
 * 						0, otherwise
 *	\param bHorzFlip	1, if the image texture must be horizontally flipped
 * 						0, otherwise 
 *	\return Texture ID.
 */
GLuint loadTexture(const char* pathImagefile, int bVertFlip, int bHorzFlip)
{
	GLuint textureID;
	
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(pathImagefile,0);
	FIBITMAP* image = FreeImage_Load(format, pathImagefile,0);
	int bRGBA = FreeImage_IsTransparent(image);
	
	FIBITMAP* temp = image;
	if(bRGBA)
	{
		image = FreeImage_ConvertTo32Bits(temp);
	}
	else
	{
		image = FreeImage_ConvertTo24Bits(temp);
	}
	FreeImage_Unload(temp);	
	
	if(bVertFlip)
	{
		FreeImage_FlipVertical(image);
	}
	
	if(bHorzFlip)
	{
		FreeImage_FlipHorizontal(image);
	}	
	
	int w = FreeImage_GetWidth(image);
	int h = FreeImage_GetHeight(image);
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	//// turn off bilinear filtering
	//gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MIN_FILTER, gl.GL_NEAREST)
	//gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MAG_FILTER, gl.GL_NEAREST)	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	if(bRGBA)
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_BGRA, GL_UNSIGNED_BYTE, FreeImage_GetBits(image));
	}
	else
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_BGR, GL_UNSIGNED_BYTE, FreeImage_GetBits(image));	
	}

	FreeImage_Unload(image);
	
	return textureID;
}

