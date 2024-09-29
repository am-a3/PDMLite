#ifndef BOMENTRY_H
#define BOMENTRY_H

#include <QString>
#include <QDateTime>

class BomEntry
{
public:
    BomEntry();

    BomEntry(QString user);

    BomEntry(qint32 id, qint32 quantity, QString created_by, QDateTime created_datetime, QString last_modified_by,
            QDateTime last_modified_datetime);

    qint32 getId();
    void setId(qint32 value);

    qint32 getQuantity();
    void setQuantity(qint32 value, QString user);

    QString getCreatedBy();

    QDateTime getCreatedDatetime();

    QString getLastModifiedBy();

    QDateTime getLastModifiedDatetime();

    bool isUpdated();
    void setSaved();

private:
    qint32 id;
    qint32 quantity;
    QString created_by;
    QDateTime created_datetime;
    QString last_modified_by;
    QDateTime last_modified_datetime;
    bool is_updated;
};

#endif // BOMENTRY_H
