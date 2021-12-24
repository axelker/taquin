/*gcc -o EXEC projetc.c -Wall -lncurses*/

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <ncurses.h> 
#include <unistd.h>
#include <string.h>

#define Hauteur 21
#define Longueur 51
#define HauteurDecoup 7
#define LongueurDecoup 17
#define Panneau 3


bool difficulte;
int compteurSouris; // Nombre de clique 
int tmpC,tmpL; // Variable temporaire du clique 
int L, C; /*L pour désigner la ligne et C la colonne du click de la souris*/
int L2,C2; // joueur le clique suivant 
char tableau[Hauteur][Longueur];

char tabBis[Hauteur*Longueur];

char tableau1[HauteurDecoup][LongueurDecoup];
char tableau2[HauteurDecoup][LongueurDecoup];
char tableau3[HauteurDecoup][LongueurDecoup];
char tableau4[HauteurDecoup][LongueurDecoup];
char tableau5[HauteurDecoup][LongueurDecoup];
char tableau6[HauteurDecoup][LongueurDecoup];
char tableau7[HauteurDecoup][LongueurDecoup];
char tableau8[HauteurDecoup][LongueurDecoup];
char tableau9[HauteurDecoup][LongueurDecoup];

char tabInitial[Panneau][Panneau];
char tabAleatoire[Panneau][Panneau];

char tabChiffreInit[Panneau][Panneau];
char tabChiffreAleatoire[Panneau][Panneau];

 


/******** Jeu Chiffre *********/
void TabChiffreInit()
{
  int indice =0;
  for(int i=0;i<Panneau;i++)
  { 
    for(int j=0;j<Panneau;j++)
    {
      if(j==2 && i==2)
      {
        tabChiffreInit[i][j]=' ';
      }
      else 
      {
        tabChiffreInit[i][j]=indice+'0';
        indice++;
      }
    }
  }
}

//INITIALISATION TABLEAU NUMÉRO PANNEAUX et chiffre 
void initab()
{
  TabChiffreInit();
  for(int i=0;i<Panneau;i++)
  { 
    for(int j=0;j<Panneau;j++)
    {
      tabInitial[i][j]=tabChiffreInit[i][j];
     
    }
  }
}

//Test si le nombre en parametre n'est pas contenu deja dans le tableau 
bool VerifIdentique(int elemTest)
{
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
      char c = tabChiffreAleatoire[i][j];
      int n = c-48;
      if(n==elemTest)
      {
        return TRUE;
      }
    }
  }
  return FALSE;
}
// Effectue un tirage aleatoire du tableau contenant les chiffres 
void aleatoireTirage()
{
  srand (time (NULL));
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
      
      int val= rand()%8;
      while(VerifIdentique(val)==TRUE && (i+j!=4))
      {
         val= rand()%8;
      }
      if(i==2 && j==2)
      {
        tabChiffreAleatoire[i][j] =' ';
      }
      else {
      tabChiffreAleatoire[i][j] = val +'0';
      }
    }
  }
  
}

// Affiche le tableau de chiffre 
void affichageTabChiffre()
{
 printw("--------------------------------------------------------\n\n");
  for(int i=0;i<3;i++)
  {
    printw("             ");
    for(int j=0;j<3;j++)
    {
      printw("|   %c   |",tabChiffreAleatoire[i][j]);
    }
    printw("\n             ---------------------------                \n\n");
  }
  printw("--------------------------------------------------------\n");
}
//FIN DE PARTIE 
bool finDeJeu(char tab1[Panneau][Panneau],char tab2[Panneau][Panneau])
{
  int cmpt=0;
  for(int i=0;i<Panneau;i++)
  { 
    for(int j=0;j<Panneau;j++)
    {
      //COnvertion en int par la soustraction du caractère ASCII
      char a = tab1[i][j];
      int n = a -48;
      char a2 =tab2[i][j];
      int n2 = a2-48;
      if(n==n2)
      {
          cmpt ++;
      }
    }
  }
  if(cmpt==9)
  {
    return true;
  }
  return false;
}

//Stockque le clique effectuer 
void stockClique(int a,int b)
{
  C2=a;
  L2=b;
}
// Renvoi la colonne du clique coresspondante dans le tableau
int colonneClique(int x)
{
  if(x>=13 && x<=21)
  {
    return 0;
  }
  if(x>=22 && x<=30)
  {
    return 1;
  }
  
    return 2;
  
}
// Renvoi la ligne du clique coresspondante dans le tableau 
int ligneClique(int x)
{
  if(x>=2 && x<=4)
  {
    return 0;
  }
  if(x>=5 && x<=7)
  {
    return 1;
  }
  return 2;
}
//Mode facile 
void play(int l,int c,int l1,int c1)
{
  int lignecliquel=ligneClique(l);
  int lignecliquel1=ligneClique(l1);
  int colonneCliquec=colonneClique(c);
  int colonneCliquec1=colonneClique(c1);
  if(tabChiffreAleatoire[lignecliquel][colonneCliquec]==tabChiffreInit[2][2] ||tabChiffreAleatoire[lignecliquel1][colonneCliquec1]==tabChiffreInit[2][2]) 
  {
  char tmp=tabChiffreAleatoire[lignecliquel][colonneCliquec];
  tabChiffreAleatoire[lignecliquel][colonneCliquec]=tabChiffreAleatoire[lignecliquel1][colonneCliquec1];
  tabChiffreAleatoire[lignecliquel1][colonneCliquec1]=tmp;
  }
  
}

//Fin de partie 
bool isOver()
{
  if(finDeJeu(tabChiffreInit,tabChiffreAleatoire))
  {
    return true;
  }
  return false;
}

//Jeu avec mode difficle 
void ModeDifficle(int l,int c,int l1,int c1)
{
  int lignecliquel=ligneClique(l);
  int lignecliquel1=ligneClique(l1);
  int colonneCliquec=colonneClique(c);
  int colonneCliquec1=colonneClique(c1);
  if(tabChiffreAleatoire[lignecliquel][colonneCliquec]==tabChiffreInit[2][2] ||tabChiffreAleatoire[lignecliquel1][colonneCliquec1]==tabChiffreInit[2][2]) 
  {
    
    if(lignecliquel==lignecliquel1 || colonneCliquec==colonneCliquec1)
    {
      char tmp=tabChiffreAleatoire[ligneClique(l)][colonneClique(c)];
      tabChiffreAleatoire[ligneClique(l)][colonneClique(c)]=tabChiffreAleatoire[ligneClique(l1)][colonneClique(c1)];
      tabChiffreAleatoire[ligneClique(l1)][colonneClique(c1)]=tmp;
    }
  }
  
}
//Affichage tableau lorsque partie terminé 
void AffichageFinish()
{
 printf("--------------------------------------------------------\n\n");
  for(int i=0;i<3;i++)
  {
    printf("             ");
    for(int j=0;j<3;j++)
    {
      printf("|   %c   |",tabChiffreAleatoire[i][j]);
    }
    printf("\n             ---------------------------                \n\n");
  }
  printf("--------------------------------------------------------\n");
  printf("Le jeu est résolu  ! \n\n");
}

/*****************************************************************/
/** JEU AVEC IMAGE ASCII */
//Initialisation tabDécoupé
void initTabDecoupe()
{
  
  for(int i=0;i<HauteurDecoup;i++)
  {
    for(int j=0;j<LongueurDecoup;j++)
    {
      tableau1[i][j]=tableau[i][j];
      tableau2[i][j]=tableau[i][j+LongueurDecoup];
      tableau3[i][j]=tableau[i][j+LongueurDecoup*2];
      tableau4[i][j]=tableau[i+HauteurDecoup][j];
      tableau5[i][j]=tableau[i+HauteurDecoup][j+LongueurDecoup];
      tableau6[i][j]=tableau[i+HauteurDecoup][j+LongueurDecoup*2];
      tableau7[i][j]=tableau[i+HauteurDecoup*2][j];
      tableau8[i][j]=tableau[i+HauteurDecoup*2][j+LongueurDecoup];
      tableau9[i][j]=tableau[i+HauteurDecoup*2][j+LongueurDecoup*2];


    }
  }
}
// Affiche tab découpe 
void afficheDecoupe(char tab[HauteurDecoup][LongueurDecoup])
{
  for(int i=0;i<HauteurDecoup;i++)
  {
    for(int j=0;j<LongueurDecoup;j++)
    {
      printw("%c", tab[i][j]);  
      
    }
    printw("\n");
    
  }    
  
}

//Affiche la découpe 
void afficheTotalDecoupe()
{
  afficheDecoupe(tableau1);
  afficheDecoupe(tableau2);
  afficheDecoupe(tableau3);
  afficheDecoupe(tableau4);
  afficheDecoupe(tableau5);
  afficheDecoupe(tableau6);
  afficheDecoupe(tableau7);
  afficheDecoupe(tableau8);
  afficheDecoupe(tableau9);
  

  

}


//Stock l'image ASCII DANS TABLEAU 
void stockageImage()
{
    FILE* fichier = NULL;
    long val=0;
    fichier = fopen("image.txt", "r");
 
    if (fichier != NULL)
    {
      char caractereActuel = fgetc(fichier); // On lit le caractère
      while (caractereActuel != EOF) { // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
        // Boucle de lecture des caractères un à un
          //Remplissage tableau
              val = ftell(fichier);
              //printw("%ld",val);
              for(int i=0;i<Hauteur*Longueur;i++)
              {

              
                if(val<Hauteur*Longueur)
                {
                  
                  tabBis[i]=caractereActuel;
                  
                  //printw("%c", tableau[i][j]); // On l'affiche
                }
                caractereActuel = fgetc(fichier);
              }

            }
          
        
 
        fclose(fichier);
    }
}

//Affiche le tableau contenant l'image 
 void affichageImage()
 {
   
  for(int i=0;i<Hauteur*Longueur;i++)
  { 
    printw("%c", tabBis[i]);
  }
   
   
 }
 // Remplis le tableau contenant l'image en Ascii
 void Remplissage()
 {
   int parcours = 0;
   for(int i=0;i<Hauteur;i++)
   {
     for(int j=0;j<Longueur;j++)
     {
       tableau[i][j]=tabBis[parcours];
       parcours+=1;
     }
     
   }
 }

//Affiche l'image en Ascii
 void affichage()
 {
   for(int i=0;i<Hauteur;i++)
   {
     for(int j=0;j<Longueur;j++)
     {
        printw("%c", tableau[i][j]);
     }
     
   }
 }



//************************************************************//
/**Initialisation de ncurses**/
void ncurses_initialiser() {
  initscr();	        /* Demarre le mode ncurses */
  cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
  noecho();             /* Desactive l'affichage des caracteres saisis */
  keypad(stdscr, TRUE);	/* Active les touches specifiques */
  refresh();            /* Met a jour l'affichage */
  curs_set(FALSE);      /* Masque le curseur */
}


/**Initialisation des couleurs**/
void ncurses_couleurs() {
  /* Vérification du support de la couleur */
  if(has_colors() == FALSE) {
    endwin();
    fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
    exit(EXIT_FAILURE);
  }

  /* Activation des couleurs */
  start_color();

}

/**Initialisation de la souris**/
void ncurses_souris() {
  if(!mousemask(ALL_MOUSE_EVENTS, NULL)) {
    endwin();
    fprintf(stderr, "Erreur lors de l'initialisation de la souris.\n");
    exit(EXIT_FAILURE);
  }

  if(has_mouse() != TRUE) {
    endwin();
    fprintf(stderr, "Aucune souris n'est détectée.\n");
    exit(EXIT_FAILURE);
  }
}


/**Pour récupérer les coordonnées (x,y) du clik de la souris**/
int click_souris()
{
  MEVENT event ;
  int ch;

  while((ch = getch()) != KEY_F(1)) 
  {
    switch(ch) 
    {
      case KEY_F(2): /*Pour quitter le jeu*/
	return 1;
      case KEY_MOUSE:
        if(getmouse(&event) == OK) 
	{
    
      tmpC = event.x;
      tmpL = event.y; 

	  if(event.bstate & BUTTON1_CLICKED)
	  {
	    if (tmpL<=9 && tmpL>=2  && tmpC>=13 && tmpC<=40) /*Vous pouvez changer ici et mettre les dimensions de votre plateau de jeu*/
	    {
        C=tmpC;
        L=tmpL;
	    return 0;
	    }
	  }
	}
    }
  }
  return 0;
}

int SaisieDifficulte(int c,int l)
{
  if(c>=21 && c<=26 && l==2)
  {
    return 0;
  }
  if(c >=30 && c<=40 && l==2)
  {
    return 1;
  }
  return -1;

}

int main() {
  
  //Fonction image Ascii
  /*stockageImage();
  Remplissage();
  initTabDecoupe();
  afficheTotalDecoupe();
  affichageImage();*/

  //Initialise tableau de départ et tire aléatoirement le second tableau 
  initab();
  aleatoireTirage();
  difficulte=false;
  ncurses_initialiser(); //Initialisation de ncurses
  //ncurses_couleurs();
  ncurses_souris();
  //DIfficulté choix 
  printw("\n\nCliquer difficulté  Facile    Difficile  ");  
  click_souris();
  clear();
  int num=SaisieDifficulte(C,L);
  if(num==1)
  {
    difficulte=TRUE;
  }
  
  //Indication et affichage du tableau de chiffre 
  printw("Cliquer sur un nombre et la case vide pour interchanger leurs positions \n");  
  affichageTabChiffre();
  
  scrollok(stdscr, TRUE);
  while (isOver()==FALSE)
  {
    click_souris();
    clear();
    printw("Vous avez cliqué sur la position (%d,%d)\n", L, C);
    if(compteurSouris==0)
    {
      stockClique(C,L);
    }
    compteurSouris++;
    if(compteurSouris==2)
    {
      if(difficulte==true)
      {
        ModeDifficle(L2,C2,L,C);
      }
      else {
      play(L2,C2,L,C);
      }
      compteurSouris=0;
    }

    affichageTabChiffre();
    //afficheDecoupe();
    //afficheTotalDecoupe();
   //affichage();

  }
  endwin(); // Suspendre la sesion ncurses et restorer le terminal
  AffichageFinish();
  
  return 0;
}
