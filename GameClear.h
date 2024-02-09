#pragma once
#include "Input.h"
#include "Sprite.h"

class GameClear {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(
	    Sprite* sprite, uint32_t textureHandle, Sprite* spriteKey, uint32_t textureHandleKey);

	/// <summary>
	/// 更新
	/// </summary>
	bool Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// 背景
	uint32_t textureHandle_ = 0u;
	Sprite* sprite_;

	// キー
	uint32_t textureHandleKey_ = 0u;
	Sprite* spriteKey_;

	Input* input_ = nullptr;

	uint32_t timer_ = 0;
};
