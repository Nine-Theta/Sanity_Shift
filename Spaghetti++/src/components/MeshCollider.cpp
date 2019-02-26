#include "components/CircleCollider.h"
#include "vec2.hpp"
#include "BoxCollider.h"
#include "MeshCollider.h"
#include "MeshComponent.h"

namespace sge {
	MeshCollider::MeshCollider(std::string mesh, float pMass) : mass(pMass)
	{
		cmesh = AssetLoader::GetMesh(mesh);
	}
	MeshCollider::MeshCollider(float pMass) : mass(pMass)
	{
	}
	MeshCollider::~MeshCollider()
	{
		destroyCollider();
	}
	btTriangleIndexVertexArray * MeshCollider::meshToBT(Mesh * mesh)
	{
		std::vector<unsigned> indices = mesh->GetIndices();
		std::vector<vec3> verts = mesh->GetVertices();
		int* indexArr = (int*)&indices[0];
		btScalar* vertArr = new btScalar[verts.size() * 3];
		for (int i = 0; i < verts.size(); i+=3) {
			vertArr[i] = verts[i / 3].x;
			vertArr[i+1] = verts[i / 3].y;
			vertArr[i+2] = verts[i / 3].z;
		}
		btTriangleIndexVertexArray* arr = new btTriangleIndexVertexArray((int)indices.size() / 3, indexArr, (int)(3 * sizeof(unsigned int)), (int)verts.size() * 3, vertArr, (int)sizeof(vec3));
		return arr;
	}
	btTriangleMesh * MeshCollider::meshToBTSlow(Mesh * mesh)
	{
		btTriangleMesh* tMesh = new btTriangleMesh();
		std::vector<unsigned> indices = mesh->GetIndices();
		std::vector<vec3> verts = mesh->GetVertices();
		for (int i = 0; i < indices.size(); i+=3) {
			tMesh->addTriangle(Physics::glmToBullet(verts[indices[i]]), Physics::glmToBullet(verts[indices[i + 1]]), Physics::glmToBullet(verts[indices[i + 2]]), true);
		}
		std::cout << "Converted a GL mesh to a mesh collider with tri count: " << indices.size() / 3 << std::endl;
		return tMesh;
	}

	void MeshCollider::makeCollider() {
		if (cmesh == NULL) {
			MeshComponent* comp = (MeshComponent*)p_gameObj->GetComponent(typeid(MeshComponent));
			if (comp == NULL) {
				std::cout << "WARNING: ATTEMPTED TO ADD A MESH COLLIDER WITHOUT MESH TO AN OBJECT! This is a waste of resources and won't collide\n";
				meshArray = new btTriangleIndexVertexArray();
			}
			else {
				cmesh = comp->GetMesh();
				meshArray = meshToBTSlow(cmesh);
			}
		}
		else
			meshArray = meshToBTSlow(cmesh);
		mass = 0.f;
		shape = new btBvhTriangleMeshShape(meshArray, true);
		shape->setMargin(0.07f);
		transform = Physics::glmToBullet(p_gameObj->GetCombinedTransform());

		btVector3 inertia(0, 0, 0);
		if (mass > 0.f)
			shape->calculateLocalInertia(mass, inertia);

		motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
		rbody = new btRigidBody(rbInfo);
		rbody->setRestitution(.8f);
		rbody->setFriction(0.3f);
		Physics::AddBody(rbody);
		p_gameObj->SetWorldTransform(Physics::bulletToGlm(rbody->getWorldTransform()));
	}

	void MeshCollider::destroyCollider()
	{
		Physics::RemoveBody(rbody);
		delete rbody;
		delete shape;
		delete motionState;
		delete meshArray;
	}

	void MeshCollider::Start()
	{
		makeCollider();
	}
	void MeshCollider::OnDestroy()
	{
	}
	void MeshCollider::Update()
	{
	}
	void MeshCollider::FixedUpdate()
	{
		//btTransform trans = rbody->getWorldTransform();
//		mat4 glTrans = Physics::bulletToGlm(trans);
		//glTrans[0] = trans.
//		p_gameObj->SetWorldTransform(glTrans);
	}
	void MeshCollider::OnRender()
	{
	}
	void MeshCollider::OnCollision(Collider * other)
	{
	}
	void MeshCollider::OnTrigger(Collider * other)
	{
	}
}