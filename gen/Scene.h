#include "carmine_defs.h"

#define		NUM_Cube_VERTICES	14
#define		NUM_Cube_POINTS		(NUM_Cube_VERTICES*3)
#define		SIZE_Cube_VERTICES	(NUM_Cube_POINTS*SIZE_OBJ3DVERTEX)

#define		NUM_Cube_QUAD_INDICES	6
#define		NUM_Cube_TRI_INDICES	0
#define		NUM_Cube_INDICES		(NUM_Cube_QUAD_INDICES*4+NUM_Cube_TRI_INDICES*3)

#define		OFFSET_Cube_QUADS	0
#define		COUNT_Cube_QUADS	(NUM_Cube_QUAD_INDICES*4)
#define		SIZE_Cube_QUADS		(NUM_Cube_QUAD_INDICES*SIZE_QUAD_INDEX)

#define		OFFSET_Cube_TRIADS	SIZE_Cube_QUADS
#define		COUNT_Cube_TRIADS	(NUM_Cube_TRI_INDICES*3)   
#define		SIZE_Cube_TRIADS	(NUM_Cube_TRI_INDICES*SIZE_TRI_INDEX)

#define		SIZE_Cube_INDICES	(OFFSET_Cube_TRIADS+SIZE_Cube_TRIADS)
	
#define		NUM_mRCap_VERTICES	54
#define		NUM_mRCap_POINTS		(NUM_mRCap_VERTICES*3)
#define		SIZE_mRCap_VERTICES	(NUM_mRCap_POINTS*SIZE_OBJ3DVERTEX)

#define		NUM_mRCap_QUAD_INDICES	20
#define		NUM_mRCap_TRI_INDICES	28
#define		NUM_mRCap_INDICES		(NUM_mRCap_QUAD_INDICES*4+NUM_mRCap_TRI_INDICES*3)

#define		OFFSET_mRCap_QUADS	0
#define		COUNT_mRCap_QUADS	(NUM_mRCap_QUAD_INDICES*4)
#define		SIZE_mRCap_QUADS		(NUM_mRCap_QUAD_INDICES*SIZE_QUAD_INDEX)

#define		OFFSET_mRCap_TRIADS	SIZE_mRCap_QUADS
#define		COUNT_mRCap_TRIADS	(NUM_mRCap_TRI_INDICES*3)   
#define		SIZE_mRCap_TRIADS	(NUM_mRCap_TRI_INDICES*SIZE_TRI_INDEX)

#define		SIZE_mRCap_INDICES	(OFFSET_mRCap_TRIADS+SIZE_mRCap_TRIADS)
	
#define		NUM_Plane_VERTICES	4
#define		NUM_Plane_POINTS		(NUM_Plane_VERTICES*3)
#define		SIZE_Plane_VERTICES	(NUM_Plane_POINTS*SIZE_OBJ3DVERTEX)

#define		NUM_Plane_QUAD_INDICES	1
#define		NUM_Plane_TRI_INDICES	0
#define		NUM_Plane_INDICES		(NUM_Plane_QUAD_INDICES*4+NUM_Plane_TRI_INDICES*3)

#define		OFFSET_Plane_QUADS	0
#define		COUNT_Plane_QUADS	(NUM_Plane_QUAD_INDICES*4)
#define		SIZE_Plane_QUADS		(NUM_Plane_QUAD_INDICES*SIZE_QUAD_INDEX)

#define		OFFSET_Plane_TRIADS	SIZE_Plane_QUADS
#define		COUNT_Plane_TRIADS	(NUM_Plane_TRI_INDICES*3)   
#define		SIZE_Plane_TRIADS	(NUM_Plane_TRI_INDICES*SIZE_TRI_INDEX)

#define		SIZE_Plane_INDICES	(OFFSET_Plane_TRIADS+SIZE_Plane_TRIADS)
	
#define		NUM_mR_wheel_VERTICES	76
#define		NUM_mR_wheel_POINTS		(NUM_mR_wheel_VERTICES*3)
#define		SIZE_mR_wheel_VERTICES	(NUM_mR_wheel_POINTS*SIZE_OBJ3DVERTEX)

#define		NUM_mR_wheel_QUAD_INDICES	18
#define		NUM_mR_wheel_TRI_INDICES	36
#define		NUM_mR_wheel_INDICES		(NUM_mR_wheel_QUAD_INDICES*4+NUM_mR_wheel_TRI_INDICES*3)

#define		OFFSET_mR_wheel_QUADS	0
#define		COUNT_mR_wheel_QUADS	(NUM_mR_wheel_QUAD_INDICES*4)
#define		SIZE_mR_wheel_QUADS		(NUM_mR_wheel_QUAD_INDICES*SIZE_QUAD_INDEX)

#define		OFFSET_mR_wheel_TRIADS	SIZE_mR_wheel_QUADS
#define		COUNT_mR_wheel_TRIADS	(NUM_mR_wheel_TRI_INDICES*3)   
#define		SIZE_mR_wheel_TRIADS	(NUM_mR_wheel_TRI_INDICES*SIZE_TRI_INDEX)

#define		SIZE_mR_wheel_INDICES	(OFFSET_mR_wheel_TRIADS+SIZE_mR_wheel_TRIADS)
	
#define		NUM_mBody_VERTICES	248
#define		NUM_mBody_POINTS		(NUM_mBody_VERTICES*3)
#define		SIZE_mBody_VERTICES	(NUM_mBody_POINTS*SIZE_OBJ3DVERTEX)

#define		NUM_mBody_QUAD_INDICES	92
#define		NUM_mBody_TRI_INDICES	28
#define		NUM_mBody_INDICES		(NUM_mBody_QUAD_INDICES*4+NUM_mBody_TRI_INDICES*3)

#define		OFFSET_mBody_QUADS	0
#define		COUNT_mBody_QUADS	(NUM_mBody_QUAD_INDICES*4)
#define		SIZE_mBody_QUADS		(NUM_mBody_QUAD_INDICES*SIZE_QUAD_INDEX)

#define		OFFSET_mBody_TRIADS	SIZE_mBody_QUADS
#define		COUNT_mBody_TRIADS	(NUM_mBody_TRI_INDICES*3)   
#define		SIZE_mBody_TRIADS	(NUM_mBody_TRI_INDICES*SIZE_TRI_INDEX)

#define		SIZE_mBody_INDICES	(OFFSET_mBody_TRIADS+SIZE_mBody_TRIADS)
	
#define		NUM_mL_wheel_VERTICES	76
#define		NUM_mL_wheel_POINTS		(NUM_mL_wheel_VERTICES*3)
#define		SIZE_mL_wheel_VERTICES	(NUM_mL_wheel_POINTS*SIZE_OBJ3DVERTEX)

#define		NUM_mL_wheel_QUAD_INDICES	18
#define		NUM_mL_wheel_TRI_INDICES	36
#define		NUM_mL_wheel_INDICES		(NUM_mL_wheel_QUAD_INDICES*4+NUM_mL_wheel_TRI_INDICES*3)

#define		OFFSET_mL_wheel_QUADS	0
#define		COUNT_mL_wheel_QUADS	(NUM_mL_wheel_QUAD_INDICES*4)
#define		SIZE_mL_wheel_QUADS		(NUM_mL_wheel_QUAD_INDICES*SIZE_QUAD_INDEX)

#define		OFFSET_mL_wheel_TRIADS	SIZE_mL_wheel_QUADS
#define		COUNT_mL_wheel_TRIADS	(NUM_mL_wheel_TRI_INDICES*3)   
#define		SIZE_mL_wheel_TRIADS	(NUM_mL_wheel_TRI_INDICES*SIZE_TRI_INDEX)

#define		SIZE_mL_wheel_INDICES	(OFFSET_mL_wheel_TRIADS+SIZE_mL_wheel_TRIADS)
	
#define		NUM_mFloor_VERTICES	25
#define		NUM_mFloor_POINTS		(NUM_mFloor_VERTICES*3)
#define		SIZE_mFloor_VERTICES	(NUM_mFloor_POINTS*SIZE_OBJ3DVERTEX)

#define		NUM_mFloor_QUAD_INDICES	7
#define		NUM_mFloor_TRI_INDICES	11
#define		NUM_mFloor_INDICES		(NUM_mFloor_QUAD_INDICES*4+NUM_mFloor_TRI_INDICES*3)

#define		OFFSET_mFloor_QUADS	0
#define		COUNT_mFloor_QUADS	(NUM_mFloor_QUAD_INDICES*4)
#define		SIZE_mFloor_QUADS		(NUM_mFloor_QUAD_INDICES*SIZE_QUAD_INDEX)

#define		OFFSET_mFloor_TRIADS	SIZE_mFloor_QUADS
#define		COUNT_mFloor_TRIADS	(NUM_mFloor_TRI_INDICES*3)   
#define		SIZE_mFloor_TRIADS	(NUM_mFloor_TRI_INDICES*SIZE_TRI_INDEX)

#define		SIZE_mFloor_INDICES	(OFFSET_mFloor_TRIADS+SIZE_mFloor_TRIADS)
	
#define		NUM_Plane__001_VERTICES	4
#define		NUM_Plane__001_POINTS		(NUM_Plane__001_VERTICES*3)
#define		SIZE_Plane__001_VERTICES	(NUM_Plane__001_POINTS*SIZE_OBJ3DVERTEX)

#define		NUM_Plane__001_QUAD_INDICES	1
#define		NUM_Plane__001_TRI_INDICES	0
#define		NUM_Plane__001_INDICES		(NUM_Plane__001_QUAD_INDICES*4+NUM_Plane__001_TRI_INDICES*3)

#define		OFFSET_Plane__001_QUADS	0
#define		COUNT_Plane__001_QUADS	(NUM_Plane__001_QUAD_INDICES*4)
#define		SIZE_Plane__001_QUADS		(NUM_Plane__001_QUAD_INDICES*SIZE_QUAD_INDEX)

#define		OFFSET_Plane__001_TRIADS	SIZE_Plane__001_QUADS
#define		COUNT_Plane__001_TRIADS	(NUM_Plane__001_TRI_INDICES*3)   
#define		SIZE_Plane__001_TRIADS	(NUM_Plane__001_TRI_INDICES*SIZE_TRI_INDEX)

#define		SIZE_Plane__001_INDICES	(OFFSET_Plane__001_TRIADS+SIZE_Plane__001_TRIADS)
	
#define		NUM_Plane__002_VERTICES	4
#define		NUM_Plane__002_POINTS		(NUM_Plane__002_VERTICES*3)
#define		SIZE_Plane__002_VERTICES	(NUM_Plane__002_POINTS*SIZE_OBJ3DVERTEX)

#define		NUM_Plane__002_QUAD_INDICES	1
#define		NUM_Plane__002_TRI_INDICES	0
#define		NUM_Plane__002_INDICES		(NUM_Plane__002_QUAD_INDICES*4+NUM_Plane__002_TRI_INDICES*3)

#define		OFFSET_Plane__002_QUADS	0
#define		COUNT_Plane__002_QUADS	(NUM_Plane__002_QUAD_INDICES*4)
#define		SIZE_Plane__002_QUADS		(NUM_Plane__002_QUAD_INDICES*SIZE_QUAD_INDEX)

#define		OFFSET_Plane__002_TRIADS	SIZE_Plane__002_QUADS
#define		COUNT_Plane__002_TRIADS	(NUM_Plane__002_TRI_INDICES*3)   
#define		SIZE_Plane__002_TRIADS	(NUM_Plane__002_TRI_INDICES*SIZE_TRI_INDEX)

#define		SIZE_Plane__002_INDICES	(OFFSET_Plane__002_TRIADS+SIZE_Plane__002_TRIADS)
	
// extern fObj3DVertex arrVertex_Cube[NUM_Cube_VERTICES];
// extern GLuint arrIndices_Cube[NUM_Cube_INDICES];
// extern fObj3DVertex arrVertex_mRCap[NUM_mRCap_VERTICES];
// extern GLuint arrIndices_mRCap[NUM_mRCap_INDICES];
// extern fObj3DVertex arrVertex_Plane[NUM_Plane_VERTICES];
// extern GLuint arrIndices_Plane[NUM_Plane_INDICES];
// extern fObj3DVertex arrVertex_mR_wheel[NUM_mR_wheel_VERTICES];
// extern GLuint arrIndices_mR_wheel[NUM_mR_wheel_INDICES];
// extern fObj3DVertex arrVertex_mBody[NUM_mBody_VERTICES];
// extern GLuint arrIndices_mBody[NUM_mBody_INDICES];
// extern fObj3DVertex arrVertex_mL_wheel[NUM_mL_wheel_VERTICES];
// extern GLuint arrIndices_mL_wheel[NUM_mL_wheel_INDICES];
// extern fObj3DVertex arrVertex_mFloor[NUM_mFloor_VERTICES];
// extern GLuint arrIndices_mFloor[NUM_mFloor_INDICES];
// extern fObj3DVertex arrVertex_Plane__001[NUM_Plane__001_VERTICES];
// extern GLuint arrIndices_Plane__001[NUM_Plane__001_INDICES];
// extern fObj3DVertex arrVertex_Plane__002[NUM_Plane__002_VERTICES];
// extern GLuint arrIndices_Plane__002[NUM_Plane__002_INDICES];
	
// extern fMeshTable oMeshTable_Cube;
// extern fMeshTable oMeshTable_mRCap;
// extern fMeshTable oMeshTable_Plane;
// extern fMeshTable oMeshTable_mR_wheel;
// extern fMeshTable oMeshTable_mBody;
// extern fMeshTable oMeshTable_mL_wheel;
// extern fMeshTable oMeshTable_mFloor;
// extern fMeshTable oMeshTable_Plane__001;
// extern fMeshTable oMeshTable_Plane__002;
	
// extern fCamera oCam4;
// extern fCamera oCam3;
// extern fCamera oCam2;
// extern fCamera oddcam;
// extern fCamera oCam1;
	
// extern int arrChildren_RR_wheel [];
// extern fObject3D oRR_wheel;
// extern int arrChildren_Body [];
// extern fObject3D oBody;
// extern int arrChildren_Cube [];
// extern fObject3D oCube;
// extern int arrChildren_Floor [];
// extern fObject3D oFloor;
// extern int arrChildren_RCap [];
// extern fObject3D oRCap;
// extern int arrChildren_CentreAnchor [];
// extern fObject3D oCentreAnchor;
// extern int arrChildren_Plane [];
// extern fObject3D oPlane;
// extern int arrChildren_FR_wheel [];
// extern fObject3D oFR_wheel;
// extern int arrChildren_RL_wheel [];
// extern fObject3D oRL_wheel;
// extern int arrChildren_Plane__005 [];
// extern fObject3D oPlane__005;
// extern int arrChildren_Plane__004 [];
// extern fObject3D oPlane__004;
// extern int arrChildren_FL_wheel [];
// extern fObject3D oFL_wheel;
// extern int arrChildren_Plane__001 [];
// extern fObject3D oPlane__001;
// extern int arrChildren_Plane__003 [];
// extern fObject3D oPlane__003;
// extern int arrChildren_Plane__002 [];
// extern fObject3D oPlane__002;
	
// extern fTextureEntry arrTextureEntry_Scene[];
// extern fObject3D* arrChildren_Scene [];
// extern int arrRootObjects_Scene [];
// extern fCamera* arrCameras_Scene [];
	
// extern fScene oScene;
	
