#include "labirinto.h"
#include "QLabel"

Labirinto::Labirinto(QWidget *parent, short tamanho)
{
    this->TamanhoLabirinto = tamanho;
    this->construirNovoLabirinto(parent);
    this->exibirLabirinto();
}

void Labirinto::construirNovoLabirinto(QWidget *parent)
{

    int posX = 10;
    int posY = 10;
    for(int i = 0; i < this->TamanhoLabirinto; i++)
    {
        for(int j = 0; j < this->TamanhoLabirinto; j++)
        {
            Sujeira *sujinho = new Sujeira;

            sujinho->criar(parent, posX, posY);
//            QLabel *novo = new QLabel(parent);
//            novo->move(posX, posY);

            posX += 35;
        }
        posY += 15;
        posX = 10;
    }
}

void Labirinto::exibirLabirinto()
{

}
