#pragma once

#include <optional>

#include "layout.h"
#include "logic.h"

// Клетка, по которой кликнули в этом кадре. std::nullopt, если клика по клетке не было.
std::optional<Position> get_clicked_cell(const BoardLayout& layout);

bool is_restart_requested();
