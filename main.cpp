#include <QTextCodec>
#include <QMessageBox>
#include "GMainWin.h"
//--------------------------------------------------------------------
class geoApplication: public QApplication
{
public:
   geoApplication(int &argc, char *argv[]) : QApplication(argc, argv) {}
    virtual ~geoApplication() {}
    bool notify(QObject *receiver_, QEvent *event_)
    {
      try
      {
        return QApplication::notify(receiver_, event_);
      }
      catch (std::exception &ex)
      {
        std::cerr << "std::exception = " <<ex.what()<< std::endl;
        QMessageBox::critical(0,"dzwon","bad");
        this->exit(1);
      }
      return false;
    }
};
//--------------------------------------------------------------------
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
