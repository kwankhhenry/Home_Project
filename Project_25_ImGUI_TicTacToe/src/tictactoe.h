#pragma once
#include <array>
#include "app_base.h"

enum class CellState
{
    Empty,
    Circle,
    Cross
};

class TicTacToe : public AppBase<TicTacToe>
{
public:
    TicTacToe() = default;
    ~TicTacToe() = default;

    void StartUp()
    {
    }

    void Update()
    {
        ImGui::Begin("Tic Tac Toe");
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        ImGuiIO& io = ImGui::GetIO();

        if(!io.WantCaptureMouse){
            if(button == ImGuiMouseButton_Left && action == 1)
                clicked = true;;
        }
        else if(button == ImGuiMouseButton_Left && action == 0){
            clicked = false; 
        }
        //ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
    }

    static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
    {
        ImGuiIO& io = ImGui::GetIO();

        if(!io.WantCaptureMouse){
            mouse_x = xpos;
            mouse_y = ypos;
        }
        //ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
    }

private:
    // Our states
    std::array<std::array<CellState, 3>, 3> game_state = {{
        {{CellState::Empty, CellState::Empty, CellState::Empty}},
        {{CellState::Cross, CellState::Cross, CellState::Cross}},
        {{CellState::Circle, CellState::Circle, CellState::Circle}}
    }};
    static int mouse_x;
    static int mouse_y;
    static bool clicked;
};

int TicTacToe::mouse_x = 0;
int TicTacToe::mouse_y = 0;
bool TicTacToe::clicked = false;