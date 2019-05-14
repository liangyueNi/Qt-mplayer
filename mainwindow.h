#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include <QPixmap>
#include <QSize>
#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QListWidget>
#include <QStringList>
#include <QListWidgetItem>
#include <QByteArray>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPixmap pixmap;
    QProcess *process;//使用进程进行操作
    QString arg;//用来存放要使用的mplayer播放器路径
//    QString currentPercent;
//    QString currentStr;
//    QString totalTime;

public:
    QString fileName;

private slots:
    void openFileSlot();//打开文件
    void deleteFileSlot();//删除文件
    void play(QString fileName);//播放
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);//项目双击播放
    void dataReceive();//接收视频信息(当前时间，总时间，进度)，并显示
    void zantingOrstartSlot();//暂停或开始

    void on_horizontalSlider_sliderMoved(int position);//移动进度条控制播放位置
    void backSlot();//后退
    void forwardSlot();//快进
    void lastSlot();//上一个
    void nextSlot();//下一个
    void reduceSlot();//减速
    void accelerateSlot();//加速
    void stopSlot();//停止
    void voiceSlot();//声音静音
    void on_voiceslider_sliderMoved(int position);//声音滑条

    void screenshotSlot();//截图

    void mousePressEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
