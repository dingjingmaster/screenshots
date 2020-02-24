#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include "screen.h"

#include <QMenu>
#include <QWidget>

class ScreenWidget : public QWidget
{
    Q_OBJECT
public:
    static ScreenWidget* Instance();
    explicit ScreenWidget(QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);

private slots:
    void saveScreen();
    void saveFullScreen();
    void saveScreenOther();
    void saveFullOther();

signals:
private:
    static QScopedPointer<ScreenWidget> self;
    QMenu *menu;            //右键菜单对象
    Screen *screen;         //截屏对象
    QPixmap *fullScreen;    //保存全屏图像
    QPixmap *bgScreen;      //模糊背景图
    QPoint movPos;          //坐标

};

#endif // SCREENWIDGET_H
