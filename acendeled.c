void inicio();

void (*isr[])()__attribute__ ((section(".vetor")))={ // Definição do interrupt
        (void (*)())0x20020000;                      //
        inicio
};

void inicio(){
        *((int*)(0x40023800 + 0x30)) = 0x08;         // Habilita PORTD
        *((int*)(0x40020C00 + 0x00)) = 0x01000000;   // configura o modo de direção como output
        *((int*)(0x40020C00 + 0x04)) = 0x00000000;   // configura o tipo de da porta como output push-pull (reset state)
        *((int*)(0x40020C00 + 0x08)) = 0x00000000;   // configura a velocidade do output para low speed
        *((int*)(0x40020C00 + 0x0C)) = 0x00000000;   // configura a porta para no pull-up, pull-down
        int ligado = 0x1000;                         // ligar led
        int desligado = 0x0000;                      // desligar led
        int i;                                       //
        int *ptr = (int*)(0x40020C00 + 0x14);        // GPIO_ODR
loop:
        i = 800000;                                  //
        *ptr = ligado;                               // liga led até que i chegue a 0
        while(i--);                                  //
        *ptr = desligado;                            // desliga led
        i = 800000;                                  //
        while(i--);                                  // Mantém o led desligado até i chegar a 0
        goto loop;                                   // Repete o processo
}
