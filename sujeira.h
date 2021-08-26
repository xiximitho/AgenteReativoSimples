#ifndef SUJEIRA_H
#define SUJEIRA_H

#include <QWidget>
#include <QLabel>

class Sujeira : public QWidget
{
    Q_OBJECT
public:
    Sujeira(QWidget *parent = nullptr, short PosicaoX = 0, short PosicaoY = 0);

    void criar(QWidget *parent = nullptr, short PosicaoX = 0, short PosicaoY = 0);
    short PosicaoX;
    short PosicaoY;
    short Altura;
    short Largura;

    QLabel *sujeira;
    QPixmap *imagem;

signals:

};

#endif // SUJEIRA_H
