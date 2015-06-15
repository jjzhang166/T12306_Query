#ifndef T12306_H
#define T12306_H

#include <QDialog>

class QString;
class QNetworkAccessManager;

namespace Ui {
class T12306;
}

class T12306 : public QDialog
{
    Q_OBJECT

public:
    explicit T12306(QWidget *parent = 0);
    ~T12306();
protected:
    static const QString utf8_to_Url(const QString& utf8);

private slots:
    void on_chaxun_pushButton_clicked();
private:
    QNetworkAccessManager *netManager;  //网络管理者

private:
    Ui::T12306 *ui;
};

#endif // T12306_H
