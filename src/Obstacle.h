#pragma once

#include "BorjaLib.h"

namespace obstcl {

	struct Obstacle {

		bool isActive = false;

		vec::Vector2 pos = { 1.25f,1.25f };

		vec::Vector2 vel = { -0.75f,0.0f };

		vec::Vector2 size = { 0.05f,0.25f };

		bColor color = DARKGREEN_B;
	};

	void Init(Obstacle& obstacle);
	void Init(Obstacle obstacles[]);

	void Reset(Obstacle& obstacle);
	void Reset(Obstacle obstacles[]);

	void Update(Obstacle& obstacle);
	void Update(Obstacle obstacles[]);

	void Draw(Obstacle& obstacle);
	void Draw(Obstacle obstacles[]);
}