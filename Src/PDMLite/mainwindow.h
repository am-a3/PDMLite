#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PdmModel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    void ConfigureOverviewTable();
    void ConfigurePartParameterTable();
    PdmModel pdm_model;
};
#endif // MAINWINDOW_H
