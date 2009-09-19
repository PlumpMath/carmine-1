#!BPY

# CarMine Exporter

## @package carmine
# 'carmine' is a python based exporter plugin for Blender3D.
#
# It exports the current Blender3D scene to C/C++ compatible code for use with OpenGL.
# It currently does not provide full fledged export and is limited simple scenes.
# It is intended for programmers who would like to incorporate 3D models in their
# OpenGL applications without adding additional 3D file support.

""" Registration info for Blender menus:
Name: 'carmine(.py)...'
Blender: 247
Group: 'Export'
ToolTip: 'Export to C code for Carmine'
"""

## Author(s) of the program
__author__ = "Anup Jayapal Rao"

## Key URLS related to this script
__url__ = ("blender", "blenderartists.org", "Author's site http://renegadepixels.in")

## Version of the script
__version__ = "0.1"

## Blenderscript documentation string
__bpydoc__ = """\
This script exports a cpp file which can be usd by the carmine addons for rendering in
a lean OpenGL application using vertex buffer objects.
"""

# carmine.py v 0.1 2009/01/29 Copyright 2009
# Author: Anup Jayapal Rao -- anup.kadam@renegadepixels.in
#
# (original python script template: Arben (Ben) Omari)
# GUI template from http://wiki.blender.org/index.php/Manual/Python_Scripting
#
# Provided under terms of LGPL V3
# http://www.gnu.org/copyleft/lesser.html
#
# Contains material referenced from 
# http://blenderartists.org/forum/showthread.php?t=117421
#
# Radians to Degress, and, Degrees to radian code obtained from VR Object script 
# by Mitch Hughes (AKA lobo_nz)

import os
import os.path
import types

import Blender
from Blender import Types

import bpy

import math
from Blender import Mathutils 

from Blender.BGL import *
from Blender.Draw import *

## Folder that is generated to write the C and H files in.
GEN_PATH = 'gen'

def rad2deg(v):
	"""
	Returns the degrees equivalent of the radians specified in v.
	"""
	return (v*180.0/math.pi)
	
def deg2rad(v):
	"""
	Returns the radians equivalent of the degrees specified in v.
	"""
	return (v*math.pi)/180.0;
	
def reduceNamesToCodeNames(str):
	"""
	Returns a 'C' code friendly name for Blender generated strings specified in str.
	A DOT or SPACE character is replaced by underscore(s).
	
	Returns a string.
	"""
	codeName = str.strip()
	codeName = codeName.replace(' ','_');
	codeName = codeName.replace('.','__');
	return codeName
				
class GLExport:
	"""
	Class to export the current Blender scene to C code.
	Only objects of the active layers are exported.
	
	A C file and a H file are generated in the 'gen' directory at the path from which 
	blender is run.
	"""
	def __init__(self, bNormal):
		"""
		Initializer.
		
		bNormal - Boolean to specify if the normals for every vertex must be exported.
		"""
		## @var bNormal
		# Boolean to indicate if normals must be included in exported data structures.
		self.bNormal = bNormal
		
		## @var currScene
		# Reference to the currently active scene.		
		self.currScene = bpy.data.scenes.active
		
		sceneName = reduceNamesToCodeNames(self.currScene.name)
		
		## @var srcCodeFileScene
		# The relative path of the generated C file.
		self.srcCodeFileScene = os.path.join(GEN_PATH,sceneName+'.c')
		
		## @var hdrFilename
		# The name of the generated H file.
		self.hdrFilename = sceneName+'.h'
		
		## @var hdrCodeFileScene
		# The relative path of the generated H file.
		self.hdrCodeFileScene = os.path.join(GEN_PATH,self.hdrFilename)
		
		## @var srcCodeFile
		# The variable used to hold the file object used to write the generated C file.		
		self.srcCodeFile = None
		
		## @var hdrCodeFile
		# The variable used to hold the file object used to write the generated H file.		
		self.hdrCodeFile = None
		
		## @var dictMeshNames
		# Dictionary object used to list the names of Blender3D meshes used.		
		self.dictMeshNames= {}
		
		## @var dictObject3DNames
		# Dictionary object used to list the names of the Blender3D objects used (including empty objects).		
		self.dictObject3DNames= {}
		
		## @var listCameraNames
		# List of names of the Blender3D camera used.
		self.listCameraNames= []
		
		## @var dictRootNames
		# Dictionary object used to list the names of the root objects in the scene.		
		self.dictRootNames = {}
		
		## @var listLampNames
		# List of names of the Blender3D lamps used. 	
		self.listLampNames = []
		
		## @var numVerts
		# Variable used to hold the number of the vertices of a mesh.
		self.numVerts = 0		
		
		## @var numFaceQuad
		# Variable used to hold the number of the quadrilateral faces in a mesh.		
		self.numFaceQuad = 0
		
		## @var numFaceTri
		# Variable used to hold the number of the triangular faces in a mesh.		
		self.numFaceTri = 0
		
		## @var dictVertices
		# Dictionary object used to list unique vertex combinations.				
		self.dictVertices = None
		
		## @var dictVertParallels
		# Dictionary object used to list vertex combinations arising from the same vertex.
		# The key used in this dictionary is the index of the vertice provided by Blender3D.
		# New index is generated and added on the fly if the vertex combination is not unique.			
		self.dictVertParallels = None
		
		## @var imageIndices
		# Dictionary object used to list the texture images by their index.		
		self.imageIndices = {}
		
		## @var imageCount
		# Variable to keep track of images used in the scene.
		self.imageCount = 0
		
	def writeCode(self,str):
		"""
		Writes str (- a string ) to the generated C file.
		"""		
		self.srcCodeFile.write(str+"\n")
		
	def writeHdr(self,str):
		"""
		Writes str (- a string ) to the generated H file.
		"""			
		self.hdrCodeFile.write(str+"\n")		

	def performPassOne(self):
		"""
		Performs the first pass during the export. 
		This pass is largely used for collection of names of objects in the scene.
		It also creates and intializes a few structures in the maintained lists
		and dictionaries.
		"""			
		print "Performing pass 1 ..."
		
		allObjects = self.currScene.objects
		
		for obj in allObjects:
			#print "Found ...", obj.name, "in layers ...",obj.layers
			bExport = False
			for objectlayer in obj.layers:
				if objectlayer in self.currScene.layers:
					bExport = True
			
			if bExport :
				print "Found ...", obj.name
				objData = obj.getData()	
				typeObjData= type(objData)
				
				if typeObjData == Types.NMeshType :
					self.dictMeshNames[objData.name] = 1
					self.dictObject3DNames[obj.name] = [objData.name, -1, [] ]
								
				if typeObjData == Types.CameraType :
					self.listCameraNames.append(obj.name)	
					
				if typeObjData == types.NoneType :
					self.dictObject3DNames[obj.name] = [None, -1, [] ]
					
				if typeObjData == Types.LampType :
					self.listLampNames.append(obj.name)					
		
	def writeMeshDefines(self, meshCodeName):
		"""
		Writes the C defines for constants defining the mesh structure in the H file.
		These defines and the related mesh structure is unique for the specified mesh name.
		
		meshCodeName - C friendly mesh name
		"""	
		self.writeHdr("#define		NUM_"+meshCodeName+"_VERTICES\t"+str(self.numVerts))  
		self.writeHdr("#define		NUM_"+meshCodeName+"_POINTS\t\t(NUM_"+meshCodeName+"_VERTICES*3)")        
		self.writeHdr("#define		SIZE_"+meshCodeName+"_VERTICES\t(NUM_"+meshCodeName+"_POINTS*SIZE_OBJ3DVERTEX)")        
		self.writeHdr("")  
		self.writeHdr("#define		NUM_"+meshCodeName+"_QUAD_INDICES\t"+str(self.numFaceQuad))  
		self.writeHdr("#define		NUM_"+meshCodeName+"_TRI_INDICES\t"+str(self.numFaceTri))  
		self.writeHdr("#define		NUM_"+meshCodeName+"_INDICES\t\t(NUM_"+meshCodeName+"_QUAD_INDICES*4+NUM_"+meshCodeName+"_TRI_INDICES*3)") 
		self.writeHdr("") 
		self.writeHdr("#define		OFFSET_"+meshCodeName+"_QUADS\t0") 
		self.writeHdr("#define		COUNT_"+meshCodeName+"_QUADS\t(NUM_"+meshCodeName+"_QUAD_INDICES*4)")       
		self.writeHdr("#define		SIZE_"+meshCodeName+"_QUADS\t\t(NUM_"+meshCodeName+"_QUAD_INDICES*SIZE_QUAD_INDEX)") 
		self.writeHdr("") 
		self.writeHdr("#define		OFFSET_"+meshCodeName+"_TRIADS\tSIZE_"+meshCodeName+"_QUADS") 
		self.writeHdr("#define		COUNT_"+meshCodeName+"_TRIADS\t(NUM_"+meshCodeName+"_TRI_INDICES*3)   ")     
		self.writeHdr("#define		SIZE_"+meshCodeName+"_TRIADS\t(NUM_"+meshCodeName+"_TRI_INDICES*SIZE_TRI_INDEX)") 
		self.writeHdr("") 
		self.writeHdr("#define		SIZE_"+meshCodeName+"_INDICES\t(OFFSET_"+meshCodeName+"_TRIADS+SIZE_"+meshCodeName+"_TRIADS)") 
		self.writeHdr("	") 
		
	def writeMagicIndexMapping(self, nNumOfPoygonVerts,faces):
		"""
		Writes the index table mapped to the generated unique vertice, texture and normal combination in the C file.
		
		nNumOfPoygonVerts - 3 or 4 depending on TRIANGLES or QUADS
		faces - Sequence of faces as contained in a Blender provided mesh
		"""			
		for face in faces:
			length = len(face.v)
			if nNumOfPoygonVerts == length :
				strSample = "	  "
				for i in range(nNumOfPoygonVerts):
					if self.bNormal:
						vertuv = (face.v[i].co[0],face.v[i].co[1],face.v[i].co[2]),(face.uv[i][0],face.uv[i][1]),(face.v[i].no.x,face.v[i].no.y,face.v[i].no.z)
					else:
						vertuv = (face.v[i].co[0],face.v[i].co[1],face.v[i].co[2]),(face.uv[i][0],face.uv[i][1])
					vertindex = face.v[i].index
					
					newVertIndex = None
					if  self.dictVertParallels.has_key(vertindex):
						old_arrParallelIndices = self.dictVertParallels[vertindex]
						
						for parallelIndex in old_arrParallelIndices:
							if vertuv == self.dictVertices[parallelIndex]:
								newVertIndex = parallelIndex
							
						if None == newVertIndex:
							newVertIndex = self.numVerts
							self.numVerts += 1	
							self.dictVertParallels[vertindex].append(newVertIndex)
							
					else:
							newVertIndex = 	vertindex
							self.dictVertParallels[newVertIndex] = []
							self.dictVertParallels[newVertIndex].append(newVertIndex)							
					
					# add the vertex	
					self.dictVertices[newVertIndex] = vertuv
					strSample = strSample + str(newVertIndex) + ","
					
				#print strSample
				self.writeCode(strSample)		
		
		
	def writeMeshIndices(self, meshCodeName, faces):
		"""
		Writes the index table for the vertices in the specifies mesh in the C file.
		
		meshCodeName - C friendly mesh name
		faces - Sequence of faces as contained in a Blender provided mesh
		"""			
		self.writeCode("GLuint		arrIndices_"+meshCodeName+"[NUM_"+meshCodeName+"_INDICES] =	{	")
		
		self.writeCode("	// QuadIndices")
		self.writeMagicIndexMapping(4,faces)
		
		self.writeCode("	// TriIndices")
		self.writeMagicIndexMapping(3,faces)
				
		self.writeCode("};")
		self.writeCode("	")  		
		
	def writeMeshVertices(self, meshCodeName):
		"""
		Writes the vertices in the specifies mesh in the C file.
		
		meshCodeName - C friendly mesh name
		"""			
		self.writeCode("fObj3DVertex	arrVertex_"+meshCodeName+"[NUM_"+meshCodeName+"_VERTICES]= {")	
		
		self.dictVertices.keys().sort()
		
		for key in self.dictVertices.keys():
			vertuv = self.dictVertices[key]
			if self.bNormal:
				self.writeCode("	{ {"
					+str(vertuv[0][0])+"f, "
					+str(vertuv[0][1])+"f, "
					+str(vertuv[0][2])+"f},{"
					
					+str(vertuv[1][0])+"f, "
					+str(vertuv[1][1])+"f},{"
					
					+str(vertuv[2][0])+"f, "
					+str(vertuv[2][1])+"f, "
					+str(vertuv[2][2])											
					+"f} },") 			
			else:
				self.writeCode("	{ {"				
					+str(vertuv[0][0])+"f, "
					+str(vertuv[0][1])+"f, "
					+str(vertuv[0][2])+"f},{"
					
					+str(vertuv[1][0])+"f, "
					+str(vertuv[1][1])				
					+"f} },")   						   
		self.writeCode("};")

		self.writeCode("	")	
		
	def writeMeshTable(self, meshCodeName):
		"""
		Writes the mesh structure in the C file.
		
		meshCodeName - C friendly mesh name
		"""			
		self.writeCode("fMeshTable		oMeshTable_"+meshCodeName+" = {")  
		self.writeCode('	"'+meshCodeName+'",')  
		self.writeCode("	arrVertex_"+meshCodeName+",")
		self.writeCode("	arrIndices_"+meshCodeName+",")
		self.writeCode("	SIZE_"+meshCodeName+"_VERTICES, SIZE_"+meshCodeName+"_INDICES,")
		self.writeCode("	COUNT_"+meshCodeName+"_QUADS, COUNT_"+meshCodeName+"_TRIADS,")
		self.writeCode("	OFFSET_"+meshCodeName+"_QUADS, OFFSET_"+meshCodeName+"_TRIADS, ") 
		self.writeCode("	0, 0,")  
		if self.bNormal:
			self.writeCode("	1,")  
		else:
			self.writeCode("	0,")  
		self.writeCode("};") 
		self.writeCode("	")	
		
	def getTextureName(self,imageTexture):
		"""
		Returns the relative path of the texture from the Blend file assuming that the 
		textures are in a sub folder in the Blend file path.
		
		imageTexture - Blender texture object
		"""			
		dirname = os.path.split(os.path.dirname(imageTexture.getFilename()))[1]
		basename = os.path.basename(imageTexture.getFilename())
		return os.path.join(dirname,basename)
		
	def indexTextureImage(self, imageTexture):
		"""
		Associates a unique index for the texture in the Blend file.
		
		imageTexture - Blender texture object
		"""			
		UV_ImageName = self.getTextureName(imageTexture) 
		if not self.imageIndices.has_key(UV_ImageName):
			self.imageIndices[UV_ImageName]  = self.imageCount
			self.imageCount = self.imageCount + 1
		
	def exportMesh(self, meshName):
		"""
		Exports the mesh object specified by the mesh name.
		This must be called after the final pass of the data collection.
		
		meshName - The Blender mesh object
		"""
		print "Generating code for mesh ...", meshName
		meshData = bpy.data.meshes[meshName]
		meshCodeName = reduceNamesToCodeNames(meshName)
		
		self.numVerts = len(meshData.verts)		
		self.numFaceQuad = 0
		self.numFaceTri = 0
		self.dictVertParallels = {}
		
		self.indexTextureImage(meshData.faces[0].image)
		
		for face in meshData.faces:
			length = len(face.v)
			if 4 == length :
				self.numFaceQuad += 1
			if 3 == length:
				self.numFaceTri += 1
		
		self.dictVertices = {}		
		self.writeMeshIndices(meshCodeName, meshData.faces)
		self.writeMeshVertices(meshCodeName)	
		self.writeMeshTable(meshCodeName)
		
		# To be moved to H file
		self.writeMeshDefines(meshCodeName)
		
	def exportCamera(self, cameraName):
		"""
		Exports the camera whose name is specified.
		A camera structure and an array listing the order of parents of the 
		camera is written to the C file. This must be called after the final 
		pass of the data collection.
		
		cameraName - name of the Blender camera object
		"""
		print "Generating code for camera ...", cameraName
		cameraCodeName = reduceNamesToCodeNames(cameraName)
		cameraData = bpy.data.objects[cameraName]	
		alt_cameraData = bpy.data.cameras[cameraData.getData().name]
		
		self.writeCode("int arrParent_"+cameraCodeName+" [] = {")  
		
		cameraParent = cameraData.getParent()
		if cameraParent:
			arrParentList = []
			while cameraParent:
				objName = cameraParent.name
				index = self.dictObject3DNames[objName][1]
				arrParentList.append(index)
				cameraParent = bpy.data.objects[objName].getParent()
				
			for index in arrParentList:
				self.writeCode("	"+str(index)+",") 
						
		self.writeCode("	-1,") 
		self.writeCode("};") 	
				
		self.writeCode("fCamera		o"+cameraCodeName+" = {") 
		self.writeCode('	"'+cameraCodeName+'",')  
		localMat = Mathutils.Matrix(cameraData.matrixLocal)
		TransMat = localMat.translationPart()
		LocX=TransMat.x
		LocY=TransMat.y
		LocZ=TransMat.z			
		
		self.writeCode("	"+str(LocX)+","+str(LocY)+","+str(LocZ)+",") 		   
		self.writeCode("	"+str(rad2deg(cameraData.RotX))+","+str(rad2deg(cameraData.RotY))+","+str(rad2deg(cameraData.RotZ))+",")    
		self.writeCode("	"+str(cameraData.SizeX)+","+str(cameraData.SizeY)+","+str(cameraData.SizeZ)+",")     
		self.writeCode("	"+str(alt_cameraData.getClipStart())+","+str(alt_cameraData.getClipEnd())+",") 
		self.writeCode("	"+str(alt_cameraData.getLens())+",") 
		self.writeCode("	arrParent_"+cameraCodeName+",") 
		self.writeCode("};") 
		self.writeCode("	")	
		
	def exportLamp(self, lampName):
		"""
		Exports the lamp whose name is specified.
		This must be called after the final pass of the data collection.		
		
		lampName - the name of the Blender lamp
		"""
		print "Generating code for lamp ...", lampName
		lampCodeName = reduceNamesToCodeNames(lampName)
		lampData = bpy.data.objects[lampName]	
		alt_lampData = bpy.data.lamps[lampData.getData().name]
		
		self.writeCode("fLamp		o"+lampCodeName+" = {") 
		self.writeCode('	"'+lampCodeName+'",')  
		localMat = Mathutils.Matrix(lampData.matrixLocal)
		TransMat = localMat.translationPart()
		LocX=TransMat.x
		LocY=TransMat.y
		LocZ=TransMat.z			
		
		self.writeCode("	{"+str(LocX)+","+str(LocY)+","+str(LocZ)+",1.0},") 		   
		self.writeCode("	"+str(rad2deg(lampData.RotX))+","+str(rad2deg(lampData.RotY))+","+str(rad2deg(lampData.RotZ))+",")    
		self.writeCode("	"+str(lampData.SizeX)+","+str(lampData.SizeY)+","+str(lampData.SizeZ)+",")     
		self.writeCode("	{"+str(alt_lampData.R)+","+str(alt_lampData.G)+","+str(alt_lampData.B)+",1.0},") 
		self.writeCode("	{"+str(alt_lampData.R)+","+str(alt_lampData.G)+","+str(alt_lampData.B)+",1.0},") 
		#self.writeCode("	{"+str(alt_lampData.energy)+","+str(alt_lampData.energy)+","+str(alt_lampData.energy)+",1.0},")
		self.writeCode("};") 
		self.writeCode("	")		
				
	def identifyRoot(self, objName):
		"""
		Identifies the objects who do not have parents and hence top the
		drawing order. This is to avoid drawing the object twice as a child object will
		get drawn when the parent is drawn.
		
		objName - the name of the Blender object
		"""
		objCodeName = reduceNamesToCodeNames(objName)
		objData = bpy.data.objects[objName]		
		parent = objData.getParent()
		if not parent:
			#print "4",self.dictRootNames
			if not self.dictRootNames.has_key(objName):
				self.dictRootNames[objName] = []	
				#print "5",self.dictRootNames	
		
	def exportObject3D(self, objName):
		"""
		Exports the object whose name is specified.
		An object structure and an array listing the order of parents of the 
		camera is written to the C file. This must be called after the final 
		pass of the data collection.
		
		objName - name of the Blender object
		"""	
		print "Generating code for Object3D ...", objName
		objCodeName = reduceNamesToCodeNames(objName)
		obj = bpy.data.objects[objName]	
		objData = obj.getData()	
		
		localMat = Mathutils.Matrix(obj.matrixLocal)
		TransMat = localMat.translationPart()
		LocX=TransMat.x
		LocY=TransMat.y
		LocZ=TransMat.z
		
		self.writeCode("int arrChildren_"+objCodeName+" [] = {")  
		
		childIndices = self.dictObject3DNames[objName][2]
		for index in childIndices:
			self.writeCode("	"+str(index)+",") 
						
		self.writeCode("	-1,") 
		self.writeCode("};") 	
		
		self.writeCode("	")		
		
		self.writeCode("fObject3D		o"+objCodeName+" = {")  
		self.writeCode('	"'+objCodeName+'",') 
		
		if objData:
			meshName = self.dictObject3DNames[objName][0]
			meshCodeName = reduceNamesToCodeNames(meshName)
			meshData = bpy.data.meshes[meshName]
			UV_ImageName = self.getTextureName(meshData.faces[0].image)
			self.writeCode("	&oMeshTable_"+meshCodeName+",")    
			self.writeCode('	//"'+UV_ImageName+'",')
			self.writeCode("	"+str(self.imageIndices[UV_ImageName])+",")		
		else:
			self.writeCode("	NULL,")    
			self.writeCode("	0,")				
		
		self.writeCode("	NULL,") 				
		self.writeCode("	"+str(LocX)+","+str(LocY)+","+str(LocZ)+",")     
		self.writeCode("	"+str(rad2deg(obj.RotX))+","+str(rad2deg(obj.RotY))+","+str(rad2deg(obj.RotZ))+",")    
		self.writeCode("	"+str(obj.SizeX)+","+str(obj.SizeY)+","+str(obj.SizeZ)+",")   
		self.writeCode("	arrChildren_"+objCodeName+",")   
 		self.writeCode("};") 
		self.writeCode("	")	
		
		self.identifyRoot(objName)
		
	def exportTextures(self):
		"""
		Exports the texture images used in the current scene.
		An array of structures listing the simple relative file path camera 
		is written to the C file. This must be called after the final 
		pass of the data collection.
		"""		
		print "Generating code for textures ..."
		self.writeCode("fTextureEntry	arrTextureEntry_"+reduceNamesToCodeNames(self.currScene.name)+"[] = {")

		invImageIndices = {}
		for key in self.imageIndices.keys():
			invImageIndices[ self.imageIndices[key] ] = key      

		invImageIndices.keys().sort()

		for index in invImageIndices:
			self.writeCode('	//"'+str(index)+'",')
			self.writeCode('	{"'+invImageIndices[index]+'",0},')
		self.writeCode("};  ")
		self.writeCode("	")		
		
	def performPassTwo(self):
		"""
		Performs the second pass during the export. 
		This pass is largely used for exporting the collected information and 
		their association as per the needs of the C structures.
		and dictionaries.
		"""		
		print "Performing pass 2 ..."	
		
		self.dictMeshNames.keys().sort()
		
		self.dictObject3DNames.keys().sort()
		
		for meshName in self.dictMeshNames.keys():
			self.exportMesh(meshName)
			
		for cameraName in self.listCameraNames:
			self.exportCamera(cameraName)
			
		for objName in self.dictObject3DNames.keys():
			self.exportObject3D(objName)			
			
		self.exportTextures()	
		
		for lampName in self.listLampNames:
			self.exportLamp(lampName)		
		
	def identifyIndicesForObjects(self):
		"""
		Identifies unique indices for the objects whose data has been collected.
		"""			
		print "Identifying indices for objects ..."
		
		self.dictObject3DNames.keys().sort
		
		objNames = self.dictObject3DNames.keys()
		
		index = 0
		for objName in objNames:
			self.dictObject3DNames[objName][1]  = index
			index += 1
		
	def associateParents(self):
		"""
		Associates the objects with their respective parent object.
		"""		
		print "Idenitfying parents for objects ..."
		
		objNames = self.dictObject3DNames.keys()
		for objName in objNames:	
			objData = bpy.data.objects[objName]		
			parent = objData.getParent()
			if parent:
				parentName = parent.name	
				childIndex = self.dictObject3DNames[objName][1]
				self.dictObject3DNames[parentName][2].append(childIndex)			
		
	def writeSceneStructure(self):
		"""
		Writes the collection of objects, root objects, cameras, and lamps which make up the scene
		to the C file.
		"""			
		print "Writing scene structure ..."	
		
		sceneName = reduceNamesToCodeNames(self.currScene.name)
		
		self.writeCode("fObject3D* arrChildren_"+sceneName+" [] = {")  
		
		for objName in self.dictObject3DNames.keys():
			objCodeName = reduceNamesToCodeNames(objName)      
			self.writeCode("	&o"+objCodeName+",")  
						
		self.writeCode("	NULL,") 
		self.writeCode("};")  			
		
		self.writeCode("	")
		
		self.writeCode("int arrRootObjects_"+sceneName+" [] = {")  
		for objName in self.dictRootNames.keys():
			self.writeCode("	"+str(self.dictObject3DNames[objName][1])+",") 
						
		self.writeCode("	-1,") 
		self.writeCode("};")  			
		
		self.writeCode("	")		
		
		self.writeCode("fCamera* arrCameras_"+sceneName+" [] = {")  
		
		for cameraName in self.listCameraNames:
			cameraCodeName = reduceNamesToCodeNames(cameraName)      
			self.writeCode("	&o"+cameraCodeName+",")  
						
		self.writeCode("	NULL,") 
		self.writeCode("};")  			
		
		self.writeCode("	")
		
		self.writeCode("fLamp* arrLamps_"+sceneName+" [] = {")  
		
		for lampName in self.listLampNames:
			lampCodeName = reduceNamesToCodeNames(lampName)      
			self.writeCode("	&o"+lampCodeName+",")  
						
		self.writeCode("	NULL,") 
		self.writeCode("};")  			
		
		self.writeCode("	")		
		
		self.writeCode("fScene o"+sceneName+" = {")
		self.writeCode("	arrTextureEntry_"+sceneName+",")
		self.writeCode("	arrChildren_"+sceneName+",")
		self.writeCode("	arrRootObjects_"+sceneName+",")
		self.writeCode("	arrCameras_"+sceneName+",")
		self.writeCode("	arrLamps_"+sceneName+",")
		self.writeCode("};  ")
		
		self.writeCode("	")		
		
	def writeClosingComments(self):
		"""
		Writes the closing comments in the H file.
		These comments are a set of externs which can be used by a programmers in their main project.
		"""
		print "Writing closing comments ..."
		
		sceneName = reduceNamesToCodeNames(self.currScene.name)
		
		for meshName in self.dictMeshNames.keys():
			meshCodeName = reduceNamesToCodeNames(meshName)
			self.writeHdr("// extern fObj3DVertex arrVertex_"+meshCodeName+"[NUM_"+meshCodeName+"_VERTICES];")
			self.writeHdr("// extern GLuint arrIndices_"+meshCodeName+"[NUM_"+meshCodeName+"_INDICES];")
		
		self.writeHdr("	")
		
		for meshName in self.dictMeshNames.keys():
			meshCodeName = reduceNamesToCodeNames(meshName)
			self.writeHdr("// extern fMeshTable oMeshTable_"+meshCodeName+";")
		
		self.writeHdr("	")
		
		for cameraName in self.listCameraNames:
			cameraCodeName = reduceNamesToCodeNames(cameraName)
			self.writeHdr("// extern fCamera o"+cameraCodeName+";")
		
		self.writeHdr("	")
			
		for objName in self.dictObject3DNames.keys():
			objCodeName = reduceNamesToCodeNames(objName)
			self.writeHdr("// extern int arrChildren_"+objCodeName+" [];") 
			self.writeHdr("// extern fObject3D o"+objCodeName+";")			
					
		self.writeHdr("	")						
		
		self.writeHdr("// extern fTextureEntry arrTextureEntry_"+sceneName+"[];")
		self.writeHdr("// extern fObject3D* arrChildren_"+sceneName+" [];")  
		self.writeHdr("// extern int arrRootObjects_"+sceneName+" [];")  
		self.writeHdr("// extern fCamera* arrCameras_"+sceneName+" [];") 
		
		self.writeHdr("	")
		
		self.writeHdr("// extern fScene o"+sceneName+";")
		
		self.writeHdr("	")	
		
	def exportScene(self):		
		"""
		Exports the current scene to a C and H file. The name for the file is generated using the
		name of the scene . The entire export procedure is broken into two passes and an indexing
		and association step between the two. This is followed by the writing of data to the C
		and the H files.
		"""
		print "###############################################"
		print 'Exporting scene : ',self.currScene.name
		print 'Exporting scene to file : ',self.srcCodeFileScene,self.hdrCodeFileScene
		
		self.hdrCodeFile = open(self.hdrCodeFileScene, "w")
		self.srcCodeFile = open(self.srcCodeFileScene, "w")
		
		self.writeHdr('#include "carmine_defs.h"')
		self.writeHdr("") 
		
		self.writeCode('#include "'+self.hdrFilename+'"')
		self.writeCode("") 
		
		self.performPassOne()
		
		self.identifyIndicesForObjects()
		
		self.associateParents()
		
		self.performPassTwo()
		
		self.writeSceneStructure()
		
		self.writeClosingComments()
				
		self.srcCodeFile.close()
		self.hdrCodeFile.close()
		
		print "Completed writing code."		




## Event upon idle state
EVENT_NOEVENT = 1
## Event fired when 'Normals' Button is toggled
EVENT_TOGGLE_NORMALS = 2
## Event fired when 'Export' button is clicked
EVENT_EXPORT = 3
## Event fired when 'Exit' button is clicked
EVENT_EXIT = 4

## Variable to hold the Toggle button
T_bNormals = Create(1)

def draw():
	"""
	Draws the GUI for the export script.
	"""
	
	global T_bNormals
	global EVENT_NOEVENT,EVENT_TOGGLE_NORMALS,EVENT_EXPORT,EVENT_EXIT
	
	glClear(GL_COLOR_BUFFER_BIT)
	glRasterPos2d(10, 160)
	Text("carmine - C / C++ exporter"+ " version " + __version__)
	
	glRasterPos2d(10, 140)
	Text("Parameters:")
	
	T_bNormals = Toggle("Include Normals",EVENT_TOGGLE_NORMALS , 10, 110, 160, 18, T_bNormals.val)
	
	Button("Export",EVENT_EXPORT , 250, 40, 80, 18)
	Button("Exit",EVENT_EXIT , 250, 16, 80, 18)
        

def conductExport():
	"""
	Exports the current scene based on the GUI controlled parameters.
	"""
	
	value_bNormal = True
	if T_bNormals.val == 0 :
		value_bNormal = False
	
	glexport = GLExport(value_bNormal)
	glexport.exportScene()

def event(evt, val):
	"""
	Handles keyboard events.
	"""
	
	if (evt == QKEY and not val):
		Exit()

def bevent(evt):
	"""
	Handles GUI events.
	"""
	
	global EVENT_NOEVENT,EVENT_TOGGLE_NORMALS,EVENT_EXPORT,EVENT_EXIT
	
	if (evt == EVENT_EXIT):
		Exit()
		
	elif (evt== EVENT_TOGGLE_NORMALS):
		Blender.Redraw()
		
	elif (evt== EVENT_EXPORT):
		conductExport()
		Blender.Redraw()
		Exit()


########################################################################

if not os.path.exists(GEN_PATH):
	os.mkdir(GEN_PATH)
	
Register(draw, event, bevent)


#glexport = GLExport(True)
##glexport = GLExport(False)
#glexport.exportScene()
##
##from pydoc import help
##help(rad2deg)
##help(deg2rad)
##help(reduceNamesToCodeNames)
##help(GLExport)

