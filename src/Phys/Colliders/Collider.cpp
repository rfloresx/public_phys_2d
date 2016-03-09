#include "Collider.h"

namespace SFMLGame{
	Collider::Collider(spTransformable& parent):_transform(parent),_aabb(0,0,0,0), _color(0,100,0,255){
		_vertices.setPrimitiveType(sf::PrimitiveType::LinesStrip);
	}

	spTransformable Collider::getTransform(){return _transform;}
	
	sf::FloatRect Collider::getLocalAABB(){
		return _aabb;
	}

	sf::FloatRect Collider::getGlobalAABB(){
		return _transform->getTransform().transformRect(_aabb);
	}

	void Collider::setOffset(sf::Vector2f offset){
		_offSet = offset;
		update();
	}

	sf::Vector2f Collider::getCenter(){
		sf::Vector2f center( _aabb.left+_aabb.width/2, _aabb.top+_aabb.height/2);

		return _transform->getTransform().transformPoint(center);
	}

	sf::Vector2f Collider::getOffset(){return _offSet;}

	sf::Vector2f Collider::getPoint(unsigned int index){
		return _offSet+ getPointInternal(index);
	}

	std::vector<sf::Vector2f> Collider::getPoints(){
		std::vector<sf::Vector2f> points;
		points.resize(getPointCount());
		for(int i = 0; i < getPointCount(); i++){
			points[i] = _transform->getTransform().transformPoint( getPoint(i) );
		}
		return points;
	}

	/*
	bool Collider::isStationary(){return _isStationary;}

	void Collider::isStationary(bool newVal){_isStationary = newVal;}

	bool Collider::isTrigger(){return _isTrigger;}
	void Collider::isTrigger(bool val){_isTrigger = val;}
	*/

	void Collider::update(){
		unsigned int count = getPointCount();

		if (count < 2){
			_vertices.resize(0);
			return;
		}

		_vertices.resize(count + 1); // repeated first point

		// Position
		for (unsigned int i = 0; i < count; ++i)
			_vertices[i].position = getPoint(i);

		_vertices[count] = _vertices[0];

		_aabb = _vertices.getBounds();
		
		for(unsigned int i = 0; i < _vertices.getVertexCount(); i++){
			_vertices[i].color = _color;
		}
	}

	void Collider::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		states.transform *= _transform->getTransform();
		target.draw(_vertices, states);
	}

};