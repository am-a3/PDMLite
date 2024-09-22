#ifndef PDMMODEL_H
#define PDMMODEL_H

#include "DataModels.h"
#include "DbManager.h"

typedef enum PdmState_t {
    PDM_IDLE = 0,
    PDM_ADD_NEW_PART,
    PDM_EDIT_EXISTING_PART,
    PDM_ADD_NEW_MANUFACTURING_DATA,
    PDM_EDIT_MANUFACTURING_DATA,
    PDM_ADD_NEW_BOM_ENTRY,
    PDM_EDIT_EXISTING_BOM_ENTRY
} PdmState_t;

class PdmModel
{
public:
    PdmModel();
    std::vector<Part>* getPartOverview(qint32 part_count);
    bool deletePart(QString proprietary_id);

    Part* setCurrentPart(QString proprietary_id);
    Part* createCurrentPart();
    Part* getCurrentPart();
    bool saveCurrentPart();

    PdmState_t getPdmState();
    void setPdmState(PdmState_t state);

    qint32 getPartOverviewEntryCount();

private:
    DbManager db_manager;
    std::vector<Part> parts_overview;
    Part current_part;
    PdmState_t pdm_state;

    bool checkPartNumberExists(QString proprietary_id);
};

#endif // PDMMODEL_H
