#include "mainwindow.h"
#include <QRandomGenerator>
#include "agente.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //labirinto = new Labirinto(this, 3);

    this->resize(500,500);
    view = new QGraphicsView(this);
    cena = new QGraphicsScene();

    view->setScene(cena);

    view->resize(500,500);

    desenharCena();

}

MainWindow::~MainWindow()
{
}

void MainWindow::setTamanhoLabirinto(long Tamanho)
{
    this->Tamanho = Tamanho;
}

long MainWindow::getTamanhoLabirinto()
{
    return this->Tamanho;
}

void MainWindow::desenharCena()
{
    cena->clear();

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            QPen *pen = new QPen(QColor(130,50,10));
            QBrush *brush = new QBrush(QColor(130,50,10));

            //Random

            /*if(QRandomGenerator::global()->bounded(10) == 5)
            {
                pen->setColor(QColor(250,250,200));
                brush->setColor(QColor(250,250,200));

            }
            else
            {*/
                pen->setColor(QColor(130,50,10));
                brush->setColor(QColor(130,50,10));
            /*}*/
            //chao
            cena->addRect(i*TAMANHO_RETANGULO, j * TAMANHO_RETANGULO, TAMANHO_RETANGULO, TAMANHO_RETANGULO, *pen, *brush);

            delete pen;
            delete brush;
        }
    }

    cena->setSceneRect(cena->itemsBoundingRect());

    QVector<QPoint> triangle;
    QColor color(111, 255, 232);
    /*if (w->isJustBumped())
        color.setRgb(255, 0, 0);*/

    Agente::acoes acao; //tem que pegar a ultima

    QPen pen(color);
    QBrush brush(color);
    int posX = 5 * TAMANHO_RETANGULO,
        posY = 5 * TAMANHO_RETANGULO;


    switch (acao)
    {
        case Agente::PARADO:
            //nada
        break;

        case Agente::CIMA:
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO / 2,
                                      posY + TAMANHO_RETANGULO / 10));
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO / 10,
                                      posY + TAMANHO_RETANGULO * 9 / 10));
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO * 9 / 10,
                                      posY + TAMANHO_RETANGULO * 9 / 10));

        break;

        case Agente::BAIXO:
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO / 2,
                                      posY + TAMANHO_RETANGULO * 9 / 10));
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO / 10,
                                      posY + TAMANHO_RETANGULO / 10));
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO * 9 / 10,
                                      posY + TAMANHO_RETANGULO / 10));
        break;

        case Agente::ESQUERDA:
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO / 10,
                                      posY + TAMANHO_RETANGULO / 2));
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO * 9 / 10,
                                      posY + TAMANHO_RETANGULO / 10));
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO * 9 / 10,
                                      posY + TAMANHO_RETANGULO * 9 / 10));
        break;

        case Agente::DIREITA:
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO * 9 / 10,
                                      posY + TAMANHO_RETANGULO / 2));
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO / 10,
                                      posY + TAMANHO_RETANGULO / 10));
            triangle.push_back(QPoint(posX + TAMANHO_RETANGULO / 10,
                                      posY + TAMANHO_RETANGULO * 9 / 10));
        break;

        default:
            //nada
        break;
    }

    if(acao == Agente::PARADO)
        cena->addRect(posX + TAMANHO_RETANGULO / 10,
                       posY + TAMANHO_RETANGULO / 10,
                       TAMANHO_RETANGULO * 4 / 5, TAMANHO_RETANGULO * 4 / 5,
                       pen, brush);
    else
        cena->addPolygon(QPolygon(triangle), pen, brush);
}
