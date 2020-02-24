#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QObject>
#include <QLabel>
#include <QWidget>

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    ImageLabel();
    ImageLabel(QWidget* parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    ~ImageLabel();
};

#endif // IMAGELABEL_H
