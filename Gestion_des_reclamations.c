#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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
    char Status[MAX_STATUS];
    char date[MAX_DATE];
    int priorite;         
    int id_client; 
   
}Reclamation;

Utilisateurs *user = NULL;
Reclamation *rec = NULL;

int Taille = 0;
int R_Taille = 0;
int index_user = -1;

int Incription();
int Connexion();
int Choix(int *choix);

// Les Fonction de Reclamation 
void Afficher_tout_les_Reclamation();
int Ajouter_un_Reclamation();
int Modifier_un_Reclamation();
int Supprimer_un_Reclamation();

int main(){

    printf("\n\t ---  Bienvenu a L'application ---\n");
    int auth = -1 , choix = 0  , r_choix = 0;

    user = malloc(Taille*sizeof(Utilisateurs));
    rec = malloc(Taille*sizeof(Reclamation));

    while(1){

        int connect = 0;

        do{
        // Authentification ---------------------- 
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
                    connect = 1;
                    auth = 0;
                } else printf("\n\t --- Inscription Invalid --- \n");
                break;
            case 2 :
                int index = Connexion();
                printf("\n\t --- Index  : %d \n" , index);
                if(index >= 0){
                    printf("\n\t \x1b[32m--- Connexion Reussite ---\x1b[0m\n");
                    index_user = index;
                    connect = 1;
                    auth = 0;
                } 
                else {
                    printf("\n\t \x1b[31m--- Erreur Lors de Connexion ---\x1b[0m \n");
                } 
                break;
        
        default:
            break;

        }
    
    }while(auth != 0);


    if(connect){
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

int Choix(int *choix){
    int ch;
    printf("\n"
               "\t==============================================\n\t"
               "|          \033[36mMenu d\'application\033[0m                |\n"
               "\t==============================================\n\t"
               "|\t[1] Ajouter une Reclamation          |\n\t"
               "|\t[2] Afficher tout les Reclamation    |\n\t"
               "|\t[3] Modifier un Reclamation          |\n\t"
               "|\t[4] Supprimer un Reclamation         |\n\t"
               "|\t[\033[33m5\033[0m] \033[33mDeconnecter\033[0m                      |\n"
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

// Relamation
void Afficher_tout_les_Reclamation(){

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

    // Validation de La Date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    strftime(reclamation.date, 100, "%d-%m-%Y %H:%M:%S", &tm);

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

    Reclamation reclamation;

    printf("\n\t \x1b[32m---- Modifier un Reclamation ----\x1b[0m\n");


    // autre champ 
    strcpy(reclamation.id, rec[pos].id);   
    strcpy(reclamation.Status, rec[pos].Status);   
    strcpy(reclamation.date, rec[pos].date);   
    reclamation.id_client = index_user;

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


    rec[pos] = reclamation;

    printf("\n --- id client : %d \n" , rec[pos].id_client); 

    return 1;

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
