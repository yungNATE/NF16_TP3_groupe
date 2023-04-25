#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tp3.h"


/* *********************
 * Fonctions utilitaires
 ********************* */
char *getStringInput(char *prompt){
    printf("%s", prompt);

    char *input = malloc(sizeof(char) * 100);
    fgets(input, 100, stdin);
    replaceNewLine_WithNullTerminator(input);
    
    return input;
}
float getFloatInput(char *prompt){
    int scanfReturn;
    float prix;

    do {
        printf("%s", prompt);
        scanfReturn = scanf("%f", &prix);
        viderBuffer();

        if (scanfReturn == 0) {
            printf("\nERREUR : le prix doit être un nombre ! ");
        }
    } 
    while (scanfReturn == 0);

    return prix;
}
int getIntInput(char *prompt){
    int scanfReturn;
    int prix;

    do {
        printf("%s", prompt);
        scanfReturn = scanf("%d", &prix);
        viderBuffer();

        if (scanfReturn == 0) {
            printf("\nERREUR : le prix doit être un nombre ! ");
        }
    } 
    while (scanfReturn == 0);

    return prix;
}

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
void replaceNewLine_WithNullTerminator(char *str) {
    str[strcspn(str, "\n")] = '\0';
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
char *getCaractereRepete(int nbCaracteres, char car) {
    if(nbCaracteres <= 0) return "";
    // Allouer de la mémoire pour la chaéne de caractéres
    char *resultat = (char *) malloc(nbCaracteres + 1);
    if (resultat == NULL) return NULL;

    // Initialiser la chaéne de caractéres avec le caractére séparateur répété nbCaracteres fois
    memset(resultat, car, nbCaracteres);

    resultat[nbCaracteres] = '\0';

    return resultat;
}
void afficherTableau(char ***tableaux) {
    // ATTENTION : Le tableau inséré doit être terminé par NULL ainsi que chacun de ses sous tableaux
    // EXEMPLE : char ***tableaux[] = {  {"Toto", NULL}, NULL } // tableau d'une colonne vide nommée "Toto"
    int i, j, k;

    //* Calcul des dimensions
    int nb_colonnes = 0;
    int nb_rangees = 0;
    int nbMax_rangees = 0;

    // Calcul nombre de colonnes
    while (tableaux[nb_colonnes] != NULL) {
        nb_colonnes++;
    }

    if(nb_colonnes == 0) return; // aucun tableau (colonnes) inséré dans tableaux[] | EX : tableaux == {NULL}

    // Calcul le nombre de rangées du tableau + largeur des colonnes
    int largeur_colonne[nb_colonnes];
    int largeur_totale_colonnes = 0;
    int hauteur_colonnes[nb_colonnes];

    for (i = 0; i < nb_colonnes; i++) {
        largeur_colonne[i] = 0;
        nb_rangees = 0;

        while (tableaux[i][nb_rangees] != NULL) {
            largeur_totale_colonnes += strlen(tableaux[i][nb_rangees]) + 1;

            if (strlen(tableaux[i][nb_rangees]) > largeur_colonne[i]) {
                largeur_colonne[i] = strlen(tableaux[i][nb_rangees]);
            }
            nb_rangees++;
        }

        if (nb_rangees > nbMax_rangees) nbMax_rangees = nb_rangees;
        hauteur_colonnes[i] = nb_rangees;
    }

    if(nbMax_rangees == 0) return; // Les tableaux insérés dans tableaux[] sont vides | EX : tableaux == {{NULL}, {NULL}, {NULL}}

    //* Affichage du tableau
    const char charLigne   = '-';
    const char charCoin    = '+';
    const char charColonne = '|';

    // construction des lignes de séparation
    char* ligne = malloc((largeur_totale_colonnes + 1) * sizeof(char));
    if (ligne == NULL) {
        printf("Erreur : impossible d'allouer de la mémoire.\n");
        exit(1);
    }
    int pos = 0;
    ligne[pos++] = charCoin;
    for (i = 0; i < nb_colonnes; i++) {
        pos += sprintf(&ligne[pos], "%s", getCaractereRepete(largeur_colonne[i] + 2, '-'));
        ligne[pos++] = charCoin;
    }
    ligne[pos++] = '\n';
    ligne[pos] = '\0';

    // Affichage de la première ligne
    printf("%s", ligne);

    // Affichage des entêtes de colonne
    printf("%c", charColonne);
    for (i = 0; i < nb_colonnes; i++) {
        printf(" %-*s |", largeur_colonne[i], tableaux[i][0]);
        // comprendre %-*s : https://stackoverflow.com/questions/23776824/what-is-the-meaning-of-s-in-a-printf-format-string 
    }
    printf("\n");

    // Affichage de la ligne de séparation
    printf("%s", ligne);


    // Affichage du contenu de la colonne
    for (i = 0; i < nbMax_rangees - 1; i++) {
        printf("%c", charColonne);
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
    printf("%s", ligne);

    free(ligne);

    return;
}



/* **********************************
 * Création et initialisation Produit
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
 * Création et initialisation Rayon
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
 * Création et initialisation Magasin
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



/* *********************************************************************************
 * Vérification de la présence / récuparation de rayons au sein du magasin
 ******************************************************************************** */
void alert_leRayonNExistePas(char *nomRayonRecherche) {
    printf("\nLe rayon %s n'existe pas ! ", nomRayonRecherche);
}
T_Rayon *getRayonParNom(T_Magasin *magasin, char *nomRayon, bool shouldWarnUser) {
    T_Rayon *rayonCourant = magasin->liste_rayons;


    while(rayonCourant != NULL) {
        if(strcmp(rayonCourant->nom_rayon, nomRayon) == 0) return rayonCourant;
        rayonCourant = rayonCourant->suivant;
    }
    printf("\n");

    if(shouldWarnUser) alert_leRayonNExistePas(nomRayon);
    return NULL;
}
bool isDeptSet(T_Magasin *magasin, char *nomRayon, bool shouldWarnUser) {
    if(! isAnyRayonSet(magasin, shouldWarnUser)) return false;   // Juste au cas oé, on vérifie qu'au moins un rayon soit bien défini.

    T_Rayon *rayon = getRayonParNom(magasin, nomRayon, false);
    if(rayon != NULL) return true;

    if(shouldWarnUser) alert_leRayonNExistePas(nomRayon);
    return false;
}



/* ********************************
 * Ajout d'un rayon dans un magasin
 ******************************** */
int ajouterRayon(T_Magasin *magasin, char *nomRayon) {
    T_Rayon *rayonPrecedent = NULL;
    T_Rayon *rayonCourant = magasin->liste_rayons;

    // On parcourt toute la liste jusqu'à trouver un mot plus grand ou la fin de la liste
    while (rayonCourant != NULL && strcmp(rayonCourant->nom_rayon, nomRayon) < 0)
    {
        rayonPrecedent = rayonCourant;
        rayonCourant = rayonCourant->suivant;
    }

    // Test si rayon existe déjé
    if (rayonCourant != NULL && strcmp(rayonCourant->nom_rayon, nomRayon) == 0)
    {
        printf("Le rayon %s existe déjà.\n", nomRayon);
        return 0;
    }

    // Ok pour insérer 

    T_Rayon *nouveauRayon = creerRayon(nomRayon);

    if(rayonPrecedent == NULL)
        magasin->liste_rayons = nouveauRayon;
    else
        rayonPrecedent->suivant = nouveauRayon;

    nouveauRayon->suivant = rayonCourant; // Pour bien marquer la fin

    printf("\nRayon %s ajouté !", nomRayon);

    return 1;
}



/* ********************************
 * Ajout d'un produit dans un rayon
 ******************************** */
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite) {
    if(quantite <= 0) { return 0; }

    //* Vérification si le produit existe déjà dans le rayon
    T_Produit *produit = rayon->liste_produits;
    while (produit != NULL) {
        if (strcmp(produit->designation, designation) == 0) {

            // Le produit existe déjà, on augmente simplement sa quantite et demande si prix modifie ou pas
            printf("Un produit avec le méme nom existe déjà.\n");
            printf("Vouz aurez le choix entre augmenter sa quantité et/ou modifier son prix si vous avez rentré un prix différent de l'ancien.\n");
            printf("Si vous souhaitez le remplacer avec la nouvelle quantité et prix, supprimez-le et créez-en un nouveau.\n");

            // Incrémentation de la quentité
            char reponse = 'n'; // Intialisation
            do
            {
                if(reponse != 'o' && reponse != 'n') 
                {
                    printf("\nERREUR : seulement 'o' et 'n' sont acceptés en réponse ! ");
                }
                printf("\nVoulez-vous augmenter sa quantité ? (o/n) ");
                reponse = getchar();
                viderBuffer();
            } while (reponse != 'o' && reponse != 'n'); 

            if(reponse == 'o') { produit->quantite_en_stock += quantite; }

            // Changement du prix
            if (prix == produit->prix) { return 0; }

            reponse = 'n'; // Intialisation
            do
            {
                if(reponse != 'o' && reponse != 'n') 
                {
                    printf("\nERREUR : seulement 'o' et 'n' sont acceptés en réponse !\n ");
                }
                printf("Souhaitez-vous modifier son prix, actuellement de %.2f (o/n) ? ", produit->prix);
                reponse = getchar();
                viderBuffer();
            } while (reponse != 'o' && reponse != 'n');

            if (reponse == 'o') // On supprime le produit et insere avec qté augmentée et prix différent pour avoir la liste encore triée
            {   
                int stockancien = produit->quantite_en_stock;
                int testsupprim, testajout;
                testsupprim = supprimerProduit(rayon, designation);
                testajout = ajouterProduit(rayon, designation, prix, stockancien);

                return (testsupprim == 1 && testajout == 1);
            }

            else if(reponse == 'n') { return 1; }
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

    // On vient de dépasser le dernier produit au prix < au prix courant. On insére 
    if(produitPrecedent == NULL) {
        nouveauProduit->suivant = rayon->liste_produits;
        rayon->liste_produits = nouveauProduit;
    }

    else { produitPrecedent->suivant = nouveauProduit; }

    nouveauProduit->suivant = produitCourant; // Pour bien marquer la fin

    return 1; // Succés de l'ajout
}



/* **********************************************
 * Ajout produit dans la nouvelle structure rayon
 ********************************************* */
void ajouterProduit_RayonTemp(T_Rayon_Temp **rayontemp, char *designation, float prix, int quantite, char *nom_rayon) {

    // Si la liste est vide, càd designation = "-1" on ajoute directement le produit
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

    // Sinon tant qu'on trouve un prix inférieur au produit courant, on avance dans le rayon 
    T_Rayon_Temp *current = *rayontemp;
    T_Rayon_Temp *precedent = NULL;
    while (current != NULL && current->prix < prix) {
        precedent = current;
        current = current->suivant;
    }

    // On crée un nouveau produit à insérer
    T_Rayon_Temp *nouveau = malloc(sizeof(T_Rayon_Temp));
    nouveau->designation = malloc(strlen(designation) + 1);
    strcpy(nouveau->designation, designation);
    nouveau->prix = prix;
    nouveau->quantite_en_stock = quantite;
    nouveau->rayon = malloc(strlen(nom_rayon) + 1);
    strcpy(nouveau->rayon, nom_rayon);
    nouveau->suivant = NULL;

    if (precedent == NULL) { // Si insertion en téte
        nouveau->suivant = *rayontemp;
        *rayontemp = nouveau;
    }

    else {
        nouveau->suivant = current;
        precedent->suivant = nouveau;
    }
}



/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasinGenerique(T_Magasin *magasin, bool shouldShowNbProducts) {
    if(! isAnyRayonSet(magasin, true)) return;

    T_Rayon *rayons;
    rayons = magasin->liste_rayons;
    
    int nbProduits;
    T_Produit *produit;

    if(shouldShowNbProducts) printf("\nAffichage des rayons du magasin \"%s\"\n", magasin->nom);

    // Récupérer le nom des rayons ainsi que le nombre de produits dans chaque rayon
    char *nomRayons[99] = {"Rayons"};
    char *nbProduitsStr;
    char *nbProduitsParRayon[99];
    if(shouldShowNbProducts) nbProduitsParRayon[0] = "Nombre produits";

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
            nbProduitsStr = malloc(sizeof(char) * 9); // Allouer de la mémoire pour la chaîne
            sprintf(nbProduitsStr, "%d", nbProduits);
            nbProduitsParRayon[rayonCourant + 1] = nbProduitsStr;
        }

        rayons = rayons->suivant;
        rayonCourant++;
    }

    nomRayons[rayonCourant + 1] = NULL;
    if(shouldShowNbProducts) nbProduitsParRayon[rayonCourant + 1] = NULL;


    if(shouldShowNbProducts) {
        char **tableaux[] = {nomRayons, nbProduitsParRayon, NULL};
        afficherTableau(tableaux);
        free(nbProduitsStr);
    }
    else {
        char **tableaux[] = {nomRayons, NULL};
        afficherTableau(tableaux);
    }

    return;
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
    char intToStrBuffer[9];
    while (produits != NULL) {

        // Ajouter le nom du produit, son prix et sa quantité dans le tableau
        nomProduits[produitCourant + 1] = produits->designation;                // ajout du nom du produit

        prixProduits[produitCourant + 1] = (char*) malloc(sizeof(char) * 9);    // ajout du prix du produit
        sprintf(intToStrBuffer, "%.2f", produits->prix);
        strcpy(prixProduits[produitCourant + 1], intToStrBuffer);

        quantiteProduits[produitCourant + 1] = (char*) malloc(sizeof(char) * 9);// ajout de la quantité du produit
        sprintf(intToStrBuffer, "%d", produits->quantite_en_stock );
        strcpy(quantiteProduits[produitCourant + 1], intToStrBuffer);

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
 * Vérifie si le magasin existe
 ****************************** */
bool isMagasinSet(T_Magasin *magasin, bool shouldWarnUser) {
    bool isMagasinSet = (bool) magasin;

    if(! isMagasinSet) {
        if(shouldWarnUser) printf("\nAucun magasin n'existe ! ");
        return false;
    }

    return true;
}



/* *********************************************************
 * Vérifie si, au sein du magasin, au moins un rayon existe
 ******************************************************** */
bool isAnyRayonSet(T_Magasin *magasin, bool shouldWarnUser) {
    if(! isMagasinSet(magasin, shouldWarnUser)) return false; // Juste au cas oé, on vérifie que le magasin soit bien défini.
                                                            // Si pas de magasin => pas de rayon

    if(magasin->liste_rayons == NULL) {
        if(shouldWarnUser) printf("\nAucun rayon n'existe ! ");
        return false;
    }

    return true;
}



/* **************************************
 * Suppression d'un produit dans un rayon
 ************************************** */
int supprimerProduit(T_Rayon *rayon, char* designation_produit) {

    T_Produit *produitprecedent = NULL;
    T_Produit *produitcurrent = rayon->liste_produits;

    // Si le produit est au début
    if (produitcurrent != NULL && strcmp(produitcurrent->designation, designation_produit) == 0)
    {
        rayon->liste_produits = produitcurrent->suivant;
        free(produitcurrent);
        return 1;
    }

    while (produitcurrent != NULL)
    {
        if (strcmp(produitcurrent->designation, designation_produit) == 0)
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

    // Si le rayon est au début
    if (rayonCourant != NULL && strcmp(rayonCourant->nom_rayon, nom_rayon) == 0)
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
        if (strcmp(rayonCourant->nom_rayon, nom_rayon) == 0)
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



/* *************************************************************
 * Recherche des produits se situant dans une fourchette de prix
 ************************************************************* */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max) {
    T_Rayon *rayon_current = magasin->liste_rayons;
    T_Produit *produit_current;

    T_Rayon_Temp *rayontemp = NULL; // Téte de la liste à afficher
    rayontemp = malloc(sizeof(T_Rayon_Temp));
    rayontemp->designation = malloc(strlen("-1") + 1); // On initialise à -1 pour savoir s'il est vide ou pas
    strcpy(rayontemp->designation, "-1");
    rayontemp->suivant = NULL;

    // On initialise celui que l'on va itérer, pour conserver le début dans rayontemp
    T_Rayon_Temp *produitsTemp = NULL;
    produitsTemp = malloc(sizeof(T_Rayon_Temp));
    produitsTemp->suivant = NULL;

    while (rayon_current != NULL) // Parcourir les rayons
    {
        produit_current = rayon_current->liste_produits;
        while (produit_current != NULL) // Itérer sur les produits du rayon
        {   
            if (produit_current->prix >= prix_min && produit_current->prix <= prix_max) { // Si c'est le bon produit
                ajouterProduit_RayonTemp(&rayontemp, produit_current->designation, produit_current->prix, produit_current->quantite_en_stock, rayon_current->nom_rayon);
            }
            
            produit_current = produit_current->suivant;
        }
        rayon_current = rayon_current->suivant;
    }

    if(strcmp(rayontemp->designation, "-1") == 0) { // Si la liste est vide
        printf("Aucun produit ne correspond à votre recherche.\n");
        return;
    }

    // A cette étape nous avons construit la liste chainée
    // On va maintenant la formatter pour l'afficher

    // Récupérer le nom des produits ainsi que leur prix et quantité
    char *nomProduits[99]       = {"Marque"};
    char *prixProduits[99]      = {"Prix"};
    char *quantiteProduits[99]  = {"Quantité en stock"};
    char *rayonProduit[99]      = {"Rayon"};
    char intToStrBuffer[9];

    int produitCourant          = 0;

    produitsTemp = rayontemp; // On revient dans la téte. On utilise current pour ne pas perdre la téte pour free la mémoire aprés

    while (produitsTemp != NULL)
    {
        // Ajouter le nom du produit, son prix, sa quantité et son rayon dans le tableau
        nomProduits[produitCourant + 1] = produitsTemp->designation;                // Ajout de la marque

        prixProduits[produitCourant + 1] = (char*) malloc(sizeof(char) * 9);        // Ajout du prix
        sprintf(intToStrBuffer, "%.2f", produitsTemp->prix);
        strcpy(prixProduits[produitCourant + 1], intToStrBuffer); 

        quantiteProduits[produitCourant + 1] = (char*) malloc(sizeof(char) * 9);    // Ajout de la quantité en stock
        sprintf(intToStrBuffer, "%d", produitsTemp->quantite_en_stock );
        strcpy(quantiteProduits[produitCourant + 1], intToStrBuffer);

        rayonProduit[produitCourant + 1] = produitsTemp->rayon;                     // Ajout du rayon

        // printf("%s --- %.2f --- %d --- %s\n", produitsTemp->designation, produitsTemp->prix, produitsTemp->quantite_en_stock, produitsTemp->rayon);


        produitsTemp = produitsTemp->suivant;
        produitCourant++;
    }

    // Afficher le tableau
    nomProduits[produitCourant + 1]         = NULL;
    prixProduits[produitCourant + 1]        = NULL;
    quantiteProduits[produitCourant + 1]    = NULL;
    rayonProduit[produitCourant + 1]        = NULL;

    char **tableaux[] = {nomProduits, prixProduits, quantiteProduits, rayonProduit, NULL};
    afficherTableau(tableaux);


    // On libére la mémoire du rayon temporaire crà
    produitsTemp = rayontemp;
    while (produitsTemp != NULL)
    {   
        T_Rayon_Temp *tofree;
        tofree = produitsTemp;
        produitsTemp = produitsTemp->suivant;
        free(tofree->designation);
        free(tofree->rayon);
        free(tofree);
    }
    free(produitsTemp);
}



/* *********************
 * Fusionner deux rayons
 ********************* */
void fusionnerRayons(T_Magasin *magasin) {

    char *nom_rayon_1 = getStringInput("\nNom du rayon 1 ? ");
    char *nom_rayon_2 = getStringInput("\nNom du rayon 2 ? ");
    char *nom_resultant = getStringInput("\nNom du rayon résultant ? ");

    if(strcmp(nom_rayon_1, nom_rayon_2) == 0) {
        printf("ERREUR: Les deux rayons sont identiques.");
        return;
    }

    if ( (!isDeptSet(magasin, nom_rayon_1, true)) || (!isDeptSet(magasin, nom_rayon_2, true)) ){
        printf("ERREUR: Au moins l'un des rayons est inexistant.");
        return;
    }

    // Identification des rayons à fusionner
    T_Rayon *rayon_1 = getRayonParNom(magasin, nom_rayon_1, true);
    T_Rayon *rayon_2 = getRayonParNom(magasin, nom_rayon_2, true);
    
    T_Produit *prayon_1 = rayon_1->liste_produits;
    T_Produit *prayon_2 = rayon_2->liste_produits;

    // Ca va nous permettre de créer le nouveau rayon avec le méme nom de ceux précédents
    // On remplace leur nom. De toute faéon on les supprime aprés

    strcpy(rayon_1->nom_rayon, "x");
    strcpy(rayon_2->nom_rayon, "xx");

    // Création et identification du nouveau rayon
    ajouterRayon(magasin, nom_resultant);
    T_Rayon *rayon_resultant = getRayonParNom(magasin, nom_resultant, true);


    // Fusion des rayons
    if(prayon_1 == NULL ^ prayon_2 == NULL) { // cas particulier ; l'un des 2 rayons est inexistant, mais pas les deux
        rayon_resultant->liste_produits = (prayon_1 != NULL) ? prayon_1 : prayon_2;
    }

    else { // cas général ; les 2 rayons existent
        
        if (prayon_1->prix >= prayon_2->prix) { // Marquer le début du rayon avec le produit le moins cher
            rayon_resultant->liste_produits = prayon_2;
            prayon_2 = prayon_2->suivant;
        } 
        else {
            rayon_resultant->liste_produits = prayon_1;
            prayon_1 = prayon_1->suivant;
        }

        T_Produit *buffer = rayon_resultant->liste_produits;

        while (prayon_1 != NULL && prayon_2 != NULL)
        {
            if(prayon_1->prix >= prayon_2->prix) {   
                buffer->suivant = prayon_2;
                buffer = prayon_2;
                prayon_2 = prayon_2->suivant;
            }

            else {
                buffer->suivant = prayon_1;
                buffer = prayon_1;
                prayon_1 = prayon_1->suivant;
            }
        }

        buffer->suivant = (prayon_1 != NULL) ? prayon_1 : prayon_2;
    }

    // DANS TOUS LES CAS :
    // On supprime ces rayons
    // Ils vont quand méme pointer sur le premier produit, on met NULL pour ne pas supprimer les produits avec
    rayon_1->liste_produits = NULL;
    rayon_2->liste_produits = NULL;

    afficherRayon(rayon_resultant);

    supprimerRayon(magasin, "x");
    supprimerRayon(magasin, "xx");

    free(nom_rayon_1);
    free(nom_rayon_2);
    free(nom_resultant);
}
