#include "mundo.h"

Mundo::Mundo(string filename)
{
    bateu = false;
    qtd_sujeira = 0;
    qtd_sujeira_gerada = 0;
    limpou = false;
    currentTime = 0;

    /* Lê e inicializa o mapa*/
    string linha;
    ifstream mapFile(filename.c_str());
    getline(mapFile, linha);
    while (linha.substr(0,2).compare("//") == 0 || linha.empty()
            || linha.find_first_not_of(' ') == string::npos)
    {
        getline(mapFile, linha);

        if(mapFile.eof())
        {
            mensagemErro = "Final de linha";
            break;
        }
    }

    istringstream parametros(linha);

    parametros.exceptions(ifstream::eofbit | ifstream::badbit);
    try
    {
        parametros >> agentePosX >> agentePosY;
    }
    catch (std::exception f)
    {
        if(parametros.eof())
            mensagemErro =  "Erro ao ler os parametros iniciais";
        else
            mensagemErro = f.what();

        return;
    };

    inicialAgentePosX = agentePosX;
    inicialAgentePosY = agentePosY;

    unsigned int mapSeed;
    try
    {
        parametros >> mapSeed;
    }
    catch (std::exception f)
    {
        if(! parametros.eof())
        {
            mensagemErro = f.what();

            return;
        }
    };

    seed = mapSeed;

    srand(time(NULL));

    try
    {
        parametros >> seed;
    }
    catch (std::exception f)
    {

    }

    int nlinha = -1;
    while(! mapFile.eof())
    {
        nlinha++;
        getline(mapFile, linha);
        istringstream map(linha);

        map.exceptions(ifstream::eofbit);
        int ncoluna = 0;
        while(! map.eof())
        {
            char c;
            int val;
            try
            {
                map >> c;
            }
            catch (std::exception f)
            {
                if(map.eof())
                    break;
            };
            switch(c)
            {
            case MAPA_OBSTACULO:
                val = OBSTACULO;
                break;

            case MAPA_SUJEIRA:
                val = SUJEIRA;
                qtd_sujeira_gerada ++;
                break;

            case MAPA_CAMINHO:
                val = 0;
                break;

            default:
                mensagemErro = "Erro de leitura de caractere";

                return;
            }
            if(nlinha == 0)
            {
                mundo.push_back(new vector<int>);
                mundo.back()->push_back(val);
            }
            else
            {
                if(ncoluna >= LARGURA_MUNDO)
                {
                    mensagemErro = QTranslator::tr("Linha %1 é maior do que os outros (deve ser %2)").arg(nlinha).arg(LARGURA_MUNDO);

                    return;
                }
                else
                {
                    mundo[ncoluna]->push_back(val);
                }
            }
            ncoluna++;
        }
        if(nlinha == 0)
        {
            LARGURA_MUNDO = mundo.size();
        }
    }
    ALTURA_MUNDO = nlinha;

    mapFile.close();

    ultimaAcao = Agente::PARADO;

    energiaConsumida = 0;
    currentTime = 0;
    agente = new Agente();

}

void Mundo::realizarAcao(Agente::acoes acao)
{
    bateu = false;
    limpou = false;

    switch (acao) {
    case Agente::ESQUERDA:
        if(agentePosX == 0 || agentePosX == LARGURA_MUNDO-1
                || mundo[agentePosX-1]->at(agentePosY) == OBSTACULO)
        {
            bateu = true;
        }
        else
        {
            agentePosX--;
        };
        energiaConsumida++;
        break;

    case Agente::DIREITA:
        if(agentePosX == 0 || agentePosX == LARGURA_MUNDO-1
                || mundo[agentePosX+1]->at(agentePosY) == OBSTACULO)
        {
            bateu = true;
        }
        else
        {
            agentePosX++;
        };
        energiaConsumida++;
        break;

    case Agente::CIMA:
        if(agentePosY == 0 || agentePosY == ALTURA_MUNDO-1
                || mundo[agentePosX]->at(agentePosY-1) == OBSTACULO)
        {
            bateu = true;
        }
        else
        {
            agentePosY--;
        };
        energiaConsumida++;
        break;

    case Agente::BAIXO:
        if(agentePosY == 0 || agentePosY == ALTURA_MUNDO-1
                || mundo[agentePosX]->at(agentePosY+1) == OBSTACULO)
        {
            bateu = true;
        }
        else
        {
            agentePosY++;
        };
        energiaConsumida++;
        break;
    case Agente::LIMPOU:
        if(mundo[agentePosX]->at(agentePosY) > 0)
        {
            mundo[agentePosX]->at(agentePosY)--;
        };
        energiaConsumida += 2;
        qtd_sujeira++;
        qDebug() << "limpou";
        break;

    case Agente::PARADO:
        break;
    }

    ultimaAcao = acao;
}


void Mundo::realizarUmaAcao()
{
    if(ultimaAcao == Agente::CIMA && !bateu)
    {
        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), Agente::CIMA));
        qDebug() << "CIMA !bateu";
    }
    else if(ultimaAcao == Agente::BAIXO && !bateu){
        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), Agente::BAIXO));
        qDebug() << "BAIXO !bateu";
    }
    else if(ultimaAcao == Agente::ESQUERDA && !bateu){
        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), Agente::ESQUERDA));
        qDebug() << "ESQUERDA !bateu";
    }
    else if(ultimaAcao == Agente::DIREITA && !bateu){
        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), Agente::DIREITA));
        qDebug() << "DIREITA !bateu";
    }
    else if (ultimaAcao == Agente::PARADO){
        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), Agente::CIMA));
        qDebug() << "PARADO";
    }
    else if (bateu){ //movimento randomico
        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), static_cast<Agente::acoes>(rand() % 4)));
           qDebug() << "BATEU";
    }
    else
    {//movimento randomico
        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), Agente::CIMA));
           qDebug() << "NBATEU";
    }
    /*else if (ultimaAcao == Agente::CIMA && bateu){
        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), Agente::ESQUERDA));
        qDebug() << "CIMA bateu";
    }
    else if (ultimaAcao == Agente::ESQUERDA && bateu){
        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), Agente::DIREITA));
        qDebug() << "ESQUERDA bateu";
    }
    else if (ultimaAcao == Agente::DIREITA && bateu){
        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), Agente::BAIXO));
        qDebug() << "DIREITA bateu";
    }
//    else if (ultimaAcao == Agente::BAIXO && bateu){
//        realizarAcao(agente->act(bateu, mundo[agentePosX]->at(agentePosY), Agente::ESQUERDA));
//        qDebug() << "BAIXO bateu";
//    }

    else{ //Chama randomicamente

    }*/



}

void Mundo::resetMapa()
{
    for(int col = 0; col < LARGURA_MUNDO; col++)
        for(int linha= 0; linha < ALTURA_MUNDO; linha++)
            if(mundo[col]->at(linha) != OBSTACULO)
            {
                mundo[col]->at(linha) = 0;
            }

    /*resetar a posicao do agente*/

    agentePosX = inicialAgentePosX;
    agentePosY = inicialAgentePosY;

    ultimaAcao= Agente::PARADO;

    currentTime = 0;

    delete agente;
    agente = new Agente();

}
