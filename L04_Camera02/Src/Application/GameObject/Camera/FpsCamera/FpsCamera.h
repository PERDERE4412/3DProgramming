#pragma once

#include "../BaseCamera.h"

class FpsCamera : public BaseCamera
{
public:

	FpsCamera() { Init(); }
	~FpsCamera()override {}

	void Update()override;

private:

	void Init()override;
};