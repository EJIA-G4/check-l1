typedef enum 
{
    OUI=0,
    NON=1,
    ABS=2,
    PER=3
} presence;

typedef struct  
{
    char name[100];
    char nom[50];
    char prenom[50];
    char stat[50];
    int num;
    presence pc;
} eleve;

typedef enum
{
    QUIT=0,
    LIST=1,
    SEARCH=2,
    CHECK=3,
    PRESENT=4,
    EXPORT=5
}choice;

typedef enum
{
    NUM=1,
    NOM=2
}type;

void stock_struct (eleve *l1);
void search_num(eleve *l1);
void search_name(eleve *l1);
void display_list(eleve *l1);
presence convert_status_to_presence(char *status);
char** read_file( const char *filename);
void write_file(const char *filename, char **lines);
void update_line(char **lines, int line_num, const char *new_content);
int file_exists(const char *filename);
void fonct_switch (int valeur,int numero,eleve *l1);
void check(eleve *l1);
void display_default (char *filename);
void cut_struct(char **lines, eleve *l1_1);
void write_file_to_html(const char *filename, eleve *l1_1);
void export_html ();
void fonct_case (int choix,eleve *l1,eleve *l1_1);
void choix ();
void free_lines(char **lines);
