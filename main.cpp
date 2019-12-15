//
//  main.cpp
//  Projet jeux 2048
//  Copyright 2014-2019 _Designlense.io_. All rights reserved.
//Author : Raphael Mahiet
//Hire me : collaborate@designlense.io
//Licence MIT
//
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
// bibliothèque nécessaire pour contrôler l'affichage du nombre de caractères.
#include <iomanip>
#include <time.h>

using namespace std ; 
#include "deplacement.h"

// prototypes des fonctions non utilisées par deplacement.cpp.
void afficherGrille(Grille grille) ;     
Grille initialiserGrille (Grille grille, int valeur);
Grille creerGrille (int nLignes , int nColonnes );
bool testerValeurDansGrille(Grille grille, int nValeurTuile); 
int tirerUnNombre(int nRange) ;
int testerTirage(int nTirage) ;
Grille placerAleatoireTuile(Grille grille) ;

//
// initGrille
//

Grille creerGrille (int nLignes , int nColonnes ){ 
     Grille  result ;
     
     result = Grille (nLignes) ; 
     // allocation des sous-tableaux
     for ( int i = 0 ; i<nLignes ; i++ ){
         result[i]= vector<int> (nColonnes) ;
     } ;
     // initialisation
     for (int i = 0 ; i<nLignes ; i++){
         for (int j=0 ; j <nColonnes ; j++){
             result[i][j] = 0 ;
         } ;
     } ;
    return (result) ; 
}
         
// 
// EstFusionAutorisee
//   la fusion est autorisée si la valeur max 2048 (soit 2 à la puissance 11) n'est pas atteinte
//   si la tuileCible a une valeur compatible soit vide soit égale à la valeur 

bool EstFusionAutorisee(int nTuileSource, int nTuileCible) {
    if (nTuileSource==11) // le max est atteint
        return false ;
    
    return ((nTuileSource==nTuileCible) || !nTuileCible) ; 
}

int fusionnerCellules(int nTuileSource, int nTuileCible) {
    int nResultat ; 
    if (!nTuileCible)
        nResultat = nTuileSource ; 
    else
        nResultat = nTuileSource+1;  

    return (nResultat) ; 
}
    
//
// tirerUnNombre renvoie un nombre aléatoire entre 0 et 10 exclu , pour la valorisation des tuiles
//  ou entre 0 et 4 exclu pour le choix de l'index dans la grille
//
int tirerUnNombre( int nRange) {
    return (rand()%nRange) ;
}
//
// testerTirage va permettre de vérifier que le nombre de tirage de 4 est conforme à ce qui est attendu.
//
int testerTirage(int nTirage) {
    int nTirageQuatre = 0 ;
    
    for (int i=0 ; i < nTirage ; i++)
     if (!tirerUnNombre(10))
         nTirageQuatre++ ; 
    return (nTirageQuatre) ;
}

//
//  placerAleatoireTuile : cette fonction parcourt la grille à partir de coordonnées aléatoire iStart et Jstart 
//  à la recherche du premier emplacement libre
//
//
Grille placerAleatoireTuile(Grille grille)
{ 
    int iStart ; 
    int jStart ;
    int i,j ; 
    
    iStart = tirerUnNombre (grille.size()) ; 
    jStart = tirerUnNombre (grille[iStart].size()) ;
    i=iStart ; 
    j=jStart ; 
  
    do {
        do {
           if (!grille[i][j])
           {            // attention : on stocke non pas 4 & 2 mais les puissances de 2.
               grille [i][j]= (!tirerUnNombre(10))? 2 : 1 ; 
             return grille ; 
           }
            j++ ;
        } while (j!=jStart);
        i++ ; 
    } while (i!=iStart) ;
    return grille ;
}
    



Grille initialiserGrille (Grille grille, int nValeur ){ 
    for (int i = 0 ; i<grille.size() ; i++){
        for (int j=0 ; j <grille[i].size() ; j++){
            grille[i][j] = nValeur ;
        } ;
    } ;
    return (grille) ; 
};

// testerValeurDansGrille
//   cette fonction vérifie si toutes les cellules de la grille sont bien à la valeur nValeurTuile
//   si c'est bien le cas, TRUE est retournée.
//
bool testerValeurDansGrille(Grille grille, int nValeurTuile) { 
    for (int i = 0 ; i< grille.size() ; i++){
        for (int j=0 ; j <grille[i].size() ; j++){
            if (nValeurTuile != grille[i][j])
                return false ; 
        }
    }
    return true ; 
}


// afficherGrille
//  Cette fonction affiche la grille en tenant compte du fait que l'exposant de la valeur de la tuile  (valeur non nulle)
//  est stocké .. il faut donc recalculer 2**valeur tuile.
//  On fait attention à ce que les colonnes restent alignés grâce à la fonction setw  (include iomanip)
//  Les traits horizontaux utilisent la fonction setfill (include iomanip)
//  Voir http://www.cprogramming.com/tutorial/iomanip.html à ce sujet.
//
void afficherGrille(Grille grille){
    int n ; 
    int nLargeur= 4 ; 
    int nLigne ; 
    nLigne = (nLargeur*(grille.size()+1)) ; 
    
    cout << '|' <<setfill('-')<< setw(nLigne) << '|' << endl ;   
    for (int i=0 ; i < grille.size() ; i++) {
        cout << "|" ;
        for (int j=0 ; j < grille[i].size() ; j++) {
            if (grille[i][j])
                n=pow(2,grille[i][j]);
            else
                n=0 ; 
                    // setw permet de contrôler le nombre de caractères affichés et setfill la valeur par défaut.
            cout <<setfill(' ') << setw(nLargeur) << n << "|" ;
        } ;
        cout <<endl ; 
        cout << '|' <<setfill('-')<< setw(nLigne) << '|' << endl ;   
    } ;
} ;
        
    
    

int main (int , const char * argv[]) {
    

    Grille grille ; 
    char cCommand ;
        
    // initialisation de la fonction random 
    srand(time(NULL)) ; 
    
    // initialisation de la grille, placement de deux tuiles aléatoirement et enfin affichage du résultat.
    grille = creerGrille(4,4) ; 
    grille = placerAleatoireTuile(grille) ; 
    grille = placerAleatoireTuile(grille) ; 
    afficherGrille(grille) ;

    
    // boucle forever de lecture et traitement des commandes - Voir la liste à la commande '?'
    for (;;) {
        cout << "enter command :" << endl ;
        cin >> cCommand ;  
        switch (cCommand){
            case 'h' :
            case 'b' :
            case 'g' :
            case 'd' :{ 
                  switch (cCommand) {
                    case 'h' : 
                        grille = deplacerVersHaut(grille) ; 
                        break ;
                    case 'b' : 
                        grille = deplacerVersBas(grille) ;
                        break ; 
                    case 'd' : 
                        grille = deplacerAdroite(grille) ;                  
                        break ; 
                    case 'g' : 
                        grille = deplacerAgauche(grille) ; 
                        break ; 
                  }
                  grille = placerAleatoireTuile(grille) ;
                  afficherGrille(grille) ;
                }
                break ; 
            case 'a' :  // tirage de 1000
                cout << testerTirage(1000)  << endl ; 
                break ; 
                
            case '?' :  // help
                cout <<"a: vérification du tirage aléatoire sur 1000 tirages" << endl ;
                cout <<"h: haut"   << endl ; 
                cout <<"b: bas "   << endl ; 
                cout <<"g: gauche" <<endl ; 
                cout <<"d: droite" <<endl ;
                cout <<"i: initialiser la grille avec deux tuiles"<<endl ; 
                cout <<"p: afficher la grille"<<endl ; 
                cout <<"t: ajout aléatoire de tuile" <<endl;
                cout <<"x: sortie du programme"<<endl ; 
                break ; 
                
            case 'i' :
                grille = initialiserGrille(grille,0) ;
                grille = placerAleatoireTuile(grille) ; 
                grille = placerAleatoireTuile(grille) ; 
                afficherGrille(grille) ;
                break ; 
            
            case 'p' :  // p= print ie afficher la grille
                afficherGrille(grille) ; 
                break ; 
            case 't' : 
                grille = placerAleatoireTuile(grille) ; 
                break ;  
                
            case 'x' : // sortie du programme 
                return (0); 
        }   
  }
}
