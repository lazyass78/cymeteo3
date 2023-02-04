# cymeteo3

Ce script permet de traiter au choix un ou plusieurs types de données du fichier renseigner comme la température (option associée -t1), la pression atmosphérique (option associée -p1), le vent (option associée -w), l’humidité (option associée -m), ou l’altitude de chaque station (option associée -h), voici un bref guide d’utilisation pour prendre en main l’application

Premièrement ne pas hésitez à aller voir le help si des commandes n’ont pas été comprise, ou si vous ne vous souvenez plus de comment les utiliser.

Tout d’abord, pour lancer le programme, une fois dans le dossier contenant tous les fichiers nécessaires à l’utilisation de l’application, il vous faudra dans le terminal ecrire la commande ./projet.sh pour pouvoir executer le programme. 

Cependant, cette commande ne doit pas s’écrire seul il faut obligatoirement saisir l’option -f suivi du fichier de données se trouvant dans le repertoire. 
L’option -f  et son argument [FICHIER] :

   -f <nom_fichier> 		(f)ichier d’entrée : Cette option est obligatoire. Le nom du fichier d’entrée doit être renseigné pour que le script puisse acquérir toutes les données.

En plus, au moins une de ces options doit être choisie pour que le script fonctionne. Il est possible d’en activer plusieurs, mais certaones combinaison ne fonctionnent pas comme -t1 et p1 en meme temps.

Les arguments et options du script [TYPE de données] :

  -t1 				        (t)emperatures : Produit en sortie un diagramme de type barres d’erreur avec en abscisse l’identifiant de la station, et en ordonnée le minimum, maximum et la moyenne des températures 

  -p1 			        	(p)ressions atmosphériques : Produit en sortie un diagramme de type barres d’erreur avec en abscisse l’identifiant de la station, et en ordonnée le minimum, maximum et la moyenne des pressions 

  -w			          	vent ( (w)ind ) : Produit en sortie un diagramme de type vecteurs (flèches orientées) avec l’abscisse correspondant à la longitude (axe Ouest-Est) et l’ordonnée correspondant à la latitude (axe Sud-Nord). 

  -h				          altitude ( (h)eight) : Produit en sortie un diagramme de type carte interpolée et colorée de l’altitude avec l’abscisse correspondant à la longitude (axe Ouest-Est) et l’ordonnée correspondant à la latitude (axe Sud-Nord) de chaque station

  -m			          	humidité ( (m)oisture ) : Produit en sortie un diagramme de type carte interpolée et colorée de l’humidité avec l’abscisse correspondant à la longitude (axe Ouest-Est) et l’ordonnée correspondant à la latitude (axe Nord-Sud) de chaque station


Les arguments et options du script [TRIS] :

Il est possible d’imposer le mode de tri des données par l’aide d’une structure d’arbre binaire,
ABR ou AVL. Ces options de tris sont exclusives entre elles : une seule peut être activée à la fois. Si aucune option de tri n’est activée, par défaut le tri se fera à l’aide d’un AVL.

--abr : 					tri effectué l’aide d’une structure de type ABR
--avl : 					tri effectué à l’aide d’une structure de type AVL


Exemples de commande :

> ./projet.sh -t1 -w -f meteo_filtered_data_v1.csv

> ./projet.sh -p1 --abr -f meteo_filtered_data_v1.csv
