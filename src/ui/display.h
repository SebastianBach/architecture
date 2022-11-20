#pragma once

#include <qpainter.h>
#include <qwidget.h>
#include "image.h"

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    DisplayWidget(QWidget* parent);

    void drawImage(const image::Image& img);


protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QImage _image;
};
