#include "BorjaLib.h"
#include "Ball.h"
#include "Obstacle.h"

int main() {

	enum class GameState {
		MAIN_MENU,
		GAMEPLAY,
		CREDITS,
		PAUSED
	};

	bool isRunning = true;
	bLib::Init("Flappy Bird");
	GameState currentState = GameState::MAIN_MENU;

	float gameTimer = 0.0f;
	//const int MOUSE_PARTICLE_COUNT = 5;

	//Menu
	btn::Button playButton;
	btn::Button creditsButton;
	btn::Button exitButton;

	// Cr�ditos
	btn::Button backButton;
	drw::TextData creditsTextData;

	// Gameplay
	btn::Button pauseButton;
	drw::TextData scoreTextData;
	//drw::AnimationData mouseAnim;
	//prtcl::ParticleActivator mouseParticleActivator;
	//prtcl::ParticleData mouseParticles[MOUSE_PARTICLE_COUNT]; // Array est�tico

	bll::Ball ball;
	bll::Init(ball);

	const int maxObstacles = 5;

	obstcl::Obstacle obstacles[maxObstacles];
	obstcl::Init(obstacles[0]);

	// Pausa
	btn::Button returnButton;
	btn::Button exitPauseButton;

	//drw::SpriteData fireFrame1;
	//fireFrame1.file = "res/sprites/fire1.png";
	//fireFrame1.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrame2;
	//fireFrame2.file = "res/sprites/fire2.png";
	//fireFrame2.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrame3;
	//fireFrame3.file = "res/sprites/fire3.png";
	//fireFrame3.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrame4;
	//fireFrame4.file = "res/sprites/fire4.png";
	//fireFrame4.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrames[] = { fireFrame1, fireFrame2, fireFrame3, fireFrame4 };

	//mouseAnim.duration = 0.25f;
	//drw::InitAnimData(mouseAnim, fireFrames, 4);

	// Inicializacion

	vec::Vector2 buttonSize = { 0.3f, 0.1f };

	//Menu
	playButton.pos = { 0.5f, 0.6f };
	playButton.size = buttonSize;
	playButton.useSprite = true;
	playButton.textData.text = "Play";
	playButton.textColor = WHITE_B;
	btn::Init(playButton);

	creditsButton.pos = { 0.5f, 0.5f };
	creditsButton.size = buttonSize;
	creditsButton.useSprite = true;
	creditsButton.textData.text = "Credits";
	creditsButton.textColor = WHITE_B;
	btn::Init(creditsButton);

	exitButton.pos = { 0.5f, 0.4f };
	exitButton.size = buttonSize;
	exitButton.useSprite = true;
	exitButton.textData.text = "Exit";
	exitButton.textColor = WHITE_B;
	btn::Init(exitButton);

	//Cr�ditos
	backButton.pos = { 0.5f, 0.3f };
	backButton.size = buttonSize;
	backButton.useSprite = true;
	backButton.textData.text = "Back";
	backButton.textColor = WHITE_B;
	btn::Init(backButton);

	creditsTextData.fontSize = 0.05f;
	creditsTextData.text = "Made by Borja Lia";

	//Gameplay
	pauseButton.pos = { 0.5f, 0.9f };
	pauseButton.size = buttonSize;
	pauseButton.useSprite = true;
	pauseButton.textData.text = "Pause";
	pauseButton.textColor = WHITE_B;
	btn::Init(pauseButton);

	scoreTextData.fontSize = 0.1f;

	//mouseParticleActivator.loop = true;
	//mouseParticleActivator.animated = true;
	//mouseParticleActivator.animation = mouseAnim;
	//mouseParticleActivator.amount = MOUSE_PARTICLE_COUNT;
	//mouseParticleActivator.lifetime = { 0.2f, 0.5f };
	//mouseParticleActivator.direction = { 0.0f, -1.0f };
	//mouseParticleActivator.spread = 180.0f;
	//mouseParticleActivator.minSize = { 0.005f, 0.005f };
	//mouseParticleActivator.maxSize = { 0.02f, 0.02f };
	//mouseParticleActivator.speed = { 0.1f, 0.3f };
	//prtcl::Init(mouseParticleActivator, mouseParticles);


	returnButton.pos = { 0.5f, 0.6f };
	returnButton.size = buttonSize;
	returnButton.useSprite = true;
	returnButton.textData.text = "Return";
	returnButton.textColor = WHITE_B;
	btn::Init(returnButton);

	exitPauseButton.pos = { 0.5f, 0.5f };
	exitPauseButton.size = buttonSize;
	exitPauseButton.useSprite = true;
	exitPauseButton.textData.text = "Exit to Menu";
	exitPauseButton.textColor = WHITE_B;
	btn::Init(exitPauseButton);

	while (isRunning) {

		isRunning = !rend::ShouldExit();

		//Update
		bLib::UpdateStart();

		switch (currentState)
		{
		case GameState::MAIN_MENU:

			btn::UpdateInput(playButton);
			btn::UpdateInput(creditsButton);
			btn::UpdateInput(exitButton);

			if (playButton.signal) {
				currentState = GameState::GAMEPLAY;
				gameTimer = 0.0f;
				bll::Reset(ball);
				obstcl::Reset(obstacles[0]);
			}
			if (creditsButton.signal) {
				currentState = GameState::CREDITS;
			}
			if (exitButton.signal) {
				isRunning = false;
			}
			break;

		case GameState::GAMEPLAY:
			
			gameTimer += rend::deltaTime;

			btn::UpdateInput(pauseButton);
			if (pauseButton.signal) {
				currentState = GameState::PAUSED;
			}

			bll::UpdateInput(ball);

			obstcl::Update(obstacles);

			bll::Update(ball);

			for (int o = 0; o < 4; o++)
			{
				if (coll::RecOnRec(ball.pos, ball.size, obstacles[o].pos, obstacles[o].size, ball.crashPoint)) {
					ball.isAlive = false;
					ball.color = GREY_B;
					ball.vel = 0.0f;
					//currentState = GameState::PAUSED;
				}
			}

			//mouseParticleActivator.pos = rend::mousePos;
			//prtcl::Update(mouseParticleActivator, mouseParticles);
			
			break;

		case GameState::CREDITS:

			btn::UpdateInput(backButton);
			if (backButton.signal) {
				currentState = GameState::MAIN_MENU;
			}
			break;

		case GameState::PAUSED:

			btn::UpdateInput(returnButton);
			btn::UpdateInput(exitPauseButton);

			if (returnButton.signal) {
				currentState = GameState::GAMEPLAY;
			}
			if (exitPauseButton.signal) {
				currentState = GameState::MAIN_MENU;
			}
			break;
		}

		bLib::UpdateEnd();

		//Draw
		drw::Begin();
		drw::Clear(DARKBLUE_B);

		switch (currentState)
		{
		case GameState::MAIN_MENU:

			btn::Draw(playButton);
			btn::Draw(creditsButton);
			btn::Draw(exitButton);
			break;

		case GameState::GAMEPLAY:

			//prtcl::Draw(mouseParticles);

			obstcl::Draw(obstacles);

			bll::Draw(ball);

			btn::Draw(pauseButton);

			scoreTextData.text = std::to_string(gameTimer);
			drw::Text(scoreTextData.text.c_str(),scoreTextData, { 0.5f, 0.5f }, scoreTextData.fontSize, { 0,0 }, WHITE_B);
			break;

		case GameState::CREDITS:

			btn::Draw(backButton);
			drw::Text(creditsTextData.text.c_str(), creditsTextData, { 0.5f, 0.6f }, creditsTextData.fontSize, { 0,0 }, WHITE_B);
			break;

		case GameState::PAUSED:

			btn::Draw(returnButton);
			btn::Draw(exitPauseButton);

			scoreTextData.text = std::to_string(gameTimer);
			drw::Text(scoreTextData.text.c_str(), scoreTextData, { 0.5f, 0.3f }, scoreTextData.fontSize, { 0,0 }, WHITE_B);
			break;
		}

		drw::End();

		//Sounds

	}

	rend::Close();
	return 0;
}