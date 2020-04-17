#define ENA 11
#define IN1 10
#define IN2 9
#define ENB 5
#define IN3 6
#define IN4 7
#define LUZ 3
#define CLAXON 2
#define NUMCOMANDOS 7;

// Instrucciones permitidas: STOP, ADELANTE, ATRAS, IZQUIERDA, DERECHA, CLAXON Y LUCES
String comandos[] = {"ST", "AD", "AT", "IZ", "DE", "CL", "LU"};

void setup() {
  Serial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);    
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LUZ, OUTPUT);
  pinMode(CLAXON, OUTPUT);
  
 // analogWrite(ENA, 0);
 // analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(LUZ, LOW);
  digitalWrite(CLAXON, LOW);
  
  // Indicador visual de OK
  digitalWrite(LED_BUILTIN, HIGH);
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  String msg;
  String comando;
  int accion; 
  byte val;

  if (Serial.available()) {
   msg=Serial.readString();  
   comando = msg.substring(0,2);
   comando.toUpperCase(); 
   accion = msg.substring(2).toInt(); // 0 apagar 1 encender 
   
   Serial.println(comando);
   Serial.println(accion);

   if (comando.equals("ST")) 
      motoresFrenar();
   else if (comando.equals("AD")) 
      motoresAdelante(255);
   else if (comando.equals("AT")) 
      motoresAtras(255);
   else if (comando.equals("IZ")) 
      motoresIzquierda(255);
   else if (comando.equals("DE")) 
      motoresDerecha(255);
   else if (comando.equals("CL")) 
      claxon(); // NO IMPLEMENTADO EL CLAXON EN ROBOT AZUL
   else if (comando.equals("LU")) {
      if (accion==1) 
        luzON(); 
      else  
        luzOFF();  
   }
  }   
}

bool comandoValido(String comando) {  
  int i;
  for (i=0;i<7;i++) {
      if (comando.equals(comandos[i]))
      return true; 
  }
  return false;
}

void motoresAdelante(int motorSpeed) { 
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);  
}
 
void motoresAtras(int motorSpeed) {
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);      
}

void motoresIzquierda(int motorSpeed) { 
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  
}

void motoresDerecha(int motorSpeed) { 
  analogWrite(ENA, motorSpeed);  
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);  
}

void motoresFrenar () {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);   
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);   
}

void luzON() {  
  Serial.println("LUZ_ON");
  digitalWrite(LUZ, HIGH);
}

void luzOFF() {  
  digitalWrite(LUZ, LOW);
}

void claxon() {
  digitalWrite(CLAXON, HIGH);
  delay(5000);
  digitalWrite(CLAXON,LOW);
}
