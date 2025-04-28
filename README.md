# Linguagem para coreografia de luzes 

**Autor:** [Lucas Lima](https://github.com/lucasouzamil)

## Apresentação

Esta é uma linguagem de programação que eu estou planejando criar para programar uma fitas de Led.
Em vez de ter que programar direto em linguagens complicadas como C++ ou mexer em bibliotecas pesadas, esta deixa tem o intuito de deixar tudo muito mais simples e intuitivo: criando efeitos visuais como animações, arco-íris, batimentos de luz, entre outros.

A ideia é criar uma linguagem focada só no que importa para esse tipo de projeto:

* controlar cada LED individualmente,

* criar efeitos dinâmicos como rotações e fades,

* e deixar loops e condições muito fáceis de escrever.

**Exemplo de programa:**

Aqui está um exemplo de código simples:

``` linguagem
strip 60

for i = 0..59 {
    set i color hsv(i*4, 1, 1)
}

loop forever {
    rotate 1 dir right
    wait 50ms
}
```

**O que esse programa faz?**

* Primeiro, a gente diz que o nosso "strip", ou seja, nossa fita, tem 60 LEDs.

* Depois, usamos um for para pintar cada LED com uma cor diferente, criando um efeito de arco-íris ao longo da fita.
Cada LED recebe uma cor diferente baseada na posição dele (i).
s disso, entramos num loop infinito (loop forever) que:

  * Gira todas as cores da fita 1 posição para a direita,

  * Espera 50 milissegundos,

  * E repete o processo para dar a sensação de movimento.

O resultado visual é um arco-íris girando suavemente pela fita.