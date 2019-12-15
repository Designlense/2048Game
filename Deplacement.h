
//  Deplacement.h
//  Projet jeux 2048
//  Copyright 2014-2019 _Designlense.io_. All rights reserved.
//Author : Raphael Mahiet
//Hire me : collaborate@designlense.io
//Licence MIT 


typedef vector<vector< int > > Grille ;
Grille deplacerAdroite(Grille grille);
Grille deplacerAgauche(Grille grille);
Grille deplacerVersHaut(Grille grille);
Grille deplacerVersBas(Grille grille);


 
bool EstFusionAutorisee(int nTuileSource, int nTuileCible) ;
int fusionnerCellules(int nTuileSource, int nTuileCible) ;
