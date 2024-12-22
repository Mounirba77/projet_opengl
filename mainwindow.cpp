#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    xCoordinate(0), yCoordinate(0), zCoordinate(0), initialSliderValue(0)
{
    ui->setupUi(this);

    // Accessing the QLabel from the UI file to display coordinates
    coordinatesLabel = ui->coordinatesLabel;  // Automatically set by Qt Designer

    // Set the initial text for the QLabel (coordinates = (0, 0, 0))
    updateCoordinates(0, 0, 0);

    // Initializing slider positions (set to 0 initially)
    ui->verticalSlider->setValue(0);
    ui->verticalSlider_2->setValue(0);
    ui->verticalSlider_3->setValue(0);

    // Connexions des signaux et des slots des sliders
    connect(ui->verticalSlider, &QSlider::actionTriggered, this, &MainWindow::on_verticalSlider_actionTriggered);
    connect(ui->verticalSlider_2, &QSlider::actionTriggered, this, &MainWindow::on_verticalSlider_2_actionTriggered);
    connect(ui->verticalSlider_3, &QSlider::actionTriggered, this, &MainWindow::on_verticalSlider_3_actionTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCoordinates(double x, double y, double z)
{
    // Mettre à jour le QLabel avec les coordonnées
    QString coordinatesText = QString("X: %1, Y: %2, Z: %3").arg(x).arg(y).arg(z);
    coordinatesLabel->setText(coordinatesText);  // Set the new text to the label
}

void MainWindow::on_verticalSlider_actionTriggered(int action)
{
    // Update X coordinate based on the slider value
    xCoordinate = ui->verticalSlider->value();
    ui->widget->rotate_x = xCoordinate;
    ui->widget->update(); // Update the widget
    updateCoordinates(xCoordinate, yCoordinate, zCoordinate); // Update coordinates on QLabel

    // Check if all sliders are at 0 and reset if true
    if (ui->verticalSlider->value() == initialSliderValue &&
        ui->verticalSlider_2->value() == initialSliderValue &&
        ui->verticalSlider_3->value() == initialSliderValue) {
        updateCoordinates(0, 0, 0);  // Reset coordinates to (0, 0, 0)
    }
}

void MainWindow::on_verticalSlider_2_actionTriggered(int action)
{
    // Update Y coordinate based on the slider value
    yCoordinate = ui->verticalSlider_2->value();
    ui->widget->rotate_y = yCoordinate;
    ui->widget->update(); // Update the widget
    updateCoordinates(xCoordinate, yCoordinate, zCoordinate); // Update coordinates on QLabel

    // Check if all sliders are at 0 and reset if true
    if (ui->verticalSlider->value() == initialSliderValue &&
        ui->verticalSlider_2->value() == initialSliderValue &&
        ui->verticalSlider_3->value() == initialSliderValue) {
        updateCoordinates(0, 0, 0);  // Reset coordinates to (0, 0, 0)
    }
}

void MainWindow::on_verticalSlider_3_actionTriggered(int action)
{
    // Update Z coordinate based on the slider value
    zCoordinate = ui->verticalSlider_3->value();
    ui->widget->rotate_z = zCoordinate;
    ui->widget->update(); // Update the widget
    updateCoordinates(xCoordinate, yCoordinate, zCoordinate); // Update coordinates on QLabel

    // Check if all sliders are at 0 and reset if true
    if (ui->verticalSlider->value() == initialSliderValue &&
        ui->verticalSlider_2->value() == initialSliderValue &&
        ui->verticalSlider_3->value() == initialSliderValue) {
        updateCoordinates(0, 0, 0);  // Reset coordinates to (0, 0, 0)
    }
}
