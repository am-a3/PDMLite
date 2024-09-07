#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include "DataModels.h"
#include <vector>

class DbManager
{
public:
    DbManager(const QString& path);
    bool addPart(PartData_t part);
    bool queryPartByProprietaryId(QString id, PartData_t &part);
    bool deletePartByProprietaryId(QString id);
    bool queryAllParts(std::vector<PartData_t> &parts, qint32 limit);
    bool updatePart(PartData_t part);
private:
    QSqlDatabase m_db;
    bool checkTableExist(const QString table_name);
    void initTables(void);
};

#endif // DBMANAGER_H
