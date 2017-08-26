#include "Component.h"

Component::Component(GameObject *_gameObject, string _tag)
{
	this->m_gameObject = _gameObject;
	this->m_tag = _tag;
}
Component::~Component()
{
}

Transform::Transform(GameObject *_gameObject, string _tag, glm::mat4 * _viewMatrix, glm::mat4 * _projectionMatrix) : Component(_gameObject, _tag)
{
	this->m_position = glm::vec3(0 ,0 ,0);
	this->m_rotation = glm::vec3(0, 0, 0);
	this->m_scale = glm::vec3(1, 1, 1);

	this->m_localPosition = glm::vec3(0, 0, 0);
	this->m_localRotation = glm::vec3(0, 0, 0);
	this->m_localScale = glm::vec3(1, 1, 1);

	this->m_localTransform = glm::mat4(1.0f);
	this->m_globalTransform = glm::mat4(1.0f);
	this->m_inheritTransform = glm::mat4(1.0f);
	this->m_parent = NULL;

	this->m_modelMatrix = glm::translate(glm::scale(glm::mat4(1.0f), this->m_scale), this->m_position);
	this->m_rotMatrix = glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), (this->m_rotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (this->m_rotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (this->m_rotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0));


	this->m_viewMatrix = _viewMatrix;
	this->m_projectionMatrix = _projectionMatrix;
}
void Transform::update()
{
	recalc();
}
void Transform::recalc()
{
	m_localTransform = glm::mat4(1.0f);
	m_globalTransform = glm::mat4(1.0f);
	m_inheritTransform = glm::mat4(1.0f);
	
	m_inheritTransform = glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), this->m_localPosition), (this->m_localRotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (this->m_localRotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (this->m_localRotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0));
	m_localTransform = glm::scale(m_inheritTransform, this->m_localScale);

	if (m_parent != NULL)
	{
		m_globalTransform = m_parent->m_inheritTransform*m_localTransform;
		m_inheritTransform = m_parent->m_inheritTransform * m_inheritTransform;
	}
	else
	{
		m_globalTransform = m_localTransform;
	}
	
	

	m_modelMatrix = m_globalTransform;
	m_rotMatrix = glm::mat4(1.0f);

}
void Transform::Parent(Transform * _parent)
{
	//m_children.push_back(_child);
	//_child->m_parent = this;
	this->m_parent = _parent;
	_parent->m_children.push_back(this);

}
Transform::~Transform()
{}

Material::Material(GameObject *_gameObject, string _tag, GLuint * _texture) : Component(_gameObject, _tag)
{
	this->m_texture = _texture;
}
Material::~Material()
{}
void Material::update()
{
}

MeshRenderer::MeshRenderer(GameObject *_gameObject, string _tag, Mesh * _mesh, ShaderProgram * _shaderProgram, int _renderMode) : Component(_gameObject, _tag)
{
	this->m_mesh = _mesh;
	this->m_transform = _gameObject->getComponent<Transform>();
	this->m_material = _gameObject->getComponent<Material>();

	this->m_shaderProgram = _shaderProgram;
    this->m_renderMode = _renderMode;
}
MeshRenderer::~MeshRenderer()
{
}
void MeshRenderer::update()
{
	//_shaderProgram = _shaderProgram3;
	glUseProgram(m_shaderProgram->m_shaderProgramLocation);


		//send texture sampler locations to the shader
		glUniform1i(m_shaderProgram->m_shaderText1SamplerLocation, 0);
		//_modelMatrix = glm::translate(glm::scale(glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), (gameObjects[i]->rotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (gameObjects[i]->rotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (gameObjects[i]->rotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0)), gameObjects[i]->scale), gameObjects[i]->position);
		glUniformMatrix4fv(m_shaderProgram->m_shaderRotMatLocation, 1, GL_FALSE, glm::value_ptr(m_transform->m_rotMatrix));
		glUniformMatrix4fv(m_shaderProgram->m_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(m_transform->m_modelMatrix));
		glUniformMatrix4fv(m_shaderProgram->m_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(*m_transform->m_viewMatrix));
		glUniformMatrix4fv(m_shaderProgram->m_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(*m_transform->m_projectionMatrix));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *m_material->m_texture);
		
        
        switch(m_renderMode)
        {
            case SOLID:
                glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                break;
            
            case WIRE:
                glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                break;
        }
            glBindVertexArray( m_mesh->m_vao );
            glDrawArrays(GL_TRIANGLES, 0, m_mesh->m_numVertices);
            glBindVertexArray( 0 );
		//m_mesh->Draw();

	
}


Camera::Camera(GameObject *_gameObject, string _tag, glm::mat4 _projectionMatrix) : Component(_gameObject, _tag)
{
	this->m_transform = _gameObject->getComponent<Transform>();
	this->m_projectionMatrix = _projectionMatrix;
	m_cameraFront = glm::vec3(
		cos(-m_transform->m_rotation.x) * sin(-m_transform->m_rotation.y),
		sin(m_transform->m_rotation.x),
		cos(-m_transform->m_rotation.x) * cos(-m_transform->m_rotation.y));
}
Camera::~Camera()
{

}

void Camera::update()
{
	m_cameraFront = glm::normalize( glm::vec3(0.0f,0.0f,-1.0f) * glm::mat3(m_viewMatrix));

	glm::mat4 tmpMat = m_transform->m_modelMatrix;

	m_viewMatrix = glm::inverse (tmpMat);
}

PhysicalComponent::PhysicalComponent(GameObject* _gameObject, string _tag) : Component(_gameObject, _tag) 
{
    this->m_transform = _gameObject->getComponent<Transform>();
}
PhysicalComponent::~PhysicalComponent()
{
    
}

void PhysicalComponent::update()
{
     glm::mat4 & modMat = m_transform->m_modelMatrix;
     float * modMatArr = (float*)glm::value_ptr(modMat);
     
     
     Kep::Quaternion q1;
     q1.setEuler(Kep::Vector3(1.0f,0.0f,0.0f), 45.0f);
     //Kep::Quaternion q2;
     //q2.setEuler(0.0f, 0.0f, 0.0f);
     
     //q1 *= q2;
     Kep::Matrix4 rotMat;
     rotMat.setOrientationAndPos(q1, Kep::Vector3(0,0,0));
    //      Kep:: Matrix4 rotMat(
    //          1.0f, 0.0f, 0.0f, 20.0f,
    //          0.0f, cos(angle*(3.14159265358979323846 / 180.0f)), -sin(angle*(3.14159265358979323846 / 180.0f)), 0.0f,
    //          0.0f, sin(angle*(3.14159265358979323846 / 180.0f)), cos(angle*(3.14159265358979323846 / 180.0f)), 0.0f,
    //          0.0f, 0.0f, 0.0f, 1.0f
    //    );
     
     rotMat = rotMat.transpose();
     //Kep::Quaternion q1;
     //q1.rotateByVector(Kep::Vector3(20,0,0));
     //mat1.setOrientationAndPos(q1, Kep::Vector3(0,0,0));
     for(int i = 0; i<16; i++)
         modMatArr[i] = rotMat.data[i];
}


