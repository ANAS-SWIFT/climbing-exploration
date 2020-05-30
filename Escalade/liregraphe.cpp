
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "graphemat.h"



typedef char NomSom [20];
int c;

void lireBlancs (FILE* fe) {
  while ( ( (c==' ')  || (c=='\n') || (c==13) )  && !feof(fe) ) {
    c = getc(fe);
  }
}

void lireUnMot (FILE* fe, char* chaine) {
  char* pCh = chaine;
  lireBlancs (fe);
  while ( isalpha(c) || isdigit(c) ) {
    *pCh++ = (char) c;
    c = getc(fe);
  }
  *pCh = 0;
  lireBlancs (fe);
}

GrapheMat* lireGraphe (FILE* fe, int nMaxSom) {
  booleen value = faux;

  GrapheMat* graphe = creerGrapheMat (nMaxSom, faux);

  c = getc(fe);
  while (c != ';') {
    char* somD = (char*) malloc (20);
    lireUnMot (fe, somD);
    ajouterUnSommet (graphe, somD);
  }
  while (c != EOF) {
    c = getc(fe);
    NomSom somD;
    lireUnMot (fe, somD);
    if (c != ':') {
      if (c != EOF) printf ("Manque : %c (%d)\n", c,c);
      graphe->value = value;
      return graphe;
    }
    c = getc(fe);
    while (c != ';') {
      NomSom somA;
      lireUnMot (fe, somA);
      int cout;
      if (c == '(') {
        value = vrai;
        fscanf (fe, "%d", &cout);
        c = getc (fe); // passer )
        if (c != ')') printf ("Manque )\n");
        c = getc (fe);
        lireBlancs (fe);
      } else {
        cout = 0;
      }
      ajouterUnArc (graphe, somD, somA, cout);
    }
  }
  graphe->value = value;
  return graphe;
}
