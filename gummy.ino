#include <Servo.h> //INCLUSÃO DA BIBLIOTECA NECESSÁRIA \newline
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //PINOS UTILIZADOS PELO DISPLAY

const int pinoServo = 6; //PINO DIGITAL UTILIZADO PELO SERVO  
const int LM35 = A0; //DEFINE O PINO QUE LERÁ A SAÍDA DO LM35
int buttonPin= 8; //DEFINE O PINO DO BOTÃO
float temperatura1;//VARIÁVEL QUE RECEBE A TEMPERATURA MEDIDA
float temperatura2;
int piezoPin = 9;//DEFINE O PINO DO BUZZER
Servo s; //OBJETO DO TIPO SERVO
int pos; //POSIÇÃO DO SERVO
int cont=0;


void setup ()
{
    lcd.begin(16, 2);//DEFINE O NÚMERO DE LINHAS E COLUNAS DO DISPLAY
    s.attach(pinoServo); //ASSOCIAÇÃO DO PINO DIGITAL AO OBJETO DO TIPO SERVO
    s.write(0); //INICIA O MOTOR NA POSIÇÃO 0º
    pinMode(buttonPin, INPUT);
    Serial.begin(9600); //INICIA A COMUNICAÇÃO SERIAL DO SENSOR LM35
}
void loop()
{
    lcd.clear();//LIMPA A TELA
    lcd.setCursor(0, 0);//POSICIONA O CURSOR DO DISPLAY NA COLUNA 0 DA LINHA 0
    lcd.print("Pronto para uso");//PRINTA A FRASE NO DISPLAY
    lcd.setCursor(0, 1);//POSICIONA O CURSOR DO DISPLAY NA COLUNA 0 DA LINHA 1
    lcd.print("Aperte o botão");//INFORMA O USUÁRIO QUE PODE UTILIZAR O EQUIPAMENTO

    int buttonState = digitalRead(buttonPin);

    if (buttonState == 1){//SE O BOTÃO ESTIVER PRESSIONADO
    //CRIAR FUNÇÃO QUE RECEBE O ESTADO DO PUSHBUTTON E ACIONA O PROJETO
    temperatura1 = (float(analogRead(LM35))*5/(1023))/0.01;//A VARIÁVEL TEMPERATURA RECEBE A SAÍDA DO SENSOR
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Em preparo.");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temperatura1);
    while(cont<30){
        for(pos = 0; pos < 180; pos++){ //PARA "pos" IGUAL A 0, ENQUANTO "pos" MENOR QUE 180, INCREMENTA "pos"
            s.write(pos); //ESCREVE O VALOR DA POSIÇÃO QUE O SERVO DEVE GIRAR
            delay(15); //INTERVALO DE 15 MILISSEGUNDOS
        }
        delay(1000); //INTERVALO DE 1 SEGUNDO
        for(pos = 180; pos >= 0; pos--){ //PARA "pos" IGUAL A 180, ENQUANTO "pos" MAIOR OU IGUAL QUE 0, DECREMENTA "pos"
            s.write(pos); //ESCREVE O VALOR DA POSIÇÃO QUE O SERVO DEVE GIRAR
            delay(15); //INTERVALO DE 15 MILISSEGUNDOS
        }
        cont++;
    } 
    temperatura2 = (float(analogRead(LM35))*5/(1023))/0.01;
    //PRINTA INFORMANDO QUE ESTÁ PRONTO NO DISPLAY
    delay(1000);
    lcd.clear();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Pronto para o consumo");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura2);
    
    tone(piezoPin, 1000, 500);
    delay(1000);
    
    }
}