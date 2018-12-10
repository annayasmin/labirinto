#ifndef MOTORES_H_
#define MOTORES_H_

// Bibliotecas -----------------------------------------------------------------
#include "Arduino.h"


// DefiniÁ„o dos Pinos ---------------------------------------------------------
#define PWM_E	6	// PWM do motor esquerdo
#define IN2_E	7	// IN2 da ponte H do motor esquerdo
#define IN1_E	8	// IN1 da ponte H do motor esquerdo
#define IN1_D	9	// IN1 da ponte H do motor direito
#define IN2_D	10	// IN2 da ponte H do motor direito
#define PWM_D	11	// PWM do motor direito


/* Função para acionamento dos motores ---------------------------
 * pwm_esquerda e pwm_direita recebem valores entre -255 e 255
 * (valores negativos giram o respectivo motor para trás)
 */
void setMotores(int pwm_esquerda, int pwm_direita)
{
    if(pwm_esquerda < 0)
    {
        pwm_esquerda *= -1;
        
        digitalWrite(IN1_E, LOW);
        digitalWrite(IN2_E, HIGH);
    }
    else
    {
        digitalWrite(IN1_E, HIGH);
        digitalWrite(IN2_E, LOW);
    }
    
    if(pwm_direita < 0)
    {
        pwm_direita *= -1;
        
        digitalWrite(IN1_D, LOW);
        digitalWrite(IN2_D, HIGH);
    }
    else
    {
        digitalWrite(IN1_D, HIGH);
        digitalWrite(IN2_D, LOW);
    }
    
    if(pwm_esquerda > 255) pwm_esquerda = 255;
    if(pwm_direita > 255) pwm_direita = 255;
    
    analogWrite(PWM_E, pwm_esquerda);
    analogWrite(PWM_D, pwm_direita);
}

/* Realiza uma curva a
 * partir de um número em graus
 */
void curva(int angulo) {
    switch (angulo)
    {
        case 90: // Vira para esquerda
            setMotores(-100, 100);
            delay(200);
            setMotores(50,50);
            break;
            
        case -90: // Vira para a direita
            setMotores(100,-100);
            delay(200);
            setMotores(50,50);
            break;
            
        case -180: // Dá meia volta
            setMotores(-100, 100);
            delay(400);
            setMotores(50,50);
            break;
    }
}

void frente(int metros) {
    
    unsigned long t0;
    
    setMotores(100,100);
    
    t0 = millis();
    while((millis() - t0) < (metros * 10))
    {
        setMotores(50,50);
    }
}

#endif /* MOTORES_H_ */
