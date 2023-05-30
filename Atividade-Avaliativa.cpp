#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 1000
#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 100
#define MAX_ADDRESS_LENGTH 100

typedef struct {
    int id;
    char nome[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char sexo[MAX_NAME_LENGTH];
    char endereco[MAX_ADDRESS_LENGTH];
    double altura;
    int vacina;
} Usuario;

Usuario usuarios[MAX_USERS];
int numUsuarios = 0;

int gerarId() {
    return rand() % 1000 + 1;
}

void adicionarUsuario() {
    if (numUsuarios == MAX_USERS) {
        printf("Limite de usuários atingido.\n");
        return;
    }

    Usuario novoUsuario;
    novoUsuario.id = gerarId();

    printf("Nome completo: ");
    fgets(novoUsuario.nome, sizeof(novoUsuario.nome), stdin);

    printf("Email: ");
    fgets(novoUsuario.email, sizeof(novoUsuario.email), stdin);

    printf("Sexo (Feminino, Masculino, Indiferente): ");
    fgets(novoUsuario.sexo, sizeof(novoUsuario.sexo), stdin);

    printf("Endereço: ");
    fgets(novoUsuario.endereco, sizeof(novoUsuario.endereco), stdin);

    printf("Altura (entre 1 e 2 metros): ");
    scanf("%lf", &novoUsuario.altura);

    printf("Vacina (1 para sim, 0 para não): ");
    scanf("%d", &novoUsuario.vacina);

    usuarios[numUsuarios] = novoUsuario;
    numUsuarios++;

    printf("Usuário adicionado com sucesso.\n");
}

void editarUsuario() {
    int id;
    printf("Digite o ID do usuário a ser editado: ");
    scanf("%d", &id);

    getchar();  // Limpar o caractere de nova linha residual no buffer

    int i;
    for (i = 0; i < numUsuarios; i++) {
        if (usuarios[i].id == id) {
            printf("Nome completo: ");
            fgets(usuarios[i].nome, sizeof(usuarios[i].nome), stdin);

            printf("Email: ");
            fgets(usuarios[i].email, sizeof(usuarios[i].email), stdin);

            printf("Sexo (Feminino, Masculino, Indiferente): ");
            fgets(usuarios[i].sexo, sizeof(usuarios[i].sexo), stdin);

            printf("Endereço: ");
            fgets(usuarios[i].endereco, sizeof(usuarios[i].endereco), stdin);

            printf("Altura (entre 1 e 2 metros): ");
            scanf("%lf", &usuarios[i].altura);

            printf("Vacina (1 para sim, 0 para não): ");
            scanf("%d", &usuarios[i].vacina);

            printf("Usuário editado com sucesso.\n");
            return;
        }
    }

    printf("Usuário não encontrado.\n");
}

void excluirUsuario() {
    int id;
    printf("Digite o ID do usuário a ser excluído: ");
    scanf("%d", &id);

    int i, posicao = -1;
    for (i = 0; i < numUsuarios; i++) {
        if (usuarios[i].id == id) {
            posicao = i;
            break;
        }
    }

    if (posicao != -1) {
        for (i = posicao; i < numUsuarios - 1; i++) {
            usuarios[i] = usuarios[i + 1];
        }

        numUsuarios--;
        printf("Usuário excluído com sucesso.\n");
    } else {
        printf("Usuário não encontrado.\n");
    }
}

void buscarUsuarioPorEmail() {
    char email[MAX_EMAIL_LENGTH];
    printf("Digite o email do usuário a ser buscado: ");
    fgets(email, sizeof(email), stdin);

    int i;
    for (i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            printf("Usuário encontrado:\n");
            printf("ID: %d\n", usuarios[i].id);
            printf("Nome completo: %s", usuarios[i].nome);
            printf("Email: %s", usuarios[i].email);
            printf("Sexo: %s", usuarios[i].sexo);
            printf("Endereço: %s", usuarios[i].endereco);
            printf("Altura: %.2lf\n", usuarios[i].altura);
            printf("Vacina: %s\n", usuarios[i].vacina ? "Sim" : "Não");
            return;
        }
    }

    printf("Usuário não encontrado.\n");
}

void imprimirUsuarios() {
    int i;
    for (i = 0; i < numUsuarios; i++) {
        printf("Usuário %d:\n", usuarios[i].id);
        printf("Nome completo: %s", usuarios[i].nome);
        printf("Email: %s", usuarios[i].email);
        printf("Sexo: %s", usuarios[i].sexo);
        printf("Endereço: %s", usuarios[i].endereco);
        printf("Altura: %.2lf\n", usuarios[i].altura);
        printf("Vacina: %s\n", usuarios[i].vacina ? "Sim" : "Não");
        printf("------------------------\n");
    }
}

void fazerBackup() {
    FILE *arquivo = fopen("backup.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de backup.\n");
        return;
    }

    int i;
    for (i = 0; i < numUsuarios; i++) {
        fprintf(arquivo, "%d\n", usuarios[i].id);
        fprintf(arquivo, "%s", usuarios[i].nome);
        fprintf(arquivo, "%s", usuarios[i].email);
        fprintf(arquivo, "%s", usuarios[i].sexo);
        fprintf(arquivo, "%s", usuarios[i].endereco);
        fprintf(arquivo, "%.2lf\n", usuarios[i].altura);
        fprintf(arquivo, "%d\n", usuarios[i].vacina);
    }

    fclose(arquivo);
    printf("Backup realizado com sucesso.\n");
}

void restaurarBackup() {
    FILE *arquivo = fopen("backup.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de backup não encontrado.\n");
        return;
    }

    numUsuarios = 0;
    while (!feof(arquivo) && numUsuarios < MAX_USERS) {
        Usuario novoUsuario;

        fscanf(arquivo, "%d", &novoUsuario.id);
        fgetc(arquivo);  // Ler o caractere de nova linha

        fgets(novoUsuario.nome, sizeof(novoUsuario.nome), arquivo);
        fgets(novoUsuario.email, sizeof(novoUsuario.email), arquivo);
        fgets(novoUsuario.sexo, sizeof(novoUsuario.sexo), arquivo);
        fgets(novoUsuario.endereco, sizeof(novoUsuario.endereco), arquivo);

        fscanf(arquivo, "%lf", &novoUsuario.altura);
        fscanf(arquivo, "%d", &novoUsuario.vacina);

        usuarios[numUsuarios] = novoUsuario;
        numUsuarios++;
    }

    fclose(arquivo);
    printf("Restauração realizada com sucesso.\n");
}

int main() {
    srand(time(NULL));

    char opcao;
    do {
        printf("Selecione uma opção:\n");
        printf("1. Adicionar usuário\n");
        printf("2. Editar usuário\n");
        printf("3. Excluir usuário\n");
        printf("4. Buscar usuário por email\n");
        printf("5. Imprimir todos os usuários\n");
        printf("6. Fazer backup dos usuários\n");
        printf("7. Restaurar dados a partir do backup\n");
        printf("8. Sair\n");
        printf("Opção: ");
        scanf(" %c", &opcao);
        getchar();  // Limpar o caractere de nova linha residual no buffer

        switch (opcao) {
            case '1':
                adicionarUsuario();
                break;
            case '2':
                editarUsuario();
                break;
            case '3':
                excluirUsuario();
                break;
            case '4':
                buscarUsuarioPorEmail();
                break;
            case '5':
                imprimirUsuarios();
                break;
            case '6':
                fazerBackup();
                break;
            case '7':
                restaurarBackup();
                break;
            case '8':
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("------------------------\n");
    } while (opcao != '8');

    return 0;
}


