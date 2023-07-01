#include "customproxymodel_rating.h"

// Rating filter code

CustomProxyModelRating::CustomProxyModelRating(QObject *parent) : QSortFilterProxyModel{parent}
{
    maxRating = 11;
    minRating = -1;
}

bool CustomProxyModelRating::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex indexRating = sourceModel()->index(sourceRow, 2, sourceParent);

    return ratingInRange(sourceModel()->data(indexRating).toDouble());
}

bool CustomProxyModelRating::ratingInRange(double rating) const
{
    return rating >= minRating && rating <= maxRating;
}

void CustomProxyModelRating::setFilterMinimumRating(double rating)
{
    minRating = rating;
    invalidateFilter();
}

void CustomProxyModelRating::setFilterMaximumRating(double rating)
{
    maxRating = rating;
    invalidateFilter();
}
