#ifndef POLYGONCOLLIDER_H
#define POLYGONCOLLIDER_H

#include "Collider.h"

namespace SFMLGame{

	DECLARE_SMART(PolygonCollider, spPolygonCollider);
	class PolygonCollider : public Collider{
	public:
		PolygonCollider(spTransformable& parent);

		void setPointCount(unsigned int count);

		virtual unsigned int getPointCount();

		void setPoint(unsigned int index, const sf::Vector2f& point);

		virtual sf::Vector2f getPointInternal(unsigned int index);

		void setPoints( const std::vector<sf::Vector2f>&  points);

		virtual ColliderType getType(){return ColliderType::PolySat;}

	private:
		std::vector<sf::Vector2f> _points;

	};

};

#endif