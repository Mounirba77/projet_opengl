#ifndef MIWIDGET_H
#define MIWIDGET_H

#include <QOpenGLFramebufferObject> // Inclusion pour gérer les Framebuffer OpenGL
#include <QOpenGLWidget>           // Inclusion pour utiliser un widget OpenGL
#include <QOpenGLFunctions>        // Inclusion pour les fonctions OpenGL
#include <cmath>                   // Inclusion pour les fonctions mathématiques comme sin et cos

// Déclaration de la classe miWidget héritant de QOpenGLWidget
// et intégrant les fonctions OpenGL (QOpenGLFunctions)
class miWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:

    // Constructeur explicite de la classe, avec un paramètre parent optionnel
    explicit miWidget(QWidget *parent = 0);

protected:
    // Méthode pour initialiser le contexte OpenGL
    void initializeGL() Q_DECL_OVERRIDE;

    // Méthode appelée lors du redimensionnement de la fenêtre
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    // Méthode principale pour effectuer le rendu graphique
    void paintGL() Q_DECL_OVERRIDE;

    // Méthode pour dessiner des lignes (comme les axes de référence)
    void graficarLineas();

    // Méthode pour dessiner une sphère
    void renderSphere(float radius, int stacks, int slices);

    // Méthode pour dessiner une étoile 3D
    void render3DStar(float outerRadius, float innerRadius, int numPoints, float depth);

    // Méthode pour dessiner un cube
    void renderCube(float size);

public:
    // Variables publiques pour gérer les angles de rotation sur les axes
    double rotate_y = 0; // Rotation autour de l'axe Y
    double rotate_x = 0; // Rotation autour de l'axe X
    double rotate_z = 0; // Rotation autour de l'axe Z

private:
         // Les membres privés sont définis ici si nécessaire
};

#endif // MIWIDGET_H
