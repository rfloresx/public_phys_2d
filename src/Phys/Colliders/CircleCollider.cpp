#include "CircleCollider.h"

namespace SFMLGame{

	CircleCollider::CircleCollider(spTransformable& parent) : Collider(parent), _radius(0), _pointCount(30),_scale(1,1){}

	void CircleCollider::setRadius(float r){
		_radius = r;
		update();
	}

	float CircleCollider::getRadius(){return _radius;}

	float CircleCollider::getRadius(float a){
		if(_scale.x == _scale.y)
			return _radius*_scale.x;
		return sqrtf(getRadiusSQ(a));
	}

	float CircleCollider::getRadiusSQ(float a){
		if(_scale.x == _scale.y)
			return _radius*_radius*_scale.x*_scale.x;

		float x = _scale.x * std::cos(a) * _radius;
		float y = _scale.y * std::sin(a) * _radius;

		return x*x+y*y;
	}

	void CircleCollider::setScale(float x, float y){
		_scale = sf::Vector2f(x,y);
		update();
	}

	sf::Vector2f CircleCollider::getScale(){return _scale;}

	void CircleCollider::setPointCount(unsigned int count){
		_pointCount = count;
		update();
	}

	unsigned int CircleCollider::getPointCount(){
		return _pointCount;
	}

	sf::Vector2f CircleCollider::getPointInternal(unsigned int index){
		float angle = (index * 2 * PI )/_pointCount - PI / 2;
		float x = _scale.x * std::cos(angle) * _radius;
		float y = _scale.y * std::sin(angle) * _radius;

		return sf::Vector2f(x, y);
	}
};