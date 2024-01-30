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


	//自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());


	// タイトル(２Dスプライト)
	uint32_t fadeTexHandle = TextureManager::Load("title.png");
	fadeSprite_ = Sprite::Create(fadeTexHandle, {0, 0});

	// エンター(２Dスプライト)
	textureHandleEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandleEnter_, {400, 500});



	
	
}

void GameScene::Update() {
	
	switch (sceneMode_) { 
	
	case 0:

		// 各クラスの更新
		player_->Update();
		skydome_->Update();
		ground_->Update();
		
		

		// 追従カメラの更新
		followCamera_->Update();

		// 追従カメラのビュー行列をゲームシーンのビュープロジェクションにコピー;
		viewProjection_.matView = followCamera_->GetViewProjection().matView;

		// 追従カメラのプロジェクション行列をゲームシーンのビュープロジェクションにコピー;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		// ゲームシーンのビュープロジェクション行列の転送処理
		viewProjection_.TransferMatrix();

		StartTimer_ -= 1;


		if (StartTimer_ == 0 ) {
		
		sceneMode_ = 1;
			StartTimer_ = 1000;
		fadeColor_.w += 0.005f;
		fadeSprite_->SetColor(fadeColor_);
		}

		

		break;
		

	case 1:
			  
		if (input_->TriggerKey(DIK_RETURN)) {
		sceneMode_ = 0;
		
		}

		gameTimer_ += 1;

		fadeColor_.w -= 0.005f;
		fadeSprite_->SetColor(fadeColor_);
			break;

	case 2:

		if (input_->TriggerKey(DIK_RETURN)) {
		sceneMode_ = 1;
		    }
				break;


	}
	
	
	


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



	switch (sceneMode_) {

		case 0:
		        fadeSprite_->Draw();
			break;

     case 1:
		    fadeSprite_->Draw();



		
			// エンター表示
			if (gameTimer_ % 40 >= 20) {
				spriteEnter_->Draw();
			}

		    




			

		 break;

    
	}





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
		 break;

		 case 1:

			 break;


			 case 2:

				 break;







	}






	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);


	switch (sceneMode_) {

	case 0:

		         break;

	case 1:

		         break;

	case 2:

		         break;
	}




	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	fadeSprite_->Draw();



	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}





















