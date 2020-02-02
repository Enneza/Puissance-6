#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> //pour system("clear");
#include <string.h> // pour le memset

/*#include "main.c"
#include "puiss6.c"*/

struct piece {
  int x;
  int y;
};
typedef struct piece piece;


struct joueur {
  int identifiant;
  piece * tabPions; // tableau des pions de chaque joueur
  int nbrPion;
};
typedef struct joueur joueur;

#define Colonnetab 13
#define Lignetab 11
#define maxPion (Colonnetab * Lignetab) / 2 //nombres de pions maximum que peut jouer chaque joueur;

int tableau [Lignetab][Colonnetab]; // le plateau de jeu

static joueur joueur1; // joueur 1
static joueur joueur2; // joueur 2

static piece pieceJoueur1[maxPion]; // piece du joueur 1
static piece pieceJoueur2[maxPion]; // piece du joueur 2

void init_tableau (int p[][Colonnetab]);
void init_joueur (joueur *, int , piece *);
void initialisation ();
void afficher_tableau(int p[][Colonnetab]);
void afficher_joueur(joueur);
int placer_piece (int, joueur *);
int verifVerticale(int , int );
int verifHorizontale(int , int );
int verifJeuGagant (int tableau[Lignetab][Colonnetab]);
void jouer();