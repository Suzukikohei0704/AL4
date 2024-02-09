#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// delete model_;
	//// 自キャラの解放
	// delete player_;
}

/// <summary>
/// 111
/// </summary>

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	//textureHandle_ = TextureManager::Load("mario.jpg");

	// 3Dモデルの生成
	//model_.reset(Model::Create());
	//model_.reset(Model::CreateFromOBJ("float"));
	modelSkydome_.reset(Model::CreateFromOBJ("skydome"));
	modelGround_.reset(Model::CreateFromOBJ("ground"));
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body"));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head"));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm"));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm"));
	modelEnemy_.reset(Model::CreateFromOBJ("needle_Body"));


	// ビュープロジェクションの初期化
	viewProjection_.farZ = 2000.0f;
	viewProjection_.translation_ = {0.0f, 2.0f, -10.0f};
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = std::make_unique<Player>();
	player_->Initialize(
	    modelFighterBody_.get(), 
		modelFighterHead_.get(), 
		modelFighterL_arm_.get(),
	    modelFighterR_arm_.get());
	
	
		//スカイドームの生成
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_.get());
	
	
	//地面の生成
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGround_.get());


	// 追従カメラの生成
	followCamera_ = std::make_unique<followCamera>();
	followCamera_->Initialize();


	// 敵の生成
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(modelEnemy_.get());


	//自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());

	

	// 背景
	textureHandleTitle_ = TextureManager::Load("title.png");
	spriteTitle_.reset(Sprite::Create(textureHandleTitle_, {0, 0}));

	
	// タイトルキー
	textureHandleKey_ = TextureManager::Load("enter.png");
	spriteKey_.reset(Sprite::Create(textureHandleKey_, {300, 400}));

	//フェード
	textureHandleBlack_ = TextureManager::Load("black.png");
	spriteBlack_.reset(Sprite::Create(textureHandleBlack_, {0, 0}));

	// ゲームクリア
	textureHandleGameClear_ = TextureManager::Load("gameclear.png");
	spriteGameClear_.reset(Sprite::Create(textureHandleGameClear_, {0, 0}));

	// タイトルの生成
	title_ = std::make_unique<Title>();
	title_->Initialize(
	    spriteTitle_.get(), textureHandleTitle_,
		spriteKey_.get(), textureHandleKey_);


	// ゲームクリアの生成
	gameClear_ = std::make_unique<GameClear>();
	gameClear_->Initialize(
	    spriteGameClear_.get(), textureHandleGameClear_, spriteKey_.get(), textureHandleKey_);

	// フェードの生成
	fade_ = std::make_unique<Fade>();
	fade_->Initialize(
	    spriteBlack_.get(), textureHandleBlack_);


	
}

void GameScene::Update() {
	
	switch (sceneMode_) {

	case 0:

		// 各クラスの更新

		player_->Update();
		skydome_->Update();
		ground_->Update();
		enemy_->Update();

		// 追従カメラの更新
		followCamera_->Update();

		// 追従カメラのビュー行列をゲームシーンのビュープロジェクションにコピー;
		viewProjection_.matView = followCamera_->GetViewProjection().matView;

		// 追従カメラのプロジェクション行列をゲームシーンのビュープロジェクションにコピー;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		// ゲームシーンのビュープロジェクション行列の転送処理
		viewProjection_.TransferMatrix();

		// 衝突判定
		if (enemy_->GetY() == 0) {

			float dx = abs(player_->GetX() - enemy_->GetX());
			float dz = abs(player_->GetZ() - enemy_->GetZ());
			if (dx < 2 && dz < 2) {

				enemy_->Hit();
				hitCount_++;
			}
		}

		if (hitCount_ >= 10) {
			fade_->FadeOutStart();
		}

		if (fade_->IsEnd() == true) {
		sceneMode_ = 2;
			fade_->FadeInStart();
		}
		break;

		case 1:
		if (title_->Update() == true) {

			fade_->FadeOutStart();
		}
		if (fade_->IsEnd() == true) {
		
		        sceneMode_ = 0u;
			    hitCount_ = 0;
			    fade_->FadeInStart();
		}
		break;

		case 2:
		if (gameClear_->Update() == true) {
			    fade_->FadeOutStart();
			
		}
		if (fade_->IsEnd() == true) {
		
		sceneMode_ = 1u;
			    fade_->FadeInStart();
		
		}

		break;


		
	}

	fade_->Update();
	   
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	switch (sceneMode_) {

	case 0:

		// 各クラスの描画
		player_->Draw(viewProjection_);
		skydome_->Draw(viewProjection_);
		ground_->Draw(viewProjection_);
		enemy_->Draw(viewProjection_);

		break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	switch (sceneMode_) {

	case 1:

		title_->Draw();

		
		break;



		case 2:

		gameClear_->Draw();

		break;
	}

fade_->Draw();



	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
