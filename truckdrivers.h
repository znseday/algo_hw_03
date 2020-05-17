#ifndef TRUCKDRIVERS_H
#define TRUCKDRIVERS_H

#include "itask.h"

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

class TruckDrivers : public ITask
{
public:
    virtual std::vector<std::string> Run(const std::vector<std::string> &_data) override;
};


#endif // TRUCKDRIVERS_H
