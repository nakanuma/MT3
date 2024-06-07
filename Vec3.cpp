#include <assert.h>
#include "Vec3.h"
#include "Matrix.h"
#include <iostream>
#include <algorithm>

Vec3::Vec3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vec3::Vec3(float argX, float argY, float argZ)
{
	x = argX;
	y = argY;
	z = argZ;
}

Vec3& Vec3::operator+(const Vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3& Vec3::operator+=(const Vec3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vec3& Vec3::operator*(const Vec3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vec3& Vec3::operator*=(const Vec3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

Vec3 Vec3::Add(const Vec3& v1, const Vec3& v2)
{
	return Vec3(
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	);
}

Vec3 Vec3::Subtract(const Vec3& v1, const Vec3& v2)
{
	return Vec3(
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	);
}

Vec3 Vec3::Multiply(float scalar, const Vec3& v)
{
	return Vec3(
		scalar * v.x,
		scalar * v.y,
		scalar * v.z
	);
}

float Vec3::Dot(const Vec3& v1, const Vec3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float Vec3::Length(const Vec3& v)
{
	return sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
}

Vec3 Vec3::Normalize(const Vec3& v)
{
	float norm = Length(v);

	return Vec3(
		v.x / norm,
		v.y / norm,
		v.z / norm
	);
}

Vec3 Vec3::Transform(const Vec3& vector, const Matrix& matrix)
{
	Vec3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

Vec3 Vec3::Cross(const Vec3& v1, const Vec3& v2)
{
	return Vec3(
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x)
	);
}

Vec3 Vec3::Project(const Vec3& v1, const Vec3& v2)
{
	// v1とv2の内積を求める
	float dot = Dot(v1, v2);

	// v2のノルムを求める
	float norm = Length(v2);

	// 求めた内積をv2のノルムの2乗で割る
	float scalar = dot / (norm * norm);

	// スカラーを用いて正射影ベクトルを求める
	Vec3 project = Multiply(scalar, v2);

	return project;
}

Vec3 Vec3::ClosestPoint(const Vec3& point, const Segment& segment)
{
	// 点から線分への始点ベクトルを計算
	Vec3 toStart = Subtract(point, segment.origin);

	// 線分の方向ベクトルに対する正射影ベクトルを計算
	float t = Dot(toStart, segment.diff) / Dot(segment.diff, segment.diff);

	// tが0未満の場合は始点、1以上の場合は終点、それ以外の場合は線分上の点を計算
	t = std::clamp(t, 0.0f, 1.0f);

	Vec3 closestPoint = Add(segment.origin, Multiply(t, segment.diff));

	return closestPoint;
}

Vec3 Vec3::Lerp(const Vec3& v1, const Vec3& v2, float t)
{
	return {
		v1.x * (1.0f - t) + v2.x * t,
		v1.y * (1.0f - t) + v2.y * t,
		v1.z * (1.0f - t) + v2.z * t,
	};
}
