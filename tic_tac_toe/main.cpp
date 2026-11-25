#include <optional>

#include "controller.h"
#include "graphic.h"
#include "layout.h"
#include "logic.h"
#include "raylib.h"

int main()
{
    const BoardLayout layout{
        .left = 30,
        .top = 110,
        .cellWidth = 160,
        .gap = 10,
    };

    InitWindow(560, 640, "Tic-Tac-Toe");
    SetTargetFPS(60);

    GameState state{ create_initial_game_state() };

    // Game loop: одна итерация = один кадр.
    while (true)
    {
        if (WindowShouldClose())
        {
            break;
        }

        // 1. Считать ввод.
        const bool isRestartRequested{ is_restart_requested() };
        const std::optional<Position> clickedCell{ get_clicked_cell(layout) };

        // 2. Обновить состояние игры.
        if (isRestartRequested)
        {
            state = create_initial_game_state();
        }
        if (clickedCell.has_value() && can_make_move(state, *clickedCell))
        {
            make_move(state, *clickedCell);
        }

        // 3. Нарисовать состояние игры.
        draw_game(state, layout);
    }

    CloseWindow();
    return 0;
}
