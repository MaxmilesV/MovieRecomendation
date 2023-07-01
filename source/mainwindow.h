#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "table.h"
#include "customproxymodel_rating.h"
#include "customproxymodel_popularity.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void createEmptyTable();
    void loadFile();
    void saveFile();
    void addRowSlot();
    void deleteRowSlot();

    void updateFilterName(const QString & text);
    void updateFilterGenre(const QString & text);
    void updateFilterYear(const QString & text);

    void updateFilterMinRating(int value);
    void updateFilterMaxRating(int value);
    void updateRatingFromLineEdit(int value);
    void updateRatingToLineEdit(int value);

    void updateFilterMinPopularity(int value);
    void updateFilterMaxPopularity(int value);
    void updatePopularityFromLineEdit(int value);
    void updatePopularityToLineEdit(int value);

    void changeActiveRow(const QModelIndex &index);
    void deselectRow();

    void showAbout();

private:
    size_t _shownDetailsColumn;
    Table *_table;
    QSortFilterProxyModel *proxyModelName;
    QSortFilterProxyModel *proxyModelGenre;
    QSortFilterProxyModel *proxyModelYear;
    CustomProxyModelRating *proxyModelRating;
    CustomProxyModelPopularity *proxyModelPopularity;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
