#include "sujeira.h"

Sujeira::Sujeira(QWidget *parent, short posicaoX, short posicaoY)
{

}

void Sujeira::criar(QWidget *parent, short PosicaoX, short PosicaoY)
{

    imagem = new QPixmap("/imgs/sujeira.png");
    sujeira = new QLabel(parent);
    sujeira->setText("a");
    sujeira->setPixmap(*imagem);
    sujeira->resize(100,100);
    sujeira->move(PosicaoX,PosicaoY);

}
