#ifndef PHYSICS2D_H
#define PHYSICS2D_h

//#include "Colliders/CircleCollider.h"
#include "../Util/instrusive_ptr.h"
#include "../Util/Vector2Util.h"
#include "../Util/List.h"

#include "Colliders.h"

namespace SFMLGame{
	DECLARE_SMART(CollisionInfo, spCollisionInfo);
	class CollisionInfo : public ref_counter{
	public:
		spCollider Collider1;
		spCollider Collider2;
		float Distance;
		sf::Vector2f Direction;

		CollisionInfo():Collider1(0),Collider2(0),Distance(0),Direction(0,0){}
	};

	DECLARE_SMART(PhysicsHandler, spPhysicsHandler);
	class PhysicsHandler :public ref_counter {
	public:
		virtual void HandleCollision(spCollider & obj1, spCollider & obj2, spCollisionInfo & info) = 0;
		virtual void HandleTrigger(spCollider & obj1, spCollider & obj2, spCollisionInfo & info) = 0;
	};

	DECLARE_SMART(Physics2D, spPhysics2D);
	class Physics2D : public ref_counter{
	private:


		///////////////////////////
		//static internal functions
		///////////////////////////
		struct Result{
			 float dist;
			 spCollisionInfo info;
			 Result(float d, spCollisionInfo i):dist(d), info(i){}
		};

		static sf::Vector2f getAxisNormal(const std::vector<sf::Vector2f>& poly, int index);
		static sf::Vector2f getMinMax(sf::Vector2f axis, const std::vector<sf::Vector2f>& points);
		static sf::Vector2f getMinMax(sf::Vector2f axis, const spCircleCollider& circle);
		static Result makeResult(const spCollisionInfo old, float min0, float max0, float min1, float max1,sf::Vector2f axis);
		
		////////////////////////////////////
		//std::vector<spCollider> _objects;
		//std::vector<spCollider> _toRemove;
		//std::vector<spCollider> _objects;
		//std::vector<spCollider> _toRemove;
		List<spCollider> _objects;
		List<spCollider> _toRemove;

		List<spPhysicsHandler> _handlers;

		void updateList();
		
		void handleCollision(spCollider & a, spCollider & b);

		void callOnTrigger(spCollider & obj1, spCollider & obj2, spCollisionInfo & info);

		void callOnCollision(spCollider & obj1, spCollider & obj2, spCollisionInfo & info);

	public:
		
		void registerHandler(spPhysicsHandler obj);

		void unregisterHandler(spPhysicsHandler obj);

		void add(spCollider & obj);

		void remove(spCollider & obj);

		void update();
		
		void draw(sf::RenderTarget & target){
			for(int i = 0; i < _objects.size(); i++){
				target.draw( (*_objects[i]) );
			}
		}
		
		static bool CheckAABBOverlap(const spCollider& a, const spCollider& b);

		static spCollisionInfo TestCollision(const spCollider& a, const spCollider& b);
		
		static spCollisionInfo TestCircleCircle(const spCircleCollider& c1, const spCircleCollider& c2);

		static spCollisionInfo TestPolygonSat(const spPolygonCollider& poly1, const spPolygonCollider& poly2);

		static spCollisionInfo TestCirclePolygonSat(const spCircleCollider& circle, const spPolygonCollider& polygon);

	};

};


#endif