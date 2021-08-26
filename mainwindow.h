#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "labirinto.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setTamanhoLabirinto(long Tamanho);
    long getTamanhoLabirinto();
    void desenharCena();

protected:
    //QPixmap *Agente;
    QPixmap *Sujeira;
    QPixmap *Parede;


private:
    QGraphicsView *view;
    QGraphicsScene *cena;
    long Tamanho;
    Labirinto *labirinto;

    static const int TAMANHO_RETANGULO = 40;
};
#endif // MAINWINDOW_H
