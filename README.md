# projPolytechInfoSpaceInvaders


# **Space Invaders Simplifié**

## **Introduction**
Space Invaders Simplifié est une version minimaliste du célèbre jeu d'arcade *Space Invaders*. Ce projet est développé en C à l'aide de la bibliothèque SDL2. L'objectif est de recréer l'expérience du jeu original avec des mécaniques simplifiées tout en favorisant l'apprentissage de la programmation graphique.

---

## **Fonctionnalités**
### **Gameplay**
- **Joueur :**
  - Déplacez un vaisseau sur l'axe horizontal (flèches gauche/droite).
  - Tirez sur les ennemis en appuyant sur *espace*.

- **Ennemis :**
  - Une ou plusieurs rangées d’ennemis qui se déplacent horizontalement et descendent progressivement.
  - Si un ennemi atteint le bas de l’écran, la partie est terminée (*Game Over*).

- **Projectiles :**
  - Les tirs du joueur détruisent les ennemis.
  - Les ennemis peuvent tirer ; leurs projectiles diminuent les points de vie du joueur.

- **Conditions de victoire/défaite :**
  - Victoire : Tous les ennemis sont détruits.
  - Défaite : Points de vie épuisés ou un ennemi atteint le bas de l’écran.

### **Interface utilisateur**
- **Écran de démarrage :**
  - Bouton *Play* pour commencer la partie.
  - Titre "Space Invaders".

- **Écran de jeu :**
  - Affichage du score et des vies restantes.

- **Écran de fin :**
  - Message *Game Over* ou *Victoire* avec option pour rejouer ou quitter.

### **Graphismes et audio**
- **Graphismes :** Sprites simples pour le vaisseau, les ennemis, et les projectiles.
- **Audio :** Effets sonores pour les tirs, explosions, et musiques de fond.

---

## **Configuration technique**
### **Langage et bibliothèques**
- **Langage :** C
- **Bibliothèques :**
  - SDL2 : Gestion graphique et des événements.
  - SDL2_ttf : Affichage du texte.
  - SDL2_mixer *(optionnel)* : Gestion des sons et musiques.

### **Structure des dossiers**

