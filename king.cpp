#include "king.h"

// 1.Прогулка Короля - BITS

// 00000000 00000000 00000011 00000010 = 770
// 2^9 + 2^8 + 2^1 = 512 + 256 + 2 = 770

// Король решил прогуляться по пустынной шахматной доске.
// Сейчас он находится в указанной клетке.
// Куда он может сейчас походить?
// Вывести количество возможных ходов короля
// и ulong число с установленными битами тех полей, куда он может походить.

// Дано>: число от 0 до 63 - индекс позиции короля
// Клетки нумеруются от а1 = 0, b1 = 1  до  h8 = 63.

// Надо: два числа на двух клетках,
// количество возможных ходов
// битовая маска всех возможных ходов короля.

// На доске кроме короля никого нет,
// король ходит на одну клетку в любую сторону
// по горизонтали/вертикали/диагонали.

using namespace std;

vector<string> King::Run(const vector<string> &_data)
{
    vector<string> res;
    if (_data.empty() )
        return res;

    uint64_t N = stoull(_data.front());

    uint64_t k = 1ull << N;

    const uint64_t kL = k & 0xFEFEFEFEFEFEFEFE;
    const uint64_t kR = k & 0x7F7F7F7F7F7F7F7F;

    uint64_t movesBits = (kL << 7) | (k << 8) | (kR << 9) |
                         (kL >> 1)            | (kR << 1) |
                         (kL >> 9) | (k >> 8) | (kR >> 7);

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
