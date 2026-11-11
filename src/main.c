/////////////////////////////////////////////////////////////////
//**      PROYECTO: Máquina de hacer tragos			  **//
//**      MATERIA: Técnicas Digitales II			     **//
//**      PROFESOR: Ing. Conejeros Cristian			**//
//**							 **//
//**      ESTUDIANTES: Gutiérrez Luciano y Gonza Natalia       **//
//**      ULTIMA FECHA DE EDICIÓN: 4/11/2017 (por estudiantes) **//
/////////////////////////////////////////////////////////////////

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "qwerty.h"
#include "uart0.h"
#include "light_ws2812.h"

struct cRGB led[1];
static uint8_t dato;
int ArmarTrago1 = 0;
int ArmarTrago2 = 0;
int ArmarTrago3 = 0;
int ArmarTrago4 = 0;
int ArmarTrago5 = 0;
int ArmarTrago6 = 0;
int ArmarTrago7 = 0;
int ArmarTrago8 = 0;


int main(void)
{
	uart0_init();
	dato=0;
	int menu=1;
	int iniciacion=0;

	while(1)
	{
		if(!(iniciacion))
		{
			uart0_puts("Inicializando maquina\r");

			GiroLedApagado(0,1,50);
			LED_ENCENDIDO_ON;
			LED_TRAGO1_ON;
			LED_TRAGO2_ON;
			LED_TRAGO3_ON;

			iniciacion=1;
			menu=0;

			BajarActuador(6000,2);
			InitMotor();

			uart0_puts("\n\r¿El vaso se encuentra en la base? [S/N]\r");
			uart0_puts("Su eleccion: \r");
			dato=0;
			dato = uart0_getchar();

			switch(dato)
			{
			case 'N':
				dato=0;
				uart0_puts("\nPor favor, coloque el vaso.\r");
				Timer1_FastPWMinvertido_50hz;
				OCIE1A_Enable;
				Servo180a45(2000);

				uart0_puts("Tiene 10 segundos para colocar el vaso.\r");

				GiroLedLila(1,0,1,0,1);

				Servo45a180(2000);
				OCIE1A_Disable;

				uart0_puts("\n\rIniciando programa...\n\r");

	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");
				break;

			case 'S':
				dato=0;
				menu=0;
				uart0_puts("\n\rIniciando programa...\n\r");
				_delay_ms(5000);

	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");
				break;
				}
		}

		_delay_ms(2000);

		TIRA_VERDE_ON;

		if(!(menu))
		{
			dato=0;
			LED_ENCENDIDO_ON;
			LED_TRAGO1_OFF;
			LED_TRAGO2_OFF;
			LED_TRAGO3_OFF;
			uart0_puts("\n\n\n\rPor favor, seleccione el jugo que quiera:\n\r");
			uart0_puts("1) Jugo 1-2-3.");
			uart0_puts("2) Jugo 1-2.");
			uart0_puts("3) Jugo 2-3.");
			uart0_puts("4) Jugo 1-3.");
			uart0_puts("5) Jugo 1.");
			uart0_puts("6) Jugo 2.");
			uart0_puts("7) Jugo 3.");
			uart0_puts("8) Jugo 4.");
			uart0_puts("9) El vaso no esta en la base.\n");
			uart0_puts("\nSu eleccion: ");
		}

		dato=0;
		dato = uart0_getchar();

		switch(dato)
		{
			case '1':
				dato=0;
				menu = 1;
				iniciacion=1;
				ArmarTrago1=1;
uart0_puts("\n\rEl Trago 1 es una mezcla de jugo de manzana, jugo de anana y jugo de naranja\r");
				uart0_puts("Desea este trago? [S/N]");
				uart0_puts("Su eleccion: ");
				break;

			case '2':
				dato=0;
				menu = 1;
				iniciacion=1;
				ArmarTrago2=1;
		uart0_puts("\n\rEl Trago 2 es una mezcla de jugo de manzana con jugo de anana\r");
				uart0_puts("Desea este trago? [S/N]");
				uart0_puts("Su eleccion: ");
				break;
			case '3':
				dato=0;
				menu = 1;
				iniciacion=1;
				ArmarTrago3=1;
		uart0_puts("\n\rEl Trago 3 es una mezcla de jugo de anana con jugo de naranja\r");
				uart0_puts("Desea este trago? [S/N]");
				uart0_puts("Su eleccion: ");
				break;

			case '4':
				dato=0;
				menu = 1;
				iniciacion=1;
				ArmarTrago4=1;
		uart0_puts("\n\rEl Trago 4 es una mezcla de jugo de manzana con jugo de naranja\r");
				uart0_puts("Desea este trago? [S/N]");
				uart0_puts("Su eleccion: ");
				break;

			case '5':
				dato=0;
				menu = 1;
				iniciacion=1;
				ArmarTrago5=1;
				uart0_puts("\n\rEl Trago 5 es jugo de manzana\r");
				uart0_puts("Desea este trago? [S/N]");
				uart0_puts("Su eleccion: ");
				break;

			case '6':
				dato=0;
				menu = 1;
				iniciacion=1;
				ArmarTrago6=1;
				uart0_puts("\n\rEl Trago 6 es jugo de anana\r");
				uart0_puts("Desea este trago? [S/N]");
				uart0_puts("Su eleccion: ");
				break;

			case '7':
				dato=0;
				menu = 1;
				iniciacion=1;
				ArmarTrago7=1;
				uart0_puts("\n\rEl Trago 7 es jugo de naranja\r");
				uart0_puts("Desea este trago? [S/N]");
				uart0_puts("Su eleccion: ");
				break;

			case '8':
				dato=0;
				menu = 1;
				iniciacion=1;
				ArmarTrago8=1;
				uart0_puts("\n\rEl Trago 8 es jugo de limonada\r");
				uart0_puts("Desea este trago? [S/N]");
				uart0_puts("Su eleccion: ");
				break;

			case '9':
				dato=0;
				menu=0;
				iniciacion=1;
				uart0_puts("Abriendo puerta...");

				Timer1_FastPWMinvertido_50hz;
				OCIE1A_Enable;
				Servo180a45(2000);

				uart0_puts("Tiene 10 segundos para colocar el vaso");

				GiroLedNaranja(1,0,1,0,1);

				Servo45a180(2000);
				OCIE1A_Disable;
				uart0_puts("\n\rVolviendo al menu principal.\r");
				_delay_ms(3000);

	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");
				break;

			case 'N':
				dato=0;
				menu=0;
				iniciacion=1;
				ArmarTrago1 = 0;
				ArmarTrago2 = 0;
				ArmarTrago3 = 0;
				ArmarTrago4 = 0;
				ArmarTrago5 = 0;
				ArmarTrago6 = 0;
				ArmarTrago7 = 0;
				ArmarTrago8 = 0;
				uart0_puts("\n\rVolviendo al menu principal.\r");
				_delay_ms(3000);

	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");
				break;


			case 'S':
				if(ArmarTrago1)
				{
					uart0_puts("Armando primer trago.");
					AscenderBlanco(255,2);

					menu=0;
					iniciacion=0;
					ArmarTrago1 = 0;

					LED_ENCENDIDO_ON;
					TIRA_ROJO_ON;
					InicializarMotorSensor1();
					AscenderBlanco(255,2);
					ServirTrago1(2);
					DescenderBlanco(255,2);

					LED_ENCENDIDO_OFF;
					LED_TRAGO1_ON;
					TIRA_AZUL_ON;
					InicializarMotorSensor2();
					AscenderBlanco(255,2);
					ServirTrago2(2);
					DescenderBlanco(255,2);

					LED_TRAGO1_OFF;
					LED_TRAGO2_ON;
					TIRA_VERDE_ON;
					InicializarMotorSensor3();
					AscenderBlanco(255,2);
					ServirTrago3(2);
					DescenderBlanco(255,2);

					LED_ENCENDIDO_ON;
					LED_TRAGO1_ON;
					LED_TRAGO2_ON;
					LED_TRAGO3_ON;
					AscenderBlanco(255,20);
					InicializarMotorSensor0();
					Timer1_FastPWMinvertido_50hz;
					OCIE1A_Enable;
					Servo180a45(2000);

			uart0_puts("Trago listo, por favor retirar en 10 segundos.\r");

					GiroLedApagado(0,1,4225);

					Servo45a180(2000);
					OCIE1A_Disable;


	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");

					_delay_ms(10000);
				}

				if(ArmarTrago2)
				{
					uart0_puts("Armando segundo trago.");
					AscenderVioleta(255,2);

					menu=0;
					iniciacion=0;
					ArmarTrago2 = 0;

					LED_ENCENDIDO_ON;
					InicializarMotorSensor1();
					TIRA_ROJO_ON;
					AscenderVioleta(255,2);
					ServirTrago1(3);
					DescenderVioleta(255,2);

					LED_ENCENDIDO_OFF;
					LED_TRAGO1_ON;
					InicializarMotorSensor2();
					TIRA_AZUL_ON;
					AscenderVioleta(255,2);
					ServirTrago2(3);
					DescenderVioleta(255,2);

					LED_ENCENDIDO_ON;
					LED_TRAGO1_ON;
					LED_TRAGO2_ON;
					LED_TRAGO3_ON;
					AscenderVioleta(255,20);
					InicializarMotorSensor0();
					Timer1_FastPWMinvertido_50hz;
					OCIE1A_Enable;
					Servo180a45(2000);

			uart0_puts("Trago listo, por favor retirar en 10 segundos.\r");

					GiroLedApagado(0,1,4225);

					Servo45a180(2000);
					OCIE1A_Disable;

	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");

					_delay_ms(10000);
				}

				if(ArmarTrago3)
				{
					uart0_puts("Armando tercer trago.");
					AscenderCeleste(255,2);

					menu=0;
					iniciacion=0;
					ArmarTrago3 = 0;

					LED_ENCENDIDO_OFF;
					LED_TRAGO1_ON;
					InicializarMotorSensor2();
					TIRA_AZUL_ON;
					AscenderCeleste(255,2);
					ServirTrago2(3);
					DescenderCeleste(255,2);

					LED_TRAGO1_OFF;
					LED_TRAGO2_ON;
					InicializarMotorSensor3();
					TIRA_VERDE_ON;
					AscenderCeleste(255,2);
					ServirTrago3(3);
					DescenderCeleste(255,2);

					LED_ENCENDIDO_ON;
					LED_TRAGO1_ON;
					LED_TRAGO2_ON;
					LED_TRAGO3_ON;
					AscenderCeleste(255,2);
					InicializarMotorSensor0();
					Timer1_FastPWMinvertido_50hz;
					OCIE1A_Enable;
					Servo180a45(2000);

			uart0_puts("Trago listo, por favor retirar en 10 segundos.\r");

					GiroLedApagado(0,1,4225);

					Servo45a180(2000);
					OCIE1A_Disable;


	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");

					_delay_ms(10000);
				}

				if(ArmarTrago4)
				{
					uart0_puts("Armando cuarto trago.");
					AscenderAmarillo(255,2);

					menu=0;
					iniciacion=0;
					ArmarTrago4 = 0;

					LED_ENCENDIDO_ON;
					InicializarMotorSensor1();
					TIRA_ROJO_ON;
					AscenderAmarillo(255,2);
					ServirTrago1(3);
					DescenderAmarillo(255,2);

					LED_TRAGO1_OFF;
					LED_TRAGO2_ON;
					InicializarMotorSensor3();
					TIRA_VERDE_ON;
					AscenderAmarillo(255,2);
					ServirTrago3(3);
					DescenderAmarillo(255,2);

					LED_ENCENDIDO_ON;
					LED_TRAGO1_ON;
					LED_TRAGO2_ON;
					LED_TRAGO3_ON;
					AscenderAmarillo(255,20);
					InicializarMotorSensor0();
					Timer1_FastPWMinvertido_50hz;
					OCIE1A_Enable;
					Servo180a45(2000);

			uart0_puts("Trago listo, por favor retirar en 10 segundos.\r");

					GiroLedApagado(0,1,4225);

					Servo45a180(2000);
					OCIE1A_Disable;

	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");

					_delay_ms(10000);
				}

				if(ArmarTrago5)
				{
					uart0_puts("Armando quinto trago.");
					AscenderRojo(255,2);

					menu=0;
					iniciacion=0;
					ArmarTrago5 = 0;

					LED_ENCENDIDO_ON;
					InicializarMotorSensor1();
					TIRA_ROJO_ON;
					AscenderRojo(255,2);
					ServirTrago1(5);
					DescenderRojo(255,2);

					LED_ENCENDIDO_ON;
					LED_TRAGO1_ON;
					LED_TRAGO2_ON;
					LED_TRAGO3_ON;
					AscenderRojo(255,20);
					InicializarMotorSensor0();
					Timer1_FastPWMinvertido_50hz;
					OCIE1A_Enable;
					Servo180a45(2000);

			uart0_puts("Trago listo, por favor retirar en 10 segundos.\r");

					GiroLedApagado(0,1,4225);

					Servo45a180(2000);
					OCIE1A_Disable;

	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");

					_delay_ms(10000);
				}

				if(ArmarTrago6)
				{
					uart0_puts("Armando sexto trago.");
					AscenderVerde(255,2);

					menu=0;
					iniciacion=0;
					ArmarTrago6 = 0;

					LED_ENCENDIDO_OFF;
					LED_TRAGO1_ON;
					InicializarMotorSensor2();
					TIRA_AZUL_ON;
					AscenderVerde(255,2);
					ServirTrago2(5);
					DescenderVerde(255,2);

					LED_ENCENDIDO_ON;
					LED_TRAGO1_ON;
					LED_TRAGO2_ON;
					LED_TRAGO3_ON;
					AscenderVerde(255,20);
					InicializarMotorSensor0();
					Timer1_FastPWMinvertido_50hz;
					OCIE1A_Enable;
					Servo180a45(2000);

			uart0_puts("Trago listo, por favor retirar en 10 segundos.\r");

					GiroLedApagado(0,1,4225);

					Servo45a180(2000);
					OCIE1A_Disable;

	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");

					_delay_ms(10000);
				}

				if(ArmarTrago7)
				{
					uart0_puts("Armando septimo trago.");
					AscenderAzul(255,2);

					menu=0;
					iniciacion=0;
					ArmarTrago7 = 0;

					LED_TRAGO1_OFF;
					LED_TRAGO2_ON;
					InicializarMotorSensor3();
					TIRA_VERDE_ON;
					AscenderAzul(255,2);
					ServirTrago3(5);
					DescenderAzul(255,2);

					LED_ENCENDIDO_ON;
					LED_TRAGO1_ON;
					LED_TRAGO2_ON;
					LED_TRAGO3_ON;
					AscenderAzul(255,20);
					InicializarMotorSensor0();
					Timer1_FastPWMinvertido_50hz;
					OCIE1A_Enable;
					Servo180a45(2000);

			uart0_puts("Trago listo, por favor retirar en 10 segundos.\r");

					GiroLedApagado(0,1,4225);

					Servo45a180(2000);
					OCIE1A_Disable;

	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");

					_delay_ms(10000);
				}

				if(ArmarTrago8)
				{
					uart0_puts("Armando octavo trago.");
					AscenderVerdeAgua(255,2);

					menu=0;
					iniciacion = 0;
					ArmarTrago8 = 0;

					LED_TRAGO3_ON;
					InicializarMotorSensor4();
					TIRA_BLANCA_ON;
					AscenderVerdeAgua(255,2);
					ServirTrago4(6);
					DescenderVerdeAgua(255,2);

					LED_ENCENDIDO_ON;
					LED_TRAGO1_ON;
					LED_TRAGO2_ON;
					LED_TRAGO3_ON;
					AscenderVerdeAgua(255,20);
					InicializarMotorSensor0();
					Timer1_FastPWMinvertido_50hz;
					OCIE1A_Enable;
					Servo180a45(2000);

				uart0_puts("Trago listo, por favor retirar en 10 segundos.\r");

					GiroLedApagado(0,1,4225);

					Servo45a180(2000);
					OCIE1A_Disable;

	uart0_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");

					_delay_ms(10000);
				}
			}
	}
}

