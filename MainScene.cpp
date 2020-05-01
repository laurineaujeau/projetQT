//
// Created by lauri on 17/04/2020.
//

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QLabel>
#include <QRect>
#include <QMessageBox>
#include <iostream>
#include <QKeyEvent>
#include <QObject>
#include <QApplication>
#include <QString>
#include "MainScene.h"
using namespace std;
MainScene::MainScene(){
    // menu
    this->input = new QInputDialog();
    bool ok= false;
    bool cancel= false;
    //creation d'un widget input avec comme titre de widget "Bienvenue"
    // la phrase au dessus de l'input est "Pseudo"
    //
    //
    //&ok permet de vérifier si le joueur a appuyer sur le bouton ok
    pseudo = this->input->getText(parent,"Bienvenue !", "Pseudo:",QLineEdit::Normal,QString(),&ok); //https://openclassrooms.com/fr/courses/1894236-programmez-avec-le-langage-c/1899971-apprenez-a-utiliser-les-boites-de-dialogue-usuelles

    //le joueur est obligé de remplir l'input pour commencer la partie
    while(ok && pseudo.isEmpty()){
        this->message->critical(parent,"Bienvenue !", "Veulliez remplir le champ");
        pseudo = this->input->getText(parent,"Bienvenue !", "Pseudo:",QLineEdit::Normal,QString(),&ok);
    }

    //le joueur a rempli son pseudo et a a^pputer sur ok = le jeu commence
    if (ok && !pseudo.isEmpty())
    {
        this->message->information(parent, "Bienvenue !", "Bonjour " + pseudo + ", le but du jeu est d'atteindre l'autre bout de la scene, utilisez les flêches pour vous déplacer et la barre espace pour sauter. Bonne Chance !");
        this->background.load("foret.jpg");
        this->setSceneRect(0, 0, this->background.width(), this->background.height());

        this->item = new AvatarItem("Personnage", "personnage.png");
        this->item->setPos(this->width()-810, this->height()/2.1 );
        this->addItem(item);
        isActive=false;
        partie();
    }
    else{
        //delete input;
        QApplication::quit();
        //connect (0, 0, qApp , SLOT (quit()));
    }

}
void MainScene::partie(){
    //en cas de "Rejouer", on supprime la boite de dialogue on replace l'avatar présent sur scene
    /*if(boite->isEnabled()){
        delete boite;
    }*/
    if(isActive){
        isActive=false;
        delete boite;
    }
    //on supprime l'avatar existant et on le replace à la postion initiale
    delete item;

    this->item = new AvatarItem("Personnage", "personnage.png");
    this->item->setPos(this->width()-810, this->height()/2.1 );
    this->addItem(item);

    //timer permettant l'actualisation du programme toutes les 30 ms
    this->timer = new QTimer(this);
    this->timer->start(30);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // on creer et on place des rectangles transparents qui serviront pour les collisions
    this->rectangles.push_back(new RectItem(0,434,233,74)); // premier sol
    this->rectangles.push_back(new RectItem(350,434,467,74));// deuxieme sol
    this->rectangles.push_back(new RectItem(515,355,112,78));//buisson
    this->rectangles.push_back(new RectItem(0,0,1,506)); //cadre gauche
    for(RectItem* rectangle : rectangles){
        this->addItem(rectangle);
        rectangle->setOpacity(0);
    }

    //creation de rectangles a part car leur collisions provoque une réaction particulière
    trou = new RectItem(270,417,48,89);
    this->addItem(trou);
    trou->setOpacity(0);
    arrivee = new RectItem(800,261,13,149);
    this->addItem(arrivee);
    arrivee->setOpacity(0);
    finTrou = new RectItem(234,506,111,1);
    this->addItem(finTrou);
    finTrou->setOpacity(0);
    hauteurMax = new RectItem(0,10,813,1);
    this->addItem(hauteurMax);
    hauteurMax->setOpacity(0);
    LimiteMax = new RectItem(808,0,1,506);
    this->addItem(LimiteMax);
    LimiteMax->setOpacity(0);

    //création d'une variable temps qui permettera de recuperer le temps écoulé à la fin de la partie
    this->temps = new QTime();
    this->temps->start();
}
void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void MainScene::update() {
    // Mise a jour de la vue centrée sur l'avatar
    this-> view = this->views().at(getItemID());
    view->centerOn(this->item);

    //Collisions
    for(RectItem* rectangle : rectangles){
        if (this->item->collidesWithItem(rectangle)){
            // déplacement dans le sens contraire au précédent afin d'éviter la collision constante
            if (getEtatPrecedent()==1){
                this->item->move("droite");
            }
            else if (getEtatPrecedent()==2){
                this->item->move("gauche");
            }
            else if (getEtatPrecedent()==3 || getEtatPrecedent()==4){
                this->item->move("haut+");
            }
        }
    }

    if (this->item->collidesWithItem(trou)){
        //provoque la chute de l'avatar
        this->item->move("tomber");
    }
    if (this->item->collidesWithItem(finTrou)){
        //provoque l'arret du jeu lorsque le joueur est au fond du trou
        setEtatAvatar(0);
        disconnect(timer, 0, 0, 0);

        //créer une boite de dialogue avec un commentaire
        boite = new QWidget();
        QLabel* text =new QLabel();
        text->setText("Perdu !");
        text->setMargin(15);
        text->setAlignment(Qt::AlignCenter);
        //Creation des boutons rejouer et quitter
        bouton1 = new QPushButton("Rejouer");
        bouton2 = new QPushButton("Quitter");

        //ajout des objets dans layout qui les positionne
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(text);
        layout->addWidget(bouton1);
        layout->addWidget(bouton2);

        // ajout de layout dans la popup et l'affiche
        boite->setLayout(layout);
        boite->show();
        isActive=true;
        //connexion entre le bouton et la fonction qui permet d'executer le choix
        connect (bouton1, SIGNAL ( clicked ()), this , SLOT (partie()));
        connect (bouton2, SIGNAL ( clicked ()), qApp , SLOT (quit()));

    }
    if (this->item->collidesWithItem(arrivee)){
        setEtatAvatar(0);
        //this->item->move("tomber"); // c'est le disconnect qui fait arreter le perso

        //provoque l'arret du jeu
        tempsFinal(); //Calcul le score du joueur et l'affiche
    }
    if (this->item->collidesWithItem(LimiteMax)){
        //permet à l'avatar de ne pas quitter la scene par la droite et le fait glisser jusqu'au sol
        setEtatAvatar(0);
        this->item->move("tomber");
        //ATTENTION, la deconnexion du timer à l'arrivée annule cet effet
    }
    if (this->item->collidesWithItem(hauteurMax)){
        //permet à l'avatar de ne pas quitter la scene par le haut et le fait tomber jusqu'au sol en fonction de son action précédente = saut droit ou en courbe
        //pour cela on est obligé de l'immobiliser sinon il traverse la collision
        //son état précédent devient donc l'immobilité
        //il faut donc enregistrer l'état de l'avatar avant son immobilité
        if (getEtatPrecedent()==4){
            setEtatPrecedent2(4);
        }
        else{
            setEtatPrecedent2(3);
        }
        setEtatAvatar(0);
        isSaut= false;
        if (getEtatPrecedent2()==4){
            setEtatAvatar(4);
        }
        if (getEtatPrecedent2()==3){
            setEtatAvatar(3);
        }
    }


    //etat update + enregistrement de l'état précédent
    if (getEtatAvatar()==0){
        this->item->move("stop");
        setEtatPrecedent(0);
    }
    else if (getEtatAvatar()==1){
        this->item->move("gauche");
        setEtatPrecedent(1);
    }
    else if (getEtatAvatar()==2){
        this->item->move("droite");
        setEtatPrecedent(2);
    }
    else if (getEtatAvatar()==3){
        setEtatPrecedent(3);
    }
    else if (getEtatAvatar()==4){
        setEtatPrecedent(4);

    }

    //monter l'avater en cas de saut
    if (isSaut){
        if (getEtatAvatar()==3){
            this->item->move("haut");
        }
        else if (getEtatAvatar()==4){
            this->item->move("sauter");

        }
    }
    //descendre l'avatar en cas de saut
    else{
        //2 problemes avec les collisions du sol = 1. l'avatar traverse le sol 2. crise d'epilesie de l'avatar avec l'entrée en contact de la collision
        //cout<<this->item->pos().x()<<endl;
        //La seule solution trouvé pour l'instant = définition d'une hauteur minimale en fonction de la région ou se trouve l'avatar
        if(this->item->pos().x()>=0 && this->item->pos().x()<=430) {
            //région avant le buisson
            //cout<<"if1"<<endl;
            if(this->item->pos().y()<=235){
                if (getEtatPrecedent()==4){
                    this->item->move("bas");
                }
                else{
                    this->item->move("tomber");
                }
            }
        }
        if(this->item->pos().x()>=600 && this->item->pos().x()<=813) {
            //région du buisson
            //cout<<"if2"<<endl;
            if(this->item->pos().y()<=235){
                if (getEtatPrecedent()==4){
                    this->item->move("bas");
                }
                else{
                    this->item->move("tomber");
                }
            }
        }
        if(this->item->pos().x()>430 && this->item->pos().x()<600) {
            //région apres le buisson
            //cout<<"if3"<<endl;
            if(this->item->pos().y()<=160){
                if (getEtatPrecedent()==4){
                    this->item->move("bas");
                }
                else{
                    this->item->move("tomber");
                }
            }
        }
    }
}
void MainScene::tempsFinal(){
    this->chrono = temps->elapsed(); // recupere le temps ecoulé depuis l'appel de start
   // AfficherChrono();
    disconnect(timer, 0, 0, 0);
    boite = new QWidget();  // popup qui affiche le score et les boutons
    QLabel* text =new QLabel(); // label pour le commentaire
    text->setText("Gagné !");
    text->setMargin(10);
    text->setAlignment(Qt::AlignCenter);

    QLabel* texte2 =new QLabel(); //label pour le score

    // calculs des temps
    int heure = chrono/(60*60*1000);
    int minute = chrono/(60*1000) - heure*60;
    int seconde = chrono/(1000) - minute*60;
    int milliseconde = chrono - seconde*1000;

    //conversion int -> QString = permet la concaténation et l'affichage avec setText
    const QString score = "Votre score est ";
    const QString sheure = QString :: number (heure);
    const QString smin = QString :: number (minute);
    const QString sseconde = QString :: number (seconde);
    const QString smilisec = QString :: number (milliseconde);

    // concaténation de la chaine en fonction du temps obtenu
    QString chaine="";
    if(heure>0){
        chaine = score +sheure+"h "+smin+"m "+sseconde+","+smilisec+"s";
    }
    else if (minute>0){
        chaine = score +smin+"m "+sseconde+","+smilisec+"s";
    }
    else if (milliseconde<100){
        chaine = score +sseconde+",0"+smilisec+"s";
    }
    else{
        chaine = score +sseconde+","+smilisec+"s";
    }
    texte2->setText(chaine);
    texte2->setMargin(10);
    texte2->setAlignment(Qt::AlignCenter);

    //enregistrement du meilleur score
    QFile fichier("record.txt");
    QLabel* texte3 =new QLabel(); //label pour le record
    if(fichier.open(QIODevice::ReadOnly)){ //j'ouvre le fichier en lecture seule pour comparer les scores
        int ligne=0;
        int vintchrono=0;
        QTextStream flux(&fichier);
        // le flux permet de lire le fichier en entier ligne pas ligne
        while(!flux.atEnd()){
            if (ligne==0){
                // la première ligne correspond au pseudo du joueur qui a le record
                QString vainqueur=fichier.readLine();
            }
            if (ligne==1){
                //le record
                QString vchrono=fichier.readLine();
                vintchrono=vchrono.toInt();
            }
            ligne++;
        }

        fichier.close();
        //comparaison des temps

        if(vintchrono<=chrono){// si le joueur n'a pas réussi a pas le record
            //  // calculs des temps
            int vheure = vintchrono/(60*60*1000);
            int vminute = vintchrono/(60*1000) - vheure*60;
            int vseconde = vintchrono/(1000) - vminute*60;
            int vmilliseconde = vintchrono - vseconde*1000;
            //conversion int -> QString = permet la concaténation et l'affichage avec setText
            const QString svheure = QString :: number (vheure);
            const QString svmin = QString :: number (vminute);
            const QString svseconde = QString :: number (vseconde);
            const QString svmilisec = QString :: number (vmilliseconde);


            // concaténation de la chaine en fonction du temps obtenu
            const QString vscore = "Le record est ";
            QString vchaine="";
            if(vheure>0){
                vchaine = vscore +svheure+"h "+svmin+"m "+svseconde+","+svmilisec+"s";
            }
            else if (vminute>0){
                vchaine = vscore +svmin+"m "+svseconde+","+svmilisec+"s";
            }
            else if (vmilliseconde<100){
                vchaine = vscore +svseconde+",0"+svmilisec+"s";
            }
            else{
                vchaine = vscore +svseconde+","+svmilisec+"s";
            }
            texte3->setText(vchaine);
            texte3->setMargin(10);
            texte3->setAlignment(Qt::AlignCenter);
        }
        else{ // si le joueur a réussi a battre le record
            QString vchaine=" Vous avez battu le record !";
            texte3->setText(vchaine);
            texte3->setMargin(10);
            texte3->setAlignment(Qt::AlignCenter);
            // Réecriture du fichier = enregistrement du nouveau record
            if(fichier.open(QIODevice::WriteOnly)){
                QTextStream flux(&fichier);
                const QString texte = this->pseudo+"\n"+QString :: number (chrono);
                flux << texte;
                fichier.close();
            }
        }


    }
    else {
        cout<<"Impossible d'ouvrir le fichier !"<<endl;
    }

    //Creation des boutons rejouer et quitter
    bouton1 = new QPushButton("Rejouer");
    bouton2 = new QPushButton("Quitter");

    //ajout des objets dans layout qui les positionne
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(text);
    layout->addWidget(texte2);
    layout->addWidget(texte3);
    layout->addWidget(bouton1);
    layout->addWidget(bouton2);

    // ajout de layout dans la popup et l'affiche
    boite->setLayout(layout);
    boite->show();
    isActive=true;
    //connexion entre le bouton et la fonction qui permet d'executer le choix
    connect (bouton1, SIGNAL ( clicked ()), this , SLOT (partie()));
    connect (bouton2, SIGNAL ( clicked ()), qApp , SLOT (quit()));
}

void MainScene::keyPressEvent(QKeyEvent * event){
    if (event->isAutoRepeat()){
        return;
    }
    //Déplacement  vers la gauche
    if(event->key() == Qt::Key_Right) {
        setEtatAvatar(1);
    }
    //Déplacement vers la droite
    if(event->key() == Qt::Key_Left) {
        setEtatAvatar(2);
    }
    //Déplacement vers le haut
    if(event->key() == Qt::Key_Up) {
        setEtatAvatar(3);
        isSaut=true;
    }
    //sauter
    if(event->key() == Qt::Key_Space) {
        setEtatAvatar(4);
        isSaut=true;
    }
}

void MainScene::keyReleaseEvent(QKeyEvent * event){
    //Permet d'éviter les déplacements sacadés
    if (event->isAutoRepeat()){
        return;
    }
    //si l'avatar se déplace a gauche/droite il s'arrete à la levée de la touche clavier
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        setEtatAvatar(0);
    }
    //si l'avatar se déplace vers le haut il tombe à la levée de la touche clavier
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Space ) {
        isSaut =false;
    }
}

void MainScene::quit(){
    delete item;
    delete timer;
    delete boite;
    delete view;
    //MainScene::~MainScene();
    //QGraphicsScene::~QGraphicsScene();
   // QGraphicsView::~QGraphicsView();
    //QApplication::~QApplication());
    //delete background;
    //return -1; seg fault apres avoir fermé la page
}
//virtual MainScene::~MainScene(){}