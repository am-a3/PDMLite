#include "PdmModel.h"

PdmModel::PdmModel()
    :db_manager("D:\\Projects\\PDMLite\\Src\\PDMLite\\pdm_db.sqlite3")
{
    pdm_state = PDM_IDLE;
}

std::vector<PartData_t>* PdmModel::getPartOverview(qint32 part_count)
{
    parts_overview.clear();

    db_manager.queryAllParts(parts_overview, part_count);

    return &parts_overview;
}

PartData_t* PdmModel::setCurrentPart(QString proprietary_id)
{
    if (db_manager.queryPartByProprietaryId(proprietary_id, current_part.part))
    {
        current_part.is_updated = false;
        return &current_part.part;
    }

    return NULL;
}

PartData_t* PdmModel::createCurrentPart()
{
    current_part = {};

    current_part.is_updated = false;
    return &current_part.part;
}

PartData_t* PdmModel::getCurrentPart()
{
    return &current_part.part;
}

bool PdmModel::saveCurrentPart()
{
    bool success = false;

    qDebug() << "Save current part";
    success = db_manager.updatePart(current_part.part);

    if (success) current_part.is_updated = false;

    return success;
}

void PdmModel::setCurrentPartUpdated()
{
    current_part.is_updated = true;
}

PdmState_t PdmModel::getPdmState()
{
    return pdm_state;
}

void PdmModel::setPdmState(PdmState_t state)
{
    pdm_state = state;
}
