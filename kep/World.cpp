#include "World.h"
using namespace Kep;

World::World()
{
    m_fReg = new Kep::ForceRegistry();
    m_gGen = new Kep::Gravity(Kep::Vector3(0.0f, -9.81f, 0.0f));
    m_ldGen = new Kep::LinearDrag(0.0f, 0.001f);
    m_adGen = new Kep::AngularDrag(0.0, 0.1f);
}
void World::update(real _duration)
{
    m_fReg->updateForces(_duration);
    for(int i = 0; i < m_rigidBody.size(); i++)
    {
        m_rigidBody[i]->integrate(_duration);
    }
}
void World::addRigidBody(RigidBody * _rigidBody)
{
    m_fReg->add(_rigidBody, m_gGen);
    m_fReg->add(_rigidBody, m_ldGen);
    m_fReg->add(_rigidBody, m_adGen);
    m_rigidBody.push_back(_rigidBody);
}
