#include "followCamera.h"




void followCamera::Initialize() {

	viewProjection_.Initialize();


}



void followCamera::Update() {


	if (target_) {
	
	Vector3 offset = {0.0f, 2.0f, -10.0f};



	viewProjection_.translation_ = target_->translation_ + offset;
	
	}


		viewProjection_.farZ = 2000.0f;
		viewProjection_.UpdateMatrix();


}





















