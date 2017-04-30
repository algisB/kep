#compilation
CC = clang -std=gnu++11


InputManager.o : ../InputManager.cpp
	$(CC) -c ../InputManager.cpp -I ../

EventSubscriber.o : ../EventSubscriber.cpp
	$(CC) -c ../EventSubscriber.cpp -I ../

Event.o : ../Event.cpp
	$(CC) -c ../Event.cpp -I ../

EventHandler.o : ../EventHandler.cpp
	$(CC) -c ../EventHandler.cpp -I ../

Component.o : ../Component.cpp
	$(CC) -c ../Component.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image

GameObject.o : ../GameObject.cpp
	$(CC) -c ../GameObject.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image

Light.o : ../Light.cpp
	$(CC) -c ../Light.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image

Mesh.o : ../Mesh.cpp
	$(CC) -c ../Mesh.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image

Obj2.o : ../Obj2.cpp
	$(CC) -c ../Obj2.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image

ShaderManager.o : ../ShaderManager.cpp
	$(CC) -c ../ShaderManager.cpp -I ../
	
Particle.o : ../kep/Particle.cpp
	$(CC) -c ../kep/Particle.cpp -I ../
Core.o : ../kep/Core.cpp
	$(CC) -c ../kep/Core.cpp -I ../
	
#-------------------------------------------------------------

Scene.o : ../Scene.cpp
	$(CC) -c ../Scene.cpp -I ../ -I ../SDL2/include -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2_image

glew.o : ../glew.c
	clang -c ../glew.c -I ../

Main.o : ../Main.cpp
	$(CC) -c ../Main.cpp -I ../ -I ../SDL2/include -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2_image


#linking
all: Main.o glew.o Scene.o  InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o Particle.o Core.o
	$(CC) -o ../bin/kek-engine-v2 Main.o glew.o Scene.o InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o Particle.o Core.o -rdynamic -L ../SDL2_image/libs -Wl,-Bstatic -lSDL2_image -Wl,-Bdynamic -lSDL2 -lGL -lm -lstdc++
	#$(CC) -o softRend Main.o glew.o Scene.o InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o ../SDL2libs/libSDL2.so -lm -lstdc++ -lGL

clean:
	rm -f *.o
