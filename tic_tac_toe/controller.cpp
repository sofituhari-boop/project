#include "controller.h"

#include "raylib.h"

std::optional<Position> get_clicked_cell(const BoardLayout& layout)
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return std::nullopt;
    }

    const ScreenPosition mouse{ .x = GetMouseX(), .y = GetMouseY() };
    return find_cell_at(layout, mouse);
}

bool is_restart_requested()
{
    return IsKeyPressed(KEY_R);
}
