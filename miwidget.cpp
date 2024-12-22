#include "miwidget.h" // Inclusion de l'en-tête pour la classe miWidget

// Constructeur de la classe miWidget
miWidget::miWidget(QWidget *parent):QOpenGLWidget(parent)
{

}

// Méthode pour initialiser les fonctions OpenGL
void miWidget::initializeGL()
{
    initializeOpenGLFunctions(); // Initialiser les fonctions OpenGL nécessaires

    // glClearColor(0.0, 0.0, 0.0, 0.0); // Définir la couleur de fond de la fenêtre
    glEnable(GL_DEPTH_TEST); // Activer le test de profondeur pour le rendu 3D
}

// Méthode appelée lorsque la fenêtre est redimensionnée
void miWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h); // Définir la zone d'affichage OpenGL aux nouvelles dimensions

    // glMatrixMode(GL_PROJECTION); // Passer en mode projection
    // glLoadIdentity(); // Réinitialiser la matrice de projection

    // glOrtho(30.0, 30.0, 30.0, 30.0, 30.0, 30.0); // Définir une projection orthographique
}

// Méthode principale pour effectuer le rendu graphique
void miWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Effacer l'écran et le tampon de profondeur

    glEnable(GL_DEPTH_TEST); // Activer le test de profondeur pour gérer les objets en 3D

    glLoadIdentity(); // Réinitialiser la matrice de vue pour préparer le rendu

    glRotatef(rotate_x, 1.0, 0.0, 0.0); // Appliquer une rotation autour de l'axe X
    glRotatef(rotate_y, 0.0, 1.0, 0.0); // Appliquer une rotation autour de l'axe Y
    glRotatef(rotate_z, 0.0, 0.0, 1.0); // Appliquer une rotation autour de l'axe Z

    //l'utilisation de 0.7f au lieux de 0.7 est pour forcer c++ a considerer la parametre comme float non double,double est plus precis que float
    //mais float occupe 32bit alors que double occupe 64bit,dans cette classe j'ai utilisée float car ce projet va generer des forme 3d.
    renderCube(0.7f); // Appeler la méthode pour dessiner un cube
    // renderSphere(0.5f, 100, 100); // Appeler la méthode pour dessiner une sphère
    // render3DStar(0.8f, 0.4f, 5, 0.5f); // Appeler la méthode pour dessiner une étoile 3D
    graficarLineas(); // Dessiner les axes ou des lignes de référence

    glFlush(); // Forcer l'exécution immédiate des commandes OpenGL
    this->makeCurrent(); // Activer le contexte OpenGL actuel
}

// Méthode pour dessiner une sphère
//radious est le rayon du sphere
//Opengl utilise 2 parametre qui sont stacks et slices
//Stacks divise la sphère horizontalement (latitude) en cercles parallèles, contrôlant la lissage vertical.
//Slices divisent la sphère verticalement (longitude) en segments, contrôlant la lissage horizontal.
//pour ces 2 parametres une valeur de 100 peut donner une sphere qui est lisse
//et pour des valeur de 30-50 elle peut afficher une sphere qui est moins lisse,cela peut créer une difference dans la parite optimisation par example.
void miWidget::renderSphere(float radius, int stacks, int slices)
{
    for (int i = 0; i < stacks; ++i) { // Parcourir les niveaux de la sphère
        float lat0 = M_PI * (-0.5 + (float)(i) / stacks); // Calculer la latitude inférieure
        float z0 = radius * sin(lat0); // Calculer la coordonnée Z inférieure
        float zr0 = radius * cos(lat0); // Calculer le rayon à cette latitude

        float lat1 = M_PI * (-0.5 + (float)(i + 1) / stacks); // Calculer la latitude supérieure
        float z1 = radius * sin(lat1); // Calculer la coordonnée Z supérieure
        float zr1 = radius * cos(lat1); // Calculer le rayon à cette latitude

        glBegin(GL_QUAD_STRIP); // Début d'un bande de quadrilatères
        for (int j = 0; j <= slices; ++j) { // Parcourir les divisions longitudinales
            float lng = 2 * M_PI * (float)(j) / slices; // Calculer la longitude
            float x = cos(lng); // Calculer la coordonnée X
            float y = sin(lng); // Calculer la coordonnée Y

            glColor3f((x + 1) / 2, (y + 1) / 2, (z0 + 1) / 2); // Définir la couleur pour le sommet inférieur
            glVertex3f(x * zr0, y * zr0, z0); // Définir le sommet inférieur
            glColor3f((x + 1) / 2, (y + 1) / 2, (z1 + 1) / 2); // Définir la couleur pour le sommet supérieur
            glVertex3f(x * zr1, y * zr1, z1); // Définir le sommet supérieur
        }
        glEnd(); // Fin de la bande de quadrilatères
    }
}

// Méthode pour dessiner une étoile 3D
//outerRadious est le longeur du rayon maximale de l'etoile,innerRadius est le longeur minimale de l'etoile
//numpoints est le combre de sommet de l'etoile,middleHeight est la distance entre les 2 sommet de l'etoile sur l'axe des z
void miWidget::render3DStar(float outerRadius, float innerRadius, int numPoints, float middleHeight)
{
    glBegin(GL_TRIANGLES); // Début du mode dessin en triangles
    float angleStep = M_PI / numPoints; // Pas angulaire pour chaque segment de l'étoile

    for (int i = 0; i < numPoints * 2; ++i) { // Boucle sur tous les segments de l'étoile
        float angle1 = i * angleStep; // Angle du premier sommet
        float angle2 = (i + 1) * angleStep; // Angle du deuxième sommet

        float radius1 = (i % 2 == 0) ? outerRadius : innerRadius; // Rayon pour les sommets alternés
        float radius2 = ((i + 1) % 2 == 0) ? outerRadius : innerRadius;

        float x1 = radius1 * cos(angle1); // Calculer la coordonnée X du premier sommet
        float y1 = radius1 * sin(angle1); // Calculer la coordonnée Y du premier sommet
        float z1 = 0.0f; // Fixer la coordonnée Z du premier sommet

        float x2 = radius2 * cos(angle2); // Calculer la coordonnée X du deuxième sommet
        float y2 = radius2 * sin(angle2); // Calculer la coordonnée Y du deuxième sommet
        float z2 = 0.0f; // Fixer la coordonnée Z du deuxième sommet

        float xMiddlet = 0.0f, yMiddlet = 0.0f, zMiddlet = middleHeight / 2; // Position du sommet élevé
        float xMiddleb = 0.0f, yMiddleb = 0.0f, zMiddleb = -middleHeight / 2; // Position du sommet abaissé

        glColor3f((x1 + 1) / 2, (y1 + 1) / 2, 1.0); // Couleur pour le premier sommet
        glVertex3f(x1, y1, z1); // Définir le premier sommet
        glColor3f((x2 + 1) / 2, (y2 + 1) / 2, 1.0); // Couleur pour le deuxième sommet
        glVertex3f(x2, y2, z2); // Définir le deuxième sommet
        glColor3f(1.0, 1.0, 0.0); // Couleur pour le sommet central élevé
        glVertex3f(xMiddlet, yMiddlet, zMiddlet); // Définir le sommet central élevé

        glColor3f((x1 + 1) / 2, (y1 + 1) / 2, 1.0); // Couleur pour le premier sommet
        glVertex3f(x1, y1, z1); // Redéfinir le premier sommet
        glColor3f((x2 + 1) / 2, (y2 + 1) / 2, 1.0); // Couleur pour le deuxième sommet
        glVertex3f(x2, y2, z2); // Redéfinir le deuxième sommet
        glColor3f(1.0, 1.0, 0.0); // Couleur pour le sommet central abaissé
        glVertex3f(xMiddleb, yMiddleb, zMiddleb); // Définir le sommet central abaissé
    }
    glEnd(); // Fin du mode dessin en triangles
}

// Méthode pour dessiner un cube
// Le paramètre `size` représente la longueur d'un côté du cube
void miWidget::renderCube(float size)
{
    float halfSize = size / 2.0f; // Calculer la moitié de la taille pour simplifier les coordonnées des sommets
    glBegin(GL_QUADS); // Début du mode de dessin des quadrilatères (quatre sommets par face)

    // Face avant (z = halfSize)
    glColor3f(1.0, 0.0, 0.0); // Définir la couleur de la face avant en rouge
    glVertex3f(-halfSize, -halfSize, halfSize); // Coin inférieur gauche de la face avant
    glVertex3f(halfSize, -halfSize, halfSize); // Coin inférieur droit de la face avant
    glVertex3f(halfSize, halfSize, halfSize); // Coin supérieur droit de la face avant
    glVertex3f(-halfSize, halfSize, halfSize); // Coin supérieur gauche de la face avant

    // Face arrière (z = -halfSize)
    glColor3f(0.0, 1.0, 0.0); // Définir la couleur de la face arrière en vert
    glVertex3f(-halfSize, -halfSize, -halfSize); // Coin inférieur gauche de la face arrière
    glVertex3f(-halfSize, halfSize, -halfSize); // Coin supérieur gauche de la face arrière
    glVertex3f(halfSize, halfSize, -halfSize); // Coin supérieur droit de la face arrière
    glVertex3f(halfSize, -halfSize, -halfSize); // Coin inférieur droit de la face arrière

    // Face gauche (x = -halfSize)
    glColor3f(0.0, 0.0, 1.0); // Définir la couleur de la face gauche en bleu
    glVertex3f(-halfSize, -halfSize, -halfSize); // Coin inférieur arrière de la face gauche
    glVertex3f(-halfSize, -halfSize, halfSize); // Coin inférieur avant de la face gauche
    glVertex3f(-halfSize, halfSize, halfSize); // Coin supérieur avant de la face gauche
    glVertex3f(-halfSize, halfSize, -halfSize); // Coin supérieur arrière de la face gauche

    // Face droite (x = halfSize)
    glColor3f(1.0, 1.0, 0.0); // Définir la couleur de la face droite en jaune
    glVertex3f(halfSize, -halfSize, -halfSize); // Coin inférieur arrière de la face droite
    glVertex3f(halfSize, halfSize, -halfSize); // Coin supérieur arrière de la face droite
    glVertex3f(halfSize, halfSize, halfSize); // Coin supérieur avant de la face droite
    glVertex3f(halfSize, -halfSize, halfSize); // Coin inférieur avant de la face droite

    // Face supérieure (y = halfSize)
    glColor3f(0.0, 1.0, 1.0); // Définir la couleur de la face supérieure en cyan
    glVertex3f(-halfSize, halfSize, -halfSize); // Coin arrière gauche de la face supérieure
    glVertex3f(-halfSize, halfSize, halfSize); // Coin avant gauche de la face supérieure
    glVertex3f(halfSize, halfSize, halfSize); // Coin avant droit de la face supérieure
    glVertex3f(halfSize, halfSize, -halfSize); // Coin arrière droit de la face supérieure

    // Face inférieure (y = -halfSize)
    glColor3f(1.0, 0.0, 1.0); // Définir la couleur de la face inférieure en magenta
    glVertex3f(-halfSize, -halfSize, -halfSize); // Coin arrière gauche de la face inférieure
    glVertex3f(halfSize, -halfSize, -halfSize); // Coin arrière droit de la face inférieure
    glVertex3f(halfSize, -halfSize, halfSize); // Coin avant droit de la face inférieure
    glVertex3f(-halfSize, -halfSize, halfSize); // Coin avant gauche de la face inférieure

    glEnd(); // Terminer le mode de dessin des quadrilatères
}


// Méthode pour tracer des lignes représentant les axes
void miWidget::graficarLineas()
{
    glBegin(GL_LINES); // Début du mode dessin en lignes
    glColor3f(1,0,0); // Couleur rouge pour l'axe X
    glVertex3f(0,0,0); // Origine
    glVertex3f(20,0,0); // Extrémité de l'axe X

    glColor3f(1,1,0); // Couleur jaune pour l'axe Y
    glVertex3f(0,0,0); // Origine
    glVertex3f(0,20,0); // Extrémité de l'axe Y

    glColor3f(0,1,1); // Couleur cyan pour l'axe Z
    glVertex3f(0,0,0); // Origine
    glVertex3f(0,0,20); // Extrémité de l'axe Z

    glEnd(); // Fin du mode dessin en lignes
}
