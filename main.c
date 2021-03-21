/*
 Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 *
 * Created: 1/24/2012 2:16:29 PM
 *  Author: gary.grewal
 * 
 * OD Atmelu je prevzata a ohnuta knihovna na I2C pomoci dvou GPIO pinu
 *
 * Author: Martin Vit  21.3.2020 20:30 - program pro rozsviceni napisu AHOJ na grafickem displeji s kontrolerem SH1106 (inicializace displeje, mazani obrayovky, skok na pozici v obrazovce)
 *****************************************************************************/
#include "TWI_Master.h"		// knihovna na I2C pomoci dvou GPIO pinu, Pin PB0 je SCL - hodiny, a pin PB3 jsou SDA - data, adresa Slave 0x78 - Displej s ?ipem SH1106 - vše je napevno nadefinovano v tom .h souboru
#include <util/delay.h>		// funkce na zpozdeni

/* Inicializace displeje, spoustu dat co posila ridici p?ikazy */
void DisplayInit()
{
	unsigned char dat1[2] = {0x00,0xAE};		// Vypni displej
	unsigned char dat2[2] = {0x00,0xD5};	
	unsigned char dat3[2] = {0x00,0x80};	
	unsigned char dat4[2] = {0x00,0xA8};	
	unsigned char dat5[2] = {0x00,0x3F};	
	unsigned char dat6[2] = {0x00,0xD3};	
	unsigned char dat7[2] = {0x00,0x00};	
	unsigned char dat8[2] = {0x00,0x40};	
	unsigned char dat9[2] = {0x00,0x8D};	
	unsigned char dat10[2] = {0x00,0x14};	
	unsigned char dat11[2] = {0x00,0x20};	
	unsigned char dat12[2] = {0x00,0x00};	
	unsigned char dat13[2] = {0x00,0xA1};	
	unsigned char dat14[2] = {0x00,0xC8};	
	unsigned char dat15[2] = {0x00,0xDA};
	unsigned char dat16[2] = {0x00,0x12};
	unsigned char dat17[2] = {0x00,0x81};		// Nastaveni kontrastu - prikaz
	unsigned char dat18[2] = {0x00,0xCF};		// Nastaveni kontrastu data (0 - 255) (0x00 az 0xFF) 
	unsigned char dat19[2] = {0x00,0xD9};	
	unsigned char dat20[2] = {0x00,0xF1};	
	unsigned char dat21[2] = {0x00,0xDB};	
	unsigned char dat22[2] = {0x00,0x40};	
	unsigned char dat23[2] = {0x00,0xA4};	
	unsigned char dat24[2] = {0x00,0xA6};		// 0xA7 inverzni displej 0 v pameti sviti / 0xA6 standartni displej 1 v pameti sviti
	unsigned char dat25[2] = {0x00,0xAF};		// Zapni display
	write_data(dat1,2);							// Funkce Write_data provede vyslani dat po I2C sbernici
	write_data(dat2,2);
	write_data(dat3,2);
	write_data(dat4,2);
	write_data(dat5,2);
	write_data(dat6,2);
	write_data(dat7,2);
	write_data(dat8,2);
	write_data(dat9,2);
	write_data(dat10,2);
	write_data(dat11,2);
	write_data(dat12,2);
	write_data(dat13,2);
	write_data(dat14,2);
	write_data(dat15,2);
	write_data(dat16,2);
	write_data(dat17,2);
	write_data(dat18,2);
	write_data(dat19,2);
	write_data(dat20,2);
	write_data(dat21,2);
	write_data(dat22,2);
	write_data(dat23,2);
	write_data(dat24,2);
	write_data(dat25,2);
	
}

/* Posune se na displeji na sloupecek x (1 az 128) a na stranku y (0 az 7)*/
/* kazde x v maluvce dole predstavuje jeden pixel displeje					*/
/*      |  S1 S2 S3 S4 S5 S6 ................................. S128
     -------------------------------------------------------------------
	 |S |   x  x  x  x  x  x                                    x
	 |T	|   x  x  x  x  x  x                                    x
	 |R	|   x  x  x  x  x  x                                    x
	 |A |   x  x  x  x  x  x                                    x
	 |N	|   x  x  x  x  x  x                                    x
	 |K	|   x  x  x  x  x  x                                    x
	 |A	|   x  x  x  x  x  x                                    x
	 |0	|   x  x  x  x  x  x                                    x
	 ---------------------------------------------------------------------	 
	 |S |   x  x  x  x  x  x                                    x
	 |T	|   x  x  x  x  x  x                                    x
	 |R	|   x  x  x  x  x  x                                    x
	 |A |   x  x  x  x  x  x                                    x
	 |N	|   x  x  x  x  x  x                                    x
	 |K	|   x  x  x  x  x  x                                    x
	 |A	|   x  x  x  x  x  x                                    x
	 |1	|   x  x  x  x  x  x                                    x
	 -------------------------------------------------------------------
	 |S |   x  x  x  x  x  x                                    x
	 |T	|   x  x  x  x  x  x                                    x
	 |R	|   x  x  x  x  x  x                                    x
	 |A |   x  x  x  x  x  x                                    x
	 |N	|   x  x  x  x  x  x                                    x
	 |K	|   x  x  x  x  x  x                                    x
	 |A	|   x  x  x  x  x  x                                    x
	 |2	|   x  x  x  x  x  x                                    x
	 ---------------------------------------------------------------------	 
	 |S |   x  x  x  x  x  x                                    x
	 |T	|   x  x  x  x  x  x                                    x
	 |R	|   x  x  x  x  x  x                                    x
	 |A |   x  x  x  x  x  x                                    x
	 |N	|   x  x  x  x  x  x                                    x
	 |K	|   x  x  x  x  x  x                                    x
	 |A	|   x  x  x  x  x  x                                    x
	 |3	|   x  x  x  x  x  x                                    x
	 ---------------------------------------------------------------------
	 |S |   x  x  x  x  x  x                                    x
	 |T	|   x  x  x  x  x  x                                    x
	 |R	|   x  x  x  x  x  x                                    x
	 |A |   x  x  x  x  x  x                                    x
	 |N	|   x  x  x  x  x  x                                    x
	 |K	|   x  x  x  x  x  x                                    x
	 |A	|   x  x  x  x  x  x                                    x
	 |4	|   x  x  x  x  x  x                                    x
	 -------------------------------------------------------------------
	 |S |   x  x  x  x  x  x                                    x
	 |T	|   x  x  x  x  x  x                                    x
	 |R	|   x  x  x  x  x  x                                    x
	 |A |   x  x  x  x  x  x                                    x
	 |N	|   x  x  x  x  x  x                                    x
	 |K	|   x  x  x  x  x  x                                    x
	 |A	|   x  x  x  x  x  x                                    x
	 |5	|   x  x  x  x  x  x                                    x
	 ---------------------------------------------------------------------	 
	 |S |   x  x  x  x  x  x                                    x
	 |T	|   x  x  x  x  x  x                                    x
	 |R	|   x  x  x  x  x  x                                    x
	 |A |   x  x  x  x  x  x                                    x
	 |N	|   x  x  x  x  x  x                                    x
	 |K	|   x  x  x  x  x  x                                    x
	 |A	|   x  x  x  x  x  x                                    x
	 |6	|   x  x  x  x  x  x                                    x
	 ---------------------------------------------------------------------
	 |S |   x  x  x  x  x  x                                    x
	 |T	|   x  x  x  x  x  x                                    x
	 |R	|   x  x  x  x  x  x                                    x
	 |A |   x  x  x  x  x  x                                    x
	 |N	|   x  x  x  x  x  x                                    x
	 |K	|   x  x  x  x  x  x                                    x
	 |A	|   x  x  x  x  x  x                                    x
	 |7	|   x  x  x  x  x  x                                    x
	 ---------------------------------------------------------------------
*/
void DisplayGotoXY(unsigned char x, unsigned char y)
{
	unsigned char data[2] = {0x00, 0x00};
	unsigned char pomocna;		// pomocna promnena pro vypocty a bitove operace
	
	data[0] = 0x00;				// control byte rika ze nasledujici byte bude prikaz
	data[1] = (0xB0 | y);		// cislo stranky a bitove se tam pricte 0xB0 do horniho nibble
	write_data(data,2);			// posune se na spravnou stranku
	
	pomocna = (x & 0x0F);		// vezme se jen spodni nible z x
	data[0] = 0x00;				// control byte rika ze nasledujici byte bude prikaz
	data[1] = pomocna;			// spodni adresa sloupce
	write_data(data,2);
	
	pomocna = (x>>4);			// vezme se horni nibble z x
	data[0] = 0x00;				// control byte rika ze nasledujici byte bude prikaz
	data[1] = 0x10 | pomocna;	// horni adresa sloupce
	write_data(data,2);
	
	
	
}

/*Vymaze vse na displeji*/
void DisplayClear()
{
	unsigned char sloupec;		//  celkem ma displej 128 sloupcu, tj 128 pixelu na sirku
	unsigned char stranka;		//  celkem ma displej 8 stranek	(viz obrazek 8 v datasheetu SH1106, vsechny stranky sviti najednou)
	unsigned char nic[131];		//  datove pole ktere si pomoci cyklu naplnim na 128 nulama a na zacatku dam ze se jedna o zapis do RAM
			
	sloupec = 0;
	stranka = 0;
	
	nic[0] = 0x40;				// 0x40 rika ze se zapisuji data do pameti RAM displeje, viz strana 14 v datasheetu displeje SH1106, Note 1: D / C# => D = 1 znamena data do RAM, je na pozici ze v control bajtu udela 4ku v hexu nahore
	for (sloupec = 0; sloupec < 130; sloupec++)
	{
		nic[sloupec+1] = 0x00;			// do kazdeho ze 128 sloupecku (kazdy sloupecek ma 8 pixelu) napise 0x00, tzn ze zhasne celkem 1024 pixelu
	}
	
	
	for (stranka = 0; stranka < 8; stranka++)
	{
		DisplayGotoXY(1, stranka);		// posune pozici kam na displeji na 1 sloupecek, na strance stranka (0 az 7)
		write_data(nic,130);			// celou jednu stranku naplni datama 0x00 (nesviti)		
	}
}


int main( void )
{
  unsigned char pismenoB[13] = {0x40,0x00,0xFE,0x92,0x92,0x92,0x6C,0x00,0xFE,0x92,0x92,0x92,0x6C };// Pismeno BB
  unsigned char pismenoA[7] = {0x40,0x00,0xF8,0x24,0x22,0x24,0xF8};	    // Pismeno A matice 5x7 pixelu (5x8) s tim ze horni pixely se nepouzivaji  
  unsigned char pismenoH[7] = {0x40,0x00,0xFE,0x10,0x10,0x10,0xFE};	    // Pismeno H matice 5x7 pixelu (5x8) s tim ze horni pixely se nepouzivaji  
  unsigned char pismenoO[7] = {0x40,0x00,0x7C,0x82,0x82,0x82,0x7C};		// Pismeno O matice 5x7 pixelu (5x8) s tim ze horni pixely se nepouzivaji 
/*
POPIS TVORBY PISMENA	FONT 5x7 pixelu (5 sloupecku, 7radek) - popis je po sloupecku
Byte sloupecku = |D7|D6|D5|D4|D3|D2|D1|D0|
				 | 0| 1| 1| 0| 0| 0| 0| 0|	= 0x60		prvni sloupec

D0						Druhy  sloupec = 0x80
D1          x			Treti  sloupec = 0x80
D2	        x			Ctvrty sloupec = 0x80	
D3	        x           Paty sloupec   = 0x7E
D4	        x
D5  x       x
D6  x       x
D7    x x x   
  
  */  
   
  unsigned char pismenoJ[7] = {0x40,0x00,0x60,0x80,0x80,0x80,0x7E};		// Pismeno J matice 5x7 pixelu (5x8) s tim ze horni pixely se nepouzivaji 
  char success = 0; 
  
  
  twi_init();			// inicializace I2C linky (SDA i SCL se nastavi do tretiho stavu a drzi log 1, diky PU resistorum)
  DisplayInit(); 		// inicializace displeje, nastavi kontrast, inverzi a neinverzi, a nakonec displej zapne
  DisplayClear();
  
  DisplayGotoXY(1, 0);		// skoci na pozici 1 0, tzn prvni sloupecek na strance 0
  write_data(pismenoA,7);	// napise pismeno A do pameti RAM displeje
  write_data(pismenoH,7);	// napise pismeno H do pameti RAM displeje
  write_data(pismenoO,7);	// napise pismeno O do pameti RAM displeje
  write_data(pismenoJ,7);	// napise pismeno J do pameti RAM displeje
}
