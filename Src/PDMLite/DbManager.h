#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include "Part.h"
#include <vector>

class DbManager
{
public:
    DbManager(const QString& path);
    bool addPart(Part part);
    Part queryPartByProprietaryId(QString id);
    bool deletePartByProprietaryId(QString id);
    bool queryAllParts(std::vector<Part> &parts, qint32 limit);
    bool updatePart(Part part);
    qint32 queryPartsCount();
private:
    QSqlDatabase m_db;
    bool checkTableExist(const QString table_name);
    void initTables(void);
};

#endif // DBMANAGER_H
