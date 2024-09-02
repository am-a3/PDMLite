#include "PdmModel.h"

PdmModel::PdmModel()
    :db_manager("D:\\Projects\\PDMLite\\Src\\PDMLite\\pdm_db.sqlite3")
{

}

std::vector<PartData_t>* PdmModel::getPartOverview(qint32 part_count)
{
    parts_overview.clear();

    db_manager.queryAllParts(parts_overview, part_count);

    return &parts_overview;
}

PartData_t* PdmModel::getPart(QString proprietary_id)
{
    db_manager.queryPartByProprietaryId(proprietary_id, part);

    return &part;
}
