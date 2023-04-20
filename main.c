#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include "tp3.h"
#include "tp3.c"


int main(void)
{ 

    // char *tableau1[] = {"Nom", "Alice", "Bob", "Charlie", NULL};
    // char *tableau2[] = {"Age", "25", "30", "35", NULL};
    // char *tableau3[] = {"Profession", "Ing�nieur", "M�decin", "Avocat", "Vendeur", NULL};
    // char *tableau4[] = {"Ville", "Tokyo", NULL};
    // char *tableau5[] = {"Ville", "Tokyo", NULL};
    // char *tableau6[] = {"Ville", "Tokyo", NULL};
    // char **tableaux[] = {tableau1, tableau2, tableau3, tableau4, tableau5, tableau6, NULL};
    // afficherTableau(tableaux);

    
    T_Magasin *mon_magasin = NULL;


    // ============= MENU UTILISATEUR ============= */
    char choix = 'x';
    while (choix != '0') {
        printf("\n======================================");
        printf("\n1. Cr�er un magasin");
        printf("\n2. Ajouter un rayon au magasin");
        printf("\n3. Ajouter un produit dans un rayon");
        printf("\n4. Afficher les rayons du magasin");
        printf("\n5. Afficher les produits d'un rayon");
        printf("\n6. Supprimer un produit");
        printf("\n7. Supprimer un rayon");
        printf("\n8. Rechercher un produit par prix");
        printf("\n9. Fusionner 2 rayons");
        printf("\n0. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        viderBuffer(); // supprimer de l'entr?e standard le retour charriot et les ?ventuels caract?res suppl?mentaires tap?s par l'utilisateur

        printf("\nChoix %c sélectionné \n", choix);


        
        char *choixNecessitantMagDefini     = "2345678";    // la liste des choix nécessitant de vérifier si mon_magasin a été initialisé
        char *choixNecessitantUnRayonDefini = "345678";     // La liste des choix nécessitant de vérifier si au moins un rayon a été initialisé.
                                                            //  choixNecessitantUnRayonDefini est composé d'une partie des choixNecessitantMagDefini

        // TODO : dans l'idéal, il faudrait virer cette partie pour intégrer les tests directement dans les fonctions
        // Pour éviter la redondance de isStoreSet & isAnyDeptSet dans le switch
        if (isCharInArray(choix, choixNecessitantMagDefini)){ 
            // Si aucun magasin n'existe pour les choixNecessitantMagDefini
            if(! isStoreSet(mon_magasin, true)) {
                continue;
            }
            
            // Si un magasin existe pour les choixNecessitantUnRayonDefini...
            if (isCharInArray(choix, choixNecessitantUnRayonDefini)) {
                // ... mais qu'aucun rayon n'existe
                if(! isAnyDeptSet(mon_magasin, true)) {
                    continue;
                }
            }
        }

        switch (choix) {
            case '0' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            case '1' : // Créer magasin

                if(isStoreSet(mon_magasin, false)) { // Si le magasin existe déjé
                    printf("\nUn magasin existe déjé ! ");
    
                    char reponse = 'n'; // Intialisation
                    do
                    {
                        if(reponse != 'o' && reponse != 'n') {
                            printf("\nERREUR : seulement 'o' et 'n' sont acceptés en réponse ! ");
                        }

                        printf("\nVoulez-vous le remplacer ? (o/n) ");
                        reponse = getchar();
                        viderBuffer();

                    } while (reponse != 'o' && reponse != 'n');
                    
                    
                    if(reponse == 'o') mon_magasin = NULL;
                    else if(reponse == 'n') break;
                }

                char *nomMagasin = getStringInput("\nNom du magasin ? ");

                mon_magasin = creerMagasin(nomMagasin);
                free(nomMagasin);
                printf("\nMagasin %s cr�� ! ", mon_magasin->nom);
                break;

            case '2' : // Ajouter rayon
            {
                // Récupération de l'input
                    char *nomRayon = getStringInput("\nNom du rayon ? ");

                    // Création
                    ajouterRayon(mon_magasin, nomRayon);

                    free(nomRayon);
                    break;
            }

            case '3' : // Ajouter produit
            {
                afficherRayons(mon_magasin);

                // récupération de l'input
                char *nomRayonRecherche = getStringInput("\nNom du rayon ? ");

                if(!getDeptByName(mon_magasin, nomRayonRecherche, true)) { 
                    printf("Merci de r�essayer avec un rayon existant.");
                    break; 
                }

                char *nomProduitAAjouter = getStringInput("\nNom du produit ? ");
                float prix = getFloatInput("\nPrix du produit ? ");
                int quantite = getIntInput("\nQuantit� du produit ? ");


                //création
                T_Rayon *rayonCourant = mon_magasin->liste_rayons;
                while (rayonCourant != NULL)
                {   
                    if (strcasecmp(rayonCourant->nom_rayon, nomRayonRecherche) == 0) {   
                        ajouterProduit(rayonCourant, nomProduitAAjouter, prix, quantite);
                        break;
                    }
                    rayonCourant = rayonCourant->suivant;
                }

                free(nomRayonRecherche);
                free(nomProduitAAjouter);

                break;
            }
            case '4' : // Afficher rayons
            {
                afficherMagasin(mon_magasin);

                break;
            }
            case '5' : // Afficher produits d'un rayon
            {
                // Rappel des noms des rayons
                afficherRayons(mon_magasin);

                char *nomRayonRecherche = getStringInput("\nNom du rayon à détailler ? ");


                T_Rayon *rayonRecherche = getDeptByName(mon_magasin, nomRayonRecherche, true);
                free(nomRayonRecherche);

                if(rayonRecherche != NULL) afficherRayon(rayonRecherche);

                break;
            }
            case '6' : // Supprimer produit
            {   
                afficherRayons(mon_magasin);
                char *nomRayonDuProduitASupprimer = getStringInput("\nNom du rayon ? ");

                T_Rayon *rayonDuProduitASupprimer = getDeptByName(mon_magasin, nomRayonDuProduitASupprimer, true);

                if(! rayonDuProduitASupprimer ) { 
                    printf("Merci de r�essayer avec un rayon existant.");
                    break; 
                }

                if(rayonDuProduitASupprimer->liste_produits == NULL) {
                    printf("Ce rayon ne contient aucun produit.");
                    break;
                }


                afficherRayon(rayonDuProduitASupprimer);
                char *nomProduitASupprimer = getStringInput("\nNom du produit ? ");

                if (isDeptSet(mon_magasin, nomRayonDuProduitASupprimer, true)){
                    T_Rayon *rayons = getDeptByName(mon_magasin, nomRayonDuProduitASupprimer, true);
                    supprimerProduit(rayons, nomProduitASupprimer);
                }

                free(nomRayonDuProduitASupprimer);
                free(nomProduitASupprimer);
                break;
            }
            case '7' : // Supprimer rayon
            {
                char *nomRayonASupprimer = getStringInput("\nNom du rayon ? ");

                if (isDeptSet(mon_magasin, nomRayonASupprimer, true)){
                    supprimerRayon(mon_magasin, nomRayonASupprimer);
                }

                free(nomRayonASupprimer);
                break;
            }
            case '8' : // Rechercher produit par prix
            {
                float prix_min = getFloatInput("\nPrix minimal du produit ? ");
                float prix_max = getFloatInput("\nPrix maximal du produit ? ");
                
                rechercheProduits(mon_magasin, prix_min, prix_max);

                break;
            }
            case '9' : // Fusionner 2 rayons
            {
                afficherRayons(mon_magasin);

                if (isAnyDeptSet(mon_magasin, true)){
                    fusionnerRayons(mon_magasin);
                }

                break;
            }
            default :
                printf("\n\nERREUR : votre choix n'est pas valide ! ");
            }
            printf("\n\n\n");

            // clear_screen();
        }

        return 0;
    }
