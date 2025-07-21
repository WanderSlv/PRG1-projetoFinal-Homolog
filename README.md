# Jogo "A Fuja das Bolas"

Este projeto foi desenvolvido como trabalho final para o primeiro semestre no Instituto Federal de Santa Catarina (IFSC), campus São José.

O objetivo principal do jogo é desafiar o jogador a desviar-se de múltiplos objetos esféricos ("bolas") pelo maior período de tempo possível. A performance do jogador é mensurada através de um sistema de pontuação dinâmico, onde o tempo de sobrevivência no cenário é diretamente convertido em pontos.

---

## Compilando o Projeto

Para compilar e executar o jogo, siga os passos abaixo de acordo com seu sistema operacional.

### Dependências

Primeiro, instale as dependências de desenvolvimento necessárias para a Raylib e o compilador:

* **Para openSUSE Tumbleweed:**
    ```bash
    sudo zypper install make gcc libx11-devel Mesa-libGL-devel
    ```

* **Para Distribuições baseadas em Debian/Ubuntu:**
    ```bash
    sudo apt install --no-install-recommends make libgl1-mesa-dev gcc libc6-dev
    ```

* **Para Windows:**
    Acesse o guia oficial da Raylib para configurar seu ambiente de desenvolvimento:
    [https://github.com/raysan5/raylib/wiki/Working-on-Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows)

### Clonando e Compilando

Após instalar as dependências, clone o repositório do projeto e compile-o:

1.  **Clone o repositório:**
    ```bash
    git clone [https://github.com/WanderSlv/PRG1-projetoFinal-Homolog](https://github.com/WanderSlv/PRG1-projetoFinal-Homolog)
    ```

2.  **Navegue até o diretório do projeto:**
    ```bash
    cd PRG1-projetoFinal-Homolog
    ```

3.  **Compile e execute o jogo:**
    ```bash
    make clean && make && ./bin/wander
    ```
    Este comando limpa compilações anteriores, recompila o projeto e, se a compilação for bem-sucedida, executa o jogo.
