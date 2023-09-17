#ifndef GUI_H
#define GUI_H

#include "types.h"
#include "widgets.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl2.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

namespace yui {

struct gui_config {
    vec2 window_size;
    std::string fontpath;
    float fontsize;
};

/**
 * @brief   Wrapper class around GLFW and ImGUI
 */
class gui {
public:
    gui(const std::string& title, const gui_config& cfg);
    ~gui();

    gui(const gui&)             = delete;
    gui(gui&& other) noexcept;
    gui& operator=(const gui&)  = delete;
    gui& operator=(gui&&)       = delete;

    void run(std::invocable auto&& callback);

    /**
     * @brief   TODO
     */
    class main_menu main_menu() {
        return yui::main_menu();
    }

    /**
     * @brief   TODO
     */
    class popup popup(const std::string& name) {
        return yui::popup(name);
    }

    /**
     * @brief   TODO
     */
    class window window(const std::string& title, const window_config& config, bool* is_open = nullptr) {
        return yui::window(title, config, is_open);
    }

    [[nodiscard]] inline auto dimensions() const noexcept { return m_dimensions; }
    [[nodiscard]] inline auto height() const noexcept { return m_height; }
    [[nodiscard]] inline auto width() const noexcept { return m_width; }

private:
    std::string_view m_glsl_version;
    GLFWwindow* m_window = nullptr;
    vec2 m_dimensions;
    int m_width, m_height;

    static void clear_color(const vec4& color);
    static std::string_view glsl_version();
};

/**
 * @brief   Event-loop
 */
void gui::run(std::invocable auto&& callback) {
    while (not glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        glfwGetWindowSize(m_window, &m_width, &m_height);

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        clear_color(color::black);

        std::invoke(callback);

        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window);
    }
}

/**
 * @brief   TODO
 */
inline void gui::clear_color(const vec4& color) {
    glClearColor(
        color.r() * color.a(),
        color.g() * color.a(),
        color.b() * color.a(),
        color.a()
    );

    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace yui

#endif // GUI_H
