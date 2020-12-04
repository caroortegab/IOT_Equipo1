#define samp_siz 4 //toma los primeros 4 valores
#define rise_threshold 5  //para en el 5 para procesar los anteriores
//Pulse Monitor Test Script
int sensorPin = 0;

void setup() {
  Serial.begin(9600);
}

void loop(){
  float reads[samp_siz], sum; //suma todos los valores obtenidos del promedio de 4
  long int now, ptr;
  float last, reader, start;
  float first, second, third, before, print_value; //variables helpers
  bool rising;
  int rise_count;
  int n;
  long int last_beat;
  for(int i=0; i<samp_siz; i++){  
    reads[i] = 0;
   }
   sum = 0;
   ptr = 0;//puntero

   while(1)
   {
    //calculate an average of the sensor
    //during a 20 ms period(this will eliminate
    //the 50 Hz noise caused by the electric light)
    n=0;
    start = millis(); //cambias a milisegundos
    reader = 0.; //toma los valores que se vayan leyendo del sensorPin
    do
    {
      reader += analogRead(sensorPin);
      n++;
      now=millis(); //compara los miliseg con lo que empezamos y con los que tenemos ahorita
    }
    while (now < start + 20);
    reader /= n; //obtener el promedio
    //Add the newest measurement to an array
    //and substract the oldest measurement from the array
    //to maintain a sum of last measurements
    sum -= reads[ptr];
    sum += reader;
    reads[ptr] = reader;
    last = sum / samp_siz;
    //now last holds the average of the values in the array
    //check for a rising curve (=a heart beat)
    if(last > before)
    {
      rise_count++;
      if (!rising && rise_count > rise_threshold)
      {
        //Ok,we detected a rising curve->this implies a heartbeat
        //Record the time since last beat, keep track of the 2 previous
        //times(first,second,third) to get a weighed average
        //The rising flag prevents us from detecting the same rise
        //more than once.
        rising=true;
        first=millis() - last_beat;

        print_value = 60000. / (0.4 * first + 0.3 * second + 0.3 *third);

        Serial.print(print_value);
        Serial.print('\n');
        third = second;
        second = first;
      }
    }
    else{
      //Ok, the curve is falling
      rising = false;
      rise_count = 0;
    }
    before = last;
    ptr++;
    ptr %= samp_siz;
    } 
  }
