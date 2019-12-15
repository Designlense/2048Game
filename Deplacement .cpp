//  Deplacement .cpp
//  Projet jeux 2048

//  Created by Raphaël Mahiet on 18/12/14.
//  ce fichier rassemble l'ensemble des fonctions de déplacements utilisés par le programme principal.
//  Copyright 2014-2019 _Designlense.io_. All rights reserved.
//Author : Raphael Mahiet
//Hire me : collaborate@designlense.io
//Licence MIT 

#include <iostream>

using namespace std ; 
#include <stdio.h>
#include <vector>
#include "Deplacement.h"

//
// deplacerAdroite 
//   cette fonction gère le déplacement à droite des tuiles de la grille
//   on examine la grille ligne après ligne
//   pour chaque ligne, pour ne avoir à se préoccuper des cellules vides on va utiliser une structure intermédiaire de pile
//   on balaye de droite à gauche chaque ligne en plaçant sur une pile les éléments non nuls en les fusionnant si nécessaire.
//   une fois que toute la ligne est balayée, le contenu de la pile est remis en fin de ligne.
//
Grille deplacerAdroite(Grille grille) {
    vector < int>  pile ; 
    long  jDernier ; 
    int   iPile ; 
    
    for (int i=0 ; i< grille.size() ; i++){
        pile.resize(0) ;
        jDernier = grille[i].size()-1 ;  
        //on met la dernière valeur de la ligne sur la pile ,même si elle est nulle, ainsi  la pile est non vide
        pile.push_back(grille[i][jDernier] ) ;
        for (int j=(int) jDernier-1 ; j>=0 ; j--) {
            if (grille[i][j])  
            {   // si la fusion est autorisée , on fusionne les cellules dans la pile ,sinon on empile la cellule non vide.
                if (EstFusionAutorisee(grille[i][j],pile[pile.size()-1]))
                    pile[pile.size()-1]=fusionnerCellules(grille[i][j],pile[pile.size()-1]) ; 
                else 
                    pile.push_back(grille[i][j]) ;
            } ;
            grille[i][j]=0 ;
        } ;
        // on recopie la pile à l'envers
        iPile=pile.size()-1 ; 
        for (long j= grille[i].size()-pile.size() ; j < grille[i].size() ; j++,iPile-- ){
            grille[i][j]=pile[iPile] ; 
        } ;
    } ;
    return (grille) ; 
    
}; 


//
// deplacerAgauche
//   cette fonction gère le déplacement à gauche des tuiles de la grille
//   on examine la grille ligne après ligne
//   pour chaque ligne, pour ne avoir à se préoccuper des cellules vides on va utiliser une structure intermédiaire de pile
//   on balaye de gauche à droite chaque ligne en plaçant sur une pile les éléments non nuls en les fusionnant si nécessaire.
//   une fois que toute la ligne est balayée, le contenu de la pile est remis en début de ligne.
//
Grille deplacerAgauche(Grille grille) {
    vector < int>  pile ; 
    int  jDebut ; 
    int   iPile ; 
    int   iPileMax ; 
    
    for (int i=0 ; i< grille.size() ; i++){
        pile.resize(0) ;
        jDebut = 0 ;  
        //on met la première valeur de la ligne sur la pile ,même si elle est nulle,  la pile est ainsi non vide
        pile.push_back(grille[i][jDebut] ) ;
        for (int j= jDebut+1 ; j< grille[i].size() ; j++) {
            if (grille[i][j])  
            {   // si la fusion est autorisée , on fusionne les cellules dans la pile ,sinon on empile la cellule non vide.
                if (EstFusionAutorisee(grille[i][j],pile[pile.size()-1]))
                    pile[pile.size()-1]=fusionnerCellules(grille[i][j],pile[pile.size()-1]) ; 
                else 
                    pile.push_back(grille[i][j]) ;
            } ;
            grille[i][j]=0 ;
        } ;
        // on recopie la pile à l'endroit
        iPileMax=pile.size() ; 
        iPile=0 ; 
        for (int j=0 ; iPile < iPileMax ; j++,iPile++){
            grille[i][j]=pile[iPile] ; 
        } ;
    } ;
    return (grille) ; 
    
}; 



//
// deplacerVersHaut
//   cette fonction gère le déplacement vers le haut des tuiles de la grille
//   on examine la grille colonne après colonne
//   pour chaque coloonne, pour ne avoir à se préoccuper des cellules vides on va utiliser une structure intermédiaire de pile
//   on balaye de haut en bas chaque colonne en plaçant sur une pile les éléments non nuls en les fusionnant si nécessaire.
//   une fois que toute la colonne est balayée, le contenu de la pile est remis en début de ligne.
//
Grille deplacerVersHaut(Grille grille) {
    vector < int>  pile ; 
    int  iDebut ; 
    int  iPile ; 
    int  iPileMax ; 
    
    for (int j=0 ; j< grille[0].size() ; j++){
        pile.resize(0) ;
        iDebut = 0 ;  
        //on met la première valeur de la colonne sur la pile ,même si elle est nulle,  la pile est ainsi non vide
        pile.push_back(grille[iDebut][j] ) ;
        for (int i= iDebut+1 ; i< grille.size() ; i++) {
            if (grille[i][j])  
            {   // si la fusion est autorisée , on fusionne les cellules dans la pile ,sinon on empile la cellule non vide.
                if (EstFusionAutorisee(grille[i][j],pile[pile.size()-1]))
                    pile[pile.size()-1]=fusionnerCellules(grille[i][j],pile[pile.size()-1]) ; 
                else 
                    pile.push_back(grille[i][j]) ;
            } ;
            grille[i][j]=0 ;
        } ;
        // on recopie la pile à l'endroit
        iPileMax=pile.size() ; 
        for (int i=0, iPile=0 ; iPile < iPileMax ; i++,iPile++){
            grille[i][j]=pile[iPile] ; 
        } ;
    } ;
    return (grille) ; 
    
}; 

//
// deplacerVersBas 
//   cette fonction gère le déplacement vers lebas des tuiles de la grille
//   on examine la grille colonne après colonne 
//   pour chaque colonne, pour ne avoir à se préoccuper des cellules vides on va utiliser une structure intermédiaire de pile
//   on balaye du bas vers le haut chaque colonne en plaçant sur une pile les éléments non nuls en les fusionnant si nécessaire.
//   une fois que toute la ligne est balayée, le contenu de la pile est remis en fin de ligne.
//
Grille deplacerVersBas(Grille grille) {
    vector < int>  pile ; 
    long  iDernier ; 
    int   iPile ; 
    
    for (int j=0 ; j< grille[0].size() ; j++){
        pile.resize(0) ;
        iDernier = grille.size()-1 ;  
        //on met la dernière valeur de la ligne sur la pile, même si elle est nulle , la pile est ainsi non vide
        pile.push_back(grille[iDernier][j] ) ;
        for (int i=(int) iDernier-1 ; i>=0 ; i--) {
            if (grille[i][j])  
            {   // si la fusion est autorisée , on fusionne les cellules dans la pile ,sinon on empile la cellule non vide.
                if (EstFusionAutorisee(grille[i][j],pile[pile.size()-1]))
                    pile[pile.size()-1]=fusionnerCellules(grille[i][j],pile[pile.size()-1]) ; 
                else 
                    pile.push_back(grille[i][j]) ;
            } ;
            grille[i][j]=0 ;
        } ;
        // on recopie la pile à l'envers
        iPile=pile.size()-1 ; 
        for (long i= grille.size()-pile.size() ; i < grille.size() ; i++,iPile-- ){
            grille[i][j]=pile[iPile] ; 
        } ;
    } ;
    return (grille) ; 
    
}; 
