**Game fuga das bolas.**

Este projeto foi desenvolvido como trabalho final para o primeiro semestre do curso de Engenharia de Telecomunicações, no Instituto Federal de Santa Catarina (IFSC), campus São José.

O objetivo principal do jogo é desafiar o jogador a desviar-se de múltiplos objetos esféricos ("bolas") pelo maior período de tempo possível. A performance do jogador é mensurada através de um sistema de pontuação dinâmico, onde o tempo de sobrevivência no cenário é diretamente convertido em pontos.

**Compilando**

Primeiro, instale as dependências necessárias:

openSUSE Tumbleweed (sistema que utilizo) →

```zypper install make gcc libX11-devel Mesa-libGL-devel```

Distribuições baseadas em Debian →

```apt install --no-install-recommends make libgl1-mesa-dev gcc libc6-dev```

Para windonws (acesse o passo a passo para donwload) →

```https://github.com/raysan5/raylib/wiki/Working-on-Windows```

Clone o repositório e compile o projeto:

```git clone https://github.com/WanderSlv/PRG1-projetoFinal-Homolog```

```cd PRG1-projetoFinal-Homolog```

Basta executar o executável:

 ```make clean && make && ./bin/wander```
