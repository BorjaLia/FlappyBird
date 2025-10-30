#include "Obstacle.h"

namespace obstcl {

	void Init(Obstacle& obstacle)
	{
		obstacle = Obstacle();
		Reset(obstacle);
	}

	void Init(Obstacle obstacles[])
	{
		for (int o = 0; o < 4; o++)
		{
			Init(obstacles[o]);
		}
	}

	void Reset(Obstacle& obstacle)
	{
		obstacle = Obstacle();
		obstacle.pos.x = 1.0f + (obstacle.size.x / 2.0f);

		obstacle.pos.y = mth::GetRandomf((obstacle.size.y / 2.0f), 1.0f - (obstacle.size.y / 2.0f));

		obstacle.isActive = true;
	}

	void Reset(Obstacle obstacles[])
	{
		for (int o = 0; o < 4; o++)
		{
			Reset(obstacles[o]);
		}
	}

	void Update(Obstacle& obstacle)
	{
		if (!obstacle.isActive) {
			return;
		}

		obstacle.pos += obstacle.vel * rend::deltaTime;

		if (obstacle.pos.x + (obstacle.size.x / 2.0f) < 0.0f) {
			Reset(obstacle);
		}
	}

	void Update(Obstacle obstacles[])
	{
		for (int o = 0; o < 4; o++)
		{
			Update(obstacles[o]);
		}
	}

	void Draw(Obstacle& obstacle)
	{
		if (!obstacle.isActive) {
			return;
		}

		drw::Rectangle(obstacle.pos, obstacle.size, obstacle.color);
	}

	void Draw(Obstacle obstacles[])
	{
		for (int o = 0; o < 4; o++)
		{
			Draw(obstacles[o]);
		}
	}

}
