#ifndef DATAMODELS_H
#define DATAMODELS_H

#include <QString>
#include <QDateTime>

const QString PartCategoryElectrical = "Electrical";
const QString PartCategoryMechanical = "Mechanical";

typedef struct PartData_t {
    QString proprietary_id;
    QString version;
    QString description;
    qint32 is_simple;
    QString created_by;
    QDateTime created_datetime;
    QString last_modified_by;
    QDateTime last_modified_datetime;
    QString category;
} PartData_t;

#endif // DATAMODELS_H
