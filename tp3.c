#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tp3.h"


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

// Fonction pour vider l'�cran (normalement iml�ment�e via de base clrscr(), mais ne fonctionne pas)
void clear_screen(){
    printf("\e[1;1H\e[2J");
}

// remplace "\n" par "\0" dans un string
void replaceNewLine_WithNullTerminator(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Longueur d'un integer (utile pour g�n�rer un beau tableau)
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


// TODO : g�n�raliser les fonctions getXInput 
// * get X input ; permet de s'assurer qu'on input bien un X + prompt l'utilisateur

/*
enum getInputTypes { STRING, INT, FLOAT };
char *getXInput(char *prompt, enum getInputTypes type, char *args){
    //* WIP
    int scanfReturn;
    float prix; //.....

    //switch en fonction du type pour param�trer le do while
    


    do {
        printf("%s", prompt);
        scanfReturn = scanf("%f", &prix);
        viderBuffer();

        if (scanfReturn == 0) {
            printf("\nERREUR : le prix doit �tre un nombre ! ");
        }
    } 
    while (scanfReturn == 0);

    return "";
}

*/
// getStringInput de string custom
char *getStringInput(char *prompt){
    printf("%s", prompt);

    char *input = malloc(sizeof(char) * 100);
    fgets(input, 100, stdin);
    replaceNewLine_WithNullTerminator(input);
    fflush(stdin); // TODO : v�rifier si utile
    
    return input;
}

// Ppermet de s'assurer qu'on input bien un float
float getFloatInput(char *prompt){
    int scanfReturn;
    float prix;

    do {
        printf("%s", prompt);
        scanfReturn = scanf("%f", &prix);
        viderBuffer();

        if (scanfReturn == 0) {
            printf("\nERREUR : le prix doit �tre un nombre ! ");
        }
    } 
    while (scanfReturn == 0);

    return prix;
}

// gPermet de s'assurer qu'on input bien un int
int getIntInput(char *prompt){
    int scanfReturn;
    int prix;

    do {
        printf("%s", prompt);
        scanfReturn = scanf("%d", &prix);
        viderBuffer();

        if (scanfReturn == 0) {
            printf("\nERREUR : le prix doit �tre un nombre ! ");
        }
    } 
    while (scanfReturn == 0);

    return prix;
}

// Fonction pour v�rifier si un char est dans un tableau de char
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


/* **********************************
 * Cr�ation et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite) {
    if(quantite <= 0) return NULL;


    T_Produit *nouveauProduit = NULL;

    nouveauProduit = malloc(sizeof(T_Produit));
    if (nouveauProduit == NULL) return NULL; // l'allocation m�moire n'a pas pu se faire


    nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace m�moire d�di� pour notre champ de structure
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
        // l'allocation m?moire s'est bien pass?e
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
    // TODO : Attention � bien v�rifier toutes les valeurs que peut prendre "magasin"

    T_Rayon *rayonPrecedent = NULL;
    T_Rayon *rayonCourant = magasin->liste_rayons;

    // On parcourt toute la liste jusqu'� trouver un mot plus grand ou la fin de la liste
    while (rayonCourant != NULL && strcmp(rayonCourant->nom_rayon, nomRayon) < 0)
    {
        rayonPrecedent = rayonCourant;
        rayonCourant = rayonCourant->suivant;
    }

    // Test si rayon existe d�j�
    if (rayonCourant != NULL && strcmp(rayonCourant->nom_rayon, nomRayon) == 0)
    {
        printf("Le rayon existe d�j�.\n");
        return 0;
    }

    // Ok pour ins�rer 

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

    //* V�rification si le produit existe d�j� dans le rayon
    T_Produit *produit = rayon->liste_produits;
    while (produit != NULL) {
        if (strcmp(produit->designation, designation) == 0) {

            // Le produit existe d�j�, on augmente simplement sa quantite et demande si prix modifie ou pas
            printf("Un produit avec le m�me nom existe d�j�.\n");
            printf("Vouz aurez le choix entre augmenter sa quantit� et/ou modifier son prix si vous avez rentr� un prix diff�rent de l'ancien.\n");
            printf("Si vous souhaitez le remplacer avec la nouvelle quantit� et prix, supprimez-le et cr�ez-en un nouveau.\n");

            char reponse = 'n'; // Intialisation
            do
            {
                if(reponse != 'o' && reponse != 'n') 
                {
                    printf("\nERREUR : seulement 'o' et 'n' sont accept�s en r�ponse ! ");
                }
                printf("\nVoulez-vous simplement augmenter sa quantit� ? (o/n) ");
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
                            printf("\nERREUR : seulement 'o' et 'n' sont accept�s en r�ponse !\n ");
                        }
                        printf("Souhaitez-vous modifier son prix (o/n) ? Ancien prix: %f\n", produit->prix);
                        reponse = getchar();
                        viderBuffer();
                    } while (reponse != 'o' && reponse != 'n');

                    if (reponse == 'o') // On supprime le produit et insere avec qt� augment�e et prix diff�rent pour avoix la liste encore tri�e
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


    //* Cr�ation du nouveau produit
    T_Produit *nouveauProduit = creerProduit(designation, prix, quantite);


    //* Insertion du nouveau produit dans le rayon, en respectant l'ordre croissant des prix
    T_Produit *produitPrecedent = NULL;
    T_Produit *produitCourant = rayon->liste_produits;

    // tant qu'on trouve un prix inf�rieur au produit courant, on avance dans le rayon 
    while (produitCourant != NULL && produitCourant->prix < prix) {
        produitPrecedent = produitCourant;
        produitCourant = produitCourant->suivant;
    }

    // On vient de d�passer le dernier produit au prix < au prix courant. On ins�re 
    if(produitPrecedent == NULL)
    {
        nouveauProduit->suivant = rayon->liste_produits;
        rayon->liste_produits = nouveauProduit;
    }

    else produitPrecedent->suivant = nouveauProduit;

    nouveauProduit->suivant = produitCourant; // Pour bien marquer la fin

    return 1; // Succ�s de l'ajout
}




/* **********************************************
 * Ajout produit dans la nouvelle structure rayon
 ********************************************* */
void ajouterProduit_RayonTemp(T_Rayon_Temp **rayontemp, char *designation, float prix, int quantite, char *nom_rayon) {

    // Si la liste est vide, c��d designation = "-1" on ajoute directement le produit
    if (strcmp((*rayontemp)->designation, "-1") == 0) {
    (*rayontemp)->designation = malloc(strlen(designation) + 1);
    strcpy((*rayontemp)->designation, designation);
    (*rayontemp)->prix = prix;
    (*rayontemp)->quantite_en_stock = quantite;
    (*rayontemp)->rayon = malloc(strlen(nom_rayon) + 1);
    strcpy((*rayontemp)->rayon, nom_rayon);
    (*rayontemp)->suivant = NULL;
    return;
    }

    // Sinon tant qu'on trouve un prix inf�rieur au produit courant, on avance dans le rayon 
    T_Rayon_Temp *current = *rayontemp;
    T_Rayon_Temp *precedent = NULL;
    while (current != NULL && current->prix < prix) {
        precedent = current;
        current = current->suivant;
    }

    // On cr�e un nouveau produit �� ins�rer
    T_Rayon_Temp *nouveau = malloc(sizeof(T_Rayon_Temp));
    nouveau->designation = malloc(strlen(designation) + 1);
    strcpy(nouveau->designation, designation);
    nouveau->prix = prix;
    nouveau->quantite_en_stock = quantite;
    nouveau->rayon = malloc(strlen(nom_rayon) + 1);
    strcpy(nouveau->rayon, nom_rayon);
    nouveau->suivant = NULL;

    if (precedent == NULL) { // Si insertion en t�te
        nouveau->suivant = *rayontemp;
        *rayontemp = nouveau;
    }

    else {
        nouveau->suivant = current;
        precedent->suivant = nouveau;
    }
}




/* *****************************************
 * R�cup�ration du nom de rayon le plus long
 ***************************************** */
char *getLongestDeptName(T_Magasin *magasin) {
    T_Rayon *rayons;
    rayons = magasin->liste_rayons;

    char *longestDeptName = NULL;
    int max = 0, currentRayonLength = 0;
    while (rayons != NULL)
    {   
        currentRayonLength = strlen(rayons->nom_rayon);
        if (currentRayonLength <= max) {
            rayons = rayons->suivant;
            continue;
        }

        max = currentRayonLength;
        longestDeptName = malloc(max + 1);
        strcpy(longestDeptName, rayons->nom_rayon);
        rayons = rayons->suivant;
    }

    return longestDeptName;
}


/* *****************************************
 * Compter le nombre de produits d'un rayon
 ***************************************** */
int compterProduits(T_Rayon *rayon) {
    int nbProduits = 0;
    T_Produit *produits = rayon->liste_produits;
    while (produits != NULL) {
        nbProduits++;
        produits = produits->suivant;
    }

    return nbProduits;
}

/* *****************************************************
 * afficher caract�re de s�paration d'un tableau affich�
 **************************************************** */
char * getRepeatedChar(int nbCaracteres, char separateur) {
    if(nbCaracteres <= 0) return "";
    // Allouer de la m�moire pour la cha�ne de caract�res
    char *resultat = (char *) malloc(nbCaracteres + 1);
    if (resultat == NULL) return NULL;

    // Initialiser la cha�ne de caract�res avec le caract�re s�parateur r�p�t� nbCaracteres fois
    memset(resultat, separateur, nbCaracteres);

    resultat[nbCaracteres] = '\0';

    return resultat;
}
char * getSeparationLine(int nbCaracteres) {
    return getRepeatedChar(nbCaracteres, '-');
}


/* **********************
 * Affichage d'un tableau
 ********************** */
void afficherTableau(char ***tableaux) {
    int i, j, k;

    // TODO : que faire si entrée d'un tableau vide ?

    //* Calcul des dimensions
    int nb_colonnes = 0;
    int nb_rangees = 0;
    int nbMax_lignes = 0;

    // Calcul nombre de colonnes
    while (tableaux[nb_colonnes] != NULL) {
        nb_colonnes++;
    }


    // Calcul le nombre de rangées du tableau + largeur des colonnes
    int largeur_colonne[nb_colonnes];
    int hauteur_colonnes[nb_colonnes];

    for (i = 0; i < nb_colonnes; i++) {
        largeur_colonne[i] = 0;
        nb_rangees = 0;

        while (tableaux[i][nb_rangees] != NULL) {
            if (strlen(tableaux[i][nb_rangees]) > largeur_colonne[i]) {
                largeur_colonne[i] = strlen(tableaux[i][nb_rangees]);
            }
            nb_rangees++;
        }

        if (nb_rangees > nbMax_lignes) nbMax_lignes = nb_rangees;
        hauteur_colonnes[i] = nb_rangees;
    }

    


    //* Affichage du tableau
    // Affichage de la première ligne
    printf("+");
    for (i = 0; i < nb_colonnes; i++) {
        for (j = 0; j < largeur_colonne[i] + 2; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Affichage des entêtes de colonne
    printf("|");
    for (i = 0; i < nb_colonnes; i++) {
        printf(" %-*s |", largeur_colonne[i], tableaux[i][0]);
        // comprendre %-*s : https://stackoverflow.com/questions/23776824/what-is-the-meaning-of-s-in-a-printf-format-string 
    }
    printf("\n");

    // Affichage de la ligne de séparation
    printf("+");
    for (i = 0; i < nb_colonnes; i++) {
        for (j = 0; j < largeur_colonne[i] + 2; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Affichage du contenu de la colonne
    for (i = 0; i < nbMax_lignes - 1; i++) {
        printf("|");
        for (j = 0; j < nb_colonnes; j++) {

            if( tableaux[j][i+1] == NULL || i >= hauteur_colonnes[j] ) { // si on sort des valeurs de la colonnes courante (AKA si on atteint ou dépasse NULL)
                printf(" %-*s |", largeur_colonne[j], "");
                continue;
            } 

            printf(" %-*s |", largeur_colonne[j], tableaux[j][i+1]);
        }
        printf("\n");
    }

    // Affichage de la dernière ligne
    printf("+");
    for (i = 0; i < nb_colonnes; i++) {
        for (j = 0; j < largeur_colonne[i] + 2; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    return;
}

/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasinGenerique(T_Magasin *magasin, bool shouldShowNbProducts) {
    if(! isAnyDeptSet(magasin, true)) return;

    T_Rayon *rayons;
    rayons = magasin->liste_rayons;
    
    int nbProduits;
    T_Produit *produit;

    if(shouldShowNbProducts) printf("\nAffichage des rayons du magasin \"%s\"\n", magasin->nom);

    // Récupérer le nom des rayons ainsi que le nombre de produits dans chaque rayon
    char *nomRayons[99] = {"Rayons"};
    char *nbProduitsParRayon[99] = {"Nombre produits"}; // TODO : inutile dans le cas du ! shouldShowNbProducts
    int rayonCourant = 0;
    while (rayons != NULL) {

        if(shouldShowNbProducts){
            // récupérer le nombre de produits dans le rayon
            nbProduits = 0;
            produit = rayons->liste_produits;
            while (produit != NULL) {
                nbProduits++;
                produit = produit->suivant;
            }
        }

        // Ajouter le nom du rayon et le nombre de produits dans le tableau
        nomRayons[rayonCourant + 1] = rayons->nom_rayon;
        if(shouldShowNbProducts){
            char *nbProduitsStr = malloc(sizeof(char) * 9); // Allouer de la mémoire pour la chaîne
            sprintf(nbProduitsStr, "%d", nbProduits);
            nbProduitsParRayon[rayonCourant + 1] = nbProduitsStr;
        }

        rayons = rayons->suivant;
        rayonCourant++;
    }

    nomRayons[rayonCourant + 1] = NULL;
    if(shouldShowNbProducts) nbProduitsParRayon[rayonCourant + 1] = NULL;


    // TODO : rendre cette partie plus élégante 
    // (j'ai essayé un opérateur ternaire pour l'assignation de valeur à tableaux, mais ça ne fonctionne pas)
    if(shouldShowNbProducts) {
        char **tableaux[] = {nomRayons, nbProduitsParRayon, NULL};
        afficherTableau(tableaux);
    }
    else {
        char **tableaux[] = {nomRayons, NULL};
        afficherTableau(tableaux);
    }

}

void afficherMagasin(T_Magasin *magasin) { 
    afficherMagasinGenerique(magasin, true); 
}

void afficherRayons(T_Magasin *magasin){ 
    afficherMagasinGenerique(magasin, false); 
}

/* *****************************************
 * Affichage de tous les produits d'un rayon
 ***************************************** */
void afficherRayon(T_Rayon *rayon) {
    T_Produit *produits;
    produits = rayon->liste_produits;

    if(produits == NULL) {
        printf("\nLe rayon \"%s\" est vide !\n", rayon->nom_rayon);
        return;
    }

    printf("\nAffichage des produits du rayon \"%s\"\n", rayon->nom_rayon);

    // Récupérer le nom des produits ainsi que leur prix et quantité
    char *nomProduits[99] = {"Designation"};
    char *prixProduits[99] = {"Prix"};
    char *quantiteProduits[99] = {"Quantité en stock"};

    int produitCourant = 0;
    char prixProduitStr[9];
    char quantiteProduitStr[9];
    while (produits != NULL) {

        // Ajouter le nom du produit, son prix et sa quantité dans le tableau
        nomProduits[produitCourant + 1] = produits->designation;

        prixProduits[produitCourant + 1] = (char*) malloc(sizeof(char) * 9); // Allouer de la mémoire pour la chaîne de caractères
        sprintf(prixProduitStr, "%.2f", produits->prix);
        strcpy(prixProduits[produitCourant + 1], prixProduitStr); // Copier la valeur de prixProduitStr dans la nouvelle zone mémoire

        quantiteProduits[produitCourant + 1] = (char*) malloc(sizeof(char) * 9); // Allouer de la mémoire pour la chaîne de caractères
        sprintf(quantiteProduitStr, "%d", produits->quantite_en_stock );
        strcpy(quantiteProduits[produitCourant + 1], quantiteProduitStr); // Copier la valeur de quantiteProduitStr dans la nouvelle zone mémoire

        produits = produits->suivant;
        produitCourant++;
    }


    nomProduits[produitCourant + 1] = NULL;
    prixProduits[produitCourant + 1] = NULL;
    quantiteProduits[produitCourant + 1] = NULL;

    char **tableaux[] = {nomProduits, prixProduits, quantiteProduits, NULL};
    afficherTableau(tableaux);
}


/* ******************************
 * V�rifie si le magasin existe
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
 * V�rifie si, au sein du magasin, au moins un rayon existe
 ******************************************************** */
bool isAnyDeptSet(T_Magasin *magasin, bool shouldWarnUser) {
    if(! isStoreSet(magasin, shouldWarnUser)) return false; // Juste au cas o�, on v�rifie que le magasin soit bien d�fini.
                                                            // Si pas de magasin => pas de rayon

    if(magasin->liste_rayons == NULL) {
        if(shouldWarnUser) printf("\nAucun rayon n'existe ! ");
        return false;
    }

    return true;
}


/* **************************************************
 * Alerte pour les fonctions de r�cup�ration de rayon
 ************************************************** */
void alert_DeptDoesNotExists(char *nomRayonRecherche) {
    printf("\nLe rayon %s n'existe pas ! ", nomRayonRecherche);
}

/* ***************************************************************
 * R�cup�re le T_Rayon correspondant au nom pass� en param�tre
 ************************************************************** */
T_Rayon *getDeptByName(T_Magasin *magasin, char *nomRayon, bool shouldWarnUser) {
    T_Rayon *rayonCourant = magasin->liste_rayons;


    while(rayonCourant != NULL) {
        printf("Dans getDeptByName : %ss", rayonCourant->nom_rayon);

        if(strcmp(rayonCourant->nom_rayon, nomRayon) == 0) return rayonCourant;
        rayonCourant = rayonCourant->suivant;
    }
    printf("\n");

    if(shouldWarnUser) alert_DeptDoesNotExists(nomRayon);
    return NULL;
}


/* ***************************************************************
 * V�rifie si, au sein du magasin, le rayon pass� en param existe
 ************************************************************** */
bool isDeptSet(T_Magasin *magasin, char *nomRayon, bool shouldWarnUser) {
    if(! isAnyDeptSet(magasin, shouldWarnUser)) return false;   // Juste au cas o�, on v�rifie qu'au moins un rayon soit bien d�fini.

    T_Rayon *rayon = getDeptByName(magasin, nomRayon, false);
    if(rayon != NULL) return true;

    if(shouldWarnUser) alert_DeptDoesNotExists(nomRayon);
    return false;
}

/* **************************************
 * Suppression d'un produit dans un rayon
 ************************************** */
int supprimerProduit(T_Rayon *rayon, char* designation_produit) {

    T_Produit *produitprecedent = NULL;
    T_Produit *produitcurrent = rayon->liste_produits;

    // Si le produit est au d�but
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

    T_Rayon *rayonCourant = magasin->liste_rayons;
    T_Rayon *rayonprecedent = NULL;
    T_Produit *produitcurrent = NULL;

    // Si le rayon est au d�but
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
 * Recherche des produits se situant dans une fourchette de prix entr?e par l'utilisateur
 ************************************************************************************** */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max) {

    T_Rayon *rayon_current = magasin->liste_rayons;
    T_Produit *produit_current;

    T_Rayon_Temp *rayontemp = NULL; // T�te de la liste �� afficher
    rayontemp = malloc(sizeof(T_Rayon_Temp));
    rayontemp->designation = malloc(strlen("-1") + 1); // On initialise �� -1 pour savoir s'il est vide ou pas
    strcpy(rayontemp->designation, "-1");
    rayontemp->suivant = NULL;


    // On initialise celui que l'on va it�rer, pour conserver le d�but dans rayontemp
    T_Rayon_Temp *rayontemp_current = NULL;
    rayontemp_current = malloc(sizeof(T_Rayon_Temp));
    rayontemp_current->suivant = NULL;

    while (rayon_current != NULL) // Parcourir les rayons
    {   
        produit_current = rayon_current->liste_produits;
        while (produit_current != NULL) // Itérer sur les produits du rayon
        {   
            if (produit_current->prix >= prix_min && produit_current->prix <= prix_max) // Si c'est le bon produit
            {   
                ajouterProduit_RayonTemp(&rayontemp, produit_current->designation, produit_current->prix, produit_current->quantite_en_stock, rayon_current->nom_rayon);
            }
            
            produit_current = produit_current->suivant;
        }
        rayon_current = rayon_current->suivant;
    }

    // A cette étape nous avons construit la liste chain�e et elle est pr�te � �tre print

    rayontemp_current = rayontemp; // On revient dans la t�te. On utilise current pour ne pas perdre la t�te pour free la m�moire apr�s

    // Afficher comme: Marque | Prix | Quantit� en stock | Rayon 
    // Normalement c'est d�j�� tri� par prix croissant

    while (rayontemp_current != NULL)
    {
        printf("%s --- %.2f --- %d --- %s\n", rayontemp_current->designation, rayontemp_current->prix, rayontemp_current->quantite_en_stock, rayontemp_current->rayon);
        rayontemp_current = rayontemp_current->suivant;
    }
    // On lib�re la m�moire du rayon temporaire cr��

    rayontemp_current = rayontemp;
    while (rayontemp_current != NULL)
    {   
        T_Rayon_Temp *tofree;
        tofree = rayontemp_current;
        rayontemp_current = rayontemp_current->suivant;
        free(tofree->designation);
        free(tofree->rayon);
        free(tofree);
    }
    free(rayontemp_current);
}



/* *********************
 * Fusionner deux rayons
 ********************* */
void fusionnerRayons(T_Magasin *magasin) {

    char *nom_rayon_1 = getStringInput("\nNom du rayon 1? ");
    char *nom_rayon_2 = getStringInput("\nNom du rayon 2 ? ");
    char *nom_resultant = getStringInput("\nNom du rayon r�sultant?");

    if (isDeptSet(magasin, nom_rayon_1, false) && isDeptSet(magasin, nom_rayon_2, false)) // Si les 2 rayons existent
    {
        printf("ISDEPTSET");
        // Identification des rayons �� fusionner
        T_Rayon *rayon_1 = getDeptByName(magasin, nom_rayon_1, true);
        T_Rayon *rayon_2 = getDeptByName(magasin, nom_rayon_2, true);
        
        T_Produit *prayon_1 = rayon_1->liste_produits;
        T_Produit *prayon_2 = rayon_2->liste_produits;

        // Ca va nous permettre de cr�er le nouveau rayon avec le m�me nom de ceux pr�c�dents
        // On remplace leur nom. De toute fa�on on les supprime apr�s

        strcpy(rayon_1->nom_rayon, "x");
        strcpy(rayon_2->nom_rayon, "xx");

        // Cr�ation et identification du nouveau rayon
        ajouterRayon(magasin, nom_resultant);
        T_Rayon *rayon_resultant = getDeptByName(magasin, nom_resultant, true);

        // Regarder si un des rayons est vide

        
        // Juste pour regrouper les cas particuliers avec if..else
        // TODO : virer le gros if, de set des flag dans les petits else if (que tu peux transformes en if) 
        // TODO : et le gros else (celui juste après ce sreen) se transforme en  if declenché par le flag
        if ((prayon_1 == NULL && prayon_2 == NULL) || (prayon_1 != NULL && prayon_2 == NULL) || (prayon_1 == NULL && prayon_2 != NULL))
        {
            if (prayon_1 == NULL && prayon_2 == NULL)
            {
                // on ne fait rien; �� la fin on supprime les 2 rayons et on laisse juste le nouveau
            }

            else if (prayon_1 != NULL && prayon_2 == NULL)
            {
                rayon_resultant->liste_produits = prayon_1;
            }

            else if (prayon_1 == NULL && prayon_2 != NULL)
            {
                rayon_resultant->liste_produits = prayon_2;
            }
        }

        else 
        {
            // Marquer le d�but du rayon avec le produit le moins cher
            if (prayon_1->prix >= prayon_2->prix)
            {
                rayon_resultant->liste_produits = prayon_2;
                prayon_2 = prayon_2->suivant;
            }

            else
            {
                rayon_resultant->liste_produits = prayon_1;
                prayon_1 = prayon_1->suivant;
            }

            T_Produit *buffer = rayon_resultant->liste_produits;

            while (prayon_1 != NULL && prayon_2 != NULL)
            {
                if (prayon_1->prix >= prayon_2->prix)
                {   
                    buffer->suivant = prayon_2;
                    buffer = prayon_2;
                    prayon_2 = prayon_2->suivant;
                }

                else
                {
                    buffer->suivant = prayon_1;
                    buffer = prayon_1;
                    prayon_1 = prayon_1->suivant;
                }
            }

            if (prayon_1 == NULL && prayon_2 != NULL)
            {
                buffer->suivant = prayon_2;
            }

            if (prayon_1 != NULL && prayon_2 == NULL)
            {
                buffer->suivant = prayon_1;
            }
        }
        // Dans TOUS LES CAS:
        // On supprime ces rayons
        // Ils vont quand m�me pointer sur le premier produit, on met NULL pour pas supprimer les produits avec
        rayon_1->liste_produits = NULL;
        rayon_2->liste_produits = NULL;

        supprimerRayon(magasin, "x");
        supprimerRayon(magasin, "xx");

        free(nom_rayon_1);
        free(nom_rayon_2);
        free(nom_resultant);
    }
    
    // Sinon si au moins un n'existe pas
    else
    {
        printf("ERREUR: l'un des rayons (ou les 2) est inexistant.");
    }
}


