#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <QWidget>
#include "sujeira.h"

class Labirinto
{
public:
    Labirinto(QWidget *parent = nullptr, short tamanho = 0);

    void construirNovoLabirinto(QWidget *parent = nullptr);
    void exibirLabirinto();


    QStringList ListaLabirinto;

    //Agente

private:
    long TamanhoLabirinto;

};

#endif // LABIRINTO_H
