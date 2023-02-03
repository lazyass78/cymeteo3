#include "headers.h"


int main(int argc, char *argv[]) {    
    if (argc == 3) {
        if (strcmp(argv[1], "-t1") == 0 && strcmp(argv[2], "ABR") == 0) {
            temperature();
            printf("-t1 --abr\n");
        }
  	 else if (strcmp(argv[1], "-h") == 0 && strcmp(argv[2], "ABR") == 0) {
        void altitude();
            printf("-h --abr\n");
        } 
        else if (strcmp(argv[1], "-w") == 0 && strcmp(argv[2], "ABR") == 0) {
            wind();
            printf("-w --abr\n");
        } 
        else if (strcmp(argv[1], "-m") == 0 && strcmp(argv[2], "ABR") == 0) {
            humidite();
            printf("-m --abr\n");
        } 
        else if (strcmp(argv[1], "-p1") == 0 && strcmp(argv[2], "ABR") == 0) {
            pression();
            printf("-p1 --abr\n");
        }
        else if (strcmp(argv[1], "-t1") == 0 && strcmp(argv[2], "AVL") == 0) {
        	temperatureavl();
        	printf("-t1 --avl\n");
        }
        else if (strcmp(argv[1], "-h") == 0 && strcmp(argv[2], "AVL") == 0) {
            altitudeavl();
        	printf("-h --avl\n");
        }
        else if (strcmp(argv[1], "-w") == 0 && strcmp(argv[2], "AVL") == 0) {
        	wind1();
        	printf("-w --avl\n");
        }
        else if (strcmp(argv[1], "-m") == 0 && strcmp(argv[2], "AVL") == 0) {
            humiditeavl();
        	printf("-m --avl\n");
        }
        else if (strcmp(argv[1], "-p1") == 0 && strcmp(argv[2], "AVL") == 0) {
        	pressionavl();
        	printf("-p1 --avl\n");
        	
        }
         else {
		printf("%s , %s",argv[1],argv[2]);
            printf("Cette combinaison n'existe pas \n");
        }
    } else {
        printf("Il n'y a pas assez d'argument \n");
    }
    return 0;
}


