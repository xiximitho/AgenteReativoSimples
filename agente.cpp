#include "agente.h"

Agente::Agente(QWidget *parent) : QWidget(parent)
{

}

Agente::acoes Agente::act(bool bateu, int sujeira, acoes A)
{
    if(sujeira > 0)
        return LIMPOU;

    return A;
    //return (static_cast<acoes>(rand() % 4)); //movimentos randomicos
}
