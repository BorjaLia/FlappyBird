#include "BorjaLib.h"
#include "Ball.h"

//TEMPORALMENTE AQUI
float gravity = 1.2f;

namespace bll {

	void Init(Ball& ball)
	{
		ball = Ball();
		Reset(ball);
	}

	void Reset(Ball& ball)
	{
		ball = Ball();
		ball.isActive = true;
		ball.isAlive = true;
	}

	void UpdateInput(Ball& ball)
	{
		if (!ball.isAlive || !ball.isActive) {
			return;
		}

		if (ctrl::IsKeyPressed(ball.upKey)) {
			ball.vel.y = ball.moveForce;
		}

		if (ctrl::IsKeyPressed(ball.downKey)) {
			ball.vel.y = -ball.moveForce;
		}

		//if (ctrl::IsMousePressed(ball.jumpButton)) {
		//	ball.vel.y = ball.jumpForce;
		//}
	}

	void Update(Ball& ball)
	{
		if (!ball.isAlive || !ball.isActive) {
			return;
		}

		//ball.vel.y -= gravity * rend::deltaTime;

		ball.pos += ball.vel * rend::deltaTime;
	}

	void Draw(Ball& ball)
	{
		if (!ball.isActive) {
			return;
		}
		drw::Circle(ball.pos, ball.size, ball.color);
	}
}