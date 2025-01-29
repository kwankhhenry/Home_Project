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
        
        for(int row = 0; row < 3; ++row){
            for(int col = 0; col < 3; ++col){
                DrawCell(row, col);
            }
        }
        ImGui::End();
    }

    void DrawCell(int row, int col){
        int cell_width = 100;
        int cell_height = 100;
        ImVec2 top_left = ImVec2(cell_width * col, cell_height * row);
        ImVec2 bottom_right = ImVec2(cell_width * (col + 1), cell_height * (row + 1));

        // Draw the grid
        ImDrawList* draw = ImGui::GetBackgroundDrawList();
        draw->AddRect(top_left, 
                      bottom_right, 
                      ImGui::GetColorU32(ImGuiCol_Text));

        // Draw the symbol according to the game state
        int symbol_size = 50;
        ImVec2 center_pos = ImVec2(top_left.x + cell_width/2, 
                                   top_left.y + cell_height/2);
        if(game_state[row][col] == CellState::Cross){
            // Draw a cross
            ImVec2 tl(center_pos.x - symbol_size/2, center_pos.y - symbol_size/2);
            ImVec2 br(center_pos.x + symbol_size/2, center_pos.y + symbol_size/2);

            ImVec2 tr(center_pos.x + symbol_size/2, center_pos.y - symbol_size/2);
            ImVec2 bl(center_pos.x - symbol_size/2, center_pos.y + symbol_size/2);
            draw->AddLine(tl, br, ImGui::GetColorU32(ImGuiCol_Text));
            draw->AddLine(tr, bl, ImGui::GetColorU32(ImGuiCol_Text));
        }
        else if(game_state[row][col] == CellState::Circle){
            // Draw a circle
            draw->AddCircle(center_pos, symbol_size / 2, ImGui::GetColorU32(ImGuiCol_Text));
        }
        else{
            // Draw nothing
            ImGui::Text("");
        }

        // When mouse hovered over the cell
        if(mouse_x > top_left.x && mouse_x < bottom_right.x &&
           mouse_y > top_left.y && mouse_y < bottom_right.y &&
           game_state[row][col] == CellState::Empty){
            draw->AddRect(ImVec2(top_left.x, top_left.y), 
                          ImVec2(bottom_right.x, bottom_right.y), 
                          ImGui::GetColorU32(ImGuiCol_ButtonActive),
                          0.0f, 0, 4.0f);
            /*if(game_state[row][col] == CellState::Empty){
                game_state[row][col] = CellState::Cross;
            }*/
        }
    }

    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        ImGuiIO& io = ImGui::GetIO();

        if(!io.WantCaptureMouse){
            if(button == ImGuiMouseButton_Left && action == 1){
                    clicked = true;
            }
            else if(button == ImGuiMouseButton_Left && action == 0){
                clicked = false; 
            }
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