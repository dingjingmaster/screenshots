#include "screenshots.h"
#include "ui_screenshots.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QTimer>
#include <QScreen>
#include <QWindow>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>

Screenshots::Screenshots(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Screenshots)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/screenshots/img/64x64/screenshots.png"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);

    screenImage = new QPixmap();
    posX = posY = 0;
    width = height = -1;

    initConfig();

    connect(ui->delayMenu, &QMenu::triggered, this, &Screenshots::delaySlot);

    connect(ui->createShotFull, &QAction::triggered, this, &Screenshots::shotFull);
    connect(ui->exitAction, &QAction::triggered, this, &Screenshots::exit);
    connect(ui->saveAction, &QAction::triggered, this, &Screenshots::saveActionSlot);
    connect(ui->cutAction, &QAction::triggered, this, &Screenshots::cutActionSlot);
}

Screenshots::~Screenshots()
{
    delete this->screenImage;
    delete ui;
}

void Screenshots::setDelay(QString str)
{
    if (str == "1 秒") {
        this->delay = SETTING_DELAY_1;
    } else if (str == "2 秒") {
        this->delay = SETTING_DELAY_2;
    } else if (str == "3 秒") {
        this->delay = SETTING_DELAY_3;
    } else if (str == "4 秒") {
        this->delay = SETTING_DELAY_4;
    } else if (str == "5 秒") {
        this->delay = SETTING_DELAY_5;
    } else {
        this->delay = SETTING_DELAY_0;
    }
}

void Screenshots::shotRect()
{
    qDebug() << "create";
    QWindow window;

    *screenImage = window.screen()->grabWindow(QApplication::desktop()->winId(), posX, posY, width, height);
    posX = posY = 0;
    width = height = -1;
}

void Screenshots::resizeEvent(QResizeEvent*)
{
    ui->picLabel->resize(ui->centralwidget->size());

    this->showImage();
}

void Screenshots::showImage()
{
    if (this->screenImage->isNull()) {
        return;
    }
    ui->picLabel->setPixmap((this->screenImage->scaled(\
        ui->picLabel->width(), ui->picLabel->height())));
    ui->picLabel->setScaledContents(true);
}

void Screenshots::shotFull()
{
    this->hide();
    QTime tim = QTime::currentTime().addMSecs(1000 * this->delay);
    while (QTime::currentTime() < tim) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    this->shotRect();
    this->show();
    this->showImage();
}

void Screenshots::initConfig()
{
    this->delay = SETTING_DELAY_0;
    ui->delay0->setChecked(true);
}

void Screenshots::shotSlot(QAction* action)
{
    qDebug() << "create shot";

}

void Screenshots::delaySlot(QAction* action)
{
    ui->delay0->setChecked(false);
    ui->delay1->setChecked(false);
    ui->delay2->setChecked(false);
    ui->delay3->setChecked(false);
    ui->delay4->setChecked(false);
    ui->delay5->setChecked(false);

    action->setChecked(true);
    this->setDelay(action->text());
}

void Screenshots::exit()
{
    QCoreApplication::quit();
}

void Screenshots::saveActionSlot()
{
    if (this->screenImage->isNull()) {
        return;
    }

    QFileDialog fd;
    QString fileName = fd.getSaveFileName(this, "打开文件", "", "(*.png)");

    // bug: 需要设置默认扩展名

    if ("" == fileName) {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::OpenModeFlag::Truncate)) {
        QMessageBox::warning(this, "警告", "保存文件失败");
        return;
    } else {
        this->screenImage->save(&file, "", 100);
        file.flush();
        file.close();
    }
}

void Screenshots::cutActionSlot()
{
    int startX, startY, endX, endY;
    qDebug() << "cut" ;

    QPixmap qp = this->screenImage->copy(0, 0, 600, 600);

    this->screenImage->swap(qp);
    this->showImage();

}



