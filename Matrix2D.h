#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <cmath>
#include <cassert>
#include <iostream>
#include "Vector2D.h"

#define _USE_MATH_DEFINES

class Matrix2D {
public:

	/**
	* Dimension Of A Row Or Column
	*/
	static const int SIZE = 3;
	/**
	* Number Of Elements (SIZE * SIZE)
	*/
	static const int ELEMENTS = SIZE * SIZE;
	/**
	* Array Containing The Elements
	*/
	double* const m = new double[ELEMENTS];

	/**
	* Inline Constructor
	* @param m00 Row 1 Col 1
	* @param m01 Row 1 Col 2
	* @param m02 Row 1 Col 3
	* @param m10 Row 2 Col 1
	* @param m11 Row 2 Col 2
	* @param m12 Row 2 Col 3
	* @param m20 Row 3 Col 1
	* @param m21 Row 3 Col 2
	* @param m22 Row 3 Col 3
	*/
	Matrix2D(
		double m00, double m01, double m02,
		double m10, double m11, double m12,
		double m20, double m21, double m22
	)
	{
		m[0] = m00;
		m[1] = m10;
		m[2] = m20;
		m[3] = m01;
		m[4] = m11;
		m[5] = m21;
		m[6] = m02;
		m[7] = m12;
		m[8] = m22;
	}


	/**
	* Array Constructor With Values Starting At Index 0
	* @param _m Array Of At Least ELEMENTS Length
	*/
	Matrix2D(double* _m) {
		for (int i = 0; i < ELEMENTS; i++) m[i] = _m[i];
	}
	/**
	* Copy Constructor
	* @param _m Matrix
	*/
	Matrix2D(Matrix2D& _m) {
		m[0] = _m.m[0];
		m[1] = _m.m[1];
		m[2] = _m.m[2];
		m[3] = _m.m[3];
		m[4] = _m.m[4];
		m[5] = _m.m[5];
		m[6] = _m.m[6];
		m[7] = _m.m[7];
		m[8] = _m.m[8];

	}

	/**
	* Identity Matrix Constructor
	*/
	Matrix2D() {
		m[0] = 1;
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;
		m[4] = 1;
		m[5] = 0;
		m[6] = 0;
		m[7] = 0;
		m[8] = 1;
	}

	friend std::ostream& operator<< (std::ostream& stream, const Matrix2D& matrix)
	{
		std::cout << matrix.m[0] << " " << matrix.m[3] << " " << matrix.m[6] << " " << std::endl;
		std::cout << matrix.m[1] << " " << matrix.m[4] << " " << matrix.m[7] << " " << std::endl;
		std::cout << matrix.m[2] << " " << matrix.m[5] << " " << matrix.m[8] << " " << std::endl;
		return stream;
	}

	/**
	* Element Index Calculation
	* @param r Column In Range [0,SIZE)
	* @param c Row    In Range [0,SIZE)
	* @return Index In Element Array (c * SIZE + r)
	*/
	static int index(int r, int c) {
		return c * SIZE + r;
	}

	/**
	* Helper To Calculate An Inner Product
	* @param left Left Side Matrix
	* @param right Right Side Matrix
	* @param r Row
	* @param c Column
	* @return Dot Product Of Row r Of Left and Column c of Right
	*/
	static double innerProduct(Matrix2D& left, Matrix2D& right, int r, int c) {
		return
			left.m[index(r, 0)] * right.m[index(0, c)] +
			left.m[index(r, 1)] * right.m[index(1, c)] +
			left.m[index(r, 2)] * right.m[index(2, c)]
			;
	}


	/**
	* Inline Setter
	* @param m00 Row 1 Col 1
	* @param m01 Row 1 Col 2
	* @param m02 Row 1 Col 3
	* @param m10 Row 2 Col 1
	* @param m11 Row 2 Col 2
	* @param m12 Row 2 Col 3
	* @param m20 Row 3 Col 1
	* @param m21 Row 3 Col 2
	* @param m22 Row 3 Col 3
	* @return Self
	*/
	Matrix2D& set(
		double m00, double m01, double m02,
		double m10, double m11, double m12,
		double m20, double m21, double m22
	) {
		m[0] = m00;
		m[1] = m10;
		m[2] = m20;
		m[3] = m01;
		m[4] = m11;
		m[5] = m21;
		m[6] = m02;
		m[7] = m12;
		m[8] = m22;
		return *this;
	}

	/**
	* Set This Matrix To The Identity Matrix
	* @return Self
	*/
	Matrix2D& setIdentity() {
		return set(
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		);
	}

	/**
	* Copy Matrix Into This Matrix
	* @param mat Matrix
	* @return Self
	*/
	Matrix2D& set(Matrix2D mat) {
		for (int i = 0; i < ELEMENTS; i++) m[i] = mat.m[i];
		return *this;
	}

	/**
	* Composes A Matrix M Onto This So That M Applies After This
	* <pre>
	* This = Mat * This
	* </pre>
	* @param mat Matrix M
	* @return This
	*/
	Matrix2D& mulAfter(Matrix2D& mat) {
		return set(
			innerProduct(mat, *this, 0, 0),
			innerProduct(mat, *this, 0, 1),
			innerProduct(mat, *this, 0, 2),
			innerProduct(mat, *this, 1, 0),
			innerProduct(mat, *this, 1, 1),
			innerProduct(mat, *this, 1, 2),
			innerProduct(mat, *this, 2, 0),
			innerProduct(mat, *this, 2, 1),
			innerProduct(mat, *this, 2, 2)
		);
	}

	/**
	* Composes A Matrix M Onto This So That M Applies Before This
	* <pre>
	* This = This * Mat
	* </pre>
	* @param mat Matrix M
	* @return This
	*/
	Matrix2D& mulBefore(Matrix2D& mat) {
		return set(
			innerProduct(*this, mat, 0, 0),
			innerProduct(*this, mat, 0, 1),
			innerProduct(*this, mat, 0, 2),
			innerProduct(*this, mat, 1, 0),
			innerProduct(*this, mat, 1, 1),
			innerProduct(*this, mat, 1, 2),
			innerProduct(*this, mat, 2, 0),
			innerProduct(*this, mat, 2, 1),
			innerProduct(*this, mat, 2, 2)
		);
	}

	/**
	* Multiplies This Matrix And Another Into Out So That M Applies After This
	* <pre>
	* Out = Mat * This
	* </pre>
	* @param mat Matrix M
	* @param out Non-Null Output Matrix
	* @return Out
	*/
	Matrix2D& mulAfter(Matrix2D mat, Matrix2D& out) {
		return out.set(
			innerProduct(mat, *this, 0, 0),
			innerProduct(mat, *this, 0, 1),
			innerProduct(mat, *this, 0, 2),
			innerProduct(mat, *this, 1, 0),
			innerProduct(mat, *this, 1, 1),
			innerProduct(mat, *this, 1, 2),
			innerProduct(mat, *this, 2, 0),
			innerProduct(mat, *this, 2, 1),
			innerProduct(mat, *this, 2, 2)
		);
	}

	/**
	* Multiplies This Matrix And Another Into Out So That M Applies Before This
	* <pre>
	* Out = This * Mat
	* </pre>
	* @param mat Matrix M
	* @param out Non-Null Output Matrix
	* @return Out
	*/
	Matrix2D& mulBefore(Matrix2D mat, Matrix2D& out) {
		return out.set(
			innerProduct(*this, mat, 0, 0),
			innerProduct(*this, mat, 0, 1),
			innerProduct(*this, mat, 0, 2),
			innerProduct(*this, mat, 1, 0),
			innerProduct(*this, mat, 1, 1),
			innerProduct(*this, mat, 1, 2),
			innerProduct(*this, mat, 2, 0),
			innerProduct(*this, mat, 2, 1),
			innerProduct(*this, mat, 2, 2)
		);
	}

	/**
	* Transforms And Homogenizes A Position Vector In Place
	* <pre>
	* {V, w} = This * {V, 1}
	* V = V / w
	* </pre>
	* @param v [{@link Vector2d POS}] Vector
	* @return Transformed Vector
	*/
	Vector2D mul(Vector2D v) {
		double w = m[6] * v.x + m[7] * v.y + m[8];
		return v.set(
			m[0] * v.x + m[1] * v.y + m[2],
			m[3] * v.x + m[4] * v.y + m[5]
		).div(w);
	}

	/**
	* Transpose In Place
	* @return This
	*/
	Matrix2D& transpose() {
		double t;
		t = m[1];  m[1] = m[3];  m[3] = t;
		t = m[2];  m[2] = m[6];  m[6] = t;
		t = m[5];  m[5] = m[7]; m[7] = t;
		return *this;
	}

	/**
	* Helper To Calculate A Cofactor
	* @param c Excluded Column
	* @param r Excluded Row
	* @return Cofactor
	*/
	double coFactor(int c, int r) {
		switch (c) {
		case 0:
			switch (r) {
			case 0:
				return m[4] * m[8] - m[5] * m[7];
			case 1:
				return m[5] * m[6] - m[3] * m[8];
			case 2:
				return m[3] * m[7] - m[4] * m[6];
			}
		case 1:
			switch (r) {
			case 0:
				return m[2] * m[7] - m[1] * m[8];
			case 1:
				return m[0] * m[8] - m[2] * m[6];
			case 2:
				return m[1] * m[6] - m[0] * m[7];
			}
		case 2:
			switch (r) {
			case 0:
				return m[1] * m[5] - m[2] * m[4];
			case 1:
				return m[2] * m[3] - m[0] * m[5];
			case 2:
				return m[0] * m[4] - m[1] * m[3];
			}
		}
		return 0;
	}

	/**
	* Calculates The Determinant Of This Matrix
	* @return Determinant
	*/
	double determinant() {
		return
			m[0] * coFactor(0, 0) +
			m[1] * coFactor(0, 1) +
			m[2] * coFactor(0, 2)
			;
	}


	/**
	* Inverts In Place If Inverse Exists
	* @return This
	* @throws AssertionError When Determinant Is Zero
	*/
	Matrix2D& invert() {
		double cof00 = coFactor(0, 0);
		double cof01 = coFactor(0, 1);
		double cof02 = coFactor(0, 2);
		double det =
			m[0] * cof00 +
			m[1] * cof01 +
			m[2] * cof02
			;
		assert(det != 0 && "Determinant Of 0");

		double f = 1 / det;
		return set(
			f * cof00, f * cof01, f * cof02,
			f * coFactor(1, 0), f * coFactor(1, 1), f * coFactor(1, 2),
			f * coFactor(2, 0), f * coFactor(2, 1), f * coFactor(2, 2)
		);

	}

	/**
	* Create A Scaling Matrix Into Out
	* <pre>
	* | x  0  0 |
	* | 0  y  0 |
	* | 0  0  1 |
	* </pre>
	* @param x X Scale
	* @param y Y Scale
	* @param out Non-Null Output Matrix
	* @return Out
	*/
	static Matrix2D& createScale(double x, double y, Matrix2D& out) {
		return out.set(
			x, 0, 0,
			0, y, 0,
			0, 0, 1
		);
	}

	/**
	* @see {@link #createScale(double, double, Matrix3d) Mat3.createScale(v.x, v.y, out)}
	* @param v [{@link Vector2d ARR}] Scaling Vector
	* @param out Non-Null Output Matrix
	* @return Out
	*/
	static Matrix2D& createScale(Vector2D v, Matrix2D& out) {
		return createScale(v.x, v.y, out);
	}


	/**
	* Create A Translation Matrix Into Out
	* <pre>
	* | 1  0  0 |
	* | 0  1  0 |
	* | x  y  1 |
	* <pre>
	* @param x X Translation
	* @param y Y Translation
	* @param out Non-Null Output Matrix
	* @return Out
	*/
	static Matrix2D& createTranslation(double x, double y, Matrix2D& out) {
		return out.set(
			1, 0, 0,
			0, 1, 0,
			x, y, 1
		);
	}
	/**
	* @see {@link #createTranslation(double, double, Matrix3d) Mat3.createTranslation(v.x, v.y, out)}
	* @param v [{@link Vector2d POS}] Translation Vector
	* @param out Non-Null Output Matrix
	* @return Out
	*/
	static Matrix2D& createTranslation(Vector2D v, Matrix2D& out) {
		return createTranslation(v.x, v.y, out);
	}


	/**
	* Create A Rotation Matrix Into Out
	* <pre>
	* |  cos(t) sin(t)  0 |
	* |  -sin(t)  cos(t)  0 |
	* |  0       0       1 |
	* </pre>
	* @param t Angle (Radians)
	* @param out Non-Null Output Matrix
	* @return Out
	*/
	static Matrix2D& createRotation(double t, Matrix2D& out) {

		double cosT = cos(t), sinT = sin(t);
		return out.set(
			cosT, sinT, 0,
			-sinT, cosT, 0,
			0, 0, 1
		);
	}

};


#endif

