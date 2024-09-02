#ifndef PDMMODEL_H
#define PDMMODEL_H

#include "DataModels.h"
#include "DbManager.h"

class PdmModel
{
public:
    PdmModel();
    std::vector<PartData_t>* getPartOverview(qint32 part_count);
    PartData_t* getPart(QString proprietary_id);
private:
    DbManager db_manager;
    std::vector<PartData_t> parts_overview;
    PartData_t part;
};

#endif // PDMMODEL_H
