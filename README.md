# ProjetoEmbaixadores
Este é um sistema de gestão de visitas desenvolvido na disciplina de AFP.
Permite criar e gerir embaixadores e visitas. 
Este conta com 3 entidades sendo elas o Embaixador, Visita e o menu.

# Entidades
## Embaixador
1. O número de estudante
2. A escola (ESTS, ESTB, ESE, ESCE ou ESS)
3. O nome completo
4. O nif (número de identificação fiscal)

## Visita
1. ID da visita (Único, automático, não pode ser alterado nem repetido)
2. Lista de embaixadores (Máximo de 9)
3. Estado da visita (Em Planeamento, Autorizada, Cancelada ou Realizada)
4. Local a visitar
5. Data da visita


## Menu
1. Listar visitas
2. Listar embaixadores
3. Consultar visita 
4. Consultar embaixador
5. Adicionar visita
6. Adicionar embaixador
7. Autorizar visita
8. Cancelar visita
9. Confirmar visita
10. Alterar informação da visita
11. Alterar informação do embaixador
12. Eliminar visita
13. Eliminar embaixador
14. Gravar (Não incluida. Os embaixadores e as visitas são gravadas ao serem criadas)
15. Sair

# Instrução para compilar o projeto
1. gcc main.c src/embaixador.c src/menu.c src/visita.c src/utils.c -o main

# Estrutura do projeto
ProjetoEmbaixadores/
├── data/
│   ├── embaixador.csv
│   └── visita.csv
├── include/
│   ├── embaixador.h
│   ├── menu.h
│   ├── utils.h
│   └── visita.h
├── src/
│   ├── embaixador.c
│   ├── menu.c
│   ├── utils.c
│   └── visita.c
├── main.c
└── README.md

## data/
1. embaixador.csv - Dados dos embaixadores
2. visita.c - Guatda os dados da visita

## include/
1. embaixador.h  -> Define a estrutura do embaixador e contém protótipo de funções do embaixador
2. menu.h  -> Protótipo de funções do menu
3. utils.h  -> Protótipo de funções para validação de dados e otimização do programa
4. visita.h  -> Define estrutura da visita e contém protótipo de funções da visita