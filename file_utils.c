#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
    while ( fgets(l1[nbr_len].name, 100 , fic) != NULL )
    {                                                            // char *tab;
        l1[nbr_len].name[strcspn(l1[nbr_len].name, "\n")] = '\0'; // esorina le '\n' de ovaina nul  
        l1[nbr_len].num = nbr_len + 1;
        nbr_len++;
    }
    fclose(fic);
}
void search_num(eleve *l1) 
{
    int n, i;
    printf("Entrez le numero de l'eleve a rechercher :\n=> ");
    scanf("%d", &n);


    if ( n > 0  &&  n <= MAX_ELEVES )
    {
        for (i = 0; i < MAX_ELEVES; i++) 
        {
            if (l1[i].num == n) 
            {
                printf("%d : %s\n", l1[i].num, l1[i].name);
                break;
            }
        }
    }
    else
        printf("Veuillez saisir un numero existant dans la liste l1 \"1-75\"\n");
}
void search_name(eleve *l1) 
{
    char temp_name[100];
    char nom_eleve[100];
    int i, j, trouve = 0;

    printf("Entrez le nom ou prenom de l'eleve a rechercher : \n=> ");
    getchar();
    fgets(temp_name, sizeof(temp_name) , stdin); //scanf => temp_name 
    temp_name[strcspn(temp_name, "\n")] = '\0';

    for (i = 0; temp_name[i]; i++) 
    {
        temp_name[i] = toupper(temp_name[i]);
    }
    for (i=0; i < MAX_ELEVES; i++) 
    {
        strcpy(nom_eleve, l1[i].name);
        for (j = 0; nom_eleve[j]; j++) {
            nom_eleve[j] = toupper(nom_eleve[j]);
        }

        if (strstr(nom_eleve, temp_name) != NULL) 
        {
            printf(" %d : %s \n", l1[i].num, l1[i].name);
            trouve = 1;
        }
    }
    if (!trouve) 
    {
        printf("Aucun eleve trouve avec le nom contenant \"%s\".\n",temp_name);
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
        printf("  %d 		  %s \n", l1[i].num, l1[i].name);
        
      
    }
    printf("╚═════════════╚═══════════════════════════════════════════════╝\n");
}
presence convert_status_to_presence(char *status)
{
    presence valeur;

    if (strcmp(status, "OUI") == 0 || strcmp(status, "0") == 0
        || strcmp(status, "YES") == 0) 
    {
        valeur = OUI;
    } 
    else if (strcmp(status, "NON") == 0 || strcmp(status, "1") == 0
            || strcmp(status, "NO") == 0 ) 
    {
        valeur = NON;
    } 
    else if (strcmp(status, "PERSONEL") == 0 || strcmp(status, "3") == 0
            || strcmp(status, "PERSO") == 0) 
    {
        valeur = PER;
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
char** read_file( const char *filename)
{
    int i;
    char temp[MAX_LINE_LENGTH];
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    } 

    char **lines = (char**)malloc (MAX_ELEVES * sizeof(char*));
    if ( lines == NULL ) 
    {
        perror("Erreur d'allocation de mémoire");
        fclose(file);
        return NULL;
    }
    for (i = 0; i < MAX_ELEVES; i++) 
    {
        if (fgets(temp, MAX_LINE_LENGTH, file) != NULL) 
        {
            lines[i] = strdup(temp);
        }
        else 
        {
            lines[i] = NULL;
        }
    }  
    fclose (file);
    return lines; 
}
void write_file(const char *filename, char **lines)
{
    int i;
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        exit(1);
    }
    for (i = 0; i < MAX_ELEVES; i++) {
        if (lines[i] != NULL) 
        {
            fprintf(file, "%s", lines[i]);
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
    free(lines[line_num - 1]);
    lines[line_num - 1] = strdup(new_content);
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
void check(eleve *l1) {
    int i, valeur, numero;
    char status[10];
    char new_content[MAX_LINE_LENGTH];
    char **lines;

    // Lire le fichier. Si liste2.csv n'existe pas, lire liste.csv.
    if (file_exists("liste2.csv")) {
        lines = read_file("liste2.csv");
    } else {
        lines = read_file("liste.csv");
    }

    if (lines == NULL) {
        printf("Erreur de lecture du fichier.\n");
        return;
    }

    for (i = 0; i < MAX_ELEVES; i++) {
        while (1) {
            printf("Entrer le numéro dans la liste d'appel de l'étudiant\n0 Retour et sauvegarde ! : ");
            if (scanf("%d", &numero) != 1) {
                printf("Veuillez saisir un nombre entier.\n");
                while (getchar() != '\n');
            } else {
                break;
            }
        }

        if (numero == 0) {
            break; // Quitter la boucle si l'utilisateur entre 0
        }

        if (numero < 1 || numero > MAX_ELEVES) {
            printf("Numéro invalide, veuillez réessayer.\n");
            i--; // Réessayer pour le même index
            continue;
        }

        printf("Entrer la présence PC\n");
        printf("╔══════════════════════════════════════════════╗\n");
        printf("║  -[0] ou [OUI] si vous prenez un PC          ║ \n");
        printf("║  -[1] ou [NON] si non                        ║ \n");
        printf("║  -[2] ou [ABS] si absent                     ║ \n");
        printf("║  -[3] ou [PERSO] si vous avez un PC personnel║ \n");
        printf("╚══════════════════════════════════════════════╝\n");
        printf("Pour %s \n=> ", l1[numero - 1].name);

        scanf("%9s", status);
        for (int j = 0; status[j]; j++) {
            status[j] = toupper(status[j]);
        }

        valeur = convert_status_to_presence(status);

        switch (valeur) {
            case OUI:
                sprintf(new_content, "%s:OUI\n", l1[numero - 1].name);
                break;
            case NON:
                sprintf(new_content, "%s:NON\n", l1[numero - 1].name);
                break;
            case ABS:
                sprintf(new_content, "%s:ABS\n", l1[numero - 1].name);
                break;
            case PER:
                sprintf(new_content, "%s:PER\n", l1[numero - 1].name);
                break;
            default:
                printf("Choix invalide\n");
                continue;
        }

        update_line(lines, numero, new_content);
    }

    write_file("liste2.csv", lines);
    printf("Sauvegardé !\n");
    free_lines(lines);
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
void cut_struct(char **lines, eleve *l1_1) 
{
    int i;
    for ( i = 0; i < MAX_ELEVES && lines[i] != NULL; i++) 
    {
        char *token = strtok(lines[i], ":");
        if (token != NULL) 
        {
            strncpy( l1_1[i].nom, token, 50 );
            token = strtok(NULL, ":");
            if (token != NULL) 
            {
                strncpy(l1_1[i].prenom, token, 50);
                token = strtok(NULL, ":");
                if (token != NULL)
                {
                    strncpy(l1_1[i].stat, token ,50);
                } 
            }
        }
    }
}

void write_file_to_html(const char *filename, eleve *l1_1) 
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        exit(1);
    }

    fprintf(file, "	<HTML>										\n");
    fprintf(file, " 	   <HEAD>\n");
    fprintf(file, "     	   <TITLE>Liste des Élèves</TITLE>		\n");
    fprintf(file, "	   	   </HEAD>									\n");
    fprintf(file, "	       <BODY>									\n");
    fprintf(file, " 	       <TABLE border='1'>					\n");		//nampiako couleur
    fprintf(file, "     	       <TR>								\n");
    fprintf(file, "         	       <TH>Numéro</TH>				\n");
    fprintf(file, "             	   <TH>Nom</TH>					\n");
    fprintf(file, "               	   <TH>Prénom(s)</TH>				\n");
    fprintf(file, "                	   <TH>Présence</TH>			\n");
    fprintf(file, "          	  </TR>							\n");

    for (int i = 0; i < MAX_ELEVES; i++) {
        fprintf(file, "            <TR bordercolor = \'#000000\'>\n");
        fprintf(file, "                <TD>%d</TD>					\n", i+1);
        fprintf(file, "                <TD>%s</TD>					\n", l1_1[i].nom);
        fprintf(file, "                <TD>%s</TD>					\n", l1_1[i].prenom);
        ///couleur présence
        l1_1[i].stat[3] = '\0';
        if (strcmp("OUI",l1_1[i].stat) == 0){
			fprintf(file, "                <TD style = \"color:#1E90FF;\">%s</TD>					\n", l1_1[i].stat);
		}
		else if (strcmp("NON",l1_1[i].stat) == 0){
			fprintf(file, "                <TD style = \"color:#F15321;\">%s</TD>					\n", l1_1[i].stat);
		}
		else if (strcmp("PERS",l1_1[i].stat) == 0){
			fprintf(file, "                <TD style = \"color:#FFFF00;\">%s</TD>					\n", l1_1[i].stat);
		}
		else if (strcmp("ABS",l1_1[i].stat) == 0){
			fprintf(file, "                <TD style = \"color:#1A1A1A;\">%s</TD>					\n", l1_1[i].stat);
		}
        fprintf(file, "            </TR>							\n");
    }	

	fprintf(file,"			<BUTTON>CLOSE</BUTTON>\n");
    fprintf(file, "    </BODY>										\n");
    fprintf(file, "</HTML>											\n");

    printf("List saved in test.html									\n");
    fclose(file);
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
void export_html ()
{
    int i;
    eleve l1_1[MAX_ELEVES];
    char **lines = read_file ("liste2.csv");
    
    FILE *fic = NULL;
    fic = fopen("test.html","w");
    cut_struct (lines,l1_1);

    printf ("Exporting file to .html \n");

    write_file_to_html ("test.html",l1_1);
    for (i = 0; i < MAX_ELEVES; i++) {
        free(lines[i]);
    }
    free(lines);
}
void fonct_case (int choix,eleve *l1,eleve *l1_1)
{
    int resultat;
       switch (choix)
        {
            case LIST:
                display_list(l1);
                break;
            case SEARCH:
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
                switch(choix)
                {
                    case NUM:
                        search_num(l1);
                        break;
                    case NOM:
                        search_name(l1);
                        break;
                    default :
                        printf("choix invalide \n");
                        break;
                }
                break;
            case CHECK:
                check(l1);
                break;
            case PRESENT:
                display_default("liste2.csv");
                break;
            case EXPORT:
                export_html ();
            default:
                break;

        }    
}
void choix ()
{
    const char* ANSI_COLOR_CYAN = "\x1b[36m";
    const char* ANSI_COLOR_RESET = "\x1b[0m";

    eleve l1[MAX_ELEVES];
    eleve l1_1[MAX_ELEVES];
    int choix;
    int resultat;

    stock_struct(l1);
    do
    {
        printf("\n");
        printf(" ╔══════════════════════════════════════════════════╗\n");
        printf(" ║            	 %sCHECK-PC-L1%s                        ║\n",ANSI_COLOR_CYAN,ANSI_COLOR_RESET);
        printf(" ║  [1].Afficher toutes les listes des eleves L1    ║\n");                
        printf(" ║  [2].Rechercher un élève                         ║\n");
        printf(" ║  [3].Check PC                                    ║\n");
        printf(" ║  [4].Vérification de présence                    ║ \n");
        printf(" ║  [5].Export list to html                         ║ \n");
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
        fonct_case (choix,l1,l1_1);
    } while (choix != 0);
    
}
