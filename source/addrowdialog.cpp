#include "addrowdialog.h"
#include "ui_addrowdialog.h"
#include <QMessageBox>
#include <QIntValidator>

// Dialog initialization
AddRowDialog::AddRowDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddRowDialog)
{
    // naming
    this->setWindowTitle("Add row");

    // UI connection
    ui->setupUi(this);

    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(saveAddedRow()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    // Validation for lines
    ui->IDLineEdit->setValidator(new QIntValidator(this));
    ui->ratingLineEdit->setValidator(new QDoubleValidator(0.0, 10.0, 1, this));
    ui->dateLineEdit->setValidator(new QIntValidator(0, 9999, this));
    ui->ratingLineEdit->setValidator(new QDoubleValidator(0.00000, 100.00000, 5, this));
}

// Saving new row data
void AddRowDialog::saveAddedRow()
{
    const QString csTitle("Error");
    QMessageBox msgBox;

    // Input data from ui
    int id = ui->IDLineEdit->text().toInt();
    QString title = ui->titleLineEdit->text();
    double rating = ui->ratingLineEdit->text().toDouble();
    int year = ui->dateLineEdit->text().toInt();
    QString genre = ui->genresLineEdit->text();
    double popularity = ui->popularityLineEdit->text().toDouble();

    // Check if data is appropriate
    if (id < 0)
    {
        const QString csMsg("ID can't be negative!");
        msgBox.critical(nullptr, csTitle, csMsg);
    }
    else if (title == "")
    {
        const QString csMsg("Title can't be empty!");
        msgBox.critical(nullptr, csTitle, csMsg);
    }
    else if (rating > 10)
    {
        const QString csMsg("Rating can't be greater than 10!");
        msgBox.critical(nullptr, csTitle, csMsg);
    }
    else if (rating < 0)
    {
        const QString csMsg("Rating can't be negative!");
        msgBox.critical(nullptr, csTitle, csMsg);
    }
    else if (year < 0)
    {
        const QString csMsg("Year can't be negative!");
        msgBox.critical(nullptr, csTitle, csMsg);
    }
    else if (genre == "")
    {
        const QString csMsg("Genre can't be empty!");
        msgBox.critical(nullptr, csTitle, csMsg);
    }
    else if (popularity > 100)
    {
        const QString csMsg("Rating can't be greater than 100!");
        msgBox.critical(nullptr, csTitle, csMsg);
    }
    else if (popularity < 0)
    {
        const QString csMsg("Popularity can't be negative!");
        msgBox.critical(nullptr, csTitle, csMsg);
    }
    else
    {
        newRow.append(id);
        newRow.append(title);
        newRow.append(rating);
        newRow.append(year);
        newRow.append(genre);
        newRow.append(popularity);
        accept();
    }
}

// Geting new row to outside scope
const QList<QVariant>& AddRowDialog::getNewRow()
{
    return newRow;
}


AddRowDialog::~AddRowDialog()
{
    delete ui;
}
