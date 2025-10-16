# JEU DE LA VIE

### Le jeu de la vie permet de décrire l'évolution de cellules dans un intervalle de temps discret.

## Règles
Ce jeu comprend deux règles :
- Une cellule morte ayant exactement trois voisines vivantes devient vivante.
- Une cellule vivante ayant deux ou trois voisines vivantes reste vivante, sinon elle meurt.

## Fonctionnement :
- En entrée, le jeu consomme un fichier comprenant une première ligne spécifiant la taille de la grille. Le reste du fichier est la matrice de booléens représentant l'état initial, vivant (1) ou mort (0) de chaque cellule.
- Pendant le jeu, à chaque itération, l'état des cellules est mis à jour suivant les règles précédentes.
- Le programme retourne finalement un fichier avec le résultat de la dernière itération.