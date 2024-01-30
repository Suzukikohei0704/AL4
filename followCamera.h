#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"








class followCamera {

	public:






	void Initialize();






	void Update();


	void SetTarget(const WorldTransform* target) { target_ = target; }

	const ViewProjection& GetViewProjection() { return viewProjection_; }






	private:
	// ビュープロジェクション
	ViewProjection viewProjection_;


	const WorldTransform* target_ = nullptr;



};
