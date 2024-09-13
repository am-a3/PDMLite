#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QString>
#include <QDateTime>

#define OVERVIEW_TABLE_ENTRY_COUNT      10

#define PART_PARAM_TABLE_PARAM_COLUMN   0
#define PART_PARAM_TABLE_VALUE_COLUMN   1

typedef enum overview_table_columns {
    OVERVIEW_TABLE_PART_NUMBER_COLUMN = 0,
    OVERVIEW_TABLE_DESCRIPTION_COLUMN,
    OVERVIEW_TABLE_CATEGORY_COLUMN,
    OVERVIEW_TABLE_COLUMN_COUNT
} overview_table_columns;

typedef enum part_parameter_table_rows {
    PART_PARAM_TABLE_PART_NUMBER_ROW = 0,
    PART_PARAM_TABLE_DESCRIPTION_ROW,
    PART_PARAM_TABLE_CATEGORY_ROW,
    PART_PARAM_TABLE_IS_SIMPLE_ROW,
    PART_PARAM_TABLE_CREATED_BY_ROW,
    PART_PARAM_TABLE_CREATED_DATE_ROW,
    PART_PARAM_TABLE_LAST_MODIFIED_BY_ROW,
    PART_PARAM_TABLE_LAST_MODIFIED_DATE_ROW,
    PART_PARAM_TABLE_ROW_COUNT
} part_parameter_table_rows;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pdm_model()
{
    ui->setupUi(this);

    ConfigureOverviewTable();
    ConfigurePartParameterTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConfigureOverviewTable()
{
    ui->overviewTable->setColumnCount(OVERVIEW_TABLE_COLUMN_COUNT);
    ui->overviewTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->overviewTable->setHorizontalHeaderLabels({"Part number", "Description", "Category"});
    ui->overviewTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    FillOverviewTable(OVERVIEW_TABLE_ENTRY_COUNT);
}

void MainWindow::FillOverviewTable(qint32 entry_number)
{
    std::vector<PartData_t>* part_overview_ptr = NULL;

    part_overview_ptr = pdm_model.getPartOverview(entry_number);
    ui->overviewTable->setRowCount(part_overview_ptr->size());
    for (qint32 i = 0; i < part_overview_ptr->size(); i++)
    {
        ui->overviewTable->setItem(i, OVERVIEW_TABLE_PART_NUMBER_COLUMN, new QTableWidgetItem((*part_overview_ptr)[i].proprietary_id));
        ui->overviewTable->setItem(i, OVERVIEW_TABLE_DESCRIPTION_COLUMN, new QTableWidgetItem((*part_overview_ptr)[i].description));
        ui->overviewTable->setItem(i, OVERVIEW_TABLE_CATEGORY_COLUMN, new QTableWidgetItem((*part_overview_ptr)[i].category));
    }
}

void MainWindow::ConfigurePartParameterTable()
{
    QTableWidgetItem* item = NULL;

    ui->partParameterTable->setColumnCount(2); // parameter and value
    ui->partParameterTable->setRowCount(PART_PARAM_TABLE_ROW_COUNT);
    ui->partParameterTable->setHorizontalHeaderLabels({"Parameter", "Value"});
    ui->partParameterTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    item = new QTableWidgetItem("Part number");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_PART_NUMBER_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("Description");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_DESCRIPTION_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("Category");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CATEGORY_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("Simple part");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_IS_SIMPLE_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("Created by");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CREATED_BY_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("Created date");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CREATED_DATE_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("Last modified by");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_LAST_MODIFIED_BY_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("Last modified date");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_LAST_MODIFIED_DATE_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
}

void MainWindow::ClearPartParameterTable()
{
    ui->partParameterTable->blockSignals(true);

    ui->partParameterTable->setItem(PART_PARAM_TABLE_PART_NUMBER_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(""));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_DESCRIPTION_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(""));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CATEGORY_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(""));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_IS_SIMPLE_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(""));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CREATED_BY_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(""));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CREATED_DATE_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(""));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_LAST_MODIFIED_BY_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(""));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_LAST_MODIFIED_DATE_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(""));

    ui->partParameterTable->blockSignals(false);
}

bool MainWindow::FillPartParameterTable(PartData_t* part)
{
    if (part == NULL) {
        return false;
    }

    ui->partParameterTable->blockSignals(true);

    ui->partParameterTable->setItem(PART_PARAM_TABLE_PART_NUMBER_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(part->proprietary_id));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_DESCRIPTION_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(part->description));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CATEGORY_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(part->category));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_IS_SIMPLE_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(QString::number(part->is_simple)));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CREATED_BY_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(part->created_by));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CREATED_DATE_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(part->created_datetime.toString()));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_LAST_MODIFIED_BY_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(part->last_modified_by));
    ui->partParameterTable->setItem(PART_PARAM_TABLE_LAST_MODIFIED_DATE_ROW, PART_PARAM_TABLE_VALUE_COLUMN, new QTableWidgetItem(part->last_modified_datetime.toString()));

    ui->partParameterTable->blockSignals(false);

    return true;
}

void MainWindow::RefreshPartView()
{
    FillOverviewTable(OVERVIEW_TABLE_ENTRY_COUNT);
}

void MainWindow::cellClickedOverviewTable(int row, int column)
{
    QTableWidgetItem* part_number;
    PartData_t* part;

    ui->savePartButton->setEnabled(false);

    auto row_count = ui->overviewTable->rowCount();

    if ((pdm_model.getPdmState() == PDM_ADD_NEW_PART) && row != (row_count - 1))
    {
        ui->overviewTable->removeRow(row_count - 1);

        ui->addPartButton->setEnabled(true);
        ui->deletePartButton->setEnabled(true);

        pdm_model.setPdmState(PDM_IDLE);
    }

    part_number = ui->overviewTable->item(row, OVERVIEW_TABLE_PART_NUMBER_COLUMN);

    if (part_number != NULL) {
        part = pdm_model.setCurrentPart(part_number->data(Qt::DisplayRole).toString());

        if (!FillPartParameterTable(part)) {
            ClearPartParameterTable();
        }
     }
    else
    {
        ClearPartParameterTable();
    }
}

void MainWindow::cellChangedParameterTable(int row, int column)
{
    PartData_t* part;
    QTableWidgetItem* parameter;

    if (column == PART_PARAM_TABLE_VALUE_COLUMN)
    {
        qDebug() << "Row: " << row << " value updated.";

        ui->savePartButton->setEnabled(true);

        part = pdm_model.getCurrentPart();

        parameter = ui->partParameterTable->item(row, column);

        switch (row)
        {
            case PART_PARAM_TABLE_PART_NUMBER_ROW:
                part->proprietary_id = parameter->text();
                break;
            case PART_PARAM_TABLE_DESCRIPTION_ROW:
                part->description = parameter->text();
                break;
            case PART_PARAM_TABLE_CATEGORY_ROW:
                part->category = parameter->text();
                break;
            case PART_PARAM_TABLE_IS_SIMPLE_ROW:
                part->is_simple = parameter->text().toInt();
                break;
            case PART_PARAM_TABLE_CREATED_BY_ROW:
                part->created_by = parameter->text();
                break;
            case PART_PARAM_TABLE_CREATED_DATE_ROW:
                part->created_datetime = QDateTime::fromString(parameter->text(), Qt::ISODate);
                break;
            case PART_PARAM_TABLE_LAST_MODIFIED_BY_ROW:
                part->last_modified_by = parameter->text();
                break;
            case PART_PARAM_TABLE_LAST_MODIFIED_DATE_ROW:
                part->last_modified_datetime = QDateTime::fromString(parameter->text(), Qt::ISODate);
                break;
        }
    }
}

void MainWindow::addPartButtonClicked()
{
    auto row_count = ui->overviewTable->rowCount();

    if (pdm_model.getPdmState() != PDM_ADD_NEW_PART)
    {
        pdm_model.setPdmState(PDM_ADD_NEW_PART);

        ui->overviewTable->setRowCount(row_count + 1);
        emit ui->overviewTable->cellClicked(row_count, 0);
        ui->overviewTable->selectRow(row_count);

        ui->addPartButton->setEnabled(false);
        ui->deletePartButton->setEnabled(false);
    }
}

void MainWindow::savePartButtonClicked()
{
        pdm_model.saveCurrentPart();
        ui->savePartButton->setEnabled(false);
        RefreshPartView();

        if (pdm_model.getPdmState() == PDM_ADD_NEW_PART)
        {
            pdm_model.setPdmState(PDM_EDIT_EXISTING_PART);

            ui->addPartButton->setEnabled(true);
            ui->deletePartButton->setEnabled(true);
        }
}
