#include "truckdrivers.h"

// 4.Дальнобойщики - BITS *

// Дана шахматная позиция в FEN формате.
// Известно, что в этой позиции есть:
// + одна белая ладья,
// + один белый слон,
// + один белый ферзь,
// а также возможно наличие других белых и чёрных фигур.

// Определить битовую маску возможных ходов белых фигур - ладьи, слона и ферзя.
// Ладья ходит по вертикалям и горизонталям.
// Слон ходит по диагоналям.
// Ферзь ходит как ладья и слон вместе.
// Фигура обязана пойти как минимум на одну клетку.
// Фигура может пойти на пустую клетку или
// на клетку с фигурой противоположного цвета.
// Фигура не может перепрыгивать другие фигуры.

// Начальные данные: строка с шахматной позицией в FEN-формате.
// Вывод результата: 3 числа типа ulong на трёх строчках.
// на первой строке - число, соответствующее битовой маске возможных ходов белой ладьи
// на второй строке - число, соответствующее битовой маске возможных ходов белого слона
// на третьей строке - число, соответствующее битовой маске возможных ходов белого ферзя

#include "fen.h"
#include <algorithm>

using namespace std;


bool ProcessCollision(uint64_t _pos, uint64_t &_res, const Board_t &_board)
{
    // столкновение с белой фигурой
    if ( any_of(_board.cbegin(), _board.cbegin()+6, [_pos](uint64_t val) {return (_pos & val); }))
        return true;

    _res |= _pos;

    // столкновение с черной фигурой
    if ( any_of(_board.cbegin()+6, _board.end(), [_pos](uint64_t val) {return (_pos & val); }))
        return true;

    return false;
}


uint64_t FindRookBits(const Board_t &_board, uint64_t _pos)
{
    uint64_t res = 0, pos;

    pos = _pos;
    while ( !(pos & 0x8080808080808080) ) // Двигаемся вправо
    {
        pos <<= 1ull;
        if ( ProcessCollision(pos, res, _board) )
            break;
    }

    pos = _pos;
    while ( !(pos & 0x0101010101010101) ) // Двигаемся влево
    {
        pos >>= 1ull;
        if ( ProcessCollision(pos, res, _board) )
            break;
    }

    pos = _pos;
    while ( !(pos & 0xFF00000000000000) ) // Двигаемся вверх
    {
        pos <<= 8ull;
        if ( ProcessCollision(pos, res, _board) )
            break;
    }

    pos = _pos;
    while ( !(pos & 0x00000000000000FF) ) // Двигаемся вниз
    {
        pos >>= 8ull;
        if ( ProcessCollision(pos, res, _board) )
            break;
    }

    return res;
}


uint64_t FindBishopBits(const Board_t &_board, uint64_t _pos)
{
    uint64_t res = 0, pos;

    pos = _pos;
    while ( !(pos & 0xFF80808080808080) ) // Двигаемся вправо-вверх
    {
        pos <<= 9ull;
        if ( ProcessCollision(pos, res, _board) )
            break;
    }

    pos = _pos;
    while ( !(pos & 0xFF01010101010101) ) // Двигаемся влево-вверх
    {
        pos <<= 7ull;
        if ( ProcessCollision(pos, res, _board) )
            break;
    }

    pos = _pos;
    while ( !(pos & 0x01010101010101FF) ) // Двигаемся влево-вниз
    {
        pos >>= 9ull;
        if ( ProcessCollision(pos, res, _board) )
            break;
    }

    pos = _pos;
    while ( !(pos & 0x80808080808080FF) ) // Двигаемся вправо-вниз
    {
        pos >>= 7ull;
        if ( ProcessCollision(pos, res, _board) )
            break;
    }

    return res;
}


uint64_t FindQueenBits(const Board_t &_board, uint64_t _pos)
{
    uint64_t resRook = FindRookBits(_board, _pos);
    uint64_t resBishop = FindBishopBits(_board, _pos);

    return resRook | resBishop;
}

vector<string> TruckDrivers::Run(const vector<string> &_data)
{
    vector<string> res;

    if (_data.empty() )
        return res;

    auto board = ConvertFenToBitBoards(_data.front());

    res.emplace_back(to_string(FindRookBits(board,   board[whiteRooks])));
    res.emplace_back(to_string(FindBishopBits(board, board[whiteBishops])));
    res.emplace_back(to_string(FindQueenBits(board,  board[whiteQueens])));

    return res;
}









