#compilation
CC = clang -std=gnu++11


InputManager.o : ../InputManager.cpp ../InputManager.h
	$(CC) -c ../InputManager.cpp -I ../

EventSubscriber.o : ../EventSubscriber.cpp ../EventSubscriber.h
	$(CC) -c ../EventSubscriber.cpp -I ../

Event.o : ../Event.cpp ../Event.h
	$(CC) -c ../Event.cpp -I ../

EventHandler.o : ../EventHandler.cpp ../EventHandler.h
	$(CC) -c ../EventHandler.cpp -I ../

Component.o : ../Component.cpp ../Component.h
	$(CC) -c ../Component.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image

GameObject.o : ../GameObject.cpp ../GameObject.h
	$(CC) -c ../GameObject.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image

Light.o : ../Light.cpp ../Light.h
	$(CC) -c ../Light.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image

Mesh.o : ../Mesh.cpp ../Mesh.h
	$(CC) -c ../Mesh.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image

Obj2.o : ../Obj2.cpp ../Obj2.h
	$(CC) -c ../Obj2.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image

ShaderManager.o : ../ShaderManager.cpp ../ShaderManager.h
	$(CC) -c ../ShaderManager.cpp -I ../
	
Particle.o : ../kep/Particle.cpp ../kep/Particle.h
	$(CC) -c ../kep/Particle.cpp -I ../
	
Core.o : ../kep/Core.cpp ../kep/Core.h
	$(CC) -c ../kep/Core.cpp -I ../
	
ParticleForceGenerator.o : ../kep/ParticleForceGenerator.cpp ../kep/ParticleForceGenerator.h
	$(CC) -c ../kep/ParticleForceGenerator.cpp -I ../
	
ParticleContact.o : ../kep/ParticleContact.cpp ../kep/ParticleContact.h
	$(CC) -c ../kep/ParticleContact.cpp -I ../
	
ParticleLink.o : ../kep/ParticleLink.cpp ../kep/ParticleLink.h
	$(CC) -c ../kep/ParticleLink.cpp -I ../
	
ParticleWorld.o : ../kep/ParticleWorld.cpp ../kep/ParticleWorld.h
	$(CC) -c ../kep/ParticleWorld.cpp -I ../
#-------------------------------------------------------------

Scene.o : ../Scene.cpp ../Scene.h
	$(CC) -c ../Scene.cpp -I ../ -I ../SDL2/include -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2_image -I ../kep/

glew.o : ../glew.c
	clang -c ../glew.c -I ../

Main.o : ../Main.cpp
	$(CC) -c ../Main.cpp -I ../ -I ../SDL2/include -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2_image -I ../kep/
	


#linking
all: Main.o glew.o Scene.o  InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o Particle.o Core.o ParticleForceGenerator.o ParticleContact.o ParticleLink.o ParticleWorld.o
	$(CC) -o ../bin/kek-engine-v2 Main.o glew.o Scene.o InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o Particle.o Core.o ParticleForceGenerator.o ParticleContact.o ParticleLink.o ParticleWorld.o -rdynamic -L ../SDL2_image/libs -Wl,-Bstatic -lSDL2_image -Wl,-Bdynamic -lSDL2 -lGL -lm -lstdc++
	#$(CC) -o softRend Main.o glew.o Scene.o InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o ../SDL2libs/libSDL2.so -lm -lstdc++ -lGL

clean:
	rm -f *.o
