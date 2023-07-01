#include "customproxymodel_popularity.h"

// Popularity filter code

CustomProxyModelPopularity::CustomProxyModelPopularity(QObject *parent) : QSortFilterProxyModel{parent}
{
    maxPopularity = 101;
    minPopularity = -1;
}

bool CustomProxyModelPopularity::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex indexPopularity = sourceModel()->index(sourceRow, 5, sourceParent);

    return popularityInRange(sourceModel()->data(indexPopularity).toDouble());
}

bool CustomProxyModelPopularity::popularityInRange(double popularity) const
{
    return popularity >= minPopularity && popularity <= maxPopularity;
}

void CustomProxyModelPopularity::setFilterMinimumPopularity(double popularity)
{
    minPopularity = popularity;
    invalidateFilter();
}

void CustomProxyModelPopularity::setFilterMaximumPopularity(double popularity)
{
    maxPopularity = popularity;
    invalidateFilter();
}
