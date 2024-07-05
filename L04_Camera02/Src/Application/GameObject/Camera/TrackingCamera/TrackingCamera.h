#pragma once

#include "../BaseCamera.h"

class TrackingCamera :public BaseCamera
{
public:

	TrackingCamera() { Init(); }
	~TrackingCamera()override {}

	void Update()override;

private:

	void Init()override;
};