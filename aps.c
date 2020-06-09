//Autor: Erick Martins Poleto
/*Implementação, etapa 1: elaborar a lógica, etapa 2: criar estruturas, variáveis static e funções
    etapa 3: testar o código com alguns cenários
*/

//para rodar basta usar o comando "./aps", ou recompilar com 'clang ./aps.c' e depois './a.out'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int preencheCatalogo();
static int preenchePedidos();

static int escolhaPedidos();
static int adicionaPedidos(int codigo, int quantidade);
static int finalizarPedido();
static int calcularFrete();
static int calcularImpostos();
static int formaDePagamento();
static int valores();
static int valorTotal();
static int lista();

typedef struct{

    int codigo;
    char nome[30];
    float preco;
    float precoAcima;

} Catalogo;

static Catalogo catalogo[5];

typedef struct{

    int codigo;
    char nome[30];
    float preco;
    int quantidade;

} Pedidos;

static Pedidos pedidos[5];

static float Total;
static float Frete;
static float Imposto;
static float Percentual;
static float TotalPedidoFinal;

int main(void){

    preencheCatalogo();
    preenchePedidos();

    int opcao = 0;

    while(opcao != 6){

        printf("1 - Fazer pedido\n");
        printf("2 - Calcular o valor da entrega\n");
        printf("3 - Calcular impostos\n");
        printf("4 - Forma de pagamento\n");
        printf("5 - Visualizar pedido\n");
        printf("6 - Sair do programa\n");
        printf("escolha uma opção: ");
        scanf("%d", &opcao);

        if(opcao < 1 || opcao > 6){
            printf("opção inválida");
            break;
        }

        switch(opcao){
            case 1:
                preenchePedidos();
                escolhaPedidos();
                break;

            case 2:
                calcularFrete();
                break;
            case 3:
                calcularImpostos();
                break;
            case 4:
                formaDePagamento();
                break;
            case 5:
                valores();
                break;
        }

    }

}

int valores(){
    TotalPedidoFinal = Frete + Imposto + Percentual + Total;
    lista();
    printf("valor do frete: R$%.2f\n", Frete);
    printf("valor do pedido com impostos: R$%.2f\n", Imposto + Total);
    printf("valor do percentual de custos financeiros: R$%.2f\n", Percentual);

    printf("valor total do pedido com custos: R$%.2f\n", TotalPedidoFinal);
    return 0;
}

int formaDePagamento(){

    int codigo;
    char confirmar = '\0';

    if(pedidos[0].codigo == 0){
        printf("sem pedidos\n");
        return 0;
    }

    if(Percentual > 0){
        printf("Percentual: R$%.2f\n", Percentual);
        return 0;
    }

    printf("cod. forma de pagamento ---   Forma de pagamento           --- valor percentual\n ");
    printf("       1               ---   Em dinheiro                  --- 0/\n");
    printf("        2               ---   Cartão de débito             --- 2/\n");
    printf("        3               ---   Cartão de crédito em 1x      --- 5/\n");
    printf("        4               ---   Cartão de crédito em até 6x  --- 10/\n");
    printf("escolha uma forma de pagamento: ");
    scanf("%d", &codigo);

    if(codigo == 1){
        Percentual = 0;
        printf("percentual aplicado: R$0\n");
        printf("valor do pedido com percentual: R$%.2f\n", Total + Percentual);
    }else if(codigo == 2){
        Percentual = (Total * 2)/ 100;
        printf("percentual aplicado: R$%.2f\n", Percentual);
        printf("valor do pedido com percentual: R$%.2f\n", Total + Percentual);
    }else if(codigo == 3){
        Percentual = (Total * 5)/ 100;
        printf("percentual aplicado: R$%.2f\n", Percentual);
        printf("valor do pedido com percentual: R$%.2f\n", Total + Percentual);
    }else{
        Percentual = (Total * 10)/ 100;
        printf("percentual aplicado: R$%.2f\n", Percentual);
        printf("valor do pedido com percentual: R$%.2f\n", Total + Percentual);
    }

    while(confirmar != 's' || confirmar != 'n'){

        printf("confirmar método de pagamento?(s/n): ");
        scanf(" %c", &confirmar);

        if(confirmar == 's'){
            break;
        }else if(confirmar == 'n'){
            Percentual = 0;
            return formaDePagamento();
        }
    }
    lista();
    return 0;

}


int calcularImpostos(){

    if(pedidos[0].codigo == 0){
        printf("sem pedidos\n");
        return 0;
    }
    Imposto = (Total * 20)/ 100;
    printf("o valor do imposto é de: R$%.2f\n", Imposto);
    printf("o valor total do pedido com imposto é de: R$%.2f\n ", Imposto + Total);
    return 0;
}

int calcularFrete(){

    int codigo;
    char confirmar = '\0';

    if(pedidos[0].codigo == 0){
        printf("sem pedidos\n");
        return 0;
    }

    if(Frete > 0){
        printf("valor do frete: R$%.2f\n", Frete);
        return 0;
    }


    printf("cod. tipo frete --- frete     --- valor pedido     --- valor frete\n");

    printf("1 ---           entrega em 2h --- <= R$50          --- R$10\n");
    printf("1 ---           entrega em 2h --- > R$50 e <=R$100 --- R$20\n");
    printf("1 ---           entrega em 2h --- > R$100          --- 20/ do valor total\n");
    printf("2 ---           entrega em 2d --- qualquer valor   --- R$10\n");
    printf("escolha uma forma de entrega: ");
    scanf("%d", &codigo);

    if(codigo < 1 || codigo > 2){
        return calcularFrete();
    }

    if(codigo == 1){
        lista();
        if(Total <= 50){
            Frete = 10;
            printf("valor do frete: R$10\n");
            printf("valor total: %.2f\n", Total + Frete);
        }else if(Total > 50 && Total <= 100){
            Frete = 20;
            printf("valor do frete: R$20\n");
            printf("valor total: %.2f\n", Total + Frete);
        }else if(Total > 100){
            Frete = (Total * 20) / 100;
            printf("valor do frete: R$%.2f\n", Frete);
            printf("valor total: R$%.2f\n", Total + Frete);
        }

    }else if(codigo == 2){
        lista();
        Frete = 10;
        printf("valor do frete: R$10\n");
        printf("valor total: R$%.2f\n", Total + Frete);
    }

    while(confirmar != 's' || confirmar != 'n'){

        printf("confirmar frete?(s/n): ");
        scanf(" %c", &confirmar);

        if(confirmar == 's'){
            break;
        }else if(confirmar == 'n'){
            Frete = 0;
            return calcularFrete();
        }
    }
    return 0;

}


int escolhaPedidos(){
    int codigo = 0;
    char confirmar = '\0';
    int quantidade = 0;

    printf("codigo --- nome --- preco\n");
    for(int lista = 0; lista < 5; lista++){
        printf("     %d --- %s --- %.2f\n", catalogo[lista].codigo, catalogo[lista].nome, catalogo[lista].preco);
    }

    printf("escolha um produto: ");
    scanf("%d", &codigo);

    if(codigo < 1 || codigo > 6){
        printf("produto inexistente\n");
        return escolhaPedidos();
    }

    printf("escolha uma quantidade: ");
    scanf("%d", &quantidade);

    adicionaPedidos(codigo, quantidade);

    while(confirmar != 'n' || confirmar != 's'){

        printf("deseja finalizar o pedido?(s/n) ");
        scanf(" %c", &confirmar);
        if(confirmar == 's'){

            return finalizarPedido();

        }else if(confirmar == 'n'){

            return escolhaPedidos();

        }
    }
    return 0;

}

int adicionaPedidos(int codigo, int quantidade){


    for(int verificaAdiciona = 0; verificaAdiciona < 5; verificaAdiciona++){
        if(pedidos[verificaAdiciona].codigo != 0){
            if(pedidos[verificaAdiciona].codigo == codigo){
                pedidos[verificaAdiciona].quantidade += quantidade;
                return 0;
            }
        }else{
            break;
        }
    }

    for(int adiciona = 0; adiciona < 5; adiciona++){
        if(pedidos[adiciona].codigo == 0){
            pedidos[adiciona].codigo = catalogo[codigo - 1].codigo;
            strcpy(pedidos[adiciona].nome, catalogo[codigo - 1].nome);
            pedidos[adiciona].quantidade = quantidade;
            return 0;
        }
    }
    return 0;
}


int finalizarPedido(){
    char escolha = '\0';
    while(escolha != 'f' || escolha != 'r'){

        printf("finalizar pedido ou repetir entrada? (f para finalizar ou r para repetir): ");
        scanf(" %c", &escolha);

        if(escolha == 'r'){

            preenchePedidos();
            return escolhaPedidos();
        }
        if(escolha == 'f'){
            valorTotal();
            return lista();
        }
    }
    return 0;
}

int valorTotal(){

    for(int listaPedidos = 0; listaPedidos < 5; listaPedidos++){
        if(pedidos[listaPedidos].codigo == 0){
            break;
        }
        for(int listaCatalogo = 0; listaCatalogo < 5; listaCatalogo++){
            if(pedidos[listaPedidos].codigo == catalogo[listaCatalogo].codigo){
                if(pedidos[listaPedidos].quantidade > 5){
                    pedidos[listaPedidos].preco = catalogo[listaCatalogo].precoAcima * pedidos[listaPedidos].quantidade;
                    return 0;
                }
                pedidos[listaPedidos].preco = catalogo[listaCatalogo].preco * pedidos[listaPedidos].quantidade;
            }
        }
    }

    return 0;

}

int lista(){
    Total = 0;
    for(int listaPedidos = 0; listaPedidos < 5; listaPedidos++){
        if(pedidos[listaPedidos].codigo == 0){
            break;
        }
        printf("codigo: %d, nome: %s , quantidade: %d, valor: R$%.2f\n", pedidos[listaPedidos].codigo,
                                                          pedidos[listaPedidos].nome,
                                                          pedidos[listaPedidos].quantidade,
                                                          pedidos[listaPedidos].preco);
        Total += pedidos[listaPedidos].preco;
    }
    printf("Valor total: R$%.2f\n", Total);
    return 0;
}

int preencheCatalogo(){

    catalogo[0].codigo = 1;
    strcpy(catalogo[0].nome, "camisa");
    catalogo[0].preco = 3.00;
    catalogo[0].precoAcima = 2.50;

    catalogo[1].codigo = 2;

    strcpy(catalogo[1].nome, "calça");
    catalogo[1].preco = 5.00;
    catalogo[1].precoAcima = 4.00;

    catalogo[2].codigo = 3;

    strcpy(catalogo[2].nome, "bermudas");
    catalogo[2].preco = 10.00;
    catalogo[2].precoAcima = 9.00;

    catalogo[3].codigo = 4;

    strcpy(catalogo[3].nome, "celular");
    catalogo[3].preco = 20.00;
    catalogo[3].precoAcima = 15.00;

    catalogo[4].codigo = 5;

    strcpy(catalogo[4].nome, "televisão");
    catalogo[4].preco = 100.00;
    catalogo[4].precoAcima = 80.00;

    return 0;
}

int preenchePedidos(){

    for(int preenche = 0; preenche < 5; preenche++){
        pedidos[preenche].codigo = 0;
        strcpy(pedidos[preenche].nome, "");
        pedidos[preenche].preco = 0;
        pedidos[preenche].quantidade = 0;
    }
    return 0;
}