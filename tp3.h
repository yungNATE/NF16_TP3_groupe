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


// Cr�ation et initialisation des structures
T_Produit *creerProduit(char *designation, float prix, int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);

// Ajout d'un rayon dans un magasin
int ajouterRayon(T_Magasin *magasin, char *nomRayon);

// Ajout d'un produit dans un rayon
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite);

// Affichage de tous les rayons d'un magasin
void afficherMagasin(T_Magasin *magasin);

// Affichage de tous les produits d'un rayon
void afficherRayon(T_Rayon *rayon);

// Suppression d'un produit dans un rayon
int supprimerProduit(T_Rayon *rayon, char* designation_produit);

// Suppression d'un rayon et de tous les produits qu'il contient
int supprimerRayon(T_Magasin *magasin, char *nom_rayon);

// Recherche des produits se situant dans une fourchette de prix entr�e par l'utilisateur
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);

// Fusionner deux rayons
void fusionnerRayons(T_Magasin *magasin);

// Vérifier si le magasin existe. Peut afficher un msg dans l'invite au besoin.
bool isStoreSet(T_Magasin *magasin, bool shouldWarnUser);


// UTILS
    // proc
void viderBuffer();
void clear_screen();

    // func
int getNumLength(int num);
int getFloatNumLength(float num);



#endif // TP3_H_INCLUDED
