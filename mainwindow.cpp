#include "mainwindow.h"
#include <QRandomGenerator>
#include "agente.h"
#include <QLabel>
#include <string>
using std::string;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(500,500);
    view = new QGraphicsView(this);
    cena = new QGraphicsScene();

    view->setScene(cena);

    view->resize(500,500);


    QFileDialog arq (this);
    arq.setFileMode(QFileDialog::ExistingFile);
    fileName = "./teste.map";//arq.getOpenFileName();


    qtdLimpo = new QLabel("", this);
    qtdLimpo->move(5, 0);

    btnIniciar = new QPushButton("Iniciar", this);
    btnIniciar->move(btnIniciar->x() + 22, btnIniciar->y());

    final = new QLabel("", this);
    final->move(150, btnIniciar->y()+7);
    final->resize(180, 13);
    aleatorio = false;

    chkAleatorio = new QCheckBox("Randomizar", this);
    chkAleatorio->move(final->x()+final->width() + 20, btnIniciar->y());
    connect(chkAleatorio, &QCheckBox::clicked, this, &MainWindow::onClickRandom);
    connect(btnIniciar, &QPushButton::clicked, this, &MainWindow::onClickBotaoPasso);
    connect(this, &MainWindow::destroyed, this, &MainWindow::onClose);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onClose()
{
    exit(0);
}

void MainWindow::carregarMapa()
{
    w = new Mundo(fileName.toLocal8Bit().constData(), aleatorio);//.toLocal8Bit().constData());

    if(w->getMensagemErro().isEmpty())
    {
            rodando = 1;
            Limpo = 0;
    }
}

void MainWindow::onClickRandom()
{
    if(this->aleatorio == true)
        this->aleatorio = false;
    else
        this->aleatorio = true;

}

void MainWindow::onClickBotaoPasso()
{
    carregarMapa();
    desenharCena();

    QTime tempoMax = QTime::currentTime().addSecs(10);
    //while(w->get_qtd_sujeira() != w->get_qtd_sujeira_gerada())
    while(QTime::currentTime() < tempoMax)
    {
        qDebug() << w->get_qtd_sujeira() << " gerada: " << w->get_qtd_sujeira_gerada();
        delay();
        w->realizarUmaAcao();
        desenharCena();
    }

    int limpo = w->get_qtd_sujeira();
    qDebug() << "limpou " << limpo << " em 10s";

    double porcentagemLimpa =  limpo*100/w->get_qtd_sujeira_gerada();
    final->setText("Limpou " + QString::number(limpo) + " de "+QString::number(w->get_qtd_sujeira_gerada())+ " em 10s = "+QString::number(porcentagemLimpa) + "% ");

    //w->resetMapa();
}

void MainWindow::delay()
{
        QTime tempoEspera= QTime::currentTime().addMSecs(50);
        while (QTime::currentTime() < tempoEspera)
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
