#pragma once
#include <cmath>
#include "Vec3.h"

class Matrix {
public:

	/// <summary>
	/// 4x4行列
	/// </summary>
	
	float m[4][4];

	// 単位行列で初期化
	Matrix();

	// floatを16個で初期化
	Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	
	Matrix operator+ (const Matrix& m1)const;
	Matrix operator+=(const Matrix& m1);

	Matrix operator- (const Matrix& m1)const;
	Matrix operator-=(const Matrix& m1);

	Matrix operator* (const Matrix& m1)const;
	Matrix operator*= (const Matrix& m1);

	// 加法
	static Matrix Add(const Matrix& m1, const Matrix& m2);
	// 減法
	static Matrix Subtract(const Matrix& m1, const Matrix& m2);
	// 積
	static Matrix Multiply(const Matrix& m1, const Matrix& m2);
	// 逆行列
	static Matrix Inverse(const Matrix& m);
	// 転置行列
	static Matrix Transpose(const Matrix& m);
	// 単位行列の作成
	static Matrix MakeIdentity();

	// 平行移動
	static Matrix MakeTranslate(const Vec3& translate);
	// 拡大縮小行列
	static Matrix MakeScale(const Vec3& scale);

	// X軸回転行列(roll)
	static Matrix MakeRotateX(float radian);
	// Y軸回転行列(pitch)
	static Matrix MakeRotateY(float radian);
	// Z軸回転行列(yaw)
	static Matrix MakeRotateZ(float radian);
	// XYZ全てかけて回転
	static Matrix MakeRotateXYZ(float roll, float pitch, float yaw);

	// 3次元アフィン変換行列
	static Matrix MakeAffine(const Vec3& scale, const Vec3& rotate, const Vec3& tlanslate);

	// 透視投影行列
	static Matrix MakePerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip);
	// 正射影行列
	static Matrix MakeOrthograph(float left, float top, float right, float bottom, float nearClip, float farClip);
	// ビューポート変換行列
	static Matrix MakeViewport(float left, float top, float width, float height, float minDepth, float maxDepth);
};
