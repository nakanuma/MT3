#include <Novice.h>
#include <imgui.h>

// MyClass
#include "Vec3.h"
#include "Matrix.h"
#include "MathUtil.h"

const char kWindowTitle[] = "LE2B_19_ナカヌマ_カツシ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// カメラの情報
	Vec3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
	Vec3 cameraRotate{ 0.26f, 0.0f, 0.0f };

	// マウスの前回の位置とクリックのフラグ
	int prevMousePosX = 0, prevMousePosY = 0;
	bool isFirstRightClick = true;
	bool isFirstMiddleClick = true;

	// deltaTime
	float deltaTime = 1.0f / 60.0f;
	bool isSimulationRunning = false;

	// 平面の初期値
	Plane plane;
	plane.normal = Vec3::Normalize({ -0.2f, 1.2f, -0.3f });
	plane.distance = 0.0f;

	// ボールの初期値
	Ball ball{};
	ball.position = { 0.8f, 1.2f, 0.3f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;
	ball.acceleration = { 0.0f, -9.8f, 0.0f };
	float e = 0.6f; // 反発係数

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// マウスでカメラの操作を行う（右クリック:回転 / 中クリック:移動 / ホイール:前後）
		CameraControl(cameraTranslate, cameraRotate, prevMousePosX, prevMousePosY, isFirstRightClick, isFirstMiddleClick);

		// 各種行列の計算
		Matrix cameraMatrix = Matrix::MakeAffine({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix viewMatrix = Matrix::Inverse(cameraMatrix);
		Matrix projectionMatrix = Matrix::MakePerspectiveFov(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix viewProjectionMatrix = Matrix::Multiply(viewMatrix, projectionMatrix);
		Matrix viewportMatrix = Matrix::MakeViewport(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		if (isSimulationRunning) {
			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;
			if (IsCollision(Sphere{ ball.position, ball.radius }, plane)) {
				Vec3 reflected = Reflect(ball.velocity, plane.normal);
				Vec3 projectToNormal = Vec3::Project(reflected, plane.normal);
				Vec3 movingDirection = reflected - projectToNormal;
				ball.velocity = projectToNormal * e + movingDirection;
			}
		}

		// ImGui
		ImGui::Begin("Window");

		if (ImGui::Button("Start")) {
			isSimulationRunning = true;
		}

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッドを描画
		DrawGrid(viewProjectionMatrix, viewportMatrix);

		// 平面を描画
		DrawPlane(plane, viewProjectionMatrix, viewportMatrix, WHITE);
		// 球を描画
		DrawSphere({ ball.position, ball.radius }, viewProjectionMatrix, viewportMatrix, WHITE, 20);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
