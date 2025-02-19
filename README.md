# Jeu d'Infiltration en C  

## Description  
Ce projet est un jeu d'infiltration développé en langage C. Le joueur incarne un aventurier dont l'objectif est de récupérer toutes les reliques cachées dans une salle surveillée par des gardiens. Grâce à des compétences magiques, le joueur peut se rendre invisible ou sprinter pour échapper aux ennemis.  

## Règles du Jeu  
- Le joueur commence à l'entrée de la salle (en haut à gauche).  
- Il doit collecter toutes les reliques sans se faire repérer par les gardiens.  
- Lorsqu'un gardien remarque une relique volée, il entre en mode "panique" et élargit son champ de vision.  
- Le joueur peut utiliser du mana pour :  
  - Se rendre invisible (Barre espace).  
  - Sprint (Touche Shift).  
- Une fois toutes les reliques collectées, le joueur doit revenir à l'entrée pour gagner la partie.  

## Commandes  
| Action                | Touche |
|----------------------|--------|
| Se déplacer         | Flèches directionnelles ou ZQSD |
| Sprint             | Shift (Gauche/Droite) |
| Invisibilité       | Barre espace |

## Installation & Compilation  
### Prérequis  
- Un compilateur C (GCC recommandé)  
- La bibliothèque **MLV** pour l'affichage  


## Installation et Compilation  
1. Assurez-vous d’avoir **GCC** et **Make** installés sur votre système.  
2. Compilez le jeu avec :  
   ```sh
   make
   ```
3. Lancez le jeu :  
   ```sh
   ./stealth
   ```

## Bugs & Problèmes  
- Les collisions dans les coins sont imprécises à grande vitesse.  
- Le mana ne se consomme pas si le joueur reste immobile tout en étant invisible.  

## Structure du Code  
Le projet est organisé en plusieurs modules :  

| Module         | Description |
|---------------|------------|
| `geometry.c` | Gestion des distances et positions. |
| `random.c` | Génération de nombres aléatoires. |
| `entity.c` | Gestion des entités (joueur et gardiens). |
| `terrain.c` | Génération du terrain et positionnement des objets. |
| `game.c` | Mécaniques de jeu et interactions. |
| `leaderboard.c` | Gestion du classement des joueurs. |
| `display.c` | Interface graphique et affichage avec **MLV**. |

## Ressources et Liens  
- Page du projet : [forge-etud.u-pem.fr](https://forge-etud.u-pem.fr/projects/stealth_crozat_nguyen)  
