#ifndef WIDGETS_H
#define WIDGETS_H

#include "types.h"

#define IM_VEC2_CLASS_EXTRA                                                     \
    constexpr ImVec2(const yui::Vec2f& vec)                                     \
        : x(vec.x())                                                            \
        , y(vec.y())                                                            \
    {}                                                                          \
    operator yui::Vec2f() const {                                               \
        return { x, y };                                                        \
    }

#include <fmt/core.h>
#include <imgui.h>

#include <functional>
#include <string>

namespace yui {

/**
 * @brief   TODO
 */
enum class window_flag {
    None                        = ImGuiWindowFlags_None,
    NoTitleBar                  = ImGuiWindowFlags_NoTitleBar,
    NoResize                    = ImGuiWindowFlags_NoResize,
    NoMove                      = ImGuiWindowFlags_NoMove,
    NoScrollbar                 = ImGuiWindowFlags_NoScrollbar,
    NoScrollWithMouse           = ImGuiWindowFlags_NoScrollWithMouse,
    NoCollapse                  = ImGuiWindowFlags_NoCollapse,
    AlwaysAutoResize            = ImGuiWindowFlags_AlwaysAutoResize,
    NoBackground                = ImGuiWindowFlags_NoBackground,
    NoSavedSettings             = ImGuiWindowFlags_NoSavedSettings,
    NoMouseInputs               = ImGuiWindowFlags_NoMouseInputs,
    MenuBar                     = ImGuiWindowFlags_MenuBar,
    HorizontalScrollbar         = ImGuiWindowFlags_HorizontalScrollbar,
    NoFocusOnAppearing          = ImGuiWindowFlags_NoFocusOnAppearing,
    NoBringToFrontOnFocus       = ImGuiWindowFlags_NoBringToFrontOnFocus,
    AlwaysVerticalScrollbar     = ImGuiWindowFlags_AlwaysVerticalScrollbar,
    AlwaysHorizontalScrollbar   = ImGuiWindowFlags_AlwaysHorizontalScrollbar,
    AlwaysUseWindowPadding      = ImGuiWindowFlags_AlwaysUseWindowPadding,
    NoNavInputs                 = ImGuiWindowFlags_NoNavInputs,
    NoNavFocus                  = ImGuiWindowFlags_NoNavFocus,
    UnsavedDocument             = ImGuiWindowFlags_UnsavedDocument,
    NoNav                       = ImGuiWindowFlags_NoNav,
    NoDecoration                = ImGuiWindowFlags_NoDecoration,
    NoInputs                    = ImGuiWindowFlags_NoInputs,
};

inline int operator|(window_flag lhs, window_flag rhs) {
    return static_cast<int>(lhs) | static_cast<int>(rhs);
}

/**
 * @brief   TODO
 */
template <typename Derived>
class widget {
public:
    widget()                         = default;
    ~widget()                        = default;

    widget(const widget&)            = delete;
    widget(widget&&)                 = delete;
    widget& operator=(const widget&) = delete;
    widget& operator=(widget&&)      = delete;

    /**
     * @brief   Calls the `callback` between widgets
     */
    Derived& callback(std::invocable auto&& callback) {
        std::invoke(callback);
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Create a button which calls the `callback` upon clicking
     */
    Derived& button(const std::string& name, std::invocable auto&& callback) {
        if (ImGui::Button(name.c_str())) {
            std::invoke(callback);
        }
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Create a button with fixed size which calls the `callback` upon clicking
     */
    Derived& button(const std::string& name, const Vec2f& size = { 0, 0 }, std::invocable auto&& callback = [] {}) {
        if (ImGui::Button(name.c_str(), size)) {
            std::invoke(callback);
        }
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Create an invisible button
     */
    Derived& invisible_button(const std::string& name, const Vec2f& size, std::invocable auto&& callback) {
        if (ImGui::InvisibleButton(name.c_str(), size)) {
            std::invoke(callback);
        }
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Create a label
     */
    Derived& text(const std::string& msg) {
        ImGui::Text("%s", msg.c_str());
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Create a label with formatted text
     */
    template <typename... Args>
    Derived& text(const std::string& fmt, Args&&... args) {
        ImGui::Text("%s", fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)).c_str());
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Create an input box
     */
    template <typename T>
    Derived& input(const std::string& label, T* value) {
        if constexpr (std::is_same_v<T, int>) {
            ImGui::InputInt(label.c_str(), value);
        } else if constexpr (std::is_same_v<T, float>) {
            ImGui::InputFloat(label.c_str(), value);
        } else if constexpr (std::is_same_v<T, double>) {
            ImGui::InputDouble(label.c_str(), value);
        } else if constexpr (std::is_same_v<T, std::string>) {
            ImGui::InputText(
                label.c_str(),
                value->data(),
                value->capacity() + 1,
                ImGuiInputTextFlags_CallbackResize,
                [](ImGuiInputTextCallbackData* data) -> int {
                    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
                        std::string* str = static_cast<std::string*>(data->UserData);
                        str->resize(static_cast<std::size_t>(data->BufTextLen));
                        data->Buf = str->data();
                    }
                    return 0;
                },
            value
            );
        } else {
            static_assert(
                std::is_same_v<T, void> && !std::is_same_v<T, void>,
                "Only the following types are supported for input: int, float, double, std::string"
            );
        }
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Create a checkbox
     */
    Derived& checkbox(const std::string& label, bool* value) {
        ImGui::Checkbox(label.c_str(), value);
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Create a listbox
     */
    Derived& listbox(const std::string& label, std::invocable auto&& callback) {
        if (ImGui::BeginListBox(label.c_str())) {
            std::invoke(callback);
            ImGui::EndListBox();
        }
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Allow overlap for the current widget
     */
    Derived& allow_overlap() {
        ImGui::SetItemAllowOverlap();
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Set the next widget to be on the same line as the one before
     */
    Derived& same_line() {
        ImGui::SameLine();
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Create a dummy object (placeholder)
     */
    Derived& dummy(const Vec2f& size) {
        ImGui::Dummy(size);
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Set default focus for the current widget
     */
    Derived& focus() {
        ImGui::SetItemDefaultFocus();
        return *static_cast<Derived*>(this);
    }

    /**
     * @brief   Create a horizontal separator
     */
    Derived& separator() {
        ImGui::Separator();
        return *static_cast<Derived*>(this);
    }
};

/**
 * @brief   TODO
 */
class window_config {
public:
    window_config() = default;

    template <typename... Args>
        requires (std::is_same_v<Args, window_flag> && ...)
    window_config(Args&&... args) {
        m_flag = static_cast<int>(((std::forward<Args>(args)) | ...));
    }

    [[nodiscard]] int flag() const noexcept { return m_flag; }

private:
    int m_flag = static_cast<int>(window_flag::None);
};

/**
 * @brief   TODO
 */
class window : public widget<window> {
public:
    window(const std::string& title, const window_config& config = {}, bool* is_open = nullptr) {
        ImGui::Begin(title.c_str(), is_open, config.flag());
    }

    ~window() {
        ImGui::End();
    }

    window(const window&)            = delete;
    window(window&&)                 = delete;
    window& operator=(const window&) = delete;
    window& operator=(window&&)      = delete;

    /**
     * @brief   Create an image on the window
     */
    // template <typename TextureId>
    // window& image(TextureId id, const Vec2f& upper_left, const Vec2f& bottom_right) {
        // ImGui::GetWindowDrawList()->AddImage(
            // reinterpret_cast<void*>(id), upper_left, bottom_right
        // );
        // return *this;
    // }

    /**
     * @brief   Create an image on the window
     */
    template <typename TextureId>
    window& image(TextureId id, const Vec2f& size) {
        ImGui::Image(reinterpret_cast<void*>(id), size);
        return *this;
    }

    /**
     * @brief   Set the window size
     */
    window& size(const Vec2f& size) {
        ImGui::SetWindowSize(size);
        return *this;
    }
};

/**
 * @brief   TODO
 */
class popup : public widget<popup> {
public:
    popup(const std::string& name):
        m_name(name),
        m_active(ImGui::BeginPopupModal(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {}

    ~popup() {
        if (m_active) {
            ImGui::EndPopup();
        }
    }

    /**
     * @brief   TODO
     */
    void open() {
        ImGui::OpenPopup(m_name.c_str());
    }

private:
    std::string m_name;
    bool m_active;
};

/**
 * @brief   TODO
 */
class menu : public widget<menu> {
public:
    menu(const std::string& name):
        m_active(ImGui::BeginMenu(name.c_str()))
    {}

    ~menu() {
        if (m_active) {
            ImGui::EndMenu();
        }
    }

    menu(const menu&) = delete;
    menu(menu&&) = delete;
    menu& operator=(const menu&) = delete;
    menu& operator=(menu&&) = delete;

    /**
     * @brief   Create a menu item with a callback
     */
    menu& item(const std::string& name, std::invocable auto&& callback = [] {}, bool* selected = nullptr, const std::string& shortcut = "") {
        if (m_active) {
            if (ImGui::MenuItem(name.c_str(), shortcut == "" ? nullptr : shortcut.c_str(), selected)) {
                std::invoke(callback);
            }
        }
        return *this;
    }

private:
    bool m_active;
};

/**
 * @brief   TODO
 */
class main_menu : public widget<main_menu> {
public:
    main_menu():
        m_active(ImGui::BeginMainMenuBar())
    {}

    ~main_menu() {
        if (m_active) {
            ImGui::EndMainMenuBar();
        }
    }

    main_menu(const main_menu&) = delete;
    main_menu(main_menu&&) = delete;
    main_menu& operator=(const main_menu&) = delete;
    main_menu& operator=(main_menu&&) = delete;

    /**
     * @brief   TODO
     */
    yui::menu menu(const std::string& name) {
        return yui::menu(name);
    }

private:
    bool m_active;
};

} // namespace yui

#endif // WIDGETS_H
