#include "RectangleCollider.h"

namespace SFMLGame{
	RectangleCollider::RectangleCollider(spTransformable& parent):PolygonCollider(parent){}

	unsigned int RectangleCollider::getPointCount(){return 4;}

	sf::Vector2f RectangleCollider::getPointInternal(unsigned int index){
		switch (index)
		{
		default:
			break;
		case 0:
			return sf::Vector2f(-_size.x/2,-_size.y/2);
		case 1:
			return sf::Vector2f(_size.x/2,-_size.y/2);
		case 2:
			return sf::Vector2f(_size.x/2,_size.y/2);
		case 3:
			return sf::Vector2f(-_size.x/2,_size.y/2);
		}
		return sf::Vector2f();
	}

	void RectangleCollider::setSize(sf::Vector2f size){
		_size = size;
		update();
	}

	sf::Vector2f RectangleCollider::getSize(){
		return _size;
	}


};