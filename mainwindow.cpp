#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    xCoordinate(0), yCoordinate(0), zCoordinate(0),
    xTranslation(0), yTranslation(0), zTranslation(0),
    scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f)  // Initialize scale
{
    ui->setupUi(this);

    // Initialisation du QLabel pour afficher les coordonnées
    coordinatesLabel = ui->coordinatesLabel;  // Automatiquement lié par Qt Designer

    // Définir le texte initial du QLabel (coordonnées = (0, 0, 0))
    updateCoordinates(0, 0, 0);

    // Initialisation des positions des sliders (assumer la valeur 0 initialement)
    ui->rotationSliderX->setValue(0);         // Rotation X
    ui->rotationSliderY->setValue(0);       // Rotation Y
    ui->rotationSliderZ->setValue(0);       // Rotation Z
    ui->translationSliderX->setValue(0);     // Translation X
    ui->translationSliderY->setValue(0);     // Translation Y
    ui->translationSliderZ->setValue(0);     // Translation Z
    ui->scaleSliderX->setValue(0);         // Scale X (100% as default)
    ui->scaleSliderY->setValue(0);         // Scale Y
    ui->scaleSliderZ->setValue(0);         // Scale Z
    ui->translationSliderX->setRange(0,100);           // Slider range
    ui->translationSliderY->setRange(0,100);
    ui->translationSliderZ->setRange(0,100);
    //ui->translationSliderX->setSingleStep(0.01);          // Small increment step (via arrow keys)
    //ui->translationSliderX->setPageStep(0.1);

    // Connexions des signaux et des slots des sliders
    connect(ui->rotationSliderX, &QSlider::actionTriggered, this, &MainWindow::on_rotationSliderX_actionTriggered);
    connect(ui->rotationSliderY, &QSlider::actionTriggered, this, &MainWindow::on_rotationSliderY_actionTriggered);
    connect(ui->rotationSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_rotationSliderZ_actionTriggered);
    connect(ui->translationSliderX, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderX_actionTriggered);
    connect(ui->translationSliderY, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderY_actionTriggered);
    connect(ui->translationSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderZ_actionTriggered);
    connect(ui->scaleSliderX, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderX_actionTriggered);
    connect(ui->scaleSliderY, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderY_actionTriggered);
    connect(ui->scaleSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderZ_actionTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCoordinates(double x, double y, double z)
{
    // Mettre à jour le QLabel avec les coordonnées
    QString coordinatesText = QString("X: %1, Y: %2, Z: %3").arg(x).arg(y).arg(z);
    coordinatesLabel->setText(coordinatesText);  // Mettre à jour les coordonnées affichées
}

void MainWindow::on_rotationSliderX_actionTriggered(int action)
{
    // Mise à jour de la rotation X selon la valeur du slider
    ui->widget->rotate_x = ui->rotationSliderX->value();
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_rotationSliderY_actionTriggered(int action)
{
    // Mise à jour de la rotation Y selon la valeur du slider
    ui->widget->rotate_y = ui->rotationSliderY->value();
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_rotationSliderZ_actionTriggered(int action)
{
    // Mise à jour de la rotation Z selon la valeur du slider
    ui->widget->rotate_z = ui->rotationSliderZ->value();
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_translationSliderX_actionTriggered(int action)
{
    // Mise à jour de la translation X selon la valeur du slider
    xTranslation = ui->translationSliderX->value()/100.0;
    ui->widget->setTranslationX(xTranslation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
    updateCoordinates(xTranslation, yTranslation, zTranslation); // Mettre à jour les coordonnées dans le QLabel
}

void MainWindow::on_translationSliderY_actionTriggered(int action)
{
    // Mise à jour de la translation Y selon la valeur du slider
    yTranslation = ui->translationSliderY->value()/100.0;
    ui->widget->setTranslationY(yTranslation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
    updateCoordinates(xTranslation, yTranslation, zTranslation); // Mettre à jour les coordonnées dans le QLabel
}

void MainWindow::on_translationSliderZ_actionTriggered(int action)
{
    // Mise à jour de la translation Z selon la valeur du slider
    zTranslation = ui->translationSliderZ->value()/100.0;
    ui->widget->setTranslationZ(zTranslation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
    updateCoordinates(xTranslation, yTranslation, zTranslation); // Mettre à jour les coordonnées dans le QLabel
}

void MainWindow::on_scaleSliderX_actionTriggered(int action)
{
    // Mise à jour de l'échelle X selon la valeur du slider
    scaleX = ui->scaleSliderX->value() / 100.0f; // Convertir la valeur en facteur de mise à l'échelle
    ui->widget->setScaleX(scaleX); // Appliquer l'échelle au widget
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_scaleSliderY_actionTriggered(int action)
{
    // Mise à jour de l'échelle Y selon la valeur du slider
    scaleY = ui->scaleSliderY->value() / 100.0f; // Convertir la valeur en facteur de mise à l'échelle
    ui->widget->setScaleY(scaleY); // Appliquer l'échelle au widget
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_scaleSliderZ_actionTriggered(int action)
{
    // Mise à jour de l'échelle Z selon la valeur du slider
    scaleZ = ui->scaleSliderZ->value() / 100.0f; // Convertir la valeur en facteur de mise à l'échelle
    ui->widget->setScaleZ(scaleZ); // Appliquer l'échelle au widget
    ui->widget->update(); // Mettre à jour le widget
}
