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
    this->setWindowIcon(QIcon(":/screenshots/img/64x64/screenshots.png"));
    this->scroll(2,3);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);

    screenPicture = new QPixmap();
    posX = posY = 0;
    width = height = -1;

    initConfig();

    connect(ui->delayMenu, &QMenu::triggered, this, &Screenshots::delaySlot);

    connect(ui->createShotFull, &QAction::triggered, this, &Screenshots::shotScreenFull);
    connect(ui->exitAction, &QAction::triggered, this, &Screenshots::exitScreenShot);
    connect(ui->saveAction, &QAction::triggered, this, &Screenshots::saveActionSlot);
}

Screenshots::~Screenshots()
{
    delete ui;
}

void Screenshots::setDelayConf(QString str)
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

void Screenshots::createRect()
{
    qDebug() << "create";
    QWindow window;

    *screenPicture = window.screen()->grabWindow(QApplication::desktop()->winId(), posX, posY, width, height);
    posX = posY = 0;
    width = height = -1;
}

void Screenshots::resizeEvent(QResizeEvent*)
{
    ui->picLabel->resize(ui->centralwidget->size());

    showPicture();
}

void Screenshots::showPicture()
{
    if (this->screenPicture->isNull()) {
        return;
    }
    ui->picLabel->setPixmap((this->screenPicture->scaled(\
        ui->picLabel->width(), ui->picLabel->height())));
    ui->picLabel->setScaledContents(true);
}

void Screenshots::shotScreenFull()
{
    this->hide();
    QTime tim = QTime::currentTime().addMSecs(1000 * this->delay);
    while (QTime::currentTime() < tim) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    createRect();
    this->show();
    showPicture();
}

void Screenshots::initConfig()
{
    this->delay = SETTING_DELAY_0;
    ui->delay0->setChecked(true);
}

void Screenshots::createShotSlot(QAction* action)
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
    this->setDelayConf(action->text());
}

void Screenshots::exitScreenShot()
{
    QCoreApplication::quit();
}

void Screenshots::saveActionSlot()
{
    if (this->screenPicture->isNull()) {
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
        this->screenPicture->save(&file, "", 100);
        file.flush();
        file.close();
    }
}



