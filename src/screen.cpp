#include "screen.h"

Screen::Screen(QSize size)
{
    maxWidth = size.width();
    maxHeight = size.height();

    startPos = QPoint(-1, -1);
    endPos = startPos;
    leftUpPos = startPos;
    rightDownPos = startPos;
    status = SELECT;
}

Screen::~Screen()
{

}

void Screen::setStart(QPoint pos)
{
    startPos = pos;
}

void Screen::setEnd(QPoint pos)
{
    endPos = pos;
    leftUpPos = startPos;
    rightDownPos = endPos;
    cmpPoint(leftUpPos, rightDownPos);
}

QPoint Screen::getStart()
{
    return startPos;
}

QPoint Screen::getEnd()
{
    return endPos;
}

QPoint Screen::getLeftUp()
{
    return leftUpPos;
}

QPoint Screen::getRightDown()
{
    return rightDownPos;
}

Screen::STATUS Screen::getStatus()
{
    return status;
}

void Screen::setStatus(Screen::STATUS status)
{
    this->status = status;
}

int Screen::width()
{
    return maxWidth;
}

int Screen::height()
{
    return maxHeight;
}

bool Screen::isInArea(QPoint pos)
{
    if (pos.x() > leftUpPos.x() && pos.x() < rightDownPos.x() &&
            pos.y() > leftUpPos.y() && pos.y() < rightDownPos.y()) {
        return true;
    }
    return false;
}

void Screen::move(QPoint p)
{
    int lx = leftUpPos.x() + p.x();
    int ly = leftUpPos.y() + p.y();
    int rx = rightDownPos.x() + p.x();
    int ry = rightDownPos.y() + p.y();

    if (lx < 0) {
        lx = 0;
        rx -= p.x();
    }

    if (ly < 0) {
        ly = 0;
        ry -= p.y();
    }

    if (rx > maxWidth) {
        rx = maxWidth;
        lx -= p.x();
    }

    if (ry > maxHeight) {
        ry = maxHeight;
        ly -= p.y();
    }

    leftUpPos = QPoint(lx, ly);
    rightDownPos = QPoint(rx, ry);
    startPos = leftUpPos;
    endPos = rightDownPos;
}

void Screen::cmpPoint(QPoint &s, QPoint &e)
{
    QPoint l = s;
    QPoint r = e;

    if (l.x() <= r.x()) {
        if (l.y() <= r.y()) {

        } else {
            s.setY(r.y());
            e.setY(l.y());
        }
    } else {
        if (l.y() < r.y()) {
            s.setX(r.x());
            e.setX(l.x());
        } else {
            QPoint tmp;
            tmp = s;
            s = e;
            e = tmp;
        }
    }

}
