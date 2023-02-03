#include "headers.h"



/*------------------------ -t1 -- abr    fonctionne parcours infixe dans la redaction du fichier dat a reparer-----------------------------*/


// permet de crée un chainon contenant les indormations d'une station
pArbre creationt(int ID,float temp,float max,float min){
    pArbre nouveau=malloc(sizeof(Arbre));
    if(nouveau==NULL){
        printf("erreur allocation ");
        exit(4);
    }
    else{
        nouveau->ID=ID;
        nouveau->temp=temp;
        nouveau->max=max;
        nouveau->min=min;
        nouveau->fg=NULL;
        nouveau->fd=NULL;
    }
    return nouveau;
}

//permet d'insérer un chainon dans un arbre de station
pArbre insertiont(pArbre a, int ID, float temp, float max, float min){
        if(a==NULL){
            return creationt(ID,temp,max,min);
        }
        else if(ID<a->ID){
            a->fg=insertiont(a->fg,ID,temp,max,min);
        }
        else if (ID>a->ID){
            a->fd=insertiont(a->fd,ID,temp,max,min);
        }
        else if(ID==a->ID){
            a->temp=((a->temp+temp)/2);// permet alors de retourner la moyenne de la station qui apparait plusieur fois dans le csv
            if(max>a->max){ //met a jour le max si et seulement si le max récuperer dans le fichier texte est plus grand que celui déja stocké
                a->max=max;
            }      
            if(min<a->min){ //met a jour le min si et seulement si le min recuperer dans le fichier texte est plus petit que celui deja stocké
            a->min=min;
            }
        }
        return a;
}
// créé un arbre de station a partir d'un fichier texte 
pArbre  creationarbret(pArbre a){
    FILE *fp=fopen("tempo.txt","r");
    if(fp==NULL){
        printf("erreur  fopen ");
        exit (2);
    }
    char buffer[2048];
    int ID;
    float temp,max,min;
    rewind(fp);
        while(fgets(buffer,2048,fp)!=NULL){   //récupère les lignes 
            int ret=sscanf(buffer,"%d %f %f %f",&ID,&temp,&min,&max);      //recupere les 4 champs de la ligne récupérer
            if(ret!=4){
                printf("erreur lors de la lescture des champs");  // si sscanf a scannée plus ou moins de 4 champs, sorti du programme
                exit(4);
            }
                a=insertiont(a,ID,temp,max,min);             //insertion des données dans l'arbre en fonction de l'identifiant de la station
        }
        
    fclose(fp);
    return a;
        
}

// réalise un parcours infixe de sorte a ce que les information soit inscrite dasn un fichier dat dans l'ordre croissant des numéro de station
void parcoursinfixe(pArbre a, FILE *fp){
    if(a!=NULL){
        parcoursinfixe(a->fg, fp);
        fprintf(fp,"%d %f %f %f\n",a->ID, a->temp,a->min,a->max);               //ecriture dans  fichier.dat dans l'ordre croissant des fonctions 
        parcoursinfixe(a->fd, fp);
    }
}


//permet de faire le tri du fichier texte dans un ABR et de réecrire les données du fichier texte désordonée dans l'ordre croissant des stations dans fichier.dat
void temperature(){
    FILE *fp=fopen("t1.dat","w");
    if(fp==NULL){
        printf("erreur fopen");
        exit(2);
    }

    pArbre nouveau=NULL;
    nouveau=creationarbret(nouveau);
    parcoursinfixe(nouveau,fp);    
    fclose(fp);
}


/*---------------------          -p1 --abr  --------------------------------------*/

//fonctionne de la meme façon que -t1 --abr



// permet de crée un chainon contenant les indormations d'une station
ppression creationp(int ID,float pres,float max,float min){
    ppression nouveau=malloc(sizeof(Pression));
    if(nouveau==NULL){
        printf("erreur allocation ");
        exit(4);
    }
    else{
        nouveau->ID=ID;
        nouveau->pres=pres;
        nouveau->max=max;
        nouveau->min=min;
        nouveau->fg=NULL;
        nouveau->fd=NULL;
    }
    return nouveau;
}

//permet d'insérer un chainon dans un arbre de station
ppression insertionp(ppression a, int ID, float pres, float max, float min){
        if(a==NULL){
            return creationp(ID,pres,max,min);
        }
        else if(ID<a->ID){
            a->fg=insertionp(a->fg,ID,pres,max,min);
        }
        else if (ID>a->ID){
            a->fd=insertionp(a->fd,ID,pres,max,min);
        }
        else if(ID==a->ID){
            a->pres=((a->pres+pres)/2);// permet alors de retourner la moyenne de la station qui apparait plusieur fois dans le csv
            if(max>a->max){    //met a jour le max si et seulement si le max récuperer est plus grand que le max déjà stocké
                a->max=max;
            }
            if(min<a->min){    //met a jour le min si et seulement si le min récuperer est plus petit que le min déjà stocké
                a->min=min;     
            }
        }
        return a;
}
// créé un arbre de station a partir d'un fichier texte 
ppression  creationarbrep(ppression a){
    FILE *fp=fopen("tempo1.txt","r");
    if(fp==NULL){
        printf("erreur  fopen ");
        exit (2);
    }
    char buffer[2048];
    int ID;
    float pres,max,min;
    rewind(fp);
        while(fgets(buffer,2048,fp)!=NULL){   //récupère les lignes 
            int ret=sscanf(buffer,"%d %f %f %f",&ID,&pres,&min,&max);      //recupere les 4 champs du fichier temporaire
            if(ret!=4){
                printf("erreur lors de la lescture des champs");
                exit(4);
            }
                a=insertionp(a,ID,pres,max,min);             //insertion dans l'arbre en fonction de l'identifiant de la station
        }
        
    fclose(fp);
    return a;
        
}

// réalise un parcours infixe de sorte a ce que les information soit inscrite dans un fichier dat dans l'ordre croissant des numéro de station
void parcoursinfixep(ppression a,FILE *fp){
    if(a!=NULL){
            parcoursinfixep(a->fg,fp);
            fprintf(fp,"%d %f %f %f\n",a->ID, a->pres,a->min,a->max);
            parcoursinfixep(a->fd,fp);
    }
}


//permet de lire un fichier texte contenant des information sur des stations puis le tri à l'aide d'un arbre binaire de recherche et réecrit les données dans l'ordre croissant de numéro de station dans un fichier dat
void pression(){
    FILE *fp=fopen("p1.dat","w");
    if(fp==NULL){
        printf("erreur fopen");
        exit(2);
    }

    ppression nouveau=NULL;
    nouveau=creationarbrep(nouveau);
    parcoursinfixep(nouveau,fp);    
    fclose(fp);
}

/*----------------   -t1 --avl ---------------------------*/
// fonction qui renvoie le plus grand int entre deux int entrées en paramètres
int max(int a,int e){
	if(a>=e){
		return a;
	}
	else{
		return e;
	}
}
//fonction qui renvoie le plus petit  int entre deux int entrées en paramètres
int min(int a,int e){
	if(a<=e){
		return a;
	}
	else{
		return e;
	}
}
//structure pour AVL 


//crée un noeud avec les données de Station pour pouvoir l'insérer dans un AVL 
pArbret1 creation(int ID,float temp, float max, float min ){
    pArbret1 nouveau=malloc(sizeof(Arbret1));
    if(nouveau==NULL){
        printf("erreur allocation");
        exit(4);
    }
    nouveau->ID=ID;
    nouveau->temp=temp;
    nouveau->max=max;
    nouveau->min=min;
    nouveau->fg=NULL;
    nouveau->fd=NULL;
    nouveau->equ=0;
    return nouveau;
}
//permet de faire une roation gauche de l'AVL pour le réequillibré
pArbret1 rotationgauche(pArbret1 a){
    pArbret1 t;
    int a_eq;
    int t_eq;
    t=a->fd;
    a->fd=t->fg;
    t->fg=a;
    a_eq=a->equ;
    t_eq=t->equ;
    a->equ=a->equ-max(t_eq,0)-1;
    t->equ=min(a_eq-2,min(a_eq+t_eq-2,t_eq-1));
    a=t;
    return a;
}
//permet de faire une rotation droite de l'AVL pour le réequilibré
pArbret1 rotationdroite(pArbret1 a){
    pArbret1 t;
    int a_eq;
    int t_eq;
    t=a->fg;
    a->fg=t->fd;
    t->fd=a;
    a_eq=a->equ;
    t_eq=t->equ;
    a->equ=a_eq-min(t_eq,0)+1;
    t->equ=max(a_eq+2,max(a_eq+2+t_eq,t_eq+1));
    a=t;
    return a;
}
//permet de faire une doublerotation pour le réequilibré
pArbret1 doublerotationgauche(pArbret1 a){
    a->fd=rotationdroite(a->fd);
    a=rotationgauche(a);
    return a;

}
//permet de faire une doublerotation pour le réequilibré
pArbret1 doublerotationdroite(pArbret1 a){
    a->fg=rotationgauche(a->fg);
    a=rotationdroite(a);
    return a;
}
//permet de faire en sorte que l'arbre reste équilibré en utilisant les rotation et double rotation
pArbret1 equilibre(pArbret1 a){
    if(a->equ>=2){              //si l'équilibre du noeud est positif
            if(a->fd->equ>=0){     // équilibre supérieur a 0
                return a=rotationgauche(a); //rotationsimple
            }
            else{
                    return a=doublerotationgauche(a); //sinon double rotation
            }
    }
    if(a->equ<=-2){
        if(a->fg->equ<=0){
                return a=rotationdroite(a);
        }
        else{
                return a=doublerotationdroite(a);
        }
    }
    else{
            return a;
    }
}
pArbret1 insertiont1(pArbret1 a, int ID,float temp,float min,float max){
    int h=0;
    if(a==NULL){
        h=1;
        return a=creation(ID,temp,max,min);
    }
    else if(ID<a->ID){
        a->fg=insertiont1(a->fg,ID,temp,min,max);
        h=-1;
    }
    else if(ID>a->ID){
        a->fd=insertiont1(a->fd,ID,temp,min,max);
    }
    else{
            h=0;
            a->temp=(a->temp+temp)/2;
            if(max>a->max){
                a->max=max;
            }
            if(min<a->min){
                a->min=min;
            }
            return a;
    }
    if(h!=0){
        a->equ=a->equ+h;
        a=equilibre(a);
        if(a==NULL){
                h=0;
        }
        else{
                h=-1;
        }
    }
    return a;
}


pArbret1  creationarbret1(pArbret1 a){
    FILE *fp=fopen("tempo.txt","r");
    if(fp==NULL){
        printf("erreur  fopen ");
        exit (2);
    }
    char buffer[2048];
    int ID;
    float temp,max,min;
        while(fgets(buffer,2048,fp)!=NULL){
            int ret=sscanf(buffer,"%d %f %f %f",&ID,&temp,&min,&max); 
            ;     //recupere les 4 champs du fichier temporaire
            if(ret!=4){
                printf("erreur lors de la lescture des champs");
                exit(4);
            }

                a=insertiont1(a,ID,temp,min,max);  
                                        //insertion dans l'arbre en fonction de l'identifiant de la station
           }
    fclose(fp);
    return a;
        
}

void parcoursinfixet1(pArbret1 a,FILE *fp){
    if(a!=NULL){
            parcoursinfixet1(a->fg,fp);
           fprintf(fp,"%d %f %f %f\n",a->ID, a->temp,a->min,a->max);
            parcoursinfixet1(a->fd,fp);
    }
}


void temperatureavl(){
    FILE *fp=fopen("t1.dat","w");
    if(fp==NULL){
        printf("erreur fopen");
        exit(2);
    }


    pArbret1 nouveau=NULL;
    nouveau=creationarbret1(nouveau);
    parcoursinfixet1(nouveau,fp);    
    free(nouveau);
}


/*----------------------  -p1 --avl  -------------*/

//structure pour AVL 


//crée un noeud avec les données de Station pour pouvoir l'insérer dans un AVL 
pArbrep1 creationp1(int ID,float pres, float max, float min ){
    pArbrep1 nouveau=malloc(sizeof(Arbret1));
    if(nouveau==NULL){
        printf("erreur allocation");
        exit(4);
    }
    nouveau->ID=ID;
    nouveau->pres=pres;
    nouveau->max=max;
    nouveau->min=min;
    nouveau->fg=NULL;
    nouveau->fd=NULL;
    nouveau->equ=0;
    return nouveau;
}
//permet de faire une roation gauche de l'AVL pour le réequillibré
pArbrep1 rotationgauchep1(pArbrep1 a){
    pArbrep1 t;
    int a_eq;
    int t_eq;
    t=a->fd;
    a->fd=t->fg;
    t->fg=a;
    a_eq=a->equ;
    t_eq=t->equ;
    a->equ=a->equ-max(t_eq,0)-1;
    t->equ=min(a_eq-2,min(a_eq+t_eq-2,t_eq-1));
    a=t;
    return a;
}
//permet de faire une rotation droite de l'AVL pour le réequilibré
pArbrep1 rotationdroitep1(pArbrep1 a){
    pArbrep1 t;
    int a_eq;
    int t_eq;
    t=a->fg;
    a->fg=t->fd;
    t->fd=a;
    a_eq=a->equ;
    t_eq=t->equ;
    a->equ=a_eq-min(t_eq,0)+1;
    t->equ=max(a_eq+2,max(a_eq+2+t_eq,t_eq+1));
    a=t;
    return a;
}
//permet de faire une doublerotation pour le réequilibré
pArbrep1 doublerotationgauchep1(pArbrep1 a){
    a->fd=rotationdroitep1(a->fd);
    a=rotationgauchep1(a);
    return a;

}
//permet de faire une doublerotation pour le réequilibré
pArbrep1 doublerotationdroitep1(pArbrep1 a){
    a->fg=rotationgauchep1(a->fg);
    a=rotationdroitep1(a);
    return a;
}
//permet de faire en sorte que l'arbre reste équilibré en utilisant les rotation et double rotation
pArbrep1 equilibrep1(pArbrep1 a){
    if(a->equ>=2){              //si l'équilibre du noeud est positif
            if(a->fd->equ>=0){     // équilibre supérieur a 0
                return a=rotationgauchep1(a); //rotationsimple
            }
            else{
                    return a=doublerotationgauchep1(a); //sinon double rotation
            }
    }
    if(a->equ<=-2){
        if(a->fg->equ<=0){
                return a=rotationdroitep1(a);
        }
        else{
                return a=doublerotationdroitep1(a);
        }
    }
    else{
            return a;
    }
}
pArbrep1 insertionp1(pArbrep1 a, int ID,float pres,float min,float max){
    int h=0;
    if(a==NULL){
        h=1;
        return a=creationp1(ID,pres,max,min);
    }
    else if(ID<a->ID){
        a->fg=insertionp1(a->fg,ID,pres,min,max);
        h=-1;
    }
    else if(ID>a->ID){
        a->fd=insertionp1(a->fd,ID,pres,min,max);
    }
    else{
            h=0;
            a->pres=(a->pres+pres)/2;
            if(max>a->max){
                a->max=max;
            }
            if(min<a->min){
                a->min=min;
            }
            return a;
    }
    if(h!=0){
        a->equ=a->equ+h;
        a=equilibrep1(a);
        if(a==NULL){
                h=0;
        }
        else{
                h=-1;
        }
    }
    return a;
}


pArbrep1  creationarbrep1(pArbrep1 a){
    FILE *fp=fopen("tempo1.txt","r");
    if(fp==NULL){
        printf("erreur  fopen ");
        exit (2);
    }
    char buffer[2048];
    int ID;
    float pres,max,min;
        while(fgets(buffer,2048,fp)!=NULL){
            int ret=sscanf(buffer,"%d %f %f %f",&ID,&pres,&min,&max); 
                //recupere les 4 champs du fichier temporaire
            if(ret!=4){
                printf("erreur lors de la lecture des champs");
                exit(4);
            }

                a=insertionp1(a,ID,pres,min,max);  
                                        //insertion dans l'arbre en fonction de l'identifiant de la station
           }
    fclose(fp);
    return a;
        
}

void parcoursinfixep1(pArbrep1 a,FILE *fp){
    if(a!=NULL){
            parcoursinfixep1(a->fg,fp);
           fprintf(fp,"%d %f %f %f\n",a->ID, a->pres,a->min,a->max);
            parcoursinfixep1(a->fd,fp);
    }
}


void pressionavl(){
    FILE *fp=fopen("p1.dat","w");
    if(fp==NULL){
        printf("erreur fopen");
        exit(2);
    }


    pArbrep1 nouveau=NULL;
    nouveau=creationarbrep1(nouveau);
    parcoursinfixep1(nouveau,fp);    
    fclose(fp);
    free(nouveau);
}







/* ------------------    -w --abr -------------------*/



pwind creationw(int ID,double x,double y,float lat, float lon){
    pwind nouveau=malloc(sizeof(Wind));
    if(nouveau==NULL){
        printf("erreur allocation ");
        exit(4);
    }
    else{
        nouveau->ID=ID;
        nouveau->x=x;
        nouveau->y=y;
        nouveau->lat=lat;
        nouveau->lon=lon;
        nouveau->fg=NULL;
        nouveau->fd=NULL;
    }
    return nouveau;
}



pwind insertionw(pwind a, int ID, double x, double y,float lat,float lon){
        if(a==NULL){
            return creationw(ID,x,y,lat,lon);
        }
        else if(ID<a->ID){
            a->fg=insertionw(a->fg,ID,x,y,lat,lon);
        }
        else if (ID>a->ID){
            a->fd=insertionw(a->fd,ID,x,y,lat,lon);
        }
        else if(ID==a->ID){
            a->x=((a->x+x)/2);// permet alors de retourner la moyenne de la station qui apparait plusieur fois dans le csv
            a->y=((a->y+y)/2);
        }
        return a;
}


double mcos(double a){  // calcul le cosinus de l'angle a, sachant que l'angle a est un angle données en radiant 
    int signe=1;
    double resultat=0.0;
    double term=1.0;
    for(int i=1; term> 1e12; i++){
        resultat += term;
        term *= -a *a / (2*i*(2*i-1));
        term *= signe;
        signe= -signe;
    }
    return resultat;
} //FONCTION QUI PEUT ETRE UTILE
 int recherche(pwind a, int ID){
 	if(a==NULL){
 		return 0;
 	}
 	else if (a->ID==ID){
 		printf("%d %lf %lf",a->ID, a->x, a->y);
 	}
 	else if(ID< a->ID){
 		return recherche(a->fg,ID);
 	}
 	else{
 		return recherche (a->fd,ID);
 	}
 }  // pareil utile pour verification
pwind  creationarbrew(pwind a){
    FILE *fp=fopen("tempo2.txt","r");
    if(fp==NULL){
        printf("erreur  fopen ");
        exit (2);
    }
    char buffer[2048];
    int ID;
    double direct;
    float v;
    float lat;
    float lon;
        while(fgets(buffer,2048,fp)!=NULL){
            int ret=sscanf(buffer,"%d %lf %f %f %f",&ID,&direct,&v,&lat,&lon); //recupere les 3 champs du fichier temporaire

            if(ret!=5){
                printf("erreur lors de la lescture des champs");
		printf("%d",ID);
                exit(4);
            }   
            
            double c= (direct*M_PI)/180;  // coverti l'angle du fichier csv donnée en degré en radiant 
            double x=cos(c)*v;    
                     // la composante x du vent est données par cette formule  x=cos(direction)*vitesse
            double y=sin(c)*v;

                a=insertionw(a,ID,x,y,lat,lon);
                                        //insertion dans l'arbre en fonction de l'identifiant de la station
           }
    fclose(fp);
    return a;
        
}



void parcoursinfixew(pwind a, FILE *fp){
    if(a!=NULL){
        parcoursinfixew(a->fg, fp);
        fprintf(fp,"%d %lf %lf %f %f \n",a->ID ,a->x,a->y,a->lat,a->lon);
        //ecriture dans  fichier.dat dans l'ordre croissant des fonctions 
        parcoursinfixew(a->fd, fp);
    }
}


//permet de faire le tri du fichier texte dans un ABR et de réecrire les données du fichier texte désordonée dans l'ordre croissant des stations dans fichier.dat
void wind(){
    FILE *fp=fopen("w.dat","w");
    if(fp==NULL){
        printf("erreur fopen");
        exit(2);
    }

    pwind nouveau=NULL;
    nouveau=creationarbrew(nouveau);
    parcoursinfixew(nouveau,fp);    
    fclose(fp);
}


/*----------------*/

/*-------- -w --avl -----------------*/


pwind1 creationw1(int ID, double x,double y,float lat, float lon){
    pwind1 nouveau=malloc(sizeof(Wind1));
    if(nouveau==NULL){
        printf("erreur allocation ");
        exit(4);
    }
    else{
        nouveau->ID=ID;
        nouveau->x=x;
        nouveau->y=y;
        nouveau->lat=lat;
        nouveau->lon=lon;
        nouveau->fg=NULL;
        nouveau->fd=NULL;
        nouveau->equ=0;
    }
    return nouveau;
}	


pwind1 rotationgauchew1(pwind1 a){
	pwind1 t;
	int a_eq;
	int t_eq;
	t=a->fd;
	a->fd=t->fg;
	t->fg=a;
    	a_eq=a->equ;
    	t_eq=t->equ;
    	a->equ=a->equ-max(t_eq,0)-1;
    	t->equ=min(a_eq-2,min(a_eq+t_eq-2,t_eq-1));
    	a=t;
    	return a;
}

pwind1 rotationdroitew1(pwind1 a){
	pwind1 t;
    	int a_eq;
    	int t_eq;
    	t=a->fg;
    	a->fg=t->fd;
    	t->fd=a;
    	a_eq=a->equ;
    	t_eq=t->equ;
    	a->equ=a_eq-min(t_eq,0)+1;
    	t->equ=max(a_eq+2,max(a_eq+2+t_eq,t_eq+1));
    	a=t;
    	return a;
}

pwind1 doublerotationgauchew1(pwind1 a){
    a->fd=rotationdroitew1(a->fd);
    a=rotationgauchew1(a);
    return a;

}
//permet de faire une doublerotation pour le réequilibré
pwind1 doublerotationdroitew1(pwind1 a){
    a->fg=rotationgauchew1(a->fg);
    a=rotationdroitew1(a);
    return a;
}
//permet de faire en sorte que l'arbre reste équilibré en utilisant les rotation et double rotation
pwind1 equilibrew1(pwind1 a){
    if(a->equ>=2){              //si l'équilibre du noeud est positif
            if(a->fd->equ>=0){     // équilibre supérieur a 0
                return a=rotationgauchew1(a); //rotationsimple
            }
            else{
                    return a=doublerotationgauchew1(a); //sinon double rotation
            }
    }
    if(a->equ<=-2){
        if(a->fg->equ<=0){
                return a=rotationdroitew1(a);
        }
        else{
                return a=doublerotationdroitew1(a);
        }
    }
    else{
            return a;
    }
}

pwind1 insertionw1(pwind1 a, int ID,double x,double y,float lat, float lon){
    int h=0;
    if(a==NULL){
        h=1;
        return a=creationw1(ID,x,y,lat,lon);
    }
    else if(ID<a->ID){
        a->fg=insertionw1(a->fg,ID,x,y,lat,lon);
        h=-1;
    }
    else if(ID>a->ID){
        a->fd=insertionw1(a->fd,ID,x,y,lat,lon);
    }
    else{
            h=0;
            a->x=(a->x+x)/2;
	    a->y=(a->y+y)/2;
            return a;
    }
    if(h!=0){
        a->equ=a->equ+h;
        a=equilibrew1(a);
        if(a==NULL){
                h=0;
        }
        else{
                h=-1;
        }
    }
    return a;
}

pwind1  creationarbrew1(pwind1 a){
    FILE *fp=fopen("tempo2.txt","r");
    if(fp==NULL){
        printf("erreur  fopen ");
        exit (2);
    }
    char buffer[2048];
    int ID;
    double direct;
    float v;
    float lat;
    float lon;
        while(fgets(buffer,2048,fp)!=NULL){
            int ret=sscanf(buffer,"%d %lf %f %f %f",&ID,&direct,&v,&lat,&lon); //recupere les 3 champs du fichier temporaire
            if(ret!=5){
                printf("erreur lors de la lescture des champs");
		printf("%d",ID);
                exit(4);
            }   
            
            double c= (direct*M_PI)/180;  // coverti l'angle du fichier csv donnée en degré en radiant 
            double x=cos(c)*v;    
                     // la composante x du vent est données par cette formule  x=cos(direction)*vitesse
            double y=sin(c)*v;

                a=insertionw1(a,ID,x,y,lat,lon);
                                        //insertion dans l'arbre en fonction de l'identifiant de la station
           }
    fclose(fp);
    return a;
        
}

void parcoursinfixew1(pwind1 a, FILE *fp){
    if(a!=NULL){
        parcoursinfixew1(a->fg, fp);
        fprintf(fp,"%d %lf %lf %f %f \n",a->ID ,a->x,a->y,a->lat,a->lon);
        //ecriture dans  fichier.dat dans l'ordre croissant des fonctions 
        parcoursinfixew1(a->fd, fp);
    }
}

void wind1(){
    FILE *fp=fopen("w.dat","w");
    if(fp==NULL){
        printf("erreur fopen");
        exit(2);
    }

    pwind1 nouveau=NULL;
    nouveau=creationarbrew1(nouveau);
    parcoursinfixew1(nouveau,fp);    
    fclose(fp);
}

/*----- -h --avl */


//crée un noeud avec les données de Station pour pouvoir l'insérer dans un AVL 
pArbreh1 creationh1(int ID,float lat, float lon,float alt){
    pArbreh1 nouveau=malloc(sizeof(Arbreh1));
    if(nouveau==NULL){
        printf("erreur allocation");
        exit(4);
    }
    nouveau->ID=ID;
    nouveau->alt=alt;
    nouveau->lat=lat;
    nouveau->lon=lon;
    nouveau->fg=NULL;
    nouveau->fd=NULL;
    nouveau->equ=0;
    return nouveau;
}

//permet de faire une roation gauche de l'AVL pour le réequillibré
pArbreh1 rotationgaucheh1(pArbreh1 a){
    pArbreh1 t;
    int a_eq;
    int t_eq;
    t=a->fd;
    a->fd=t->fg;
    t->fg=a;
    a_eq=a->equ;
    t_eq=t->equ;
    a->equ=a->equ-max(t_eq,0)-1;
    t->equ=min(a_eq-2,min(a_eq+t_eq-2,t_eq-1));
    a=t;
    return a;
}
//permet de faire une rotation droite de l'AVL pour le réequilibré
pArbreh1 rotationdroiteh1(pArbreh1 a){
    pArbreh1 t;
    int a_eq;
    int t_eq;
    t=a->fg;
    a->fg=t->fd;
    t->fd=a;
    a_eq=a->equ;
    t_eq=t->equ;
    a->equ=a_eq-min(t_eq,0)+1;
    t->equ=max(a_eq+2,max(a_eq+2+t_eq,t_eq+1));
    a=t;
    return a;
}

//permet de faire une doublerotation pour le réequilibré
pArbreh1 doublerotationgaucheh1(pArbreh1 a){
    a->fd=rotationdroiteh1(a->fd);
    a=rotationgaucheh1(a);
    return a;

}

//permet de faire une doublerotation pour le réequilibré
pArbreh1 doublerotationdroiteh1(pArbreh1 a){
    a->fg=rotationgaucheh1(a->fg);
    a=rotationdroiteh1(a);
    return a;
}

//permet de faire en sorte que l'arbre reste équilibré en utilisant les rotation et double rotation
pArbreh1 equilibreh1(pArbreh1 a){
    if(a->equ>=2){              //si l'équilibre du noeud est positif
            if(a->fd->equ>=0){     // équilibre supérieur a 0
                return a=rotationgaucheh1(a); //rotationsimple
            }
            else{
                    return a=doublerotationgaucheh1(a); //sinon double rotation
            }
    }
    if(a->equ<=-2){
        if(a->fg->equ<=0){
                return a=rotationdroiteh1(a);
        }
        else{
                return a=doublerotationdroiteh1(a);
        }
    }
    else{
            return a;
    }
}

// fonction d'insertion en avl pour altitude
pArbreh1 insertionh1(pArbreh1 a, int ID,float lat, float lon,float alt){
    int h=0;
    if(a==NULL){
        h=1;
        return a=creationh1(ID,lat,lon,alt);
    }
    else if(alt<a->alt){
        a->fg=insertionh1(a->fg,ID,lat,lon,alt);
        h=-1;
    }
    else if(alt>a->alt){
        a->fd=insertionh1(a->fd,ID,lat,lon,alt);
    }
    else{
        h=0;
        return a;
    }
    if(h!=0){
        a->equ=a->equ+h;
        a=equilibreh1(a);
        if(a==NULL){
                h=0;
        }
        else{
                h=-1;
        }
    }
    return a;
}

pArbreh1  creationarbreh1(pArbreh1 a){
    FILE *fp=fopen("tempo3.txt","r");
    if(fp==NULL){
        printf("erreur  fopen ");
        exit (2);
    }
    char buffer[2048];
    int ID;
    float alt;
    float lon;
    float lat;
        while(fgets(buffer,2048,fp)!=NULL){
            int ret=sscanf(buffer,"%d %f %f %f",&ID,&lat,&lon,&alt); 
                //recupere les 4 champs du fichier temporaire
            if(ret!=4){
                printf("erreur lors de la lecture des champs");
                exit(4);
            }

                a=insertionh1(a,ID,lat,lon,alt);  
                                        //insertion dans l'arbre en fonction de l'identifiant de la station
           }
    fclose(fp);
    return a;
}

void parcoursRinfixeh1(pArbreh1 a,FILE *fp){
    if(a!=NULL){
            parcoursRinfixeh1(a->fd,fp);
            fprintf(fp,"%d %f %f %f\n",a->ID, a->alt, a->lat, a->lon);
            parcoursRinfixeh1(a->fg,fp);
    }
}


void altitudeavl(){
    FILE *fp=fopen("h.dat","w");
    if(fp==NULL){
        printf("erreur fopen");
        exit(2);
    }


    pArbreh1 nouveau=NULL;
    nouveau=creationarbreh1(nouveau);
    parcoursRinfixeh1(nouveau,fp);    
    fclose(fp);
    free(nouveau);
}


/*---------------------------   -m --avl ------------------------------*/



//crée un noeud avec les données de Station pour pouvoir l'insérer dans un AVL 
pArbrem1 creationm1(int ID,float lat, float lon,float hum){
    pArbrem1 nouveau=malloc(sizeof(Arbrem1));
    if(nouveau==NULL){
        printf("erreur allocation");
        exit(4);
    }
    nouveau->ID=ID;
    nouveau->hum=hum;
    nouveau->lat=lat;
    nouveau->lon=lon;
    nouveau->fg=NULL;
    nouveau->fd=NULL;
    nouveau->equ=0;
    return nouveau;
}

//permet de faire une roation gauche de l'AVL pour le réequillibré
pArbrem1 rotationgauchem1(pArbrem1 a){
    pArbrem1 t;
    int a_eq;
    int t_eq;
    t=a->fd;
    a->fd=t->fg;
    t->fg=a;
    a_eq=a->equ;
    t_eq=t->equ;
    a->equ=a->equ-max(t_eq,0)-1;
    t->equ=min(a_eq-2,min(a_eq+t_eq-2,t_eq-1));
    a=t;
    return a;
}
//permet de faire une rotation droite de l'AVL pour le réequilibré
pArbrem1 rotationdroitem1(pArbrem1 a){
    pArbrem1 t;
    int a_eq;
    int t_eq;
    t=a->fg;
    a->fg=t->fd;
    t->fd=a;
    a_eq=a->equ;
    t_eq=t->equ;
    a->equ=a_eq-min(t_eq,0)+1;
    t->equ=max(a_eq+2,max(a_eq+2+t_eq,t_eq+1));
    a=t;
    return a;
}

//permet de faire une doublerotation pour le réequilibré
pArbrem1 doublerotationgauchem1(pArbrem1 a){
    a->fd=rotationdroitem1(a->fd);
    a=rotationgauchem1(a);
    return a;

}

//permet de faire une doublerotation pour le réequilibré
pArbrem1 doublerotationdroitem1(pArbrem1 a){
    a->fg=rotationgauchem1(a->fg);
    a=rotationdroitem1(a);
    return a;
}

//permet de faire en sorte que l'arbre reste équilibré en utilisant les rotation et double rotation
pArbrem1 equilibrem1(pArbrem1 a){
    if(a->equ>=2){              //si l'équilibre du noeud est positif
            if(a->fd->equ>=0){     // équilibre supérieur a 0
                return a=rotationgauchem1(a); //rotationsimple
            }
            else{
                    return a=doublerotationgauchem1(a); //sinon double rotation
            }
    }
    if(a->equ<=-2){
        if(a->fg->equ<=0){
                return a=rotationdroitem1(a);
        }
        else{
                return a=doublerotationdroitem1(a);
        }
    }
    else{
            return a;
    }
}


// fonction d'insertion en avl pour altitude
pArbrem1 insertionm1(pArbrem1 a, int ID,float lat, float lon,float hum){
    int h=0;
    if(a==NULL){
        h=1;
        return a=creationm1(ID,lat,lon,hum);
    }
    else if(hum<a->hum){
        a->fg=insertionm1(a->fg,ID,lat,lon,hum);
        h=-1;
    }
    else if(hum>a->hum){
        a->fd=insertionm1(a->fd,ID,lat,lon,hum);
    }
    else{
        h=0;
        return a;
    }
    if(h!=0){
        a->equ=a->equ+h;
        a=equilibrem1(a);
        if(a==NULL){
                h=0;
        }
        else{
                h=-1;
        }
    }
    return a;
}


pArbrem1  creationarbrem1(pArbrem1 a){
    FILE *fp=fopen("tempo4.txt","r");
    if(fp==NULL){
        printf("erreur  fopen ");
        exit (2);
    }
    char buffer[2048];
    int ID;
    float hum;
    float lon;
    float lat;
        while(fgets(buffer,2048,fp)!=NULL){
            int ret=sscanf(buffer,"%d %f %f %f",&ID,&hum,&lat,&lon); 
                //recupere les 4 champs du fichier temporaire
            if(ret!=4){
                printf("erreur lors de la lecture des champs");
                exit(4);
            }

                a=insertionm1(a,ID,lat,lon,hum);  
                                        //insertion dans l'arbre en fonction de l'identifiant de la station
           }
    fclose(fp);
    return a;
}

void parcoursRinfixem1(pArbrem1 a,FILE *fp){
    if(a!=NULL){
            parcoursRinfixem1(a->fd,fp);
            fprintf(fp,"%d %f %f %f\n",a->ID, a->hum, a->lat, a->lon);
            parcoursRinfixem1(a->fg,fp);
    }
}


void humiditeavl(){
    FILE *fp=fopen("m.dat","w");
    if(fp==NULL){
        printf("erreur fopen");
        exit(2);
    }


    pArbrem1 nouveau=NULL;
    nouveau=creationarbrem1(nouveau);
    parcoursRinfixem1(nouveau,fp);    
    fclose(fp);
    free(nouveau);
}



	/*------ -h --abr ----------*/


pAltitude creationalt(int ID,float lat, float lon, float alt){
    pAltitude nouveau=malloc(sizeof(Altitude));
    if(nouveau==NULL){
        printf("erreur allocation ");
        exit(4);
    }
    else{
        nouveau->ID=ID;
        nouveau->alt=alt;
        nouveau->lat=lat;
        nouveau->lon=lon;
        nouveau->fg=NULL;
        nouveau->fd=NULL;
    }
    return nouveau;
}

pAltitude insertionalt(pAltitude a, int ID,float lat, float lon, float alt){
        if(a==NULL){
            return creationalt(ID,lat,lon,alt);
        }
        else if(alt<a->alt){
            a->fg=insertionalt(a->fg,ID,lat,lon,alt);
        }
        else if (alt>a->alt){
            a->fd=insertionalt(a->fd,ID,lat,lon,alt);
        }
        else {
            a->alt=alt;
        }
        return a;
}

pAltitude  creationarbrealt(pAltitude a){
    FILE *fp=fopen("tempo3.txt","r");
    if(fp==NULL){
        printf("erreur  fopen ");
        exit (2);
    }
    char buffer[2048];
    int ID;
    float alt;
    float lat;
    float lon;
        while(fgets(buffer,2048,fp)!=NULL){   //récupère les lignes 
            int ret=sscanf(buffer,"%d %f %f %f",&ID,&lat,&lon,&alt);      //recupere les 2 champs du fichier temporaire
            if(ret!=4){
                printf("erreur lors de la lescture des champs");
                exit(4);
            }
                a=insertionalt(a,ID,lat,lon,alt);             //insertion dans l'arbre en fonction de l'identifiant de la station
        }
        
    fclose(fp);
    return a;
        
}

void parcoursRinfixealt(pAltitude a,FILE *fp){
    if(a!=NULL){
            parcoursRinfixealt(a->fd,fp);
            fprintf(fp,"%d %f %f %f\n",a->ID, a->alt, a->lat, a->lon);
            parcoursRinfixealt(a->fg,fp);
    }
}

void altitude(){
    FILE *fp=fopen("h.dat","w");
    if(fp==NULL){
        printf("erreur fopen");
        exit(2);
    }

    pAltitude nouveau=NULL;
    nouveau=creationarbrealt(nouveau);
    parcoursRinfixealt(nouveau,fp);    
    fclose(fp);
}

/*----------------   -m --abr ---------------------------*/



pHumidite creationhum(int ID,float lat, float lon, float hum){
    pHumidite nouveau=malloc(sizeof(Humidite));
    if(nouveau==NULL){
        printf("erreur allocation ");
        exit(4);
    }
    else{
        nouveau->ID=ID;
        nouveau->hum=hum;
        nouveau->lat=lat;
        nouveau->lon=lon;
        nouveau->fg=NULL;
        nouveau->fd=NULL;
    }
    return nouveau;
}

pHumidite insertionhum(pHumidite a, int ID,float lat, float lon, float hum){
        if(a==NULL){
            return creationhum(ID,lat,lon,hum);
        }
        else if(hum<a->hum){
            a->fg=insertionhum(a->fg,ID,lat,lon,hum);
        }
        else if(hum>a->hum){
            a->fd=insertionhum(a->fd,ID,lat,lon,hum);
        }
        return a;
}

pHumidite  creationarbrehum(pHumidite a){
    FILE *fp=fopen("tempo4.txt","r");
    if(fp==NULL){
        printf("erreur  fopen ");
        exit (2);
    }
    char buffer[2048];
    int ID;
    float hum;
    float lat;
    float lon;
        while(fgets(buffer,2048,fp)!=NULL){   //récupère les lignes 
            int ret=sscanf(buffer,"%d %f %f %f",&ID,&hum,&lat,&lon);      //recupere les 2 champs du fichier temporaire
            if(ret!=4){
                printf("erreur lors de la lescture des champs");
                exit(4);
            }
                a=insertionhum(a,ID,lat,lon,hum);             //insertion dans l'arbre en fonction de l'identifiant de la station
        }
        
    fclose(fp);
    return a;
        
}

void parcoursRinfixehum(pHumidite a,FILE *fp){
    if(a!=NULL){
            parcoursRinfixehum(a->fd,fp);
            fprintf(fp,"%d %f %f %f\n",a->ID, a->hum, a->lat, a->lon);
            parcoursRinfixehum(a->fg,fp);
    }
}

void humidite(){
    FILE *fp=fopen("m.dat","w");
    if(fp==NULL){
        printf("erreur fopen");
        exit(2);
    }

    pHumidite nouveau=NULL;
    nouveau=creationarbrehum(nouveau);
    parcoursRinfixehum(nouveau,fp);    
    fclose(fp);
}


