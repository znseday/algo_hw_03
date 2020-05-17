#include "knight.h"

// 2.Конь - BITS *

// 00000000 00000010 00000100 00000000 = 132096
// 2^17 + 2^10 = 131072 + 1024 = 132096

// Шахматный конь решил пробежаться по шахматной доске.
// Сейчас он находится в указанной клетке.
// Куда он может сейчас походить?
// Вывести количество возможных ходов коня
// и ulong число с установленными битами тех полей, куда он может походить.


// Дано: число от 0 до 63 - индекс позиции коня
// Клетки нумеруются от а1 = 0, b1 = 1  до  h8 = 63.

// Надо: два числа на двух клетках
// количество возможных ходов
// битовая маска всех возможных ходов коня.

// На доске кроме коня никого нет, конь ходит буквой "Г": две клетки вперёд и одна вбок.


using namespace std;

vector<string> Knight::Run(const vector<string> &_data)
{
    vector<string> res;
    if (_data.empty() )
        return res;

    uint64_t N = stoull(_data[0]);

    uint64_t k = 1ull << N;

    const uint64_t nA  = 0xFeFeFeFeFeFeFeFe;
    const uint64_t nAB = 0xFcFcFcFcFcFcFcFc;
    const uint64_t nH  = 0x7f7f7f7f7f7f7f7f;
    const uint64_t nGH = 0x3f3f3f3f3f3f3f3f;

    uint64_t movesBits = (nGH & (k <<  6 | k >> 10)) |
                         (nH  & (k << 15 | k >> 17)) |
                         (nA  & (k << 17 | k >> 15)) |
                         (nAB & (k << 10 | k >>  6));

    uint64_t movesBitsRes = movesBits;

    size_t movesCount = 0;
    while (movesBits)
    {
        movesBits &= (movesBits - 1);
        ++movesCount;
    }

    res.emplace_back(to_string(movesCount));
    res.emplace_back(to_string(movesBitsRes));

    return res;
}
