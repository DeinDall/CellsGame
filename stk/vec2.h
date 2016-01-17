#ifndef STK_VEC2_H
#define STK_VEC2_H

#include <SFML/System.hpp>

namespace stk {

class vec2 : public sf::Vector2f {
public:
	vec2();
	vec2(const sf::Vector2f& vec);
	vec2(float xx, float yy);

	float len();
	float lenSq();
	void normalize();

	vec2 normalized();

	static float len(const sf::Vector2f& v);
	static float lenSq(const sf::Vector2f& v);
	static void normalize(sf::Vector2f& v);
};

float operator * (const sf::Vector2f& a, const sf::Vector2f& b);
sf::Vector2f operator / (float left, const sf::Vector2f& right);

} // namespace stk

#endif // STK_VEC2_H
