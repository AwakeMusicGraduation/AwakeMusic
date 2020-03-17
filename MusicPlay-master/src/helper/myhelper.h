#ifndef MYHELPER_H
#define MYHELPER_H

#include <QTextCodec>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QTranslator>
#include <QObject>

class QLineEdit;
class QStandardItemModel;
class QCompleter;

class myHelper : public QObject
{
    Q_OBJECT
public:
    static void SetGBK2312Code();                                   //设置编码为GB2312
    static void SetUTF8Code();                                      //设置编码为UTF8
    static void SetStyle(const QString &StyleName);                 //设置皮肤样式
    static void SetChinese();                                       //加载中文字符

    static void Sleep(int sec);                                     //延时


    //支持的文件文件格式
    static QStringList supportFormatsFilterDialogString();

public:
    explicit myHelper(QObject *parent = 0);
    

private:
    QLineEdit *m_pLineEdit;
    QCompleter *completer;
    QStandardItemModel *StandarModel;
    
};

#endif // MYHELPER_H
