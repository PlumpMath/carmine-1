/** \file 		carmine_defs.c
 *  \author  	Anup Jayapal Rao
 *  \date		25 Feb 2009
 * 
 * Definitions for the carmine core functions.
 * 
 * This file lists the definitions for the carmine core  functions. 
 */

#include "carmine_addons.h"
#include "carmine_defs.h"

/*!
 *	\brief Positions the camera used for rendering the objects in the scene. Parented and non-parented
 * 		   camera setups can be used, currently however only non parented cameras are known to work well.
 *	\param pCamera Pointer to camera that must be used for the view while rendering.
 *	\param pParentScene	Pointer to the scene object in which the camera and its parents
 *                      exist.
 */
void positionCamera(const fCamera* pCamera, fScene* pParentScene)
{
	int i,j,k;
	float arrfMat[16];	
	
	int* parrParentIndices = pCamera->m_parrParentIndices;
	
	float fRotX = pCamera->fRotX;
	float fRotY = pCamera->fRotY;
	float fRotZ = pCamera->fRotZ;	
	
	float fLocX = pCamera->fLocX;
	float fLocY = pCamera->fLocY;
	float fLocZ = pCamera->fLocZ;
	
	float fScaleX=1.0;
	float fScaleY=1.0;
	float fScaleZ=1.0;
	
	glRotatef(pCamera->fRotX, -1.0, 0.0, 0.0);
	glRotatef(pCamera->fRotY, 0.0, -1.0, 0.0);			
	glRotatef(pCamera->fRotZ, 0.0, 0.0, -1.0);
	
	if(parrParentIndices)
	{	
		fObject3D**  parrpObjects = pParentScene->m_parrpObjects;		
		fObject3D*	 pParentObj = NULL;
		int nParentIndex = *parrParentIndices;	
		
		while(nParentIndex >= 0)
		{
			pParentObj = parrpObjects[nParentIndex];
			
			fScaleX = 1.0/pParentObj->fScaleX;
			fScaleY = 1.0/pParentObj->fScaleY;
			fScaleZ = 1.0/pParentObj->fScaleZ;	
			
			glScalef(fScaleX,fScaleY,fScaleZ);

			glTranslatef(-fLocX, -fLocY, -fLocZ);
			
			fRotX = pParentObj->fRotX;
			fRotY = pParentObj->fRotY;
			fRotZ = pParentObj->fRotZ;
			
			glRotatef(fRotX, -1.0, 0.0, 0.0);
			glRotatef(fRotY, 0.0, -1.0, 0.0);			
			glRotatef(fRotZ, 0.0, 0.0, -1.0);			
			
			fLocX = pParentObj->fLocX;
			fLocY = pParentObj->fLocY;
			fLocZ = pParentObj->fLocZ;	
			
			parrParentIndices++;
			nParentIndex = *parrParentIndices;						
		}
	}	
	
	glTranslatef(-fLocX, -fLocY, -fLocZ);
}

/*!
 *	\brief Renders the buffer objects associated with the provided meshtable structure and the texture.
 *	\param pMeshTable 	Pointer to a Meshtable structure that contains the list of vertices,normals and texture.
 *	\param pTextureId	Pointer to a texture ID that must be while rendering the texture for this mesh.
 */
void renderBO(fMeshTable* pMeshTable, const GLuint* pTextureId)
{
	static int bHasNormals;
	
	bHasNormals = pMeshTable->bHasNormals;
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	if(bHasNormals)
	{
		glEnableClientState(GL_NORMAL_ARRAY);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, pMeshTable->m_idVBO);			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pMeshTable->m_idIBO);
	
	glVertexPointer(3, GL_FLOAT, SIZE_OBJ3DVERTEX, (const GLvoid*) OFFSET_FMESHTABLE_VERTICES);	
	glTexCoordPointer(2, GL_FLOAT, SIZE_OBJ3DVERTEX, (const GLvoid*) OFFSET_FMESHTABLE_UVS);
	if(bHasNormals)
	{
		glNormalPointer(GL_FLOAT, SIZE_OBJ3DVERTEX, (const GLvoid*) OFFSET_FMESHTABLE_NORMALS);	
	}
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, *pTextureId );
	
		glDrawElements(GL_QUADS, pMeshTable->nSizeQuadIndices, GL_UNSIGNED_INT, (const GLvoid*) pMeshTable->nOffsetQuadIndices);

		glDrawElements(GL_TRIANGLES, pMeshTable->nSizeTriIndices, GL_UNSIGNED_INT, (const GLvoid*) pMeshTable->nOffsetTriIndices);
	
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisable(GL_TEXTURE_2D);				
			
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	if(bHasNormals)
	{
		glDisableClientState(GL_NORMAL_ARRAY);
	}	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);		
	glDisableClientState(GL_VERTEX_ARRAY);	
}

/*!
 *	\brief Renders the provided 3D object and all descendents or child objects.
 *	\param pObj Pointer to the 3D object that must be rendered.
 *	\param parrpObjects	Pointer to the scene object array used to refer and render the child objects.
 */
void renderObject3D(fObject3D* pObj, fObject3D** parrpObjects)
{
	glPushMatrix();

		glTranslatef(pObj->fLocX, pObj->fLocY, pObj->fLocZ);
		
		glRotatef(pObj->fRotX, 1.0, 0.0, 0.0);
		glRotatef(pObj->fRotY, 0.0, 1.0, 0.0);
		glRotatef(pObj->fRotZ, 0.0, 0.0, 1.0);
	
		glScalef(pObj->fScaleX,pObj->fScaleY,pObj->fScaleZ);						
	
		if(NULL != pObj->m_pMeshTable)
		{		
			renderBO(pObj->m_pMeshTable, pObj->m_pTextureId);
		}
		
		{
			int* parrChildIndices = pObj->m_parrChildIndices;
			int nChildIndex = *parrChildIndices;
			fObject3D*	 pChildObj = NULL;
			while(nChildIndex >= 0)
			{
				pChildObj = parrpObjects[nChildIndex];
				renderObject3D(pChildObj, parrpObjects);
				parrChildIndices++;
				nChildIndex = *parrChildIndices;			
			}
		}
		
	glPopMatrix();
}

/*!
 *	\brief Renders the provided scene and the contained root objects. Child objects are rendered by their respective parents.
 *	\param pScene Pointer to the scene that must be rendered.
 */
void renderParent(fScene* pScene)
{	
	int nRootIndex = -1;
	
	fTextureEntry* 	parrTextureEntry = pScene->m_parrTextureEntry;
	fObject3D**  parrpObjects = pScene->m_parrpObjects;
	int* parrRootIndices = pScene->m_parrRootIndices;
	
	if( parrpObjects && parrTextureEntry && parrRootIndices)
	{
		fObject3D*	 pObj = NULL;
		nRootIndex = *parrRootIndices;
		while( nRootIndex >= 0)
		{
			pObj = parrpObjects[nRootIndex];

			renderObject3D(pObj, parrpObjects);
			
			parrRootIndices++;
			nRootIndex = *parrRootIndices;
		}
	}		
}

/*!
 *	\brief Creates the buffer object for the meshtable provided. A vertex buffer object and an index buffer are created
 * 		   with an vertices, texture coordinates and normals (optional). 
 *	\param pMeshTable 	Pointer to a Meshtable structure whose buffer objects must be created.
 */
void createBO(fMeshTable* pMeshTable)
{
	int nBufferSize;
	int nDataSize;
	GLenum target;
	
	if(0 != pMeshTable->m_idVBO)
	{
		/*
		printf("0 != pMeshTable->m_idVBO\n");
		*/
		return;
	}
	
	printf("Creating VBO for %s\n",pMeshTable->m_pName);
	pMeshTable->m_idVBO = 0;
	nDataSize = pMeshTable->nVBODataSize;
	target = GL_ARRAY_BUFFER;
	glGenBuffers( 1, &pMeshTable->m_idVBO);
	glBindBuffer( target, pMeshTable->m_idVBO);
	glBufferData( target, nDataSize, pMeshTable->m_pVertex, GL_STATIC_DRAW);
	nBufferSize = 0;
	glGetBufferParameteriv(target,GL_BUFFER_SIZE,&nBufferSize);
	if(nDataSize != nBufferSize)
	{
		glDeleteBuffers(1, &pMeshTable->m_idVBO);
		pMeshTable->m_idVBO = 0;
		printf("VBO creation failed for %s\n",pMeshTable->m_pName);
		exit(-1);
	}
	glBindBuffer( target, 0);
	
	if(0 != pMeshTable->m_idIBO)
	{
		/*
		printf("0 != pMeshTable->m_idIBO\n");
		*/
		return;
	}	
	
	printf("Creating IBO for %s\n",pMeshTable->m_pName);
	pMeshTable->m_idIBO = 0;
	nDataSize = pMeshTable->nIBODataSize; 
	target = GL_ARRAY_BUFFER;
	glGenBuffers( 1, &pMeshTable->m_idIBO);
	glBindBuffer( target, pMeshTable->m_idIBO);
	glBufferData( target, nDataSize, pMeshTable->m_pIndices, GL_STATIC_DRAW);
	nBufferSize = 0;
	glGetBufferParameteriv(target,GL_BUFFER_SIZE,&nBufferSize);
	if(nDataSize != nBufferSize)
	{
		glDeleteBuffers(1, &pMeshTable->m_idIBO);
		pMeshTable->m_idIBO = 0;
		printf("IBO creation failed for %s\n",pMeshTable->m_pName);
		exit(-1);
	}
	glBindBuffer( target, 0);	
}

/*!
 *	\brief Deletes the buffer object for the meshtable provided. The vertex buffer object and the related index buffer are 
 * 	       deleted. 
 *	\param pMeshTable 	Pointer to a Meshtable structure whose buffer objects must be deleted.
 */
void deleteBO(fMeshTable* pMeshTable)
{	
	if(0 != pMeshTable->m_idIBO)
	{
		printf("Deleting IBO for %s\n",pMeshTable->m_pName);
		glDeleteBuffers(1, &pMeshTable->m_idIBO);
		pMeshTable->m_idIBO = 0;	
	}
			
	if(0 != pMeshTable->m_idVBO)
	{
		printf("Deleting VBO for %s\n",pMeshTable->m_pName);		
		glDeleteBuffers(1, &pMeshTable->m_idVBO);
		pMeshTable->m_idVBO = 0;	
	}	
}

/*!
 *	\brief Creates the specified 3D object with the necessary textures specified in the provided texture entry array. The child
 * 		   objects are referred from the scene's object array which must also be provided. The texture for the object is also 
 * 		   loaded here if not previously loaded.
 *	\param pObj Pointer to the 3D object that must be created.
 *	\param parrTextureEntry	Pointer to array of textury entry objects used in the parent scene
 *	\param parrpObjects	Pointer to the scene object array used to refer and create the child objects.
 */
void createObject3D(fObject3D* pObj, fTextureEntry* parrTextureEntry, fObject3D**  parrpObjects)
{	
	if(NULL != pObj->m_pMeshTable)
	{
		int nTextureIndex = pObj->m_nTextureIndex;
		fTextureEntry* pTextureEntry = &parrTextureEntry[nTextureIndex];
		
		if( 0 == pTextureEntry->m_idTexture )
		{
			pTextureEntry->m_idTexture =  loadTexture(pTextureEntry->m_pTexturePath,0,0);
			printf("Loading texture: %s with ID as %d\n", pTextureEntry->m_pTexturePath, pTextureEntry->m_idTexture);
		}
		
		pObj->m_pTextureId = &pTextureEntry->m_idTexture;		
		
		createBO(pObj->m_pMeshTable);
	}
	
	{
		fObject3D*	 pChildObj = NULL;
		int* parrChildIndices = pObj->m_parrChildIndices;
		int nChildIndex = *parrChildIndices;
		while(nChildIndex >= 0)
		{
			pChildObj = parrpObjects[nChildIndex];
			createObject3D(pChildObj, parrTextureEntry, parrpObjects);
			parrChildIndices++;
			nChildIndex = *parrChildIndices;			
		}
	}
}

/*!
 *	\brief Deleted the specified 3D object with the necessary textures specified in the provided texture entry array. The child
 * 		   objects are referred from the scene's object array which must also be provided. The texture for the object is also 
 * 		   deleted here if not previously deleted.
 *	\param pObj Pointer to the 3D object that must be deleted.
 *	\param parrTextureEntry	Pointer to array of textury entry objects used in the parent scene
 *	\param parrpObjects	Pointer to the scene object array used to refer and delete the child objects.
 */
void deleteObject3D(fObject3D* pObj, fTextureEntry* parrTextureEntry, fObject3D**  parrpObjects)
{
	{
		fObject3D*	 pChildObj = NULL;
		int* parrChildIndices = pObj->m_parrChildIndices;
		int nChildIndex = *parrChildIndices;
		while(nChildIndex >= 0)
		{
			pChildObj = parrpObjects[nChildIndex];
			deleteObject3D(pChildObj, parrTextureEntry, parrpObjects);
			parrChildIndices++;
			nChildIndex = *parrChildIndices;			
		}
	}
		
	if(NULL != pObj->m_pMeshTable)
	{
		deleteBO(pObj->m_pMeshTable);
		if(pObj->m_pTextureId)
		{
			fTextureEntry* pTextureEntry = &parrTextureEntry[pObj->m_nTextureIndex];
			GLuint TextureId = *pObj->m_pTextureId;
			if(TextureId)
			{
				printf("Unloading texture: %s with ID %d\n", pTextureEntry->m_pTexturePath, TextureId);
				glDeleteTextures(1, &pTextureEntry->m_idTexture);
				pTextureEntry->m_idTexture = 0;
			}
			pObj->m_pTextureId = NULL;
		}
	}	
}

/*!
 *	\brief Creates the scene that is specified with the contained objects.
 *	\param pScene Pointer to the scene that must be created.
 */
void createParent(fScene* pScene)
{	
	int nRootIndex = -1;
	
	fTextureEntry* 	parrTextureEntry = pScene->m_parrTextureEntry;
	fObject3D**  parrpObjects = pScene->m_parrpObjects;
	int* parrRootIndices = pScene->m_parrRootIndices;
	
	if( parrpObjects && parrTextureEntry && parrRootIndices)
	{
		fObject3D*	 pObj = NULL;
		nRootIndex = *parrRootIndices;
		while( nRootIndex >= 0)
		{
			pObj = parrpObjects[nRootIndex];
			
			createObject3D(pObj, parrTextureEntry, parrpObjects);
			
			parrRootIndices++;
			nRootIndex = *parrRootIndices;
		}
	}		
}

/*!
 *	\brief Deletes the scene that is specified with the contained objects.
 *	\param pScene Pointer to the scene that must be deleted.
 */
void deleteParent(fScene* pScene)
{
	int nRootIndex = -1;
	
	fTextureEntry* 	parrTextureEntry = pScene->m_parrTextureEntry;
	fObject3D**  parrpObjects = pScene->m_parrpObjects;
	int* parrRootIndices = pScene->m_parrRootIndices;
	
	if( parrpObjects && parrTextureEntry && parrRootIndices)
	{
		fObject3D*	 pObj = NULL;
		nRootIndex = *parrRootIndices;
		while( nRootIndex >= 0)
		{
			pObj = parrpObjects[nRootIndex];
			
			deleteObject3D(pObj, parrTextureEntry, parrpObjects);
			
			parrRootIndices++;
			nRootIndex = *parrRootIndices;
		}
	}	
}

/*!
 *	\brief Creates the light setup that is specified in the provided scene object.
 *	\param pScene Pointer to the scene in which the intended light setup exists.
 */
void createLights(fScene* pScene)
{	
	int nIndex = 0;
	fLamp**  parrpLamps = pScene->m_parrpLamps;
	
	if( parrpLamps )
	{
		GLenum eLightIndex;
		fLamp*	 pLamp = parrpLamps[nIndex];
		while(pLamp && (nIndex<GL_MAX_LIGHTS) )
		{			
			eLightIndex = GL_LIGHT1 + nIndex;
			
			glLightfv(eLightIndex, GL_AMBIENT, pLamp->LightAmbient);
			glLightfv(eLightIndex, GL_DIFFUSE, pLamp->LightDiffuse);	
			glLightfv(eLightIndex, GL_POSITION, pLamp->fLoc);
			glEnable(eLightIndex);
			
			nIndex++;
			pLamp = parrpLamps[nIndex];
		}
	}		
}
