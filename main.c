#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include "tp3.h"
#include "tp3.c"

int main(void)
{
    
    T_Magasin *mon_magasin = NULL;


    // ============= MENU UTILISATEUR ============= */
    char choix = 'x';
    while (choix != '0') {
        printf("\n======================================");
        printf("\n1. Cr‚er un magasin");
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
        viderBuffer(); // suppression de l'entr?e standard le retour charriot et les ?ventuels caract?res suppl?mentaires tap?s par l'utilisateur

        printf("\nChoix %c s‚lectionn‚ \n", choix);


        switch (choix) {
            case '0' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            case '1' : // Cr‚er magasin

                if(isMagasinSet(mon_magasin, false)) { // Si le magasin existe d‚j…, on propose de le remplacer (destruction + cr‚ation nouveau)
                    printf("\nUn magasin existe d‚j… ! ");
    
                    char reponse = 'n'; // Intialisation pour le do-while
                    do
                    {
                        if(reponse != 'o' && reponse != 'n') {
                            printf("\nERREUR : seulement 'o' et 'n' sont accept‚s en r‚ponse ! ");
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
                printf("\nMagasin %s cr‚‚ ! ", mon_magasin->nom);
                break;

            case '2' : // Ajouter rayon
            {
                if(! isMagasinSet(mon_magasin, true)) {
                    continue;
                }

                // R‚cup‚ration de l'input
                char *nomRayon = getStringInput("\nNom du rayon ? ");

                // Cr‚ation
                ajouterRayon(mon_magasin, nomRayon);

                free(nomRayon);
                break;
            }
            case '3' : // Ajouter produit
            {
                afficherRayons(mon_magasin);

                // r‚cup‚ration de l'input
                char *nomRayonRecherche = getStringInput("\nNom du rayon ? ");

                if(!getRayonParNom(mon_magasin, nomRayonRecherche, true)) { 
                    printf("Merci de r‚essayer avec un rayon existant.");
                    break; 
                }

                char *nomProduitAAjouter = getStringInput("\nNom du produit ? ");
                float prix = getFloatInput("\nPrix du produit ? ");
                int quantite = getIntInput("\nQuantit‚ du produit ? ");


                //cr‚ation
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
            case '4' : // Afficher rayons du magasin
            {
                afficherMagasin(mon_magasin);

                break;
            }
            case '5' : // Afficher produits d'un rayon
            {
                // Rappel des noms des rayons
                afficherRayons(mon_magasin);

                char *nomRayonRecherche = getStringInput("\nNom du rayon … d‚tailler ? ");


                T_Rayon *rayonRecherche = getRayonParNom(mon_magasin, nomRayonRecherche, true);
                free(nomRayonRecherche);

                if(rayonRecherche != NULL) afficherRayon(rayonRecherche);

                break;
            }
            case '6' : // Supprimer produit
            {   
                afficherRayons(mon_magasin);

                char *nomRayonDuProduitASupprimer = getStringInput("\nNom du rayon ? ");

                T_Rayon *rayonDuProduitASupprimer = getRayonParNom(mon_magasin, nomRayonDuProduitASupprimer, true);

                if(! rayonDuProduitASupprimer ) { 
                    printf("Merci de r‚essayer avec un rayon existant.");
                    break; 
                }

                if(rayonDuProduitASupprimer->liste_produits == NULL) {
                    printf("Ce rayon ne contient aucun produit.");
                    break;
                }


                afficherRayon(rayonDuProduitASupprimer);
                char *nomProduitASupprimer = getStringInput("\nNom du produit ? ");

                if (isRayonSet(mon_magasin, nomRayonDuProduitASupprimer, true)){
                    T_Rayon *rayons = getRayonParNom(mon_magasin, nomRayonDuProduitASupprimer, true);
                    supprimerProduit(rayons, nomProduitASupprimer);
                }

                free(nomRayonDuProduitASupprimer);
                free(nomProduitASupprimer);
                break;
            }
            case '7' : // Supprimer rayon
            {
                if(! isAnyRayonSet(mon_magasin, true)) {
                    continue;
                }

                char *nomRayonASupprimer = getStringInput("\nNom du rayon ? ");

                if (isRayonSet(mon_magasin, nomRayonASupprimer, true)){
                    supprimerRayon(mon_magasin, nomRayonASupprimer);
                }

                free(nomRayonASupprimer);
                break;
            }
            case '8' : // Rechercher produit par prix
            {
                if(! isAnyRayonSet(mon_magasin, true)) {
                    continue;
                }

                float prix_min = getFloatInput("\nPrix minimal du produit ? ");
                float prix_max = getFloatInput("\nPrix maximal du produit ? ");
                
                rechercheProduits(mon_magasin, prix_min, prix_max);

                break;
            }
            case '9' : // Fusionner 2 rayons
            {
                afficherRayons(mon_magasin);

                if (isAnyRayonSet(mon_magasin, true)){
                    fusionnerRayons(mon_magasin);
                }

                break;
            }
            default :
                printf("\n\nERREUR : votre choix n'est pas valide ! ");
            }
            printf("\n\n\n");
        }

        return 0;
    }
