#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>
#include <player.h>
#include"Skydome.h"
#include"Ground.h"
#include "followCamera.h"
#include"Enemy.h"
#include"Title.h"
#include"GameClear.h"
#include"Fade.h"






/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	//uint32_t textureHandle_ = 0;

	// 3Dモデルデータ
	//std::unique_ptr<Model> model_;
	std::unique_ptr<Model> modelSkydome_;
	std::unique_ptr<Model> modelGround_;
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;
	std::unique_ptr<Model> modelEnemy_;


	// ビュープロジェクション
	ViewProjection viewProjection_;

	//各クラス
	std::unique_ptr<Player> player_;
	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Ground> ground_;
	std::unique_ptr<followCamera> followCamera_;
	std::unique_ptr<Enemy> enemy_;
	std::unique_ptr<Title> title_;
	std::unique_ptr<GameClear> gameClear_;
	std::unique_ptr<Fade> fade_;





	// タイトル
	uint32_t textureHandleTitle_ = 0u;
	std::unique_ptr<Sprite> spriteTitle_;

	//ゲームクリア
	uint32_t textureHandleGameClear_ = 0u;
	std::unique_ptr<Sprite> spriteGameClear_;
	

	// フェード
	uint32_t textureHandleBlack_ = 0u;
	std::unique_ptr<Sprite> spriteBlack_;


	// エンター
	uint32_t textureHandleKey_ = 0u;
	std::unique_ptr<Sprite> spriteKey_;




	// シーンモード（０：ゲームプレイ、１：タイトル、２：ゲームクリア）
	uint32_t sceneMode_ = 1u;

	uint32_t hitCount_ = 0;


	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
