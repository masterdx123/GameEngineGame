#pragma once

class Vector2 {
public:
	Vector2(float x_, float y_) : x(x_), y(y_) {}
	float x;
	float y;

	Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator*(const Vector2& other) const {
		return Vector2(x * other.x, y * other.y);
	}

	Vector2 operator/(const Vector2& other) const {
		return Vector2(x / other.x, y / other.y);
	}

	bool operator==(const Vector2& other) const {
		return (x == other.x && y == other.y);
	}

	bool operator!=(const Vector2& other) const {
		return !(*this == other);
	}

	Vector2& operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& operator*=(const Vector2& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vector2& operator/=(const Vector2& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}



};