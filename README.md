# SpaceBattle (Space Invaders-like)

![til](/projet/ressources/spacebattle.gif)

Petit jeu 2D inspiré de Space Invaders, développé en C avec la bibliothèque SDL2 en binôme dans le cadre d'un projet étudiant de première année d'informatique.

## 📦 Prérequis

Pour compiler et exécuter le projet, il faut :

- Un compilateur C (gcc recommandé)
- Make
- SDL2
- SDL2_ttf

### 🖱 Installation des dépendances (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install build-essential make \
                 libsdl2-dev libsdl2-ttf-dev
```

### 🎮 Compilation

À la racine du projet :
- Dans un terminal : make
- L'exécutable créé se lance avec ./spacebattle
- Nettoyage : make clear
