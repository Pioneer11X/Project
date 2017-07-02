#include "GUI.h"



GUI::GUI()
{
	
}


GUI * GUI::Instance()
{
	static GUI * instance = new GUI();

	return instance;
}


void GUI::Init(GLFWwindow * window)
{
	ImGui_ImplGlfwGL3_Init(window, false);
}

void GUI::Loop()
{
	ImGui_ImplGlfwGL3_NewFrame();

	// Menu
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Quit")) {
				// TODO: Add a global singleton variable to qui
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("Metrics");
			ImGui::MenuItem("Style Editor");
			ImGui::MenuItem("About ImGui");
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void GUI::Draw()
{
	ImGui::Render();
}

void GUI::End()
{
	ImGui_ImplGlfwGL3_Shutdown();
}

GUI::~GUI()
{
	if (nullptr != instance) {
		delete instance;
	}
}
