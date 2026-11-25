#pragma once

#include <array>
#include <cstddef>
#include <optional>

// Размер поля. Это константа времени компиляции: она нужна как размер std::array.
// Она никогда не меняется, поэтому это не глобальное состояние игры.
inline constexpr std::size_t boardSize{ 3 };

enum class Player
{
    X,
    O,
};

enum class GameStatus
{
    Playing,
    XWon,
    OWon,
    Draw,
};

// Клетка на поле (не на экране): номер строки и номер столбца, с нуля.
struct Position
{
    std::size_t row;
    std::size_t col;
};

// Клетка либо хранит игрока, который в неё походил, либо пуста (std::nullopt).
struct Board
{
    std::array<std::array<std::optional<Player>, boardSize>, boardSize> cells;
};

// Всё, что нужно помнить об игре между кадрами.
struct GameState
{
    Board board;
    Player currentPlayer;
    GameStatus status;
};

GameState create_initial_game_state();

bool can_make_move(const GameState& state, Position position);

// Предусловие: can_make_move(state, position).
void make_move(GameState& state, Position position);
