#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "Collider.h"
#include "../../Util/Vector2Util.h"

namespace SFMLGame{

	DECLARE_SMART(CircleCollider, spCircleCollider);
	class CircleCollider : public Collider{
	protected:
		float _radius;
		sf::Vector2f _scale;

		unsigned int _pointCount;;
	public:
		CircleCollider(spTransformable&parent);

		void setRadius(float r);

		float getRadius();

		float getRadius(float a);

		float getRadiusSQ(float a);

		void setScale(float x, float y);

		sf::Vector2f getScale();

		void setPointCount(unsigned int size);

		virtual unsigned int getPointCount();

		virtual sf::Vector2f getPointInternal( unsigned int index);

		virtual ColliderType getType(){return ColliderType::Circle;}

	};


};

#endif