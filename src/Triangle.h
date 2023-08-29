#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

class Triangle {
public:
    void run();

private:
    GLFWwindow *window;
    VkInstance instance;
    const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    void initWindow();

    void initVulkan();

    void createInstance();

    void mainLoop();

    void cleanup();

    bool checkValidationLayerSupport();
};
