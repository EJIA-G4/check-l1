typedef enum 
{
    OUI=0,
    NON=1,
    ABS=2,
    PERSO=3
} presence;

typedef struct  
{
    char nom[100];
    int num;
    presence pc;
} eleve;

void stock_struct (eleve *l1);
void search_num(eleve *l1);
void search_name(eleve *l1);
void display_list(eleve *l1);
void display_default (char *filename);
void display_check_abs(eleve *l1_1);
void display_check_yes(eleve *l1_1);
void stockData(eleve *l1);
char** read_file(const char *filename);
void write_file(const char *filename, char **lines);
void update_line(char **lines, int line_num, const char *new_content);
void free_lines(char **lines);
void check(eleve *l1);
int file_exists(const char *filename);
void choix ();
