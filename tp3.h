#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED
#define LEN_MAX_QTE 15
#define LEN_MAX_PRIX 15
#define NMAX_STR 50

// Structures et types
struct Produit {
    char *designation;
    float prix;
    int quantite_en_stock;
    struct Produit *suivant;
};
typedef struct Produit T_Produit;

struct Rayon {
    char * nom_rayon;
    T_Produit *liste_produits;
    struct Rayon *suivant;
};
typedef struct Rayon T_Rayon;

struct Magasin {
    char *nom;
    T_Rayon *liste_rayons;
};
typedef struct Magasin T_Magasin;

struct Rayon_Temp {
    char *designation;
    float prix;
    int quantite_en_stock;
    char *rayon;
    struct Rayon_Temp *suivant;
};
typedef struct Rayon_Temp T_Rayon_Temp;


// Cr?ation et initialisation des structures
T_Produit *creerProduit(char *designation, float prix, int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);


// FONCTIONS METIER
    // Ajout d'un rayon dans un magasin
int ajouterRayon(T_Magasin *magasin, char *nomRayon);

    // Ajout d'un produit dans un rayon
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite);

    // Ajout d'un produit dans un rayon de la nouvelle structure
void ajouterProduit_RayonTemp(T_Rayon_Temp **rayon, char *designation, float prix, int quantite, char *nom_rayon);

    // Affichage de tous les rayons d'un magasin
void afficherMagasin(T_Magasin *magasin);

    // Affichage de tous les produits d'un rayon
void afficherRayon(T_Rayon *rayon);

    // Suppression d'un produit dans un rayon
int supprimerProduit(T_Rayon *rayon, char* designation_produit);

    // Suppression d'un rayon et de tous les produits qu'il contient
int supprimerRayon(T_Magasin *magasin, char *nom_rayon);

    // Recherche des produits se situant dans une fourchette de prix entr?e par l'utilisateur
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);

    // Fusionne deux rayons
void fusionnerRayons(T_Magasin *magasin);

    // V?rifie si le magasin existe. Peut afficher un msg dans l'invite au besoin.
bool isMagasinSet(T_Magasin *magasin, bool shouldWarnUser);

    // Récupère le T_Rayon correspondant au nom passé en paramètre
T_Rayon *getRayonParNom(T_Magasin *magasin, char *nomRayon, bool shouldWarnUser);

    // V?rifie si, au sein du magasin, au moins un rayon existe. Peut afficher un msg dans l'invite au besoin.
bool isAnyRayonSet(T_Magasin *magasin, bool shouldWarnUser);

    // Affiche le magasin. En fonction de l'utilité, le nombre de produits peut être affiché ou non.
void afficherMagasinGenerique(T_Magasin *magasin, bool shouldShowNbProducts);

    // Affiche le magasin en forçant l'affichage du nombre de produits
void afficherMagasin(T_Magasin *magasin);

    // Affiche le magasin en cachant l'affichage du nombre de produits
void afficherRayons(T_Magasin *magasin);




// UTILS
    // proc
void viderBuffer(); // Vider le buffer (utile quand on utilise des getchar() )
void replaceNewLine_WithNullTerminator(char *string); // remplace "\n" par "\0" dans un string
void alert_leRayonNExistePas(char *nomRayonRecherche); // wrapper d'un printf() avec un message d'erreur
void afficherTableau(char ***tableaux); // Affichage d'un tableau

    // func
char *getCaractereRepete(int nbCaracteres, char separateur); // Affiche caractère de séparation d'un tableau affiché

char *getStringInput(char *prompt); // Les fonctions getTypeInput() permettent de s'assurer qu'on input bien le type recherché
float getFloatInput(char *prompt);
int getIntInput(char *prompt);

#endif // TP3_H_INCLUDED
