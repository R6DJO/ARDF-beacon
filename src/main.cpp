// #include <Arduino.h>

#include <avr/io.h>
#include <util/delay.h>

/*
PORTA 0...2
B000 MOT
B001 MOE
B010 MOИ
B011 MOC
B100 MOX
B101 MO5

*/
// #define CW 13
#define DIT 60
#define DOT 3 * DIT
#define DC 2 * DIT
#define DW 2 * DIT

void pin_cw_up()
{
  PORTB |= 0x20;
}

void pin_cw_down()
{
  PORTB &= 0xdf;
}

void dit()
{
  pin_cw_up();
  _delay_ms(DIT);
  pin_cw_down();
  _delay_ms(DIT);
}

void dot()
{
  pin_cw_up();
  _delay_ms(DOT);
  pin_cw_down();
  _delay_ms(DIT);
}

void M()
{
  dot();
  dot();
  _delay_ms(DC);
}

void O()
{
  dot();
  _delay_ms(DIT);
  dot();
  _delay_ms(DIT);
  dot();
  _delay_ms(DC);
}

void T()
{
  dot();
  _delay_ms(DC);
}

void FOX(int n)
{
  M();
  O();
  for (int i = 0; i < n; i++)
  {
    dit();
  }
  _delay_ms(DW);
}

void BEACON(int b)
{
  switch (b)
  {
  case 0:
    M();
    O();
    T();
    break;
  case 1:
    FOX(1);
    break;
  case 2:
    FOX(1);
    break;
  case 3:
    FOX(1);
    break;
  case 4:
    FOX(1);
    break;
  case 5:
    FOX(1);
    break;
  default:
    M();
    O();
  }
}

// void setup()
// {
// }

// void loop()
// {
//   // put your main code here, to run repeatedly:
//   BEACON(beacon);
//   _delay_ms(DW);
// }

int main()
{
  // uint8_t config = PIND;
  uint8_t beacon = PIND & 0b111;
  uint8_t cycle = PIND >> 3 & 0b111;
  uint8_t start_delay = PIND >> 6 & 0x04;
  bool fast = PIND & 0x01;
  // setup();
  // unsigned long start = millis();
  BEACON(beacon);
  // _delay_ms(start_delay*3600000-(millis()-start));
  // _delay_ms(start_delay*3600000-30*DIT);
  _delay_ms(3600000 * start_delay);
  while(1)
  {
    BEACON(beacon);
  _delay_ms(DW);
  }
}