Fonctionnement montagne russe


Le main contient :

-Les Points de la courbes

-Le Point Central du chariot

-Un objet Chariot

-Un objet Courbe

-Un objet Rail




À l’initialisation : 

-On lance notre objet courbe qui vas renvoyer un tableau de points de la courbe, ça va définir aussi la trajectoire de notre chariot

-On place un point quelque part sur la courbe (mais un peu au dessus de la courbe), ça va définir le point central du chariot et où il doit translate


À l’affichage : 

-L’objet chariot vas construire le chariot et être translate sur le point central

-L’objet Rail vas récup les points de la courbe et dessiner des rails dessus


À l’animation : 

-Le point central se déplace sur la courbe (ce qui définit les paramètre du glTranslatef)

	-Il faudras aussi déterminer la bonne rotation du chariot pour qu’il soit parallèle aux rails (possible avec la tangente de la courbe ?)
   
-Définir le temps de réaffichage de la prochaine frame en fonction de comment le chariot est soumis à la gravité


Nos objets : 

-Chariot : Construit le chariot avec la méthode construire(), penser à l’écart entre les roues avec l’objet Rail (Disons 1 d'écart).

-Courbe : S’initialise avec des Points de contrôle déclaré dans son constructeur et construit la courbe du circuit et renvoie les points de la courbe. Une méthode qui renvoie la normale de la tangente de la courbe à un moment t ? (Peut être utile pour placer le rail dessus mais y’a surement une meilleure méthode)

-Rail : Récupère les points de la courbe et construit un rail en parcourant le tableau des courbes 2 par 2 pour au mieux relier les rails. 



Répartition : 

-Construction Chariot + Rail

-Animation avec gravité

-Construction courbe (renvoie tableau points qui construisent la courbe) 

-Orientation du chariot en fonction de la courbe
