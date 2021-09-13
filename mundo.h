#ifndef MUNDO_H
#define MUNDO_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "agente.h"

using std::vector;
using std::ifstream;
using std::ios_base;
using std::string;
using std::istringstream;


class Mundo
{
public:
    Mundo(string, bool = false);

    vector< vector<int> * > getMundo()
    {
        return mundo;
    }

    int getLarguraMundo()
    {
        return LARGURA_MUNDO;
    }

    int getAlturaMundo()
    {
        return ALTURA_MUNDO;
    }

    int getCurrentTime()
    {
        return currentTime;
    }


    Agente::acoes getUltimaAcao()
    {
        return ultimaAcao;
    }

    int getAgentePosX()
    {
        return agentePosX;
    }

    int getAgentePosY()
    {
        return agentePosY;
    }

    bool getBateu()
    {
        return bateu;
    }

    bool getLimpou()
    {
        return limpou;
    }

    int get_qtd_sujeira_gerada()
    {
        return qtd_sujeira_gerada;
    }

    int get_qtd_sujeira()
    {
        return qtd_sujeira;
    }

    QString getMensagemErro(){ return mensagemErro;}

    void realizarAcao(Agente::acoes acao);
    void realizarUmaAcao();
    void resetMapa();

private:

    vector< vector<int> * > mundo;

    bool limpou;
    int qtd_sujeira;
    int qtd_sujeira_gerada;
    bool bateu;
    QString mensagemErro;
    int currentTime;
    int LARGURA_MUNDO, ALTURA_MUNDO;
    unsigned long energiaConsumida;
    /* desenho do mapa */

    static const int OBSTACULO = -1, SUJEIRA = 1;

    static const char MAPA_OBSTACULO = 'O',
                      MAPA_CAMINHO = '-',
                      MAPA_SUJEIRA = 'x';


    int agentePosX, agentePosY;
    int inicialAgentePosX, inicialAgentePosY;

    Agente::acoes ultimaAcao;
    Agente *agente;

    unsigned int seed;
};

#endif // MUNDO_H
