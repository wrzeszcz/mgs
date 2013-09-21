#include <QTextCodec>
#include <QMessageBox>
#include "GMainWin.h"
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
//--------------------------------------------------------------------
