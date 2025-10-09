# Pac-Man (Come Come)

Implementação em C do famoso jogo de arcade Pac Man, popularmente conhecido no Brasil como Come Come, utilizando a biblioteca raylib. Esse repositório representa um projeto final da disciplina de Programação de Computadores II da Universidade Federal do Rio de Janeiro.

## Instalação e uso 

Crie uma cópia local desse repositório: 
```shell
git clone https://github.com/joaordc/pac-man.git
```

Em /pac-man, compile pacman.c:
```shell
gcc pacman.c -o pacman -lraylib -lwinmm -lgdi32 -lopeng132
```

Em seguida, rode o arquivo binário:
```shell
./pacman
```