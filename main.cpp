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


	// ばねの初期値
	Spring spring{};
	spring.anchor = { 0.0f, 0.0f, 0.0f };
	spring.naturalLength = 1.0f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	// ボールの初期値
	Ball ball{};
	ball.position = { 1.2f, 0.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	// deltaTime
	float deltaTime = 1.0f / 60.0f;

	bool isSimulationRunning = false;

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
			Vec3 diff = ball.position - spring.anchor; // ばねの現在の長さ
			float length = Vec3::Length(diff); // diffベクトルの長さ
			if (length != 0.0f) {
				Vec3 direction = Vec3::Normalize(diff); // diffを正規化してばねの方向を計算
				Vec3 restPosition = spring.anchor + direction * spring.naturalLength; // ばねが自然長のときのボールの位置
				Vec3 displacement = length * (ball.position - restPosition); // ばねが変位している量
				Vec3 restoringForce = -spring.stiffness * displacement; // 復元力の計算（変位に反対の方向）

				// 減衰抵抗を計算する
				Vec3 dampingForce = -spring.dampingCoefficient * ball.velocity;
				// 減衰抵抗も加味して、物体にかかる力を決定する
				Vec3 force = restoringForce + dampingForce;

				ball.acceleration = force / ball.mass; // 力を質量で割って加速度を求める
			}
			// 加速度も速度もどちらも秒を基準とした値である
			// それが、1/60秒間(deltaTime)適用されたと考える
			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;
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

		// ボールの描画
		DrawSphere({ ball.position, 0.05f }, viewProjectionMatrix, viewportMatrix, ball.color, 20);
		// アンカーからボールの中心への線分
		DrawSegment({ spring.anchor * 1.01f, ball.position - spring.anchor }, viewProjectionMatrix, viewportMatrix);

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
