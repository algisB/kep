#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include <time.h>
#include <gtc/type_ptr.hpp> 
#include <glm.hpp>
#include <quaternion.hpp>
#include "ShaderManager.h"
#include "SETTINGS.h"
#include "kep/Core.h"
#include "kep/RigidBody.h"
#include "kep/ForceGenerator.h"
#include "kep/World.h"
//

class GameObject;
class Component
{
public:
	GameObject * m_gameObject;
	string m_tag;

	Component(GameObject *_gameObject, string _tag);
	virtual ~Component()=0;
	virtual void update()=0;
};

class Transform : public Component
{
	public:
		// world space
		glm::vec3 m_position; 
		glm::vec3 m_rotation;
		glm::vec3 m_scale;

		//relative to parent
		glm::vec3 m_localPosition;
		glm::vec3 m_localRotation;
		glm::vec3 m_localScale;


		glm::mat4 m_rotMatrix;
		glm::mat4 m_modelMatrix;

		glm::mat4 *m_viewMatrix;
		glm::mat4 *m_projectionMatrix;

		//new scene graph
		glm::mat4 m_globalTransform;
		glm::mat4 m_localTransform;
		glm::mat4 m_inheritTransform;
		Transform * m_parent;
		vector<Transform*> m_children;


		Transform(GameObject *_gameObject, string _tag, glm::mat4 * _viewMatrix, glm::mat4 * _projectionMatrix );
		~Transform();
		void update();
		void recalc();

		void Parent(Transform * _parent);
		//void RemoveChild(ActorID id);

};
class Material : public Component
{
public:
	GLuint * m_texture;
	Material(GameObject *_gameObject, string _tag, GLuint * _texture);
	~Material();
	void update();
};
class MeshRenderer : public Component
{
public:
    enum
    {
        SOLID = 0,
        WIRE
    };
	Mesh * m_mesh;
	Transform * m_transform;
	Material * m_material;
	ShaderProgram * m_shaderProgram;

    int m_renderMode;
    
	MeshRenderer(GameObject *_gameObject, string _tag, Mesh * _mesh, ShaderProgram * _shaderProgram, int _renderMode);
	~MeshRenderer();
	void update();

};
class Camera : public Component
{
public:
	Transform * m_transform;
	glm::vec3 m_cameraFront;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

	Camera(GameObject *_gameObject, string _tag, glm::mat4 _projectionMatrix);
	~Camera();
	void update();
};

//made for testing purposes
class PhysicalComponent : public Component
{
public:
    Transform * p_transform;
    Kep::World * p_physicsWorld;
    Kep::RigidBody * m_body;

    
    PhysicalComponent(GameObject *_gameObject, string _tag, Kep::World * _physicsWorld, Kep::real _mass);
    ~PhysicalComponent();
    
    void update();
    
    
};



