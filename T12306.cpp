#include "T12306.h"
#include "ui_T12306.h"
#include "StringListModel.h"

#include <QString>

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QUrl>
#include <QEventLoop>
#include <QTextCodec>


#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

static const char* Url_yupiao   = "http://www.chepiao100.com/api/yupiao.php?";
static const char* Url_checi    = "http://www.chepiao100.com/api/checi?";
static const char* Url_chezhan  = "http://www.chepiao100.com/api/chezhan?";

static const char* myKey    = "be6637e1841745a59bf8c5904e3a0d82";


T12306::T12306(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T12306)
{
    ui->setupUi(this);
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    ui->dateEdit->setDate(QDate::currentDate().addDays(2));
    //设置TableView整行选中模式
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    QStringList header;
    header<<"车次"<<"始发"<<"终到"<<"发站"<<"发时"<<"到站"<<"到时"<<"历时"
         <<"硬卧"<<"硬座"<<"一等座"<<"二等座"<<"软卧"<<"无座";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    //设置宽度自适应内容
    ui->tableWidget->resizeColumnsToContents();
    //网络管理者
    netManager = new QNetworkAccessManager();

}

T12306::~T12306()
{
    delete ui;
}

const QString T12306::utf8_to_Url(const QString &utf8)
{
    qDebug()<<utf8;
    int len=utf8.toUtf8().size();
    QString p;
    //p.resize(len*3);
    for(int i=0;i<len;++i){
        unsigned char t=utf8.toUtf8()[i];
        p.append("%").append(QString().setNum(t,16));
    }

    return p;
}

void T12306::on_chaxun_pushButton_clicked()
{
    QString url("http://apis.haoservice.com/lifeservice/train/ypcx?");

    url+="date=" + ui->dateEdit->text();
    url+="&from=" + ui->qidian_comboBox->currentText();
    url+= "&to=" + ui->zhongdian_comboBox_2->currentText();
    url+= "&key=be6637e1841745a59bf8c5904e3a0d82";

    qDebug()<<url;
    // 网络连接管理
    //QNetworkAccessManager *netManager = new QNetworkAccessManager();
    //QNetwork发包
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    //request.setRawHeader("User-Agent", "FireFox 5.0");
    QNetworkReply *reply = netManager->get(request);    //get完成会产生finished信号

    // 阻塞等待请求返回
    QEventLoop eventLoop;
    QObject::connect(netManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();       //阻塞直到完成

    QJsonParseError json_error;
    QString res(reply->readAll());  //获取返回数据

    // 获取到JSON格式的数据，解析，获取JSON对象
    QJsonObject ob=QJsonDocument::fromJson(res.toUtf8(), &json_error).object();
    // 获取失败，返回错误码不是0
    if(ob.value("error_code").toString() == "0"){
        qDebug() << ob.take("error_code").toString();
        return;
    }

    qDebug() << ob.value("result").isArray();
    QJsonArray jarr(ob.value("result").toArray());
    // qDebug() << jarr[0].toObject().value("start_station_name").toString();

    //<<"车次"<<"始发"<<"终到"<<"发站"<<"发时"<<"到站"<<"到时"<<"历时"
    // <<"硬卧"<<"硬座"<<"一等座"<<"二等座"<<"软卧"<<"无座";

    QTableWidget* table=ui->tableWidget;
    table->clearContents();   //情况内容
    table->setRowCount(jarr.count()); //设置行数
    for(int row=0;row < jarr.count();++row){
        //设置车次
        table->setItem(row,0,
                       new QTableWidgetItem(jarr[row].toObject().value("station_train_code").toString()));

        //设置始发站
        table->setItem(row,1,
                       new QTableWidgetItem(jarr[row].toObject().value("start_station_name").toString()));
        //设置终到站
        table->setItem(row,2,
                       new QTableWidgetItem(jarr[row].toObject().value("end_station_name").toString()));
        //设置发站
        table->setItem(row,3,
                       new QTableWidgetItem(jarr[row].toObject().value("from_station_name").toString()));
        //设置发时
        table->setItem(row,4,
                       new QTableWidgetItem(jarr[row].toObject().value("start_time").toString()));
        //设置到站
        table->setItem(row,5,
                       new QTableWidgetItem(jarr[row].toObject().value("to_station_name").toString()));
        //设置到时
        table->setItem(row,6,
                       new QTableWidgetItem(jarr[row].toObject().value("arrive_time").toString()));
        //设置历时
        table->setItem(row,7,
                       new QTableWidgetItem(jarr[row].toObject().value("lishi").toString()));

        //设置硬卧
        table->setItem(row,8,
                       new QTableWidgetItem(jarr[row].toObject().value("yw_num").toString()));
        //设置硬座
        table->setItem(row,9,
                       new QTableWidgetItem(jarr[row].toObject().value("yz_num").toString()));
        //设置一等座
        table->setItem(row,10,
                       new QTableWidgetItem(jarr[row].toObject().value("zy_num").toString()));
        //设置二等座
        table->setItem(row,11,
                       new QTableWidgetItem(jarr[row].toObject().value("ze_num").toString()));
        //设置软卧
        table->setItem(row,12,
                       new QTableWidgetItem(jarr[row].toObject().value("rw_num").toString()));
        //设置无座
        table->setItem(row,13,
                       new QTableWidgetItem(jarr[row].toObject().value("wz_num").toString()));
    }
    table->resizeColumnsToContents();


#if 0

{
    "error_code": "0",
    "reason": "Success",
    "result": [{
        "train_no": "D2287",
        /*车次*/
        "start_station_name": "上海虹桥",
        /*车次始发站*/
        "end_station_name": "深圳北",
        /*车次终点站*/
        "from_station_name": "上海虹桥",
        /*出发站*/
        "to_station_name": "温州南",
        /*到达站*/
        "start_time": "06:25",
        /*出发时间*/
        "arrive_time": "10:53",
        /*到达时间*/
        "train_class_name": "动车",
        /*车次类型*/
        "day_difference": "0",
        /*历时天数*/
        "lishi": "04:28",
        /*总历时时间*/
        "gr_num": "--",
        /*高级软卧：-- 说明无该席位*/
        "qt_num": "--",
        /*其他*/
        "rw_num": "--",
        /*软卧*/
        "rz_num": "--",
        /*软座*/
        "tz_num": "--",
        /*特等座*/
        "wz_num": "无",
        /*无座*/
        "yw_num": "--",
        /*硬卧*/
        "yz_num": "--",
        /*硬座*/
        "ze_num": "无",
        /*二等座*/
        "zy_num": "无",
        /*一等座*/
        "swz_num": "--"
        /*商务座*/
    },
    {
        "train_no": "D3203",
        "start_station_name": "上海虹桥",
        "end_station_name": "厦门北",
        "from_station_name": "上海虹桥",
        "to_station_name": "温州南",
        "start_time": "06:30",
        "arrive_time": "11:09",
        "train_class_name": "动车",
        "day_difference": "0",
        "lishi": "04:39",
        "gr_num": "--",
        "qt_num": "--",
        "rw_num": "--",
        "rz_num": "--",
        "tz_num": "--",
        "wz_num": "无",
        "yw_num": "--",
        "yz_num": "--",
        "ze_num": "无",
        "zy_num": "无",
        "swz_num": "--"
    },
    {
        "train_no": "G7501",
        "start_station_name": "上海虹桥",
        "end_station_name": "苍南",
        "from_station_name": "上海虹桥",
        "to_station_name": "温州南",
        "start_time": "07:00",
        "arrive_time": "11:00",
        "train_class_name": "",
        "day_difference": "0",
        "lishi": "04:00",
        "gr_num": "--",
        "qt_num": "--",
        "rw_num": "--",
        "rz_num": "--",
        "tz_num": "--",
        "wz_num": "165",
        "yw_num": "--",
        "yz_num": "--",
        "ze_num": "无",
        "zy_num": "无",
        "swz_num": "15"
    }]
}

#endif








    /*
    QString url="http://www.chepiao100.com/application/views/statics/doc/demo/yupiao.php?userid=hx_335%40163.com&seckey=69f2ebd4010474b2806e8460dcacdfa3"; //&startStation=%E4%B8%8A%E6%B5%B7&arriveStation=%E5%8C%97%E4%BA%AC&date=2015-05-22";

    url+="&startStation="+ utf8_to_Url(ui->qidian_comboBox->currentText());
    url+="&arriveStation="+ utf8_to_Url(ui->zhongdian_comboBox_2->currentText());
    url+="&date=" + ui->dateEdit->text();

    qDebug()<<url;
    */
    /*
    // 网络连接管理
    QNetworkAccessManager *netManager = new QNetworkAccessManager();
    //QNetwork发包
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("User-Agent", "FireFox 5.0");
    QNetworkReply *reply = netManager->get(request);    //get完成会产生finished信号

    // 阻塞等待请求返回
    QEventLoop eventLoop;
    QObject::connect(netManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();       //阻塞直到完成

    // 文本编码  搜狐网站返回的数据是gbk编码的
    //QTextCodec *codec = QTextCodec::codecForName("gbk");
    //QString var = codec->toUnicode(reply->readAll());

    QString res(reply->readAll());
    */
    //ui->webView->load(QUrl("http://apis.haoservice.com/lifeservice/train/ypcx?date=2015-05-27&from=上海&to=温州&key=be6637e1841745a59bf8c5904e3a0d82"));
    //ui->webView->setHtml(res);
    //qDebug()<<res;




}
