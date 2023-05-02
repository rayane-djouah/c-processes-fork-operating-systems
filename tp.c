#include <stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <unistd.h>
#include <string.h>
int main (int argc,char* argv[])  //prog.c = argv[1]
{
    int p, err;
    p= fork(); //P1
    if (p==0)
    {
        //P1
        //Création du module objet prog.o
        err=execlp("cc","cc","-c","prog1.c","-o","prog1.o",NULL);
        if(err!=0)

        {
            printf("\n Module objet non créé ; err : %d", err>>8);
            return 0;
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
            err=execlp("cc","cc","prog1.o","-o","prog1",NULL);
            if(err!=0)

            {
                printf("\n Module exécutable non créé ; err : %d", err>>8);
            return 0;
            }
            return 0;


        }

    }
    while(wait(NULL)!=-1);
    //éxecution du prog
    err=execl("./prog1","prog1",NULL);
    if(err!=0)

    {
        printf("\n Erreur d'exécution : %d", err>>8);
        exit(3);
    }
    return 0;


}
