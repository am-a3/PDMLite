#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <vector>

#include "BomEntry.h"
#include "Part.h"

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
    bool queryPartProprietaryIdExists(QString id);

    QMap<QString, BomEntry> queryPartBom(QString id);
    bool savePartBomEntry(QString part_id, QString contains_part_id, BomEntry& entry);

private:
    QSqlDatabase m_db;
    bool checkTableExist(const QString table_name);
    void initTables(void);

    bool checkPartBomEntryExists(QString part_number, QString contains_part_number);
};

#endif // DBMANAGER_H
