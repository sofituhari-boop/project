#pragma once

#include <optional>

#include "logic.h"

// Точка на экране, в пикселях. Начало координат — левый верхний угол окна.
struct ScreenPosition
{
    int x;
    int y;
};

// Где и какого размера поле на экране, в пикселях.
struct BoardLayout
{
    int left;
    int top;
    int cellWidth;
    int gap;
};

// Клетка поля -> левый верхний угол этой клетки на экране.
ScreenPosition get_cell_screen_position(const BoardLayout& layout, Position position);

// Точка на экране -> клетка поля. std::nullopt, если точка не попала ни в одну клетку.
std::optional<Position> find_cell_at(const BoardLayout& layout, ScreenPosition point);
