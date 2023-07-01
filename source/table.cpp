#include "table.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

// Table initialization
Table::Table(QObject *parent) : QAbstractTableModel(parent)
{
}

// Creating an empty table
void Table::createEmpty()
{
    // Template for header
    QString template_header = "id;title;average rating;release date;genres;popularity";
    for (QString& item : template_header.split(";")) 
    {
        headerList.append(item);
    }

    // Template for row
    QString line = "0;name;0;0;genre;0";
    QList<QVariant> dataRow;

    // Reading row's data
    int columnIdx = 0;
    for (QString& item : line.split(";")) 
    {
        if (columnIdx == 0 || columnIdx == 3)
        {
            dataRow.append(item.toInt());
        }
        else if (columnIdx == 2 || columnIdx == 5)
        {
            dataRow.append(item.toDouble());
        }
        else
        {
            dataRow.append(item);
        }
        ++columnIdx;
    }

    // Adding data from row to table
    dataTable.append(dataRow);
}


// Reading file
void Table::fillDataTableFromFile(QString path)
{
    // Connecting input to file
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    // Reading columns names
    QString firstline = inputStream.readLine();
    for (QString& item : firstline.split(";")) 
    {
        headerList.append(item);
    }

    // Reading table rows
    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();

        QList<QVariant> dataRow;
        int columnIdx = 0;
        for (QString& item : line.split(";")) 
        {
            if (columnIdx == 0 || columnIdx == 3)
            {
                dataRow.append(item.toInt());
            }
            else if (columnIdx == 2 || columnIdx == 5)
            {
                dataRow.append(item.toDouble());
            }
            else
            {
                dataRow.append(item);
            }
            ++columnIdx;
        }
        dataTable.append(dataRow);
    }

    // Closing file
    inputFile.close();
}

// Writing to file
void Table::saveDataTableToFile(QString path)
{
    //Connecting output to file
    QFile outputFile(path);
    outputFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream outputStream(&outputFile);

    // Writing columns names
    bool first = true;
    for (QString& item : headerList) 
    {
        if (first)
        {
            outputStream << item;
            first = false;
        }
        else
        {
            outputStream << ";";
            outputStream << item;
        }
    }
    outputStream << "\n";

    // Writing table rows
    for (QList<QVariant>& row: dataTable)
    {
        bool first = true;
        for (QVariant& item : row) 
        {
            if (first)
            {
                outputStream << item.toString();
                first = false;
            }
            else
            {
                outputStream << ";";
                outputStream << item.toString();
            }
        }
        outputStream << "\n";
    }

    // Closing file
    outputFile.close();
}


// Row counter
int Table::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return dataTable.size();
}

// Columns counter
int Table::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (dataTable.empty())
    {
        return 0;
    }

    return dataTable[0].size();
}

// Get data from header
QVariant Table::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headerList[section];
    }
    return QVariant();
}

// get cell value
QVariant Table::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int row = index.row();
        int col = index.column();
        return dataTable[row][col];
    }
    return QVariant();
}

// Change cell value
bool Table::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) 
    {
        int row = index.row();
        int col = index.column();

        QVariant new_value;

        if (col == 0 && (value.toInt() < 0))
        {
            new_value = 0;
        }
        else if (col == 2 && (value.toDouble() > 10))
        {
            new_value = 10;
        }
        else if (col == 2 && (value.toDouble() < 100))
        {
            new_value = 0;
        }
        else if (col == 3 && (value.toInt() < 0))
        {
            new_value = 0;
        }
        else if (col == 5 && (value.toDouble() > 100))
        {
            new_value = 100;
        }
        else if (col == 5 && (value.toDouble() < 100))
        {
            new_value = 0;
        }
        else
        {
            new_value = value;
        }

        dataTable[row][col] = new_value;
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

// Flags
Qt::ItemFlags Table::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

// Add new row
void Table::appendRow(const QList<QVariant> &row)
{
    size_t newRowNumber = rowCount();
    beginInsertRows(QModelIndex(), newRowNumber, newRowNumber);
    dataTable.append(row);
    endInsertRows();
}

// Remove row
void Table::removeRow(int idx)
{
    beginRemoveRows(QModelIndex(), idx, idx);
    dataTable.removeAt(idx);
    endRemoveRows();
}
