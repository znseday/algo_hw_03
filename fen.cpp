#include "fen.h"
#include <array>

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

// enum Piece;

// Начальные данные: строка символов - позиция в FEN нотации
// Вывод результата: 12 беззнаковых 64-битных целых чисел, по одному на каждой строке.

using namespace std;

Board_t ConvertFenToBitBoards(const string &_fen)
{
    Board_t board = {0};   // uint64_t board[12] = {0};

//    7k/8/8/8/8/8/8/K7
//    rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR

    Piece piece;
    size_t i = 7, j = 0;
    for (auto c : _fen)
    {
        switch (c)
        {
        case '/':
            --i;
            j = 0;
            continue;

        case 'r':
            piece = blackRooks;
            break;

        case 'n':
            piece = blackKnights;
            break;

        case 'b':
            piece = blackBishops;
            break;

        case 'q':
            piece = blackQueens;
            break;

        case 'k':
            piece = blackKing;
            break;

        case 'p':
            piece = blackPawns;
            break;

        case 'R':
            piece = whiteRooks;
            break;

        case 'N':
            piece = whiteKnights;
            break;

        case 'B':
            piece = whiteBishops;
            break;

        case 'Q':
            piece = whiteQueens;
            break;

        case 'K':
            piece = whiteKing;
            break;

        case 'P':
            piece = whitePawns;
            break;
        }

        if (c >= '1' && c <= '8')
        {
            size_t digit = c - '0';
            j += digit;
            continue;
        }

        board[piece]  |=  (1ull << (i*8 + j++)) ;
    }
    return board;
}


vector<string> FEN::Run(const vector<string> &_data)
{
    vector<string> res;
    if (_data.empty() )
        return res;

    auto board = ConvertFenToBitBoards(_data.front());

    for (auto b : board)
        res.emplace_back(to_string(b));

    return res;
}








