#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tp3.h"


/* **********************************
 * Cr�ation et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite) {
    if(quantite <= 0) return NULL;


    T_Produit *nouveauProduit = NULL;

    nouveauProduit = malloc(sizeof(T_Produit));
    if (nouveauProduit == NULL) return NULL; // l'allocation mémoire n'a pas pu se faire


    nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace mémoire dédié pour notre champ de structure
    strcpy(nouveauProduit->designation,designation);
    nouveauProduit->prix = prix;
    nouveauProduit->quantite_en_stock = quantite;
    nouveauProduit->suivant = NULL;

    return nouveauProduit;
}



/* ********************************
 * Cr�ation et initialisation Rayon
 ******************************** */
T_Rayon *creerRayon(char *nom) {
    T_Rayon *nouveauRayon = NULL;

    nouveauRayon = malloc(sizeof(T_Rayon));
    if (nouveauRayon != NULL) {
        // l'allocation m�moire s'est bien pass�e
        nouveauRayon->nom_rayon = malloc(strlen(nom) + 1);
        strcpy(nouveauRayon->nom_rayon,nom);
        nouveauRayon->liste_produits = NULL;
        nouveauRayon->suivant = NULL;
    }

    return nouveauRayon;
}



/* **********************************
 * Cr�ation et initialisation Magasin
 ********************************** */
T_Magasin *creerMagasin(char *nom) {
    T_Magasin *nouveauMagasin = NULL;

    nouveauMagasin = malloc(sizeof(T_Magasin));
    if (nouveauMagasin != NULL) {
        nouveauMagasin->nom = malloc(strlen(nom) + 1);
        strcpy(nouveauMagasin->nom,nom);
        nouveauMagasin->liste_rayons = NULL;
    }

    return nouveauMagasin;
}



/* ********************************
 * Ajout d'un rayon dans un magasin
 ******************************** */
int ajouterRayon(T_Magasin *magasin, char *nomRayon) {
    // TODO : Attention à bien vérifier toutes les valeurs que peut prendre "magasin"

    if (magasin == NULL) 
    {
        printf("Magasin inexistant.\n");
    }

    T_Rayon *rayonPrecedent = NULL;
    T_Rayon *rayonCourant = magasin->liste_rayons;

    // On parcourt toute la liste jusqu'à trouver un mot plus grand ou la fin de la liste
    while (rayonCourant != NULL && strcmp(rayonCourant->nom_rayon, nomRayon) < 0)
    {
        rayonPrecedent = rayonCourant;
        rayonCourant = rayonCourant->suivant;
    }

    // Test si rayon existe déjà
    if (rayonCourant != NULL && strcmp(rayonCourant->nom_rayon, nomRayon) == 0)
    {
        printf("Le rayon existe déjà.\n");
        return 0;
    }

    // Ok pour insérer 

    T_Rayon *nouveauRayon = creerRayon(nomRayon);

    if(rayonPrecedent == NULL)
        magasin->liste_rayons = nouveauRayon;
    else
        rayonPrecedent->suivant = nouveauRayon;

    nouveauRayon->suivant = rayonCourant; // Pour bien marquer la fin
    return 1;
}



/* ********************************
 * Ajout d'un produit dans un rayon
 ******************************** */
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite) {
    if(quantite <= 0) 
    {
        return 0; // TODO : vérifier pourquoi cette ligne lève un warning. Au pire on la vire mais c'est dommage
        // Peut être car return NULL? Dans le sujet on dit si y a un pb on renvoie 0
    }

    //* Vérification si le produit existe déjà dans le rayon
    T_Produit *produit = rayon->liste_produits;
    while (produit != NULL) {
        if (strcmp(produit->designation, designation) == 0) {
            // Le produit existe déjà, on augmente simplement sa quantite
            produit->quantite_en_stock += quantite;
            return 1; // Return 1 car on a ajouté et tout s'est bien passé
        }
        produit = produit->suivant;
    }


    //* Création du nouveau produit
    T_Produit *nouveauProduit = creerProduit(designation, prix, quantite);


    //* Insertion du nouveau produit dans le rayon, en respectant l'ordre croissant des prix
    T_Produit *produitPrecedent = NULL;
    T_Produit *produitCourant = rayon->liste_produits;

    // tant qu'on trouve un prix inférieur au produit courant, on avance dans le rayon 
    while (produitCourant != NULL && produitCourant->prix < prix) {
        produitPrecedent = produitCourant;
        produitCourant = produitCourant->suivant;
    }

    // On vient de dépasser le dernier produit au prix < au prix courant. On insère 
    if(produitPrecedent == NULL)
        rayon->liste_produits = nouveauProduit;
    else
        produitPrecedent->suivant = nouveauProduit;

    nouveauProduit->suivant = produitCourant; // Pour bien marquer la fin

    return 1; // Succès de l'ajout
}



/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasin(T_Magasin *magasin) {
    T_Rayon *current;
    current = magasin->liste_rayons;

    if (magasin == NULL)
    {
        printf("Magasin inexistant.");
    }
    

    int nb_produits;
    T_Produit *produit;

    if (current == NULL)
    {
        printf("Magasin vide.\n");
    }

    else
    {   
        // Pour avoir une table sympa on va calculer la longueur du mot le plus long
        printf("Affichage des rayons du magasin %s\n", magasin->nom);
        int max = strlen("Nom du rayon");
        while (current != NULL)
        {   
            if (strlen(current->nom_rayon) > max)
            {
                max = strlen(current->nom_rayon);
            }
            current = current->suivant;
        }
        printf("+");
        for (int k = 0; k < max*1.5; k++)
        {
            printf("-");
        }
        printf("+");
        for (int k = 0; k < strlen(" Nombre de produits") + 1; k++)
        {
            printf("-");
        }
        printf(("+\n"));
        printf("| Nom du rayon");
        for (int k = 0; k < max*1.5 - strlen("| Nom du rayon") + 1; k++)
        {
            printf(" ");
        }
        printf("|");
        printf(" Nombre de produits ");
        printf("|\n");
        printf("+");
        for (int k = 0; k < max*1.5; k++)
        {
            printf("-");
        }
        printf("+");
        for (int k = 0; k < strlen(" Nombre de produits") + 1; k++)
        {
            printf("-");
        }
        printf(("+\n"));

        current = magasin->liste_rayons; // Car current a été itéré

        while (current != NULL)
        {   
            produit = current->liste_produits;
            nb_produits = 0;
            // while (produit->suivant != NULL)
            // {
            //     nb_produits++;
            // }
            printf("| %s", current->nom_rayon);
            for (int k = 0; k < 1.5*max - strlen(current->nom_rayon) - 1; k++)
            {
                printf(" ");
            }
            printf("| ");
            printf("%d", nb_produits);
            for (int k = 0; k < strlen(" Nombre de produits") - getNumLength(nb_produits) - 1; k++)
            {
                printf(" ");
            }
            printf("|\n");
            current = current->suivant;
        }
    }
}



/* *****************************************
 * Affichage de tous les produits d'un rayon
 ***************************************** */
void afficherRayon(T_Rayon *rayon) {
    T_Produit *current;
    current = rayon->liste_produits;

    if (rayon == NULL)
    {
        printf("Rayon inexistant.");
    }

    else if (current == NULL)
    {
        printf("Rayon vide.\n");
    }

    else
    {   
        // Pour avoir une table sympa on va calculer la longueur du mot le plus long
        int max = strlen("Designation");
        while (current != NULL)
        {   
            if (strlen(current->designation) > max)
            {
                max = strlen(current->designation);
            }
            current = current->suivant;
        }
        printf("+");
        for (int k = 0; k < max*1.5; k++)
        {
            printf("-");
        }
        printf("+");
        for (int k = 0; k < LEN_MAX_PRIX*1.5; k++)
        {
            printf("-");
        }
        printf("+");
        for (int k = 0; k < LEN_MAX_QTE*1.5; k++)
        {
            printf("-");
        }
        printf(("+\n"));
        printf("| Designation ");
        for (int k = 0; k < max*1.5 - strlen("| Designation ") + 1; k++)
        {
            printf(" ");
        }
        printf("|");
        printf(" Prix ");
        for (int k = 0; k < LEN_MAX_PRIX*1.5 - strlen(" Prix "); k++) // Si temps faire dynamique en fonction du plus grand prix
        {
            printf(" ");
        }
        printf("| Quantite en stock ");
        for (int k = 0; k < LEN_MAX_QTE*1.5 - strlen("| Quantite en stock ") + 1; k++) // Si temps faire dynamique en fonction du plus grand qté
        {
            printf(" ");
        }
        printf("|\n");
        printf("+");
        for (int k = 0; k < max*1.5; k++)
        {
            printf("-");
        }
        printf("+");
        for (int k = 0; k < LEN_MAX_PRIX*1.5; k++)
        {
            printf("-");
        }
        printf("+");
        for (int k = 0; k < LEN_MAX_QTE*1.5; k++)
        {
            printf("-");
        }
        printf(("+\n"));


        current = rayon->liste_produits; // Car current a été itéré

        while (current != NULL)
        {   
            printf("| %s", current->designation);
            for (int k = 0; k < 1.5*max - strlen(current->designation) - 1; k++)
            {
                printf(" ");
            }
            printf("| ");
            printf("%.2f", current->prix);
            for (int k = 0; k < LEN_MAX_PRIX*1.5 - getFloatNumLength(current->prix) - 1 - 3; k++)
            {
                printf(" ");
            }
            printf("| ");
            printf("%d", current->quantite_en_stock);
            for (int k = 0; k < LEN_MAX_QTE*1.5 - getNumLength(current->quantite_en_stock) - 1; k++)
            {
                printf(" ");
            }
            printf("|\n");
            current = current->suivant;
        }
        printf("+");
        for (int k = 0; k < max*1.5; k++)
        {
            printf("-");
        }
        printf("+");
        for (int k = 0; k < LEN_MAX_PRIX*1.5; k++)
        {
            printf("-");
        }
        printf("+");
        for (int k = 0; k < LEN_MAX_QTE*1.5; k++)
        {
            printf("-");
        }
        printf(("+\n"));
    }
}



/* **************************************
 * Suppression d'un produit dans un rayon
 ************************************** */
int supprimerProduit(T_Rayon *rayon, char* designation_produit) {
    // TODO
    return 1;
}



/* *************************************************************
 * Suppression d'un rayon et de tous les produits qu'il contient
 ************************************************************* */
int supprimerRayon(T_Magasin *magasin, char *nom_rayon) {
    // TODO
    return 1;
}



/* **************************************************************************************
 * Recherche des produits se situant dans une fourchette de prix entr�e par l'utilisateur
 ************************************************************************************** */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max) {
    // TODO
}



/* *********************
 * Fusionner deux rayons
 ********************* */
void fusionnerRayons(T_Magasin *magasin) {
    // TODO
}


/* ******************************
 * Vérifier si le magasin existe
 ****************************** */
bool isStoreSet(T_Magasin *magasin, bool shouldWarnUser) {
    bool isStoreSet = (bool) magasin;

    if(! isStoreSet) {
        printf("\nAucun magasin n'existe ! ");
        return false;
    }

    return true;
}

/* *********************
 * Fonctions utilitaires
 ********************* */
// Vider le buffer (utile quand on utlise des getchar() )
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

// Fonction pour vider l'écran (normalement imlémentée via de base clrscr(), mais ne fonctionne pas)
void clear_screen(){
    printf("\e[1;1H\e[2J");
}

// Longueur d'un integer (utile pour générer un beau tableau)
int getNumLength(int num) {
    int length = 0;
    while (num != 0) {
        num /= 10;
        ++length;
    }
    return length;
}

int getFloatNumLength(float num) {
    int intNum = (int)num;  // convert float to integer
    int length = 0;
    while (intNum != 0) {
        intNum /= 10;
        ++length;
    }
    return length;
}

