#ifndef COLLIDER_H
#define COLLIDER_H

#include "../../Util/instrusive_ptr.h"
#include "../../SPDeclaration.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace SFMLGame{
	//typedef unsinged int uint;
	enum ColliderType{
		PolySat,
		Circle,
		NONE
	};

	DECLARE_SMART(Collider, spCollider);
	class Collider : public sf::Drawable, public ref_counter{
	protected:
		spTransformable _transform;
		sf::FloatRect _aabb;
		sf::Vector2f _offSet;

		sf::VertexArray _vertices;
		sf::Color _color;

		virtual sf::Vector2f getPointInternal( unsigned int index){return sf::Vector2f();}

	public:
		bool isTrigger;

		bool isStationary;

		/*
		bool isStationary();

		void isStationary(bool newVal);

		bool isTrigger();

		void isTrigger(bool trigger);
		*/

		Collider(spTransformable& parent);
		
		spTransformable getTransform();

		sf::FloatRect getLocalAABB();

		sf::FloatRect getGlobalAABB();

		void setOffset(sf::Vector2f offset);

		sf::Vector2f getOffset();

		sf::Vector2f getPoint(unsigned int index);
		
		sf::Vector2f getCenter();

		std::vector<sf::Vector2f> getPoints();

		

		virtual unsigned int getPointCount(){return 0;}

		virtual ColliderType getType(){return ColliderType::NONE;}

		virtual void update();

		//For debug
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	};

};

#endif
