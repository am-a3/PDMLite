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

typedef struct current_part_t {
    bool is_updated;
    PartData_t part;
} current_part_t;

class PdmModel
{
public:
    PdmModel();
    std::vector<PartData_t>* getPartOverview(qint32 part_count);

    PartData_t* setCurrentPart(QString proprietary_id);
    PartData_t* createCurrentPart();
    PartData_t* getCurrentPart();
    bool saveCurrentPart();
    void setCurrentPartUpdated();

    PdmState_t getPdmState();
    void setPdmState(PdmState_t state);

private:
    DbManager db_manager;
    std::vector<PartData_t> parts_overview;
    current_part_t current_part;
    PdmState_t pdm_state;
};

#endif // PDMMODEL_H
