#include "logic.h"

#include <cassert>

// Функции со static видны только внутри этого файла.

static bool is_on_board(Position position)
{
    return position.row < boardSize && position.col < boardSize;
}

static std::optional<Player> get_cell(const Board& board, Position position)
{
    assert(is_on_board(position));
    return board.cells[position.row][position.col];
}

static Player get_other_player(Player player)
{
    if (player == Player::X)
    {
        return Player::O;
    }
    return Player::X;
}

// Если в трёх клетках стоит один и тот же игрок, возвращает его.
// Иначе возвращает std::nullopt.
static std::optional<Player> get_line_winner(
    const Board& board,
    Position a,
    Position b,
    Position c)
{
    const std::optional<Player> first{ get_cell(board, a) };
    if (!first.has_value())
    {
        return std::nullopt;
    }
    if (get_cell(board, b) != first)
    {
        return std::nullopt;
    }
    if (get_cell(board, c) != first)
    {
        return std::nullopt;
    }
    return first;
}

static std::optional<Player> find_winner(const Board& board)
{
    // 3 строки и 3 столбца.
    for (std::size_t i = 0; i < boardSize; i++)
    {
        const std::optional<Player> rowWinner{
            get_line_winner(board, { i, 0 }, { i, 1 }, { i, 2 })
        };
        if (rowWinner.has_value())
        {
            return rowWinner;
        }

        const std::optional<Player> colWinner{
            get_line_winner(board, { 0, i }, { 1, i }, { 2, i })
        };
        if (colWinner.has_value())
        {
            return colWinner;
        }
    }

    // 2 диагонали.
    const std::optional<Player> diagonalWinner{
        get_line_winner(board, { 0, 0 }, { 1, 1 }, { 2, 2 })
    };
    if (diagonalWinner.has_value())
    {
        return diagonalWinner;
    }
    return get_line_winner(board, { 0, 2 }, { 1, 1 }, { 2, 0 });
}

static bool is_board_full(const Board& board)
{
    for (const auto& row : board.cells)
    {
        for (const auto& cell : row)
        {
            if (!cell.has_value())
            {
                return false;
            }
        }
    }
    return true;
}

static GameStatus compute_status(const Board& board)
{
    // Победу проверяем раньше ничьей:
    // последний ход может и заполнить поле, и выиграть.
    const std::optional<Player> winner{ find_winner(board) };
    if (winner == Player::X)
    {
        return GameStatus::XWon;
    }
    if (winner == Player::O)
    {
        return GameStatus::OWon;
    }
    if (is_board_full(board))
    {
        return GameStatus::Draw;
    }
    return GameStatus::Playing;
}

GameState create_initial_game_state()
{
    return {
        .board = {},
        .currentPlayer = Player::X,
        .status = GameStatus::Playing,
    };
}

bool can_make_move(const GameState& state, Position position)
{
    if (state.status != GameStatus::Playing)
    {
        return false;
    }
    return !get_cell(state.board, position).has_value();
}

void make_move(GameState& state, Position position)
{
    assert(can_make_move(state, position));

    state.board.cells[position.row][position.col] = state.currentPlayer;
    state.status = compute_status(state.board);
    state.currentPlayer = get_other_player(state.currentPlayer);
}
