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
    void onClose();

protected:
    QString fileName;
private slots:
    void onClickBotaoPasso();
    void onClickRandom();
private:
    QGraphicsView *view;
    QGraphicsScene *cena;
    QLabel *qtdLimpo;
    QPushButton *btnIniciar;
    QCheckBox *chkAleatorio;
    bool aleatorio;
    QLabel *final;
    long Tamanho;
    int rodando;
    void delay();
    int Limpo;

    Mundo *w;
    static const int TAMANHO_RETANGULO = 40;

    void atualizar();
};
#endif // MAINWINDOW_H
