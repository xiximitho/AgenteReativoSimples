#ifndef AGENTE_H
#define AGENTE_H

#include <QtWidgets>

class Agente : public QWidget
{
    Q_OBJECT
public:
    explicit Agente(QWidget *parent = nullptr);


    enum acoes
    {
        ESQUERDA,
        DIREITA,
        CIMA,
        BAIXO,
        PARADO
    };

    QPixmap imagem;

    void moverEsquerda();
    void moverDireita();
    void moverCima();
    void moverBaixo();

    acoes act(bool, int , acoes);

signals:

};

#endif // AGENTE_H
