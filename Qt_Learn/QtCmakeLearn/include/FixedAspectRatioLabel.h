#pragma once
#include <QLabel>
#include <QResizeEvent>

class FixedAspectRatioLabel : public QLabel
{
public:
    FixedAspectRatioLabel(QWidget *parent = nullptr) : QLabel(parent)
    {
        aspectRatio_ = 2.0;
    }

    void setAspectRatio(double aspectRatio)
    {
        aspectRatio_ = aspectRatio;
        updateFixedHeight();
    }

protected:
    void resizeEvent(QResizeEvent *event) override
    {
        QLabel::resizeEvent(event);
        updateFixedHeight();
    }

private:
    void updateFixedHeight()
    {
        int width = this->height()*aspectRatio_;
        int height = this->height();
        this->setFixedWidth(width);
    }

    double aspectRatio_;
};