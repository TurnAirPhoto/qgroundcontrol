#include "UASQuickViewTextItem.h"
#include <QVBoxLayout>
#include <QDebug>
UASQuickViewTextItem::UASQuickViewTextItem(QWidget *parent) : UASQuickViewItem(parent)
{
    // Set a standard vertical layout.
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSizeConstraint(QLayout::SetMinimumSize);

    // Create the title label. Scale the font based on available size.
    titleLabel = new QLabel(this);
// <<<<<<< HEAD
     titleLabel->setAlignment(Qt::AlignHCenter);
     titleLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);
     titleLabel->setObjectName(QString::fromUtf8("title"));
     QFont titlefont = titleLabel->font();
     titlefont.setPixelSize(this->height() / 4.0);
     titleLabel->setFont(titlefont);
     layout->addWidget(titleLabel);

     // Create the value label. Scale the font based on available size.
     valueLabel = new QLabel(this);
     valueLabel->setAlignment(Qt::AlignHCenter);
     valueLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);
     valueLabel->setObjectName(QString::fromUtf8("value"));
     valueLabel->setText("0.00");
// =======
//    titleLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
//    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
//    this->layout()->addWidget(titleLabel);
//    valueLabel = new QLabel(this);
//    valueLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
//    valueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
//    valueLabel->setText("0.00");
//    this->layout()->addWidget(valueLabel);
//    //spacerItem = new QSpacerItem(20,40,QSizePolicy::Minimum,QSizePolicy::Ignored);
//    //layout->addSpacerItem(spacerItem);
// >>>>>>> 34eaf1fb422146f5df3b01fad4d756343b3127c9
    QFont valuefont = valueLabel->font();
    valuefont.setPixelSize(this->height() / 2.0);
    valueLabel->setFont(valuefont);
    layout->addWidget(valueLabel);

    // And make sure the items are evenly spaced in the UASQuickView.
    layout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    this->setLayout(layout);
}
void UASQuickViewTextItem::setValue(double value)
{
    valueLabel->setText(QString::number(value,'f',4));
}

void UASQuickViewTextItem::setTitle(QString title)
{
    if (title.indexOf(".") != -1 && title.indexOf(":") != -1)
    {
        titleLabel->setText(title.mid(title.indexOf(".")+1));
    }
    else
    {
        titleLabel->setText(title);
    }
}
void UASQuickViewTextItem::resizeEvent(QResizeEvent *event)
{
    QFont valuefont = valueLabel->font();
    QFont titlefont = titleLabel->font();
    valuefont.setPixelSize(this->height());
    titlefont.setPixelSize(valuefont.pixelSize() / 2.0);
    //spacerItem->setGeometry(QRect(0,0,20,this->height()/10.0));

    QFontMetrics metrics(valuefont);
    //valuefont.setPixelSize(this->height() / 2.0);
    bool fit = false;
    while (!fit)
    {

        QFontMetrics valfm( valuefont );
        QRect valbound = valfm.boundingRect(0,0, valueLabel->width(), valueLabel->height(), Qt::TextWordWrap | Qt::AlignLeft, valueLabel->text());
        //QFontMetrics titlefm( titlefont );
        //QRect titlebound = titlefm.boundingRect(0,0, titleLabel->width(), titleLabel->height(), Qt::TextWordWrap | Qt::AlignLeft, titleLabel->text());

        if ((valbound.width() <= valueLabel->width() && valbound.height() <= valueLabel->height()))// && (titlebound.width() <= titleLabel->width() && titlebound.height() <= titleLabel->height()))
            fit = true;
        else
        {
            if (valuefont.pixelSize()-5 <= 0)
            {
                fit = true;
                valuefont.setPixelSize(5);
            }
            else
            {
                valuefont.setPixelSize(valuefont.pixelSize() - 5);
            }
            //titlefont.setPixelSize(valuefont.pixelSize() / 2.0);
            //qDebug() << "Point size:" << valuefont.pixelSize() << valueLabel->width() << valueLabel->height();
        }
    }
titlefont.setPixelSize(valuefont.pixelSize() / 2.0);
    valueLabel->setFont(valuefont);
    titleLabel->setFont(titlefont);
    update();
}