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

#include <QTextCodec>
#include <QMessageBox>
#include "GMainWin.h"
#include <iostream>
//------------------------------------------------------------------------------
///
/// \brief The geoApplication class
///
class geoApplication: public QApplication
{
public:
    ///
    /// \brief geoApplication
    /// \param argc
    /// \param argv
    ///
    geoApplication(int &argc, char *argv[]) : QApplication(argc, argv) {}
    ///
    /// \brief ~geoApplication
    ///
    virtual ~geoApplication() {}
    ///
    /// \brief notify
    /// \param receiver_
    /// \param event_
    /// \return
    ///
    bool notify(QObject *receiver_, QEvent *event_)
    {
      try
      {
        return QApplication::notify(receiver_, event_);
      }
      catch (std::exception &ex)
      {
        std::cerr << "std::exception = " <<ex.what()<< std::endl;
        QMessageBox::critical(0,"EXCEPTION", QString(ex.what()));
        this->exit(1);
      }
      return false;
    }
};
//------------------------------------------------------------------------------
///
/// \brief main
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{
    geoApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    GMainWin w;
    w.show();
    return a.exec();
}
//------------------------------------------------------------------------------
