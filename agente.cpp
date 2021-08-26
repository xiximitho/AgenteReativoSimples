#include "agente.h"

Agente::Agente(QWidget *parent) : QWidget(parent)
{



}

Agente::acoes Agente::act(bool, int, acoes)
{
    return (static_cast<acoes>(rand() % 4));
}
