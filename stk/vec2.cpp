#include "vec2.h"

namespace stk {

vec2::vec2() : vec2(0, 0) {}
vec2::vec2(const sf::Vector2f& vec) : vec2(vec.x, vec.y) {}
vec2::vec2(float xx, float yy) : sf::Vector2f(xx, yy) {}

float vec2::len() {
	return sqrtf(x*x+y*y);
}

float vec2::lenSq() {
	return x*x+y*y;
}

void vec2::normalize() {
	float invlen = 1.f/sqrtf(x*x+y*y);

	x *= invlen;
	y *= invlen;
}

vec2 vec2::normalized() {
	vec2 v(x, y);
	v.normalize();
	return v;
}

float vec2::len(const sf::Vector2f& v) {
	return sqrtf(v.x*v.x+v.y*v.y);
}

float vec2::lenSq(const sf::Vector2f& v) {
	return v.x*v.x+v.y*v.y;
}

void vec2::normalize(sf::Vector2f& v) {
	float invlen = 1.f/sqrtf(v.x*v.x+v.y*v.y);

	v.x *= invlen;
	v.y *= invlen;
}

float operator*(const sf::Vector2f& a, const sf::Vector2f& b) {
	return a.x*b.x + a.y*b.y;
}

sf::Vector2f operator / (float left, const sf::Vector2f& right) {
	return sf::Vector2f(left/right.x, left/right.y);
}

} // namespace stk

