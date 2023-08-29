#include <cstring>
#include "Triangle.h"

void Triangle::run() {
    this->initVulkan();
    this->mainLoop();
    this->cleanup();
}


void Triangle::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);                                     // 使glfw不要创建OpenGL
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);                                       // 关闭窗口自动调整

    this->window = glfwCreateWindow(1024, 768, "My Fuckin Vulkan", nullptr, nullptr); // 创建窗口
}


void Triangle::initVulkan() {
    createInstance();
}


// 创建vk实例
void Triangle::createInstance() {
    if (enableValidationLayers && !this->checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};

    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // VkInstanceCreateInfo(非可选结构)结构为global extension和validation layer指定详细设置.
    VkInstanceCreateInfo createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // global extension 设置
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    /*
     * Validation layer:
     * 1.Checking the values of parameters against the specification to detect misuse.
     * 2.Tracking creation and destruction of objects to find resource leaks.
     * 3.Checking thread safety by tracking the threads that calls originate from.
     * 4.Logging every call and its parameters to the standard output.
     * 5.Tracing Vulkan calls for profiling and replaying.
     */
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    // Create Vkinstance
    VkResult result = vkCreateInstance(&createInfo, nullptr, &this->instance);

    // 报错
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}


void Triangle::mainLoop() {
    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
    }
}


void Triangle::cleanup() {
    vkDestroyInstance(this->instance, nullptr);

    glfwDestroyWindow(this->window);

    glfwTerminate();
}


bool Triangle::checkValidationLayerSupport() {
    uint32_t layerCount;

    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);

    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName : this->validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

