#include "aboutdialog.h"
#include "ui_aboutdialog.h"

// Dialog initialization
AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("About");
}

// Emblem draw by lines
void AboutDialog::paintEvent(QPaintEvent *event)
{
    QPainter myline(this);
    QPen linePen(Qt::black);
    linePen.setWidth(3);

    myline.setPen(linePen);

    // Drawing a camera box
    myline.drawLine(112, 120, 345, 120);
    myline.drawLine(345, 120, 345, 260);
    myline.drawLine(112, 241, 345, 241);
    myline.drawLine(112, 260, 112, 120);
    myline.drawLine(345, 260, 112, 260);

    // Drawing a camera lens
    myline.drawLine(406, 118, 406, 243);
    myline.drawLine(406, 243, 345, 180);
    myline.drawLine(345, 180, 406, 118);

    myline.drawEllipse(117, 25, 95, 95);
    myline.drawEllipse(243, 53, 67, 67);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}