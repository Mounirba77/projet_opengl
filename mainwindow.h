#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>  // Inclure QString pour gérer les chaînes de caractères
#include <QLabel>   // Inclure QLabel pour afficher les coordonnées

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT // Ajout de cette macro pour les signaux/slots

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateCoordinates(double x, double y, double z); // Slot pour mettre à jour les coordonnées

    // Déclaration des autres slots pour les sliders
    void on_verticalSlider_actionTriggered(int action);
    void on_verticalSlider_2_actionTriggered(int action);
    void on_verticalSlider_3_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
    QLabel *coordinatesLabel; // Un QLabel pour afficher les coordonnées

    // Variables pour stocker les coordonnées des sliders
    double xCoordinate, yCoordinate, zCoordinate;

    // Initial positions for sliders (assuming initial value is 0)
    int initialSliderValue;
};

#endif // MAINWINDOW_H
