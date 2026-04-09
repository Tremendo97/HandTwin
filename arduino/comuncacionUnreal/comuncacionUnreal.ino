#include <Servo.h>

enum Dedo : uint32_t
{
  Indice = 0,
  Corazon = 1,
  Anular = 2,
  Menique = 3,
  Pulgar = 4, 
  Vacio = 5
};

struct posicion {
  float pos1;
  float pos2;
  Dedo dedo=Menique;
  String toString() {
    //necesita \0 ya que es el seprador que usa el plugin.
    return String(dedo) + ": " + String(pos1) + "," + String(pos2);
  }
};

class Hand{
  public:
    Servo indice1;
    Servo indice2;
    Servo corazon1;
    Servo corazon2;
    Servo anular1;
    Servo anular2;
    Servo menique1;
    Servo menique2;
    Servo pulgar1;
    Servo pulgar2;
  public:
    setHand(){
      
      //asignar los servos a sus salidas
      indice1.attach(13);
      indice2.attach(12);

      corazon1.attach(11);
      corazon2.attach(10);

      anular1.attach(9);
      anular2.attach(8);

      menique1.attach(7);
      menique2.attach(6);

      pulgar1.attach(4);
      pulgar2.attach(5);

      //colocar en la posicion por defecto
      corazon1.write(0);
      corazon2.write(0);

      indice1.write(0);
      indice2.write(0);

      anular1.write(0);
      anular2.write(0);

      menique1.write(0);
      menique2.write(0);

      pulgar1.write(0);
      pulgar2.write(0);
    }
  public:
    void setPosition(posicion posiciones){
      switch (posiciones.dedo) {
        case Indice:
          indice1.write(posiciones.pos1);
          indice2.write(posiciones.pos2);
          break;
        case Corazon:
          corazon1.write(posiciones.pos1);
          corazon2.write(posiciones.pos2);
          break;
        case Anular:
          anular1.write(posiciones.pos1);
          anular2.write(posiciones.pos2);
          break;
        case Menique:
          menique1.write(posiciones.pos1);
          menique2.write(posiciones.pos2);
          break;
        case Pulgar:
          break;
      }
    }
};

posicion pos;
Hand hand;

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(1);

  delay(1000);
  
  hand.setHand();
  // Serial.println(sizeof(posicion));
}

void loop() {
  if (Serial.available() >= sizeof(pos)) {
    // Leemos los bytes directamente en la estructura
    Serial.readBytes((char*)&pos, sizeof(pos));
    hand.setPosition(pos);
    
  }
  Serial.println(pos.toString());
}




