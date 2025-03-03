
#include "GL/glut.h"													// Inclusion Bib. GLUT (OPENGL) //
#include "Missiles.h"													// Inclusion Fichier En-T�te 'Missiles.h' //

extern int PosXMissileJoueur;
extern int PosYMissileJoueur;											// Coordonn�es Missile Joueur et Alien issues du Source Principal //
extern int PosXMissileAlien;
extern int PosYMissileAlien;



void Missiles::DessinerMissileJoueur()
{

	glPushMatrix();														// On Sauvegarde la Matrice Active avant Translation //

	glTranslated(PosXMissileJoueur+0.5, PosYMissileJoueur+0.5, 0.0);	// On D�place le Missile Joueur par ses Coordonn�es //
	glColor3d(0.0, 0.0, 1.0);											// Couleur Bleue //
	glutWireCube(0.3);


	glPopMatrix();														// On Restaure la Matrice Active apr�s Translation //

}




void Missiles::DessinerMissileAlien()
{

	glPushMatrix();														// On Sauvegarde la Matrice Active avant Translation //

	glTranslated(PosXMissileAlien+0.5, PosYMissileAlien+0.5, 0.0);		// On D�place le Missile Alien par ses Coordonn�es //
	glColor3d(0.0, 1.0, 0.0);											// Couleur Verte //
	glutWireCube(0.3);


	glPopMatrix();														// On Restaure la Matrice Active apr�s Translation //

}