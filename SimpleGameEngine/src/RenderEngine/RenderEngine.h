#pragma once

#ifndef SIMPLE_RENDERENGINE_H
#define SIMPLE_RENDERENGINE_H

#include <string>
#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <GameLogic/GameLogic.h>

typedef std::pair<Model*, const Shader*> ModelAndShader;
// This is a static class!
class RenderEngine
{
public:
	static bool init(std::string title = "Simple Game Engine");
	static void run();
	static void stop();

	// WindowSize
	static float SCR_WIDTH;
	static float SCR_HEIGHT;

	// Provided shaders
	static SkyboxShader skyboxShader;
	static LightShader defaultShader;

	static GLFWwindow* getWindow();
	static float getDeltaTime();

	static void setGameLogic(GameLogic& logic);

	static void disableCursor();
	static void enableCursor();
	
	// set the default color of background
	static void setBackGround(float R, float G, float B);
	
	// set the sky of scene
	static void setSkyBox(const std::string& path);

	// set camera
	static void setCamera(Camera& camera);

	// adjust models to display
	static void addModel(Model& model, const Shader& shader = defaultShader);
	static bool deleteModel(Model& model);

	// adjust lights (methods from defaultShader)
	static void setDirLight(int index, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	static void addDirLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	static void setPointLight(int index, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		float constant, float linear, float quadratic);
	static void addPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		float constant, float linear, float quadratic);
	static void setSpotLight(int index, glm::vec3 position, glm::vec3 direction, glm::vec3 diffuse, glm::vec3 specular,
		float constant, float linear, float quadratic, float cutoff, float outerCutoff);
	static void addSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 diffuse, glm::vec3 specular,
		float constant, float linear, float quadratic, float cutoff, float outerCutoff);

protected:
	// game logic
	static GameLogic* currentLogic;

	// Measures how fast the RenderEngine is working
	static float deltaTime, lastFrame;

	// window
	static std::string title;
	static GLFWwindow* window;

	// background
	static float bgR, bgG, bgB;
	static unsigned int sky, skyVAO, skyVBO;
	static bool haveSky;

	// caller functions
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void ProcessInput(GLFWwindow* window, float deltaTime);
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void DrawFrame(void);

	static Camera *camera;

	static std::vector<ModelAndShader> models;
};

#endif