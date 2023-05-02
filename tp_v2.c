#include <stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <unistd.h>
#include <string.h>
int main (int argc,char* argv[])  //l'argument argv[1] contient le nom + l'extension .c (exemple: prog.c)
//EXECUTER EN TERMINAL EN PASSANT EN ARGUMENT LE NOM DU PROGRAMME
{
    //enlever .c de l'argument et le sauvegarder dans prog
    const char * point = ".";
    char* prog;
    prog= strtok(argv[1], point);

    //sauvegarder l'argument dans progc
    char progc[50];
    strcpy(progc,argv[1]);

    //ajouter .o et le sauvegarder dans progo
    char progo[50];
    strcpy(progo,prog);
    strcat(progo,".o");

    //exec contient ./ + le nom du programme
    char exec[50]= "./";
    strcat(exec,prog);

    int p, err;
    p= fork(); //P1
    if (p==0)
    {
        //P1
        //Création du module objet prog.o
        printf("\n Création du module objet %s \n", progo);
        err=execlp("cc","cc","-c",progc,"-o",progo,NULL);
        if(err!=0)

        {
            printf("\n Module objet non créé ; err : %d", err>>8);
            exit(1);
        }
        return 0;

    }
    else
    {
        while(wait(NULL)!=-1);
        //P2
        p= fork(); //P2
        if(p==0)
        {
            //Création du programme prog
            printf("\n Création du programme %s \n",prog);
            err=execlp("cc","cc",progo,"-o",prog,NULL);
            if(err!=0)

            {
                printf("\n Module exécutable non créé ; err : %d", err>>8);
                exit(2);
            }
            return 0;


        }

    }
    while(wait(NULL)!=-1);
    //éxecution du prog
    printf("\n Execution du programme %s \n\n",prog);
    err=execl(exec,prog,NULL);
    if(err!=0)
    {
        printf("\n Erreur d'exécution : %d", err>>8);
        exit(3);
    }
    return 0;


}
