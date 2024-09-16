#include "Part.h"
#include <random>

Part::Part(QString user) {
    this->id = 0;
    this->proprietary_id = QString::number(generatePartNumber());
    this->version = "";
    this->description = "";
    this->is_simple = 0;
    this->created_by = user;
    this->created_datetime = QDateTime::currentDateTime();
    this->last_modified_by = "";
    this->last_modified_datetime = QDateTime::currentDateTime();
    this->category = "";

    this->is_new = true;
    this-> is_updated = false;
}

Part::Part(
    qint32 id,
    QString proprietary_id,
    QString version,
    QString description,
    qint32 is_simple,
    QString created_by,
    QDateTime created_datetime,
    QString last_modified_by,
    QDateTime last_modified_datetime,
    QString category
    )
{
    this->id = id;
    this->proprietary_id = proprietary_id;
    this->version = version;
    this->description = description;
    this->is_simple = is_simple;
    this->created_by = created_by;
    this->created_datetime = created_datetime;
    this->last_modified_by = last_modified_by;
    this->last_modified_datetime = last_modified_datetime;
    this->category = category;

    this->is_new = false;
    this-> is_updated = false;
}

QString Part::getProprietaryId()
{
    return this->proprietary_id;
}

bool Part::setVersion(QString value, QString user)
{
    this->version = value;
    updateLastModified(user);
    return true;
}

QString Part::getVersion()
{
    return this->version;
}

bool Part::setDescription(QString value, QString user)
{
    this->description = value;
    updateLastModified(user);
    return true;
}

QString Part::getDescription()
{
    return this->description;
}

qint32 Part::getIsSimplePart()
{
    return this->is_simple;
}

QString Part::getCreatedBy()
{
    return this->created_by;
}

QDateTime Part::getCreatedDate()
{
    return this->created_datetime;
}

QString Part::getLastModifiedBy()
{
    return this->last_modified_by;
}

QDateTime Part::getLastModifiedDate()
{
    return this->last_modified_datetime;
}

bool Part::setCategory(QString value, QString user)
{
    this->category = value;
    updateLastModified(user);
    return true;
}

QString Part::getCategory()
{
    return this->category;
}

bool Part::isNew()
{
    return this->is_new;
}

bool Part::isUpdated()
{
    return this-> is_updated;
}

void Part::setSaved()
{
    this-> is_new = false;
    this-> is_updated = false;
}

void Part::clearParameters(QString user)
{
    this->id = 0;
    this->proprietary_id = QString::number(generatePartNumber());
    this->version = "";
    this->description = "";
    this->is_simple = 0;
    this->created_by = user;
    this->created_datetime = QDateTime::currentDateTime();
    this->last_modified_by = "";
    this->last_modified_datetime = QDateTime::currentDateTime();
    this->category = "";

    this->is_new = true;
    this-> is_updated = false;
}

void Part::updateLastModified(QString user)
{
    this->last_modified_by = user;
    this->last_modified_datetime = QDateTime::currentDateTime();
    this-> is_updated = true;
}

qint32 Part::generatePartNumber()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> part_number(10000, 99999); //TODO: temporary solution

    return part_number(rng);
}
