#ifndef VECTOR2UTIL_H
#define VECTOR2UTIL_H

#include <SFML/System/Vector2.hpp>
#include <math.h>

#define PI 3.141592654

namespace Vector2{

	template<class T, class U>
	float distance(const sf::Vector2<T>& a, const sf::Vector2<U>& b){
		return sqrtf( distanceSqrt<T,U>(a,b) );
	}

	template<class T, class U>
	float distanceSqrt(const sf::Vector2<T>& a, const sf::Vector2<U>& b){
		float x = a.x - b.x;
		float y = a.y - b.y;
		return  x * x + y * y;
	}

	template<class T, class U>
	float dot(const sf::Vector2<T>& a, const  sf::Vector2<U> & b){
		return a.x*b.x+a.y*b.y;
	}

	template<class T, class U>
	sf::Vector2f cross(const sf::Vector2<T> & a, const sf::Vector2<T> & b){
		return sf::Vector2f(a.x*b.y, a.y*b.x);
	}

	template<class T>
	float angleDeg(const sf::Vector2<T> & a){
		float angle = atan2f(a.x, a.y)*(180/PI);
		if( angle < 0)
			angle += 360;
		return angle;
	}

	template<class T>
	float angleRad(const sf::Vector2<T> & a){
		float angle = atan2f(a.y, a.x);
		if(angle < 0)
			angle += 2*PI;
		return  angle;
	}

	template<class T, class U>
	float angleBetweenDeg(const sf::Vector2<T> & a, const sf::Vector2<U> & b){
		float db = angleDeg(b);
		float da = angleDeg(a);

		float angle = da - db;

		return angle < 0 ? angle + 360 : angle;
	}

	template<class T, class U>
	float angleBetweenRad(const sf::Vector2<T> & a, const sf::Vector2<U> & b){
		float db = angleRad(b);
		float da = angleRad(a);

		float angle = da - db;

		return angle < 0 ? (angle + 2*PI) : angle;
	}

	template<class T>
	sf::Vector2f Normalize(const sf::Vector2<T> &a){
		float m = Magnitude(a);
		if(m == 0)
			return sf::Vector2f();
		return sf::Vector2f(a.x/m, a.y/m);
	}

	template<class T>
	float Magnitude(const sf::Vector2<T> & a){
		return sqrtf(a.x*a.x+a.y*a.y);
	}

	template<class T> 
	sf::Vector2<T> Normal(const sf::Vector2<T> & a){
		return sf::Vector2<T>(a.y, -a.x);
	}

	template<class T>
	sf::Vector2<T> scale(const sf::Vector2<T>& a, const float scale){
		return sf::Vector2<T>(a.x*scale, a.y*scale);
	}
};

#endif