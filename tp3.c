#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"


/* **********************************
 * Cr�ation et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite) {
    T_Produit *nouveauProduit = NULL;

    nouveauProduit = malloc(sizeof(T_Produit));
    if (nouveauProduit != NULL) {
        // l'allocation m�moire s'est bien pass�e
        nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace m�moire d�di� pour notre champ de structure
        strcpy(nouveauProduit->designation,designation);
        nouveauProduit->prix = prix;
        nouveauProduit->quantite_en_stock = quantite;
        nouveauProduit->suivant = NULL;
    }

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
    if (magasin == NULL)
    {
        printf("Magasin inexistant.\n");
    }

    T_Rayon *precedent = NULL;
    T_Rayon *current = magasin->liste_rayons;

    // On parcourt toute la liste jusqu'à trouver un mot plus grand ou la fin de la liste
    while (current != NULL && strcmp(current->nom_rayon, nomRayon) < 0)
    {
        precedent = current;
        current = current->suivant;
    }

    // Test si rayon existe déjà
    if (current != NULL && strcmp(current->nom_rayon, nomRayon) == 0)
    {
        printf("Le rayon existe déjà.\n");
        return 0;
    }

    // Ok pour insérer 

    T_Rayon *nouveau = creerRayon(nomRayon);

    if (precedent == NULL)
    {
        magasin->liste_rayons = nouveau;
    }
    else
    {
        precedent->suivant = nouveau;
    }

    nouveau->suivant = current; // Pour bien marquer la fin
    return 1;
}



/* ********************************
 * Ajout d'un produit dans un rayon
 ******************************** */
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite) {

    // // Vérification si le produit existe déjà dans le rayon
    // T_Produit *produit = rayon->premierProduit;
    // while (produit != NULL) {
    //     if (strcmp(produit->designation, designation) == 0) {
    //         return 0; // Le produit existe déjà, on ne peut pas l'ajouter
    //     }
    //     produit = produit->produitSuivant;
    // }

    // // Création du nouveau produit
    // T_Produit *nouveauProduit = (T_Produit*) malloc(sizeof(T_Produit));
    // if (nouveauProduit == NULL) {
    //     return 0; // Echec de l'allocation de mémoire
    // }
    // nouveauProduit->designation = (char*) malloc(sizeof(char) * (strlen(designation) + 1));
    // if (nouveauProduit->designation == NULL) {
    //     free(nouveauProduit);
    //     return 0; // Echec de l'allocation de mémoire
    // }
    // strcpy(nouveauProduit->designation, designation);
    // nouveauProduit->prix = prix;
    // nouveauProduit->quantite = quantite;

    // // Insertion du nouveau produit dans le rayon, en respectant l'ordre croissant des prix
    // T_Produit *produitCourant = rayon->premierProduit;
    // T_Produit *produitPrecedent = NULL;
    // while (produitCourant != NULL && produitCourant->prix < prix) {
    //     produitPrecedent = produitCourant;
    //     produitCourant = produitCourant->produitSuivant;
    // }
    // if (produitPrecedent == NULL) {
    //     nouveauProduit->produitSuivant = rayon->premierProduit;
    //     rayon->premierProduit = nouveauProduit;
    // } 
    // else {
    //     nouveauProduit->produitSuivant = produitCourant;
    //     produitPrecedent->produitSuivant = nouveauProduit;
    // }

    // return 1; // Succès de l'ajout
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
        int max = 0;
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
    // TO DO
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

// Longueur d'un integer (utile pour générer un beau tableau)

int getNumLength(int num) {
    int length = 0;
    while (num != 0) {
        num /= 10;
        ++length;
    }
    return length;
}
