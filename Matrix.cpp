#include "Matrix.h"

Matrix::Matrix()
{
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

Matrix::Matrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;

	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;

	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;

	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

Matrix Matrix::operator+(const Matrix& m1) const
{
	return Matrix(
		this->m[0][0] + m1.m[0][0],
		this->m[0][1] + m1.m[0][1],
		this->m[0][2] + m1.m[0][2],
		this->m[0][3] + m1.m[0][3],

		this->m[1][0] + m1.m[1][0],
		this->m[1][1] + m1.m[1][1],
		this->m[1][2] + m1.m[1][2],
		this->m[1][3] + m1.m[1][3],

		this->m[2][0] + m1.m[2][0],
		this->m[2][1] + m1.m[2][1],
		this->m[2][2] + m1.m[2][2],
		this->m[2][3] + m1.m[2][3],

		this->m[3][0] + m1.m[3][0],
		this->m[3][1] + m1.m[3][1],
		this->m[3][2] + m1.m[3][2],
		this->m[3][3] + m1.m[3][3]
	);
}

Matrix Matrix::operator+=(const Matrix& m1)
{
	this->m[0][0] += m1.m[0][0];
	this->m[0][1] += m1.m[0][1];
	this->m[0][2] += m1.m[0][2];
	this->m[0][3] += m1.m[0][3];

	this->m[1][0] += m1.m[1][0];
	this->m[1][1] += m1.m[1][1];
	this->m[1][2] += m1.m[1][2];
	this->m[1][3] += m1.m[1][3];

	this->m[2][0] += m1.m[2][0];
	this->m[2][1] += m1.m[2][1];
	this->m[2][2] += m1.m[2][2];
	this->m[2][3] += m1.m[2][3];

	this->m[3][0] += m1.m[3][0];
	this->m[3][1] += m1.m[3][1];
	this->m[3][2] += m1.m[3][2];
	this->m[3][3] += m1.m[3][3];

	return *this;
}

Matrix Matrix::operator-(const Matrix& m1) const
{
	return Matrix(
		this->m[0][0] - m1.m[0][0],
		this->m[0][1] - m1.m[0][1],
		this->m[0][2] - m1.m[0][2],
		this->m[0][3] - m1.m[0][3],

		this->m[1][0] - m1.m[1][0],
		this->m[1][1] - m1.m[1][1],
		this->m[1][2] - m1.m[1][2],
		this->m[1][3] - m1.m[1][3],

		this->m[2][0] - m1.m[2][0],
		this->m[2][1] - m1.m[2][1],
		this->m[2][2] - m1.m[2][2],
		this->m[2][3] - m1.m[2][3],

		this->m[3][0] - m1.m[3][0],
		this->m[3][1] - m1.m[3][1],
		this->m[3][2] - m1.m[3][2],
		this->m[3][3] - m1.m[3][3]
	);
}

Matrix Matrix::operator-=(const Matrix& m1)
{
	this->m[0][0] -= m1.m[0][0];
	this->m[0][1] -= m1.m[0][1];
	this->m[0][2] -= m1.m[0][2];
	this->m[0][3] -= m1.m[0][3];

	this->m[1][0] -= m1.m[1][0];
	this->m[1][1] -= m1.m[1][1];
	this->m[1][2] -= m1.m[1][2];
	this->m[1][3] -= m1.m[1][3];

	this->m[2][0] -= m1.m[2][0];
	this->m[2][1] -= m1.m[2][1];
	this->m[2][2] -= m1.m[2][2];
	this->m[2][3] -= m1.m[2][3];

	this->m[3][0] -= m1.m[3][0];
	this->m[3][1] -= m1.m[3][1];
	this->m[3][2] -= m1.m[3][2];
	this->m[3][3] -= m1.m[3][3];

	return *this;
}


Matrix Matrix::operator*(const Matrix& m1) const
{
	return Matrix(
		m[0][0] * m1.m[0][0] + m[0][1] * m1.m[1][0] + m[0][2] * m1.m[2][0] + m[0][3] * m1.m[3][0],
		m[0][0] * m1.m[0][1] + m[0][1] * m1.m[1][1] + m[0][2] * m1.m[2][1] + m[0][3] * m1.m[3][1],
		m[0][0] * m1.m[0][2] + m[0][1] * m1.m[1][2] + m[0][2] * m1.m[2][2] + m[0][3] * m1.m[3][2],
		m[0][0] * m1.m[0][3] + m[0][1] * m1.m[1][3] + m[0][2] * m1.m[2][3] + m[0][3] * m1.m[3][3],
							  								  						   
		m[1][0] * m1.m[0][0] + m[1][1] * m1.m[1][0] + m[1][2] * m1.m[2][0] + m[1][3] * m1.m[3][0],
		m[1][0] * m1.m[0][1] + m[1][1] * m1.m[1][1] + m[1][2] * m1.m[2][1] + m[1][3] * m1.m[3][1],
		m[1][0] * m1.m[0][2] + m[1][1] * m1.m[1][2] + m[1][2] * m1.m[2][2] + m[1][3] * m1.m[3][2],
		m[1][0] * m1.m[0][3] + m[1][1] * m1.m[1][3] + m[1][2] * m1.m[2][3] + m[1][3] * m1.m[3][3],
						  								  							  
		m[2][0] * m1.m[0][0] + m[2][1] * m1.m[1][0] + m[2][2] * m1.m[2][0] + m[2][3] * m1.m[3][0],
		m[2][0] * m1.m[0][1] + m[2][1] * m1.m[1][1] + m[2][2] * m1.m[2][1] + m[2][3] * m1.m[3][1],
		m[2][0] * m1.m[0][2] + m[2][1] * m1.m[1][2] + m[2][2] * m1.m[2][2] + m[2][3] * m1.m[3][2],
		m[2][0] * m1.m[0][3] + m[2][1] * m1.m[1][3] + m[2][2] * m1.m[2][3] + m[2][3] * m1.m[3][3],
							  								  						 
		m[3][0] * m1.m[0][0] + m[3][1] * m1.m[1][0] + m[3][2] * m1.m[2][0] + m[3][3] * m1.m[3][0],
		m[3][0] * m1.m[0][1] + m[3][1] * m1.m[1][1] + m[3][2] * m1.m[2][1] + m[3][3] * m1.m[3][1],
		m[3][0] * m1.m[0][2] + m[3][1] * m1.m[1][2] + m[3][2] * m1.m[2][2] + m[3][3] * m1.m[3][2],
		m[3][0] * m1.m[0][3] + m[3][1] * m1.m[1][3] + m[3][2] * m1.m[2][3] + m[3][3] * m1.m[3][3]
	);
}

Matrix Matrix::operator*=(const Matrix& m1)
{
	*this = *this * m1;
	return *this;
}

Matrix Matrix::Add(const Matrix& m1, const Matrix& m2)
{
	Matrix result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

Matrix Matrix::Subtract(const Matrix& m1, const Matrix& m2)
{
	Matrix result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

Matrix Matrix::Multiply(const Matrix& m1, const Matrix& m2)
{
	return Matrix(
		m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0],
		m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1],
		m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2],
		m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3],

		m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0],
		m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1],
		m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2],
		m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3],

		m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0],
		m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1],
		m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2],
		m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3],

		m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0],
		m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1],
		m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2],
		m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3]
	);
}

Matrix Matrix::Inverse(const Matrix& m)
{
	Matrix result;
	float temp[4][8] = {};
	float a;

	// 一時行列にコピー
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[i][j] = m.m[i][j];

			// 右側の4列に単位行列を入れる
			if (i == j)temp[i][4 + j] = 1;
		}
	}

	// 各列を正規化
	for (int k = 0; k < 4; k++) {
		a = 1 / temp[k][k];

		// 対角成分を1に正規化
		for (int j = 0; j < 8; j++) {
			temp[k][j] *= a;
		}

		// 掃き出し法を使って他の要素を0にする
		for (int i = 0; i < 4; i++) {
			if (i == k) {
				continue;
			}

			a = -temp[i][k];

			for (int j = 0; j < 8; j++) {
				temp[i][j] += temp[k][j] * a;
			}

		}
	}

	// 逆行列をresultにコピー
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = temp[i][4 + j];
		}
	}

	return result;
}

Matrix Matrix::Transpose(const Matrix& m)
{
	Matrix result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m.m[j][i];
		}
	}

	return result;
}

Matrix Matrix::MakeIdentity()
{
	Matrix result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = (i == j) ? 1.0f : 0.0f; // 対角成分のみ1を入れる
		}
	}

	return result;
}

Matrix Matrix::MakeTranslate(const Vec3& translate)
{
	Matrix result = MakeIdentity();

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

Matrix Matrix::MakeScale(const Vec3& scale)
{
	Matrix result = MakeIdentity();

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;

	return result;
}

Matrix Matrix::MakeRotateX(float radian)
{
	Matrix result = MakeIdentity();

	result.m[1][1] = std::cosf(radian);
	result.m[2][1] = -std::sinf(radian);
	result.m[1][2] = std::sinf(radian);
	result.m[2][2] = std::cosf(radian);

	return result;
}

Matrix Matrix::MakeRotateY(float radian)
{
	Matrix result = MakeIdentity();

	result.m[0][0] = std::cosf(radian);
	result.m[2][0] = std::sinf(radian);
	result.m[0][2] = -std::sinf(radian);
	result.m[2][2] = std::cosf(radian);

	return result;
}

Matrix Matrix::MakeRotateZ(float radian)
{
	Matrix result = MakeIdentity();

	result.m[0][0] = std::cosf(radian);
	result.m[1][0] = -std::sinf(radian);
	result.m[0][1] = std::sinf(radian);
	result.m[1][1] = std::cosf(radian);

	return result;
}

Matrix Matrix::MakeRotateXYZ(float roll, float pitch, float yaw)
{
	Matrix result = MakeIdentity();

	return result * MakeRotateX(roll) * MakeRotateY(pitch) * MakeRotateZ(yaw);
}

Matrix Matrix::MakeAffine(const Vec3& scale, const Vec3& rotate, const Vec3& tlanslate)
{
	Matrix result = MakeIdentity();

	result *= MakeScale(scale);
	result *= MakeRotateXYZ(rotate.x, rotate.y, rotate.z);
	result *= MakeTranslate(tlanslate);

	return result;
}

Matrix Matrix::MakePerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix result = MakeIdentity();

	result.m[1][1] = 1.0f / std::tanf(fovY / 2.0f);
	result.m[0][0] = result.m[1][1] / aspectRatio;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][3] = 0.0f;

	return result;
}

Matrix Matrix::MakeOrthograph(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	return Matrix(
		2.0f / (right - left), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f / (farClip - nearClip), 0.0f,
		(left + right) / (left - right), (top + bottom) / (bottom - top), nearClip / (nearClip - farClip), 1.0f
	);
}

Matrix Matrix::MakeViewport(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	return Matrix(
		width / 2.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -height / 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, maxDepth - minDepth, 0,
		left + (width / 2.0f), top + (height / 2.0f), minDepth, 1.0f
	);
}
