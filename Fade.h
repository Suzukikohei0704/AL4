#pragma once
#include "Sprite.h"

class Fade {

	

	

	public:
		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize(  Sprite* sprite, uint32_t textureHandle );

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		void FadeInStart();
	    void FadeOutStart();
	    bool IsEnd() { return endFlag_; }



	private:
		// 背景
		uint32_t textureHandle_ = 0u;
		Sprite* sprite_;

		

		float timer_ = 1.0f;
	
		//フェードモード(0無し,1フェードイン,2フェードアウト)

		uint32_t mode_ = 1u;

		bool endFlag_ = false;


};
