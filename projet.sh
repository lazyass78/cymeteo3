#!/bin/bash

########################## Fonction vérification de l'option -f et du fichier de données ##########################



verif_fichier () {
a=$#                                        #Nombre d'arguments entrés en commande
if [ $# -lt 1 ]                             #Vérification : au moins un argument en commande
then 
    echo "Il faut noter des arguments en précisant au moins une option souhaite, voir l aide en tapant --help, si besoin"
    exit 1;
fi

for (( i=1 ; i<="$a" ; i++ ))               #Vérification de chaque argument de la commande pour trouver l'option -f
do  
    if [ "$1" == "-f" ] 
    then  
         shift;
         if [ -f "$1" ]                     #Vérification : le fichier qui suit l'option -f existe
         then 
            fichier="$1"
            echo "$fichier"
            exit 2;
         else 
            echo "Il faut que l option -f soit suivi d un nom de fichier existant, voir l aide en tapant --help, si besoin"  #-f (separé d'un espace) <nom_fichier> 
            exit 3;
         fi
    else 
        shift;
    fi
done
echo "Il faut ajouter l option -f <nom_fichier>, voir l aide en tapant --help, si besoin"
exit 4
}

fichier=$(verif_fichier "$@")               #Récupération du fichier de données
echo "$fichier"



########################## Tri en fonction des options -dates et -lieux du fichier de données ##########################

##awk cut eviter le for car trop long, faire des | et donc une longue ligne





########################## Récupération du mode de tri ##########################

TAB='--tab'
ABR='--abr'
AVL='--avl'

Tri1=0
Tri2=0
Tri3=0

STR=$*                                    #Récupération de la ligne de commande

case $STR in                              #Vérification si l'option --tab est présente
   *"$TAB"*) Tri1='TAB'
     ;;
esac

case $STR in                              #Vérification si l'option --abr est présente
   *"$ABR"*) Tri2='ABR'
     ;;
esac

case $STR in                              #Vérification si l'option --avl est présente
   *"$AVL"*) Tri3='AVL'
     ;;
esac

# Vérification du respect des règles de saisie du tri (1 seule option maximum et --avl par défaut)
if [[ "$Tri1" == 0 && "$Tri2" == 0 && "$Tri3" == 0 ]]; then
    Tri='AVL'
elif [[ "$Tri1" == 'TAB' && "$Tri2" == 0 && "$Tri3" == 0 ]]; then
    Tri='TAB'
elif [[ "$Tri1" == 0 && "$Tri2" == 'ABR' && "$Tri3" == 0 ]]; then
    Tri='ABR'
elif [[ "$Tri1" == 0 && "$Tri2" == 0 && "$Tri3" == 'AVL' ]]; then
    Tri='AVL'
else 
    echo "Vous devez saisir un seul mode de tri, voir l'aide en tapant --help, si besoin"
    exit 4
fi


if [[ "$Tri" == 'TAB' ]]
then 
    echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option" 
    exit  
fi  

echo "$Tri"                                          #Récupération de la variable de tri (Option : --tab ou --abr ou --avl)


########################## Fonction pour afficher le help ##########################

fonctionaide() {
cat << EOF  

Le script permet de traiter au choix un ou plusieurs types de données comme la température (option associée -t1), la pression atmosphérique (option associée -p1), le vent (option associée -w), l’humidité (option associée -m), ou l’altitude de chaque station (option associée -h).

Au moins l’une de ces options doit être choisie pour que le script fonctionne. Il est possible d’en activer plusieurs.


Les arguments et options du script [FICHIER] :

    -f <nom_fichier> 		(f)ichier d’entrée : Cette option est obligatoire. Le nom du fichier d’entrée doit être renseigné pour que le script puisse acquérir toutes les données.


Les arguments et options du script [TYPE de données] :

    -t1 				    (t)emperatures : Produit en sortie un diagramme de type barres d’erreur avec en abscisse l’identifiant de la station, et en ordonnée le minimum, maximum et la moyenne des températures 

    -p1 				    (p)ressions atmosphériques : Produit en sortie un diagramme de type barres d’erreur avec en abscisse l’identifiant de la station, et en ordonnée le minimum, maximum et la moyenne des pressions 

    -w				        vent ( (w)ind ) : Produit en sortie un diagramme de type vecteurs (flèches orientées) avec l’abscisse correspondant à la longitude (axe Ouest-Est) et l’ordonnée correspondant à la latitude (axe Sud-Nord). 

    -h				        altitude ( (h)eight) : Produit en sortie un diagramme de type carte interpolée et colorée de l’altitude avec l’abscisse correspondant à la longitude (axe Ouest-Est) et l’ordonnée correspondant à la latitude (axe Sud-Nord) de chaque station

    -m				        humidité ( (m)oisture ) : Produit en sortie un diagramme de type carte interpolée et colorée de l’humidité avec l’abscisse correspondant à la longitude (axe Ouest-Est) et l’ordonnée correspondant à la latitude (axe Nord-Sud) de chaque station


Les arguments et options du script [TRIS] :

Il est possible d’imposer le mode de tri des données par l’aide d’une structure d’arbre binaire,
ABR ou AVL. Ces options de tris sont exclusives entre elles : une seule peut être activée à la fois. Si aucune option de tri n’est activée, par défaut le tri se fera à l’aide d’un AVL.

    --abr : 				tri effectué l’aide d’une structure de type ABR

    --avl : 				tri effectué à l’aide d’une structure de type AVL


Exemples de commande :

    > ./projet.sh -t1 -w -f meteo_filtered_data_v1.csv

    > ./projet.sh -p1 --abr -f meteo_filtered_data_v1.csv

EOF
}




########################## Tri selon les options restantes du fichier de données ##########################

option=$(getopt -l "help" -o "t: p: d: f: whmFGSAOQ" -- "$@") #fonction getopt permettant de pouvoir créer des nouvelles options 
                                                                      # -l "..." = les options de types longues qui seront appelé de cette manière --tab
                                                                      # -o "..." = les options de types courtes (1 lettre), les ":" indiques que cette option prend un argument
eval set -- "$option"                                                 #ligne permettant de ...

## A REPRENDRE !!
##Chemin="$pwd"

while true ; do 
    
                                   #boucle while avec une condition toujours vrai pour vérifier les différents options notés par l'utilisateur
   case "$1" in                                     #case pour differentier les differents cas
                                                      #tips creer variable tri et initialiser en avl puis changer dans tab et abr et l'appeler dans le gcc ...
                                                      # 1 seul tri a choisir PAS PLUS
        -t)  argument="$2" 

             case "$argument" in  
                  1) echo "mode temperature 1"
                     tail -n+2 "$fichier" | cut -d';' -f1,11,12,13 > temp.txt 
                     awk -F ";" '( $2=="" ||$3=="" || $4=="" ) {next}{print $1" " $2 " " $3 " " $4}' temp.txt > tempo.txt ## commande permettant de supprimer toute les lignes ou des données sont manquantes sur au moins une colonne
                     sed -i 's/\;/ /g' tempo.txt        ## commande qui remplace les ';' par des espaces                                                        
                     if [ ! -e exec ] 
                     then 
                         make   
                     fi  
                     
                     ./exec   -t1 "$Tri"                ## (arguments données au C) <nom_fichier> <Tri> <mode>
                     if (( "$?" != O  )) 
                     then 
                     case "$?" in                                                          #pour voir les valeurs retour du C
                        2) echo "Problème avec le fichier d'entrée, veuillez vérifier le fichier envoyé, voir l'aide en tapant --help, si besoin"     
                        ;;

                        3) echo "Problème avec le fichier de sortie, une erreur sur la creation du fichier de sortie, voir l'aide en tapant --help, si besoin"
                        ;;

                        4) echo "Erreur interne détécté, codage par de mauvais codeur, revoir les codes"
                        ;;
                        
                        *) echo " "
                        ;;
                     esac    
                     fi     
                     gnuplot t.gnu
                     rm t.dat
                     rm *p.txt                           
                     shift 2;;  


                  2) echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option"       
                     shift 2;;


                  3) echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option"        
                     shift 2;;
                  *) echo "mode de la temperature incorrect, saisir un mode" 
                  ;;
             esac 
             shift 2;; 
        -p)  argument="$2" ;
             case "$argument" in 
                  1) echo "mode pression 1"
                     tail -n+2 "$fichier" | cut -d';' -f1,3,7,8 > temp1.txt 
                     awk -F ";" '( $2=="" || $3=="" || $4=="" ) {next}{print $1" " $2 " " $3 " " $4}' temp1.txt > tempo1.txt  ## commande permettant de supprimer toute les lignes ou des données sont manquantes sur au moins une colonne
                     sed -i 's/\;/ /g' tempo1.txt         ## commande qui remplace les ';' par des espaces
                     if [ ! -e exec ] 
                     then 
                         make   
                     fi  
                     ./exec -p1 "$Tri"                  #arguments du C : (option) (tri)
                     if (( "$?" != O  )) 
                     then 
                     case "$?" in                                                          #pour voir les valeurs retour du C
                        2) echo "Problème avec le fichier d'entrée, veuillez vérifier le fichier envoyé, voir l'aide en tapant --help, si besoin"     
                        ;;

                        3) echo "Problème avec le fichier de sortie, une erreur sur la creation du fichier de sortie, voir l'aide en tapant --help, si besoin"
                        ;;

                        4) echo "Erreur interne détécté, codage par de mauvais codeur, revoir les codes"
                        ;;
                        
                        *) echo " "
                        ;;
                     esac    
                     fi   
                     gnuplot p.gnu 
                     rm p.dat
                     rm *1.txt
                     shift 2;;
                  2) echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option" 
                     shift 2;;
                  3) echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option"
                    shift 2;;
                  *) echo "mode de la pression incorrect" ;;
             esac ;
             shift 2;;
        -d)   echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option"
              shift 2;;
        -f) shift 2;;
        -w) echo "vent" 
	        tail -n+2 "$fichier" | cut -d';' -f1,4,5,10 > temp2.txt 
            awk -F ";" '( $2=="" || $3=="" || $4=="" ) {next}{print $1" " $2 " " $3 " " $4}' temp2.txt > tempo2.txt
            sed -i 's/\;/ /g' tempo2.txt 
            sed -i 's/\,/ /g' tempo2.txt
            if [ ! -e exec ] 
            then 
                  make   
            fi  
            ./exec -w "$Tri" #-f <nom_fichier> #    #(arguments du C)               ##"$Tri"
            if (( "$?" != O  )) 
            then 
            case "$?" in                                                          #pour voir les valeurs retour du C
                2) echo "Problème avec le fichier d'entrée, veuillez vérifier le fichier envoyé, voir l'aide en tapant --help, si besoin"     
                ;;

                3) echo "Problème avec le fichier de sortie, une erreur sur la creation du fichier de sortie, voir l'aide en tapant --help, si besoin"
                ;;

                4) echo "Erreur interne détécté, codage par de mauvais codeur, revoir les codes"
                ;;
                        
                *) echo " "
                ;;
            esac    
            fi    
            gnuplot w.gnu
            rm w.dat
            rm *2.txt
            shift;;
            
        -h) echo "altitude" 
            tail -n+2 "$fichier" | cut -d';' -f1,14,10 > temp3.txt 
            awk -F ";" '( $2=="" || $3==""  ) {next}{print $1 " " $2 " " $3}' temp3.txt > tempo3.txt
            sed -i 's/\;/ /g' tempo3.txt 
            sed -i 's/\,/ /g' tempo3.txt 
            if [ ! -e exec ] 
            then 
                  make   
            fi  
            ./exec -h "$Tri"  #-f <nom_fichier> #    #(arguments du C)               ##"$Tri"
            if (( "$?" != O  )) 
            then 
            case "$?" in                                                          #pour voir les valeurs retour du C
                2) echo "Problème avec le fichier d'entrée, veuillez vérifier le fichier envoyé, voir l'aide en tapant --help, si besoin"     
                ;;

                3) echo "Problème avec le fichier de sortie, une erreur sur la creation du fichier de sortie, voir l'aide en tapant --help, si besoin"
                ;;

                4) echo "Erreur interne détécté, codage par de mauvais codeur, revoir les codes"
                ;;
                        
                *) echo " "
                ;;
            esac    
            fi    
            gnuplot h.gnu 
            rm h.dat
            rm *3.txt
            shift;;
        -m) echo "humidite" 
            tail -n+2 "$fichier" | cut -d';' -f1,6,10 > temp4.txt 
            awk -F ";" '( $2=="" || $3=="" ) {next}{print $1 " " $2 " " $3}' temp4.txt > tempo4.txt
            sed -i 's/\;/ /g' tempo4.txt  
            sed -i 's/\,/ /g' tempo4.txt
            if [ ! -e exec ] 
            then 
                  make   
            fi  
            ./exec -m  "$Tri" #-f <nom_fichier> #    #(arguments du C)               ##"$Tri"
             if (( "$?" != O  )) 
            then 
            case "$?" in                                                          #pour voir les valeurs retour du C
                2) echo "Problème avec le fichier d'entrée, veuillez vérifier le fichier envoyé, voir l'aide en tapant --help, si besoin"     
                ;;

                3) echo "Problème avec le fichier de sortie, une erreur sur la creation du fichier de sortie, voir l'aide en tapant --help, si besoin"
                ;;

                4) echo "Erreur interne détécté, codage par de mauvais codeur, revoir les codes"
                ;;
                        
                *) echo " "
                ;;
            esac    
            fi    
            gnuplot m.gnu 
            rm m.dat
            rm *4.txt
            shift;;
    --help) fonctionaide
            shift;;

        -F) echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option" ;               #--LIEUX il va falloir preciser qu'une seule est a choisir PAS PLUS
            shift;;
        -G) echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option" ;
            shift;;
        -S) echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option" ;
            shift;;
        -A) echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option" ;
            shift;;
        -O) echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option" ;
            shift;;
        -Q) echo "Cette option n'est pas encore disponible sur cette version, veuillez patienter un petiti peu, la version 2.10.23 arrive très prochainement avec cette option";
            shift;;
        --) 
            shift;
            break;;
    esac 
done 
exit 1