#pragma once

#include "IdentitySphere.h"
#include "IdentityCube.h"

class CPhysWorld
{
public:
	CPhysWorld(const glm::vec3 & gravity);
	~CPhysWorld();

	int AddShape(btCollisionShape * shape);
	void AddRigidBody(btRigidBody * body);

	void StepSimulation(float timeStep, int maxSubSteps);

	glm::vec3 GetPosition(int shapeIndex);
	glm::quat GetOrientation(int shapeIndex);

private:
	btDefaultCollisionConfiguration * m_collisionConfiguration = nullptr;
	btCollisionDispatcher * m_dispatcher = nullptr;
	btBroadphaseInterface * m_overlappingPairCache = nullptr;
	btSequentialImpulseConstraintSolver * m_solver = nullptr;
	btDiscreteDynamicsWorld * m_world = nullptr;

	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
};

class CPhysBox
{
public:
	CPhysBox(CPhysWorld & world, const glm::vec3 & size, const glm::vec3 & pos, float mass)
		:m_world(world)
	{
		m_shape = new btBoxShape(btVector3(size.x, size.y, size.z));
		m_worldIndex = m_world.AddShape(m_shape);

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

		btScalar weight(mass);
		btVector3 localInertia(0, 0, 0);
		if (weight != 0.f)
		{
			m_shape->calculateLocalInertia(weight, localInertia);
		}

		m_motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(weight, m_motionState, m_shape, localInertia);
		m_body = new btRigidBody(rbInfo);

		m_world.AddRigidBody(m_body);
	}

	int GetWorldIndex() const
	{
		return m_worldIndex;
	}

private:
	CPhysWorld & m_world;
	btCollisionShape * m_shape = nullptr;
	btRigidBody * m_body = nullptr;

	btDefaultMotionState * m_motionState = nullptr;

	int m_worldIndex = -1;
};

class CPhysSphere
{
public:
	CPhysSphere(CPhysWorld & world, float radius, const glm::vec3 & pos, float mass)
		:m_world(world)
	{
		m_shape = new btSphereShape(btScalar(radius));
		m_worldIndex = m_world.AddShape(m_shape);

		btTransform startTransform;
		startTransform.setIdentity();

		btScalar weight(mass);
		btVector3 localInertia(0, 0, 0);

		if (weight != 0.f)
		{
			m_shape->calculateLocalInertia(weight, localInertia);
		}

		startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));

		m_motionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(weight, m_motionState, m_shape, localInertia);
		btRigidBody * body = new btRigidBody(rbInfo);
		m_world.AddRigidBody(body);
	}

	int GetWorldIndex() const
	{
		return m_worldIndex;
	}

private:
	CPhysWorld & m_world;
	btCollisionShape * m_shape = nullptr;
	btRigidBody * m_body = nullptr;

	btDefaultMotionState * m_motionState = nullptr;

	int m_worldIndex = -1;
};

class CTransform3D
{
public:
	CTransform3D()
	{

	}

	void SetSizeScale(const glm::vec3 & scale)
	{
		m_sizeScale = scale;
	}

	void SetPosition(const glm::vec3 & pos)
	{
		m_position = pos;
	}

	void SetOrientation(const glm::quat & orientation)
	{
		m_orientation = orientation;
	}

	glm::mat4 ToMat4() const
	{
		const glm::mat4 scaleMatrix = glm::scale(glm::mat4(), m_sizeScale);
		const glm::mat4 rotationMatrix = glm::mat4_cast(m_orientation);
		const glm::mat4 translateMatrix = glm::translate(glm::mat4(), m_position);

		return translateMatrix * rotationMatrix * scaleMatrix;
	}

private:
	glm::vec3 m_sizeScale;
	glm::quat m_orientation;
	glm::vec3 m_position;
};

class CSphereEntity
	:public CPhysSphere
	,public CIdentitySphere
	,public CTransform3D
{
public:
	CSphereEntity(CPhysWorld & world, float radius, const glm::vec3 & pos, float mass, unsigned slices, unsigned stacks)
		:CIdentitySphere(slices, stacks)
		,CPhysSphere(world, radius, pos, mass)
	{
		SetSizeScale(glm::vec3(radius, radius, radius));
		SetPosition(pos);
		SetOrientation(glm::quat());
	}
};

class CCubeEntity
	:public CPhysBox
	,public CIdentityCube
	,public CTransform3D
{
public:
	CCubeEntity(CPhysWorld & world, float size, const glm::vec3 & pos, float mass)
		:CPhysBox(world, glm::vec3(size, size, size), pos, mass)
	{
		SetSizeScale(glm::vec3(size, size, size));
		SetPosition(pos);
		SetOrientation(glm::quat());
	}
};
