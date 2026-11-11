#include "qwerty.h"
#include "light_ws2812.h"
#include "ws2812_config.h"
#include <avr/io.h>
#include <util/delay.h>

//--------------------PISTON------------------------------------//
//** Si PinEnable está como salida (1): STOP
//** Si PinEnable está como entrada (0): FORWARD

//** Si la lógica es NEGATIVO(-) / POSITIVO(+):
//** Sube: 0 PinDir1 ; 1 PinDir2
//** Baja: 0 PinDir2 ; 1 PinDir1
uint8_t PinDir1 = 0;
uint8_t PinDir2 = 1;
uint8_t PinEnable = 2;
int DistanciaSubida = 0;
int DistanciaBajada = 0;
int Retardo = 0;
//** Con 6000ms llega a tope y retiene


void SubirActuador(int DistanciaSubida,int Retardo)
{
	PISTON_ON;
	PISTONENABLE_OFF;

	PISTON_UP;
	_delay_ms(DistanciaSubida);

	PISTONENABLE_ON;
	_delay_ms(Retardo);

	PISTON_OFF;
}

void BajarActuador(int DistanciaBajada,int Retardo){
	PISTON_ON;
	PISTONENABLE_OFF;

	PISTON_DOWN;
	_delay_ms(DistanciaBajada);

	PISTONENABLE_ON;
	_delay_ms(Retardo);

	PISTON_OFF;
}

void ServirTrago1(int Veces){
	for(int i=1;i<=Veces;i++)
	{
	SubirActuador(4400,2800);
	SubirActuador(900,2800);
	BajarActuador(6000,5);
	}
}

void ServirTrago2(int Veces){
	for(int i=1;i<=Veces;i++)
	{
		SubirActuador(4300,2800);
		SubirActuador(1100,2800);
		BajarActuador(6000,5);
	}
}


void ServirTrago3(int Veces){
	for(int i=1;i<=Veces;i++)
	{
	SubirActuador(4400,2800);
	SubirActuador(1100,2800);
	BajarActuador(6000,5);
	}
}
void ServirTrago4(int Veces){
	for(int i=1;i<=Veces;i++)
	{
	SubirActuador(4800,2800);
	SubirActuador(1500,2800);
	BajarActuador(6000,5);
	}
}


//______________________FIN PISTON________________________________//


//--------------------------- MOTOR PASO A PASO----------------------------//
//** Si CantP es 800 = 360°
//** Si CantP es 400 = 180°
//** Si CantP es ~15000 va de un extremo a otro

// _delay_ms(225) es la máxima velocidad que puede tener el motor


int PinDirPaP = 3;
int PinPasosPaP = 4;
int PinEnablePaP = 5;
int TragoListo = 0;

//** InitMotor gira el motor hasta encontrar un fin de carrera **//

void InitMotor(){
	INIT_MOTORPAP;
	PAP_ON;
	INIT_DIR_DER;

	while (((PINK & (1<<PK6))==0)) // PULL DOWN (FIN DE CARRERA)
	{
		PAP_PASOS_ON;
		_delay_us(VELOCIDAD_RAPIDA);
		PAP_PASOS_OFF;
		_delay_us(VELOCIDAD_RAPIDA);
	}

	MotorAvanzar(200);
	MotorRetroceder(175);
	PAP_OFF;
}

void InicializarMotorSensor0(){
	INIT_MOTORPAP;
	PAP_ON;
	INIT_DIR_DER;

	while(!((!((PINE & (1<<PE3))==0))))
	{
		PAP_PASOS_ON;
		_delay_us(VELOCIDAD_RAPIDA);
		PAP_PASOS_OFF;
		_delay_us(VELOCIDAD_RAPIDA);
	}
}

void InicializarMotorSensor1(){
	INIT_MOTORPAP;
	PAP_ON;
	INIT_DIR_IZQ;

	while(!((!((PINH & (1<<PH6))==0))))
	{//corre motor hasta primera posicion y activa piston
		PAP_PASOS_ON;
		_delay_us(VELOCIDAD_RAPIDA);
		PAP_PASOS_OFF;
		_delay_us(VELOCIDAD_RAPIDA);
	}

	PAP_OFF;
}
void InicializarMotorSensor2(){
	INIT_MOTORPAP;
	PAP_ON;
	INIT_DIR_IZQ;

	while(!((!((PINH & (1<<PH5))==0))))
	{//corre motor hasta primera posicion y activa piston
		PAP_PASOS_ON;
		_delay_us(VELOCIDAD_RAPIDA);
		PAP_PASOS_OFF;
		_delay_us(VELOCIDAD_RAPIDA);
	}

	PAP_OFF;
}

void InicializarMotorSensor3(){
	INIT_MOTORPAP;
	PAP_ON;
	INIT_DIR_IZQ;

	while(!((!((PINH & (1<<PH4))==0))))
	{//corre motor hasta primera posicion y activa piston
		PAP_PASOS_ON;
		_delay_us(VELOCIDAD_RAPIDA);
		PAP_PASOS_OFF;
		_delay_us(VELOCIDAD_RAPIDA);
	}

	PAP_OFF;
}

void InicializarMotorSensor4(){
	INIT_MOTORPAP;
	PAP_ON;
	INIT_DIR_IZQ;

	while(!((!((PINH & (1<<PH3))==0))))
	{//corre motor hasta primera posicion y activa piston
		PAP_PASOS_ON;
		_delay_us(VELOCIDAD_RAPIDA);
		PAP_PASOS_OFF;
		_delay_us(VELOCIDAD_RAPIDA);
	}

	PAP_OFF;
}


void MotorAvanzar(int CantPasos){
	INIT_MOTORPAP;
	PAP_ON;
	INIT_DIR_IZQ;
	for (int j=0;j<=CantPasos;j++){
			PAP_PASOS_ON;
			_delay_us(VELOCIDAD_RAPIDA);
			PAP_PASOS_OFF;
			_delay_us(VELOCIDAD_RAPIDA);
	}
	PAP_OFF;
}

void MotorRetroceder (int CantPasos){
	INIT_MOTORPAP;
		PAP_ON;
		INIT_DIR_DER;

		for (int j=0;j<=CantPasos;j++){
			PAP_PASOS_ON;
			_delay_us(VELOCIDAD_RAPIDA);
			PAP_PASOS_OFF;
			_delay_us(VELOCIDAD_RAPIDA);
			}
		PAP_OFF;
}
//___________________FIN MOTOR PASO A PASO____________________//


//--------------------SERVOMOTOR-------------------------//
void Servo0a90(int Velocidad){
	Servo_0;
	_delay_ms(500);
	for(int i=2899;i>=1799;i--)
	{
		OCR1A = ICR1 - i;
		_delay_us(Velocidad);
	}
	_delay_ms(1000);
}

void Servo90a180(int Velocidad){
	Servo_90;
	_delay_ms(500);
	for(int i=1799;i>=859;i--)
	{
		OCR1A = ICR1 - i;
		_delay_us(Velocidad);
	}
	_delay_ms(1000);
	}

void Servo180a90(int Velocidad){
	Servo_180;
	_delay_ms(500);
	for(int i=859;i<=1799;i++)
	{
		OCR1A= ICR1 - i;
		_delay_us(Velocidad);
	}
	_delay_ms(1000);
}

void Servo180a45(int Velocidad){
	Servo_180;
	_delay_ms(500);
	for(int i=859;i<=2000;i++)
	{
		OCR1A= ICR1 - i;
		_delay_us(Velocidad);
	}
	_delay_ms(1000);
}

void Servo45a180(int Velocidad){
	Servo_90;
	_delay_ms(500);
	for(int i=2000;i>=859;i--)
	{
		OCR1A = ICR1 - i;
		_delay_us(Velocidad);
	}
	_delay_ms(1000);
	}

void Servo90a0(int Velocidad){
	Servo_90;
	_delay_ms(500);
	for(int i=1799;i<=2899;i++)
	{
		OCR1A = ICR1 - i;
		_delay_us(Velocidad);
	}
	_delay_ms(1000);
}

void Servo0a180(int Velocidad)
{
	Servo_0;
	_delay_ms(500);
	for(int i=2899;i>=859;i--)
	{
		OCR1A = ICR1 - i;
		_delay_us(Velocidad);
	}
	_delay_ms(1000);
}
void Servo180a0(int Velocidad){
	Servo_180;
	_delay_ms(500);
	for(int i=859;i<=2899;i++)
	{
		OCR1A = ICR1 - i;
		_delay_us(Velocidad);
	}
	_delay_ms(1000);
}
//_________________FIN SERVOMOTOR_______________________//

//--------------------LUZ VASO--------------------------//
struct cRGB led[1];

void GiroLedRojo(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
	for(int k=1;k<=CantidadGiros;k++){

		if(Sentido)
		{
		for(int i=0;i<=15;i++)
			  for(int j=20;j<125;j=j+RapidezIda)
			 {
			  led[i].r=j;led[i].g=0;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
			 }
			if(VueltaEnable)
			{
			  for(int i=0;i<=15;i++)
				  for(int j=125;j>=2;j=j-RapidezVuelta)
				 {
				  led[i].r=j;led[i].g=0;led[i].b=0;
				 ws2812_setleds(led,16);
				 _delay_us(50);
				 }
			}
		}
		else
		{
		for(int i=15;i>=0;i--)
			  for(int j=20;j<125;j=j+RapidezIda)
			 {
			  led[i].r=j;led[i].g=0;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
			 }
			if(VueltaEnable)
			{
			  for(int i=15;i>=0;i--)
				  for(int j=125;j>=2;j=j-RapidezVuelta)
				 {
				  led[i].r=j;led[i].g=0;led[i].b=0;
				 ws2812_setleds(led,16);
				 _delay_us(50);
				 }
				}
		}
	}
}

void GiroLedVerde(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
	for(int k=1;k<=CantidadGiros;k++){

	if(Sentido)
	{
		for(int i=0;i<=15;i++)
			  for(int j=20;j<125;j=j+RapidezIda)
			 {
			  led[i].r=0;led[i].g=j;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
			 }
		if(VueltaEnable)
		{
		  for(int i=0;i<=15;i++)
			  for(int j=125;j>=2;j=j-RapidezVuelta)
			 {
			  led[i].r=0;led[i].g=j;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(50);
			 }
		}
	}
	else
	{
		for(int i=15;i>=0;i--)
			  for(int j=20;j<125;j=j+RapidezIda)
			 {
			  led[i].r=0;led[i].g=j;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
			 }
		if(VueltaEnable)
		{
		  for(int i=15;i>=0;i--)
			  for(int j=125;j>=2;j=j-RapidezVuelta)
			 {
			  led[i].r=0;led[i].g=j;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(50);
			 }
		}
	}
	}
}

void GiroLedAzul(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
	for(int k=1;k<=CantidadGiros;k++){


		if(Sentido)
		{
			for(int i=0;i<=15;i++)
			  for(int j=20;j<125;j=j+RapidezIda)
			 {
			  led[i].r=0;led[i].g=0;led[i].b=j;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
			 }
			if(VueltaEnable)
			{
				for(int i=0;i<=15;i++)
					for(int j=125;j>=2;j=j-RapidezVuelta)
					{
					led[i].r=0;led[i].g=0;led[i].b=j;
					ws2812_setleds(led,16);
					_delay_us(50);
					}
			}
		}
		else
		{
			for(int i=15;i>=0;i--)
				for(int j=20;j<125;j=j+RapidezIda)
				{
				led[i].r=0;led[i].g=0;led[i].b=j;
				 ws2812_setleds(led,16);
				 _delay_us(4225);
				 }
			if(VueltaEnable)
			{
				for(int i=15;i>=0;i--)
					for(int j=125;j>=2;j=j-RapidezVuelta)
					 {
					  led[i].r=0;led[i].g=0;led[i].b=j;
					 ws2812_setleds(led,16);
					 _delay_us(50);
					 }
			}
		}
	}
}

void GiroLedCeleste(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
	for(int k=1;k<=CantidadGiros;k++){

	if(Sentido)
	{
	  for(int i=0;i<=15;i++)
	  for(int j=20;j<125;j=j+RapidezIda)
	  {
		  led[i].r=0;led[i].g=j;led[i].b=j;
		  ws2812_setleds(led,16);
		 _delay_us(4225);
	  }
	  if(VueltaEnable)
	  {
		  for(int i=0;i<=15;i++)
		  for(int j=125;j>=2;j=j-RapidezVuelta)
		  {
			  led[i].r=0;led[i].g=j;led[i].b=j;
			  ws2812_setleds(led,16);
			  _delay_us(50);
		  }
	  }
	}
	  else
	  {
		for(int i=15;i>=0;i--)
		for(int j=20;j<125;j=j+RapidezIda)
		{
			led[i].r=0;led[i].g=j;led[i].b=j;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
		 }
		if(VueltaEnable)
		{
			for(int i=15;i>=0;i--)
			for(int j=125;j>=2;j=j-RapidezVuelta)
		    {
				led[i].r=0;led[i].g=j;led[i].b=j;
				ws2812_setleds(led,16);
				_delay_us(50);
			 }
		}
	  }
	}
}

void GiroLedVioleta(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
	for(int k=1;k<=CantidadGiros;k++){

	if(Sentido)
	{
	  for(int i=0;i<=15;i++)
	  for(int j=20;j<125;j=j+RapidezIda)
	  {
		led[i].r=j;led[i].g=0;led[i].b=j;
		ws2812_setleds(led,16);
		 _delay_us(4225);
	  }
		  if(VueltaEnable)
		  {
			  for(int i=0;i<=15;i++)
			  for(int j=125;j>=2;j=j-RapidezVuelta)
			  {
				led[i].r=j;led[i].g=0;led[i].b=j;
				ws2812_setleds(led,16);
				_delay_us(50);
			  }
		  }
	}
	  else
	  {
			for(int i=15;i>=0;i--)
			for(int j=20;j<125;j=j+RapidezIda)
			{
				led[i].r=j;led[i].g=0;led[i].b=j;
				 ws2812_setleds(led,16);
				 _delay_us(4225);
			 }
			if(VueltaEnable)
			{
				for(int i=15;i>=0;i--)
				for(int j=125;j>=2;j=j-RapidezVuelta)
			    {
					led[i].r=j;led[i].g=0;led[i].b=j;
					ws2812_setleds(led,16);
					_delay_us(50);
			    }
			}
	  }
	}
}

void GiroLedAmarillo(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
for(int k=1;k<=CantidadGiros;k++){

	if(Sentido)
	{
	  for(int i=0;i<=15;i++)
	  for(int j=20;j<100;j=j+RapidezIda)
	  {
		led[i].r=j;led[i].g=j;led[i].b=0;
		ws2812_setleds(led,16);
		_delay_us(4225);
	  }

		  if(VueltaEnable)
		  {
			  for(int i=0;i<=15;i++)
			  for(int j=100;j>=2;j=j-RapidezVuelta)
			  {
				  led[i].r=j;led[i].g=j;led[i].b=0;
				  ws2812_setleds(led,16);
				  _delay_us(50);
			  }
		  }
	}
	else
	{
		for(int i=15;i>=0;i--)
		for(int j=20;j<100;j=j+RapidezIda)
		{
			led[i].r=j;led[i].g=j;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
		 }
		if(VueltaEnable)
		{
			for(int i=15;i>=0;i--)
			for(int j=100;j>=2;j=j-RapidezVuelta)
		    {
				led[i].r=j;led[i].g=j;led[i].b=0;
				ws2812_setleds(led,16);
				_delay_us(50);
		    }
		}
	}
	}
}

void GiroLedAzulMarino(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
for(int k=1;k<=CantidadGiros;k++){

	if(Sentido)
	{
	  for(int i=0;i<=15;i++)
	  for(int j=20;j<125;j=j+RapidezIda)
	  {
		 led[i].r=0;led[i].g=j/4;led[i].b=j;
		 ws2812_setleds(led,16);
		 _delay_us(4225);
	  }

		  if(VueltaEnable)
		  {
			  for(int i=0;i<=15;i++)
			  for(int j=125;j>=2;j=j-RapidezVuelta)
			  {
				 led[i].r=0;led[i].g=j/4;led[i].b=j;
				 ws2812_setleds(led,16);
				 _delay_us(50);
			  }
		  }
	}
	else
	{
		for(int i=15;i>=0;i--)
		for(int j=20;j<125;j=j+RapidezIda)
		{
			led[i].r=0;led[i].g=j/4;led[i].b=j;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
		}
			if(VueltaEnable)
			{
			for(int i=15;i>=0;i--)
			for(int j=125;j>=2;j=j-RapidezVuelta)
		    {
				led[i].r=0;led[i].g=j/4;led[i].b=j;
				ws2812_setleds(led,16);
				_delay_us(50);
		    }
		}
	}
	}
}

void GiroLedVerdeAgua(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
for(int k=1;k<=CantidadGiros;k++){

	if(Sentido)
	{
	  for(int i=0;i<=15;i++)
	  for(int j=20;j<125;j=j+RapidezIda)
	  {
		led[i].r=0;led[i].g=j;led[i].b=j/4;
		 ws2812_setleds(led,16);
		 _delay_us(4225);
	  }

		  if(VueltaEnable)
		  {
			  for(int i=0;i<=15;i++)
			  for(int j=125;j>=2;j=j-RapidezVuelta)
			  {
				 led[i].r=0;led[i].g=j;led[i].b=j/4;
				 ws2812_setleds(led,16);
				 _delay_us(50);
			  }
		  }
	}
	else
	{
		for(int i=15;i>=0;i--)
		for(int j=20;j<125;j=j+RapidezIda)
		{
			led[i].r=0;led[i].g=j;led[i].b=j/4;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
		}
			if(VueltaEnable)
			{
			for(int i=15;i>=0;i--)
			for(int j=125;j>=2;j=j-RapidezVuelta)
		    {
				led[i].r=0;led[i].g=j;led[i].b=j/4;
				ws2812_setleds(led,16);
				_delay_us(50);
		    }
		}
	}
}
}

void GiroLedRosa(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
for(int k=1;k<=CantidadGiros;k++){

	if(Sentido)
	{
	  for(int i=0;i<=15;i++)
	  for(int j=20;j<125;j=j+RapidezIda)
	  {
		 led[i].r=j;led[i].g=0;led[i].b=j/4;
		 ws2812_setleds(led,16);
		 _delay_us(4225);
	  }

		  if(VueltaEnable)
		  {
			  for(int i=0;i<=15;i++)
			  for(int j=125;j>=2;j=j-RapidezVuelta)
			  {
				 led[i].r=j;led[i].g=0;led[i].b=j/4;
				 ws2812_setleds(led,16);
				 _delay_us(50);
			  }
		  }
	}
	else
	{
		for(int i=15;i>=0;i--)
		for(int j=20;j<125;j=j+RapidezIda)
		{
			led[i].r=j;led[i].g=0;led[i].b=j/4;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
		}
			if(VueltaEnable)
			{
			for(int i=15;i>=0;i--)
			for(int j=125;j>=2;j=j-RapidezVuelta)
		    {
				led[i].r=j;led[i].g=0;led[i].b=j/4;
				ws2812_setleds(led,16);
				_delay_us(50);
		    }
		}
	}
}
}

void GiroLedLila(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
for(int k=1;k<=CantidadGiros;k++){

	if(Sentido)
	{
		  for(int i=0;i<=15;i++)
		  for(int j=20;j<125;j=j+RapidezIda)
		  {
			  led[i].r=j/4;led[i].g=0;led[i].b=j;
			  ws2812_setleds(led,16);
			  _delay_us(4225);
		  }

			  if(VueltaEnable)
			  {
				  for(int i=0;i<=15;i++)
				  for(int j=125;j>=2;j=j-RapidezVuelta)
				  {
					  led[i].r=j/4;led[i].g=0;led[i].b=j;
					  ws2812_setleds(led,16);
					  _delay_us(50);
				  }
			  }
	}
	else
	{
		for(int i=15;i>=0;i--)
		for(int j=20;j<125;j=j+RapidezIda)
		{
			led[i].r=j/4;led[i].g=0;led[i].b=j;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
		}
			if(VueltaEnable)
			{
			for(int i=15;i>=0;i--)
			for(int j=125;j>=2;j=j-RapidezVuelta)
		    {
				led[i].r=j/4;led[i].g=0;led[i].b=j;
				ws2812_setleds(led,16);
				_delay_us(50);
		    }
		}
	}
}
}

void GiroLedVerdeVivo(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
for(int k=1;k<=CantidadGiros;k++){

	if(Sentido)
	{
		  for(int i=0;i<=15;i++)
		  for(int j=20;j<125;j=j+RapidezIda)
		  {
			  led[i].r=j/4;led[i].g=j;led[i].b=0;
			  ws2812_setleds(led,16);
			  _delay_us(4225);
		 }

		  if(VueltaEnable)
		  {
			  for(int i=0;i<=15;i++)
			  for(int j=125;j>=2;j=j-RapidezVuelta)
			  {
				 led[i].r=j/4;led[i].g=j;led[i].b=0;
				 ws2812_setleds(led,16);
				 _delay_us(50);
			  }
		  }
	}
	else
	{
		for(int i=15;i>=0;i--)
		for(int j=20;j<125;j=j+RapidezIda)
		{
			led[i].r=j/4;led[i].g=j;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
		}
			if(VueltaEnable)
			{
			for(int i=15;i>=0;i--)
			for(int j=125;j>=2;j=j-RapidezVuelta)
		    {
				led[i].r=j/4;led[i].g=j;led[i].b=0;
				ws2812_setleds(led,16);
				_delay_us(50);
		    }
		}
	}
	}
}

void GiroLedNaranja(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
for(int k=1;k<=CantidadGiros;k++){
	if(Sentido)
	{
	  for(int i=0;i<=15;i++)
	  for(int j=20;j<125;j=j+RapidezIda)
	  {
		 led[i].r=j;led[i].g=j/4;led[i].b=0;
		 ws2812_setleds(led,16);
		 _delay_us(4225);
	  }

		  if(VueltaEnable)
		  {
			  for(int i=0;i<=15;i++)
		      for(int j=125;j>=2;j=j-RapidezVuelta)
		      {
				 led[i].r=j;led[i].g=j/4;led[i].b=0;
				 ws2812_setleds(led,16);
				 _delay_us(50);
		      }
		  }
	 }
	else
	{
		for(int i=15;i>=0;i--)
		for(int j=20;j<125;j=j+RapidezIda)
		{
			led[i].r=j;led[i].g=j/4;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
		}
			if(VueltaEnable)
			{
			for(int i=15;i>=0;i--)
			for(int j=125;j>=2;j=j-RapidezVuelta)
		    {
				led[i].r=j;led[i].g=j/4;led[i].b=0;
				ws2812_setleds(led,16);
				_delay_us(50);
		    }
		}
	}
	}
}

void GiroLedBlanco(int CantidadGiros,int Sentido,int RapidezIda,int VueltaEnable,int RapidezVuelta){
for(int k=1;k<=CantidadGiros;k++){
	if(Sentido)
	{
		for(int i=0;i<=15;i++)
		for(int j=20;j<=125;j=j+RapidezIda)
		{
			led[i].r=j;led[i].g=j;led[i].b=j;
			ws2812_setleds(led,16);
			_delay_us(4225);
		}

		  if(VueltaEnable)
		  {
			 for(int i=0;i<=15;i++)
			 for(int j=125;j>=2;j=j-RapidezVuelta)
			 {
				 led[i].r=j;led[i].g=j;led[i].b=j;
				 ws2812_setleds(led,16);
				 _delay_us(50);
			 }
		  }
	}
	else
	{
		for(int i=15;i>=0;i--)
		for(int j=20;j<125;j=j+RapidezIda)
		{
			led[i].r=j;led[i].g=j;led[i].b=j;
			 ws2812_setleds(led,16);
			 _delay_us(4225);
		}
			if(VueltaEnable)
			{
			for(int i=15;i>=0;i--)
			for(int j=125;j>=2;j=j-RapidezVuelta)
		    {
				led[i].r=j;led[i].g=j;led[i].b=j;
				ws2812_setleds(led,16);
				_delay_us(50);
		    }
		}
	}
	}
}

void GiroLedApagado(int Sentido,int Rapidez,int Velocidad){
	if(Sentido)
	{
		for(int i=0;i<=15;i++)
		  for(int j=125;j>20;j=j-Rapidez)
		 {
			  led[i].r=0;led[i].g=0;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(Velocidad);
		 }
	}
	else
	{
		for(int i=15;i>=0;i--)
		for(int j=20;j<125;j=j+Rapidez)
		{
			led[i].r=0;led[i].g=0;led[i].b=0;
			 ws2812_setleds(led,16);
			 _delay_us(Velocidad);
		}
	}
}

void AscenderRojo(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
	{
		led[0].r=i;led[0].g=0;led[0].b=0;
		led[1].r=i;led[1].g=0;led[1].b=0;
		led[2].r=i;led[2].g=0;led[2].b=0;
		led[3].r=i;led[3].g=0;led[3].b=0;
		led[4].r=i;led[4].g=0;led[4].b=0;
		led[5].r=i;led[5].g=0;led[5].b=0;
		led[6].r=i;led[6].g=0;led[6].b=0;
		led[7].r=i;led[7].g=0;led[7].b=0;
		led[8].r=i;led[8].g=0;led[8].b=0;
		led[9].r=i;led[9].g=0;led[9].b=0;
		led[10].r=i;led[10].g=0;led[10].b=0;
		led[11].r=i;led[11].g=0;led[11].b=0;
		led[12].r=i;led[12].g=0;led[12].b=0;
		led[13].r=i;led[13].g=0;led[13].b=0;
		led[14].r=i;led[14].g=0;led[14].b=0;
		led[15].r=i;led[15].g=0;led[15].b=0;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void DescenderRojo(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=j;led[0].g=0;led[0].b=0;
		led[1].r=j;led[1].g=0;led[1].b=0;
		led[2].r=j;led[2].g=0;led[2].b=0;
		led[3].r=j;led[3].g=0;led[3].b=0;
		led[4].r=j;led[4].g=0;led[4].b=0;
		led[5].r=j;led[5].g=0;led[5].b=0;
		led[6].r=j;led[6].g=0;led[6].b=0;
		led[7].r=j;led[7].g=0;led[7].b=0;
		led[8].r=j;led[8].g=0;led[8].b=0;
		led[9].r=j;led[9].g=0;led[9].b=0;
		led[10].r=j;led[10].g=0;led[10].b=0;
		led[11].r=j;led[11].g=0;led[11].b=0;
		led[12].r=j;led[12].g=0;led[12].b=0;
		led[13].r=j;led[13].g=0;led[13].b=0;
		led[14].r=j;led[14].g=0;led[14].b=0;
		led[15].r=j;led[15].g=0;led[15].b=0;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderVerde(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
	{
		led[0].r=0;led[0].g=i;led[0].b=0;
		led[1].r=0;led[1].g=i;led[1].b=0;
		led[2].r=0;led[2].g=i;led[2].b=0;
		led[3].r=0;led[3].g=i;led[3].b=0;
		led[4].r=0;led[4].g=i;led[4].b=0;
		led[5].r=0;led[5].g=i;led[5].b=0;
		led[6].r=0;led[6].g=i;led[6].b=0;
		led[7].r=0;led[7].g=i;led[7].b=0;
		led[8].r=0;led[8].g=i;led[8].b=0;
		led[9].r=0;led[9].g=i;led[9].b=0;
		led[10].r=0;led[10].g=i;led[10].b=0;
		led[11].r=0;led[11].g=i;led[11].b=0;
		led[12].r=0;led[12].g=i;led[12].b=0;
		led[13].r=0;led[13].g=i;led[13].b=0;
		led[14].r=0;led[14].g=i;led[14].b=0;
		led[15].r=0;led[15].g=i;led[15].b=0;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}


}

void DescenderVerde(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=0;led[0].g=j;led[0].b=0;
		led[1].r=0;led[1].g=j;led[1].b=0;
		led[2].r=0;led[2].g=j;led[2].b=0;
		led[3].r=0;led[3].g=j;led[3].b=0;
		led[4].r=0;led[4].g=j;led[4].b=0;
		led[5].r=0;led[5].g=j;led[5].b=0;
		led[6].r=0;led[6].g=j;led[6].b=0;
		led[7].r=0;led[7].g=j;led[7].b=0;
		led[8].r=0;led[8].g=j;led[8].b=0;
		led[9].r=0;led[9].g=j;led[9].b=0;
		led[10].r=0;led[10].g=j;led[10].b=0;
		led[11].r=0;led[11].g=j;led[11].b=0;
		led[12].r=0;led[12].g=j;led[12].b=0;
		led[13].r=0;led[13].g=j;led[13].b=0;
		led[14].r=0;led[14].g=j;led[14].b=0;
		led[15].r=0;led[15].g=j;led[15].b=0;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderAzul(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
	{
		led[0].r=0;led[0].g=0;led[0].b=i;
		led[1].r=0;led[1].g=0;led[1].b=i;
		led[2].r=0;led[2].g=0;led[2].b=i;
		led[3].r=0;led[3].g=0;led[3].b=i;
		led[4].r=0;led[4].g=0;led[4].b=i;
		led[5].r=0;led[5].g=0;led[5].b=i;
		led[6].r=0;led[6].g=0;led[6].b=i;
		led[7].r=0;led[7].g=0;led[7].b=i;
		led[8].r=0;led[8].g=0;led[8].b=i;
		led[9].r=0;led[9].g=0;led[9].b=i;
		led[10].r=0;led[10].g=0;led[10].b=i;
		led[11].r=0;led[11].g=0;led[11].b=i;
		led[12].r=0;led[12].g=0;led[12].b=i;
		led[13].r=0;led[13].g=0;led[13].b=i;
		led[14].r=0;led[14].g=0;led[14].b=i;
		led[15].r=0;led[15].g=0;led[15].b=i;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void DescenderAzul(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=0;led[0].g=0;led[0].b=j;
		led[1].r=0;led[1].g=0;led[1].b=j;
		led[2].r=0;led[2].g=0;led[2].b=j;
		led[3].r=0;led[3].g=0;led[3].b=j;
		led[4].r=0;led[4].g=0;led[4].b=j;
		led[5].r=0;led[5].g=0;led[5].b=j;
		led[6].r=0;led[6].g=0;led[6].b=j;
		led[7].r=0;led[7].g=0;led[7].b=j;
		led[8].r=0;led[8].g=0;led[8].b=j;
		led[9].r=0;led[9].g=0;led[9].b=j;
		led[10].r=0;led[10].g=0;led[10].b=j;
		led[11].r=0;led[11].g=0;led[11].b=j;
		led[12].r=0;led[12].g=0;led[12].b=j;
		led[13].r=0;led[13].g=0;led[13].b=j;
		led[14].r=0;led[14].g=0;led[14].b=j;
		led[15].r=0;led[15].g=0;led[15].b=j;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderBlanco(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
	{
		led[0].r=i;led[0].g=i;led[0].b=i;
		led[1].r=i;led[1].g=i;led[1].b=i;
		led[2].r=i;led[2].g=i;led[2].b=i;
		led[3].r=i;led[3].g=i;led[3].b=i;
		led[4].r=i;led[4].g=i;led[4].b=i;
		led[5].r=i;led[5].g=i;led[5].b=i;
		led[6].r=i;led[6].g=i;led[6].b=i;
		led[7].r=i;led[7].g=i;led[7].b=i;
		led[8].r=i;led[8].g=i;led[8].b=i;
		led[9].r=i;led[9].g=i;led[9].b=i;
		led[10].r=i;led[10].g=i;led[10].b=i;
		led[11].r=i;led[11].g=i;led[11].b=i;
		led[12].r=i;led[12].g=i;led[12].b=i;
		led[13].r=i;led[13].g=i;led[13].b=i;
		led[14].r=i;led[14].g=i;led[14].b=i;
		led[15].r=i;led[15].g=i;led[15].b=i;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}

}

void DescenderBlanco(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=j;led[0].g=j;led[0].b=j;
		led[1].r=j;led[1].g=j;led[1].b=j;
		led[2].r=j;led[2].g=j;led[2].b=j;
		led[3].r=j;led[3].g=j;led[3].b=j;
		led[4].r=j;led[4].g=j;led[4].b=j;
		led[5].r=j;led[5].g=j;led[5].b=j;
		led[6].r=j;led[6].g=j;led[6].b=j;
		led[7].r=j;led[7].g=j;led[7].b=j;
		led[8].r=j;led[8].g=j;led[8].b=j;
		led[9].r=j;led[9].g=j;led[9].b=j;
		led[10].r=j;led[10].g=j;led[10].b=j;
		led[11].r=j;led[11].g=j;led[11].b=j;
		led[12].r=j;led[12].g=j;led[12].b=j;
		led[13].r=j;led[13].g=j;led[13].b=j;
		led[14].r=j;led[14].g=j;led[14].b=j;
		led[15].r=j;led[15].g=j;led[15].b=j;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderCeleste(int Intensidad,int Rapidez){
for(int i=0;i<=Intensidad;i=i+Rapidez)
	{
		led[0].r=0;led[0].g=i;led[0].b=i;
		led[1].r=0;led[1].g=i;led[1].b=i;
		led[2].r=0;led[2].g=i;led[2].b=i;
		led[3].r=0;led[3].g=i;led[3].b=i;
		led[4].r=0;led[4].g=i;led[4].b=i;
		led[5].r=0;led[5].g=i;led[5].b=i;
		led[6].r=0;led[6].g=i;led[6].b=i;
		led[7].r=0;led[7].g=i;led[7].b=i;
		led[8].r=0;led[8].g=i;led[8].b=i;
		led[9].r=0;led[9].g=i;led[9].b=i;
		led[10].r=0;led[10].g=i;led[10].b=i;
		led[11].r=0;led[11].g=i;led[11].b=i;
		led[12].r=0;led[12].g=i;led[12].b=i;
		led[13].r=0;led[13].g=i;led[13].b=i;
		led[14].r=0;led[14].g=i;led[14].b=i;
		led[15].r=0;led[15].g=i;led[15].b=i;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void DescenderCeleste(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=0;led[0].g=j;led[0].b=j;
		led[1].r=0;led[1].g=j;led[1].b=j;
		led[2].r=0;led[2].g=j;led[2].b=j;
		led[3].r=0;led[3].g=j;led[3].b=j;
		led[4].r=0;led[4].g=j;led[4].b=j;
		led[5].r=0;led[5].g=j;led[5].b=j;
		led[6].r=0;led[6].g=j;led[6].b=j;
		led[7].r=0;led[7].g=j;led[7].b=j;
		led[8].r=0;led[8].g=j;led[8].b=j;
		led[9].r=0;led[9].g=j;led[9].b=j;
		led[10].r=0;led[10].g=j;led[10].b=j;
		led[11].r=0;led[11].g=j;led[11].b=j;
		led[12].r=0;led[12].g=j;led[12].b=j;
		led[13].r=0;led[13].g=j;led[13].b=j;
		led[14].r=0;led[14].g=j;led[14].b=j;
		led[15].r=0;led[15].g=j;led[15].b=j;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderVioleta(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
		{
			led[0].r=i;led[0].g=0;led[0].b=i;
			led[1].r=i;led[1].g=0;led[1].b=i;
			led[2].r=i;led[2].g=0;led[2].b=i;
			led[3].r=i;led[3].g=0;led[3].b=i;
			led[4].r=i;led[4].g=0;led[4].b=i;
			led[5].r=i;led[5].g=0;led[5].b=i;
			led[6].r=i;led[6].g=0;led[6].b=i;
			led[7].r=i;led[7].g=0;led[7].b=i;
			led[8].r=i;led[8].g=0;led[8].b=i;
			led[9].r=i;led[9].g=0;led[9].b=i;
			led[10].r=i;led[10].g=0;led[10].b=i;
			led[11].r=i;led[11].g=0;led[11].b=i;
			led[12].r=i;led[12].g=0;led[12].b=i;
			led[13].r=i;led[13].g=0;led[13].b=i;
			led[14].r=i;led[14].g=0;led[14].b=i;
			led[15].r=i;led[15].g=0;led[15].b=i;
			 ws2812_setleds(led,16);
			 _delay_ms(10);
		}
}

void DescenderVioleta(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=j;led[0].g=0;led[0].b=j;
		led[1].r=j;led[1].g=0;led[1].b=j;
		led[2].r=j;led[2].g=0;led[2].b=j;
		led[3].r=j;led[3].g=0;led[3].b=j;
		led[4].r=j;led[4].g=0;led[4].b=j;
		led[5].r=j;led[5].g=0;led[5].b=j;
		led[6].r=j;led[6].g=0;led[6].b=j;
		led[7].r=j;led[7].g=0;led[7].b=j;
		led[8].r=j;led[8].g=0;led[8].b=j;
		led[9].r=j;led[9].g=0;led[9].b=j;
		led[10].r=j;led[10].g=0;led[10].b=j;
		led[11].r=j;led[11].g=0;led[11].b=j;
		led[12].r=j;led[12].g=0;led[12].b=j;
		led[13].r=j;led[13].g=0;led[13].b=j;
		led[14].r=j;led[14].g=0;led[14].b=j;
		led[15].r=j;led[15].g=0;led[15].b=j;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderAmarillo(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
		{
			led[0].r=i;led[0].g=i;led[0].b=0;
			led[1].r=i;led[1].g=i;led[1].b=0;
			led[2].r=i;led[2].g=i;led[2].b=0;
			led[3].r=i;led[3].g=i;led[3].b=0;
			led[4].r=i;led[4].g=i;led[4].b=0;
			led[5].r=i;led[5].g=i;led[5].b=0;
			led[6].r=i;led[6].g=i;led[6].b=0;
			led[7].r=i;led[7].g=i;led[7].b=0;
			led[8].r=i;led[8].g=i;led[8].b=0;
			led[9].r=i;led[9].g=i;led[9].b=0;
			led[10].r=i;led[10].g=i;led[10].b=0;
			led[11].r=i;led[11].g=i;led[11].b=0;
			led[12].r=i;led[12].g=i;led[12].b=0;
			led[13].r=i;led[13].g=i;led[13].b=0;
			led[14].r=i;led[14].g=i;led[14].b=0;
			led[15].r=i;led[15].g=i;led[15].b=0;
			 ws2812_setleds(led,16);
			 _delay_ms(10);
		}
}

void DescenderAmarillo(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=j;led[0].g=j;led[0].b=0;
		led[1].r=j;led[1].g=j;led[1].b=0;
		led[2].r=j;led[2].g=j;led[2].b=0;
		led[3].r=j;led[3].g=j;led[3].b=0;
		led[4].r=j;led[4].g=j;led[4].b=0;
		led[5].r=j;led[5].g=j;led[5].b=0;
		led[6].r=j;led[6].g=j;led[6].b=0;
		led[7].r=j;led[7].g=j;led[7].b=0;
		led[8].r=j;led[8].g=j;led[8].b=0;
		led[9].r=j;led[9].g=j;led[9].b=0;
		led[10].r=j;led[10].g=j;led[10].b=0;
		led[11].r=j;led[11].g=j;led[11].b=0;
		led[12].r=j;led[12].g=j;led[12].b=0;
		led[13].r=j;led[13].g=j;led[13].b=0;
		led[14].r=j;led[14].g=j;led[14].b=0;
		led[15].r=j;led[15].g=j;led[15].b=0;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderRosa(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
		{
			led[0].r=i;led[0].g=0;led[0].b=i/4;
			led[1].r=i;led[1].g=0;led[1].b=i/4;
			led[2].r=i;led[2].g=0;led[2].b=i/4;
			led[3].r=i;led[3].g=0;led[3].b=i/4;
			led[4].r=i;led[4].g=0;led[4].b=i/4;
			led[5].r=i;led[5].g=0;led[5].b=i/4;
			led[6].r=i;led[6].g=0;led[6].b=i/4;
			led[7].r=i;led[7].g=0;led[7].b=i/4;
			led[8].r=i;led[8].g=0;led[8].b=i/4;
			led[9].r=i;led[9].g=0;led[9].b=i/4;
			led[10].r=i;led[10].g=0;led[10].b=i/4;
			led[11].r=i;led[11].g=0;led[11].b=i/4;
			led[12].r=i;led[12].g=0;led[12].b=i/4;
			led[13].r=i;led[13].g=0;led[13].b=i/4;
			led[14].r=i;led[14].g=0;led[14].b=i/4;
			led[15].r=i;led[15].g=0;led[15].b=i/4;
			 ws2812_setleds(led,16);
			 _delay_ms(10);
		}
}

void DescenderRosa(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=j;led[0].g=0;led[0].b=j/4;
		led[1].r=j;led[1].g=0;led[1].b=j/4;
		led[2].r=j;led[2].g=0;led[2].b=j/4;
		led[3].r=j;led[3].g=0;led[3].b=j/4;
		led[4].r=j;led[4].g=0;led[4].b=j/4;
		led[5].r=j;led[5].g=0;led[5].b=j/4;
		led[6].r=j;led[6].g=0;led[6].b=j/4;
		led[7].r=j;led[7].g=0;led[7].b=j/4;
		led[8].r=j;led[8].g=0;led[8].b=j/4;
		led[9].r=j;led[9].g=0;led[9].b=j/4;
		led[10].r=j;led[10].g=0;led[10].b=j/4;
		led[11].r=j;led[11].g=0;led[11].b=j/4;
		led[12].r=j;led[12].g=0;led[12].b=j/4;
		led[13].r=j;led[13].g=0;led[13].b=j/4;
		led[14].r=j;led[14].g=0;led[14].b=j/4;
		led[15].r=j;led[15].g=0;led[15].b=j/4;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderLila(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
		{
			led[0].r=i/4;led[0].g=0;led[0].b=i;
			led[1].r=i/4;led[1].g=0;led[1].b=i;
			led[2].r=i/4;led[2].g=0;led[2].b=i;
			led[3].r=i/4;led[3].g=0;led[3].b=i;
			led[4].r=i/4;led[4].g=0;led[4].b=i;
			led[5].r=i/4;led[5].g=0;led[5].b=i;
			led[6].r=i/4;led[6].g=0;led[6].b=i;
			led[7].r=i/4;led[7].g=0;led[7].b=i;
			led[8].r=i/4;led[8].g=0;led[8].b=i;
			led[9].r=i/4;led[9].g=0;led[9].b=i;
			led[10].r=i/4;led[10].g=0;led[10].b=i;
			led[11].r=i/4;led[11].g=0;led[11].b=i;
			led[12].r=i/4;led[12].g=0;led[12].b=i;
			led[13].r=i/4;led[13].g=0;led[13].b=i;
			led[14].r=i/4;led[14].g=0;led[14].b=i;
			led[15].r=i/4;led[15].g=0;led[15].b=i;
			 ws2812_setleds(led,16);
			 _delay_ms(10);
		}
}

void DescenderLila(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=j/4;led[0].g=0;led[0].b=j;
		led[1].r=j/4;led[1].g=0;led[1].b=j;
		led[2].r=j/4;led[2].g=0;led[2].b=j;
		led[3].r=j/4;led[3].g=0;led[3].b=j;
		led[4].r=j/4;led[4].g=0;led[4].b=j;
		led[5].r=j/4;led[5].g=0;led[5].b=j;
		led[6].r=j/4;led[6].g=0;led[6].b=j;
		led[7].r=j/4;led[7].g=0;led[7].b=j;
		led[8].r=j/4;led[8].g=0;led[8].b=j;
		led[9].r=j/4;led[9].g=0;led[9].b=j;
		led[10].r=j/4;led[10].g=0;led[10].b=j;
		led[11].r=j/4;led[11].g=0;led[11].b=j;
		led[12].r=j/4;led[12].g=0;led[12].b=j;
		led[13].r=j/4;led[13].g=0;led[13].b=j;
		led[14].r=j/4;led[14].g=0;led[14].b=j;
		led[15].r=j/4;led[15].g=0;led[15].b=j;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderNaranja(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
		{
			led[0].r=i;led[0].g=i/4;led[0].b=0;
			led[1].r=i;led[1].g=i/4;led[1].b=0;
			led[2].r=i;led[2].g=i/4;led[2].b=0;
			led[3].r=i;led[3].g=i/4;led[3].b=0;
			led[4].r=i;led[4].g=i/4;led[4].b=0;
			led[5].r=i;led[5].g=i/4;led[5].b=0;
			led[6].r=i;led[6].g=i/4;led[6].b=0;
			led[7].r=i;led[7].g=i/4;led[7].b=0;
			led[8].r=i;led[8].g=i/4;led[8].b=0;
			led[9].r=i;led[9].g=i/4;led[9].b=0;
			led[10].r=i;led[10].g=i/4;led[10].b=0;
			led[11].r=i;led[11].g=i/4;led[11].b=0;
			led[12].r=i;led[12].g=i/4;led[12].b=0;
			led[13].r=i;led[13].g=i/4;led[13].b=0;
			led[14].r=i;led[14].g=i/4;led[14].b=0;
			led[15].r=i;led[15].g=i/4;led[15].b=0;
			 ws2812_setleds(led,16);
			 _delay_ms(10);
		}
}

void DescenderNaranja(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=j;led[0].g=j/4;led[0].b=0;
		led[1].r=j;led[1].g=j/4;led[1].b=0;
		led[2].r=j;led[2].g=j/4;led[2].b=0;
		led[3].r=j;led[3].g=j/4;led[3].b=0;
		led[4].r=j;led[4].g=j/4;led[4].b=0;
		led[5].r=j;led[5].g=j/4;led[5].b=0;
		led[6].r=j;led[6].g=j/4;led[6].b=0;
		led[7].r=j;led[7].g=j/4;led[7].b=0;
		led[8].r=j;led[8].g=j/4;led[8].b=0;
		led[9].r=j;led[9].g=j/4;led[9].b=0;
		led[10].r=j;led[10].g=j/4;led[10].b=0;
		led[11].r=j;led[11].g=j/4;led[11].b=0;
		led[12].r=j;led[12].g=j/4;led[12].b=0;
		led[13].r=j;led[13].g=j/4;led[13].b=0;
		led[14].r=j;led[14].g=j/4;led[14].b=0;
		led[15].r=j;led[15].g=j/4;led[15].b=0;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderVerdeVivo(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
		{
			led[0].r=i/4;led[0].g=i;led[0].b=0;
			led[1].r=i/4;led[1].g=i;led[1].b=0;
			led[2].r=i/4;led[2].g=i;led[2].b=0;
			led[3].r=i/4;led[3].g=i;led[3].b=0;
			led[4].r=i/4;led[4].g=i;led[4].b=0;
			led[5].r=i/4;led[5].g=i;led[5].b=0;
			led[6].r=i/4;led[6].g=i;led[6].b=0;
			led[7].r=i/4;led[7].g=i;led[7].b=0;
			led[8].r=i/4;led[8].g=i;led[8].b=0;
			led[9].r=i/4;led[9].g=i;led[9].b=0;
			led[10].r=i/4;led[10].g=i;led[10].b=0;
			led[11].r=i/4;led[11].g=i;led[11].b=0;
			led[12].r=i/4;led[12].g=i;led[12].b=0;
			led[13].r=i/4;led[13].g=i;led[13].b=0;
			led[14].r=i/4;led[14].g=i;led[14].b=0;
			led[15].r=i/4;led[15].g=i;led[15].b=0;
			 ws2812_setleds(led,16);
			 _delay_ms(10);
		}
}

void DescenderVerdeVivo(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=j/4;led[0].g=j;led[0].b=0;
		led[1].r=j/4;led[1].g=j;led[1].b=0;
		led[2].r=j/4;led[2].g=j;led[2].b=0;
		led[3].r=j/4;led[3].g=j;led[3].b=0;
		led[4].r=j/4;led[4].g=j;led[4].b=0;
		led[5].r=j/4;led[5].g=j;led[5].b=0;
		led[6].r=j/4;led[6].g=j;led[6].b=0;
		led[7].r=j/4;led[7].g=j;led[7].b=0;
		led[8].r=j/4;led[8].g=j;led[8].b=0;
		led[9].r=j/4;led[9].g=j;led[9].b=0;
		led[10].r=j/4;led[10].g=j;led[10].b=0;
		led[11].r=j/4;led[11].g=j;led[11].b=0;
		led[12].r=j/4;led[12].g=j;led[12].b=0;
		led[13].r=j/4;led[13].g=j;led[13].b=0;
		led[14].r=j/4;led[14].g=j;led[14].b=0;
		led[15].r=j/4;led[15].g=j;led[15].b=0;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}

void AscenderVerdeAgua(int Intensidad,int Rapidez){
	for(int i=0;i<=Intensidad;i=i+Rapidez)
	{
		led[0].r=0;led[0].g=i;led[0].b=i/4;
		led[1].r=0;led[1].g=i;led[1].b=i/4;
		led[2].r=0;led[2].g=i;led[2].b=i/4;
		led[3].r=0;led[3].g=i;led[3].b=i/4;
		led[4].r=0;led[4].g=i;led[4].b=i/4;
		led[5].r=0;led[5].g=i;led[5].b=i/4;
		led[6].r=0;led[6].g=i;led[6].b=i/4;
		led[7].r=0;led[7].g=i;led[7].b=i/4;
		led[8].r=0;led[8].g=i;led[8].b=i/4;
		led[9].r=0;led[9].g=i;led[9].b=i/4;
		led[10].r=0;led[10].g=i;led[10].b=i/4;
		led[11].r=0;led[11].g=i;led[11].b=i/4;
		led[12].r=0;led[12].g=i;led[12].b=i/4;
		led[13].r=0;led[13].g=i;led[13].b=i/4;
		led[14].r=0;led[14].g=i;led[14].b=i/4;
		led[15].r=0;led[15].g=i;led[15].b=i/4;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}


void DescenderVerdeAgua(int Intensidad,int Rapidez){
	for(int j=Intensidad;j>=0;j=j-Rapidez)
	{
		led[0].r=0;led[0].g=j;led[0].b=j/4;
		led[1].r=0;led[1].g=j;led[1].b=j/4;
		led[2].r=0;led[2].g=j;led[2].b=j/4;
		led[3].r=0;led[3].g=j;led[3].b=j/4;
		led[4].r=0;led[4].g=j;led[4].b=j/4;
		led[5].r=0;led[5].g=j;led[5].b=j/4;
		led[6].r=0;led[6].g=j;led[6].b=j/4;
		led[7].r=0;led[7].g=j;led[7].b=j/4;
		led[8].r=0;led[8].g=j;led[8].b=j/4;
		led[9].r=0;led[9].g=j;led[9].b=j/4;
		led[10].r=0;led[10].g=j;led[10].b=j/4;
		led[11].r=0;led[11].g=j;led[11].b=j/4;
		led[12].r=0;led[12].g=j;led[12].b=j/4;
		led[13].r=0;led[13].g=j;led[13].b=j/4;
		led[14].r=0;led[14].g=j;led[14].b=j/4;
		led[15].r=0;led[15].g=j;led[15].b=j/4;
		 ws2812_setleds(led,16);
		 _delay_ms(10);
	}
}


