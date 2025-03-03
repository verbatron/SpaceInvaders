																		// *** Jeu Space Invaders *** //
																		//      C++ Natif (OPENGL)    //
																		//         En Pixel Art		  //
																		//           Mai 2024		  //
																		////////////////////////////////



#include <string>														// Pour Affichage des Textes //
#include <cstdbool>														// Pour Booléens //
#include <cstdio>														// Bib. Standard E/S C //
#include <cstdlib>														// Idem //
#include <Ctime>														// Pour Fonction rand() //
#include <Windows.h>													// Pour Masquer la Fenêtre Console //
#include <fstream>														// Inclusion Pour les Fichiers externes //
#include "Missiles.h"													// Inclusion Fichier En-Tête 'Missiles.h' //
#include "GL/freeglut.h"
#include "GL/freeglut_ext.h"
#include "GL/freeglut_std.h"
#include "GL/glut.h"													// Inclusion Bib. GLUT (OPENGL) //



using namespace std;													// Inclusion Espace de Noms Standard //



bool DepartJeu = false;													// Variable booléenne Depart du Jeu //
bool ValidFin = false;													// Variable booléenne Validation Fin Jeu //
bool ValidDeplacMissileAlien = false;									// Variable booléenne Validation Creation Missile Alien //
bool ValidDeplacMissileJoueur = false;									// Variable booléenne Validation Déplacement Missile Joueur //
bool ValidAffJoueur = true;												// Variable booléenne Validation Affichage Joueur //
bool ValidAffMissileJoueur = false;										// Variable booléenne Validation Affichage Missile Joueur //
bool ValidAffMissileAlien = false;										// Variable booléenne Validation Affichage Missile Alien //
bool ValidAffExplosion = false;											// Variable booléenne Validation Affichage Explosion //
unsigned short int NombreAliensRestant = 40;							// Variable Nombre Aliens Restant a Eliminer (40 au Départ) //
char** Matrice;															// Tableau a 2 Dimensions alloué par des Pointeurs dans le TAS //
int NbColonnes = 17;													// Variable Nombre de Colonnes dans Tableau //
int NbLignes = 34;														// Variable Nombre de Lignes dans Tableau //
const int TimerMillisEtoiles = 500;										// Variable Valeur Temps entre 2 Evenements Timer Etoiles //
const int TimerMillisMissileAlien = 50;									// Variable Valeur Temps entre 2 Evenements Timer Missile Alien //
const int TimerMillisMissileJoueur = 50;								// Variable Valeur Temps entre 2 Evenements Timer Missile Joueur //
const int TimerMillisCreationMissileAlien = 1500;						// Variable Valeur Temps entre 2 Evenements Timer Création Missile Alien //
const int TimerMillisFinExplosion = 5000;								// Variable Valeur Temps entre 2 Evenements Timer Fin Explosion //


int PosXJoueur = 8;														//					
int PosYJoueur = 32;													//
int PosXMissileJoueur = PosXJoueur;										// 
int PosYMissileJoueur = PosYJoueur - 1;									//
int PosXAlien;															//
int PosYAlien;															//  
int PosXMissileAlien;													//  Variables Coordonnées des Différents Elements de la Scène //
int PosYMissileAlien;													//
int PosXEtoiles;														//
int PosYEtoiles;														//
int PosXExplosion;														//
int PosYExplosion;														//


// DESSIN PRIMITIVE GL BITMAP JOUEUR (48 Pixels de Large et 24 Pixels de Haut) //


GLubyte Joueur[144] = { 0x01,0xFF,0xFF,0xFF,0xFF,0x80,					// 000000011111111111111111111111111111111110000000 //
0x02,0x40,0x00,0x00,0x02,0x40,											// 000000100100000000000000000000000000001001000000 //
0x04,0x40,0x00,0x00,0x02,0x20,											// 000001000100000000000000000000000000001000100000 //
0x08,0x40,0x00,0x00,0x02,0x10,										    // 000010000100000000000000000000000000001000010000 //
0x10,0x40,0x00,0x00,0x02,0x08,									        // 000100000100000000000000000000000000001000001000 //
0x20,0x40,0x00,0x00,0x02,0x04,									        // 001000000100000000000000000000000000001000000100 //
0x40,0x40,0x00,0x00,0x02,0x02,									        // 010000000100000000000000000000000000001000000010 //
0x80,0x40,0x00,0x00,0x02,0x01,									        // 100000000100000000000000000000000000001000000001 //
0x40,0x40,0x00,0x00,0x02,0x02,									        // 010000000100000000000000000000000000001000000010 //
0x20,0x40,0x00,0x00,0x02,0x04,									        // 001000000100000000000000000000000000001000000100 //
0x10,0x40,0x00,0x00,0x02,0x08,					                        // 000100000100000000000000000000000000001000001000 //
0x08,0x40,0x00,0x00,0x02,0x10,					                        // 000010000100000000000000000000000000001000010000 //
0x04,0x40,0x00,0x00,0x02,0x20,					                        // 000001000100000000000000000000000000001000100000 //
0x02,0x40,0x00,0x00,0x02,0x40,					                        // 000000100100000000000000000000000000001001000000 // 
0x01,0xFF,0xFF,0xFF,0xFF,0x80,					                        // 000000011111111111111111111111111111111110000000 //
0x00,0x01,0x00,0x01,0x00,0x00,					                        // 000000000000000100000000000000010000000000000000 //
0x00,0x00,0x80,0x02,0x00,0x00,					                        // 000000000000000010000000000000100000000000000000 //
0x00,0x00,0x40,0x04,0x00,0x00,					                        // 000000000000000001000000000001000000000000000000 //
0x00,0x00,0x20,0x08,0x00,0x00,					                        // 000000000000000000100000000010000000000000000000 //
0x00,0x00,0x10,0x10,0x00,0x00,					                        // 000000000000000000010000000100000000000000000000 //
0x00,0x00,0x08,0x20,0x00,0x00,					                        // 000000000000000000001000001000000000000000000000 //
0x00,0x00,0x04,0x40,0x00,0x00,					                        // 000000000000000000000100010000000000000000000000 //
0x00,0x00,0x02,0x80,0x00,0x00,					                        // 000000000000000000000010100000000000000000000000 //
0x00,0x00,0x01,0x00,0x00,0x00 };				                        // 000000000000000000000001000000000000000000000000 //



// DESSIN PRIMITIVE GL BITMAP ALIEN (48 Pixels de Large et 24 Pixels de Haut) //


GLubyte Alien[144] = { 0x00,0x0F,0xFF,0xFF,0xF0,0x00,					// 000000000000111111111111111111111111000000000000 //
0x00,0x10,0x00,0x00,0x08,0x00,											// 000000000001000000000000000000000000100000000000 //
0x00,0x20,0x00,0x00,0x04,0x00,											// 000000000010000000000000000000000000010000000000 //
0x00,0x40,0x00,0x00,0x02,0x00,											// 000000000100000000000000000000000000001000000000 //
0x00,0x80,0x00,0x00,0x01,0x00,											// 000000001000000000000000000000000000000100000000 //
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,											// 111111111111111111111111111111111111111111111111 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0x80,0x00,0x00,0x00,0x00,0x01,											// 100000000000000000000000000000000000000000000001 //
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,											// 111111111111111111111111111111111111111111111111 //
0x00,0x80,0x00,0x00,0x01,0x00,											// 000000001000000000000000000000000000000100000000 //
0x00,0x40,0x00,0x00,0x02,0x00,											// 000000000100000000000000000000000000001000000000 //
0x00,0x20,0x00,0x00,0x04,0x00,											// 000000000010000000000000000000000000010000000000 //
0x00,0x10,0x00,0x00,0x08,0x00,											// 000000000001000000000000000000000000100000000000 //
0x00,0x0F,0xFF,0xFF,0xF0,0x00 };										// 000000000000111111111111111111111111000000000000 //


Missiles LeMissileJoueur;
Missiles LeMissileAlien;												// Objets Globaux de la Classe Missiles //


void Init();															// Déclaration Fonction Initialisation Primitives GL BITMAP //
void OuvrirNiveau(char nom_fichier[]);									// Déclaration Fonction Ouverture Fichier Externe (En Lecture) pour Récupérer Données //
void SceneAff();														// Déclaration Fonction Affichage Scène du Jeu //
void SceneRedim(int x, int y);											// Déclaration Fonction Redimensionnement Fenêtre OPENGL //
void SceneClavierSpecial(int key, int x, int y);						// Déclaration Fonction Gestion Clavier //
void DeplacGauche();													// Déclaration Fonction Gestion Déplacement à Gauche du Joueur (et Missile Joueur sans Tir) //
void DeplacDroite();													// Déclaration Fonction Gestion Déplacement à Droite du Joueur (et Missile Joueur sans Tir) //
void DessinerJoueur();													// Déclaration Fonction Affichage Joueur //
void DessinerMissileJoueur();											// Déclaration Fonction Affichage Missile Joueur //
void DessinerMissileAlien();											// Déclaration Fonction Affichage Missile Alien //
void DessinerExplosion();												// Déclaration Fonction Affichage Explosion //
void TimerEtoiles(int value);											// Déclaration Fonction Timer Déplacement Etoiles //
void TimerCreationMissileAlien(int value);								// Déclaration Fonction Timer Création Missiles Alien //
void TimerMissileAlien(int value);										// Déclaration Fonction Timer Déplacement Missile Alien //
void TimerMissileJoueur(int value);										// Déclaration Fonction Timer Déplacement Missile Joueur //
void TimerFinExplosion(int value);										// Déclaration Fonction Timer Fin Explosion //
void GestionMissileJoueur();											// Déclaration Fonction Gestion Missile Joueur //
void GestionMissileAlien();												// Déclaration Fonction Gestion Missile Alien  //
void LibererMemoire();													// Déclaration Fonction Gestion Libération TAS //
void AffTexteVictoire();												// Déclaration Fonction Affichage Texte 'VICTOIRE' //
void AffTexteDefaite();													// Déclaration Fonction Affichage Texte 'DEFAITE' //



int main(int argc, char** argv)											// Fonction Principale du Programme (avec Initialisation) //
{

	srand((int)time(NULL));												// Amorçage du Pseudo Aléatoire dans le main() //

	FreeConsole();														// On Masque la Fenêtre Console au Départ //

	glutInit(&argc, argv);												// Fonction Initialisation GLUT //
	glutInitWindowPosition(552, 192);									// Fonction GLUT Position Fenêtre OPENGL à l'écran //
	glutInitWindowSize(816, 816);										// Fonction GLUT Taille Fenêtre OPENGL d'origine //
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);						// Fonction GLUT Mode Couleurs RVB & Double Tampon affichage //
	glutCreateWindow("Space Invaders");									// Fonction GLUT Creation Fenêtre OPENGL avec son titre //
	Init();																// Fonction Initialisation Primitives GL BITMAP //
	glutDisplayFunc(SceneAff);											// Fonction GLUT Affichage Scène //
	glutReshapeFunc(SceneRedim);										// Fonction GLUT Redimensionnement Fenêtre OPENGL //
	glutSpecialFunc(SceneClavierSpecial);								// Fonction GLUT Gestion Clavier //
	glutTimerFunc(TimerMillisEtoiles, TimerEtoiles, 0);					// Fonction GLUT Timer Gestion Etoiles //
	glutTimerFunc(TimerMillisCreationMissileAlien, TimerCreationMissileAlien, 1); // Fonction GLUT Timer Création Missile Alien //
	glutTimerFunc(TimerMillisMissileAlien, TimerMissileAlien, 2);		// Fonction GLUT Timer Gestion Missile Alien //
	glutTimerFunc(TimerMillisMissileJoueur, TimerMissileJoueur, 3);		// Fonction GLUT Timer Gestion Missile Joueur //
	glutTimerFunc(TimerMillisFinExplosion, TimerFinExplosion, 4);		// Fonction GLUT Timer Gestion Fin Explosion //



	char nom_fichier[] = { "Datas\\niveau.txt" };						// Ouverture Fichier Externe dans le main() //
	OuvrirNiveau(nom_fichier);											//


	glutMainLoop();														// Fonction GLUT Boucle Principale du main() //

	return 0;															// Return de la Fonction main() avec Renvoi de la Valeur 0 à L'OS //


}



void Init()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);								// Fonction GLUT Initialisation Bitmaps //
}



void SceneAff()
{

	glClearColor(0.0, 0.0, 0.0, 1.0);									// Couleur Noire pour le Fond //
	glClear(GL_COLOR_BUFFER_BIT);										// On Efface le Tampon Affichage Couleur //
	glMatrixMode(GL_MODELVIEW);											// Matrice active Vue de Modèles //


	for (int i = 0; i < 30; i++)										// Pour 30 Etoiles //

	{

		PosXEtoiles = (rand() % 15) +1;									// Positions en X et Y aléatoire dans la Scene //
		PosYEtoiles = (rand() % 32) +1;

		glPushMatrix();													// On Sauvegarde la Matrice avant Translation //
		glTranslated(PosXEtoiles, PosYEtoiles, 0.0);					// On Positionne chaque Etoile selon ses Coordonnées //
		glColor3d(1.0,1.0,1.0);											// Etoiles Blanches //
		glutSolidSphere(0.05, 12, 12);									// On Crée Chaque Etoile //
		glPopMatrix();													// On Restaure la Matrice après Translation //

	}

	DessinerJoueur();													// On Dessine le Joueur (Si Validation Affichage) //

	DessinerMissileJoueur();											// On Dessine le Missile Joueur (Si Validation Affichage) //

	DessinerMissileAlien();												// On Dessine le Missile Alien (Si Validation Affichage) //

	DessinerExplosion();												// On Dessine l'explosion (Si Validation Affichage) //

	for (int i = 0; i < NbColonnes; i++)
		for (int j = 0; j < NbLignes; j++)
		{
			switch (Matrice[i][j])										// On Commute sur le Tableau //
			{

			case '1':													// Cas Alien //
			{
				PosXAlien = i;											// On Affecte les Coordonnées a cet Endroit là //
				PosYAlien = j;
				glColor3f(0.0, 1.0, 0.0);
				glRasterPos2i(PosXAlien, PosYAlien);					// On Dessine la Primitive Bitmap Alien Verte déplaçable selon les Coordonnées en X et Y //
				glBitmap(48, 24, 0.0, 0.0, 0.0, 0.0, Alien);
				break;
			}


			}

		}

	GestionMissileJoueur();												// On Execute la Fonction Gestion Missile Joueur //

	GestionMissileAlien();												// On Execute la Fonction Gestion Missile Alien //

	glutSwapBuffers();

}



void DessinerJoueur()
{

	if (ValidAffJoueur)													// Si l'affichage du Joueur est Validé //
	{
		glColor3f(0.0, 0.0, 1.0);
		glRasterPos2i(PosXJoueur, PosYJoueur);							// On Dessine la Primitive Bitmap Joueur Bleu déplaçable selon les Coordonnées en X et Y //
		glBitmap(48, 24, 0.0, 0.0, 0.0, 0.0, Joueur);
	}


}



void DessinerMissileJoueur()
{

	if (ValidAffMissileJoueur)											// Si l'affichage du Missile Joueur est Validé //
	{
		LeMissileJoueur.DessinerMissileJoueur();						// On Dessine le Missile Joueur //
	}


}



void DessinerMissileAlien()
{

	if (ValidAffMissileAlien)											// Si l'affichage du Missile Alien est Validé //
	{
		LeMissileAlien.DessinerMissileAlien();							// On Dessine le Missile Alien //
	}


}


void DessinerExplosion()
{

	if (ValidAffExplosion)												// Si l'affichage de l'explosion est validé //
	{
		glPushMatrix();													// On Sauvegarde la Matrice Active avant Translation //
		glTranslated(PosXExplosion+0.5, PosYExplosion-0.5, 0.0);		// On Positionne l'explosion par ses Coordonnées en X et Y //
		glColor3d(1.0, 1.0, 0.0);										// Couleur Jaune //
		glutSolidSphere(1, 12, 12);										// Dessin de l'explosion //
		glPopMatrix();													// On Restaure la Matrice Active après Translation //
	}


}



void SceneRedim(int x, int y)
{

	glViewport(0, 0, x, y);												// Fonction ViewPort (perspective) //
	glMatrixMode(GL_PROJECTION);										// Matrice de Projection //
	glLoadIdentity();													// On charge Identité Matrice //
	gluOrtho2D(0.0, (double)NbColonnes, (double)NbLignes, 0.0);			// Fonction de redimensionnement GLUT //




}



void OuvrirNiveau(char nom_fichier[])
{

	ifstream fichier;													// On lance la Gestion Fichier //
	fichier.open(nom_fichier);											// On ouvre le Fichier //

	fichier >> NbColonnes;												// On récupère le Nombre de Colonnes et de Lignes //
	fichier >> NbLignes;

	Matrice = new char* [NbColonnes];
	for (int i = 0; i < NbColonnes; i++)
		// Allocation en Espace Mémoire adressable (TAS) de la Matrice avec des Pointeurs //
	{
		Matrice[i] = new char[NbLignes];
	}

	for (int i = 0; i < NbColonnes; i++)
		for (int j = 0; j < NbLignes; j++)
		{
			Matrice[i][j] = '0';										// On initialise le Contenu à 0 //
		}


	for (int j = 0; j < NbLignes; j++)
		for (int i = 0; i < NbColonnes; i++)

		{
			fichier >> Matrice[i][j];									// On récupère le Contenu de chaque Colonne et Lignes à partir du Fichier pour la Matrice //
		}


	for (int i = 0; i < NbColonnes; i++)
		for (int j = 0; j < NbLignes; j++)
		{
			switch (Matrice[i][j])										// On Commute sur le Tableau //
			{

			case 'j':													// Cas Joueur //
			{
				PosXJoueur = i;											// On Affecte les Coordonnées a cet Endroit là //
				PosYJoueur = j;
				break;
			}


			}

		}

	fichier.close();													// Fermeture du Fichier Externe a la Fin de la Récupération Données //
}



void LibererMemoire()
{

	for (int i = 0; i < NbColonnes; i++)								// On Va Supprimer la Matrice Alloué en Mémoire // 

		delete[] Matrice[i];
			delete[] Matrice;											// De Manière Manuelle avec Instruction delete //




}



void SceneClavierSpecial(int key, int x, int y)
{

	switch (key)														// On Commute sur la Touche Appuyée //
	{

	case GLUT_KEY_F1:													// Appui sur 'F1' //
	{
		DepartJeu = true;												// Validation Démarrage du Jeu //
		ValidFin = false;
		break;
	}

	case GLUT_KEY_F4:													// Appui sur 'F4' //
	{
		ValidAffMissileJoueur = true;									// On Valide l'affichage Missile Joueur //
		ValidDeplacMissileJoueur = true;								// On Valide le Déplacement Missile Joueur //
		PlaySound(TEXT("Datas\\Tir.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son de Tir //
		break;
	}

	case GLUT_KEY_F10:													// Appui sur 'F10' //
	{
		LibererMemoire();												// On Libère le TAS //
		exit(0);														// On Quitte le Jeu en Renvoyant la Valeur '0' à WINDOWS //
		break;
	}

	case GLUT_KEY_LEFT:													// Appui sur 'GAUCHE' //
	{
		DeplacGauche();													// On Execute la Fonction de Déplacement à Gauche //
		break;
	}

	case GLUT_KEY_RIGHT:												// Appui sur 'DROITE' //
	{
		DeplacDroite();													// On Execute la Fonction de Déplacement à Droite //
		break;
	}


	}


}



void DeplacGauche()
{

	if (DepartJeu && !ValidFin && ValidAffJoueur  && PosXJoueur > 0)	// Si les Conditions sont Réunies //
	{
		PosXJoueur--;													// On Déplace le Joueur à Gauche //
		Matrice[PosXJoueur][PosYJoueur] = 'j';							// On Actualise la Position du Joueur dans le Tableau après Déplacement //
		Matrice[PosXJoueur + 1][PosYJoueur] = '0';						//
		if (!ValidDeplacMissileJoueur)
		{
			PosXMissileJoueur--;										// Et le Missile Joueur aussi s'il n'y a pas de Tir //
		}
		glutPostRedisplay();
	}


}



void DeplacDroite()
{

	if (DepartJeu && !ValidFin && ValidAffJoueur && PosXJoueur < 16)	// Si les Conditions sont Réunies //
	{
		PosXJoueur++;													// On Déplace le Joueur à Droite //
		Matrice[PosXJoueur][PosYJoueur] = 'j';							// On Actualise la Position du Joueur dans le Tableau après Déplacement //
		Matrice[PosXJoueur - 1][PosYJoueur] = '0';						//
		if (!ValidDeplacMissileJoueur)
		{
			PosXMissileJoueur++;										// Et le Missile Joueur aussi s'il n'y a pas de Tir //
		}
		glutPostRedisplay();
	}


}



void TimerEtoiles(int value)
{

	if (DepartJeu && !ValidFin)											// Si on est en Cours de Jeu //
	{
		PosYEtoiles += 25;												// On déplace les Etoiles de 25 Pixels vers le Bas //
		PosXEtoiles = PosXEtoiles;										// Horizontalement la Position des Etoiles ne varient pas //

		glutPostRedisplay();											// On Redessine Affichage //

	}

	glutTimerFunc(TimerMillisEtoiles, TimerEtoiles, 0);					// On Réarme ce Timer //

}



void TimerMissileAlien(int value)
{
	if (DepartJeu && !ValidFin && ValidDeplacMissileAlien)				// Si les Conditions sont réunies //
	{
		PosYMissileAlien += 2;											// On Déplace le Missile vers le Bas //
		glutPostRedisplay();											// On Redessine Affichage //

		if (PosYMissileAlien > 33)										// Si le Missile Alien a dépassé le Bas de la Fenêtre //
		{
			ValidAffMissileAlien = false;								// On Annule son Affichage //
			ValidDeplacMissileAlien = false;							// On Annule son Déplacement //
		}

	}

	glutTimerFunc(TimerMillisMissileAlien, TimerMissileAlien, 2);		// On Réarme ce Timer //

}



void TimerMissileJoueur(int value)
{

	if (DepartJeu && !ValidFin && ValidDeplacMissileJoueur)				// Si on est en Cours de Jeu et qu'on a Tiré //
	{
		PosXMissileJoueur = PosXMissileJoueur;							// Horizontalement le Missile suit sa propre Trajectoire //
		PosYMissileJoueur -= 1;											// On Déplace le Missile vers le Haut //
		glutPostRedisplay();											// On Redessine Affichage //

		if (PosYMissileJoueur < 0)										// Si le Missile Joueur a dépassé le Haut de la Fenêtre //
		{
			ValidAffMissileJoueur = false;								// Dans un Premier Temps on le Supprime de l'affichage //
			PosXMissileJoueur = PosXJoueur;
			PosYMissileJoueur = PosYJoueur - 1;							// On Le Remet a ses Coordonnées d'origine //
			ValidDeplacMissileJoueur = false;							// On Désactive la Fonction de ce Timer (Pour Stopper tout Déplacement Missile) //
			ValidAffMissileJoueur = true;								// On le Réaffiche //
		}



	}

	glutTimerFunc(TimerMillisMissileJoueur, TimerMissileJoueur, 2);		// On Réarme ce Timer //
}



void TimerFinExplosion(int value)
{

	ValidAffExplosion = false;											// On Désactive l'affichage de l'explosion //


	glutTimerFunc(TimerMillisFinExplosion, TimerFinExplosion, 4);		// On Réarme ce Timer //

}



void TimerCreationMissileAlien(int value)
{
	if (DepartJeu && !ValidFin && ValidAffJoueur)						// Si on est en Cours de Jeu //
	{

		for (int i = 0; i < 11; i++)									// On va parcourir les Lignes correspondantes aux Aliens //
		{
			if (Matrice[PosXJoueur][i] == '1')							// Si aligné horizontalement au Joueur et si Verticalement il y a Présence d'un Alien //
			{
				PosXMissileAlien = PosXJoueur;							// On Affecte les Coordonnées du Missile Alien //
				PosYMissileAlien = i - 1;
				ValidAffMissileAlien = true;							// On Valide son Affichage //
				ValidDeplacMissileAlien = true;							// On Valide son Déplacement //
			}

		}

	}

	glutTimerFunc(TimerMillisCreationMissileAlien, TimerCreationMissileAlien, 1);	// On Réarme ce Timer //
}




void GestionMissileJoueur()
{
	if (DepartJeu && !ValidFin && ValidDeplacMissileJoueur)				// Si on est en Cours de Jeu et qu'on a Tiré //
	{
		if (Matrice[PosXMissileJoueur][PosYMissileJoueur] == '1')		// Si le Missile Joueur rencontre un Alien //
		{
			PosXExplosion = PosXMissileJoueur;							// A l'endroit de la Rencontre on affiche une Explosion //
			PosYExplosion = PosYMissileJoueur;							//
			ValidAffExplosion = true;									// 
			Matrice[PosXMissileJoueur][PosYMissileJoueur] = '0';		// On Supprime Alien Concerné du Tableau //
			glutPostRedisplay();										// On Redessine Affichage //
			PlaySound(TEXT("Datas\\Collision.wav"), NULL, SND_FILENAME | SND_ASYNC); // On Joue le Son de l'explosion //
			NombreAliensRestant--;										// On a supprimé un Alien //
			ValidAffMissileJoueur = false;								// Dans un Premier Temps on le Supprime de l'affichage //
			PosXMissileJoueur = PosXJoueur;
			PosYMissileJoueur = PosYJoueur - 1;							// On Le Remet a ses Coordonnées d'origine //
			ValidDeplacMissileJoueur = false;							// On Désactive le Déplacement Missile Joueur //
			if (ValidAffJoueur)
			{
				ValidAffMissileJoueur = true;							// On le Réaffiche //
			}
		}

	}


	if (NombreAliensRestant == 0 && !ValidAffExplosion)					// Cas de la VICTOIRE //
	{ 
		AffTexteVictoire();												// On Affiche le Texte 'VICTOIRE' //
		PlaySound(TEXT("Datas\\Victoire.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son de la Victoire //
		ValidFin = true;												// On Valide la Fin de Jeu //

	}

}



void GestionMissileAlien()
{
	if (DepartJeu && !ValidFin && ValidDeplacMissileAlien)				// Si on est en Cours de Jeu et que un Missile Alien a été Tiré //
	{
		if (PosXMissileAlien == PosXJoueur && PosYMissileAlien == PosYJoueur - 1)	// Si le Missile Alien Rencontre le Joueur //
		{
			PlaySound(TEXT("Datas\\Collision.wav"), NULL, SND_FILENAME | SND_ASYNC); // On Joue le Son de l'explosion //
			PosXExplosion = PosXJoueur;
			PosYExplosion = PosYJoueur;									// A l'endroit de la Rencontre on affiche une Explosion //
			ValidAffExplosion = true;									//
			ValidAffJoueur = false;										// On Supprime le Joueur //
			ValidAffMissileJoueur = false;								// On Supprime le Missile Joueur //
			ValidAffMissileAlien = false;								// On Supprime le Missile Alien //
			glutPostRedisplay();
			ValidDeplacMissileAlien = false;							// On Stoppe le Déplacement du Missile Alien (et Annule cette Fonction) //
		}

	}

	if (!ValidAffJoueur && !ValidAffExplosion)					// Si l'explosion est Finie //
	{
		AffTexteDefaite();
		PlaySound(TEXT("Datas\\GameOver.wav"), NULL, SND_FILENAME | SND_ASYNC); // On Joue le Son de la Défaite //
		ValidFin = true;
	}


}



void AffTexteVictoire()
{

	glMatrixMode(GL_PROJECTION);										// Matrice de Projection //
	glPushMatrix();														// On Sauvegarde la Matrice//
	glLoadIdentity();													// On charge la Matrice à son Identité //
	gluOrtho2D(0.0,816.0,816.0,0.0);									// On définit le Minimum / Maximum de la Fenetre //

	glMatrixMode(GL_MODELVIEW);											// Matrice de Vue de Modèle //
	glPushMatrix();														// On Sauvegarde la Matrice //
	glLoadIdentity();													// On charge la Matrice à son Identité //

	glColor3d(0.0, 0.0, 1.0);											// Texte en Bleu //

	glRasterPos2i(350,408);												// Position du Texte //


	string s = "VICTOIRE";												// Texte à afficher //

	void* font = GLUT_BITMAP_TIMES_ROMAN_24;							// On définit le Type de Police et sa Taille //

	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;													// Fonction GLUT affichage Texte //
		glutBitmapCharacter(font, c);
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();														// On restaure la Matrice de Vue de Modèle // 

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();														// On restaure la Matrice de Projection //	




}



void AffTexteDefaite()
{

	glMatrixMode(GL_PROJECTION);										// Matrice de Projection //
	glPushMatrix();														// On Sauvegarde la Matrice//
	glLoadIdentity();													// On charge la Matrice à son Identité //
	gluOrtho2D(0.0, 816.0, 816.0, 0.0);									// On définit le Minimum / Maximum de la Fenetre //

	glMatrixMode(GL_MODELVIEW);											// Matrice de Vue de Modèle //
	glPushMatrix();														// On Sauvegarde la Matrice //
	glLoadIdentity();													// On charge la Matrice à son Identité //

	glColor3d(0.0, 0.0, 1.0);											// Texte en Bleu //

	glRasterPos2i(350, 408);											// Position du Texte //


	string s = "DEFAITE";												// Texte à afficher //

	void* font = GLUT_BITMAP_TIMES_ROMAN_24;							// On définit le Type de Police et sa Taille //

	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;													// Fonction GLUT affichage Texte //
		glutBitmapCharacter(font, c);
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();														// On restaure la Matrice de Vue de Modèle // 

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();														// On restaure la Matrice de Projection //




}

