//
// Created by Ngan Nguyen on 3/18/18.
//

#ifndef GRAPHICS2D_VECTOR2D_H
#define GRAPHICS2D_VECTOR2D_H
#include <cmath>
#include <iostream>


class Vector2D {
public:
	static const int NUM_COMPONENTS = 2;

	/**
	* Coordinates of the vector
	*/
	double x, y;

	/**
	* Inline constructor
	* @param _x X coordinate
	* @param _y Y coordinate
	*/
	Vector2D(double _x, double _y) {
		x = _x;
		y = _y;
	}
	/**
	* Copy constructor
	* @param v Vector
	*/
	Vector2D(const Vector2D& v) {
		x = v.x;
		y = v.y;
	}

	/**
	* Uniform Value Constructor
	* @param f Value
	*/
	Vector2D(double f) {
		this->x = f;
		this->y = f;
	}

	/**
	* Zero Vector constructor
	*/
	Vector2D() {
		x = 0;
		y = 0;
	}

	friend std::ostream& operator<< (std::ostream& stream, const Vector2D& vector)
	{
		std::cout << vector.x << "," << vector.y << std::endl;

		return stream;
	}

	/**
	* Inline setter
	* @param _x X coordinate
	* @param _y Y coordinate
	* @return this
	*/
	Vector2D& set(double _x, double _y) {
		x = _x;
		y = _y;
		return *this;
	}

	/**
	* Set this vector to uniform values
	* @param f Value
	* @return this
	*/
	Vector2D& set(double f) {
		return set(f, f);
	}

	/**
	* Set this vector to the zero vector
	* @return this
	*/
	Vector2D& setZero() {
		return set(0);
	}

	/**
	* Copy a vector into this vector
	* @param v Vector
	* @return this
	*/
	Vector2D& set(Vector2D& v) {
		return set(v.x, v.y);
	}

	/**
	* Sets this vector to a multiple of XYZ components
	* <pre>
	* This = s * {_x, _y}
	* </pre>
	* @param s Scalar
	* @param _x X component
	* @param _y Y component
	* @return this
	*/
	Vector2D& setMultiple(double s, double _x, double _y) {
		x = s * _x;
		y = s * _y;
		return *this;
	}

	/**
	* Sets this vector to its component wise prodt with another
	* <pre>
	* This = s * v
	* </pre>
	* @param s Scalar
	* @param v Vector
	* @return this
	*/
	Vector2D& setMultiple(double s, Vector2D v) {
		return setMultiple(s, v.x, v.y);
	}


	/**
	* In-place addition
	* <pre>
	* This = this + {_x, _y}
	* </pre>
	* @param _x X component
	* @param _y Y component
	* @return this
	*/
	Vector2D& add(double _x, double _y) {
		x += _x;
		y += _y;
		return *this;
	}

	/**
	* In-place addition
	* <pre>
	* This = this + v
	* </pre>
	* @param v Vector
	* @return this
	*/
	Vector2D& add(Vector2D v) {
		return add(v.x, v.y);
	}

	/**
	* In-place uniform addition
	* <pre>
	* This = this + {f, f}
	* </pre>
	* @param f Value
	* @return this
	*/
	Vector2D& add(double f) {
		return add(f, f);
	}

	/**
	* In-place scaled addition
	* <pre>
	* This = this + s * {_x, _y}
	* </pre>
	* @param s Scalar
	* @param _x X component
	* @param _y Y component
	* @return this
	*/
	Vector2D& addMultiple(double s, double _x, double _y) {
		x += s * _x;
		y += s * _y;
		return *this;
	}

	/**
	* In-place scaled addition
	* <pre>
	* This = this + s * v
	* </pre>
	* @param s Scalar
	* @param v Vector
	* @return this
	*/
	Vector2D& addMultiple(double s, Vector2D v) {
		return addMultiple(s, v.x, v.y);
	}

	/**
	* In-place subtraction
	* <pre>
	* This = this - {_x, _y}
	* </pre>
	* @param _x X component
	* @param _y Y component
	* @return this
	*/
	Vector2D& sub(double _x, double _y) {
		x -= _x;
		y -= _y;
		return *this;
	}

	/**
	* In-place subtraction
	* <pre>
	* This = this - v
	* </pre>
	* @param v Vector
	* @return this
	*/
	Vector2D& sub(Vector2D v) {
		return sub(v.x, v.y);
	}

	/**
	* In-place uniform subtraction
	* <pre>
	* This = this - {f, f}
	* </pre>
	* @param f Value
	* @return this
	*/
	Vector2D& sub(double f) {
		return sub(f, f);
	}

	/**
	* In-place scaled subtraction
	* <pre>
	* This = this - s * {_x, _y}
	* </pre>
	* @param s Scalar
	* @param _x X component
	* @param _y Y component
	* @return this
	*/
	Vector2D& subMultiple(double s, double _x, double _y) {
		x -= s * _x;
		y -= s * _y;
		return *this;
	}

	/**
	* In-place scaled subtraction
	* <pre>
	* This = this - s * v
	* </pre>
	* @param s Scalar
	* @param v Vector
	* @return this
	*/
	Vector2D& subMultiple(double s, Vector2D v) {
		return subMultiple(s, v.x, v.y);
	}

	/**
	* In-place component wise multiplication
	* <pre>
	* This = this * {_x, _y}
	* </pre>
	* @param _x X component
	* @param _y Y component
	* @param _z Z Component
	* @return this
	*/
	Vector2D& mul(double _x, double _y) {
		x *= _x;
		y *= _y;
		return *this;
	}

	/**
	* In-place component wise multiplication
	* <pre>
	* This = this * v
	* </pre>
	* @param v Vector
	* @return this
	*/
	Vector2D& mul(Vector2D v) {
		return mul(v.x, v.y);
	}

	/**
	* In-place uniform multiplication
	* <pre>
	* This = this * {f, f}
	* </pre>
	* @param f Value
	* @return this
	*/
	Vector2D& mul(double f) {
		return mul(f, f);
	}

	/**
	* In-place component wise division
	* <pre>
	* This = this / {_x, _y}
	* </pre>
	* @param _x X component
	* @param _y Y component
	* @return this
	*/
	Vector2D& div(double _x, double _y) {
		x /= _x;
		y /= _y;
		return *this;
	}

	/**
	* In-place division
	* <pre>
	* This = this / v
	* </pre>
	* @param v Vector
	* @return this
	*/
	Vector2D& div(Vector2D v) {
		return div(v.x, v.y);
	}

	/**
	* In-place uniform division
	* <pre>
	* This = this * {1 / f, 1 / f}
	* </pre>
	* @param f Value
	* @return this
	*/
	Vector2D& div(double f) {
		return mul(1 / f);
	}

	/**
	* In-place absolute value
	* @return this
	*/
	Vector2D& abs() {
		if (x < 0) x = -x;
		if (y < 0) y = -y;
		return *this;
	}

	/**
	* In-place negation
	* @return this
	*/
	Vector2D& negate() {
		x = -x;
		y = -y;
		return *this;
	}

	/**
	* Dot product between this and another vector
	* @param v [{@link Vector2d ARR}] Vector
	* @return Vector Dot Product
	*/
	double dot(Vector2D& v) {
		return x * v.x + y * v.y;
	}

	/**
	* This vector's dot product with itself
	* @return This vector's length squared
	*/
	double lenSq() {
		return dot(*this);
	}

	/**
	* Calculates the length
	* @return This vector's length
	*/
	double len() {
		return sqrt(lenSq());
	}

	/**
	* Calculates squared distance between this vector and another
	* @param v [{@link Vector2d POS}] Vector
	* @return Squared distance
	*/
	double distSq(Vector2D& v) {
		double ox = x - v.x;
		double oy = y - v.y;
		return ox * ox + oy * oy;
	}

	/**
	* Calculates distance between this vector and another
	* @param v [{@link Vector2d POS}] Vector
	* @return Distance
	*/
	double dist(Vector2D v) {
		return (double)sqrt(distSq(v));
	}

	/**
	* Calculate angle between this vector and another
	* @param v [{@link Vector2d DIRN}] Vector
	* @return Angle between vectors (radians)
	*/
	double angle(Vector2D v) {
		return acos(dot(v) / (len() * v.len()));
	}

	/**
	* In-place normalization to unit length
	* @return this
	*/
	Vector2D& normalize() {
		return mul(1 / len());
	}

	/**
	* Checks component equality between this vector and another
	* @param v Vector
	* @return True if all components equal
	*/
	bool equals(Vector2D v) {
		return x == v.x && y == v.y;
	}

	int size() {
		return NUM_COMPONENTS;
	}

};

#endif //GRAPHICS2D_VECTOR2D_H


