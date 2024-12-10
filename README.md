# ProjetoEmbaixadores
Este é o projeto desenvolvido na disciplina de AFP

The directory data is going to store the data related to visita and embaixadores

Embaixador
    numeroEstudante
    escola (ESTS, ESTB, ESE, ESCE ou ESS)
    nomeCompleto
    nif

Visita
    idVisita
    listaEmbaixadores (máximo 9)
    estadoAtual (em planeamento, autorizada, cancelada ou realizada)
    localVisita
    dataVisita

Menu
    Opção 1: Listar visitas e detalhes
    Opção 2: Listar embaixadores e detalhes
    Opção 3: Consultar visita específica
    Opção 4: Consultar embaixador específico
    Opção 5: Adicionar visita
    Opção 6: Adicionar embaixador
    Opção 7: Autorizar visita
    Opção 8: Cancelar visita
    Opção 9: Confirmar realização da visita
    Opção 10: Alterar informação da visita
    Opção 11: Alterar informação do embaixador
    Opção 12: Eliminar visita
    Opção 13: Eliminar embaixador
    Opção 14: Gravar visitas e embaixadores em ficheiros de texto
    Opção 15: Sair da aplicação


gcc main.c embaixador.c -o main
./main
