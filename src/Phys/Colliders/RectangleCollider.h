#ifndef RECTANGLECOLLIDER_H
#define RECTANGLECOLLIDER_H

#include "Collider.h"
#include "PolygonCollider.h"

namespace SFMLGame{

	DECLARE_SMART(RectangleCollider, spRectangleCollider);
	class RectangleCollider : public PolygonCollider{
	public:
		RectangleCollider(spTransformable& parent);

		virtual unsigned int getPointCount();

		virtual sf::Vector2f getPointInternal(unsigned int index);

		virtual ColliderType getType(){return ColliderType::PolySat;}

		void setSize(sf::Vector2f size);

		sf::Vector2f getSize();

	private:
		sf::Vector2f _size;

	};
};

#endif