#include "BomEntry.h"

BomEntry::BomEntry() {}

BomEntry::BomEntry(QString user)
{
    this->id = 0;
    this->quantity = 0;
    this->created_by = user;
    this->created_datetime = QDateTime::currentDateTime();
    this->last_modified_by = user;
    this->last_modified_datetime = QDateTime::currentDateTime();
    this->is_updated = false;
}

BomEntry::BomEntry(qint32 id, qint32 quantity, QString created_by, QDateTime created_datetime, QString last_modified_by,
         QDateTime last_modified_datetime)
{
    this->id = id;
    this->quantity = quantity;
    this->created_by = created_by;
    this->created_datetime = created_datetime;
    this->last_modified_by = last_modified_by;
    this->last_modified_datetime = last_modified_datetime;
    this->is_updated = false;
}

qint32 BomEntry::getId()
{
    return this->id;
}

void BomEntry::setId(qint32 value)
{
    this->id = value;
}

qint32 BomEntry::getQuantity()
{
    return this->quantity;
}

void BomEntry::setQuantity(qint32 value, QString user)
{
    this->quantity = value;
    this->last_modified_by = user;
    this->last_modified_datetime = QDateTime::currentDateTime();
    this->is_updated = true;
}

QString BomEntry::getCreatedBy()
{
    return this->created_by;
}

QDateTime BomEntry::getCreatedDatetime()
{
    return this->created_datetime;
}

QString BomEntry::getLastModifiedBy()
{
    return this->last_modified_by;
}

QDateTime BomEntry::getLastModifiedDatetime()
{
    return this->last_modified_datetime;
}

bool BomEntry::isUpdated()
{
    return this->is_updated;
}

void BomEntry::setSaved()
{
    this->is_updated = false;
}
