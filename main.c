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
    char choix = '0';
    while (choix != '9') {
        printf("\n======================================");
        printf("\n1. Creer un magasin");
        printf("\n2. Ajouter un rayon au magasin");
        printf("\n3. Ajouter un produit dans un rayon");
        printf("\n4. Afficher les rayons du magasin");
        printf("\n5. Afficher les produits d'un rayon");
        printf("\n6. Supprimer un produit");
        printf("\n7. Supprimer un rayon");
        printf("\n8. Rechercher un produit par prix");
        printf("\n9. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        viderBuffer(); // supprimer de l'entr�e standard le retour charriot et les �ventuels caract�res suppl�mentaires tap�s par l'utilisateur

        printf("\nChoix %c sélectionné \n", choix);

        switch (choix) {
            case '1' : // Créer magasin

                if(mon_magasin != NULL) { // Si le magasin existe déjà
                    printf("\nUn magasin existe déjà ! ");
    
                    char reponse = 'n'; // Intialisation
                    do
                    {
                        if(reponse != 'o' && reponse != 'n') 
                        {
                            printf("\nERREUR : seulement 'o' et 'n' sont acceptés en réponse ! ");
                        }

                        printf("\nVoulez-vous le remplacer ? (o/n) ");
                        reponse = getchar();
                        viderBuffer();

                    } while (reponse != 'o' && reponse != 'n');
                    
                    
                    if(reponse == 'o') mon_magasin = NULL;
                    else if(reponse == 'n') break;
                }

                printf("\nNom du magasin ? ");
                char nom[50];
                scanf("%s", nom);
                viderBuffer();

                mon_magasin = creerMagasin(nom);
                printf("\nMagasin %s créé ! ", mon_magasin->nom);
                break;

            case '2' : // Ajouter rayon

                // Si aucun magasin n'existe
                if(! isStoreSet(mon_magasin, true)) 
                {
                    break;
                }

                // Récupération de l'input
                printf("\nNom du rayon ? ");
                char nomRayon[50];
                scanf("%s", nomRayon);
                viderBuffer();

                // Création
                ajouterRayon(mon_magasin, nomRayon);
                

                break;

            case '3' : // Ajouter produit

                // si aucun magasin n'existe
                if(! isStoreSet(mon_magasin, true)) 
                {
                    break;
                }
                // récupération de l'input
                printf("\nNom du rayon ? ");
                char nomRayonrecherche[50];
                scanf("%s", nomRayonrecherche);
                viderBuffer();

                printf("\nNom du produit ? ");
                char produitRajouter[50];
                scanf("%s", produitRajouter);
                viderBuffer();

                printf("\nPrix du produit ? ");
                float prix;
                scanf("%f", &prix);
                viderBuffer();

                printf("\nQuantité du produit ? ");
                int quantite;
                scanf("%d", &quantite);
                viderBuffer();

                //création
                T_Rayon *rayoncurrent = mon_magasin->liste_rayons;
                while (rayoncurrent != NULL)
                {   
                    if (strcmp(rayoncurrent->nom_rayon, nomRayonrecherche) == 0)
                    {   
                        ajouterProduit(rayoncurrent, produitRajouter, prix, quantite);
                        break;
                    }
                    rayoncurrent = rayoncurrent->suivant;
                }


                break;

            case '4' : // Afficher rayons

                // si aucun magasin n'existe
                if(! isStoreSet(mon_magasin, true)) 
                {   
                    printf("Le magasin n'existe pas.");

                    break;
                }

                afficherMagasin(mon_magasin);

                break;

            case '5' : // Afficher produits

                if(! isStoreSet(mon_magasin, true))
                {   
                    printf("Le magasin n'existe pas.");
                    break;
                }

                // Récupération de l'input
                printf("\nNom du rayon ? ");
                scanf("%s", nomRayonrecherche);
                viderBuffer();

                rayoncurrent = mon_magasin->liste_rayons;
                while (rayoncurrent != NULL)
                {   
                    if (strcmp(rayoncurrent->nom_rayon, nomRayonrecherche) == 0)
                    {   
                        afficherRayon(rayoncurrent);
                        break;
                    }
                    rayoncurrent = rayoncurrent->suivant;
                }

                break;

            case '6' : // Supprimer produit
                break;

            case '7' : // Supprimer rayon
               break;

            case '8' : // Rechercher produit par prix
               break;

            case '9' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
        }
        printf("\n\n\n");

        // clear_screen();
    }

    return 0;
}
