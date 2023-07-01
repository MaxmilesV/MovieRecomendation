#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include "aboutdialog.h"
#include <QFileDialog>
#include <QRegularExpression>
#include <QMessageBox>

// MainWindow initialization
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Connection with UI
    ui->setupUi(this);

    QObject::connect(ui->createTableButton, SIGNAL(clicked()), this, SLOT(createEmptyTable()));
    QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
    QObject::connect(ui->deleteRowButton, SIGNAL(clicked()), this, SLOT(deleteRowSlot()));
    QObject::connect(ui->addRowButton, SIGNAL(clicked()), this, SLOT(addRowSlot()));

    QObject::connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadFile()));
    QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(ui->actionCreate_new, SIGNAL(triggered()), this, SLOT(createEmptyTable()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));

    QObject::connect(ui->nameFilterlineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateFilterName(const QString &)));
    QObject::connect(ui->genreFilterlineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateFilterGenre(const QString &)));
    QObject::connect(ui->yearFilterlineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateFilterYear(const QString &)));

    QObject::connect(ui->ratingFromSlider, SIGNAL(valueChanged(int)), this, SLOT(updateFilterMinRating(int)));
    QObject::connect(ui->ratingFromSlider, SIGNAL(valueChanged(int)), this, SLOT(updateRatingFromLineEdit(int)));
    QObject::connect(ui->ratingToSlider, SIGNAL(valueChanged(int)), this, SLOT(updateFilterMaxRating(int)));
    QObject::connect(ui->ratingToSlider, SIGNAL(valueChanged(int)), this, SLOT(updateRatingToLineEdit(int)));

    QObject::connect(ui->popularityFromSlider, SIGNAL(valueChanged(int)), this, SLOT(updateFilterMinPopularity(int)));
    QObject::connect(ui->popularityFromSlider, SIGNAL(valueChanged(int)), this, SLOT(updatePopularityFromLineEdit(int)));
    QObject::connect(ui->popularityToSlider, SIGNAL(valueChanged(int)), this, SLOT(updateFilterMaxPopularity(int)));
    QObject::connect(ui->popularityToSlider, SIGNAL(valueChanged(int)), this, SLOT(updatePopularityToLineEdit(int)));

    QObject::connect(ui->tableDetailsView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeActiveRow(QModelIndex)));

    QObject::connect(ui->tableDetailsView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeActiveRow(QModelIndex)));

    // Validation for year filter
    ui->yearFilterlineEdit->setValidator(new QIntValidator(0, 9999, this));

    // Table creation
    _table = new Table(this);
    _table->createEmpty();

    // Filters initialization
    proxyModelName = new QSortFilterProxyModel(this);
    proxyModelGenre = new QSortFilterProxyModel(this);
    proxyModelYear = new QSortFilterProxyModel(this);
    proxyModelRating = new CustomProxyModelRating(this);
    proxyModelPopularity = new CustomProxyModelPopularity(this);

    proxyModelName->setSourceModel(_table);
    proxyModelGenre->setSourceModel(proxyModelName);
    proxyModelYear->setSourceModel(proxyModelGenre);
    proxyModelRating->setSourceModel(proxyModelYear);
    proxyModelPopularity->setSourceModel(proxyModelRating);

    ui->tableDetailsView->setModel(proxyModelPopularity);
    ui->tableDetailsView->setSortingEnabled(true);

    proxyModelName->setFilterKeyColumn(1);
    proxyModelGenre->setFilterKeyColumn(4);
    proxyModelYear->setFilterKeyColumn(3);
}


// About window
void MainWindow::showAbout()
{
    AboutDialog d;
    d.exec();
}


// Slider filter
void MainWindow::updateRatingFromLineEdit(int value)
{
    ui->ratingFromLineEdit->setText(QVariant(value).toString());
}

void MainWindow::updateRatingToLineEdit(int value)
{
    ui->ratingToLineEdit->setText(QVariant(value).toString());
}

void MainWindow::updatePopularityFromLineEdit(int value)
{
    ui->popularityFromLineEdit->setText(QVariant(value).toString());
}

void MainWindow::updatePopularityToLineEdit(int value)
{
    ui->popularityToLineEdit->setText(QVariant(value).toString());
}


// Row deletion
void MainWindow::deleteRowSlot()
{
    QModelIndex idx1 = ui->tableDetailsView->currentIndex();
    QModelIndex idx2 = proxyModelPopularity->mapToSource(idx1);
    QModelIndex idx3 = proxyModelRating->mapToSource(idx2);
    QModelIndex idx4 = proxyModelYear->mapToSource(idx3);
    QModelIndex idx5 = proxyModelGenre->mapToSource(idx4);
    QModelIndex idx6 = proxyModelName->mapToSource(idx5);
    if (_table->hasIndex(idx6.row(), idx6.column()))
    {
        _table->removeRow(idx6.row());
        deselectRow();
    }
}


// Rating filter change
void MainWindow::updateFilterMinRating(int value)
{
    proxyModelRating->setFilterMinimumRating(value);

    deselectRow();
}

void MainWindow::updateFilterMaxRating(int value)
{
    proxyModelRating->setFilterMaximumRating(value);

    deselectRow();
}


// Popularity filter change
void MainWindow::updateFilterMinPopularity(int value)
{
    proxyModelPopularity->setFilterMinimumPopularity(value);

    deselectRow();
}

void MainWindow::updateFilterMaxPopularity(int value)
{
    proxyModelPopularity->setFilterMaximumPopularity(value);

    deselectRow();
}


// Name filter change
void MainWindow::updateFilterName(const QString & text)
{
    proxyModelName->setFilterRegularExpression(QRegularExpression(text));

    deselectRow();
}


// Genre filter
void MainWindow::updateFilterGenre(const QString & text)
{
    proxyModelGenre->setFilterRegularExpression(QRegularExpression(text));

    deselectRow();
}


// Year filter
void MainWindow::updateFilterYear(const QString & text)
{
    proxyModelYear->setFilterRegularExpression(QRegularExpression(text));

    deselectRow();
}


// Create an empty table
void MainWindow::createEmptyTable()
{
    delete _table;

    _table = new Table(this);
    _table->createEmpty();

    proxyModelName->setSourceModel(_table);

    deselectRow();
}


// Read table from .csv file
void MainWindow::loadFile()
{
    delete _table;

    _table = new Table(this);
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", ".../", "Data (*.csv)");
    _table->fillDataTableFromFile(fileName);

    proxyModelName->setSourceModel(_table);
    
    deselectRow();
}


// Save table to .csv file
void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", ".../", "Data (*.csv)");
    _table->saveDataTableToFile(fileName);
}


// Add new row to existing table
void MainWindow::addRowSlot()
{
    AddRowDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        QList<QVariant> newRow = dialog.getNewRow();

        const QString csTitle("Warning");
        QMessageBox msgBox;

        bool valid = true;
        int col = 0;
        for (QVariant element : newRow)
        {
            if (col == 2)
            {
                double number = element.toDouble();
                double minRat = ui->ratingFromLineEdit->text().toDouble();
                double maxRat = ui->ratingToLineEdit->text().toDouble();

                if (maxRat < number || number < minRat)
                {
                    const QString csMsg("Row was created successfully, but is not in rating range filter!");
                    msgBox.critical(nullptr, csTitle, csMsg);
                }
            }
            else if (col == 5)
            {
                double number = element.toDouble();
                double minPop = ui->popularityFromLineEdit->text().toDouble();
                double maxPop = ui->popularityToLineEdit->text().toDouble();

                if (maxPop < number || number < minPop)
                {
                    const QString csMsg("Row was created successfully, but is not in popularity range filter!");
                    msgBox.critical(nullptr, csTitle, csMsg);
                }
            }
            ++col;
        }

        _table->appendRow(newRow);
    }



}


// Master-Detail implementation
void MainWindow::changeActiveRow(const QModelIndex &index)
{
    int row = index.row();

    QModelIndex idx1 = ui->tableDetailsView->currentIndex();
    QModelIndex idx2 = proxyModelPopularity->mapToSource(idx1);
    QModelIndex idx3 = proxyModelRating->mapToSource(idx2);
    QModelIndex idx4 = proxyModelYear->mapToSource(idx3);
    QModelIndex idx5 = proxyModelGenre->mapToSource(idx4);
    QModelIndex idx6 = proxyModelName->mapToSource(idx5);

    if (_table->hasIndex(idx6.row(), idx6.column()))
    {
        QModelIndex idIndex = _table->index(idx6.row(), 0);
        QModelIndex titleIndex = _table->index(idx6.row(), 1);
        QModelIndex dateIndex = _table->index(idx6.row(), 2);
        QModelIndex genreIndex = _table->index(idx6.row(), 4);
        QModelIndex popularityIndex = _table->index(idx6.row(), 5);

        QVariant idData = _table->data(idIndex);
        QVariant titleData = _table->data(titleIndex);
        QVariant dateData = _table->data(dateIndex);
        QVariant genreData = _table->data(genreIndex);
        QVariant popularityData = _table->data(popularityIndex);

        ui->idDataLabel->setText(idData.toString());
        ui->titleDataLabel->setText(titleData.toString());
        ui->dateDataLabel->setText(dateData.toString());
        ui->genreDataLabel->setText(genreData.toString());
        ui->popularityDataLabel->setText(popularityData.toString());
    }
}


// Restores Master-Detail initial value
void MainWindow::deselectRow()
{
    QString buffer = "__________";
    ui->idDataLabel->setText(buffer);
    ui->titleDataLabel->setText(buffer);
    ui->dateDataLabel->setText(buffer);
    ui->genreDataLabel->setText(buffer);
    ui->popularityDataLabel->setText(buffer);

    // Making wrong current index
    ui->tableDetailsView->setCurrentIndex(QModelIndex());
}

MainWindow::~MainWindow()
{
    delete ui;
}