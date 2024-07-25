#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "file_utils.h"

#define MAX_ELEVES 75
#define MAX_LINE_LENGTH 256

void stock_struct (eleve *l1)
{
    FILE *fic = NULL;
    int nbr_len = 0;

    fic = fopen("liste.csv", "r" );
    if (fic == NULL)
    {
        printf ("Erreur de l'ouverture de la fichier liste.csv\n");
        exit(1);
    }
    while ( fgets(l1[nbr_len].nom, 100 , fic) != NULL )
    {                                                            // char *tab;
        l1[nbr_len].nom[strcspn(l1[nbr_len].nom, "\n")] = '\0'; // esorina le '\n' de ovaina nul  
        l1[nbr_len].num = nbr_len + 1;
        nbr_len++;
    }
    fclose(fic);
}
void search_num(eleve *l1) 
{
    int n, i;
    printf("Entrez le numero de l'eleve a rechercher : ");
    scanf("%d", &n);


    if ( n > 0  &&  n <= MAX_ELEVES )
    {
        for (i = 0; i < MAX_ELEVES; i++) 
        {
            if (l1[i].num == n) {
                printf("%d : %s\n", l1[i].num, l1[i].nom);
                break;
            }
        }
    }
    else
        printf("%d n'existe pas dans la liste l1\n",n);
}
void search_name(eleve *l1) 
{
    char name[100];
    char nom_eleve[100];
    int i, j, trouve = 0;

    printf("Entrez le nom ou prenom de l'eleve a rechercher : ");
    getchar();
    fgets(name, sizeof(name) , stdin); //scanf => name 
    name[strcspn(name, "\n")] = '\0';

    for (i = 0; name[i]; i++) 
    {
        name[i] = toupper(name[i]);
    }

    for (i=0; i < MAX_ELEVES; i++) 
    {
        strcpy(nom_eleve, l1[i].nom);
        for (j = 0; nom_eleve[j]; j++) {
            nom_eleve[j] = toupper(nom_eleve[j]);
        }

        if (strstr(nom_eleve, name) != NULL) 
        {
            printf(" %d: %s \n", l1[i].num, l1[i].nom);
            trouve = 1;
        }
    }
    if (!trouve) 
    {
        printf("Aucun eleve trouve avec le nom contenant \"%s\".\n", name);
    }
}
void display_list(eleve *l1)
{
    int i;
    printf("\t******************************************\n");
    printf("\t*---- Voici les listes des eleves L1 ----*\n");
    printf("\t******************************************\n");
    printf("╔═════════════╔═══════════════════════════════════════════════╗\n");
    printf(" Numero			Nom et prenoms			  \n");
    for (i = 0; i < MAX_ELEVES; i++)
    {	
		printf("╠═════════════╠═══════════════════════════════════════════════╣\n");
        printf("  %d 		  %s \n", l1[i].num, l1[i].nom);
        
      
    }
    printf("╚═════════════╚═══════════════════════════════════════════════╝\n");
}
void display_default (char *filename)
{
    FILE *fic = fopen (filename,"r");
    int c;
    while ( (c=fgetc(fic)) != EOF )
    {
        printf ("%c", c);
    }
}
void display_check_yes(eleve *l1_1)
{
    FILE *fic = fopen("liste2.csv", "r");
    char line[MAX_LINE_LENGTH];
    
    if (fic == NULL)
    {
        printf ("Erreur de l'ouverture du fichier liste2.csv\n");
        exit(1);
    }

    printf("\tListe des élèves qui ont pris le PC :\n");

    while (fgets(line, MAX_LINE_LENGTH, fic) != NULL)
    {
        if (strstr(line, "OUI" ) != NULL)
        {
            int num;
            char nom[100];

            sscanf(line, "%d : %[^\n]", &num, nom);

            printf("%d : %s\n", num, nom);
        }
    }

    fclose(fic);
}
void display_check_abs(eleve *l1_1)
{
    FILE *fic = fopen("liste2.csv", "r");
    char line[MAX_LINE_LENGTH];
    
    if (fic == NULL)
    {
        printf ("Erreur de l'ouverture du fichier liste2.csv\n");
        exit(1);
    }

    printf("\tListe des élèves qui ont pris le PC :\n");

    while (fgets(line, MAX_LINE_LENGTH, fic) != NULL)
    {
        if (strstr(line, "ABS" ) != NULL)
        {
            int num;
            char nom[100];

            sscanf(line, "%d : %[^\n]", &num, nom);

            printf("%d : %s\n", num, nom);
        }
    }

    fclose(fic);
}
presence convert_status_to_presence(char *status)
{
    presence valeur;

    if (strcmp(status, "OUI") == 0 || strcmp(status, "0") == 0
        || strcmp(status, "ENY") == 0 || strcmp(status, "YES") == 0) 
    {
        valeur = OUI;
    } 
    else if (strcmp(status, "NON") == 0 || strcmp(status, "1") == 0
            || strcmp(status, "TSIA") == 0 ) 
    {
        valeur = NON;
    } 
    else if (strcmp(status, "PERSONEL") == 0 || strcmp(status, "3") == 0
            || strcmp(status, "PERSO") == 0) 
    {
        valeur = PERSO;
    } 
    else if (strcmp(status, "ABSENT") == 0 || strcmp(status, "2") == 0
            || strcmp(status, "ABS") == 0) 
    {
        valeur = ABS;
    } 
    else 
    {
        valeur = -1; // Valeur invalide ou non reconnue
    }

    return valeur;
}

char** read_file(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];
    char **lines = (char**)malloc(MAX_ELEVES * sizeof(char*));
    if (file == NULL) 
    {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        exit(1);
    }
    for (int i = 0; i < MAX_ELEVES; i++) 
    {
        if (fgets(line, MAX_LINE_LENGTH, file) != NULL) 
        {
            lines[i] = strdup(line);
        }
        else 
        {
            lines[i] = NULL;
        }
    }
    fclose(file);
    return lines;
}
void write_file(const char *filename, char **lines) 
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        exit(1);
    }
    for (int i = 0; i < MAX_ELEVES; i++) {
        if (lines[i] != NULL) {
            fprintf(file, "%d : %s",i+1, lines[i]);
        }
    }
    fclose(file);
}
void update_line(char **lines, int line_num, const char *new_content) 
{
    if (line_num < 1 || line_num > MAX_ELEVES) 
    {
        printf("Numero de ligne invalide.\n");
        return;
    }

    // Effacer le contenu de la ligne line_num et remplacer par new_content
    free(lines[line_num - 1]);
    lines[line_num - 1] = strdup(new_content);
}
void free_lines(char **lines)
{
    for (int i = 0; i < MAX_ELEVES; i++) 
    {
        if (lines[i] != NULL) {
            free(lines[i]);
        }
    }
    free(lines);
}

int file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        fclose(file);
        return 1;
    }
    return 0;
}

void check(eleve *l1) 
{
    stock_struct(l1);

    char **lines;
    if (file_exists("liste2.csv"))
    {
        lines = read_file("liste2.csv");
    }
    else
    {
        lines = read_file("liste.csv");
    }

    int numero;
    int i;
    int valeur;
    int resultat;
    char status[10];
    char new_content[MAX_LINE_LENGTH];

    for ( i = 0; i < MAX_ELEVES; i++) 
    {
        while (1)
        {
            printf("Entrer le numero dans la liste d'appel de l'étudiant \n0 Retour et sauvegarde ! : ");
            resultat = scanf("%d", &numero);
            if (resultat != 1)
            {
                printf ("Veuillez saisir un nombre entier.\n");
                while ( getchar() != '\n' );               
            }
            else
                break;
        }
        
        
        if (numero == 0)
            break;

        if (numero < 1 || numero > MAX_ELEVES) 
        {
            printf("Numéro invalide, veuillez réessayer.\n");
            i--;
            continue;
        }
		
		printf("  Entrer la présence pc\n");
		printf("╔══════════════════════════════════════════════╗\n");
		printf("  -[0] ou [OUI] si vous prenez un pc \n");
		printf("  -[1] ou [NON] si non \n");
		printf("  -[2] ou [ABS] si absent \n");
		printf("  -[3] ou [PERSO] si vous avez un pc personnel\n");
		printf("╚══════════════════════════════════════════════╝\n");
        printf("  pour %s \n=> ", l1[numero-1].nom);
 
        scanf("%9s", status);
        for ( i = 0; status[i]; i++) {
            status[i] = toupper(status[i]);
        }        
        valeur = convert_status_to_presence(status);
        switch ( valeur)
        {
        case OUI:
            sprintf(new_content, "%s  OUI\n", l1[numero-1].nom);
            break;
        case NON:
            sprintf(new_content, "%s  NON\n", l1[numero-1].nom);
            break;
        case ABS:        
            sprintf(new_content, "%s  ABS\n", l1[numero-1].nom);
            break;
        case PERSO:
            sprintf(new_content, "%s  PERSO\n", l1[numero-1].nom);
            break;
        default:
            printf("Choix invalide\n");
            break;
        }
        if(new_content != NULL )
        {
            update_line(lines, numero, new_content);
        }
    }

    write_file("liste2.csv", lines);
    printf("Saved!\n");
    free_lines(lines);
}
void choix ()
{
    const char* ANSI_COLOR_CYAN = "\x1b[36m";
    const char* ANSI_COLOR_RESET = "\x1b[0m";

    eleve l1[MAX_ELEVES];
    int choix;
    int resultat;
    int checked_pc;

    stock_struct(l1);
    do
    {
        printf("\n");
        printf(" ╔══════════════════════════════════════════════════╗\n");
        printf(" ║            	 %sCHECK-PC-L1%s                        ║\n",ANSI_COLOR_CYAN,ANSI_COLOR_RESET);
        printf(" ║  [1].Afficher toutes les listes des eleves L1    ║\n");                
        printf(" ║  [2].Rechercher un élève                         ║\n");
        printf(" ║  [3].Check PC                                    ║\n");
        if(checked_pc)
        {
             printf(" ║  [4].Vérification de présence                   ║ \n");
        }
        printf(" ║  [0].Quitter                                     ║ \n");
        printf(" ╚══════════════════════════════════════════════════╝\n");
        while (1)
        {
			printf ("votre choix : \n=> ");
            resultat = scanf ("%d",&choix);

            if(resultat != 1)
            {
                printf ("Veuillez ressayer !\n");
                while (getchar() != '\n' );
            }
            else 
                break;
        }

        switch (choix)
        {
            case 1:
                display_list(l1);
                break;
            case 2:
                resultat = 0;
                printf("        ╔═══════════════════════╗\n");
                printf("        ║ [1]. par numero       ║\n");
                printf("        ║ [2]. par nom          ║\n");
                printf("        ╚═══════════════════════╝\n"); 
                while (1)
                {
                    choix = 0;
                    resultat = scanf("%d",&choix);
                    if( resultat != 1 )
                    {
                        printf ("Veuillez saisir un nombre entier.\n");
                        while ( getchar() != '\n' );
                    }
                    else
                        break;
                }
                switch( choix )
                {
                    case 1:
                        search_num(l1);
                        break;
                    case 2:
                        search_name(l1);
                        break;
                    default :
                        printf("choix invalide \n");
                        break;
                }
                break;
            case 3:
                check(l1);
                checked_pc = 1;
                break;
            case 4:
				printf("╔════════════════════════════════════╗\n");
                printf (" => 1.affiche liste avec presence\n");
                printf (" => 2.afiche liste des eleves : \n");
                printf("╚════════════════════════════════════╝\n"); 
                resultat = 0;
                while (1)
                {
                    choix = 0;
                    resultat = scanf ("%d",&choix);
                    if (resultat != 1)
                    {
                        printf ("Veuillez saisir un entier \n");
                        while (getchar() != '\n' );                        
                    }
                    else
                        break;
                }
                switch (choix)
                {
                    case 1:
                        display_default("liste2.csv");
                        break;
                    case 2:
                        choix = 0;
                        resultat = 0;
                        printf("╔════════════════════════════════╗\n");
                        printf (" [1].Affichage des présents\n");
                        printf (" [2].Affichage des absents\n");
                        printf("╚════════════════════════════════╝\n"); 
                        while (1)
                        {
                            printf ("votre choix : \n=> ");
                            resultat = scanf ("%d",&choix);
                            if (resultat != 1)
                            {
                                printf ("Veuillez saisir a nouveau un entier.\n");
                                while ( getchar() != '\n');
                            }
                            else 
                                break;
                        }
                        switch (choix)
                        {
                        case 1:
                            display_check_yes(l1);
                            
                            break;
                        case 2:
                            display_check_abs(l1);
                            break;
                        default:
                            break;
                        }

                        break;
                    default:
                        printf ("Choix invalide. Veuillez choisir a nouveau.\n");
                        break;
                }
                break;
            default:
                break;

        }
        

    } while (choix != 0);
    

}
