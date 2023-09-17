#include "yui/gui.h"

namespace yui {

gui::gui(const std::string& title, const gui_config& cfg):
    m_glsl_version(glsl_version()),
    m_dimensions(cfg.window_size)
{
    glfwSetErrorCallback([]([[maybe_unused]] int err, [[maybe_unused]] const char* msg) { /* logging::error("{} {}", err, msg); */ });

    if (not glfwInit()) {
        throw std::runtime_error("Failed to initialize GUI!");
    }

    m_window = glfwCreateWindow(
        static_cast<int>(m_dimensions.x()),
        static_cast<int>(m_dimensions.y()),
        title.c_str(),
        nullptr,
        nullptr
    );

    if (m_window == nullptr) {
        throw std::runtime_error("Failed to initialize window!");
    }

    glfwMakeContextCurrent(m_window);

    // logging::info("OpenGL Version: {}", std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

    // Enable vsync
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    if (not cfg.fontpath.empty()) {
        io.Fonts->AddFontFromFileTTF(cfg.fontpath.c_str(), cfg.fontsize);
    }

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);

    ImGui_ImplOpenGL2_Init();
}

gui::gui(gui&& other) noexcept {
    m_window = other.m_window;
    m_glsl_version = other.m_glsl_version;
    m_dimensions = other.m_dimensions;

    other.m_window = nullptr;
}

gui::~gui() {
    if (m_window == nullptr) {
        return;
    }

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

std::string_view gui::glsl_version() {
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    return "#version 100";
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                // Required on Mac
    return "#version 150";
#else
    // GL 3.0 + GLSL 130
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);   // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);             // 3.0+ only
    return "#version 130";
#endif
}

} // namespace yui
