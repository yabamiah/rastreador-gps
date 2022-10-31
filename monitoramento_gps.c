
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

void envio_dados(){// envio dos dados coletados do gps atraves da comunação usart


}


void main(void){
    // Inicia o dispositivo
    SYSTEM_Initialize();
    // Habilita as Interrup��es Globais
    INTERRUPT_GlobalInterruptEnable();
    // Habilita as Interrup��es por Perif�ricos
    INTERRUPT_PeripheralInterruptEnable();

}