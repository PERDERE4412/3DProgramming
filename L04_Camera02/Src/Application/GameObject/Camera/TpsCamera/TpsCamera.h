#pragma once

#include "../BaseCamera.h"

class TpsCamera : public BaseCamera
{
public:

	TpsCamera() { Init(); }
	~TpsCamera()override {}

	void Update()override;

private:

	void Init()override;
};