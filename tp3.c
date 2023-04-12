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
    if(quantite <= 0) {
        return 0;
    }

    //* Vérification si le produit existe déjà dans le rayon
    T_Produit *produit = rayon->liste_produits;
    while (produit != NULL) {
        if (strcmp(produit->designation, designation) == 0) {

            // Le produit existe déjà, on augmente simplement sa quantite et demande si prix modifie ou pas
            printf("Un produit avec le même nom existe déjà.\n");
            printf("Vouz aurez le choix entre augmenter sa quantité et/ou modifier son prix si vous avez rentré un prix différent de l'ancien.\n");
            printf("Si vous souhaitez le remplacer avec la nouvelle quantité et prix, supprimez-le et créez-en un nouveau.\n");

            char reponse = 'n'; // Intialisation
            do
            {
                if(reponse != 'o' && reponse != 'n') 
                {
                    printf("\nERREUR : seulement 'o' et 'n' sont acceptés en réponse ! ");
                }
                printf("\nVoulez-vous simplement augmenter sa quantité ? (o/n) ");
                reponse = getchar();
                viderBuffer();
            } while (reponse != 'o' && reponse != 'n'); 

            if(reponse == 'o') 
            {
                produit->quantite_en_stock += quantite;
                if (prix != produit->prix)
                {
                    reponse = 'n'; // Intialisation
                    do
                    {
                        if(reponse != 'o' && reponse != 'n') 
                        {
                            printf("\nERREUR : seulement 'o' et 'n' sont acceptés en réponse !\n ");
                        }
                        printf("Souhaitez-vous modifier son prix (o/n) ? Ancien prix: %f\n", produit->prix);
                        reponse = getchar();
                        viderBuffer();
                    } while (reponse != 'o' && reponse != 'n');

                    if (reponse == 'o') // On supprime le produit et insere avec qté augmentée et prix différent pour avoix la liste encore triée
                    {   
                        int stockancien = produit->quantite_en_stock;
                        int testsupprim, testajout;
                        testsupprim = supprimerProduit(rayon, designation);
                        testajout = ajouterProduit(rayon, designation, prix, stockancien);

                        if (testsupprim == 1 && testajout == 1) // Si tout est ok
                        {
                            return 1;
                        }

                        else
                        {
                            return 0;
                        }
                    }

                    else
                    {
                        return 1;
                    }
                }

                return 1;
            }

            else if(reponse == 'n')
            {
                return 0;
            }
            
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
    // TODO : ajouter un paramètre booleen isSimplified pour supprimer la colonne quantité en stock 
    //          (permet de faire de l'affichage des rayons seuls), notamment pour les choix
    
    
    T_Rayon *current;
    current = magasin->liste_rayons;

    if (magasin == NULL) // TODO : utiliser isStoreSet() ?
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
            while (produit != NULL)
            {
                nb_produits++;
                produit = produit->suivant;
            }
            printf("| %s", current->nom_rayon);
            for (int k = 0; k < 1.5*max - strlen(current->nom_rayon) - 1; k++)
            {
                printf(" ");
            }
            printf("| ");
            printf("%d", nb_produits);
            for (int k = 0; k < strlen(" Nombre de produits") - getNumLength(nb_produits); k++)
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
        for (int k = 0; k < LEN_MAX_QTE*1.5 - strlen("| Quantité en stock ") + 2; k++) // Si temps faire dynamique en fonction du plus grand qté
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

    // Si le rayon n'existe pas
    if (rayon == NULL)
    {
        printf("Rayon inexistant.\n");
        return 0;
    }

    // Si le rayon est vide
    if (rayon->liste_produits == NULL)
    {
        printf("Rayon vide.\n");
        return 0;
    }

    T_Produit *produitprecedent = NULL;
    T_Produit *produitcurrent = rayon->liste_produits;

    // Si le produit est au début
    if (produitcurrent != NULL && strcasecmp(produitcurrent->designation, designation_produit) == 0)
    {
        rayon->liste_produits = produitcurrent->suivant;
        free(produitcurrent);
        return 1;
    }

    while (produitcurrent != NULL)
    {
        if (strcasecmp(produitcurrent->designation, designation_produit) == 0)
        {
            produitprecedent->suivant = produitcurrent->suivant;
            free(produitcurrent);
            return 1;
        }

        produitprecedent = produitcurrent;
        produitcurrent = produitcurrent->suivant;
    }

    printf("ERREUR: Le produit n'est pas dans ce rayon.\n");
    return 0;
}



/* *************************************************************
 * Suppression d'un rayon et de tous les produits qu'il contient
 ************************************************************* */
int supprimerRayon(T_Magasin *magasin, char *nom_rayon) {
    
    if (magasin == NULL)
    {   
        printf("Magasin inexistant.");
        return 0;
    }

    if (magasin->liste_rayons == NULL)
    {
        printf("Magasin vide.");
        return 0;
    }

    T_Rayon *rayonCourant = magasin->liste_rayons;
    T_Rayon *rayonprecedent = NULL;
    T_Produit *produitcurrent = NULL;

    // Si le rayon est au début
    if (rayonCourant != NULL && strcasecmp(rayonCourant->nom_rayon, nom_rayon) == 0)
    {
        magasin->liste_rayons = rayonCourant->suivant;
        produitcurrent = rayonCourant->liste_produits;
        while (produitcurrent != NULL)
        {
            free(produitcurrent);
            produitcurrent = produitcurrent->suivant;
        }
        free(rayonCourant);
        return 1;
    }

    while (rayonCourant != NULL)
    {
        if (strcasecmp(rayonCourant->nom_rayon, nom_rayon) == 0)
        {   
            produitcurrent = rayonCourant->liste_produits;
            while (produitcurrent != NULL)
            {
                free(produitcurrent);
                produitcurrent = produitcurrent->suivant;
            }
            rayonprecedent->suivant = rayonCourant->suivant;
            free(rayonCourant);
            return 1;
        }

        rayonprecedent = rayonCourant;
        rayonCourant = rayonCourant->suivant;
    }

    printf("ERREUR: le rayon n'existe pas.");
    return 0;
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
    // merge dept
    
}
    


/* ******************************
 * Vérifie si le magasin existe
 ****************************** */
bool isStoreSet(T_Magasin *magasin, bool shouldWarnUser) {
    bool isStoreSet = (bool) magasin;

    if(! isStoreSet) {
        if(shouldWarnUser) printf("\nAucun magasin n'existe ! ");
        return false;
    }

    return true;
}


/* *********************************************************
 * Vérifie si, au sein du magasin, au moins un rayon existe
 ******************************************************** */
bool isAnyDeptSet(T_Magasin *magasin, bool shouldWarnUser) {
    if(! isStoreSet(magasin, shouldWarnUser)) return false; // Juste au cas où, on vérifie que le magasin soit bien défini.
                                                            // Si pas de magasin => pas de rayon

    if(magasin->liste_rayons == NULL) {
        if(shouldWarnUser) printf("\nAucun rayon n'existe ! ");
        return false;
    }

    return true;
}

/* *********************************************************
 * Vérifie si, au sein du magasin, au moins un rayon existe
 ******************************************************** */


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

// remplace "\n" par "\0" dans un string
void replaceNewLine_WithNullTerminator(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Longueur d'un integer (utile pour générer un beau tableau)
int getNumLength(int num) {
    int length = 0;

    if (num == 0)
    {
        return 1;
    }

    while (num != 0) {
        num /= 10;
        ++length;
    }
    return length;
}

// Longueur d'un float
int getFloatNumLength(float num) {
    int intNum = (int)num;  // convert float to integer
    int length = 0;

    if (intNum == 0)
    {
        return 1;
    }

    while (intNum != 0) {
        intNum /= 10;
        ++length;
    }
    return length;
}

// getStringInput de string custom
char *getStringInput(char *prompt){
    char *input = malloc(sizeof(char) * 100);
    printf("%s", prompt);
    fgets(input, 100, stdin);
    replaceNewLine_WithNullTerminator(input);
    fflush(stdin); // TODO : vérifier si utile
    return input;
}


bool isCharInArray(char c, char *array) {
    int i = 0;
    while (array[i] != '\0') {
        if (array[i] == c) {
            return true;
        }
        i++;
    }
    return false;
}