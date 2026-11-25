#include "layout.h"

ScreenPosition get_cell_screen_position(const BoardLayout& layout, Position position)
{
    // Шаг от одной клетки до следующей: сама клетка + промежуток.
    const int step{ layout.cellWidth + layout.gap };
    return {
        .x = layout.left + static_cast<int>(position.col) * step,
        .y = layout.top + static_cast<int>(position.row) * step,
    };
}

static bool is_inside_cell(
    const BoardLayout& layout,
    Position position,
    ScreenPosition point)
{
    const ScreenPosition corner{ get_cell_screen_position(layout, position) };
    const bool isInsideX{ point.x >= corner.x && point.x < corner.x + layout.cellWidth };
    const bool isInsideY{ point.y >= corner.y && point.y < corner.y + layout.cellWidth };
    return isInsideX && isInsideY;
}

std::optional<Position> find_cell_at(const BoardLayout& layout, ScreenPosition point)
{
    for (std::size_t row = 0; row < boardSize; row++)
    {
        for (std::size_t col = 0; col < boardSize; col++)
        {
            const Position position{ .row = row, .col = col };
            if (is_inside_cell(layout, position, point))
            {
                return position;
            }
        }
    }
    return std::nullopt;
}
