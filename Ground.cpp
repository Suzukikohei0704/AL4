#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Ground.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>

void Ground::Initialize(Model* model) {

	// NULLポインタチェック
	assert(model);
	model_ = model;
	// textureHandle_ = textureHandle;
	worldTransform_.Initialize();
};

void Ground::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
};

void Ground::Draw(ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection);
};