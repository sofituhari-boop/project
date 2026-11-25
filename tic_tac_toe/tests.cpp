#include <cassert>
#include <iostream>
#include <span>

#include "layout.h"
#include "logic.h"

// Делает ходы по очереди (X, O, X, ...) и возвращает итоговое состояние.
static GameState play(std::span<const Position> moves)
{
    GameState state{ create_initial_game_state() };
    for (const Position& move : moves)
    {
        make_move(state, move);
    }
    return state;
}

static void test_initial_state()
{
    const GameState state{ create_initial_game_state() };
    assert(state.currentPlayer == Player::X);
    assert(state.status == GameStatus::Playing);
    assert(can_make_move(state, { 0, 0 }));
}

static void test_players_alternate()
{
    const std::array<Position, 1> moves{ { { 1, 1 } } };
    const GameState state{ play(moves) };
    assert(state.board.cells[1][1] == Player::X);
    assert(state.currentPlayer == Player::O);
}

static void test_cannot_use_taken_cell()
{
    const std::array<Position, 1> moves{ { { 1, 1 } } };
    const GameState state{ play(moves) };
    assert(!can_make_move(state, { 1, 1 }));
    assert(can_make_move(state, { 0, 0 }));
}

static void test_row_win()
{
    const std::array<Position, 5> moves{ { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 } } };
    const GameState state{ play(moves) };
    assert(state.status == GameStatus::XWon);
    // После победы ходить нельзя.
    assert(!can_make_move(state, { 2, 2 }));
}

static void test_column_win()
{
    const std::array<Position, 6> moves{
        { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 }, { 2, 2 }, { 2, 1 } }
    };
    assert(play(moves).status == GameStatus::OWon);
}

static void test_diagonal_wins()
{
    const std::array<Position, 5> mainDiagonal{ { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 }, { 2, 2 } } };
    assert(play(mainDiagonal).status == GameStatus::XWon);

    const std::array<Position, 5> otherDiagonal{ { { 0, 2 }, { 0, 1 }, { 1, 1 }, { 0, 0 }, { 2, 0 } } };
    assert(play(otherDiagonal).status == GameStatus::XWon);
}

static void test_draw()
{
    // X O X
    // X O O
    // O X X
    const std::array<Position, 9> moves{
        { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 1 }, { 1, 0 }, { 1, 2 }, { 2, 1 }, { 2, 0 }, { 2, 2 } }
    };
    assert(play(moves).status == GameStatus::Draw);
}

static void test_win_on_last_move_is_not_draw()
{
    // X O X
    // O X O
    // O X X   <- последний ход X в { 2, 2 } закрывает диагональ
    const std::array<Position, 9> moves{
        { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 1 }, { 2, 0 }, { 2, 2 } }
    };
    assert(play(moves).status == GameStatus::XWon);
}

static void test_find_cell_at()
{
    const BoardLayout layout{ .left = 30, .top = 110, .cellWidth = 160, .gap = 10 };

    const std::optional<Position> first{ find_cell_at(layout, { .x = 30, .y = 110 }) };
    assert(first.has_value());
    assert(first->row == 0 && first->col == 0);

    // x отвечает за столбец, y — за строку.
    const std::optional<Position> right{ find_cell_at(layout, { .x = 400, .y = 150 }) };
    assert(right.has_value());
    assert(right->row == 0 && right->col == 2);

    // Промежуток между клетками и точка вне поля.
    assert(!find_cell_at(layout, { .x = 195, .y = 150 }).has_value());
    assert(!find_cell_at(layout, { .x = 5, .y = 5 }).has_value());
}

int main()
{
    test_initial_state();
    test_players_alternate();
    test_cannot_use_taken_cell();
    test_row_win();
    test_column_win();
    test_diagonal_wins();
    test_draw();
    test_win_on_last_move_is_not_draw();
    test_find_cell_at();
    std::cout << "All tests passed" << std::endl;
}
