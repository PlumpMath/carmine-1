env = Environment()

# For profiling
#env.Append(CCFLAGS = ' -pg ')
#env.Append(LINKFLAGS = ' -pg ')

env.Append(CPPPATH = [
	'/usr/include/freetype2',
	'/usr/local/include',
	'include', 
	'contrib' , 
	'contrib/timer' , 
	'gen' , 
	])
	
env.Append(LIBPATH = [
	'/usr/local/lib',
	])	

env.Append(LIBS = [
	'SDL',
	'GL', 
	'GLU', 
	'stdc++', 
	'freetype', 
	'freeimage',
	'ftgl',
	])

src = env.Library(
	'src/src.a', 
	[
		'src/main.cpp',	
		'src/demo.cpp',	
		'src/app.cpp', 		
		'src/window.cpp',
		'src/carmine_defs.c',
		'src/carmine_addons.c',				
	])
	
gen = env.Library(
	'gen/gen.a', 
	[
		'gen/Scene.c', 
	])

contrib = env.Library(
	'contrib/contrib.a', 
	[
		'contrib/GLee/GLee.cpp', 
		'contrib/timer/timer.cpp', 
	])

carmine = env.Program(
	'bin/carmine', 
	[
		src[0], 
		gen[0], 
		contrib[0],
	])

Depends(carmine, src)
Depends(carmine, gen)
Depends(carmine, contrib)

