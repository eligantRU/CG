#include "stdafx.h"

#include "PhysWorld.h"

CPhysWorld::CPhysWorld(const glm::vec3 & gravity)
{
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_overlappingPairCache = new btDbvtBroadphase();
	m_solver = new btSequentialImpulseConstraintSolver;
	m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache,
	                                      m_solver, m_collisionConfiguration);

	m_world->setGravity(btVector3(btScalar(gravity.x), btScalar(gravity.y), btScalar(gravity.z)));
}

CPhysWorld::~CPhysWorld()
{
	for (int i = m_world->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject * obj = m_world->getCollisionObjectArray()[i];
		btRigidBody * body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_world->removeCollisionObject(obj);
		delete obj;
	}

	for (int i = 0; i < m_collisionShapes.size(); i++)
	{
		btCollisionShape * shape = m_collisionShapes[i];
		m_collisionShapes[i] = 0;
		delete shape;
	}

	delete m_world;
	delete m_solver;
	delete m_overlappingPairCache;
	delete m_dispatcher;
	delete m_collisionConfiguration;
	m_collisionShapes.clear();
}

int CPhysWorld::AddShape(btCollisionShape * shape)
{
	m_collisionShapes.push_back(shape);
	return m_collisionShapes.size() - 1;
}

void CPhysWorld::AddRigidBody(btRigidBody * body)
{
	m_world->addRigidBody(body);
}

void CPhysWorld::StepSimulation(float timeStep, int maxSubSteps = 1)
{
	m_world->stepSimulation(btScalar(timeStep), maxSubSteps);
}

glm::vec3 CPhysWorld::GetPosition(int shapeIndex)
{
	btCollisionObject * obj = m_world->getCollisionObjectArray()[shapeIndex];
	btRigidBody * body = btRigidBody::upcast(obj);
	btTransform trans;
	if (body && body->getMotionState())
	{
		body->getMotionState()->getWorldTransform(trans);
	}
	else
	{
		trans = obj->getWorldTransform();
	}
	return {
		trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()
	};
}
