#pragma once
#include "bullet/btBulletDynamicsCommon.h"
//#include "GameObject.h"

//#include "components/ObjectBehaviour.h"
#include <map>
#include <string>
#include <iterator>
#include <unordered_map>



namespace sge {

	class AbstractCollider;



	struct ColliderPair {
		AbstractCollider* colA;
		AbstractCollider* colB;
		bool trigger;

		bool operator==(const ColliderPair& other) const{
			return (int)colA + (int)colB == (int)other.colA + (int)other.colB;
		}
		bool operator<(const ColliderPair& other) const{
			return (int)colA + (int)colB < (int)other.colA + (int)other.colB;
		}

		size_t operator()(const ColliderPair& k) const
		{
			// Compute individual hash values for two data members and combine them using XOR and bit shifting
			return (int)k.colA + (int)+k.colB;
		}
	};

	struct collider_hash
	{
		size_t operator()(const ColliderPair& k) const
		{
			// Compute individual hash values for two data members and combine them using XOR and bit shifting
			return (int)k.colA + (int)+k.colB;
		}
	};

	inline size_t hashCols(const ColliderPair& k) 
	{
		// Compute individual hash values for two data members and combine them using XOR and bit shifting
		return (int)k.colA + (int)+k.colB;
	}
	
	struct Collision {
		AbstractCollider*	collider;
		AbstractCollider*	otherCollider;
//		vec3				appliedForce;
		bool trigger;
		unsigned			contactPoints;
	};

	struct RaycastHit {
		glm::vec3 point;
		glm::vec3 normal;
		bool hit;
		AbstractCollider* collider;
	};
	class Physics
	{
	public:
		Physics();
		~Physics();
		static void Init();
		static int AddBody(btRigidBody* body);
		static void RemoveBody(btRigidBody* body);
		static int AddCollision(btCollisionObject* obj);
		static btTransform GetTransform(int id);
		static void Update(float dt);

		//static std::vector<RaycastHit> RaycastAll(vec3 dir);
		static RaycastHit Raycast(glm::vec3 start, glm::vec3 dir, float length = 0);

		static glm::mat4 bulletToGlm(const btTransform& t) {
			glm::mat4 m;
			const btMatrix3x3& basis = t.getBasis();
			// rotation
			for (int r = 0; r < 3; r++)
			{
				for (int c = 0; c < 3; c++)
				{
					m[c][r] = basis[r][c];
				}
			}
			// traslation
			btVector3 origin = t.getOrigin();
			m[3][0] = origin.getX();
			m[3][1] = origin.getY();
			m[3][2] = origin.getZ();
			// unit scale
			m[0][3] = 0.0f;
			m[1][3] = 0.0f;
			m[2][3] = 0.0f;
			m[3][3] = 1.0f;
			return m;
		}
		// btTransform does not contain a full 4x4 matrix, so this transform is lossy.
		// Affine transformations are OK but perspective transformations are not.
		static btTransform glmToBullet(const glm::mat4& m)
		{
			glm::mat3 m3(m);
			return btTransform(glmToBullet(m3), glmToBullet(glm::vec3(m[3][0], m[3][1], m[3][2])));
		}
		static btMatrix3x3 glmToBullet(const glm::mat3& m) { return btMatrix3x3(m[0][0], m[1][0], m[2][0], m[0][1], m[1][1], m[2][1], m[0][2], m[1][2], m[2][2]); }
		static btVector3 glmToBullet(const glm::vec3& v) { return btVector3(v.x, v.y, v.z); }

	private:
		static btDefaultCollisionConfiguration* collisionConfig;
		static btCollisionDispatcher* dispatcher;
		static btBroadphaseInterface* overlappingPairCache;
		static btSequentialImpulseConstraintSolver* solver;
		static btDiscreteDynamicsWorld* world;

		static void updateCollisions();
		//typedef std::pair<AbstractCollider*, AbstractCollider*> ColliderPair;
		/*struct hash_colliderpair {
			size_t operator() (const ColliderPair &pColliderPair) const
			{
				return (int)pColliderPair.first + (int)+pColliderPair.second;
			}
		};*/
		static std::unordered_map<ColliderPair, int, collider_hash> _collisionPairs;
		static std::unordered_map<AbstractCollider*, int> _colliders;

		//static bool customContactDestroyedCallback(void* userData);
		//static bool customContactAddedCallback(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1);
	};

}