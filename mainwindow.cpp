#include "mainwindow.h"
#include <QRandomGenerator>
#include "agente.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(500,500);
    view = new QGraphicsView(this);
    cena = new QGraphicsScene();

    view->setScene(cena);

    view->resize(500,500);

    fileName = "./teste.map";
    carregarMapa();

    desenharCena();



    qtdLimpo = new QLabel("", this);

    btnIniciar = new QPushButton("Iniciar", this);
    btnIniciar->move(btnIniciar->x() + 20, btnIniciar->y());

    connect(btnIniciar, &QPushButton::clicked, this, &MainWindow::onClickBotaoPasso);
}

MainWindow::~MainWindow()
{
}

void MainWindow::carregarMapa()
{
    w = new Mundo(fileName.toLocal8Bit().constData());
    if(w->getMensagemErro().isEmpty())
    {
            rodando = 1;
            Limpo = 0;
    }
}

void MainWindow::onClickBotaoPasso()
{
    while(w->get_qtd_sujeira() != w->get_qtd_sujeira_gerada())
    {
        qDebug() << w->get_qtd_sujeira() << " gerada: " << w->get_qtd_sujeira_gerada();
        delay();
        w->realizarUmaAcao();
        desenharCena();
    }
    //w->resetMapa();
}

void MainWindow::delay()
{
        QTime dieTime= QTime::currentTime().addMSecs(50);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
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

            //Desenhar o mundo conforme os Lines

            if(w->getMundo().at(i)->at(j) != -1)
            {
                //int sujeira = w->getMundo().at(i)->at(j);
                int corSujeira = 255;

                pen->setColor(QColor(corSujeira, corSujeira, corSujeira));
                brush->setColor(QColor(corSujeira, corSujeira, corSujeira));

            }
            if(w->getMundo().at(i)->at(j) == 1) //codigo da sujeira
            {
                //int sujeira = w->getMundo().at(i)->at(j);
                int corSujeira = 100;

                pen->setColor(QColor(corSujeira, corSujeira, corSujeira));
                brush->setColor(QColor(corSujeira, corSujeira, corSujeira));

            }

            cena->addRect(i*TAMANHO_RETANGULO, j * TAMANHO_RETANGULO, TAMANHO_RETANGULO, TAMANHO_RETANGULO, *pen, *brush);

            delete pen;
            delete brush;
        }
    }

    cena->setSceneRect(cena->itemsBoundingRect());

    QVector<QPoint> triangle;
    QColor color(111, 255, 232);
    if (w->getBateu())
        color.setRgb(255, 0, 0);

    Agente::acoes acao = w->getUltimaAcao(); //tem que pegar a ultima

    QPen pen(color);
    QBrush brush(color);
    int posX = w->getAgentePosX() * TAMANHO_RETANGULO,
        posY = w->getAgentePosY() * TAMANHO_RETANGULO;


    switch (acao)
    {
    case Agente::PARADO:
        //nada
        break;

    case Agente::LIMPOU: //pinta de amarelo
        pen.setColor(QColor(255, 255, 0));
        brush.setColor(QColor(255, 255, 0));

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

    atualizar();
}

void MainWindow::atualizar()
{
    QString ultimaAcao;

    switch (w->getUltimaAcao()) {
    case Agente::CIMA:
        ultimaAcao = "Cima";
        break;
    case Agente::BAIXO:
        ultimaAcao = "Baixo";
        break;
    case Agente::ESQUERDA:
        ultimaAcao = "Esquerda";
        break;
    case Agente::DIREITA:
        ultimaAcao = "Direita";
        break;
    case Agente::LIMPOU:
        ultimaAcao = "Limpou";
        Limpo++;
        qtdLimpo->setText(QString::number(Limpo));
        break;
    default:
        ultimaAcao = "Parado";
        break;
    }

    if(w->getBateu())
        ultimaAcao.append((QString("Bateu!")));
    else
        ultimaAcao.append(NULL);
}
