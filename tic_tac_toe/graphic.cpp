#include "graphic.h"

#include <cassert>

#include "raylib.h"

static const char* get_status_text(const GameState& state)
{
    switch (state.status)
    {
        case GameStatus::Playing:
        {
            if (state.currentPlayer == Player::X)
            {
                return "Turn: X";
            }
            return "Turn: O";
        }
        case GameStatus::XWon:
        {
            return "X won!";
        }
        case GameStatus::OWon:
        {
            return "O won!";
        }
        case GameStatus::Draw:
        {
            return "Draw!";
        }
    }

    assert(false);
    return "";
}

static void draw_x(ScreenPosition corner, int cellWidth)
{
    const int padding{ cellWidth / 5 };
    const float left{ static_cast<float>(corner.x + padding) };
    const float right{ static_cast<float>(corner.x + cellWidth - padding) };
    const float top{ static_cast<float>(corner.y + padding) };
    const float bottom{ static_cast<float>(corner.y + cellWidth - padding) };
    const float thickness{ 14.0f };

    DrawLineEx({ left, top }, { right, bottom }, thickness, BLUE);
    DrawLineEx({ right, top }, { left, bottom }, thickness, BLUE);
}

static void draw_o(ScreenPosition corner, int cellWidth, Color cellColor)
{
    const int centerX{ corner.x + cellWidth / 2 };
    const int centerY{ corner.y + cellWidth / 2 };
    const float outerRadius{ static_cast<float>(cellWidth) * 0.32f };
    const float innerRadius{ outerRadius - 14.0f };

    // Кольцо: большой круг, поверх него — круг поменьше цвета клетки.
    DrawCircle(centerX, centerY, outerRadius, RED);
    DrawCircle(centerX, centerY, innerRadius, cellColor);
}

static void draw_cell(
    std::optional<Player> cell,
    ScreenPosition corner,
    int cellWidth)
{
    const Color cellColor{ RAYWHITE };
    DrawRectangle(corner.x, corner.y, cellWidth, cellWidth, cellColor);

    if (cell == Player::X)
    {
        draw_x(corner, cellWidth);
    }
    if (cell == Player::O)
    {
        draw_o(corner, cellWidth, cellColor);
    }
}

static void draw_board(const Board& board, const BoardLayout& layout)
{
    for (std::size_t row = 0; row < boardSize; row++)
    {
        for (std::size_t col = 0; col < boardSize; col++)
        {
            const Position position{ .row = row, .col = col };
            const ScreenPosition corner{ get_cell_screen_position(layout, position) };
            draw_cell(board.cells[row][col], corner, layout.cellWidth);
        }
    }
}

void draw_game(const GameState& state, const BoardLayout& layout)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    DrawText(get_status_text(state), layout.left, 20, 40, WHITE);
    DrawText("R - new game", layout.left, 65, 20, LIGHTGRAY);
    draw_board(state.board, layout);

    EndDrawing();
}
