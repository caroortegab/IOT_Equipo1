int senal = A0;  //Conectar en el pin analogico A0 
int valor;
int ledPin=8;

void setup(){
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);  //Activar puerto serial 
  }
  


void loop(){
  valor = analogRead(senal); //Lectura señal anañogica  
  if(valor>50){
    Serial.println(valor);
    digitalWrite(ledPin,1);
   }
   else{
    Serial.println(0); 
    digitalWrite(ledPin,0);
   }
   delay(50);
  }


  

  /*
  if(valor >= 30 && 50 >= valor){       
  Serial.println("No hay pulso");    
  }   
  
  else{        
  Serial.println("Hay pulso");   
  } */
