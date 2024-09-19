#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CHARACTERE 50
#define MAX_DESCRIPTION 500
#define MAX_STATUS 10

typedef struct {

    char id[MAX_CHARACTERE];
    char Nom[MAX_CHARACTERE];
    char Email[MAX_CHARACTERE]; 
    char Password[MAX_CHARACTERE];
    int  Role;

}Utilisateurs;

typedef struct {
    int jour;
    int mois;
    int annee;

}Date;

typedef struct 
{
    char id[MAX_CHARACTERE];
    char Motif[MAX_CHARACTERE];
    char Description[MAX_DESCRIPTION];
    char Categorie[MAX_CHARACTERE];
    char Status[MAX_CHARACTERE];
    int index;
    Date date;

}Reclamation;

Utilisateurs *user = NULL;
Reclamation *rec = NULL;
int Taille = 0;
int R_Taille = 0;

int Incription();
int Connexion();

int main(){

    int auth , choix = 0 , index_user;

    user = malloc(Taille*sizeof(Utilisateurs));
    rec = malloc(Taille*sizeof(Reclamation));

    while(auth != 0){

        printf("\n\t ---  Bienvenu a L'application ---\n");
        printf("\n\t --- 1. Inscription ---\n");
        printf("\n\t --- 2. Connexion ---\n");
        printf("\n\t --- 0. Quitter ---\n");
        printf("\n\t -- Tapez Votre Choix :  ");
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
                    auth = 0;
                } else printf("\n\t --- Inscription Invalid --- \n");
                break;
            case 2 :
                int index = Connexion();
                if(index != 0){
                    printf("\n\t \x1b[32m--- Connexion Reussite ---\x1b[0m\n");
                    index_user = index;
                    auth = 0;
                } 
                else printf("\n\t --- Erreur Lors de Connexion --- \n");
                break;
        
        default:

            printf("\n\t --- Invalide Choix --- \n");
            break;
        }
    
    }

    while(1){

        int valid_choix = Choix(&choix);

        if (valid_choix == 0 || choix < 1 || choix > 5){
            printf("\n\t \x1b[31m---- Choix Invalid ----\x1b[0m \n");
        }else {

             switch (choix){

                case 1 :
                    /* code */
                    break;
                
                default:
                    break;
            }
        }
    
    }
}


int Choix(int *choix){
    int ch; 
    printf("\n"
               "\t==============================================\n\t"
               "|          \033[36mMenu d\'application\033[0m                |\n"
               "\t==============================================\n\t"
               "|\t[1] Faire une Reclamation            |\n\t"
               "|\t[2] Afficher tout les Reclamation    |\n\t"
               "|\t[3] Modifier un Reclamation          |\n\t"
               "|\t[4] Supprimer un Reclamation         |\n\t"
               "|\t[\033[33m5\033[0m] \033[33mQuitter\033[0m                          |\n"
               "\t==============================================\n\t"
               "\n\tTapez votre choix [1-5] : ");
               ch = scanf("%d", choix);
               while(getchar() != '\n');
               if(ch) return ch;
               else return 0;
}

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
    int nom_count = 0  , index;
    while(1){

        int valid_nom = 0 , valid_password = 0;
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
                }
            }
        }

        if(valid_nom && valid_password){
            return index;
        }else if(nom_count > 5){
            return 0;
        }else if(valid_nom == 0) {
            nom_count++;
            printf("\n\t \x1b[33m-- Nom n'est pas exist --\x1b[0m \n");
        }else if(valid_password == 0) {
            nom_count++;
            printf("\n\t \x1b[33m-- Invalid mot de pass --\x1b[0m \n");
        }
    }

}