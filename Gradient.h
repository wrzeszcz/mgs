/*******************************************************************************
**  Copyright (C) 2013  Marek Wrzeszcz
**  mail: marek.wrzeszcz@hotmail.com
**
**  This file is part of the MGEOSTAT.
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#ifndef GRADIENT_H
#define GRADIENT_H
#include <QColor>
///
/// \brief Klasa Gradient
/// oblicza skalę barw dla przedziału 0.0-1.0
///
class Gradient
{
public:
    ///
    /// \brief Gradient
    ///
    Gradient();
    ///
    /// \brief get_kolor
    /// \param poz - double od 0.0 do 1.0
    /// \return kolor w skali barw
    ///
    QColor get_kolor(double poz);
private:
    ///
    /// \brief k
    ///
    QColor k;
};

#endif // GRADIENT_H
