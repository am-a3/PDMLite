#include "DbManager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

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
        query.prepare("CREATE TABLE parts (id INT NOT NULL AUTO_INCREMENT,"
                      "proprietary_id VARCHAR NOT NULL,"
                      "description VARCHAR,"
                      "is_simple INT NOT NULL,"
                      "created_by VARCHAR,"
                      "create_datetime DATETIME,"
                      "last_modified_by VARCHAR,"
                      "last_modified_datetime DATETIME,"
                      "category VARCHAR"
                      "PRIMARY KEY (id,proprietary_id))");

        if(!query.exec())
        {
            qDebug() << "create parts table error:"
                     << query.lastError();
        }
    }
}

bool DbManager::queryAllParts(std::vector<PartData_t> &parts)
{

}

bool DbManager::addPart(PartData_t part)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO parts (proprietary_id, version, description, is_simple,"
                  "created_by, created_datetime, last_modified_by, last_modified_datetime,"
                  "category) VALUES (:proprietary_id, :version, :description, :is_simple,"
                  ":created_by, current_timestamp, :last_modified_by, current_timestamp,"
                  ":category)");
    query.bindValue(":proprietary_id", part.proprietary_id);
    query.bindValue(":version", part.version);
    query.bindValue(":description", part.description);
    query.bindValue(":is_simple", part.is_simple);
    query.bindValue(":created_by", part.created_by);
    query.bindValue(":last_modified_by", part.last_modified_by);
    query.bindValue(":category", part.category);

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

bool DbManager::queryPartById(QString id, PartData_t &part)
{
    PartData_t data;
    QSqlQuery query;
    int index;

    query.prepare("SELECT * FROM parts WHERE proprietary_id = (:id) LIMIT 1");
    query.bindValue(":id", id);

    if(query.exec())
    {
        if (query.next()) {
            part.proprietary_id = id;
            index = query.record().indexOf("version");
            part.version = query.value(index).toString();
            index = query.record().indexOf("description");
            part.description = query.value(index).toString();
            index = query.record().indexOf("is_simple");
            part.is_simple = query.value(index).toBool();
            index = query.record().indexOf("created_by");
            part.created_by = query.value(index).toString();
            index = query.record().indexOf("created_datetime");
            part.created_datetime = query.value(index).toDateTime();
            index = query.record().indexOf("last_modified_by");
            part.last_modified_by = query.value(index).toString();
            index = query.record().indexOf("last_modified_datetime");
            part.last_modified_datetime = query.value(index).toDateTime();
            index = query.record().indexOf("category");
            part.category = query.value(index).toString();

            return true;
        }
    }
    else
    {
        qDebug() << "query part error:"
                 << query.lastError();
    }

    return false;
}

bool DbManager::deletePartById(QString id)
{
    QSqlQuery query;
    bool success = false;

    query.prepare("DELETE FROM parts WHERE id = (:id)");
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
