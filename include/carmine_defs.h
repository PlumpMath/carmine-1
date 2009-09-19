/** \file 		carmine_defs.h
 *  \author  	Anup Jayapal Rao
 *  \date		25 Feb 2009
 * 
 * Definitions of constants and structure declarations.
 * 
 * The carmine exporter script exports the contents of the Blender scene in a specific format as C structures and defines.
 * These definitions of constants and structure declarations are described in this file.
 */
#ifndef _CARMINE_DEFS
#define _CARMINE_DEFS

#include "carmine_opengl.h"
#include "carmine_addons.h"

/// Colour of the CARMINE Red in HEX
#define CARMINE_COLOUR_HEX	960018H

/// Value of Red in CARMINE Red in decimal
#define CARMINE_R 150

/// Value of Green in CARMINE Red in decimal
#define CARMINE_G 0

/// Value of Blue in CARMINE Red in decimal
#define CARMINE_B 24

/// Structure used to contain vertice information
typedef struct 
{
	/// X co-ordinate.
	float x;
	
	/// Y co-ordinate.
	float y;
	
	/// Z co-ordinate.
	float z;
	
}fVertex;

/// Structure used to contain texture coordinate information
typedef struct 
{
	/// U co-ordinate.
	float u;
	
	/// V co-ordinate.
	float v;
	
}fTexUV;

/// Structure used to contain vertice normal information
typedef struct 
{
	/// X co-ordinate.
	float x;
	
	/// Y co-ordinate.
	float y;
	
	/// Z co-ordinate.
	float z;
	
}fNormal;	

/// Structure used to contain vertex array information for a 3D object
typedef struct 
{
	/// Vertice data.
	fVertex			m_Vertices;
	
	/// Texture data.
	fTexUV			m_fTexUVs;
	
	/// Normal data.
	fVertex			m_Normals;
	
}fObj3DVertex;		

/// Structure used to contain vertice information for a mesh
typedef struct 
{
	/// Name of the mesh.
	const char*				m_pName;
	
	/// Pointer to the vertex array.
	fObj3DVertex*			m_pVertex;
	
	/// Pointer to the index array.
	GLuint*					m_pIndices;
	
	/// Size of the vertex buffer data.
	int 					nVBODataSize;
	
	/// Size of the index buffer data.
	int 					nIBODataSize;
	
	/// Number of Quad indices
	GLuint					nSizeQuadIndices;
	
	/// Number of Triangle indices
	GLuint					nSizeTriIndices;
	
	/// Offset at which Quad Indicies occur in the vertex array
	GLuint					nOffsetQuadIndices;
	
	/// Offset at which Tri Indicies occur in the vertex array
	GLuint					nOffsetTriIndices;	
	
	/// Id for the vertex buffer object
	GLuint 					m_idVBO;
	
	/// Id for the index buffer object
	GLuint 					m_idIBO;	
	
	/// Boolean to indicate that vertex data has 'normals' in it
	int						bHasNormals;	
			
}fMeshTable;

/// Structure used to contain information for a 3D object
typedef struct 
{
	/// Name of the 3D object.
	const char*				m_pName;
	
	/// Pointer to the mesh table.
	fMeshTable*				m_pMeshTable;
	
	/// Index of the texture in the array of scene textures.
	int						m_nTextureIndex;	
		
	/// Pointer to the ID assigned to the texture.
	const GLuint*			m_pTextureId;
			
	/// X co-ordinate of location of the object relative to parent.
	GLfloat					fLocX;
	
	/// Y co-ordinate of location of the object relative to parent.
	GLfloat					fLocY;
	
	/// Z co-ordinate of location of the object relative to parent.
	GLfloat					fLocZ;
	
	/// X axis rotation of the object relative to parent.
	GLfloat					fRotX;		
	
	/// Y axis rotation of the object relative to parent.
	GLfloat					fRotY;		
	
	/// Z axis rotation of the object relative to parent.
	GLfloat					fRotZ;				
	
	/// X axis scale of the object relative to parent. 
	GLfloat					fScaleX;
	
	/// Y axis scale of the object relative to parent.
	GLfloat					fScaleY;
	
	/// Z axis scale of the object relative to parent.
	GLfloat					fScaleZ;
	
	/// Pointer to array of indices listing the child objects. 
	int*					m_parrChildIndices;	
				
}fObject3D;

/// Structure used to contain camera parameters
typedef struct 
{
	/// Name of the camera.
	const char*				m_pName;
		
	/// X co-ordinate of location of the camera relative to parent.
	GLfloat					fLocX;
	
	/// Y co-ordinate of location of the camera relative to parent.
	GLfloat					fLocY;
	
	/// Z co-ordinate of location of the camera relative to parent.
	GLfloat					fLocZ;
	
	/// X axis rotation of the camera relative to parent.
	GLfloat					fRotX;		
	
	/// Y axis rotation of the camera relative to parent.
	GLfloat					fRotY;		
	
	/// Z axis rotation of the camera relative to parent.
	GLfloat					fRotZ;				
	
	/// X axis scale of the camera relative to parent. 
	GLfloat					fScaleX;
	
	/// Y axis scale of the camera relative to parent.
	GLfloat					fScaleY;
	
	/// Z axis scale of the camera relative to parent.
	GLfloat					fScaleZ;
	
	/// Start of camera clipping distance.
	GLfloat					fClipStart;
	
	/// End of camera clipping distance.
	GLfloat					fClipEnd;
	
	/// Camera lens parameter.
	GLfloat					fLens;
	
	/// Pointer to array of indices listing the parent objects. 
	int*					m_parrParentIndices;	/* From topmost to lowermost (eldest to younger ... hehehe) */
	
}fCamera;	

/// Structure used to contain texture information
typedef struct 
{
	/// Path of the texture image
	const char*				m_pTexturePath;
	
	/// ID assigned to the texture.
	GLuint 					m_idTexture;
	
}fTextureEntry;

/// Structure used to contain lamp parameters
typedef struct 
{
	/// Name of the lamp.
	const char*				m_pName;
	
	/// Location of the lamp relative to scene. The fourth and last member must always be 1.0.
	GLfloat					fLoc[4];
	
	/// X axis rotation of the lamp relative to scene.
	GLfloat					fRotX;		
	
	/// Y axis rotation of the lamp relative to scene.
	GLfloat					fRotY;		
	
	/// Z axis rotation of the lamp relative to scene.
	GLfloat					fRotZ;				
	
	/// X axis scale of the lamp relative to scene. 
	GLfloat					fScaleX;
	
	/// Y axis scale of the lamp relative to scene.
	GLfloat					fScaleY;
	
	/// Z axis scale of the lamp relative to scene.
	GLfloat					fScaleZ;		
	
	/// Ambient light parameters. The fourth and last member must always be 1.0.
	GLfloat					LightAmbient[4];
	
	/// Diffuse light parameters. The fourth and last member must always be 1.0.
	GLfloat 				LightDiffuse[4];
	
}fLamp;

/// Structure used to contain scene information
typedef struct 
{
	/// Pointer to array of texture entry objects describing the textures used in the scene.
	fTextureEntry* 			m_parrTextureEntry;
	
	/// Pointer to array of pointers to objects in the scene.
	fObject3D**				m_parrpObjects;
	
	/// Pointer to the array of integers containing the indices of the root objects in the scene. Root objects
	/// are usually those that lack a parent object. 
	int*					m_parrRootIndices;	/* Index of the highest objects in hierarchy */
												
	/// Pointer to array of pointers to cameras in the scene.
	fCamera**				m_parrpCameras;
	
	/// Pointer to array of pointers to lamps in the scene.
	fLamp**					m_parrpLamps;
	
}fScene;

/// Offset of the vertices in the meshtable
#define		OFFSET_FMESHTABLE_VERTICES	0

/// Offset of the texture co-ordinates in the meshtable
#define		OFFSET_FMESHTABLE_UVS		(OFFSET_FMESHTABLE_VERTICES+sizeof(fVertex))

/// Offset of the normals in the meshtable
#define		OFFSET_FMESHTABLE_NORMALS	(OFFSET_FMESHTABLE_UVS+sizeof(fTexUV))

/// Size of the object 3D vertex information
#define		SIZE_OBJ3DVERTEX	(sizeof(fObj3DVertex))

/// Size of the indices used to describe a quadrilateral
#define		SIZE_QUAD_INDEX		(sizeof(GLuint)*4)

/// Size of the indices used to describe a triangle
#define		SIZE_TRI_INDEX		(sizeof(GLuint)*3)

void createParent(fScene* pScene);
void renderParent(fScene* pScene);
void deleteParent(fScene* pScene);

void createObject3D(fObject3D* pObj, fTextureEntry* parrTextureEntry, fObject3D**  parrpObjects);
void renderObject3D(fObject3D* pObj, fObject3D**  parrpObjects);
void deleteObject3D(fObject3D* pObj, fTextureEntry* parrTextureEntry, fObject3D**  parrpObjects);

void createBO(fMeshTable* m_pMeshTable);
void renderBO(fMeshTable* m_pMeshTable, const GLuint* pTextureId);
void deleteBO(fMeshTable* m_pMeshTable);

void positionCamera(const fCamera* pCamera, fScene* pParentScene);
void createLights(fScene* pScene);

#endif /* _CARMINE_DEFS */
