# projPolytechInfoSpaceInvaders


Space Invaders Projet info Polytech


Le but de ce projet est de développer une version simplifiée du Space Invaders en utilisant la
bibliothèque SDL2 en C.

1 Gameplay
    1. Joueur :
        o Le joueur contrôle un vaisseau situé en bas de l'écran.
        o Déplacements horizontaux (gauche/droite) avec les touches du clavier
        o Tirs avec une touche
    2. Ennemis :
        o Une rangée d’ennemis en haut de l’écran.
        o Les ennemis se déplacent horizontalement et descendent progressivement.
        o Si un ennemi atteint le bas de l’écran, le jeu est terminé (Game Over).
    3. Projectiles :
        o Les tirs du joueur détruisent les ennemis au contact.
        o Les ennemis peuvent également tirer (projective en bas vers le jouer), et toucher le
        joueur réduit sa vie.
    4. Conditions de victoire/défaite :
        o Le joueur gagne en détruisant tous les ennemis.
        o Le joueur perd si tous ses points de vie sont épuisés ou si un ennemi atteint le bas.
    2 Interface utilisateur
        • Écran de démarrage :
            o Un bouton Play pour commencer la partie.
            o Affichage du titre "Space Invaders".
        • Écran de jeu :
            o Affichage des points de vie et du score.
    • Écran de fin :
        o Un message Game Over ou Victoire avec une option pour rejouer ou quitter.
2. Contraintes techniques
    2.1 Langage et bibliothèques
        • Langage : C
        • Bibliothèques utilisées :
            o SDL2 : Gestion graphique et des événements.
            o SDL2_ttf : Affichage du texte.
    2.2 Plateforme
        • Systèmes d’exploitation ciblés :
            o Windows (prioritaire)
            o MAC OS à voir si j’arrive à le faire fonctionner dessus
    2.3 Performances
        • Maintenir un framerate constant à 25 FPS.
        • Optimisation pour éviter les ralentissements.
3. Développement et architecture
    3.1 Structure du projet
      1. Fichiers principaux :
          o main.c : Point d'entrée du programme.
          o player.c / player.h : Gestion du joueur (déplacement, tirs).
          o enemy.c / enemy.h : Gestion des ennemis (déplacement, comportement).
          o projectile.c / projectile.h : Gestion des tirs.
          o ui.c / ui.h : Gestion des interfaces utilisateur (menus, affichages).
          o game.c / game.h : Boucle principale du jeu et logique.
2. Arborescence des dossiers :
    SpaceInvaders/
    ── bin/ # Fichiers compilés
    ── fonts/ # Polices utilisées
    ── lib/ # Bibliothèques SDL2
    ── src/ # Code source
    ── assets/ # Graphismes
    ── README.md # description cahier de charge
3.2 Plan de développement
    1. Étape 1 : Préparation de l’environnement
        o Installer et configurer SDL2 et SDL2_ttf.
        o Créer un projet C structuré avec un fichier Makefile.
    2. Étape 2 : Interfaces utilisateur
        o Développer un écran de démarrage fonctionnel avec un bouton Play.
        o Ajouter un affichage pour le score et les vies dans l’écran de jeu.
    3. Étape 3 : Gameplay de base
        o Implémenter les déplacements du joueur et ses tirs.
        o Ajouter une rangée simple d’ennemis et leur déplacement.
    4. Étape 4 : Interactions joueur/ennemis
        o Détecter les collisions entre tirs et ennemis.
        o Ajouter des tirs ennemis et des collisions avec le joueur.
    5. Étape 5 : Conditions de victoire/défaite
        o Implémenter la logique de fin de partie.
        o Ajouter un écran de fin avec options.
    6. Étape 6 : Améliorations
        o Ajouter plusieurs niveaux.
        o Implémenter des ennemis avec comportements variés.
