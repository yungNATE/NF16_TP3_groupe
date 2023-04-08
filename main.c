#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
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

                if(mon_magasin != NULL) {
                    printf("\nUn magasin existe déjà ! ");

    
                    char reponse = 'n'; // intialisation
                    do
                    {
                        if(reponse != 'o' && reponse != 'n') printf("\nERREUR : seulement 'o' et 'n' sont acceptés en réponse ! ");

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
                //! : tests effectués avec 1 bizarrerie
                /*
                    premier passage en entrant "1" : tout va bien, je créé le magasin
                    deuxième passage en entrant "1" : je tombe dans le cas default du switch général comme si j'avais entré autre chose qu'une valeur [1-9]
                    3...n passages en entrant "1" : tout va bien, je renomme le magasin

                    Je soupsonne un buffer mal vidé à cause de "scanf("%s", nom);"

                */
                mon_magasin = creerMagasin(nom);
                printf("\nMagasin %s créé ! ", mon_magasin->nom);
                break;

            case '2' : // Ajouter rayon

                break;

            case '3' : // Ajouter produit
                break;

            case '4' : // Afficher rayons
                break;

            case '5' : // Afficher produits
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
