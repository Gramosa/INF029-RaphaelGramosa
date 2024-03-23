# Projeto Escola

## Descrição

O Projeto Escola é um sistema de cadastro (CRUD) desenvolvido com o objetivo de gerenciar estudantes, professores e disciplinas, estabelecendo relações entre eles. Além disso, possibilita a geração de relatórios simples, sendo executado em um terminal.

## Colaboradores

- Maria Vitória Santos da Silva
- Raphael de Jesus Gramosa (@Gramosa)
- Ravena Dafne Costa Carneiro (@RavenaDafne)

## Compilação

Para compilar o projeto, siga os passos abaixo:

1. Navegue até o diretório do projeto:

    ```bash
    cd projetoEscola/
    ```

2. Execute o comando de compilação:

    ```bash
    gcc main.c person.c utils.c subject.c -Wno-unused-result -o projeto && ./projeto
    ```

## Funcionalidades

### Cadastro de Pessoas (alunos e professores)

- Criar, editar e excluir.
- Validação de campos como:
  - Nome: Capitalização automática, caracteres alfabéticos, ausência de espaços duplicados ou no início da palavra, entre outros.
  - Matrícula: Valores positivos não nulos, não repetição de matrículas já cadastradas, etc.
  - CPF: Verificação dos dígitos verificadores através de cálculo matemático, exemplos de CPFs válidos: 12345678909, 06077218049, 56040728000, entre outros.
  - Sexo: Capitalização automática (ex: 'm' ou 'M' são aceitos).
  - Data de nascimento: Coleta em formato dd/mm/aaaa, validação de limites (inclusive anos bissextos).
  - Idade (calculada através da data de nascimento): Validação de limites (idade mínima 5 anos e máxima 120 anos), entre outros.

### Cadastro de Matérias

- Criar, editar e excluir.
- Validação de campos como:
  - Nome: Mesmos critérios de validação utilizados para Pessoas.
  - Código e semestre: Positivos e não nulos.
  - Professor e Aluno: Cadastro de pessoas existentes e não cadastradas na respectiva matéria.

### Emissão de Relatórios

Além das funcionalidades de cadastro, o sistema permite a emissão de alguns relatórios.


 ============================================
|             Menu Principal          |
|-------------------------------------|
|  0 - Sair                           |
|  1 - Cadastro de Aluno              |
|  2 - Cadastro de Professor          |
|  3 - Cadastro de Disciplina         |
|  4 - Relatórios                     |
=======================================

=======================================
|        Cadastro de Aluno            |
|-------------------------------------|
|  0 - Voltar                         |
|  1 - Cadastrar Aluno                |
|  2 - Atualizar Aluno                |
|  3 - Excluir Aluno                  |
=======================================

 ============================================
|       Cadastro de Professor         |
|-------------------------------------|
|  0 - Voltar                         |
|  1 - Cadastrar Professor            |
|  2 - Atualizar Professor            |
|  3 - Excluir Professor              |
=======================================

 =============================================
|      Cadastro de Disciplina         |
|-------------------------------------|
|  0 - Voltar                         |
|  1 - Cadastrar Disciplina           |
|  2 - Atualizar Disciplina           |
|  3 - Excluir Disciplina             |
=======================================

 =================================================
|             Relatórios                 |
|----------------------------------------|
|  0 - Voltar                            |
|  1 - Listar Alunos                     |
|  2 - Listar Professores                |
|  3 - Listar Disciplinas                |
|  4 - Listar uma Disciplina             |
|  5 - Listar Alunos por Sexo            |
|  6 - Listar Alunos por Nome            |
|  7 - Listar Alunos por Data Nasc.      |
|  8 - Listar Professores por Sexo       |
|  9 - Listar Professores por Nome       |
| 10 - Listar Professores por Data Nasc. |
| 11 - Aniversariantes do Mês            |
| 12 - Lista de pessoas (professor/aluno)|
| 13 - Lista de Alunos < 3 Disciplinas   | 
| 14 - Lista de Disciplinas > 40 Vagas   |
=========================================
