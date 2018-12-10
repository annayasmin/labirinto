#ifndef SENSORES_H_
#define SENSORES_H_

// Bibliotecas -----------------------------------------------------------------
#include "Arduino.h"


// DefiniÁ„o dos Pinos ---------------------------------------------------------
#define FE_RECEPTOR	A0	// Fototransistor frontal esquerdo
#define LE_RECEPTOR	A1	// Fototransistor lateral esquerdo
#define LD_RECEPTOR	A2	// Fototransistor lateral direito
#define FD_RECEPTOR	A3	// Fototransistor frontal direito
#define FE_EMISSOR	A4	// LED frontal esquerdo
#define L_EMISSORES	13	// LEDs laterais
#define FD_EMISSOR	A5	// LED frontal direito


// Constantes ------------------------------------------------------------------
const int16_t ALINHAMENTO_FRONTAL = 300;	// Valor para habilitar o alinhamento pelos sensores frontais

// Vari·veis Externas ----------------------------------------------------------
extern int16_t frontal_esquerdo = 0;
extern int16_t lateral_esquerdo = 0;
extern int16_t lateral_direito = 0;
extern int16_t frontal_direito = 0;

/* Função para leitura dos sensores de parede --------------------
 * Atualiza as leituras dos sensores frontais e laterais.
 * Retorna uma máscara de bits indicando presença (1) ou não (0)
 * de paredes. O bit mais significativo representa a parede da
 * esquerda. Ex.: 011 = presença de parede frontal e direita.
 */
uint8_t getSensoresParede(void)
{
    uint8_t paredes = 0;
    
    frontal_esquerdo = analogRead(FE_RECEPTOR);
    lateral_esquerdo = analogRead(LE_RECEPTOR);
    lateral_direito = analogRead(LD_RECEPTOR);
    frontal_direito = analogRead(FD_RECEPTOR);
    
    // Registra o tempo atual
    unsigned long t0 = micros();
    
    // Sensor frontal esquerdo
    digitalWrite(FE_EMISSOR, HIGH);
    while((micros() - t0) < 60);
    frontal_esquerdo = analogRead(FE_RECEPTOR) - frontal_esquerdo;
    digitalWrite(FE_EMISSOR, LOW);
    if(frontal_esquerdo < 0) frontal_esquerdo = 0;
    while((micros() - t0) < 140);
    
    // Sensor frontal direito
    digitalWrite(FD_EMISSOR, HIGH);
    while((micros() - t0) < 200);
    frontal_direito = analogRead(FD_RECEPTOR) - frontal_direito;
    digitalWrite(FD_EMISSOR, LOW);
    if(frontal_direito < 0) frontal_direito = 0;
    while((micros() - t0) < 280);
    
    // Sensores laterais
    digitalWrite(L_EMISSORES, HIGH);
    while((micros() - t0) < 340);
    lateral_esquerdo = analogRead(LE_RECEPTOR) - lateral_esquerdo;
    lateral_direito = analogRead(LD_RECEPTOR) - lateral_direito;
    digitalWrite(L_EMISSORES, LOW);
    if(lateral_esquerdo < 0) lateral_esquerdo = 0;
    if(lateral_direito < 0) lateral_direito = 0;
    
    // Realiza a máscara de bits
    if(frontal_esquerdo > ALINHAMENTO_FRONTAL || frontal_direito > ALINHAMENTO_FRONTAL)
    {
        paredes |= 0b010;
    }
    
    if(lateral_esquerdo > ALINHAMENTO_FRONTAL)
    {
        paredes |= 0b100;
    }
    
    if(lateral_direito > ALINHAMENTO_FRONTAL)
    {
        paredes |= 0b001;
    }
    
    return paredes;
}


#endif /* SENSORES_H_ */
