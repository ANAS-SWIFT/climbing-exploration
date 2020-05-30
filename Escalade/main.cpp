//
//  main.cpp
//  Escalade
//
//  Created by ANAS on 4/30/20.
//  Copyright © 2020 ANAS. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graphemat.h"
#include "liregraphe.h"

NomSom path[]= {"A", "B", "C", "D" ,"E"};
typedef GrapheMat Graphe;
int nbtrajet = 0;

int menu ()
{
    printf ("\n\n Algorithmes de resolution du PVC \n\n");
    printf ("1 -  Creation du graphe\n");
    printf ("2 - Affichage du graphe\n");
    printf ("3 - Escalade 2-opt \n");
    printf ("0 - Quitter");

    printf ("\n");
    printf ("Votre choix ? ");
    int cod;
    scanf ("%d", &cod);
    getchar();
    printf ("\n");
    return cod;
}

int nbville(Graphe* g)
{
    return g->n;
}



bool sommetDanstrajet(int* trajet, int s)
{
    for(int i = 0; i < nbtrajet; i++)
    {
        if(trajet[i] == s)
            return true;
    }
    return false;
}


int* creerTrajet(Graphe* g,int premier){
    int* trajet = (int*) malloc (sizeof(g->n));
    if(g->n>premier)
        trajet[0] = premier;
    else
        printf("\n erreur lors de la creation du trajet premier element depasse la taille totale");
    return trajet;
}

int randomInt(int max) //retourne une ville aleatoire
{
    return rand() % max;
}

void ajouter(int* trajet, int s)
{
    nbtrajet++;
    trajet[nbtrajet] = s;
}

void affichertrajet(Graphe* graphe, int* trajet)
{
    for(int i = 0; i < nbtrajet; i++)
    {
        printf (" -%s ", graphe->nomS[trajet[i]]) ;
    }
}


int plusProcheVoisin (GrapheMat* graphe, int s, int * trajet)
{
    int posmin = -1;
    if (graphe->n == 0)
    {
        printf ("rien ‡ afficher\n");
    }
    else
    {
        int minc = 1000 ;            // un minimum jamais atteint
        int nMax = graphe->nMax ;
        for (int j=0; j<graphe->n; j++)
        {
            if (graphe->element [s*nMax+j] == vrai)
            {
                if (graphe->value)
                {
                    if(graphe->valeur [s*nMax+j] < minc && !sommetDanstrajet(trajet, j))
                    {
                        minc = graphe->valeur [s*nMax+j];
                        posmin = j;
                    }
                }
            }
        }
    }
    return posmin;
}



int* trajet_2opt(Graphe* graphe,int* trajet,int i , int k)
{
    int n=graphe->n;
    int* trajetnew=(int*)malloc(n*sizeof(int));

    for(int j=0; j<=i-1 ; j++)
    {
        trajetnew[j]=trajet[j];
    }
    int compteur=0;
    for(int j=i; j<=k ; j++)
    {
        trajetnew[j]=trajet[k-compteur];
        compteur++;
    }
    for(int j=k+1; j<n ; j++)
    {
        trajetnew[j]=trajet[j];
    }
    return trajetnew;
}

int cout_trajet(int* trajet,Graphe* graphe)
{
    int nmax = graphe->nMax;
    int n = graphe->n;
    int cout = 0;
    for(int i=0; i<n-1;i++){

        cout+=graphe->valeur[trajet[i]*nmax+trajet[i+1]];

    }

    cout+=graphe->valeur[trajet[n-1]*nmax+trajet[0]];
    return cout;
}



int main ()
{
    srand(time(0));
    Graphe* graphe;
    booleen fini = faux;
    while (!fini)
    {
        switch ( menu() )
        {
        case 0:
            fini = vrai;
            break;

        case 1:
        {
            char nomFe [150] = "/Users/mac/Desktop/Study/myS8/Intelligence Artificielle/PART2/Escalade/Escalade/graphe.txt";
            FILE* fe = fopen (nomFe, "r");
            if (fe == NULL)
            {
                perror (nomFe);
            }
            else
            {
                graphe = lireGraphe (fe, 20);
                fclose (fe);

            }
            break;
        }

        case 2:
        {
            ecrireGraphe (graphe);
            break;
        }

        case 3:
        {
                    int rv = 2;
                    printf("\n Le Depart : = %s", graphe->nomS[rv]);
                    int* trajetCourant = creerTrajet(graphe, rv);
                    int s = rv;

                    while(nbtrajet < (graphe->n))
                    {
                        s = plusProcheVoisin(graphe, s, trajetCourant);
                        ajouter(trajetCourant, s);
                    }

                    printf("\n Le tour initial Plus proche voisin \n");
                    affichertrajet(graphe,trajetCourant);
                    printf("\n ");
                    printf("Le cout est : %d",cout_trajet(trajetCourant,graphe));

                    int n=graphe->n;
                    booleen trouve = false;

                    while(!trouve){

                        int* MeilleurVoisin = trajetCourant;
                        for (int i = 1; i < n-2;i++)
                        {
                            for (int k = i+1; k < n; k++)
                            {
                              int* trajetVoisin=trajet_2opt(graphe,trajetCourant,i ,k);
                                //affichertrajet(graphe,trajetVoisin);
                                if(cout_trajet(trajetVoisin,graphe)<cout_trajet(MeilleurVoisin,graphe))
                                      MeilleurVoisin=trajetVoisin;
                            }
                        }
                     if(cout_trajet(MeilleurVoisin,graphe)<cout_trajet(trajetCourant,graphe))
                             trajetCourant=MeilleurVoisin;
                        else
                             trouve=true;
                    }

                    printf("\n Le trajet Escalade (2opt) est : \n ");
                    affichertrajet(graphe,trajetCourant);
                    printf("\n Cout: %d \n \n \n",cout_trajet(trajetCourant,graphe));
                    nbtrajet=0;
                    free(trajetCourant);
                    return 0;
            }

        }

    }




    return 0;
}











