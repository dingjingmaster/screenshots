#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

enum DelayConfig {
    SETTING_DELAY_0,
    SETTING_DELAY_1,
    SETTING_DELAY_2,
    SETTING_DELAY_3,
    SETTING_DELAY_4,
    SETTING_DELAY_5,
};

QT_BEGIN_NAMESPACE
namespace Ui { class Screenshots; }
QT_END_NAMESPACE

class Screenshots : public QMainWindow
{
    Q_OBJECT

public:
    Screenshots(QWidget *parent = nullptr);
    ~Screenshots();
    void setDelayConf(QString);
    void createRect();
    void showPicture();
    void shotScreenFull();


protected:
    virtual void resizeEvent(QResizeEvent* size) override;

private:
    void initConfig();

protected slots:
    void createShotSlot(QAction*);
    void delaySlot(QAction*);
    void exitScreenShot();
    void saveActionSlot();

private:
    enum DelayConfig delay;
    QPixmap* screenPicture;
    int posX, posY, width, height;

private:
    Ui::Screenshots *ui;
};
#endif // MAINWINDOW_H
