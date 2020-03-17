#ifndef SEARCHLINEEDIT_H
#define SEARCHLINEEDIT_H
#include <QLineEdit>
#include <QWidget>
class QToolButton;
class QHBoxLayout;
class QWidget;

class SearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    SearchLineEdit(QWidget *parent = 0);
    ~SearchLineEdit();

    void initForm();
    void initConnect();
    void translator();
protected:
    virtual void focusInEvent(QFocusEvent * event);
    virtual void focusOutEvent(QFocusEvent * event);

private slots:
    void slotSendSearchContent();
signals:
    void signalSearchContent(const QString &test);
    void signalSearchClicked();

private:
    QToolButton *m_tbnSearch;
    QHBoxLayout *m_mainLayout;
};

#endif // SEARCHLINEEDIT_H
