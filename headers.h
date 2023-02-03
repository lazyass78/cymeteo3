#ifndef HEADERS_H
#define HEADERS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUFFER 1000
#define SEP ';'


typedef struct arbre{
        int ID;
        float temp;
        float max;
        float min;
        struct arbre *fg;
        struct arbre *fd;
}Arbre;

typedef Arbre* pArbre;


typedef struct pression{
        int ID;
        float pres;
        float max;
        float min;
        struct pression *fg;
        struct pression *fd;
}Pression;

typedef Pression* ppression;

typedef struct arbret1{
        int ID;
        float temp;
        float max;
        float min;
        struct arbret1 *fg;
        struct arbret1 *fd;
        int equ;
}Arbret1;



typedef Arbret1* pArbret1;
typedef struct arbrep1{
        int ID;
        float pres;
        float max;
        float min;
        struct arbrep1 *fg;
        struct arbrep1 *fd;
        int equ;
}Arbrep1;



typedef Arbrep1* pArbrep1;

typedef struct wind{
        int ID;
        double x;
        double y;
        float lat;
        float lon;
        struct wind *fg;
        struct wind *fd;
}Wind;

typedef Wind * pwind;

typedef Arbrep1* pArbrep1;

typedef struct wind1{
        int ID;
        double x;
        double y;
        float lat;
        float lon;
        struct wind1 *fg;
        struct wind1 *fd;
        int equ;
}Wind1;

typedef Wind1 * pwind1;

//structure pour AVL 
typedef struct arbreh1 {
        int ID;
        float alt;
        float lat;
        float lon;
        struct arbreh1 *fg;
        struct arbreh1 *fd;
        int equ;
}Arbreh1;

typedef Arbreh1* pArbreh1;

//structure pour AVL 
typedef struct arbrem1 {
        int ID;
        float hum;
        float lat;
        float lon;
        struct arbrem1 *fg;
        struct arbrem1 *fd;
        int equ;
}Arbrem1;

typedef Arbrem1* pArbrem1;

typedef struct altitude{
        int ID;
        float alt;
        float lat;
        float lon;
        struct altitude *fg;
        struct altitude *fd;
}Altitude;

typedef Altitude* pAltitude;

typedef struct humidite{
        int ID;
        float hum;
        float lat;
        float lon;
        struct humidite *fg;
        struct humidite *fd;
}Humidite;

typedef Humidite* pHumidite;

pArbre creationt(int ID,float temp,float max,float min);
Arbre* insertiont(Arbre* , int ID , float temp , float max , float min );
Arbre*  creationarbret(Arbre* );
void parcoursinfixe(Arbre* , FILE *fp );
void temperature();

Pression* creationp(int ID ,float pres ,float max ,float min);
Pression* insertionp(Pression* ,int ID ,float pres ,float max ,float min);
Pression*  creationarbrep(Pression* );
void parcoursinfixep(Pression* ,FILE *fp);
void pression();

int max(int a,int e);
int min(int a,int e );

Arbret1* creation(int ID,float temp, float max, float min);
Arbret1* rotationgauche(Arbret1* a );
Arbret1* rotationdroite(Arbret1* a);
Arbret1* doublerotationgauche(Arbret1* a);
Arbret1* doublerotationdroite(Arbret1* a);
Arbret1* equilibre(Arbret1* a);
Arbret1* insertiont1(Arbret1* a, int ID,float temp,float min,float max);
Arbret1*  creationarbret1(Arbret1* a);
void parcoursinfixet1(Arbret1* a,FILE *f);
void temperatureavl();

Arbrep1*creationp1(int ID,float pres, float max, float min );
Arbrep1*rotationgauchep1(Arbrep1* a);
Arbrep1* rotationdroitep1(Arbrep1* a);
Arbrep1* doublerotationgauchep1(Arbrep1*a );
Arbrep1* doublerotationdroitep1(Arbrep1* a);
Arbrep1* equilibrep1(Arbrep1* a);
Arbrep1* insertionp1(Arbrep1* a, int ID,float pres,float min,float max);
Arbrep1*  creationarbrep1(Arbrep1* a);
void parcoursinfixep1(Arbrep1* a,FILE *fp);
void pressionavl();

pwind creationw(int ID,double x,double y,float lat, float lon );
Wind * insertionw(Wind *a, int ID, double x, double y,float lat,float lon);
double mcos(double a);
int recherche(Wind* a, int ID);
Wind *  creationarbrew(Wind * a);
void parcoursinfixew(Wind * a, FILE *fp );
void wind();

pwind1 creationw1(int ID, double x,double y,float lat, float lon);
pwind1 rotationgauchew1(pwind1 a);
pwind1 rotationdroitew1(pwind1 a);
pwind1 doublerotationgauchew1(pwind1 a);
pwind1 doublerotationdroitew1(pwind1 a);
pwind1 equilibrew1(pwind1 a);
pwind1 insertionw1(pwind1 a, int ID,double x,double y,float lat, float lon);
pwind1  creationarbrew1(pwind1 a);
void parcoursinfixew1(pwind1 a, FILE *fp);
void wind1();


pArbreh1 creationh1(int ID,float lat, float lon,float alt);
pArbreh1 rotationgaucheh1(pArbreh1 a);
pArbreh1 rotationdroiteh1(pArbreh1 a);
pArbreh1 doublerotationgaucheh1(pArbreh1 a);
pArbreh1 doublerotationdroiteh1(pArbreh1 a);
pArbreh1 equilibreh1(pArbreh1 a);
pArbreh1 insertionh1(pArbreh1 a, int ID,float lat, float lon,float alt);
pArbreh1  creationarbreh1(pArbreh1 a);
void parcoursRinfixeh1(pArbreh1 a,FILE *fp);
void altitudeavl();

pArbrem1 creationm1(int ID,float lat, float lon,float hum);
pArbrem1 rotationgauchem1(pArbrem1 a);
pArbrem1 rotationdroitem1(pArbrem1 a);
pArbrem1 doublerotationgauchem1(pArbrem1 a);
pArbrem1 doublerotationdroitem1(pArbrem1 a);
pArbrem1 equilibrem1(pArbrem1 a);
pArbrem1 insertionm1(pArbrem1 a, int ID,float lat, float lon,float hum);
pArbrem1  creationarbrem1(pArbrem1 a);
void parcoursRinfixem1(pArbrem1 a,FILE *fp);
void humiditeavl();

pAltitude creationalt(int ID,float lat, float lon, float alt);
pAltitude insertionalt(pAltitude a, int ID,float lat, float lon, float alt);
pAltitude  creationarbrealt(pAltitude a);
void parcoursRinfixealt(pAltitude a,FILE *fp);
void altitude();

pHumidite creationhum(int ID,float lat, float lon, float hum);
pHumidite insertionhum(pHumidite a, int ID,float lat, float lon, float hum);
pHumidite  creationarbrehum(pHumidite a);
void parcoursRinfixehum(pHumidite a,FILE *fp);
void humidite();



#endif
