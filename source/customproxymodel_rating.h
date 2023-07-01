#ifndef CUSTOMPROXYMODEL_RATING_H
#define CUSTOMPROXYMODEL_RATING_H

#include <QSortFilterProxyModel>

class CustomProxyModelRating : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    CustomProxyModelRating(QObject *parent = nullptr);

    double filterMinimumRating() const { return minRating; }
    void setFilterMinimumRating(double rating);

    double filterMaximumRating() const { return maxRating; }
    void setFilterMaximumRating(double rating);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    bool ratingInRange(double rating) const;

    double minRating;
    double maxRating;
};


#endif // CUSTOMPROXYMODEL_RATING_H
