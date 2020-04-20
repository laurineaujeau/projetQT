//
// Created by lauri on 19/04/2020.
//
mainWindow::mainWindow(QWidget *parent): QMainWindow(parent)
{

    this->mainScene = new MainScene();

    QVector<PlaneItem*> planes = this->mainScene->getPlanes();

    for(PlaneItem* plane : planes){

        QGraphicsView* planeView = new QGraphicsView();
        planeView->setScene(mainScene);
        //planeView->scale(0.5, 0.5);
        planeView->resize(300, 300);
        planeView->setWindowTitle(plane->getDescription());
        planeView->show();

    }

    mainView = new QGraphicsView();
    mainView->setScene(mainScene);
    mainView->scale(1, 1);

    this->setCentralWidget(mainView);
    this->setWindowTitle("Main view");
    this->resize(1000, 600);

    //QKeyEvent* event;
    //mainScene->keyPressEvent(event);
}

MainScene::MainScene(){

    this->background.load("foret.jpg");
    this->setSceneRect(0, 0, this->background.width(), this->background.height());
    //cout<<getW()<<endl;
    //cout<<getW()<<endl;

    /*this->timer = new QTimer(this);
    this->timer->start(30);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));*/

    this->planeItems.push_back(new PlaneItem("Personnage", "personnage.png"));
    int nbPlaneItems = this->planeItems.size();

    for (unsigned int i = 0; i < nbPlaneItems; i++) {

        PlaneItem* planeItem = this->planeItems[i];

        this->addItem(planeItem);

        // all the planeItems on the right side of the scene
        planeItem->setPos(this->width()-810, this->height()/2.1 );

    }



}
void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}
void MainScene::update() {

    int nbPlaneItems = planeItems.size();

    for (unsigned int i = 0; i < nbPlaneItems; i++) {

        PlaneItem* planeItem = this->planeItems[i];

        planeItem->move();

        // view update
        QGraphicsView * view = this->views().at(i);
        view->centerOn(planeItem);
    }
}
