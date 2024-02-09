#pragma once


#include "Input.h"
#include "Model.h"
#include "worldTransform.h"
#include "MathUtilityForText.h"

/// <summary>
/// 自キャラ
/// </summary>

class Player {
public:
	///< summary>
	/// 初期化
	///</summary>
	void Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm);
;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>

	void Draw(ViewProjection& viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	//浮遊ギミック初期化
	void InitalizeFloatingGimmick();

	//浮遊ギミック更新
	void UpdateFloatingGimmick();


private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;



	// モデル
	//Model* model_ = nullptr;
	//3Dモデル
	Model* modelFighterBody_;
	Model* modelFighterlHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;


	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;


	//浮遊ギミックの変数
	float floatingParameter_ = 0.0f;


};

























