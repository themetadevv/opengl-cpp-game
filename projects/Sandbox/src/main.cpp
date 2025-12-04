

#include "pch.h"
#include "Core/Core.h"
#include "Core/Window.h"

#include "Platform/Windows/WindowsWindow.h"

#include "Game/Level.h"
#include "Game/Sprite.h"
#include "Game/ResManager.h"
#include "Game/Time.h"

// test program
int main() {
	using namespace Platform::OpenGL;

	Core::WindowData Specs;
	Specs.Title = "Platform - " + std::string(PLATFORM) + " API - OpenGL\n";
	Specs.Width = 1600;
	Specs.Height = 900;
	Specs.VSync = true;

	auto& time = Game::Time::GetTime();

	Core::IWindow* window = new Platform::Windows::Window(Specs);
	Renderer* renderer = new Renderer();

	IMesh* mesh = new Mesh::Quad();
	Shader* mesh_shader = new Shader("MeshShader.GLSL", "assets/MeshShader.GLSL");

	Texture2D* bird_texture = new Texture2D("BirdTexture", "assets/bird.png");
	Game::Sprite* bird_sprite = new Game::Sprite("Bird", renderer);
	
	bird_sprite->SetMesh(mesh);
	bird_sprite->SetShader(mesh_shader);
	bird_sprite->SetTexture(bird_texture);

	Mat4 view_matrix(1.0f);
	view_matrix = glm::translate(view_matrix, Vector3(300.0f, 150.0f, 0.0f));

	Mat4 projection_matrix(1.0f);
	projection_matrix = glm::ortho(0.0f, 1366.0f, 0.0f, 768.0f, -1.0f, 1.0f);

	while (window->Running()) {
		renderer->Clear({ 0.3f, 0.2f, 0.3f, 1.0f });
		time.Update();

		bird_sprite->SetPosition({ 100.0f, 50.0f });
		bird_sprite->SetSize({ 50.0f, 50.0f });
		bird_sprite->SetMVP(view_matrix, projection_matrix);

		bird_sprite->Draw();

		window->OnUpdate();
	}

	delete window;
	delete renderer;
	delete mesh;
	delete mesh_shader;
	delete bird_texture;
	delete bird_sprite;
}