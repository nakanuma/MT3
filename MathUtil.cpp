#include "MathUtil.h"

#include <Novice.h>
#include <math.h>

#include "Vec3.h"
#include "Vec4.h" 

void DrawGrid(const Matrix& viewProjectionMatrix, const Matrix& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f; // Gridの半分の幅
	const uint32_t kSubdivision = 10; // 分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision); // 1つ分の長さ

	float zPositionStart = kGridHalfWidth;
	float zPositionEnd = -kGridHalfWidth;

	float xPositionStart = -kGridHalfWidth;
	float xPositionEnd = kGridHalfWidth;

	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float xPosition = -kGridHalfWidth + (xIndex * kGridEvery);
		// ワールド座標系
		Vec3 startPos = { xPosition, 0.0f, zPositionStart };
		Vec3 endPos = { xPosition, 0.0f, zPositionEnd };
		// ワールド座標系->正規化デバイス座標系
		Vec3 ndcStartPos = Vec3::Transform(startPos, viewProjectionMatrix);
		Vec3 ndcEndPos = Vec3::Transform(endPos, viewProjectionMatrix);
		// 正規化デバイス座標系->スクリーン座標系
		Vec3 screenStartPos = Vec3::Transform(ndcStartPos, viewportMatrix);
		Vec3 screenEndPos = Vec3::Transform(ndcEndPos, viewportMatrix);
		if (xIndex == 5) {
			// 描画
			Novice::DrawLine(
				static_cast<int>(screenStartPos.x),
				static_cast<int>(screenStartPos.y),
				static_cast<int>(screenEndPos.x),
				static_cast<int>(screenEndPos.y),
				BLACK
			);
		} else {
			Novice::DrawLine(
				static_cast<int>(screenStartPos.x),
				static_cast<int>(screenStartPos.y),
				static_cast<int>(screenEndPos.x),
				static_cast<int>(screenEndPos.y),
				WHITE
			);
		}
	}
	// 左から右も同じように順々引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float zPosition = kGridHalfWidth - (zIndex * kGridEvery);
		// ワールド座標系
		Vec3 startPos = { xPositionStart, 0.0f, zPosition };
		Vec3 endPos = { xPositionEnd, 0.0f, zPosition };
		// ワールド座標系->正規化デバイス座標系
		Vec3 ndcStartPos = Vec3::Transform(startPos, viewProjectionMatrix);
		Vec3 ndcEndPos = Vec3::Transform(endPos, viewProjectionMatrix);
		// 正規化デバイス座標系->スクリーン座標系
		Vec3 screenStartPos = Vec3::Transform(ndcStartPos, viewportMatrix);
		Vec3 screenEndPos = Vec3::Transform(ndcEndPos, viewportMatrix);
		// 描画
		if (zIndex == 5) {
			Novice::DrawLine(
				static_cast<int>(screenStartPos.x),
				static_cast<int>(screenStartPos.y),
				static_cast<int>(screenEndPos.x),
				static_cast<int>(screenEndPos.y),
				BLACK
			);
		} else {
			Novice::DrawLine(
				static_cast<int>(screenStartPos.x),
				static_cast<int>(screenStartPos.y),
				static_cast<int>(screenEndPos.x),
				static_cast<int>(screenEndPos.y),
				WHITE
			);
		}
	}
}

void DrawSphere(const Sphere& sphere, const Matrix& viewProjectionMatrix, const Matrix& viewportMatrix, uint32_t color, uint32_t division)
{
	const uint32_t kSubdivision = division; // 分割数
	const float kLonEvery = (PIf * 2.0f) / kSubdivision;
	const float kLatEvery = (PIf * 2.0f) / kSubdivision;
	// 緯度の方向に分割 -π/2 = π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -PIf / 2.0f + kLatEvery * latIndex; // 現在の緯度
		// 経度の方向に分割　0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度
			// world座標系でのa,b,cを求める
			Vec3 a, b, c;
			a = { cosf(lat) * cosf(lon) * sphere.radius, sinf(lat) * sphere.radius, cosf(lat) * sinf(lon) * sphere.radius };
			b = { cosf(lat + kLatEvery) * cosf(lon) * sphere.radius, sinf(lat + kLatEvery) * sphere.radius, cosf(lat + kLatEvery) * sinf(lon) * sphere.radius };
			c = { cosf(lat) * cosf(lon + kLonEvery) * sphere.radius, sinf(lat) * sphere.radius, cosf(lat) * sinf(lon + kLonEvery) * sphere.radius };
			a = Vec3::Add(a, sphere.center);
			b = Vec3::Add(b, sphere.center);
			c = Vec3::Add(c, sphere.center);
			// a,b,cをScreen座標系まで変換
			Vec3 screenA = WorldToScreen(a, viewProjectionMatrix, viewportMatrix);
			Vec3 screenB = WorldToScreen(b, viewProjectionMatrix, viewportMatrix);
			Vec3 screenC = WorldToScreen(c, viewProjectionMatrix, viewportMatrix);
			// ab,acで線を引く
			Novice::DrawLine(
				static_cast<int>(screenA.x),
				static_cast<int>(screenA.y),
				static_cast<int>(screenB.x),
				static_cast<int>(screenB.y),
				color
			);
			Novice::DrawLine(
				static_cast<int>(screenA.x),
				static_cast<int>(screenA.y),
				static_cast<int>(screenC.x),
				static_cast<int>(screenC.y),
				color
			);
		}
	}
}

Vec3 Perpendicular(const Vec3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y, vector.x, 0.0f };
	}
	return { 0.0f, -vector.z, vector.y };
}

void DrawPlane(const Plane& plane, const Matrix& viewProjectionMatrix, const Matrix& viewportMatrix, uint32_t color)
{
	// 中心点を求める
	Vec3 center = Vec3::Multiply(plane.distance, plane.normal);
	Vec3 perpendiculars[4];
	perpendiculars[0] = Vec3::Normalize(Perpendicular(plane.normal)); // 法線と垂直なベクトルを1つ求める
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z }; // [0]の逆ベクトルを求める
	perpendiculars[2] = Vec3::Cross(plane.normal, perpendiculars[0]); // [0]と法線とのクロス積を求める
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z }; // [2]の逆ベクトルを求める
	// 4頂点を求める
	Vec3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vec3 extend = Vec3::Multiply(2.0f, perpendiculars[index]);
		Vec3 point = Vec3::Add(center, extend);
		points[index] = Vec3::Transform(Vec3::Transform(point, viewProjectionMatrix), viewportMatrix);
	}
	// pointsをそれぞれ結んで矩形を描画する
	Novice::DrawLine(
		static_cast<int>(points[0].x), static_cast<int>(points[0].y),
		static_cast<int>(points[2].x), static_cast<int>(points[2].y),
		color
	);
	Novice::DrawLine(
		static_cast<int>(points[1].x), static_cast<int>(points[1].y),
		static_cast<int>(points[2].x), static_cast<int>(points[2].y),
		color
	);
	Novice::DrawLine(
		static_cast<int>(points[1].x), static_cast<int>(points[1].y),
		static_cast<int>(points[3].x), static_cast<int>(points[3].y),
		color
	);
	Novice::DrawLine(
		static_cast<int>(points[3].x), static_cast<int>(points[3].y),
		static_cast<int>(points[0].x), static_cast<int>(points[0].y),
		color
	);
}

void DrawTriangle(const Triangle& triangle, const Matrix& viewProjectionMatrix, const Matrix& viewportMatrix, uint32_t color)
{
	// スクリーン座標に変換した頂点情報を保持
	Vec3 screenVertices[3];

	// 三角形の頂点の座標変換を行う（ワールド座標->スクリーン座標）
	for (uint32_t i = 0; i < 3; i++) {
		screenVertices[i] = WorldToScreen(triangle.vertices[i], viewProjectionMatrix, viewportMatrix);
	}

	// 三角形を描画
	Novice::DrawTriangle(
		static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
		static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
		static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
		color,
		kFillModeWireFrame
	);
}

Vec3 WorldToScreen(const Vec3& worldCoordinate, const Matrix& viewProjectionMatrix, const Matrix& viewportMatrix)
{
	// ワールド座標系->正規化デバイス座標系
	Vec3 ndc = Vec3::Transform(worldCoordinate, viewProjectionMatrix);
	// 正規化デバイス座標系->スクリーン座標系
	Vec3 screen = Vec3::Transform(ndc, viewportMatrix);

	return screen;
}

bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	// 2つの球の中心点間の距離を求める
	float distance = Vec3::Length(Vec3::Subtract(s2.center, s1.center));
	// 半径の合計よりも短ければ衝突
	if (distance <= s1.radius + s2.radius) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const Sphere& sphere, const Plane& plane)
{
	// 球の中心と平面の距離を計算
	float numerator = Vec3::Dot(plane.normal, sphere.center) - plane.distance;
	float denominator = sqrtf(powf(plane.normal.x, 2.0f) + powf(plane.normal.y, 2) + powf(plane.normal.z, 2));

	float distance = numerator / denominator;

	// 球の中心と平面の距離が球の半径以下だったら衝突
	if (std::fabs(distance) <= sphere.radius) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const Segment& segment, const Plane& plane)
{
	// 平面の法線ベクトルと線分の差分ベクトルの内積を計算
	float dot = Vec3::Dot(plane.normal, segment.diff);

	// dotが0の場合、平行のため衝突はしない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (plane.distance - Vec3::Dot(segment.origin, plane.normal)) / dot;

	// 衝突点が線分上にあるかを判定する
	if (t >= 0.0f && t <= 1.0f) {
		return true;
	}

	return false;
}

bool IsCollision(const Triangle& triangle, const Segment& segment)
{
	// 2つのベクトルを計算
	Vec3 vec1 = Vec3::Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vec3 vec2 = Vec3::Subtract(triangle.vertices[2], triangle.vertices[1]);

	// 外積を計算して法線ベクトルを得る
	Vec3 normal = Vec3::Cross(vec1, vec2);

	// 法線ベクトルを正規化
	float length = Vec3::Length(normal);
	normal.x /= length;
	normal.y /= length;
	normal.z /= length;

	// 平面までの距離を計算
	float distance =
		-(normal.x * triangle.vertices[0].x,
			normal.y * triangle.vertices[0].y,
			normal.z * triangle.vertices[0].z);

	// 三角形の存在する平面を作成
	Plane plane = { normal, distance };

	// 最初に線と三角形の存在する平面との衝突判定を行う
	if (IsCollision(segment, plane)) {
		// 衝突点pを求める
		float dot = Vec3::Dot(plane.normal, segment.diff);
		float t = (plane.distance - Vec3::Dot(segment.origin, plane.normal)) / dot;
		Vec3 p = Vec3::Add(segment.origin, Vec3::Multiply(t, segment.diff));

		// 小三角形のクロス積を取る
		// 0->1->pからなる三角形
		Vec3 v01 = Vec3::Subtract(triangle.vertices[1], triangle.vertices[0]);
		Vec3 v1p = Vec3::Subtract(p, triangle.vertices[1]);
		Vec3 cross01 = Vec3::Cross(v01, v1p);

		// 1->2->pからなる三角形
		Vec3 v12 = Vec3::Subtract(triangle.vertices[2], triangle.vertices[1]);
		Vec3 v2p = Vec3::Subtract(p, triangle.vertices[2]);
		Vec3 cross12 = Vec3::Cross(v12, v2p);

		// 2->0->pからなる三角形
		Vec3 v20 = Vec3::Subtract(triangle.vertices[0], triangle.vertices[2]);
		Vec3 v0p = Vec3::Subtract(p, triangle.vertices[0]);
		Vec3 cross20 = Vec3::Cross(v20, v0p);

		// すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
		if (Vec3::Dot(cross01, normal) >= 0.0f &&
			Vec3::Dot(cross12, normal) >= 0.0f &&
			Vec3::Dot(cross20, normal) >= 0.0f) {
			return true;
		}
	}

	return false;

	/*----------------------------------------------------*/

	//// 三角形の法線ベクトルを計算
	//Vec3 edge1 = Vec3::Subtract(triangle.vertices[1], triangle.vertices[0]);
	//Vec3 edge2 = Vec3::Subtract(triangle.vertices[2], triangle.vertices[1]);
	//Vec3 cross1 = Vec3::Cross(edge1, edge2);
	//Vec3 normal = Vec3::Normalize(cross1);

	//// 衝突点pを求める
	//Vec3 p = Vec3::Add(segment.origin, segment.diff);

	//// 小三角形のクロス積を取る
	//// 0->1->pからなる三角形
	//Vec3 v01 = Vec3::Subtract(triangle.vertices[1], triangle.vertices[0]);
	//Vec3 v1p = Vec3::Subtract(p, triangle.vertices[1]);
	//Vec3 cross01 = Vec3::Cross(v01, v1p);

	//// 1->2->pからなる三角形
	//Vec3 v12 = Vec3::Subtract(triangle.vertices[2], triangle.vertices[1]);
	//Vec3 v2p = Vec3::Subtract(p, triangle.vertices[2]);
	//Vec3 cross12 = Vec3::Cross(v12, v2p);

	//// 2->0->pからなる三角形
	//Vec3 v20 = Vec3::Subtract(triangle.vertices[0], triangle.vertices[2]);
	//Vec3 v0p = Vec3::Subtract(p, triangle.vertices[0]);
	//Vec3 cross20 = Vec3::Cross(v20, v0p);

	//// すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
	//if (Vec3::Dot(cross01, normal) >= 0.0f &&
	//	Vec3::Dot(cross12, normal) >= 0.0f &&
	//	Vec3::Dot(cross20, normal) >= 0.0f) {
	//	return true;
	//}

	//return false;
}

void VectorScreenPrintf(int x, int y, const Vec3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix& matrix, const char* label)
{
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + kRowHeight + (row * kRowHeight), "%6.02f", matrix.m[row][column]
			);
		}
	}
}

void CameraControl(Vec3& cameraTranslate, Vec3& cameraRotate, int& prevMousePosX, int& prevMousePosY, bool& isFirstRightClick, bool& isFirstMiddleClick)
{
	// 右クリックが押されている場合（カメラの回転）
	if (Novice::IsPressMouse(1)) {
		// マウスの位置を取得
		int mousePosX, mousePosY;
		Novice::GetMousePosition(&mousePosX, &mousePosY);

		// 初回クリックの場合
		if (isFirstRightClick) {
			// マウスの現在位置を前回の位置として保存
			prevMousePosX = mousePosX;
			prevMousePosY = mousePosY;
			isFirstRightClick = false;
		}

		// マウスの移動量を計算
		int dx = mousePosX - prevMousePosX;
		int dy = mousePosY - prevMousePosY;
		isFirstRightClick = false;

		// カメラの回転を更新
		cameraRotate.y += static_cast<float>(dx) * 0.001f;
		cameraRotate.x += static_cast<float>(dy) * 0.001f;

		// マウスの現在位置を前回の位置として保存
		prevMousePosX = mousePosX;
		prevMousePosY = mousePosY;
	} else {
		// 右クリックが離された場合、次回のクリックで初期化するためのフラグを設定
		isFirstRightClick = true;
	}

	// 左クリックが押されている場合（カメラの移動）
	if (Novice::IsPressMouse(2)) {
		// マウスの位置を取得
		int mousePosX, mousePosY;
		Novice::GetMousePosition(&mousePosX, &mousePosY);

		if (isFirstMiddleClick) {
			// 初回の左クリックの場合、現在の位置を前回の位置として保存
			prevMousePosX = mousePosX;
			prevMousePosY = mousePosY;
			isFirstMiddleClick = false;
		}

		// マウスの移動量を計算
		int dx = mousePosX - prevMousePosX;
		int dy = mousePosY - prevMousePosY;

		// カメラのTranslateを更新
		cameraTranslate.x -= static_cast<float>(dx) * 0.01f;
		cameraTranslate.y += static_cast<float>(dy) * 0.01f;

		// マウスの現在位置を前回の位置として保存
		prevMousePosX = mousePosX;
		prevMousePosY = mousePosY;
	} else {
		// 左クリックが離された場合、次回のクリックで初期化するためのフラグを設定
		isFirstMiddleClick = true;
	}
	// ホイールスクロールでカメラの前後を変更
	int wheelDelta = Novice::GetWheel();
	if (wheelDelta != 0) {
		cameraTranslate.z += static_cast<float>(wheelDelta) * 0.001f;
		wheelDelta = 0;
	}
}
