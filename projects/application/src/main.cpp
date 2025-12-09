

#include "pch.h"
#include "Core/Core.h"
#include "Core/Window.h"
#include "Core/Time.h"
#include "Core/Input.h"

#include "Objects/Sprite.h"
#include "Objects/Resource.h"

#include "OpenGL/UI/FontAtlas.h"
#include "Objects/Text.h"

#include "Core/Font.h"

// test program
int main() {
	using namespace OpenGL;

	Core::FontSpecification font_spec;
	font_spec.Name = "Arial";
	font_spec.Path = "assets/Roboto-Black.ttf";
	font_spec.FaceIndex = 0;
	font_spec.Size = 28;

	Core::Font* font = new Core::Font(font_spec);

	std::cout << "m_FTLibrary: " << font->GetLibrary() << std::endl;
	std::cout << "m_Face: " << font->GetFace() << std::endl;


	Core::WindowSpecification Specs;
	Specs.Title = "Platform - " + std::string(PLATFORM) + " API - OpenGL\n";
	Specs.Size.first = 1600;
	Specs.Size.second = 900;
	Specs.VidMode = Core::VideoMode::Windowed;
	Specs.WinState = Core::WindowState::Maximized | Core::WindowState::InputFocused;
	Specs.VSync = false;

	Core::Window* window = new Core::Window(Specs);
	Renderer* renderer = new Renderer();

	FontAtlas* font_atlas_test = new FontAtlas("TextAtlas", font);

	Log("Width : ", font_atlas_test->GetWidth());
	Log("Height : ", font_atlas_test->GetHeight());

	Shader* text_shader = new Shader("TextShader.GLSL", "assets/TextShader.GLSL");

	Objects::UI::TextRendererData tex_data;
	tex_data.TextFontAtlas = font_atlas_test;
	tex_data.TextShader = text_shader;

	Objects::UI::TextRenderer* text_renderer = new Objects::UI::TextRenderer(tex_data, renderer);

	renderer->SetViewport(window->GetWindowHandle());

	Core::Input::Init(window->GetWindowHandle());
	Core::Time::Init();

	IMesh* quad_mesh = new Mesh::Quad();
	IMesh* tri_mesh = new Mesh::Triangle();

	Shader* mesh_shader = new Shader("MeshShader.GLSL", "assets/MeshShader.GLSL");

	Texture2D* bird_texture = new Texture2D("BirdTexture", "assets/bird.png");
	Game::Sprite* bird_sprite = new Game::Sprite("Bird");

	Mat4 view_matrix(1.0f);
	view_matrix = glm::translate(view_matrix, Vector3(300.0f, 150.0f, 0.0f));

	Mat4 projection_matrix(1.0f);
	projection_matrix = glm::ortho(0.0f, (float)window->GetWindowSize().first, 0.0f, (float)window->GetWindowSize().second, -1.0f, 1.0f);

	bird_sprite->SetShader(mesh_shader);
	bird_sprite->SetTexture(bird_texture);
	bird_sprite->SetMesh(quad_mesh);

	Vector2 birdpos(100.0f, 50.0f);
	float gravity = -200.0f; 
	float jumpVelocity = 150.0f; 
	float birdVelocity = 0.0f;


	bird_sprite->SetSize({ 50.0f,50.0f });
	Vector2 cursor_pos(1.0f);

	renderer->SetProjectionMatrix(projection_matrix);
	renderer->SetViewMatrix(view_matrix);

	Transform2D t;
	t.Size = { 1.0f , 0.0f };
	t.Position = { 100.0f, 450.0f };
	t.Rotation = 10.0f;


	while (window->Running()) {
		renderer->Clear({ 0.3f,0.2f,0.3f,1.0f });

		Color sprite_color = Color(255.0f);

		cursor_pos = Vector2((float)Core::Input::GetMousePosX(), (float)Core::Input::GetMousePosY());
		//std::cout << "Cursor Pos (X, Y) : " << cursor_pos.x << ", " << cursor_pos.y << '\n';

		if (Core::Input::IsKeyPressed(KeyCode::Escape))
			window->Shutdown();

		if (Core::Input::IsKeyDown(KeyCode::W))
			birdpos.y += 100.0f * (float)Core::Time::GetDeltaTime();

		if (Core::Input::IsKeyDown(KeyCode::S))
			birdpos.y -= 100.0f * (float)Core::Time::GetDeltaTime();

		if (Core::Input::IsKeyDown(KeyCode::A))
			birdpos.x -= 100.0f * (float)Core::Time::GetDeltaTime();

		if (Core::Input::IsKeyDown(KeyCode::D))
			birdpos.x += 100.0f * (float)Core::Time::GetDeltaTime();

		if (Core::Input::IsKeyPressed(KeyCode::Space)) 
			birdVelocity = jumpVelocity;

		if (Core::Input::IsMouseButtonDown(MouseCode::Left))
			sprite_color = Color(255.0f, 0.0f, 0.0f);

		if (Core::Input::IsMouseButtonReleased(MouseCode::Left))
			sprite_color = Color(0.0f, 255.0f, 0.0f, 150.0f);

		if (Core::Input::IsKeyPressed(KeyCode::F11)) {
			window->SetVideoMode(Core::VideoMode::Fullscreen);
		}
			
		if (Core::Input::IsKeyPressed(KeyCode::F10)) {
			window->SetVideoMode(Core::VideoMode::Borderless);
		}

		if (Core::Input::IsKeyPressed(KeyCode::F9)) {
			window->SetVideoMode(Core::VideoMode::Windowed);
		}

		text_renderer->DrawText("FPS:" + std::to_string(Core::Time::GetFPS()), {100.0f, 450.0f}, 1.0f, Color(255, 0, 0));
		text_renderer->DrawText("Elapsed:" + std::to_string(Core::Time::GetElapsedTime()), {100.0f, 500.0f}, 1.0f, Color(0, 255, 0));
		text_renderer->DrawText("Delta:" + std::to_string(Core::Time::GetDeltaTime()), {100.0f, 550.0f}, 1.0f, Color(0, 0, 100));

		birdVelocity += gravity * Core::Time::GetDeltaTime();
		birdpos.y += birdVelocity * Core::Time::GetDeltaTime();

		// draw
		bird_sprite->SetPosition(birdpos);
		bird_sprite->SetColor(sprite_color);

		float right = bird_sprite->GetPosition().x + bird_sprite->GetSize().x;
		float left = bird_sprite->GetPosition().x;
		float bottom = bird_sprite->GetPosition().y;
		float top = bird_sprite->GetPosition().y + bird_sprite->GetSize().y;

		bird_sprite->Draw(renderer);

		Core::Input::Update();
		Core::Time::Update();
		window->Update();
	}

	delete window;
	delete renderer;
	delete quad_mesh;
	delete tri_mesh;
	delete mesh_shader;
	delete bird_texture;
	delete bird_sprite;
	delete font;
	delete font_atlas_test;
}