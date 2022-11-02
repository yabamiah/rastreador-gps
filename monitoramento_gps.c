//#include <gprs.h>
#include <string.h>
//================================================
// Variaveis globais
signed int      latitude, longitude ;
int i;
bool solicitacao_coleta = false;
bool solicitacao_envio = false;
//=======================



void novo_intervalo() { // interrupção para a inserção de um novo intervalo 
    INTERRUPT_GlobalInterruptDisable();

}

void coleta_dados(){// recebimento dos dados do gps atraves da comunicação spi


}

void conectar_gsm(String cmd, char *res) { // função para conectar o gsm

    while(1) {
    Serial.println(cmd);
    Serial1.println(cmd);
    delay(2000);

    while(Serial1.available() > 0) { // se houver dados na serial1

        if(Serial1.find(res)) { // se encontrar a resposta
            delay(1000);
            return;
        }
    }
    delay(1000);
    }
}

void iniciar_gsm() {// inicialização do gsm
    conectar_gsm("AT", "OK");
    conectar_gsm("AT+CPIN?", "READY"); // Não precisa de senha
}

// Função para se comunicar com a operadora
void gms_connect_gprs() { // conecta ao GPRS
    conectar_gsm("AT+CREG?", "OK"); // verifica se o módulo está registrado na rede

    conectar_gsm("AT+CGATT=1", "OK"); // ativa o GPRS

    conectar_gsm("AT+SAPBR=1,1", "OK"); // ativa o contexto GPRS 

    conectar_gsm("AT+SAPBR=2,1", "OK"); // consulta o contexto GPRS 

    Serial1.println("AT+CIFSR"); // consulta o IP
    delay(1000);
}

// Exemplo de função utilizando o método GET
void envio_dados(void){// envio dos dados coletados do gps atraves da comunação usart
    printf("AT+HTTPINIT\r\n"); // inicializa o HTTP
    delay_ms(1000);

    printf("AT+HTTPPARA=\"URL\",https://github.com/yabamiah/rastreador-gps\r\n"); // define a URL     
    delay_ms(50);

    printf("AT+HTTPPARA=\"CID\",1\r\n"); // finaliza a configuração do HTTP
    delay_ms(2000);

    printf("AT+HTTPACTION=0\r\n"); // gera uma requisição HTTP
    delay_ms(3000);

    printf("AT+HTTPTERM\r\n"); // finaliza o HTTP
    delay_ms(3000);

}


void main(void){
    // Inicia o dispositivo
    SYSTEM_Initialize();
    // Habilita as Interrup��es Globais
    INTERRUPT_GlobalInterruptEnable();
    // Habilita as Interrup��es por Perif�ricos
    INTERRUPT_PeripheralInterruptEnable();

}