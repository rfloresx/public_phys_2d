#include "PolygonCollider.h"

namespace SFMLGame{

	PolygonCollider::PolygonCollider(spTransformable& parent):_points(0),Collider(parent){}

	void PolygonCollider::setPointCount(unsigned int count){
		_points.resize(count);
		update();
	}

	unsigned int PolygonCollider::getPointCount(){
		return _points.size();
	}

	void PolygonCollider::setPoint(unsigned int index, const sf::Vector2f& point){
		_points[index] = point;
		update();
	}

	sf::Vector2f PolygonCollider::getPointInternal(unsigned int index){
		return _points[index];
	}

	void PolygonCollider::setPoints( const std::vector<sf::Vector2f>&  points){
		_points.resize(points.size());
		for(unsigned int i =0; i < points.size(); i++){
			_points[i] = points[i];
		}
		update();
	}


};