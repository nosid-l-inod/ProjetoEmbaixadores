# ProjetoEmbaixadores
Este é o projeto desenvolvido na disciplina de AFP

# Instruções para compilar o projeto
gcc main.c src/embaixador.c src/utils.c -o main
gcc main.c src/embaixador.c src/menu.c src/utils.c -o main
gcc main.c src/embaixador.c src/menu.c src/visita.c src/utils.c -o main
gcc main.c src/embaixador.c src/menu.c src/visita.c src/utils.c -o main

# Menu do projeto
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
14. Gravar visitas (Não incluí no projeto. As visitas são gravadas no ficheiro ao serem criadas ou alteradas)
15. Sair
16. Outras funcionalidades

# Adicionar Embaixador
Esta função cria um embaixador e guarda o mesmo no ficheiro csv

# Validar numero de estudante
garante que o campo aceite o tipo de dado esperado, um numero

# Estrutura do projeto
ProjetoEmbaixadores/
├── src/
│   ├── embaixadore.c
│   ├── menu.c
│   ├── utils.c
│   └── visita.c
├── include/
│   ├── embaixadore.h
│   ├── menu.h
│   ├── utils.h
│   └── visita.h
├── data/
│   ├── embaixador.csv
│   └── visita.csv
├── main.c
└── README.md

# menu.c
Para mostrar o menu, utilizei procedimentos ao invez de funções para manter o main.c limpo