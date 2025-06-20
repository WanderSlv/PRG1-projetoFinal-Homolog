#include "funcoes.h"

void menu() {
    printf("Bem-vindo ao meu joguinho a FUJA DAS BOLAS\n");
    printf("1 - Jogar\n");
    printf("2 - Sair\n");
    printf("3 - Opções\n");
    printf("4 - Créditos\n");
    printf("Escolha uma opção: ");
}

int main() {


    int vOp = 0;

    while (1) {
        menu();
        scanf("%d", &vOp);

         if (vOp == 1 || vOp == 2 || vOp == 3 || vOp == 4){       
            switch (vOp) {
                case 1:
                    printf("Você escolheu Jogar.\n");
                    printf("(Para Jogar utilize as setinhas do seu computador!!!!)\n");
                    printf("Digite seu nome: ");
                    char texto[50];
                    scanf("%49s",texto);
                    
                    int larguraJanela=1280;
                    int alturaJanela = 720;
                    SetTraceLogLevel(LOG_NONE);

                    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);

                    InitWindow(larguraJanela, alturaJanela, "Projeto Final");
                    int textoPosX=50;
                    int textoPosY=50;

                    desenha(textoPosX, textoPosY, larguraJanela, alturaJanela, texto);
                    break;

                case 2:
                    printf("Você escolheu Sair. Tchau!\n");
                    return 0;

                case 3:
                    printf("Você escolheu Opções. Ainda em desenvolvimento...\n");
                    break;

                case 4:
                    printf("Você escolheu Créditos. Feito por você!\n");
                    break;

                case 5:
                    printf("Olá Mundo!");
                    break;

                default:
                    printf("Escolha inválida! Tente novamente...\n");
            }

            printf("\n\n");
        } else {
            printf("Digitou errado, seu burro!");
            return 1;            
        }
    }

    return 0;
}