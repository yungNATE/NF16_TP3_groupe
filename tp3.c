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

// Fonction pour vider l'‚cran (normalement iml‚ment‚e via de base clrscr(), mais ne fonctionne pas)
void clear_screen(){
    printf("\e[1;1H\e[2J");
}

// remplace "\n" par "\0" dans un string
void replaceNewLine_WithNullTerminator(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Longueur d'un integer (utile pour g‚n‚rer un beau tableau)
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


// TODO : g‚n‚raliser les fonctions getXInput 
// * get X input ; permet de s'assurer qu'on input bien un X + prompt l'utilisateur

/*
enum getInputTypes { STRING, INT, FLOAT };
char *getXInput(char *prompt, enum getInputTypes type, char *args){
    //* WIP
    int scanfReturn;
    float prix; //.....

    //switch en fonction du type pour param‚trer le do while
    


    do {
        printf("%s", prompt);
        scanfReturn = scanf("%f", &prix);
        viderBuffer();

        if (scanfReturn == 0) {
            printf("\nERREUR : le prix doit ˆtre un nombre ! ");
        }
    } 
    while (scanfReturn == 0);

    return "";
}

*/
// getStringInput de string custom
char *getStringInput(char *prompt){
    char *input = malloc(sizeof(char) * 100);
    printf("%s", prompt);
    fgets(input, 100, stdin);
    replaceNewLine_WithNullTerminator(input);
    fflush(stdin); // TODO : v‚rifier si utile
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
            printf("\nERREUR : le prix doit ˆtre un nombre ! ");
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
            printf("\nERREUR : le prix doit ˆtre un nombre ! ");
        }
    } 
    while (scanfReturn == 0);

    return prix;
}

// Fonction pour v‚rifier si un char est dans un tableau de char
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
 * Cr‚ation et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite) {
    if(quantite <= 0) return NULL;


    T_Produit *nouveauProduit = NULL;

    nouveauProduit = malloc(sizeof(T_Produit));
    if (nouveauProduit == NULL) return NULL; // l'allocation m‚moire n'a pas pu se faire


    nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace m‚moire d‚di‚ pour notre champ de structure
    strcpy(nouveauProduit->designation,designation);
    nouveauProduit->prix = prix;
    nouveauProduit->quantite_en_stock = quantite;
    nouveauProduit->suivant = NULL;

    return nouveauProduit;
}



/* ********************************
 * Cr‚ation et initialisation Rayon
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
 * Cr‚ation et initialisation Magasin
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
    // TODO : Attention … bien v‚rifier toutes les valeurs que peut prendre "magasin"

    T_Rayon *rayonPrecedent = NULL;
    T_Rayon *rayonCourant = magasin->liste_rayons;

    // On parcourt toute la liste jusqu'… trouver un mot plus grand ou la fin de la liste
    while (rayonCourant != NULL && strcmp(rayonCourant->nom_rayon, nomRayon) < 0)
    {
        rayonPrecedent = rayonCourant;
        rayonCourant = rayonCourant->suivant;
    }

    // Test si rayon existe d‚j…
    if (rayonCourant != NULL && strcmp(rayonCourant->nom_rayon, nomRayon) == 0)
    {
        printf("Le rayon existe d‚j….\n");
        return 0;
    }

    // Ok pour ins‚rer 

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

    //* V‚rification si le produit existe d‚j… dans le rayon
    T_Produit *produit = rayon->liste_produits;
    while (produit != NULL) {
        if (strcmp(produit->designation, designation) == 0) {

            // Le produit existe d‚j…, on augmente simplement sa quantite et demande si prix modifie ou pas
            printf("Un produit avec le mˆme nom existe d‚j….\n");
            printf("Vouz aurez le choix entre augmenter sa quantit‚ et/ou modifier son prix si vous avez rentr‚ un prix diff‚rent de l'ancien.\n");
            printf("Si vous souhaitez le remplacer avec la nouvelle quantit‚ et prix, supprimez-le et cr‚ez-en un nouveau.\n");

            char reponse = 'n'; // Intialisation
            do
            {
                if(reponse != 'o' && reponse != 'n') 
                {
                    printf("\nERREUR : seulement 'o' et 'n' sont accept‚s en r‚ponse ! ");
                }
                printf("\nVoulez-vous simplement augmenter sa quantit‚ ? (o/n) ");
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
                            printf("\nERREUR : seulement 'o' et 'n' sont accept‚s en r‚ponse !\n ");
                        }
                        printf("Souhaitez-vous modifier son prix (o/n) ? Ancien prix: %f\n", produit->prix);
                        reponse = getchar();
                        viderBuffer();
                    } while (reponse != 'o' && reponse != 'n');

                    if (reponse == 'o') // On supprime le produit et insere avec qt‚ augment‚e et prix diff‚rent pour avoix la liste encore tri‚e
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


    //* Cr‚ation du nouveau produit
    T_Produit *nouveauProduit = creerProduit(designation, prix, quantite);


    //* Insertion du nouveau produit dans le rayon, en respectant l'ordre croissant des prix
    T_Produit *produitPrecedent = NULL;
    T_Produit *produitCourant = rayon->liste_produits;

    // tant qu'on trouve un prix inf‚rieur au produit courant, on avance dans le rayon 
    while (produitCourant != NULL && produitCourant->prix < prix) {
        produitPrecedent = produitCourant;
        produitCourant = produitCourant->suivant;
    }

    // On vient de d‚passer le dernier produit au prix < au prix courant. On insŠre 
    if(produitPrecedent == NULL)
    {
        nouveauProduit->suivant = rayon->liste_produits;
        rayon->liste_produits = nouveauProduit;
    }

    else produitPrecedent->suivant = nouveauProduit;

    nouveauProduit->suivant = produitCourant; // Pour bien marquer la fin

    return 1; // SuccŠs de l'ajout
}




/* **********************************************
 * Ajout produit dans la nouvelle structure rayon
 ********************************************* */
void ajouterProduit_RayonTemp(T_Rayon_Temp **rayontemp, char *designation, float prix, int quantite, char *nom_rayon) {

    // Si la liste est vide, cÃ d designation = "-1" on ajoute directement le produit
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

    // Sinon tant qu'on trouve un prix infÃ©rieur au produit courant, on avance dans le rayon 
    T_Rayon_Temp *current = *rayontemp;
    T_Rayon_Temp *precedent = NULL;
    while (current != NULL && current->prix < prix) {
        precedent = current;
        current = current->suivant;
    }

    // On crÃ©e un nouveau produit Ã  insÃ©rer
    T_Rayon_Temp *nouveau = malloc(sizeof(T_Rayon_Temp));
    nouveau->designation = malloc(strlen(designation) + 1);
    strcpy(nouveau->designation, designation);
    nouveau->prix = prix;
    nouveau->quantite_en_stock = quantite;
    nouveau->rayon = malloc(strlen(nom_rayon) + 1);
    strcpy(nouveau->rayon, nom_rayon);
    nouveau->suivant = NULL;

    if (precedent == NULL) { // Si insertion en tÃªte
        nouveau->suivant = *rayontemp;
        *rayontemp = nouveau;
    }

    else {
        nouveau->suivant = current;
        precedent->suivant = nouveau;
    }
}




/* *****************************************
 * R‚cup‚ration du nom de rayon le plus long
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
 * afficher caractŠre de s‚paration d'un tableau affich‚
 **************************************************** */
char * getRepeatedChar(int nbCaracteres, char separateur) {
    if(nbCaracteres <= 0) return "";
    // Allouer de la m‚moire pour la chaŒne de caractŠres
    char *resultat = (char *) malloc(nbCaracteres + 1);
    if (resultat == NULL) return NULL;

    // Initialiser la chaŒne de caractŠres avec le caractŠre s‚parateur r‚p‚t‚ nbCaracteres fois
    memset(resultat, separateur, nbCaracteres);

    resultat[nbCaracteres] = '\0';

    return resultat;
}
char * getSeparationLine(int nbCaracteres) {
    return getRepeatedChar(nbCaracteres, '-');
}


/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasin(T_Magasin *magasin) { 
    // TODO : ajouter un paramŠtre booleen isSimplified pour supprimer la colonne quantit‚ en stock 
    //          (permet de faire de l'affichage des rayons seuls), notamment pour le switch du main
      
    if(! isAnyDeptSet(magasin, true)) return;

    T_Rayon *rayons;
    rayons = magasin->liste_rayons;
    
    int nbProduits;
    T_Produit *produit;
  
    printf("\nAffichage des rayons du magasin \"%s\"\n", magasin->nom);


    //* ParamŠtres du tableau
    char *longestDeptName = getLongestDeptName(magasin);
    char *colonneUnNom = "Nom du rayon";
    
    int longestDeptNameLength = strlen(longestDeptName);
    int colonneUnLength = strlen(colonneUnNom);
    // vvv comme on traite une colonne de string, on v‚rifie qu'un rayon n'a pas un nom plus long que l'entˆte de colonne
    colonneUnLength = longestDeptNameLength > colonneUnLength ? longestDeptNameLength : colonneUnLength; 
    colonneUnLength += 2; // On ajoute 2 espaces pour prendre en compte les caractŠres de s‚paration

    char *espacesColonneUnNom = getRepeatedChar(colonneUnLength - strlen(colonneUnNom) - 2, ' ');


    // pour la 2e colonne, on considŠre que la longueur du nombre de produit n'exedera jamais colonneDeuxNom
    // donc pas besoin de calculs de longueur du nombre de produit de rayon en amont
    char *colonneDeuxNom = "Nombre de produits";
    int colonneDeuxLength = strlen(colonneDeuxNom);
    colonneDeuxLength += 2; // On ajoute 2 espaces pour prendre en compte les caractŠres de s‚paration

    char colonneSeparation = '|';
    char angle = '+';


    //* Affichage
    // Affichage des entˆtes du tableau
    printf("%c%s%c%s%c\n", angle, getSeparationLine(colonneUnLength), angle, getSeparationLine(colonneDeuxLength), angle);
    printf("%c %s%s %c %s %c\n", colonneSeparation, colonneUnNom, espacesColonneUnNom, colonneSeparation, colonneDeuxNom, colonneSeparation);
    printf("%c%s%c%s%c\n", angle, getSeparationLine(colonneUnLength), angle, getSeparationLine(colonneDeuxLength), angle);

    // int nbEspacesAAjouterApresNomRayon = maxElargi - ( colonneUnLength + 1 ); // Pour a‚rer un peu le tableau et ‚viter que la prochaine colonne s‚paration soit coll‚e


    // Affichage des rayons
    rayons = magasin->liste_rayons; // TODO : v‚rifier si n‚cessaire
    while (rayons != NULL)
    {
        // Affichage du nom du rayon
        int tailleNomRayon = strlen(rayons->nom_rayon) + 1;

        char *espaceNomRayon = getRepeatedChar(colonneUnLength - tailleNomRayon, ' ');
        char *nomRayonAAfficher = strcat(rayons->nom_rayon, espaceNomRayon);
        printf("%c %s",colonneSeparation, nomRayonAAfficher);


        // Affichage du nombre de produits
        int nbProduits = compterProduits(rayons);
        int tailleNbProduits = getNumLength(nbProduits) + 1;

        char *nbProduitsStringified = malloc(tailleNbProduits * sizeof(char));
        sprintf(nbProduitsStringified, "%d", nbProduits); // nbProduits en string
        char *espaceNbProduits = getRepeatedChar(colonneDeuxLength - tailleNbProduits, ' ');
        char *nbProduitsAAfficher = strcat(nbProduitsStringified, espaceNbProduits);
        // printf("\nnbprod string : %s\n", nbProduitsAAfficher);
        
        printf("%c %s", colonneSeparation, nbProduitsAAfficher);
        
        printf("%c\n", colonneSeparation);


        rayons = rayons->suivant;
    }
}


/* *****************************************
 * Affichage de tous les produits d'un rayon
 ***************************************** */
void afficherRayon(T_Rayon *rayon) {
    T_Produit *produits;
    produits = rayon->liste_produits;

    if (rayon == NULL)
    {
        printf("Rayon inexistant.");
    }

    else if (produits == NULL)
    {
        printf("Rayon vide.\n");
    }

    else
    {   
        // Pour avoir une table sympa on va calculer la longueur du mot le plus long
        int max = strlen("Designation");
        int maxElargi = max*1.5;
        while (produits != NULL)
        {   
            if (strlen(produits->designation) > max)
            {
                max = strlen(produits->designation);
            }
            produits = produits->suivant;
        }
        printf("+");
        for (int k = 0; k < maxElargi; k++)
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
        for (int k = 0; k < maxElargi - strlen("| Designation ") + 1; k++)
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
        for (int k = 0; k < LEN_MAX_QTE*1.5 - strlen("| Quantit‚ en stock ") + 2; k++) // Si temps faire dynamique en fonction du plus grand qt‚
        {
            printf(" ");
        }
        printf("|\n");
        printf("+");
        for (int k = 0; k < maxElargi; k++)
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


        produits = rayon->liste_produits; // Car produits a ‚t‚ it‚r‚

        while (produits != NULL)
        {   
            printf("| %s", produits->designation);
            for (int k = 0; k < 1.5*max - strlen(produits->designation) - 1; k++)
            {
                printf(" ");
            }
            printf("| ");
            printf("%.2f", produits->prix);
            for (int k = 0; k < LEN_MAX_PRIX*1.5 - getFloatNumLength(produits->prix) - 1 - 3; k++)
            {
                printf(" ");
            }
            printf("| ");
            printf("%d", produits->quantite_en_stock);
            for (int k = 0; k < LEN_MAX_QTE*1.5 - getNumLength(produits->quantite_en_stock) - 1; k++)
            {
                printf(" ");
            }
            printf("|\n");
            produits = produits->suivant;
        }
        printf("+");
        for (int k = 0; k < maxElargi; k++)
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


/* ******************************
 * V‚rifie si le magasin existe
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
 * V‚rifie si, au sein du magasin, au moins un rayon existe
 ******************************************************** */
bool isAnyDeptSet(T_Magasin *magasin, bool shouldWarnUser) {
    if(! isStoreSet(magasin, shouldWarnUser)) return false; // Juste au cas o—, on v‚rifie que le magasin soit bien d‚fini.
                                                            // Si pas de magasin => pas de rayon

    if(magasin->liste_rayons == NULL) {
        if(shouldWarnUser) printf("\nAucun rayon n'existe ! ");
        return false;
    }

    return true;
}


/* ***************************************************************
 * Alerte pour les fonctions de r‚cup‚ration de rayon
 ************************************************************** */
void alert_DeptDoesNotExists(T_Rayon *rayon) {
    printf("\nLe rayon %s n'existe pas ! ", rayon->nom_rayon);
}

/* ***************************************************************
 * R‚cupŠre le T_Rayon correspondant au nom pass‚ en paramŠtre
 ************************************************************** */
T_Rayon *getDeptByName(T_Magasin *magasin, char *nom_rayon, bool shouldWarnUser) {
    T_Rayon *rayonCourant = magasin->liste_rayons;

    while(rayonCourant != NULL) {
        if(strcasecmp(rayonCourant->nom_rayon, nom_rayon) == 0) return rayonCourant;
        rayonCourant = rayonCourant->suivant;
    }

    if(shouldWarnUser) alert_DeptDoesNotExists(rayonCourant);
    return NULL;
}


/* ***************************************************************
 * V‚rifie si, au sein du magasin, le rayon pass‚ en param existe
 ************************************************************** */
bool isDeptSet(T_Magasin *magasin, char *nom_rayon, bool shouldWarnUser) {
    if(! isAnyDeptSet(magasin, shouldWarnUser)) return false;   // Juste au cas o—, on v‚rifie qu'au moins un rayon soit bien d‚fini.

    T_Rayon *rayon = getDeptByName(magasin, nom_rayon, false);
    if(rayon != NULL) return true;

    if(shouldWarnUser) alert_DeptDoesNotExists(rayon);
    return false;
}

/* **************************************
 * Suppression d'un produit dans un rayon
 ************************************** */
int supprimerProduit(T_Rayon *rayon, char* designation_produit) {

    T_Produit *produitprecedent = NULL;
    T_Produit *produitcurrent = rayon->liste_produits;

    // Si le produit est au d‚but
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

    // Si le rayon est au d‚but
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

    T_Rayon_Temp *rayontemp = NULL; // TÃªte de la liste Ã  afficher
    rayontemp = malloc(sizeof(T_Rayon_Temp));
    rayontemp->designation = malloc(strlen("-1") + 1); // On initialise Ã  -1 pour savoir s'il est vide ou pas
    strcpy(rayontemp->designation, "-1");
    rayontemp->suivant = NULL;


    // On initialise celui que l'on va itÃ©rer, pour conserver le dÃ©but dans rayontemp
    T_Rayon_Temp *rayontemp_current = NULL;
    rayontemp_current = malloc(sizeof(T_Rayon_Temp));
    rayontemp_current->suivant = NULL;

    while (rayon_current != NULL) // ItÃ©rer les rayons
    {   
        produit_current = rayon_current->liste_produits;
        while (produit_current != NULL) // ItÃ©rer les produits du rayon
        {   
            if (produit_current->prix >= prix_min && produit_current->prix <= prix_max) // Si c'est le bon produit
            {   
                ajouterProduit_RayonTemp(&rayontemp, produit_current->designation, produit_current->prix, produit_current->quantite_en_stock, rayon_current->nom_rayon);
            }
            
            produit_current = produit_current->suivant;
        }
        rayon_current = rayon_current->suivant;
    }

    // A cette Ã©tape nous avons construit la liste chainÃ©e et elle est prÃªte Ã  Ãªtre print

    rayontemp_current = rayontemp; // On revient dans la tÃªte. On utilise current pour ne pas perdre la tÃªte pour free la mÃ©moire aprÃ¨s

    // Afficher comme: Marque | Prix | QuantitÃ© en stock | Rayon 
    // Normalement c'est dÃ©jÃ  triÃ© par prix croissant

    while (rayontemp_current != NULL)
    {
        printf("%s --- %.2f --- %d --- %s\n", rayontemp_current->designation, rayontemp_current->prix, rayontemp_current->quantite_en_stock, rayontemp_current->rayon);
        rayontemp_current = rayontemp_current->suivant;
    }
    // On libÃ¨re la mÃ©moire du rayon temporaire crÃ©Ã©

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
    char *nom_resultant = getStringInput("\nNom du rayon rÃ©sultant?");

    if (isDeptSet(magasin, nom_rayon_1, false) && isDeptSet(magasin, nom_rayon_2, false)) // Si les 2 rayons existent
    {
        printf("ISDEPTSET");
        // Identification des rayons Ã  fusionner
        T_Rayon *rayon_1 = getDeptByName(magasin, nom_rayon_1, true);
        T_Rayon *rayon_2 = getDeptByName(magasin, nom_rayon_2, true);
        
        T_Produit *prayon_1 = rayon_1->liste_produits;
        T_Produit *prayon_2 = rayon_2->liste_produits;

        // Ca va nous permettre de crÃ©er le nouveau rayon avec le mÃªme nom de ceux prÃ©cÃ©dents
        // On remplace leur nom. De toute faÃ§on on les supprime aprÃ¨s

        strcpy(rayon_1->nom_rayon, "x");
        strcpy(rayon_2->nom_rayon, "xx");

        // CrÃ©ation et identification du nouveau rayon
        ajouterRayon(magasin, nom_resultant);
        T_Rayon *rayon_resultant = getDeptByName(magasin, nom_resultant, true);

        // Regarder si un des rayons est vide

        
        // Juste pour regrouper les cas particuliers avec if..else
        if ((prayon_1 == NULL && prayon_2 == NULL) || (prayon_1 != NULL && prayon_2 == NULL) || (prayon_1 == NULL && prayon_2 != NULL))
        {
            if (prayon_1 == NULL && prayon_2 == NULL)
            {
                // on ne fait rien; Ã  la fin on supprime les 2 rayons et on laisse juste le nouveau
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
            // Marquer le dÃ©but du rayon avec le produit le moins cher
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
        // Ils vont quand mÃªme pointer sur le premier produit, on met NULL pour pas supprimer les produits avec
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


