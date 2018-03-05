#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int restoCPF(int x);
void limpaBuffer();
int validar(char *s);
int pegaN();
void novoCPF(char *cpf);

int main(int argc, char **argv) {
    FILE *f;
    char cpf[11];
    int n = 1;

    srand(time(NULL));
    if(argc == 2) {
        f = fopen(argv[1], "r+");
        if(f != NULL) {
            if(validar(argv[1]) == 1) {
                fclose(f);
                fopen(argv[1], "w");
            } else {
                fopen(argv[1], "r+");
            }
        } else {
            f = fopen(argv[1], "w");
        }
        n = pegaN();
        fseek(f, 0, SEEK_SET);
    
        for(int i = 0; i < n; i++) {
            novoCPF(cpf);
            fprintf(f, "%s\n", cpf);
        }

        if(fclose(f) != 0) {
            printf("Arquivo %s nao conseguiu ser salvo", argv[1]);
        }
    }
    else if(argc > 2) {
        printf("Uso geracpf [nome do arquivo] (Nome do arquivo e opcional\n");
        return 0;
    }
    else {
        novoCPF(cpf);
        printf("%s\n", cpf);
    }
    return 0;
}

int restoCPF(int x) {
    x = x * 10 % 11;
    return (x == 10) ? 0 : x;
} 

void novoCPF(char *cpf) {
    int priDig = 0, segDig = 0, multiplicador = 10;

    for(int i = 0; i < 10; i++) {
        cpf[i] = (rand() % 10) + '0';
    }

    // acha primeiro digito
    for(int i = 0; i <= 8; i++) {
        priDig += ((cpf[i] - '0') * multiplicador);
        --multiplicador; 
    }
    cpf[9] = (restoCPF(priDig) - '0');


    // acha segundo digito
    multiplicador = 11;
    for(int i = 0; i <= 9; i++) {
        segDig += ((cpf[i] - '0') * multiplicador);
        --multiplicador; 
    }
    cpf[10] = (restoCPF(segDig) - '0');
    
}

void limpaBuffer() {
    char c;

    do {
        scanf("%c", &c);
    } while(c != '\n');
}

int validar(char *s) {
    int erro = 0, resp;

    do {
        if(erro) {
            printf("Resposta Invalida. ");
        }
        printf("Arquivo %s existe. Deseja:\n\n", s);
        printf("\t1 - Para sobrescreve-lo\n");
        printf("\t2 - Acrescentar ao final do arquivo\n\n");
        printf("Sua escolha: ");
        scanf("%d", &resp);
        limpaBuffer();
        erro = 1;
    } while (resp < 1 && resp > 2);
    return resp;
}

int pegaN() {
    int resp, erro = 0;

    do {
        if(erro) {
            printf("Numero precisa ser maior que zero ");
        }
        printf("Digite o numero de CPFs desejado: ");
        scanf("%d", &resp);
        limpaBuffer();
        erro = 1;
    } while(resp <= 0);
    return resp;
}