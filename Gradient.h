#ifndef GRADIENT_H
#define GRADIENT_H
#include <QColor>
///
/// \brief The Gradient class
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
    /// \param poz
    /// \return
    ///
    QColor get_kolor(double poz);
private:
    ///
    /// \brief k
    ///
    QColor k;
};

#endif // GRADIENT_H
