# Graded-Unit-Repo-2
A repository for storage of my Year 3 Graded Unit Project

Linking project:
Place "Dev" Folder within the c: drive directory

Link:

c/c++ -> general -> additional include directories:
C:\Dev\SDL2-2.0.8\include;C:\Dev\SDL2_ttf-2.0.14;C:\Dev\SDL2_image-2.0.3;C:\Dev\glm;C:\Dev\glew-2.1.0\include;%(AdditionalIncludeDirectories)


Linker -> general -> Additional library directories:
C:\Dev\SDL2-2.0.8\VisualC\Win32\Debug;C:\Dev\SDL2_ttf-2.0.14\VisualC\Win32\Debug;C:\Dev\SDL2_image-2.0.3\VisualC\Win32\Debug;C:\Dev\glew-2.1.0\lib\Debug\Win32;%(AdditionalLibraryDirectories)

Linker -> general -> Input:
SDL2.lib;SDL2main.lib;glew32d.lib;opengl32.lib;SDL2_image.lib;SDL2_ttf.lib;bass.lib;%(AdditionalDependencies)

Run as x86 platform solution




GAMEPLAY:
Keyboard:
A & D = move player left and right
SPACE = Jump

Game pad:
D-Pad - Left & right = move player left and right
A = Jump
