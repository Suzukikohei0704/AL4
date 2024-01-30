
#include <cassert>
#include <player.h>

void Player::Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm) {

	// NULLポインタチェック
	assert(modelBody);
	assert(modelHead);
	assert(modelL_arm);
	assert(modelR_arm);

	modelFighterBody_ = modelBody;
	modelFighterlHead_ = modelHead;
	modelFighterL_arm_ = modelL_arm;
	modelFighterR_arm_ = modelR_arm;




	//textureHandle_ = textureHandle;
	
	
	//ワールド変換の初期化
	
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	
	// 親子構造
	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformHead_.parent_ = &worldTransformBody_;
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	worldTransformR_arm_.parent_ = &worldTransformBody_;


	// 位置調整
	worldTransformHead_.translation_.y = 1.5038f;
	worldTransformL_arm_.translation_.x = -0.5275f;
	worldTransformL_arm_.translation_.y = 1.2619f;
	worldTransformR_arm_.translation_.x = +0.5275f;
	worldTransformR_arm_.translation_.y = 1.2619f;



	InitalizeFloatingGimmick();

	input_ = Input::GetInstance();

};

void Player::Update() {
	
	const float speed = 0.3f;
	Vector3 move = {0.0f, 0.0f, 0.0f};
	if (input_->PushKey(DIK_RIGHT)) {
		move.x = 1.0f;
	}
	if (input_->PushKey(DIK_LEFT)) {
		move.x = -1.0f;
	}
	if (input_->PushKey(DIK_UP)) {
		move.z = 1.0f;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.z = -1.0f;
	}

	move = Normalize(move) * speed;

	worldTransform_.translation_ += move;

	
	// 移動ベクトルのY軸周り角度
	worldTransform_.rotation_.y = std::atan2(move.x, move.z);

	UpdateFloatingGimmick();
	
	// 行列を更新
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();

};

void Player::Draw(ViewProjection& viewProjection) {

	// 3Dモデルを描画
	modelFighterBody_->Draw(worldTransformBody_, viewProjection);
	modelFighterlHead_->Draw(worldTransformHead_, viewProjection);
	modelFighterL_arm_->Draw(worldTransformL_arm_, viewProjection);
	modelFighterR_arm_->Draw(worldTransformR_arm_, viewProjection);
};



void Player::InitalizeFloatingGimmick(){

	floatingParameter_ = 0.0f;


};

void Player::UpdateFloatingGimmick() {

	// 最もシンプルなアニメーション処理
	floatingParameter_ += 0.1f;
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * 0.2f;
	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * 0.5f;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * 0.5f;


}










