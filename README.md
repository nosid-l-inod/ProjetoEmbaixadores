# ProjetoEmbaixadores
Este é o projeto desenvolvido na disciplina de AFP

gcc main.c src/embaixador.c src/menu.c src/visita.c -o main
gcc main.c src/embaixador.c src/menu.c -o main


Mostrar a estrutura do projeto envez de escrever cenas
    Tipo a organização dos ficheiros

# Menu
1. Listar visitas e detalhes (total e por estado da visita - por ordem decrescente de ID de visita)
2. Listar embaixadores (total - apresentados por ordem alfabética do nome)
3. Consultar visita (específica mostrando os respetivos detalhes por ID)
4. Consultar embaixador (específico mostrando os respetivos detalhes por número de estudante)
5. Adicionar visita (o ID deve ser atribuído automaticamente, o estado inicial é em planeamento e os
restantes detalhes são fornecidos pelo utilizador)
6. Adicionar embaixador
7. Autorizar visita (por ID da visita, apenas possível se a visita estiver em planeamento e se tiver no
mínimo 2 embaixadores)
8. Cancelar visita (por ID da visita, possível se a visita não estiver realizada)
9. Confirmar visita (por ID da visita, apenas possível se a visita estiver autorizada e a data da visita for anterior à data actual)
10. Alterar informação da visita
11. Alterar informação do embaixador
12. Eliminar visita (apenas possível se a visita ainda não estiver realizada)
13. Eliminar embaixador (apenas possível se o embaixador não se encontrar associado a nenhuma
visita autorizada)
14. Gravar visitas
15. Sair
16. Outras funcionalidades


# Adicionar Embaixador
Esta função cria um embaixador e guarda o mesmo no ficheiro csv

# Validar numero de estudante
garante que o campo aceite o tipo de dado esperado, um numero