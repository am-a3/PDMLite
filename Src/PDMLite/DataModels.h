#ifndef DATAMODELS_H
#define DATAMODELS_H

#include <QString>
#include <QDateTime>

struct PartData_t
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

#endif // DATAMODELS_H
