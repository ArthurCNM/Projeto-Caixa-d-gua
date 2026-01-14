#define TRIG_PIN 6
#define ECHO_PIN 7
#define BOMBA_PIN 8

#define NIVEL_CHEIO_CM 40
#define NIVEL_VAZIO_CM 130

float distancia;
long duracao;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BOMBA_PIN, OUTPUT);

  Serial.begin(9600);

  // Inicia com a lâmpada desligada
  digitalWrite(BOMBA_PIN, HIGH);  
}

void loop() {
  // Medição da distância
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duracao = pulseIn(ECHO_PIN, HIGH);
  distancia = duracao * 0.034 / 2;

  Serial.print("Distância até a água: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Controle da bomba/lâmpada (considerando relé ativo baixo)
  if (distancia > NIVEL_VAZIO_CM) {
    digitalWrite(BOMBA_PIN, LOW);  // Liga a bomba
    Serial.println("BOMBA LIGADA");
  } else if (distancia < NIVEL_CHEIO_CM) {
    digitalWrite(BOMBA_PIN, HIGH); // Desliga a bomba
    Serial.println("BOMBA DESLIGADA");
  }

  delay(1000);
}