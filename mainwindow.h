#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "mundo.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setTamanhoLabirinto(long Tamanho);
    long getTamanhoLabirinto();
    void desenharCena();
    void carregarMapa();

protected:
    QString fileName;
private slots:
    void onClickBotaoPasso();
private:
    QGraphicsView *view;
    QGraphicsScene *cena;
    long Tamanho;
    int rodando;
    void delay();

    Mundo *w;
    static const int TAMANHO_RETANGULO = 40;

    void atualizar();
};
#endif // MAINWINDOW_H
