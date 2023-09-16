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

class image {
public:
    image(yui::vec2 dimensions)
        : m_dimensions(dimensions)
        , m_data(
            static_cast<std::size_t>(area(dimensions)),
            0xFFFFFFFF
        )
    {}

    image(const image&) = delete;
    image(image&&) = delete;
    image& operator=(const image&) = delete;
    image& operator=(image&&) = delete;

    [[nodiscard]] const auto* data() const noexcept { return m_data.data(); }
    [[nodiscard]] auto* data()             noexcept { return m_data.data(); }
    [[nodiscard]] auto width()       const noexcept { return m_dimensions.x(); }
    [[nodiscard]] auto height()      const noexcept { return m_dimensions.y(); }
    [[nodiscard]] auto dimensions()  const noexcept { return m_dimensions; }
    [[nodiscard]] auto& texture_id()       noexcept { return m_texture_id; }

    [[nodiscard]] auto& at(int x, int y) noexcept {
        using SizeT = decltype(m_data)::size_type;
        return m_data[static_cast<SizeT>(x * static_cast<int>(height()) + y)];
    }

private:
    yui::vec2 m_dimensions;
    std::vector<std::uint32_t> m_data;
    unsigned int m_texture_id;
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

    /**
     * @brief   Display an image
     */
    GLuint load(class image& img) {
        // Create a OpenGL texture identifier
        glGenTextures(1, &img.texture_id());
        glBindTexture(GL_TEXTURE_2D, img.texture_id());

        // Setup filtering parameters for display
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<int>(img.width()), static_cast<int>(img.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data());

        return img.texture_id();
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
