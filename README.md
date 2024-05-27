# Info Drive Utility

## Descrição

O __infoDrive__ é um utilirário em C++ que coleta e exibe informações detalhas sobre os drives do sistema. 
Ele fornece dados como espaço total e livre, tamanho de clusters e setores, etc.

## Funcionalidades

- __infoDrive(char drive)__: Retorna informações detalhadas sobre um drive específico.
- __currentDrive()__: Retorna a letra do drive atual.
- __numberOfDrives()__: Retorna o número total de drives disponíveis no sistema.
- __drives()__: Retorna uma string com as letras de todos os drives do sistema.
- __relatorio()__: Exibe o relatório detalhado de todos os drives do sistema

## Como Usar

### Compilação

Para compilar o programa, você precisa de um compilador em C++ que suporte a biblioteca padrão C++ e a biblioteca `direct.h`. 
No teminal o seguinte comando:

```

g++ -o InfoDrive InfoDrive.cpp

```

### Execução

Após a compilação, execute o programa com:

```

./InfoDrive

```

O programa exibirá um relatório sobre os drives do sistema.




