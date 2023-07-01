#ifndef CUSTOMPROXYMODEL_POPULARITY_H
#define CUSTOMPROXYMODEL_POPULARITY_H

#include <QSortFilterProxyModel>

class CustomProxyModelPopularity : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    CustomProxyModelPopularity(QObject *parent = nullptr);

    double filterMinimumPopularity() const { return minPopularity; }
    void setFilterMinimumPopularity(double popularity);

    double filterMaximumPopularity() const { return maxPopularity; }
    void setFilterMaximumPopularity(double popularity);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    bool popularityInRange(double popularity) const;

    double minPopularity;
    double maxPopularity;
};


#endif // CUSTOMPROXYMODEL_POPULARITY_H
