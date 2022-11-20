#include "display.h"
#include "image_util.h"
#include "utility.h"

DisplayWidget::DisplayWidget(QWidget* parent) {}

void DisplayWidget::drawImage(const image::Image& img)
{
    util::convert_image(img, _image);
    repaint();
}

void DisplayWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    const QRect rect{0, 0, this->width(), this->height()};

    painter.drawImage(rect, _image);
}
