#include "GUI.h"


GUI::GUI()
{

}


void GUI::Init(GLFWwindow * window)
{
	ImGui_ImplGlfwGL3_Init(window, false);
}

bool GUI::Loop()
{

	bool returnVar = true;

	ImGui_ImplGlfwGL3_NewFrame();

	// Menu
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Quit")) {
				returnVar = false;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Shaders"))
		{
			ImGui::MenuItem("Original");
			ImGui::MenuItem("Grayscale");
			ImGui::MenuItem("About ImGui");
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	return returnVar;
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

}
