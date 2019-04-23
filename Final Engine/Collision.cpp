#include "Collision.h"

namespace Collision {
	bool detected = false;

	bool collisionDetection(Entity* ent1, Entity* ent2)
	{

		bool p1collision_z = (ent1->getPosition().z - ent1->getCollisionBox().z) > (ent2->getPosition().z - ent2->getCollisionBox().z) &&
							 (ent1->getPosition().z - ent1->getCollisionBox().z) < (ent2->getPosition().z + ent2->getCollisionBox().z);
		
		bool p2collision_z = (ent1->getPosition().z + ent1->getCollisionBox().z) > (ent2->getPosition().z - ent2->getCollisionBox().z) &&
							 (ent1->getPosition().z + ent1->getCollisionBox().z) < (ent2->getPosition().z + ent2->getCollisionBox().z);
		
		bool p1collision_y = (ent1->getPosition().y - ent1->getCollisionBox().y) > (ent2->getPosition().y - ent2->getCollisionBox().y) &&
							 (ent1->getPosition().y - ent1->getCollisionBox().y) < (ent2->getPosition().y + ent2->getCollisionBox().y);
		
		bool p2collision_y = (ent1->getPosition().y + ent1->getCollisionBox().y) > (ent2->getPosition().y - ent2->getCollisionBox().y) &&
							 (ent1->getPosition().y + ent1->getCollisionBox().y) < (ent2->getPosition().y + ent2->getCollisionBox().y);
		
		if ((p1collision_y || p2collision_y) && (p1collision_z || p2collision_z))
		{
			detected = true;
		}
		else detected = false;

		return detected;
	}


	bool returnDetected()
	{
		return detected;
	}
}
