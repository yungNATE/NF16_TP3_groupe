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


        
        char *choices = "2345678"; // la liste des choix nécessitant de vérifier si mon_magasin a été initialisé

        if (isCharInArray(choix, choices)){ 
            // Si aucun magasin n'existe
            if(! isStoreSet(mon_magasin, true)) {
                continue;
            }
        }

        switch (choix) {
            case '1' : // Créer magasin

                if(isStoreSet(mon_magasin, false)) { // Si le magasin existe déjà
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

                char *nomMagasin = getStringInput("\nNom du magasin ? ");

                mon_magasin = creerMagasin(nomMagasin);
                printf("\nMagasin %s créé ! ", mon_magasin->nom);
                break;

            case '2' : // Ajouter rayon
            {
                // Récupération de l'input
                char *nomRayon = getStringInput("\nNom du rayon ? ");

                // Création
                ajouterRayon(mon_magasin, nomRayon);

                break;
            }

            case '3' : // Ajouter produit
            {
                // récupération de l'input
                char *nomRayonRecherche = getStringInput("\nNom du rayon ? ");
                char *nomProduitAAjouter = getStringInput("\nNom du produit ? ");


                printf("\nPrix du produit ? "); // TODO : ça vaut le coup de créer des fonctions de généralisation ici ? genre un getIntInput & getFloatInput ?
                float prix;
                scanf("%f", &prix);
                viderBuffer();

                printf("\nQuantité du produit ? "); // TODO : ^^^^
                int quantite;
                scanf("%d", &quantite);
                viderBuffer();

                //création
                T_Rayon *rayoncurrent = mon_magasin->liste_rayons;
                while (rayoncurrent != NULL)
                {   
                    if (strcasecmp(rayoncurrent->nom_rayon, nomRayonRecherche) == 0)
                    {   
                        ajouterProduit(rayoncurrent, nomProduitAAjouter, prix, quantite);
                        break;
                    }
                    rayoncurrent = rayoncurrent->suivant;
                }

                break;
            }
            case '4' : // Afficher rayons
            {
                afficherMagasin(mon_magasin);

                break;
            }
            case '5' : // Afficher produits
            {
                // Récupération de l'input
                char *nomRayonRecherche = getStringInput("\nNom du rayon ? ");

                T_Rayon *rayoncurrent = mon_magasin->liste_rayons;
                while (rayoncurrent != NULL)
                {   
                    if (strcasecmp(rayoncurrent->nom_rayon, nomRayonRecherche) == 0)
                    {   
                        afficherRayon(rayoncurrent);
                        break;
                    }
                    rayoncurrent = rayoncurrent->suivant;
                }

                break;
            }
            case '6' : // Supprimer produit
            {                
                // Récupération de l'input
                char *nomRayonDuProduitASupprimer = getStringInput("\nNom du rayon ? ");
                char *nomProduitASupprimer = getStringInput("\nNom du produit ? ");

                int flag = 0;
                T_Rayon *rayoncurrent = mon_magasin->liste_rayons;

                while (rayoncurrent != NULL)
                {
                    if (strcasecmp(rayoncurrent->nom_rayon, nomRayonDuProduitASupprimer) == 0)
                    {
                        supprimerProduit(rayoncurrent, nomProduitASupprimer);
                        flag = 1;
                        break;
                    }
                    rayoncurrent = rayoncurrent->suivant;
                }   

                if (flag == 0) {
                    printf("Rayon inexistant");
                }

                break;
            }
            case '7' : // Supprimer rayon
            {
                char *nomRayonASupprimer = getStringInput("\nNom du rayon ? ");
                supprimerRayon(mon_magasin, nomRayonASupprimer);

               break;
            }
            case '8' : // Rechercher produit par prix
            {

               break;
            }
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
