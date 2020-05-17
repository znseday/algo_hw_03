#ifndef FEN_H
#define FEN_H

#include <array>

#include "itask.h"

// 3.FEN - BITS *

// Дано расположение шахматных фигур на доске в FEN-нотации (первая часть fen-кода).
// Например, начальная позиция записывается так:
// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
// Подробнее о формате нотации см.
// https://ru.wikipedia.org/wiki/Нотация_Форсайта_—_Эдвардса

// Перевести её в Bitboard Board-Definition формат.

// В 64-битном числе хранятся биты каждой клетки шахматной доски:
// поле a1 соответствует нулевому биту и равно 2^0 = 1
// поле b1 соответствует нулевому биту и равно 2^1 = 2
// поле h1 соответствует седьмому биту и равно 2^7 = 128
// поле a2 соответствует восьмому биту и равно 2^8 = 256
// поле h8 соответствует 63-му биту и равно 2^63 = 9 223 372 036 854 775 808

// Для хранения позиции использовать массив board
// из двенадцати 64-битных беззнаковых целых чисел:
//	ulong [12] board

// Каждый элемент массива board хранит битовую маску фигур
// (0-нет, 1-есть) в порядке перечисления Piece:

enum Piece
{
    whitePawns,
    whiteKnights,
    whiteBishops,
    whiteRooks,
    whiteQueens,
    whiteKing,

    blackPawns,
    blackKnights,
    blackBishops,
    blackRooks,
    blackQueens,
    blackKing
};

// Начальные данные: строка символов - позиция в FEN нотации
// Вывод результата: 12 беззнаковых 64-битных целых чисел, по одному на каждой строке.


using Board_t = std::array<uint64_t, 12>;

Board_t ConvertFenToBitBoards(const std::string &_fen);

class FEN : public ITask
{
public:
    virtual std::vector<std::string> Run(const std::vector<std::string> &_data) override;
};

#endif // FEN_H
