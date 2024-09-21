#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"

#define MAX_CHARACTERE 50
#define MAX_DESCRIPTION 500
#define MAX_STATUS 20
#define MAX_DATE 12

typedef struct {
    char id[MAX_CHARACTERE];
    char Nom[MAX_CHARACTERE];
    char Email[MAX_CHARACTERE]; 
    char Password[MAX_CHARACTERE];
    int  Role;
}Utilisateurs;

typedef struct 
{
    char id[MAX_CHARACTERE];
    char Motif[MAX_CHARACTERE];
    char Description[MAX_DESCRIPTION];
    char Categorie[MAX_CHARACTERE];
    char Note[MAX_CHARACTERE];
    char Status[MAX_STATUS];
    char date[MAX_DATE];
    int priorite;         
    int id_client; 
    time_t heure_de_debut;
   
}Reclamation;

Utilisateurs *user = NULL;
Reclamation *rec = NULL;

int Taille = 0;
int R_Taille = 0;
int index_user = -1;

int Incription();
int Connexion();

// Les Menu (Admin / Client / Agent)
int Choix(int *choix);
int Choix_Admin(int *choix);
int Choix_Agent(int *choix);

// Les Fonction de Reclamation
void Afficher_tout_les_Reclamation();
void Afficher_Reclamation();
int Ajouter_un_Reclamation();
int Modifier_un_Reclamation();
int Supprimer_un_Reclamation();
int verifier_duree(time_t heure_de_debut);

// Les Fonction de L'admin et L'agent
int Modifier_Role_Utilisateur();
int Modifier_Status_Utilisateur();

int main(){

    printf("\n\t  \x1b[35m========================================\x1b[0m");
    printf("\n\t  \x1b[35m||      BIENVENU A L'APPLICATION      ||\x1b[0m\n");
    printf("\t  \x1b[35m========================================\x1b[0m\n");

    int auth = -1 , choix = 0  , r_choix = 0 , choix_admin = 0 , choix_agent = 0;

    user = malloc(Taille*sizeof(Utilisateurs));
    rec = malloc(Taille*sizeof(Reclamation));

    while(1){

        int connect = 0;

        do{
        // Authentification ---------------------- 
            printf("\n"
               "\t==============================================\n\t"
               "|             \033[36m AUTHENTIFICATION \033[0m             |\n"
               "\t==============================================\n\t"
               "|\t                                     |\n\t"
               "|\t      [1] INSCRIPTION                |\n\t"
               "|\t      [2] CONNEXION                  |\n\t"
               "|\t      [\033[33m5\033[0m] \033[33mQUITTER\033[0m                    |\n"
               "\t|                                            |\n"
               "\t==============================================\n\t"
               "\n\tTapez votre choix => : ");
            scanf("%d" , &auth);
            while(getchar()  != '\n'); 

        switch (auth)
        {
            case 1 :
                int valid_inscr = Incription();
                if(valid_inscr){
                    printf("\n\t \x1b[32m--- Inscription Reussite ---\x1b[0m\n");
                    index_user = Taille;
                    Taille++;
                    connect = 1;
                    auth = 0;
                } else printf("\n\t --- Inscription Invalid --- \n");
                break;
            case 2 :
                int index = Connexion();
                if(index >= 0){
                    printf("\n\t \x1b[32m--- Connexion Reussite ---\x1b[0m\n");
                    index_user = index;
                    connect = 1;
                    auth = 0;
                } 
                else {
                    printf("\n\t \x1b[31m Veuillez Essayer apres 10s ... \x1b[0m \n");
                    Sleep(10000);
                } 
                break;
        
        default:
            break;

        }
    
    }while(auth != 0);

    if(connect && user[index_user].Role == 0){
        while(1){

        int valid_choix = Choix(&r_choix);

        if (valid_choix == 0 || r_choix < 1 || r_choix > 5){
            printf("\n\t \x1b[31m---- Choix Invalid ----\x1b[0m \n");
        }else {

             switch (r_choix){

                case 1:
                    int valid_Ajoute = Ajouter_un_Reclamation();
                    if(valid_Ajoute){
                        printf("\n\t \x1b[32m--- Le Contact a ete Ajoute avec Succes ----\x1b[0m \n");
                        R_Taille++;
                    }else{
                        printf("\n\t \x1b[31m--- Erreur d'ajoutr ----\x1b[0m \n");
                    }
                break;
                case 2:
                    Afficher_Reclamation();
                    break;
                case 3 :
                    int valid_mod = Modifier_un_Reclamation();
                    if(valid_mod){
                        printf("\n\t \x1b[32m--- La Reclamation a ete Modifiier avec Succes ----\x1b[0m \n");
                    }else{
                        printf("\n\t \x1b[31m--- Erreur lors de Modification ----\x1b[0m \n");
                    }
                    break;
                case 4 :
                    int valid_sup = Supprimer_un_Reclamation();
                    if(valid_sup == 1){
                        printf("\n\t \x1b[32m--- La Reclamation a ete Supprimer avec Succes ----\x1b[0m \n");
                    }else if(valid_sup == 2){
                        printf("\n\t \x1b[33m--- Aucun Recalamtion a Supprimer --- \x1b[0m\n");
                    }else{
                        printf("\n\t \x1b[31m--- Erreur lors de Suppression ----\x1b[0m \n");
                    }
                    break;
                case 5 :
                    auth = -1;
                    break;
                
                default:
                    break;
            }
        }

        if(auth != 0) break;
    
        }

    }else if(connect && user[index_user].Role == 2){

        while(1){

        int valid_choix = Choix_Agent(&choix_agent);

        if (valid_choix == 0 || choix_agent < 1 || choix_agent > 6){
            printf("\n\t \x1b[31m---- Choix Invalid ----\x1b[0m \n");
        }else{

             switch (choix_agent){

                case 1:
                    int valid_Ajoute = Ajouter_un_Reclamation();
                    if(valid_Ajoute){
                        printf("\n\t \x1b[32m--- Le Contact a ete Ajoute avec Succes ----\x1b[0m \n");
                        R_Taille++;
                    }else{
                        printf("\n\t \x1b[31m--- Erreur d'ajoutr ----\x1b[0m \n");
                    }
                break;
                case 2:
                    Afficher_tout_les_Reclamation();
                    break;
                case 3 :
                    int valid_mod = Modifier_un_Reclamation();
                    if(valid_mod){
                        printf("\n\t \x1b[32m--- La Reclamation a ete Modifiier avec Succes ----\x1b[0m \n");
                    }else{
                        printf("\n\t \x1b[31m--- Erreur lors de Modification ----\x1b[0m \n");
                    }
                    break;
                case 4 :
                    int valid_sup = Supprimer_un_Reclamation();
                    if(valid_sup == 1){
                        printf("\n\t \x1b[32m--- La Reclamation a ete Supprimer avec Succes ----\x1b[0m \n");
                    }else if(valid_sup == 2){
                        printf("\n\t \x1b[33m--- Aucun Recalamtion a Supprimer --- \x1b[0m\n");
                    }else{
                        printf("\n\t \x1b[31m--- Erreur lors de Suppression ----\x1b[0m \n");
                    }
                    break;
                case 5 :
                        int valid_status = Modifier_Status_Utilisateur();
                         if(valid_status){
                            printf("\n\t \x1b[32m--- Le Status de Reclamation a ete modifier avec succes ----\x1b[0m \n");
                        }else{
                            printf("\n\t \x1b[31m--- Erreur lors de Modification de Recalamtion ----\x1b[0m \n");
                    }
                    break;
                case 6 :
                    auth = -1;
                    break;
                default:
                    break;
            }
        }

        if(auth != 0) break;
    
        }
    }else if(connect && user[index_user].Role == 1){
         while(1){

        int valid_choix = Choix_Admin(&choix_admin);

        if (valid_choix == 0 || choix_admin < 1 || choix_admin > 12){
            printf("\n\t \x1b[31m---- Choix Invalid ----\x1b[0m \n");
        }else{

             switch (choix_admin){

                case 1:
                    int valid_Ajoute = Ajouter_un_Reclamation();
                    if(valid_Ajoute){
                        printf("\n\t \x1b[32m--- Le Contact a ete Ajoute avec Succes ----\x1b[0m \n");
                        R_Taille++;
                    }else{
                        printf("\n\t \x1b[31m--- Erreur d'ajoutr ----\x1b[0m \n");
                    }
                break;
                case 2:

                    Afficher_tout_les_Reclamation();
                    break;
                case 3 :
                    int valid_mod = Modifier_un_Reclamation();
                    if(valid_mod){
                        printf("\n\t \x1b[32m--- La Reclamation a ete Modifiier avec Succes ----\x1b[0m \n");
                    }else{
                        printf("\n\t \x1b[31m--- Erreur lors de Modification ----\x1b[0m \n");
                    }
                    break;
                case 4 :
                    int valid_sup = Supprimer_un_Reclamation();
                    if(valid_sup == 1){
                        printf("\n\t \x1b[32m--- La Reclamation a ete Supprimer avec Succes ----\x1b[0m \n");
                    }else if(valid_sup == 2){
                        printf("\n\t \x1b[33m--- Aucun Recalamtion a Supprimer --- \x1b[0m\n");
                    }else{
                        printf("\n\t \x1b[31m--- Erreur lors de Suppression ----\x1b[0m \n");
                    }
                    break;
                case 5 :
                        int valid_role = Modifier_Role_Utilisateur();
                         if(valid_role){
                            printf("\n\t \x1b[32m--- Le Role D'utilisateur a ete modifier avec succes ----\x1b[0m \n");
                        }else{
                            printf("\n\t \x1b[31m--- Erreur lors de Modification de role ----\x1b[0m \n");
                    }
                    break;
                case 6 :
                        int valid_status = Modifier_Status_Utilisateur();
                         if(valid_status){
                            printf("\n\t \x1b[32m--- Le Status de Reclamation a ete modifier avec succes ----\x1b[0m \n");
                        }else{
                            printf("\n\t \x1b[31m--- Erreur lors de Modification de Recalamtion ----\x1b[0m \n");
                    }
                    break;
                    break;
                case 7 :
                    break;
                case 8 :
                    break;
                case 9 :
                    break;
                case 10 :
                    break;
                case 11 :
                    break;
                case 12 :
                    auth = -1;
                    break;
                
                default:
                    break;
            }
        }

        if(auth != 0) break;
    
        }
    }
}
}

// Les Menu D'application ------------------------------------------------------------------------

int Choix(int *choix){
    int ch;
        printf("\n");
        printf(CYAN "\t=========================================================\n\t" RESET);
        printf( "\033[36m||\033[0m                  \x1b[32m Espace Client \033[0m                    \033[36m||\033[0m \n" );
        printf(CYAN "\t=========================================================\n\t" RESET);
        printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
        printf( "\033[36m||\033[0m\t \x1b[33m[1] Ajouter un Reclamation \x1b[0m                   \033[36m||\033[0m\n\t" );
        printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
        printf( "\033[36m||\033[0m\t \x1b[33m[2] Afficher la list des Reclamation\x1b[0m          \033[36m||\033[0m\n\t" );
        printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
        printf( "\033[36m||\033[0m\t \x1b[33m[3] Modifier un Reclamation \x1b[0m                  \033[36m||\033[0m\n\t" );
        printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
        printf( "\033[36m||\033[0m\t \x1b[33m[4] Supprimer un Reclamation  \x1b[0m                \033[36m||\033[0m\n\t" );
        printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
        printf( "\033[36m||\033[0m\t \x1b[31m[5] Deconnecter \x1b[0m                              \033[36m||\033[0m\n");
        printf( "\t\033[36m||\033[0m\t                                               \033[36m||\033[0m\n");
        printf(CYAN "\t=========================================================\n\t" RESET);
        printf("\n\tTapez votre choix => : ");
               ch = scanf("%d", choix);
               while(getchar() != '\n');
               if(ch) return ch;
               else return 0;
}

int Choix_Agent(int *choix){
            int ch;
            printf("\n");
            printf(CYAN "\t=========================================================\n\t" RESET);
            printf( "\033[36m||\033[0m            \x1b[32m Espace D'Agent de Reclamation \033[0m          \033[36m||\033[0m \n" );
            printf(CYAN "\t=========================================================\n\t" RESET);
            printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
            printf( "\033[36m||\033[0m\t \x1b[33m[1] Ajouter un Reclamation \x1b[0m                   \033[36m||\033[0m\n\t" );
            printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
            printf( "\033[36m||\033[0m\t \x1b[33m[2] Afficher la list des Reclamation\x1b[0m          \033[36m||\033[0m\n\t" );
            printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
            printf( "\033[36m||\033[0m\t \x1b[33m[3] Modifier un Reclamation \x1b[0m                  \033[36m||\033[0m\n\t" );
            printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
            printf( "\033[36m||\033[0m\t \x1b[33m[4] Supprimer un Reclamation  \x1b[0m                \033[36m||\033[0m\n\t" );
            printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
            printf( "\033[36m||\033[0m\t \x1b[33m[5] Modifier Le Status d'une Reclamation \x1b[0m     \033[36m||\033[0m\n\t" );
            printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
            printf( "\033[36m||\033[0m\t \x1b[31m[6] Deconnecter \x1b[0m                              \033[36m||\033[0m\n");
            printf( "\t\033[36m||\033[0m\t                                               \033[36m||\033[0m\n");
            printf(CYAN "\t=========================================================\n\t" RESET);
            printf("\n\tTapez votre choix => : ");
            ch = scanf("%d", choix);
            while(getchar() != '\n');
            if(ch) return ch;
            else return 0;
}

int Choix_Admin(int *choix){

    printf("\n");
    printf(CYAN "\t=========================================================\n\t" RESET);
    printf( "\033[36m||\033[0m              \x1b[32m Espace Administrateur \033[0m                \033[36m||\033[0m \n" );
    printf(CYAN "\t=========================================================\n\t" RESET);
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[1] Ajouter un Reclamation \x1b[0m                   \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[2] Afficher la list des Reclamation\x1b[0m          \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[3] Modifier un Reclamation \x1b[0m                  \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[4] Supprimer un Reclamation  \x1b[0m                \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[5] Modifier Le Role d'un Utilisateur \x1b[0m        \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[6] Modifier Le Status d'une Reclamation \x1b[0m     \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[7] Nombre Total de Reclamation \x1b[0m              \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[8] Taux de Resolution des Reclamations \x1b[0m      \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[9] Statistic et rapports \x1b[0m                    \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[10] Calculer Le Delai Moyen de Traitement \x1b[0m   \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[33m[11] Rapport Journalier \x1b[0m                      \033[36m||\033[0m\n\t" );
    printf( "\033[36m||\033[0m\t                                               \033[36m||\033[0m\n\t");
    printf( "\033[36m||\033[0m\t \x1b[31m[12] Deconnecter \x1b[0m                             \033[36m||\033[0m\n");
    printf( "\t\033[36m||\033[0m\t                                               \033[36m||\033[0m\n");
    printf(CYAN "\t=========================================================\n\t" RESET);
    printf("\n\tTapez votre choix => : ");

    int chx = scanf("%d" , choix);
    while(getchar() != '\n');

    return chx;

}

// Authentification ------------------------------------------------------------------------

int Incription(){

    int i;
    user = realloc(user , (Taille + 1)*sizeof(Utilisateurs));

    if(user == NULL){
        printf("\n\t \x1b[31m--- Erreur D'allocation ----\x1b[0m\n");
        return 0;
    }

    Utilisateurs user_inscr;
    printf("\n\t \x1b[32m---- Inscription ----\x1b[0m \n");
 
    // generer L'id ----------- 
    srand(time(NULL));
    while(1){

        int counter = 0 , i;  
        char Generate_id[100];

        for(i=0;counter<100;i++){
            char random = 48 + (rand() % 74);
            if( (random >= 48 && random <= 57 ) || (random >= 65 && random <= 90 ) || (random >= 97 && random <= 122 )){
                Generate_id[i] = random; 
                counter++;      
                
            }
        }

        Generate_id[i] = '\0';

        int exist = 1;
        for(i=0;i<Taille;i++){
            if(strcmp(user_inscr.id,Generate_id) == 0) exist = 0;
        }

        if(exist && strlen(Generate_id) > 10 ){
            strncpy(user_inscr.id , Generate_id , 10);
            break;
        }

    }
    
    // Validation de nom -------
    int nom_count = 0 ;
    while(1){
        printf("\n\t -- Nom d'utilisateur : ");
        int valide_input = scanf(" %[^\n]s" , user_inscr.Nom);
        
        int i = 0 , valid_nom = 1;
        while(user_inscr.Nom[i] != '\0'){
            if( (user_inscr.Nom[i] >= 65 && user_inscr.Nom[i] <= 90) || (user_inscr.Nom[i] >= 97 && user_inscr.Nom[i] <= 122)){
                valid_nom = 1;
            }else{
                valid_nom = 0;
                break;
            }
            i++;
        }

        if(valide_input && strlen(user_inscr.Nom) > 3 && valid_nom){
            break;
        }else if(nom_count > 2){
            return 0;
        }else{
            nom_count++;
            printf("\n\t \x1b[31m-- Invalid Nom --\x1b[0m \n");
        }
    }

    // Validation d'email -------
    int email_count = 0; 
    while(1){
        printf("\n\t -- Email   : ");
        int valide_input = scanf(" %[^\n]s" , user_inscr.Email);
        while(getchar() != '\n');

        int valid_email = 1;
        
        char *arb = strchr(user_inscr.Email , '@'); 
        if(arb != NULL){
            char *point = strchr( arb,'.');
            if(point != NULL){
                valid_email = 1;
            } else {
                valid_email = 0;
            }

        }else{
            valid_email = 0;
        }

        if(valide_input && strlen(user_inscr.Email) > 3 && valid_email){
            break;
        }else if(email_count > 2){
            return 0;
        }else{
            email_count++;
            printf("\n\t \x1b[31m-- Invalid Email --\x1b[0m \n");
        }
    }
    
    // Validation de Mot de Pass 
    while(1){

        printf("\n\t -- Password   : ");
        int valide_input = scanf(" %[^\n]s" , user_inscr.Password);
        
        int i = 0 , maj = 0 , min = 0 , chiffre = 0 , charactere = 0;
        int valid_password = 0;

        while(user_inscr.Password[i] != '\0'){
            if(user_inscr.Password[i] >= 47 && user_inscr.Password[i] <= 57){
                chiffre = 1;
            }else if(user_inscr.Password[i] >= 65 && user_inscr.Password[i] <= 90){
                maj = 1;
            }else if(user_inscr.Password[i] >= 97 && user_inscr.Password[i] <= 122){
                min = 1;
            }else if(user_inscr.Password[i] >= 58 && user_inscr.Password[i] <= 64){
                charactere = 1;
            }
            i++;
        }

        valid_password = maj + min + chiffre + charactere;

        if(valide_input && strlen(user_inscr.Password) > 8 && valid_password >= 4){
            break;
        }else if(nom_count > 2){
            return 0;
        }else{
            nom_count++;
            printf("\n\t \x1b[31m-- Invalid Password --\x1b[0m \n");
        }       

    }
    
    // Role 
    if(Taille == 0)
        user_inscr.Role = 1;
    else 
        user_inscr.Role = 0;

    user[Taille] = user_inscr; 

    return 1;
}

int Connexion(){

    char Nom[MAX_CHARACTERE];
    char Password[MAX_CHARACTERE];

    // Validation de nom -------
    int nom_count = 0;
    while(1){
        int valid_nom = 0 , valid_password = 0 , index = 0;
        printf("\n\t -- Nom d'utilisateur : ");
        scanf(" %[^\n]s" , Nom);

        printf("\n\t -- Password : ");
        scanf(" %[^\n]s" , Password);

        for(int i=0;i<Taille;i++){
            if(strcmp(user[i].Nom , Nom) == 0){
                valid_nom = 1;
                if(strcmp(user[i].Password , Password) == 0){
                    valid_password = 1;
                    index = i;
                    break;
                }
            }
        }

        if(valid_nom && valid_password){
            return index;
        }else if(nom_count > 2){
            return -1;
        }else if(valid_nom == 0 || valid_password == 0) {
            nom_count++;
            printf("\n\t \x1b[33m-- Nom ou mot de passe incorrect --\x1b[0m \n");
        }
    }

}

// Relamation ------------------------------------------------------------------------ 

void Afficher_tout_les_Reclamation(){

    if(rec == NULL || R_Taille  == 0 ){
        printf("\n\t \x1b[31m---- Aucun Reclamation a Afficher ----\x1b[0m\n");
        return; 
    }

    for(int i=0;i<R_Taille;i++){

            printf("\n\t \x1b[32m------ Reclamation %d ------\x1b[0m\n\n" , i+1);
            printf("\t -- iD          : %s\n" , rec[i].id);
            printf("\t -- Client      : %s\n" , user[rec[i].id_client].Nom);
            printf("\t -- Motif       : %s\n" , rec[i].Motif);
            printf("\t -- Catgorie    : %s\n" , rec[i].Categorie);
            printf("\t -- Status      : %s\n" , rec[i].Status);
            printf("\t -- Description : %s\n" , rec[i].Description);
            printf("\t -- Note        : %s\n" , rec[i].Note);
            printf("\t -- Date        : %s\n" , rec[i].date);
            if(user[rec[i].id_client].Role == 1) printf("\t -- Role        : Administrateur\n");
            else if(user[rec[i].id_client].Role == 2) printf("\t -- Role        : Agent de Reclamation\n");
            else if(user[rec[i].id_client].Role == 0) printf("\t -- Role        : Client\n");
            

    }

}

void Afficher_Reclamation(){

    if(rec == NULL || R_Taille  == 0 ){
        printf("\n\t \x1b[31m---- Aucun Reclamation a Afficher ----\x1b[0m\n");
        return; 
    }

    int i , exist = 0 , index = 1;
    for(int i=0;i<R_Taille;i++){
        if(rec[i].id_client == index_user){
            printf("\n\t \x1b[32m------ Reclamation %d ------\x1b[0m\n\n" , index);
            printf("\t -- iD          : %s\n" , rec[i].id);
            printf("\t -- Motif       : %s\n" , rec[i].Motif);
            printf("\t -- Catgorie    : %s\n" , rec[i].Categorie);
            printf("\t -- Status      : %s\n" , rec[i].Status);
            printf("\t -- Description : %s\n" , rec[i].Description);
            printf("\t -- Note        : %s\n" , rec[i].Note);
            printf("\t -- Date        : %s\n" , rec[i].date);
            exist = 1;
            index += 1;
        }
    }

    if(exist == 0) printf("\n\t \x1b[31m---- Aucun Reclamation a Afficher ----\x1b[0m\n");
    
}

int Ajouter_un_Reclamation(){

    int i;
    rec = realloc(rec , (R_Taille + 1)*sizeof(Reclamation));

    if(rec == NULL){
        printf("\n\t \x1b[31m--- Erreur D'allocation ----\x1b[0m\n");
        return 0;
    }

    Reclamation reclamation;
    
    printf("\n\t \x1b[32m---- Ajouter un Reclamation ----\x1b[0m \n");
 
    // generer L'id ----------- 
    srand(time(NULL));
    while(1){

        int counter= 0 , i;  
        char Generate_id[100];

        for(i=0;counter<100;i++){
            char random = 48 + (rand() % 74);
            if( (random >= 48 && random <= 57 ) || (random >= 65 && random <= 90 ) || (random >= 97 && random <= 122 )){
                Generate_id[i] = random; 
                counter++;      
                
            }
        }

        Generate_id[i] = '\0';

        int exist = 1;
        for(i=0;i<R_Taille;i++){
            if(strcmp(reclamation.id,Generate_id) == 0) exist = 0;
        }

        if(exist && strlen(Generate_id) > 10 ){
            strncpy(reclamation.id , Generate_id , 10);
            break;
        }
    }
    
    // Validation de motif -------
    int Motif_count = 0;
    while(1){
        printf("\n\t -- Le Motif de la Reclamation : ");
        int valide_input = scanf(" %[^\n]s" , reclamation.Motif);

        if(valide_input && strlen(reclamation.Motif) > 3){
            break;
        }else if(Motif_count > 2){
            return 0;
        }else{
            Motif_count++;
            printf("\n\t \x1b[31m-- Invalid Motif --\x1b[0m \n");
        }
    }

    // Validation de description -------
    int Description_count = 0;
    while(1){
        printf("\n\t -- La Description de la Reclamation : ");
        int valide_input = scanf(" %[^\n]s" , reclamation.Description);

        if(valide_input && strlen(reclamation.Description) > 3){
            break;
        }else if(Description_count > 2){
            return 0;
        }else{
            Description_count++;
            printf("\n\t \x1b[31m-- Invalid Description --\x1b[0m \n");
        }
    }

    // Validation de Categorie -------
    int Categorie_count = 0;
    while(1){
        printf("\n\t -- La Categorie de la Reclamation : ");
        int valide_input = scanf(" %[^\n]s" , reclamation.Categorie);

        if(valide_input && strlen(reclamation.Categorie) > 3){
            break;
        }else if(Categorie_count > 2){
            return 0;
        }else{
            Categorie_count++;
            printf("\n\t \x1b[31m-- Invalid Categorie --\x1b[0m \n");
        }
    }

    // Validation de Status -------
    strcpy(reclamation.Status , "en cours");
    strcpy(reclamation.Note , "");

    // Validation de La Date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // La date de creation
    strftime(reclamation.date, 100, "%d-%m-%Y %H:%M", &tm);
    reclamation.heure_de_debut = time(NULL);

    // id_clien
    reclamation.id_client = index_user; 

    rec[R_Taille] = reclamation;

    return 1;
}

int Modifier_un_Reclamation(){

    // virifier l'dentification existe ou non
    int mod_count = 0 , pos;
   
    while(1){
        char id[20];
        bool exist = false;
        printf("\n\t -- Veuillez Saisir Le identification de Reclamation : ");
        scanf(" %[^\n]s" , id);
        while(getchar() != '\n');

        for(int i=0;i<R_Taille;i++){
            if(strcmp(rec[i].id , id) == 0){
                exist = true;
                pos = i;
                break;
            }  
        }


        if(exist){
            break;
        }else if( mod_count > 2 ) {
            return 0;
        }else if (exist == false) {
            printf("\n\t \x1b[33m--- Reclamation avec cette identification n'est pas exist ----\x1b[0m \n");
            mod_count++;
        }else{
            printf("\n\t \x1b[31m-- Invalid Id --\x1b[0m \n");
            mod_count++;
        }
    }


    if (verifier_duree(rec[pos].heure_de_debut) && user[index_user].Role == 0){

        printf("\n\t \x1b[33m !! Le Delai Pour La Modification Est Expire !! \x1b[0m\n");
        return 0;
    }else{

        printf("\n\t \x1b[32m---- Modifier un Reclamation ----\x1b[0m\n");


        // Validation de motif -------
        int Motif_count = 0;
        while(1){
            printf("\n\t -- Le Motif de la Reclamation : ");
            int valide_input = scanf(" %[^\n]s" , rec[pos].Motif);

            if(valide_input && strlen(rec[pos].Motif) > 3){
                break;
            }else if(Motif_count > 2){
                return 0;
            }else{
                Motif_count++;
                printf("\n\t \x1b[31m-- Invalid Motif --\x1b[0m \n");
            }
        }

        // Validation de description -------
        int Description_count = 0;
        while(1){
            printf("\n\t -- La Description de la Reclamation : ");
            int valide_input = scanf(" %[^\n]s" , rec[pos].Description);

            if(valide_input && strlen(rec[pos].Description) > 3){
                break;
            }else if(Description_count > 2){
                return 0;
            }else{
                Description_count++;
                printf("\n\t \x1b[31m-- Invalid Description --\x1b[0m \n");
            }
        }

        // Validation de Categorie -------
        int Categorie_count = 0;
        while(1){
                printf("\n\t -- La Categorie de la Reclamation : ");
                int valide_input = scanf(" %[^\n]s" , rec[pos].Categorie);

                if(valide_input && strlen(rec[pos].Categorie) > 3){
                    break;
                }else if(Categorie_count > 2){
                    return 0;
                }else{
                    Categorie_count++;
                    printf("\n\t \x1b[31m-- Invalid Categorie --\x1b[0m \n");
                }
            }

        printf("\n\t --- id client : %d \n" , rec[pos].id_client); 

        return 1;
    }

    
    
}

int Supprimer_un_Reclamation(){

    // virifier l'dentification existe ou non
    int sup_coount = 0 , pos;
   
    while(1){
        char id[20];
        bool exist = false;
        printf("\n\t -- Veuillez Saisir Le identification de Reclamation : ");
        scanf(" %[^\n]s" , id);
        while(getchar() != '\n');

        for(int i=0;i<R_Taille;i++){
            if(strcmp(rec[i].id , id) == 0){
                exist = true;
                pos = i;
                break;
            }  
        }

        if(exist){
            break;
        }else if( sup_coount > 2 ) {
            return 0;
        }else if (exist == false) {
            printf("\n\t \x1b[33m--- Reclamation avec cette identification n'est pas exist ----\x1b[0m \n");
            sup_coount++;
        }else{
            printf("\n\t \x1b[31m-- Invalid Id --\x1b[0m \n");
            sup_coount++;
        }
    }

    if(R_Taille == 0){
        return 2;
    }

    for(int i=pos;i<R_Taille - 1;i++){
            rec[i] = rec[i+1];
    }
    R_Taille--;
    return 1;

}

// Utilisateur ------------------------------------------------------------------------

int Modifier_Role_Utilisateur(){

    // virifier l'dentification existe ou non
    int nom_count = 0 , pos; 
   
    while(1){

        char Nom[20];
        bool exist = false;
        printf("\n\t -- Veuillez Saisir Le Nom D'utilisateur : ");
        scanf(" %[^\n]s" , Nom);
        while(getchar() != '\n');

        for(int i=0;i<Taille;i++){
            if(strcmp(user[i].Nom , Nom) == 0){
                exist = true;
                pos = i;
                break;
            }  
        }

        if(exist){
            break;
        }else if( nom_count > 2 ) {
            return 0;
        }else if (exist == false) {
            printf("\n\t \x1b[33m--- Utilisateur avec ce nom n'est pas exist ----\x1b[0m \n");
            nom_count++;
        }else{
            printf("\n\t \x1b[31m-- Invalid Id --\x1b[0m \n");
            nom_count++;
        }
    }


    int role;
    printf("\n\t ---- Role d'Utilisateur ----\n");
    printf("\t -- 1. Administrateur.\n");
    printf("\t -- 2. Agent de Reclamation.\n");
    printf("\t -- 3. Client.\n");
    printf("\t - Tapez Votre Choix : ");
    scanf("%d" , &role);

    if(role >=1 && role <= 3){
        user[pos].Role = role;
        return 1;
    }else{
        return 0;
    }

}

int Modifier_Status_Utilisateur(){

    // virifier l'dentification existe ou non
    int id_count = 0 , pos; 
   
    while(1){

        char id[20];
        bool exist = false;
        printf("\n\t -- Veuillez Saisir L'dentification de Reclamation : ");
        scanf(" %[^\n]s" , id);
        while(getchar() != '\n');

        for(int i=0;i<R_Taille;i++){
            if(strcmp(rec[i].id , id) == 0){
                exist = true;
                pos = i;
                break;
            }  
        }

        if(exist){
            break;
        }else if( id_count > 2 ) {
            return 0;
        }else if (exist == false) {
            printf("\n\t \x1b[33m--- Utilisateur avec ce nom n'est pas exist ----\x1b[0m \n");
            id_count++;
        }else{
            printf("\n\t \x1b[31m-- Invalid Id --\x1b[0m \n");
            id_count++;
        }
    }

    int status;
    printf("\n\t ---- Status de Reclamation ----\n");
    printf("\t -- 1. en cours.\n");
    printf("\t -- 2. Resolu.\n");
    printf("\t -- 3. Rejeter.\n");
    printf("\t - Tapez Votre Choix : ");
    scanf("%d" , &status);

    if(status >= 1 && status <= 3){
        if(status == 1) strcpy(rec[pos].Status , "en cours");
        else if (status == 2) strcpy(rec[pos].Status , "Resolu");
        else if ( status == 3) strcpy(rec[pos].Status , "Rejeter");

        char note[MAX_CHARACTERE];
        int  option = 0;
        printf("\n\t -- voulez-vous Ajouter une Note : \n");
        printf("\t -- 1. Oui.\n");
        printf("\t -- 2. Non.\n");
        printf("\t -- Taper Votre Choix : ");
        scanf("%d" , &option);

        if(option == 1){
            printf("\n\t -- Saisir La Note : ");
            scanf(" %[^\n]s" , note);
            strcpy(rec[pos].Note , note);
        }

        return 1;
    }else{
        return 0;
    }
}

// virification de modification ------------------------------------------------------------------------

int verifier_duree(time_t heure_de_debut) {
    time_t heure_actuelle = time(NULL);
    double difference = difftime(heure_actuelle, heure_de_debut);
    
    // Vérifier si 24 heures (86400 secondes) sont passées
    return difference >= 60;
}