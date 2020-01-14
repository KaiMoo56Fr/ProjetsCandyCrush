#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define Colonnes 26
#define Lignes 27

 int Texte_Menu();
struct saisie
         {
             signed char username[256];
             int lignes;
             int colonnes;
             int lettres_max;
             int permax;
         };
void Jeu();
void Remplissage_Grille();
void Affichage_Grille();
void Supression_alignements();
int** Allocation_Dynamique_Grille();
void Liberation_memoire(int** tab, int lignes);
void Permutation();
void Remplissage_apr_perm();


void main()

{
    int i=0;
    do
    {
        i=Texte_Menu();
        switch(i)
        {
        case(0):
            break;
        case(1):
            Jeu();
            break;
        default:
            printf("\nVeuillez choisir un choix valide!\n");
        }
    }
    while(i!=0);
    system("pause");
}

int Texte_Menu()
{

    int i;
    system("cls");
    printf("\nBienvenue\n");
    printf("\**********Pseudo Candy Crush**********\n");
    printf("\nAfin de commencer a jouer tapez :1\n");
    printf("\nPour quitter tapez : 0\n");
    printf("\nChoix : => ");
    fflush(stdin);
    scanf("%d",&i);
    return i;
}


void Jeu()
{
    int** grille;
    int i, j, n=0 ;
    int perm=0;
    int score=0; int end=0;
    struct saisie p;


    printf("\nTapez Votre Nom : ");
    scanf("%s",&p.username);


    printf("\n\nNombre de lignes :");

    scanf("%d", &p.lignes);

    printf("\n\nNombre de colonnes :");

    scanf("%d",&p.colonnes);

    printf("\n\nNombre de lettres max :");

    scanf("%d",&p.lettres_max);

    printf("\n\nNombre de permutation max :");

    scanf("%d",&p.permax);



    grille=Allocation_Dynamique_Grille(p.lignes,p.colonnes);

    while(perm<p.permax && end != ' ')
    {

        system("cls");
        printf("\nPseudo Candy Crush");
        Remplissage_Grille(grille,p.lignes,p.colonnes,p.lettres_max);
        Supression_alignements(grille,p.lignes,p.colonnes);
         Affichage_Grille(grille,p.lignes,p.colonnes,p.username,perm,p.permax,score);

        Permutation(grille,p.lignes,p.colonnes);
        Remplissage_apr_perm(grille,p.lignes,p.colonnes,p.lettres_max);
      score+=3;
         Affichage_Grille(grille,p.lignes,p.colonnes,p.username,perm,p.permax,score);
        printf("\n\n\nvoulez vous sortir du jeu? si oui appuyez sur ESPACE\nsinon, appuyez sur nimporte quelle touche");
        scanf("%c",&end);
        perm++;

    }
    Liberation_memoire(grille,p.lignes);
    printf("Fin du jeu");

    system("pause");
}

void Remplissage_Grille(int tab[][Colonnes],int lignes, int colonnes,int lettres_max)
{
    int i, j;
    for (i=0; i<lignes; i++)
    {
        for (j=0; j<colonnes; j++)
        {
            tab[i][j]='a'+rand()%((lettres_max));
        }
    }
}

void  Affichage_Grille(int tab[][Colonnes], int lignes, int colonnes,char nom[], int perm, int permax,int score)
{
    int i, j,n;
    printf("\n\n\t");
    for (n=0; n<colonnes; n++)  printf("%3d",n+1);
    printf("\n");

    for (i=0; i<lignes; i++)
    {
        printf("\n%c\t",'A'+i);
        for (j=0; j<colonnes; j++)
        {
            printf("%3c", tab[i][j]);
        }
    }
    printf("\n\njoueur : %s\n",nom);
    printf("\nle score=%d",score);

    printf("\npermutation=%d\tpermutation max=%d",perm,permax);

}



void Supression_alignements(int tab[][Colonnes], int lignes, int colonnes,int lettres_max)
{
    int i, j;
    for (i=0; i<lignes; i++)
    {
        for (j=0; j<colonnes; j++)
        {
            if(tab[i][j]==tab[i+1][j] && tab[i][j]==tab[i+2][j])
            {
                tab[i][j]='a'+rand()%lettres_max;
                tab[i+1][j]='a'+rand()%lettres_max;
                tab[i+2][j]='a'+rand()%lettres_max;
            }
            if(tab[i][j]==tab[i][j+1] && tab[i][j]==tab[i][j+2])
            {

                tab[i][j]='a'+rand()%lettres_max;
                tab[i][j+1]='a'+rand()%lettres_max;
                tab[i][j+2]='a'+rand()%lettres_max;
            }
        }
    }
}

void Permutation(int tab[][Colonnes],int lignes, int colonnes)
{
    int a,b,c,d;
    char temp,x,y;

    printf("\nL1\n");
    scanf("%s",&x);
    a=x-'A';
    printf("\nC1\n");
    scanf("%d",&b);
    b--;
    printf("\nL2\n");
    scanf("%s",&y);
    c=y-'A';
    printf("\nC2\n");
    scanf("%d",&d);
    d--;
    if(abs(a-c)>1 || abs(b-d)>1)
    {
        printf(" \nproblem\n");

    }

    temp=tab[a][b];
    tab[a][b]=tab[c][d];
    tab[c][d]=temp;

    int i, j,n;
    printf("\n\n\t");
    for (n=0; n<colonnes; n++)  printf("%3d",n+1);
    printf("\n");

    for (i=0; i<lignes; i++)
    {
        printf("\n%c\t",'A'+i);
        for (j=0; j<colonnes; j++)
        {
            printf("%3c", tab[i][j]);
        }
    }
}
void Remplissage_apr_perm(int tab[][Colonnes],int lignes,int colonnes,int lettres_max)
{int score=0;
    int i,j;
    for (i=0; i<lignes; i++)
    {
        for (j=0; j<colonnes; j++)
        {
            if(tab[i][j]==tab[i+1][j] && tab[i+1][j]==tab[i+2][j])
            {
                score+=3;
                tab[i][j]='a'+rand()%lettres_max;
                tab[i+1][j]='a'+rand()%lettres_max;
                tab[i+2][j]='a'+rand()%lettres_max;

            }
            if(tab[i][j]==tab[i][j+1] && tab[i][j]==tab[i][j+2] )
            {
                 score+=3;
                tab[i][j]=rand()%lettres_max;
                tab[i][j+1]=rand()%lettres_max;
                tab[i][j+2]=rand()%lettres_max;

            }


        }
    }

    printf("score = %d",score);
    system("pause");
}

int** Allocation_Dynamique_Grille( int lignes, int colonnes)
{
    return malloc(lignes*colonnes*sizeof(char));
}


void Liberation_memoire(int** tab, int lignes)
{
    int i;
    for(i=0; i<lignes; i++)    free(tab[i]);
}
