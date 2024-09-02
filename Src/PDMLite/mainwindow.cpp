#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QString>

#define OVERVIEW_TABLE_ENTRY_COUNT  10

typedef enum overview_table_columns {
    OVERVIEW_TABLE_PART_NUMBER_COLUMN = 0,
    OVERVIEW_TABLE_DESCRIPTION_COLUMN,
    OVERVIEW_TABLE_CATEGORY_COLUMN,
    OVERVIEW_TABLE_COLUMN_COUNT
} overview_table_columns;

typedef enum part_parameter_table_columns {
    PART_PARAM_TABLE_PART_NUMBER_COLUMN = 0,
    PART_PARAM_TABLE_DESCRIPTION_COLUMN,
    PART_PARAM_TABLE_CATEGORY_COLUMN,
    PART_PARAM_TABLE_COLUMN_COUNT
} part_parameter_table_columns;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pdm_model()
{
    ui->setupUi(this);

    ConfigureOverviewTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConfigureOverviewTable()
{
    std::vector<PartData_t>* part_overview_ptr = NULL;

    ui->overviewTable->setColumnCount(OVERVIEW_TABLE_COLUMN_COUNT);
    ui->overviewTable->setRowCount(OVERVIEW_TABLE_ENTRY_COUNT);
    ui->overviewTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->overviewTable->setHorizontalHeaderLabels({"Part number", "Description", "Category"});
    part_overview_ptr = pdm_model.getPartOverview(OVERVIEW_TABLE_ENTRY_COUNT);
    for (qint32 i = 0; i < part_overview_ptr->size(); i++)
    {
        ui->overviewTable->setItem(i, OVERVIEW_TABLE_PART_NUMBER_COLUMN, new QTableWidgetItem((*part_overview_ptr)[i].proprietary_id));
        ui->overviewTable->setItem(i, OVERVIEW_TABLE_DESCRIPTION_COLUMN, new QTableWidgetItem((*part_overview_ptr)[i].description));
        ui->overviewTable->setItem(i, OVERVIEW_TABLE_CATEGORY_COLUMN, new QTableWidgetItem((*part_overview_ptr)[i].category));
    }
}

void MainWindow::ConfigurePartParameterTable()
{
    ui->partParameterTable->setColumnCount(PART_PARAM_TABLE_COLUMN_COUNT);
}

void MainWindow::cellDoubleClicked(int row, int column)
{
    QTableWidgetItem* part_number;
    PartData_t* part;

    if (column == OVERVIEW_TABLE_PART_NUMBER_COLUMN) {
        part_number = ui->overviewTable->item(row, column);
        part = pdm_model.getPart(part_number->data(Qt::DisplayRole).toString());
    }
}
