
#include "GL/glut.h"													// Inclusion Bib. GLUT (OPENGL) //
#include "Missiles.h"													// Inclusion Fichier En-Tête 'Missiles.h' //

extern int PosXMissileJoueur;
extern int PosYMissileJoueur;											// Coordonnées Missile Joueur et Alien issues du Source Principal //
extern int PosXMissileAlien;
extern int PosYMissileAlien;



void Missiles::DessinerMissileJoueur()
{

	glPushMatrix();														// On Sauvegarde la Matrice Active avant Translation //

	glTranslated(PosXMissileJoueur+0.5, PosYMissileJoueur+0.5, 0.0);	// On Déplace le Missile Joueur par ses Coordonnées //
	glColor3d(0.0, 0.0, 1.0);											// Couleur Bleue //
	glutWireCube(0.3);


	glPopMatrix();														// On Restaure la Matrice Active après Translation //

}




void Missiles::DessinerMissileAlien()
{

	glPushMatrix();														// On Sauvegarde la Matrice Active avant Translation //

	glTranslated(PosXMissileAlien+0.5, PosYMissileAlien+0.5, 0.0);		// On Déplace le Missile Alien par ses Coordonnées //
	glColor3d(0.0, 1.0, 0.0);											// Couleur Verte //
	glutWireCube(0.3);


	glPopMatrix();														// On Restaure la Matrice Active après Translation //

}