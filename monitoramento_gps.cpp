//#include <gprs.h>
#include <string>
#include <iostream>

using namespace std;

//================================================
// Variaveis globais
signed int      latitude, longitude ;
int i;
bool solicitacao_coleta = false;
bool solicitacao_envio = false;
string serverIP, server, uri, port, sunInfluence, location; 
//=======================



void novo_intervalo() { // interrupção para a inserção de um novo intervalo 
    INTERRUPT_GlobalInterruptDisable();

}

void coleta_dados(){// recebimento dos dados do gps atraves da comunicação spi


}

void conectar_gsm(string cmd, char *res) { // função para conectar o gsm

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

// Função para iniciar a conexão TCP/IP
void iniciar_conexao_tcp() {
    conectar_gsm("AT+CIPSHUT", "SHUT OK"); // desliga a conexão TCP
    conectar_gsm("AT+CIPMUX=0", "OK"); // ativa o modo de conexão de um único IP
    gms_connect_gprs();
    conectar_gsm("AT+CIICR", "OK"); // ativa a conexão TCP
    conectar_gsm("AT+CIFSR", "OK"); // mostra o IP local
    conectar_gsm("AT+CIPSTART=1,\"TCP\",\"" + serverIP + "\",80", "CONNECT OK");
}

// Função para se comunicar com a operadora e iniciar a conexão TCP
void gms_connect_gprs() { // conecta ao GPRS
    conectar_gsm("AT+CREG?", "OK"); // verifica se o módulo está registrado na rede
    conectar_gsm("AT+CGATT=1", "OK"); // ativa o GPRS
    conectar_gsm("AT+CSTT=\"gprs.timbrasil.com.br\",\"tim\",\"tim\"", "OK"); // Exemplo configura o APN
    delay(1000);
}

// Exemplo de função utilizando TCP/IP
void envio_dados(void){// envio dos dados coletados do gps atraves da comunação usart
    iniciar_gsm();
    iniciar_conexao_tcp();

    if (Serial1.find("OK")) {
        Serial.println("Conectado ao servidor");
        delay(2000);

        // Exemplo de postRequest
        String postRequest = "POST " + uri + "?location=" + "\'" + location + "\'" +
        "&sun_influence=" + "\'" + sunInfluence + "\'" + "&module_name=" + "\'" + moduleName + "\'" + " 
        HTTP/1.1\r\nHost: " + server + "\r\n\r\n";

        conectar_gsm("AT+CIPSEND=1," + String(postRequest.length()));

        if(Serial1.available()) { 
            if(Serial1.find(">")) { 
                conectar_gsm("Sending ..", "SEND OK");
                conectar_gsm(postRequest, "SEND OK");
                delay(200);
                if(Serial1.find("SEND OK")) { 
                    conectar_gsm("Data sent", "OK");
                    conectar_gsm("AT+CIPCLOSE=1", "CLOSE OK");
                }
                else {
                    conectar_gsm("Data not sent", "FAIL");
                }
            }
            else {
                conectar_gsm("Error", "ERROR");
            }
        }else {
            conectar_gsm("Nothing received", "FAIL");
        }
    }else {   
        conectar_gsm("TCP connection failed", "FAIL");
    }
}

void receber_dados(){// recebimento dos dados do servidor atraves do modulo gsm
    iniciar_gsm();
    iniciar_conexao_tcp();

    if (Serial1.find("OK")) {
        Serial.println("Conectado ao servidor");
        delay(2000);

        // Exemplo de postRequest
        String postRequest = "GET " + uri + "?location=" + "\'" + location + "\'" +
        "&sun_influence=" + "\'" + sunInfluence + "\'" + "&module_name=" + "\'" + moduleName + "\'" + " 
        HTTP/1.1\r\nHost: " + server + "\r\n\r\n";

        conectar_gsm("AT+CIPSEND=1," + String(postRequest.length()));

        if(Serial1.available()) { 
            if(Serial1.find(">")) { 
                conectar_gsm("Sending ..", "SEND OK");
                conectar_gsm(postRequest, "SEND OK");
                delay(200);
                if(Serial1.find("SEND OK")) { 
                    conectar_gsm("Data sent", "OK");
                    conectar_gsm("AT+CIPCLOSE=1", "CLOSE OK");
                }
                else {
                    conectar_gsm("Data not sent", "FAIL");
                }
            }
            else {
                conectar_gsm("Error", "ERROR");
            }
        }else {
            conectar_gsm("Nothing received", "FAIL");
        }
    }else {   
        conectar_gsm("TCP connection failed", "FAIL");
    }
}


void main(void){
    // Inicia o dispositivo
    SYSTEM_Initialize();
    // Habilita as Interrup��es Globais
    INTERRUPT_GlobalInterruptEnable();
    // Habilita as Interrup��es por Perif�ricos
    INTERRUPT_PeripheralInterruptEnable();

}