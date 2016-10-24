void main(void)
{

unsigned char i=0;
unsigned char j=0;

PORTA=0x00;
DDRA=0x00;
PORTB=0x00;
DDRB=0xFF;
PORTD=0x00;
DDRD=0x3F;

while (1)
{
      for(i=0;i<=255;i++){
      PORTB=i;
      delay_ms(50);
      if(PIND.6==1) break;
      }
      if(i>=0 && i<125) 
      {
        PORTD.2=1;      
         if(i>=0&&i<24)
         {
            PORTD.3=0;
            PORTD.4=0;
            PORTD.5=0;
         }
        else if(i>=64 && i<125)
        {
           PORTD.3=1;
           PORTD.4=1;
           PORTD.5=1;
        }
        else
        {
           for(j=0;j<3;j++)
            {
            PORTD.3=0;
            PORTD.4=0;
            PORTD.5=0;
            delay_ms(1000);
            PORTD.3=1;
            PORTD.4=1;
            PORTD.5=1;
            delay_ms(1000);
            }
        }
      }
      
      else 
      {
        PORTD.2=0;
        PORTD.3=0;
        PORTD.4=0;
        PORTD.5=0;
      }
}
  
      
}
