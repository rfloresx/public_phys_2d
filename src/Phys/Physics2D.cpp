#include "Physics2D.h"

#define INF 1000000000.0f

namespace SFMLGame{
	
	void Physics2D::callOnTrigger(spCollider & obj1, spCollider & obj2, spCollisionInfo & info){
		for(int i = 0; i < _handlers.size(); i++){
			_handlers[i]->HandleTrigger(obj1, obj2, info);
		}
	}

	void Physics2D::callOnCollision(spCollider & obj1, spCollider & obj2, spCollisionInfo & info){
		for(int i = 0; i < _handlers.size(); i++){
			_handlers[i]->HandleCollision(obj1, obj2, info);
		}
	}

	void Physics2D::registerHandler(spPhysicsHandler obj){
		_handlers.Add(obj);
	}

	void Physics2D::unregisterHandler(spPhysicsHandler obj){
		_handlers.Remove(obj);
	}

	void Physics2D::updateList(){
		for(int i = 0; i < _toRemove.size(); i++){
			_objects.Remove(_toRemove[i] );
		}
		_toRemove.clear();
	}
		
	void Physics2D::handleCollision(spCollider & obj1, spCollider & obj2){
		if(obj1->isStationary && obj2->isStationary )
			return;
		spCollisionInfo info = TestCollision(obj1, obj2);
		
		float dist = .01f;

		if(info){
			if(obj1->isTrigger || obj2->isTrigger){
				if(obj1->isTrigger && obj2->isTrigger)
					return;
				else
					callOnTrigger(obj1, obj2, info);
			}else{
				spCollider o1 = info->Collider1;
				spCollider o2 = info->Collider2;

				if(o1->isStationary){
					sf::Vector2f move = info->Direction * (-(info->Distance + dist) );
					info->Collider2->getTransform()->move(move);
				}else if(o2->isStationary){
					sf::Vector2f move = info->Direction * ((info->Distance + dist) );
					info->Collider1->getTransform()->move(move);
				}else{
					sf::Vector2f move = info->Direction*( (info->Distance + dist)/2);
					info->Collider1->getTransform()->move(move);
					info->Collider2->getTransform()->move(-move.x, -move.y);
				}
				//handleCollision(obj1, obj2, info);
				callOnCollision(o1, o2, info);
			}
		}

		/*
                if not obj1.isStationary or not obj2.isStationary:
                    if obj1.isStationary:
                        move = info.direction.scale(info.distance + dis)
                        info.collider2.position = info.collider2.position.add(move.scale(-1))
                    elif obj2.isStationary:
                        move = info.direction.scale(info.distance + dis)
                        info.collider1.position = info.collider1.position.add(move)
                    else:
                        move = info.direction.scale((info.distance + dis) / 2)
                        info.collider1.position = info.collider1.position.add(move)
                        info.collider2.position = info.collider2.position.add(move.scale(-1))
                PhysUtility.HandleCollision(obj1, obj2, info)
                self.callOnCollision(obj1, obj2, info)

		*/
	}

	void Physics2D::add(spCollider & obj){
		if(!_objects.Contains(obj))
			_objects.Add(obj);
	}

	void Physics2D::remove(spCollider & obj){
		_objects.Remove(obj);
	}

	void Physics2D::update(){
		updateList();
		int size = _objects.size();
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				handleCollision(_objects[i], _objects[j] );
			}
		}
	}


	sf::Vector2f Physics2D::getAxisNormal(const std::vector<sf::Vector2f>& poly, int index){
		sf::Vector2f p1 = poly[index];
		int i2 = (index+1) < poly.size() ? (index + 1) : 0;
		sf::Vector2f p2 = poly[i2];

		return Vector2::Normalize( Vector2::Normal(p2 - p1) );
	}

	sf::Vector2f Physics2D::getMinMax(sf::Vector2f axis, const std::vector<sf::Vector2f>& points){

		float min = Vector2::dot(axis, points[0]);
		float max = min;
		for(int i = 1; i < points.size(); i++){
			float t = Vector2::dot(axis, points[i]);
			if(t < min)
				min = t;
			if(t > max)
				max = t;
		}

		return sf::Vector2f(min,max);
	}

	sf::Vector2f Physics2D::getMinMax(sf::Vector2f axis, const spCircleCollider& circle){
		float ang = Vector2::angleRad(axis);
		float r = circle->getRadius(ang);
		float min1 = Vector2::dot(axis, circle->getCenter());
		float max1 = min1 + r;
		min1 = min1 - r;
		return sf::Vector2f(min1,max1);
	}

	Physics2D::Result Physics2D::makeResult(const spCollisionInfo old, float min0, float max0, float min1, float max1,sf::Vector2f axis){
		
		if (max0 < min1)
			return Result(0, NULL);
		if (max1 < min0)
			return Result(0, NULL);

		spCollisionInfo info = new CollisionInfo();
		info->Collider1 = old->Collider1;
		info->Collider2 = old->Collider2;

		float distmin;
		if(min0 < min1){
			distmin = min1 - max0;

			axis *= -1.0f;
		}else{
			distmin = min0 - max1;
		}

		float distminAbs = distmin < 0 ? -distmin : distmin;
		info->Distance = distminAbs;

		if(distmin < 0)
			info->Direction = Vector2::Normalize(axis);
		else
			info->Direction = Vector2::Normalize( Vector2::scale(axis, -1) );
    
		return Result(distminAbs, info);
	}

	bool Physics2D::CheckAABBOverlap(const spCollider& a, const spCollider& b){
		return a->getGlobalAABB().intersects(b->getGlobalAABB());
	}

	spCollisionInfo Physics2D::TestCollision(const spCollider& a, const spCollider& b){
		if(CheckAABBOverlap(a,b)){
			if(a->getType() == b->getType()){
				if(a->getType() == ColliderType::Circle)
					return TestCircleCircle(dynamic_pointer_cast<CircleCollider>(a), dynamic_pointer_cast<CircleCollider>(b));
				if(a->getType() == ColliderType::PolySat)
					return TestPolygonSat( dynamic_pointer_cast<PolygonCollider>(a), dynamic_pointer_cast<PolygonCollider>(b));
				return NULL;
			}
			if(a->getType() == ColliderType::Circle){
				return TestCirclePolygonSat(dynamic_pointer_cast<CircleCollider>(a), dynamic_pointer_cast<PolygonCollider>(b));
			}
			return TestCirclePolygonSat(dynamic_pointer_cast<CircleCollider>(b), dynamic_pointer_cast<PolygonCollider>(a));
		}

		return spCollisionInfo();
	}
		
	spCollisionInfo Physics2D::TestCircleCircle(const spCircleCollider& c1, const spCircleCollider& c2){
		
		sf::Vector2f center1 = c1->getCenter();
		sf::Vector2f center2 = c2->getCenter();
		sf::Vector2f left(1,0);

		
		float ang1 = Vector2::angleRad(center2-center1);//Vector2::angleBetweenRad(left, center2 - center1);
		//float ang2 = Vector2::angleBetweenRad(left, center1 - center2);
		float totalRad = c1->getRadius(ang1) + c2->getRadius(ang1);
		float disqs = Vector2::distanceSqrt(center1, center2);
		if(disqs > totalRad*totalRad)
			return NULL;
		spCollisionInfo info = new CollisionInfo();
		info->Collider1 = c1;
		info->Collider2 = c2;
		info->Direction = Vector2::Normalize(center2 - center1);
		info->Distance = sqrtf(disqs) - totalRad;
		return info;
	}

	spCollisionInfo Physics2D::TestPolygonSat(const spPolygonCollider& poly1, const spPolygonCollider& poly2){
		float shorterDist = INF;
		spCollisionInfo result = new CollisionInfo;
		result->Collider1 = poly1;
		result->Collider2 = poly2;

		std::vector<sf::Vector2f> p1 = poly1->getPoints();
		std::vector<sf::Vector2f> p2 = poly2->getPoints();

		for(int i = 0; i < p1.size(); i++){

			sf::Vector2f vAxis = getAxisNormal(p1, i);

			sf::Vector2f MinMax0 = getMinMax(vAxis, p1);

			sf::Vector2f MinMax1 = getMinMax(vAxis, p2);

			Result _new = makeResult(result, MinMax0.x, MinMax0.y, MinMax1.x, MinMax1.y, vAxis);
			if(_new.dist <= shorterDist){
				shorterDist = _new.dist;
				if( _new.info == NULL)
					return NULL;
				result = _new.info;
			}
		}
		for(int i = 0; i < p2.size(); i++){

			sf::Vector2f vAxis = getAxisNormal(p2, i);

			sf::Vector2f MinMax0 = getMinMax(vAxis, p1);

			sf::Vector2f MinMax1 = getMinMax(vAxis, p2);

			Result _new = makeResult(result, MinMax0.x, MinMax0.y, MinMax1.x, MinMax1.y, vAxis);
			if(_new.dist <= shorterDist){
				shorterDist = _new.dist;
				if( _new.info == NULL)
					return NULL;
				result = _new.info;
			}
		}
		return result;
	}

	spCollisionInfo Physics2D::TestCirclePolygonSat(const spCircleCollider& circle, const spPolygonCollider& polygon){
		float dist = INF;
		float shorterDist = INF;
		sf::Vector2f closestPoint;
		float currDist;

		spCollisionInfo result = new CollisionInfo();
		result->Collider1 = polygon;
		result->Collider2 = circle;

		std::vector<sf::Vector2f> p1 = polygon->getPoints();
		sf::Vector2f center = circle->getCenter();

		for(int i = 0; i< p1.size(); i++){
			currDist = Vector2::distance(p1[i], center);
			if(currDist < dist){
				dist = currDist;
				closestPoint = p1[i];
			}
		}
		sf::Vector2f vAxis = Vector2::Normalize(center - closestPoint);

		sf::Vector2f MinMax0 = getMinMax(vAxis, p1);

		sf::Vector2f MinMax1 = getMinMax(vAxis, circle);

		Result _new = makeResult(result, MinMax0.x, MinMax0.y, MinMax1.x, MinMax1.y, vAxis);
		if(_new.dist <= shorterDist){
			shorterDist = _new.dist;
			if( _new.info == NULL)
				return NULL;
			result = _new.info;
		}

		for(int i = 0; i < p1.size(); i++){

			vAxis = getAxisNormal(p1, i);

			MinMax0 = getMinMax(vAxis, p1);

			MinMax1 = getMinMax(vAxis, circle);

			_new = makeResult(result, MinMax0.x, MinMax0.y, MinMax1.x, MinMax1.y, vAxis);
			if(_new.dist <= shorterDist){
				shorterDist = _new.dist;
				if( _new.info == NULL)
					return NULL;
				result = _new.info;
			}
		}

		return result;
	}

};
