# PROJET QT
## Description
Ce projet a été codé en C++ et QT. Les objectifs étaient :
* Créer un jeu d'objet qui saute des obstacles sous forme de bars ou de vides en utilisant les touches du clavier.
* Le jeu doit être composé d'au moins deux fenêtres, la première est une vue complète sur le plateau de jeu et la seconde est une petite vue centrée sur l'obejt en mouvement.
* L'objet qui se déplace doit atteindre une ligne d'arrivée et le meilleur temps pour y parvenir doit être mémorisé.
* Le joueur doit pouvoir recommencer une partie ou quitter complètement le jeu lorsqu'il a franchi la ligne d'arrivée.

## Installation
* Etape 1 : Lancer Debian.
* Etape 2 : Ouvrir le dossier du projet sur Clion.
* Etape 3 : Cliquer sur Run, Edit Configuration et remplir le champ Working directory par " ..\img ".
* Etape 4 : Toujours dans Edit configuration, cliquer sur le champ de Environment variables puis sur  + , Remplir le champ Name par DISPLAY et le champ Value par :0.0 Enfin cliquer sur Appliquer.
* Etape 5 : Lancer Xming.

## Comment jouer
Pour lancer le jeu cliquer sur Run puis Run 'projetQT'.
Remplir le nom du joueur est obligatoire pour pouvoir continuer.
Utiliser les flêches pour se déplacer et la barre espace pour sauter.

## Fonctionnement du programme
* Fichier main.cpp : permet le lancement du jeu
* Fichier mainWindow.cpp : permet de créer les deux fenêtres principales du jeu et de les afficher
* Fichier MainScene.cpp : permet le remplissage des fenêtres et l'actualisation du jeu
* Fichier AvatarItem.cpp : permet la création et le déplacement de l'objet qui sera manipulé par le joueur
* Fichier RectItem.cpp : permet la création des rectangles utilisés pour les collisions

## Sources utilisées
* Forum "Aide C++/Qt" (ISEN Rennes)
* Documention officielle QT
* OpenClassroom.com

## Auteur
AUJEAU Laurine