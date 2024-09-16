#include "DbManager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

struct PartQueryData_t
{
    qint32 id = 0;
    QString proprietary_id = "";
    QString version = "";
    QString description = "";
    qint32 is_simple = 0;
    QString created_by = "";
    QDateTime created_datetime = QDateTime::currentDateTime();
    QString last_modified_by = "";
    QDateTime last_modified_datetime = QDateTime::currentDateTime();
    QString category = "";
};

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
        initTables();
    }
}

bool DbManager::checkTableExist(const QString table_name)
{
    QSqlQuery query;
    query.prepare("SELECT name FROM sqlite_master WHERE type='table' AND name=:tableName");
    query.bindValue(":tableName", table_name);

    if (query.exec()) {
        return query.next();
    } else {
        qDebug() << "Error checking table existence:" << query.lastError().text();
        return false;
    }
}

void DbManager::initTables(void)
{
    QSqlQuery query;

    if (!checkTableExist("parts")) {
        qDebug() << "Creating parts table";
        query.prepare("CREATE TABLE parts ("
                      "id INTEGER PRIMARY KEY, "
                      "proprietary_id VARCHAR(255) NOT NULL, "
                      "description VARCHAR(255), "
                      "is_simple INT NOT NULL, "
                      "created_by VARCHAR(255), "
                      "create_datetime DATETIME, "
                      "last_modified_by VARCHAR(255), "
                      "last_modified_datetime DATETIME, "
                      "category VARCHAR(255), "
                      "UNIQUE (proprietary_id)"
                      ");");

        if(!query.exec())
        {
            qDebug() << "create parts table error:"
                     << query.lastError();
        }
    }


}

bool DbManager::queryAllParts(std::vector<Part> &parts, qint32 limit)
{
    bool success = false;
    QSqlQuery query;
    int index;
    PartQueryData_t part_query;

    query.prepare("SELECT * FROM parts LIMIT :limit");
    query.bindValue(":limit", limit);

    if(query.exec())
    {
        while (query.next()) {
            index = query.record().indexOf("id");
            part_query.id = query.value(index).toInt();
            index = query.record().indexOf("proprietary_id");
            part_query.proprietary_id = query.value(index).toString();
            index = query.record().indexOf("version");
            part_query.version = query.value(index).toString();
            index = query.record().indexOf("description");
            part_query.description = query.value(index).toString();
            index = query.record().indexOf("is_simple");
            part_query.is_simple = query.value(index).toBool();
            index = query.record().indexOf("created_by");
            part_query.created_by = query.value(index).toString();
            index = query.record().indexOf("create_datetime");
            part_query.created_datetime = query.value(index).toDateTime();
            index = query.record().indexOf("last_modified_by");
            part_query.last_modified_by = query.value(index).toString();
            index = query.record().indexOf("last_modified_datetime");
            part_query.last_modified_datetime = query.value(index).toDateTime();
            index = query.record().indexOf("category");
            part_query.category = query.value(index).toString();

            auto part = Part(
                            part_query.id,
                            part_query.proprietary_id,
                            part_query.version,
                            part_query.description,
                            part_query.is_simple,
                            part_query.created_by,
                            part_query.created_datetime,
                            part_query.last_modified_by,
                            part_query.last_modified_datetime,
                            part_query.category
                );

            parts.push_back(part);
        }

        success = true;
    }
    else
    {
        qDebug() << "addPart error:"
                 << query.lastError();
    }

    return success;
}

bool DbManager::addPart(Part part)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO parts (proprietary_id, version, description, is_simple,"
                  "created_by, create_datetime, last_modified_by, last_modified_datetime,"
                  "category) VALUES (:proprietary_id, :version, :description, :is_simple,"
                  ":created_by, :created_datetime, :last_modified_by, :last_modified_datetime,"
                  ":category)");
    query.bindValue(":proprietary_id", part.getProprietaryId());
    query.bindValue(":version", part.getVersion());
    query.bindValue(":description", part.getDescription());
    query.bindValue(":is_simple", part.getIsSimplePart());
    query.bindValue(":created_by", part.getCreatedBy());
    query.bindValue(":last_modified_by", part.getLastModifiedBy());
    query.bindValue(":category", part.getCategory());
    query.bindValue(":created_datetime", part.getCreatedDate());
    query.bindValue(":last_modified_datetime", part.getLastModifiedDate());

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "[ERROR] addPart:"
                 << query.lastError();
    }

    return success;
}

Part DbManager::queryPartByProprietaryId(QString id) //TODO: need to throw exception if quesry fail
{
    QSqlQuery query;
    int index;
    PartQueryData_t part;

    query.prepare("SELECT * FROM parts WHERE proprietary_id = (:id) LIMIT 1");
    query.bindValue(":id", id);

    if(query.exec())
    {
        if (query.next()) {
            part.proprietary_id = id;
            index = query.record().indexOf("id");
            part.id = query.value(index).toInt();
            index = query.record().indexOf("version");
            part.version = query.value(index).toString();
            index = query.record().indexOf("description");
            part.description = query.value(index).toString();
            index = query.record().indexOf("is_simple");
            part.is_simple = query.value(index).toBool();
            index = query.record().indexOf("created_by");
            part.created_by = query.value(index).toString();
            index = query.record().indexOf("create_datetime");
            part.created_datetime = query.value(index).toDateTime();
            index = query.record().indexOf("last_modified_by");
            part.last_modified_by = query.value(index).toString();
            index = query.record().indexOf("last_modified_datetime");
            part.last_modified_datetime = query.value(index).toDateTime();
            index = query.record().indexOf("category");
            part.category = query.value(index).toString();

            return Part(
                part.id,
                part.proprietary_id,
                part.version,
                part.description,
                part.is_simple,
                part.created_by,
                part.created_datetime,
                part.last_modified_by,
                part.last_modified_datetime,
                part.category);
        }
    }
    else
    {
        qDebug() << "query part error:"
                 << query.lastError();
    }

    return Part("dummy");
}

bool DbManager::deletePartByProprietaryId(QString id)
{
    QSqlQuery query;
    bool success = false;

    query.prepare("DELETE FROM parts WHERE proprietary_id = (:id)");
    query.bindValue(":id", id);

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addPart error:"
                 << query.lastError();
    }

    return success;
}

bool DbManager::updatePart(Part part)
{
    QSqlQuery query;
    bool success = false;

    query.prepare("UPDATE parts SET description = :description, category = :category, version = :version,"
                  "is_simple = :is_simple, last_modified_by = :last_modified_by, last_modified_datetime = :last_modified_datetime"
                  " WHERE proprietary_id = :proprietary_id");
    query.bindValue(":description", part.getDescription());
    query.bindValue(":category", part.getCategory());
    query.bindValue(":proprietary_id", part.getProprietaryId());
    query.bindValue(":version", part.getVersion());
    query.bindValue(":is_simple", part.getIsSimplePart());
    query.bindValue(":last_modified_by", part.getLastModifiedBy());
    query.bindValue(":last_modified_datetime", part.getLastModifiedDate());

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addPart error:"
                 << query.lastError();
    }

    return success;
}
