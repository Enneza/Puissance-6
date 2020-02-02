#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> //pour system("clear");
#include <string.h> // pour le memset
#include "puissance.h"


void init_tableau (int p[][Colonnetab]){
  int l, c;
  for (l = 0; l < Lignetab; l++)
    for (c = 0; c < Colonnetab; c++)
      p[l][c] = 0;
}

void init_joueur (joueur *j, int idt, piece *tabPiece){
  j->identifiant = idt;
  j->tabPions = tabPiece;
  j->nbrPion = 0;
}

// faire une boucle qui donne l'identifiant aux joueurs

void initialisation (){
  init_joueur (&joueur1, 1, pieceJoueur1);
  init_joueur (&joueur2, 2, pieceJoueur2);
  init_tableau(tableau);
}

void afficher_tableau(int p[][Colonnetab]){
  int l, c;
  printf("  ");
  for (c = 0; c < Colonnetab; c++){
    printf(" %d",c+1);
  }
  printf("\n");
  for (l = 0; l < Lignetab; l++){
    printf("  ");
    for (c = 0; c < Colonnetab; c++){
      if (c >= 10)
	printf(" ");
      if ( p[l][c] == 0 ){
	printf(" .");
      }
      else if ( p[l][c] == 1 ){
	printf(" x");
      }
      else if( p[l][c] == 2 ){
	printf(" #");
      }
    }
    printf("\n");
  }
  printf("\n");
}


int placer_piece (int cordonneeX, joueur *j){
  int y = 0;
  piece pc;
  if ((cordonneeX >= 0) && (cordonneeX < Colonnetab)){
    while ((y < Lignetab) && (tableau[y][cordonneeX] == 0) )
      y++;
    if (y == 0)
      return 1;
    y--;
    tableau[y][cordonneeX] = j->identifiant;
    pc.x = cordonneeX;
    pc.y = y;
    j->tabPions[j->nbrPion++] = pc;
    if (j->nbrPion == maxPion)
      return 2;
    return 0;
  }
  return -1;
}


int verifVerticale(int l, int c){
	int compteur = 1;
	int i = 1;

	// Parcours vers le bas
	while(l+i < Lignetab && tableau[l][c] == tableau[l+i][c]){
		compteur++;
		i++;
	}
	if (compteur >= 6)
	{
		return compteur;
	}
	i = 1;

	// Parcours vers le haut
	while(l-i >= 0 && tableau[l][c] == tableau[l-i][c]){
		compteur++;
		if (compteur >= 6)
		{
			return compteur;
		}
		i++;
	}

	return compteur;
}


int verifHorizontale(int ligne, int colonne){
	int compteur = 1;
	int i = 1;

	// Parcours vers la droite
	while(colonne+i < Colonnetab && tableau[ligne][colonne] == tableau[ligne][colonne+i]){
		compteur++;
		if (compteur == 4 && verifVerticale(ligne,colonne) >= 3)
		{
			return 6;
		}else if (compteur == 3 && verifVerticale(ligne,colonne) >= 4){
			return 6;
		}
		i++;
	}
	i = 1;

	// Parcours vers la gauche
	while(colonne-i >= 0 && tableau[ligne][colonne] == tableau[ligne][colonne-i]){
		compteur++;
		if (compteur == 4 && verifVerticale(ligne,colonne) >= 3)
		{
			return 6;
		}else if (compteur == 3 && verifVerticale(ligne,colonne) >= 4){
			return 6;
		}
		i++;
	}
	return compteur;
}


int verifJeuGagant (int tableau[Lignetab][Colonnetab]){
  
  for (int i = 0; i < Lignetab; i++){
  	for (int j = 0; j < Colonnetab; j++){
  		if (tableau[i][j] != 0 && verifHorizontale(i, j) >= 6)
  		{
  			return tableau[i][j];
  		}else if (tableau[i][j] != 0 && verifVerticale(i, j) >= 6)
  		{
  			return tableau[i][j];
  		}
  	}
  }
  return 0;
}

void jouer(){
  int colonneJouee = -1;
  int pc1=-1, pc2=-1;
  char s[64];
  static int n = 0;	// Joueur
  int win = 0;
  system("clear"); // effacer l'ecran
  afficher_tableau(tableau); // afficher le plateau
    
  for(;;){
    //afficher_tableau(tableau); // afficher le plateau
    if ((pc1 == 2) && (pc2 == 2)){
      printf("MATCH NUL !!!\n");
      break;
    }
    printf("Joueur_Num %d :", n%2 + 1);
    
    do { // on choisit dans la boucle le numero de la colonne entre 1 et 13
      memset(s, 0, sizeof(s));
      printf(" (1-13) : ");
      fgets(s, sizeof(s), stdin);
      colonneJouee = atoi(s);
      
    } while ((colonneJouee<1) || (colonneJouee>13));
    
    colonneJouee--; // pour avoir le bon indice dans le tableau

    if (n%2 == 0){ // joueur 1 qui joue le coup
      printf("joueur1\n");
      pc1 = placer_piece(colonneJouee, &joueur1);
      system("clear"); // effacer l'ecran
  	  afficher_tableau(tableau); // afficher le plateau
     
	  win = verifJeuGagant(tableau);
      
      if (win != 0){
    	printf("Le gagnant est le joueur %d\n", win);
    	break;
      }
      n++;
     
    }
    else{ // joueur 2 qui joue le coup
      printf("joueur2\n");
      pc2 = placer_piece(colonneJouee, &joueur2);
      system("clear"); // effacer l'ecran
  	  afficher_tableau(tableau); // afficher le plateau
      win = verifJeuGagant(tableau);
      if (win != 0)
      {
    	printf("Le gagnant est le joueur %d\n", win);
    	break;
      }
      n++;
      
    }
    
  }// fin boucle for
}