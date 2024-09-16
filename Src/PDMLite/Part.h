#ifndef PART_H
#define PART_H

#include <QString>
#include <QDateTime>

class Part
{
public:
    Part(QString user);

    Part(
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
        );

    QString getProprietaryId();

    bool setVersion(QString value, QString user);
    QString getVersion();

    bool setDescription(QString value, QString user);
    QString getDescription();

    qint32 getIsSimplePart();

    QString getCreatedBy();

    QDateTime getCreatedDate();

    QString getLastModifiedBy();

    QDateTime getLastModifiedDate();

    bool setCategory(QString value, QString user);
    QString getCategory();

    bool isNew();

    bool isUpdated();

    void setSaved();

    void clearParameters(QString user);

private:
    qint32 id;
    QString proprietary_id;
    QString version;
    QString description;
    qint32 is_simple;
    QString created_by;
    QDateTime created_datetime;
    QString last_modified_by;
    QDateTime last_modified_datetime;
    QString category;

    bool is_updated;
    bool is_new;

    void updateLastModified(QString user);
    qint32 generatePartNumber();
};

#endif // PART_H
