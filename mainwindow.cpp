#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

static double speed=1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->process = new QProcess;
    this->process->setProcessChannelMode(QProcess::MergedChannels);
    arg = "F:/mypler-vedio/MPlayer/mplayer.exe";

    ui->setupUi(this);

    QPixmap pixmap;
    pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
    ui->voiceButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->voiceButton->setIcon(pixmap);
    ui->voiceButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->voiceButton->setToolTip("音量");
    ui->voiceButton->show();
    ui->voiceslider->setSliderPosition(20);
    ui->voiceslider->setValue(20);

    QPixmap pixmap1;
    pixmap1.load("E:/VS2013 QT/New_Qt Creator/vedio-player/last.png");
    ui->lastButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->lastButton->setIcon(pixmap1);
    ui->lastButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->lastButton->setToolTip("上一个");
    ui->lastButton->show();

    QPixmap pixmap2;
    pixmap2.load("E:/VS2013 QT/New_Qt Creator/vedio-player/next.png");
    ui->nextButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->nextButton->setIcon(pixmap2);
    ui->nextButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->nextButton->setToolTip("下一个");
    ui->nextButton->show();

    QPixmap pixmap3;
    pixmap3.load("E:/VS2013 QT/New_Qt Creator/vedio-player/start.png");
    ui->startButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->startButton->setIcon(pixmap3);
    ui->startButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->startButton->setToolTip("开始播放");
    ui->startButton->show();

    QPixmap pixmap5;
    pixmap5.load("E:/VS2013 QT/New_Qt Creator/vedio-player/manfang.png");
    ui->manButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->manButton->setIcon(pixmap5);
    ui->manButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->manButton->setToolTip("减速播放");
    ui->manButton->show();

    QPixmap pixmap6;
    pixmap6.load("E:/VS2013 QT/New_Qt Creator/vedio-player/kuaifang.png");
    ui->kuaiButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->kuaiButton->setIcon(pixmap6);
    ui->kuaiButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->kuaiButton->setToolTip("加速播放");
    ui->kuaiButton->show();

    QPixmap pixmap7;
    pixmap7.load("E:/VS2013 QT/New_Qt Creator/vedio-player/back.png");
    ui->backButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->backButton->setIcon(pixmap7);
    ui->backButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->backButton->setToolTip("后退");
    ui->backButton->show();

    QPixmap pixmap8;
    pixmap8.load("E:/VS2013 QT/New_Qt Creator/vedio-player/fast.png");
    ui->fastButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->fastButton->setIcon(pixmap8);
    ui->fastButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->fastButton->setToolTip("快进");
    ui->fastButton->show();

    QPixmap pixmap9;
    pixmap9.load("E:/VS2013 QT/New_Qt Creator/vedio-player/tingzhi.png");
    ui->tingzhiButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->tingzhiButton->setIcon(pixmap9);
    ui->tingzhiButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->tingzhiButton->setToolTip("停止");
    ui->tingzhiButton->show();

    QPixmap pixmap10;
    pixmap10.load("E:/VS2013 QT/New_Qt Creator/vedio-player/cut.jpg");
    ui->shotscreenButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->shotscreenButton->setIcon(pixmap10);
    ui->shotscreenButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->shotscreenButton->setToolTip("截屏");
    ui->shotscreenButton->show();

    ui->centralWidget->setAutoFillBackground(true);//设置中心部件背景颜色
    QPalette p = ui->centralWidget ->palette();
    p.setColor(QPalette::Window,QColor(136, 136, 136));
    ui->centralWidget->setPalette(p);

    QFile dataFile("x.txt");
    if (dataFile.open(QFile::ReadOnly|QIODevice::Text))
    {
        QTextStream data(&dataFile);
        QStringList fonts;
        QString line;
        while (!data.atEnd())//逐行读取文本，并去除每行的回车
        {
            line = data.readLine();
            line.remove('\n');
            fonts<<line;
        }
        ui->listWidget->addItems(fonts);//把各行添加到listwidget
    }

    QObject::connect(ui->addfileButton,SIGNAL(clicked()),this,SLOT(openFileSlot()));//添加文件
    QObject::connect(ui->deleteButton,SIGNAL(clicked()),this,SLOT(deleteFileSlot()));//删除文件
    QObject::connect(ui->startButton,SIGNAL(clicked()),this,SLOT(zantingOrstartSlot()));//开始暂停
    QObject::connect(ui->backButton,SIGNAL(clicked()),this,SLOT(backSlot()));//后退
    QObject::connect(ui->fastButton,SIGNAL(clicked()),this,SLOT(forwardSlot()));//快进
    QObject::connect(ui->lastButton,SIGNAL(clicked()),this,SLOT(lastSlot()));//上一个
    QObject::connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(nextSlot()));//下一个
    QObject::connect(ui->manButton,SIGNAL(clicked()),this,SLOT(reduceSlot()));//减速
    QObject::connect(ui->kuaiButton,SIGNAL(clicked()),this,SLOT(accelerateSlot()));//加速
    QObject::connect(ui->tingzhiButton,SIGNAL(clicked()),this,SLOT(stopSlot()));//停止
    QObject::connect(ui->voiceButton,SIGNAL(clicked()),this,SLOT(voiceSlot()));//声音静音
    QObject::connect(ui->shotscreenButton,SIGNAL(clicked()),this,SLOT(screenshotSlot()));//

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::zantingOrstartSlot()//暂停或者开始
{
    this->process->write("pause\n");
    if(ui->startButton->toolTip() == "开始播放")
    {
        if(ui->listWidget->count() == 0)
        {
            QMessageBox::information(this,"open false","please add file first");
        }
        else
        {
            QObject::connect(this->process,SIGNAL(readyReadStandardOutput()),this,SLOT(dataReceive()));
            this->process->write("get_time_length\n");
            this->process->write("get_time_pos\n");
            this->process->write("get_percent_pos\n");
            QPixmap pixmap;
            pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
            QPixmap pixmap4;
            pixmap4.load("E:/VS2013 QT/New_Qt Creator/vedio-player/stop.png");
            ui->startButton->setFixedSize(pixmap.width(),pixmap.height());
            ui->startButton->setIcon(pixmap4);
            ui->startButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
            ui->startButton->setToolTip("暂停播放");
            ui->startButton->show();

        }
    }
    else
    {
        QObject::disconnect(this->process,SIGNAL(readyReadStandardOutput()),this,SLOT(dataReceive()));

        QPixmap pixmap;
        pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
        QPixmap pixmap3;
        pixmap3.load("E:/VS2013 QT/New_Qt Creator/vedio-player/start.png");
        ui->startButton->setFixedSize(pixmap.width(),pixmap.height());
        ui->startButton->setIcon(pixmap3);
        ui->startButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
        ui->startButton->setToolTip("开始播放");
        ui->startButton->show();

    }

}

void MainWindow::openFileSlot()//打开文件添加列表
{
    int k=0;
    QStringList filenames = QFileDialog::getOpenFileNames(this,"选择文件","/",tr("视频文件(*mp3 *mp4 *wma *3gp *wav *avi *rmvb *mkv *ts *wmv)"));
    //筛选重复项
    if(ui->listWidget->count() != -1)
    {

        for (QStringList::Iterator j=filenames.begin();j!=filenames.end();++j)
        {
            for(int i=0;i<ui->listWidget->count();++i)
            {
                if(*j == ui->listWidget->item(i)->text())
                {
                    k=1;
                    continue;
                }


            }
            if(k!=1)
            {
                ui->listWidget->addItem(*j);
            }
            else
            {
                k=0;
            }
        }

    }
    else
    {
        if(filenames.count()!=0)
        {
            ui->listWidget->addItems(filenames);
        }
    }

    //将listWidget中的项内容写入到txt文本中
    QStringList lines;
    QString line;
    int row=0;
    QFile file("x.txt");//打开该文件进入编辑模式
    if(file.open(QIODevice::WriteOnly))//如果被打开
    {
        file.resize("x.txt",0);//清空内容
        while(row<(ui->listWidget->count()))//从wistlidget里一行一行的读取文本并存入lines里边
        {
            line=ui->listWidget->item(row)->text();
            row++;
            lines<<line;
        }
        QTextStream stream( &file );//开始写入文本
        for ( QStringList::Iterator it=lines.begin();it!=lines.end();++it )
        stream<<*it<<"\r\n";//注意是"\r\n"！！！！！！如果是单个"\n"  保存文本的时候它不保留换行符！！！！
    }
    file.close();

}

void MainWindow::deleteFileSlot()//删除
{
    if(ui->listWidget->currentRow() == -1)
    {
        QMessageBox::information(this,"Error delete","Not select a flie or thie list is null");
    }
    else
    {
        ui->listWidget->takeItem(ui->listWidget->currentRow());

        //将listWidget中的项内容写入到txt文本中
        QStringList lines;
        QString line;
        int row=0;
        QFile file("x.txt");//打开该文件进入编辑模式
        if(file.open(QIODevice::WriteOnly))//如果被打开
        {
            file.resize("x.txt",0);//清空内容
            while(row<(ui->listWidget->count()))//从wistlidget里一行一行的读取文本并存入lines里边
            {
                line=ui->listWidget->item(row)->text();
                row++;
                lines<<line;
            }
            QTextStream stream( &file );//开始写入文本
            for ( QStringList::Iterator it=lines.begin();it!=lines.end();++it )
            stream<<*it<<"\r\n";//注意是"\r\n"！！！！！！如果是单个"\n"  保存文本的时候它不保留换行符！！！！
        }
        file.close();
    }

}

void MainWindow::dataReceive()//接收信息
{
    this->process->write("get_time_length\n");
    this->process->write("get_time_pos\n");
    this->process->write("get_percent_pos\n");
    while(this->process->canReadLine())
    {
        QByteArray b(this->process->readLine());
        b.replace(QByteArray("\n"), QByteArray(""));
        QString s(b);

        if (b.startsWith("ANS_LENGTH"))  //输出视频总时间
        {
            int totalTimeNum = s.mid(11).toFloat();
            int sec = 0, min = 0, hour = 0;
            if(totalTimeNum < 60)
            {
                sec = totalTimeNum;
                min = 0;
                hour= 0;
            }
            if(totalTimeNum >= 60 && totalTimeNum <3600)
            {
                sec = totalTimeNum%60;
                min = totalTimeNum/60;
                hour= 0;
            }
            if(totalTimeNum > 3600)
            {
                sec = totalTimeNum%60;
                min = totalTimeNum/60%60;
                hour= totalTimeNum/3600;
            }

            QString totalTime = QString("%1:%2:%3").arg(hour).arg(min).arg(sec);  //标准格式输出时间
            ui->totletimeLable->setText(totalTime);

            ui->horizontalSlider->setRange(0,totalTimeNum);
        }

        else if (b.startsWith("ANS_TIME_POSITION"))  //输出视频当前时间
        {
            int currentTimeNum = s.mid(18).toFloat();
            int sec = 0, min = 0, hour = 0;
            if(currentTimeNum < 60)
            {
                sec = currentTimeNum;
                min = 0;
                hour= 0;
            }
            if(currentTimeNum >= 60 && currentTimeNum <3600)
            {
                sec = currentTimeNum%60;
                min = currentTimeNum/60;
                hour= 0;
            }
            if(currentTimeNum > 3600)
            {
                sec = currentTimeNum%60;
                min = currentTimeNum/60%60;
                hour= currentTimeNum/3600;
            }

            QString currentTime = QString("%1:%2:%3").arg(hour).arg(min).arg(sec);
            ui->currenttimeLable->setText(currentTime);

            ui->horizontalSlider->setValue(currentTimeNum);
        }

        else if(b.startsWith("ANS_PERCENT_POSITION"))
        {
            QString currentPercent = s.mid(21);
            ui->precentLable->setText(currentPercent+"%");//视频播放进度百分比
        }
    }
}

void MainWindow::play(QString fileName)//播放
{

    QStringList arg1;
    this->process->kill();
    this->process=new QProcess;
    arg1 << fileName;
    arg1 << "-slave";//默认情况下，mplayer接受键盘的命令，而"-slave"使其不再接受键盘事件，而是作为后台程序运行，
                     //接受以“\n”结束的命令控制，这样我们可以在进程中给他发送命令，而不需要操作键盘了.
    arg1 << "-quiet"; //尽可能的不打印播放信息
    arg1 << "-zoom"; //视频居中，四周黑条，全屏播放
    arg1 << "-wid" << QString::number((unsigned int)(ui->widget->winId()));
             // "-wid <窗口标识>" 是指让MPlayer依附于那个窗口，
             //ui->widget->winId() 这个指令就是用来获取widget的标识码 ,
             //这样视频播放的时候，就在这个部件里播放，相当于给他固定起来。

    connect(this->process,SIGNAL(readyReadStandardOutput()),this,SLOT(dataReceive()));
    this->process->start(arg,arg1);   //开始播放进程

    this->setWindowTitle(fileName);//设置当前播放的视频的标题名称

    QPixmap pixmap;
    pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
    QPixmap pixmap4;
    pixmap4.load("E:/VS2013 QT/New_Qt Creator/vedio-player/stop.png");
    ui->startButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->startButton->setIcon(pixmap4);
    ui->startButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->startButton->setToolTip("暂停播放");
    ui->startButton->show();

}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)//项目双击播放
{
      play(item->text());
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)//进度条移动
{
    this->process->write(QString("seek "+QString::number(position)+" 2\n").toUtf8());
}
void MainWindow::backSlot()//后退
{
    this->process->write("seek -5 0\n");

}
void MainWindow::forwardSlot()//快进
{
    this->process->write("seek +1 0\n");
}
void MainWindow::lastSlot()//上一个
{
    if(ui->listWidget->currentRow() == 0)//当光标在第一个文件时，点击上一个光标移动到最下面的文件，不播放
    {
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }
    else
    {
        ui->listWidget->setCurrentRow(ui->listWidget->currentRow()-1);
        play(ui->listWidget->currentItem()->text());

        QPixmap pixmap;
        pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
        QPixmap pixmap4;
        pixmap4.load("E:/VS2013 QT/New_Qt Creator/vedio-player/stop.png");
        ui->startButton->setFixedSize(pixmap.width(),pixmap.height());
        ui->startButton->setIcon(pixmap4);
        ui->startButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
        ui->startButton->setToolTip("暂停播放");
        ui->startButton->show();

    }

}
void MainWindow::nextSlot()//下一个
{
    if(ui->listWidget->currentRow() == ui->listWidget->count()-1)
    {
        ui->listWidget->setCurrentRow(0);//当光标在最后一个文件时，点击下一个，光标移动到第一个，不播放
    }
    else
    {
        ui->listWidget->setCurrentRow(ui->listWidget->currentRow()+1);
        play(ui->listWidget->currentItem()->text());

        QPixmap pixmap;
        pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
        QPixmap pixmap4;
        pixmap4.load("E:/VS2013 QT/New_Qt Creator/vedio-player/stop.png");
        ui->startButton->setFixedSize(pixmap.width(),pixmap.height());
        ui->startButton->setIcon(pixmap4);
        ui->startButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
        ui->startButton->setToolTip("暂停播放");
        ui->startButton->show();
    }

}

void MainWindow::reduceSlot()//减速
{
    speed=speed/2;
    this->process->write(QString("speed_set " + QString::number(speed)+" 2\n").toUtf8());
}
void MainWindow::accelerateSlot()//加速
{

    speed=speed*2;
    this->process->write(QString("speed_set " + QString::number(speed) +" 2\n").toUtf8());

}
void MainWindow::stopSlot()//停止
{

    this->process->write("quit\n");
    ui->horizontalSlider->setSliderPosition(0);
    ui->totletimeLable->clear();
    ui->currenttimeLable->clear();
    ui->precentLable->clear();

    QPixmap pixmap;
    pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
    QPixmap pixmap3;
    pixmap3.load("E:/VS2013 QT/New_Qt Creator/vedio-player/start.png");
    ui->startButton->setFixedSize(pixmap.width(),pixmap.height());
    ui->startButton->setIcon(pixmap3);
    ui->startButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
    ui->startButton->setToolTip("开始播放");
    ui->startButton->show();

}
void MainWindow::voiceSlot()//声音静音(待实现)
{
    if(ui->voiceButton->toolTip() == "音量")
    {
        //this->process->write("mute 1\n"); //开启静音

        QPixmap pixmap;
        pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
        QPixmap pixmap1;
        pixmap1.load("E:/VS2013 QT/New_Qt Creator/vedio-player/novoice.png");
        ui->voiceButton->setFixedSize(pixmap.width(),pixmap.height());
        ui->voiceButton->setIcon(pixmap1);
        ui->voiceButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
        ui->voiceButton->setToolTip("静音");
        ui->voiceButton->show();

    }
    else
    {
        this->process->write("mute 0\n");      //关闭静音

        QPixmap pixmap;
        pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
        ui->voiceButton->setFixedSize(pixmap.width(),pixmap.height());
        ui->voiceButton->setIcon(pixmap);
        ui->voiceButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
        ui->voiceButton->setToolTip("音量");
        ui->voiceButton->show();

    }


}

void MainWindow::on_voiceslider_sliderMoved(int position)//声音滑条
{
    this->process->write(QString("volume " + QString::number(position) +" 2\n").toUtf8());
    if(position == 0)
    {
        QPixmap pixmap;
        pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
        QPixmap pixmap1;
        pixmap1.load("E:/VS2013 QT/New_Qt Creator/vedio-player/novoice.png");
        ui->voiceButton->setFixedSize(pixmap.width(),pixmap.height());
        ui->voiceButton->setIcon(pixmap1);
        ui->voiceButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
        ui->voiceButton->setToolTip("静音");
        ui->voiceButton->show();
    }
    else
    {
        QPixmap pixmap;
        pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
        ui->voiceButton->setFixedSize(pixmap.width(),pixmap.height());
        ui->voiceButton->setIcon(pixmap);
        ui->voiceButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
        ui->voiceButton->setToolTip("音量");
        ui->voiceButton->show();

    }
}

void MainWindow::screenshotSlot()//截图(不能显示视频的画面)
{
    process->write("pause\n");
//  QPixmap snapImage = QPixmap::grabWindow(QApplication::desktop()->winId());//截取整个桌面窗口
    this->pixmap =  QPixmap::grabWindow(ui->widget->winId());//截取依附的窗口
    QString filename = QFileDialog::getSaveFileName(this,tr("保存图片"),"./未命名",tr("PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)"));//弹出保存图片的文件窗口

    if(filename!=NULL)
    {
        this->pixmap.save(filename);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)//鼠标单击实现视频播放暂停
{
    this->process->write("pause\n");
    int x=event->x();
    int y=event->y();
    if((x>10&&x<491)&&(y>20&&y<301))
    {
        if((event->button() == Qt::LeftButton)&&(ui->startButton->toolTip() == "开始播放"))
        {

            QObject::connect(this->process,SIGNAL(readyReadStandardOutput()),this,SLOT(dataReceive()));
            this->process->write("get_time_length\n");
            this->process->write("get_time_pos\n");
            this->process->write("get_percent_pos\n");
            QPixmap pixmap;
            pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
            QPixmap pixmap7;
            pixmap7.load("E:/VS2013 QT/New_Qt Creator/vedio-player/stop.png");
            ui->startButton->setFixedSize(pixmap.width(),pixmap.height());
            ui->startButton->setIcon(pixmap7);
            ui->startButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
            ui->startButton->setToolTip("暂停播放");
            ui->startButton->show();

            this->statusBar()->showMessage("开始",3*1000);//显示此时的状态,显示3秒

        }
//不能用此语句，要用else
// if((event->button() == Qt::LeftButton)&&(ui->startButton->toolTip() == "暂停播放"))
        else
        {
            QObject::disconnect(this->process,SIGNAL(readyReadStandardOutput()),this,SLOT(dataReceive()));

            QPixmap pixmap;
            pixmap.load("E:/VS2013 QT/New_Qt Creator/vedio-player/voice.png");
            QPixmap pixmap3;
            pixmap3.load("E:/VS2013 QT/New_Qt Creator/vedio-player/start.png");
            ui->startButton->setFixedSize(pixmap.width(),pixmap.height());
            ui->startButton->setIcon(pixmap3);
            ui->startButton->setIconSize(QSize(pixmap.width(),pixmap.height()));
            ui->startButton->setToolTip("开始播放");
            ui->startButton->show();

            this->statusBar()->showMessage("暂停",3*1000);//显示此时的状态,显示3秒
        }

    }


}
