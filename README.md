# CoconutpartY 
Pour compiler notre programme, vous pouvez taper la commande "make" depuis le terminal, grâce au makefile. Sans le makefile, il faut compiler chaque .c en .o en utilisant la commande gcc -c exemple1.c .
Il faut faire ca pour chaque .c puis faire un gcc -o exec exemple1.c exemple2.c etc... avec exec le nom de l'executable.

Pour executer le programme, il suffit seulement de taper la commande ./exec dans le terminal.

VARIANTES : 
- La partie se termine lorsque le roi des singes n’a plus de points de vie. Chaque crabe qui atteint la couronne fait perdre 1 point de vie. Le nombre de points de vie est fixé aléatoirement en début de partie.
- Les dimensions initiales de la carte sont des valeurs générées aléatoirement.
- La case de départ est située à droite, et la couronne à gauche de la carte.


Le but du jeu est de défendre la couronne de l'invasion de crabes, en plaçant des singes qui vont attaquer tous les envahisseurs. Le seul moyen de perdre est qu'un assez grand nombre de crabes atteignent la couronne, chaque crabe qui arrive a la couronne fera baisser les points de vie de la couronne de 1 jusqu'à ce qu'elle arrive à 0.


En lançant l'éxecutable, il faut d'abord selectionner ce que l'on veut faire :
1 pour jouer, 2 pour reprendre une ancienne partie, 3 pour quitter.
Une fois que vous avez choisi de jouer, il faut commencer par entrer les points de vie de la couronne.
Une fois cela fait, la carte va se generer aleatoirement avec un # qui est le départ des crabes, des lettres qui correspondent aux emplacements prédefinis pour les singes, des @ qui correspondent aux singes, des C qui correspondent aux crabes, une X qui est la couronne et des . qui sont le chemin que les crabes doivent emprunter.
Vous devez commencer par placer un singe et la première vague se lance. La vague se termine lorsqu'il n'y a plus de crabe sur le terrain (ils auront soit atteint la couronne, soit ils se seront fait tuer par les singes).
Au debut de chaque vague, vous pourrez placer un singe sur un emplacement prédefinit et reprendre le jeu ou sauvegarder et quitter.