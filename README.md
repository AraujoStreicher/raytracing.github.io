# Raytracing in One Weekend

Nossa cena desenvolvida com Raytracing in One Weekend como parte da avaliação da disciplina de Processamento Gráfico. A cena representa um rosto feliz composto por esferas.

## Grupo
- Ana Clara Santana Matta – RA: 822396
- Anne Mari Suenaga Sakai – RA: 822304
- Felipe Jun Nishitani – RA: 822353
- Gabriel Araujo Streicher – RA: 822485

## Especificações do Projeto

### Requisitos Cumpridos

- Seguimos o tutorial *Raytracing in One Weekend*
- A cena composta por diversos materias
- A câmera foi ajustada para visualização do rosto
  
## Construção e Execução

O projeto usa **CMake**. Para construir:

```bash
# Configuração
$ cmake -B build

# Compilação 
$ cmake --build build
ou
$ cmake --build build --target inOneWeekend

# Gerar imagem
$ build/inOneWeekend > image.ppm

# Visualizar imagem
$ gimp image.ppm
```
