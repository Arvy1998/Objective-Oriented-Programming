#pragma once
//#ifndef CMDINTERFACE_H /* CodeBlocks GUI */	// ARVYDAS BARANAUSKAS PRIF-17/2
//#define CMDINTERFACE_H
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include <sstream>
#include <conio.h>

namespace windowsLibraryControler {
	using namespace std; // visur naudojame namespace std
	#define VERTICAL_LINE char(179) // viengubo remelio simboliai ir ju reiksmes
	#define HORIZONTAL_LINE char(196)
	#define BOTTOM_LEFT_CORNER char(192)
	#define BOTTOM_RIGHT_CORNER char(217)
	#define TOP_LEFT_CORNER char(218)
	#define TOP_RIGHT_CORNER char(191)

	#define VERTICAL_LINE_DOUBLE char(186) // dvigubo remelio simboliai ir ju reiksmes
	#define HORIZONTAL_LINE_DOUBLE char(205)
	#define BOTTOM_LEFT_CORNER_DOUBLE char(200)
	#define BOTTOM_RIGHT_CORNER_DOUBLE char(188)
	#define TOP_LEFT_CORNER_DOUBLE char(201)
	#define TOP_RIGHT_CORNER_DOUBLE char(187)

	#define DEFAULT_COLOR 0b00001111 // standartine objekto spalva
	#define DEFAULT_ACTIVE_COLOR 0b00001001 // standartine aktyvaus objekto spalva
	#define DEFAULT_TEXT_MESSAGE "Hello World!" // standartinis pranesimas indikatoriui
	#define DEFAULT_TEXT_MESSAGE_LENGTH 12 // standartinio pranesimo maksimalus ilgis
	#define DEFAULT_COORDINATE_RANGE 20 // standartine koordinates reiksme
	#define DEFAULT_TENSITY_VALUE 0b00010001 // standartas spalvos kaitos intensyvumui
	#define DEFULT_HUE_VALUE 0b00010001 // spalvos kaitos laipsnis
	#define DEFAULT_ALLIGNMENT_STYLE 0 // standartinis teksto lygiavimas arba meniu punktu atskyrimas
	#define DEFAULT_MENU_TITLE "No Title"

	class CoordinatesXY {	// bazinės klasės
	private:
		short coordinateX, coordinateY; // koordinates X ir Y
	public:
		CoordinatesXY();	// nustatom standartines pradines reikšmes
		bool setCoordinatesXY(short, short);	// koordinaciu nustatymas
		short getCoordinateX(); // X koordinates gavimas
		short getCoordinateY(); // Y koordinates gavimas
	};

	class WindowColorControler {
	private:
		short windowColor, fillColor; // lango ir uzpildo spalvos
	public:
		WindowColorControler();		// nustatom standartines pradines reikšmes
		~WindowColorControler();	// atstatyti pradinę cmd lango spalvą (pvz. juodai-balta)
		bool setWindowColor(short);		// nustatyti objekto spalva
		short getWindowColor();		// isgauti objekto spalva
		bool setFillColor(short);	// nustatyti objekto, kuris turi uzdara kontura, uzpildo spalva
		short getFillColor();	// gauti uzpildo spalvos koda
	};

	class WindowBorderStyleControler : public WindowColorControler {	// kitos klasės
	private:	// short spalva iš spalvaClass (private)
		CoordinatesXY windowSize, windowPosition;	// objekto dydzio ir pozicijos objektai, turintys X ir Y reiksmes
		bool borderActive, borderDouble;	// boolean kintamieji, nuo kuriu priklauso, remelis bus viengubas, dvigubas arba jo nebus
		friend class TextOutputControler;	// kad sekanciai klasei butu pasiekiami sioje klaseje esantys privatus objektai ir kintamieji
		friend class MenuControler;
	public:
		WindowBorderStyleControler();	// konstruktorius nustato numatytus parametrus
		bool setWindowSize(short, short);	// nustatyti lango dydi
		bool setWindowPosition(short, short);	// nustatyti lango pozicija
		bool setBorder(bool);	// nustatyti vienguba remeli
		bool setBorderDouble(bool);		// nustatyti dviguba remeli
		void drawWindowBorder(bool borderActive, bool borderDouble);	// piesia vienguba remeli arba jo nepiesia
		void drawWindowBorderDouble(bool borderDouble);		// piesia dviguba remeli
		void interpretBorder();		// atvaizdavimas i konsole
	};

	class IndicatorControler : public WindowColorControler, public CoordinatesXY {
	private:
		short textLength;	// max vieta skirta pranešimui 
		string textMessage;		// pranesimas
		bool rainbowActive;		// vaivorykstes efekto aktyvacija
		short tensity, hue;	// spalvos kaitos intensyvumas
		friend class MenuControler;
	public:
		IndicatorControler();	// konstruktorius
		bool setTextLength(short);	// nustatome objekto ilgi
		short getTextLength();	// isgauname objekto ilgi
		bool setTextMessage(string);	// nustatome, koks bus isvedamas pranesimas
		string getTextMessage();	// gauname pranesima
		short drawRainbowEffect(short, short);	// vaivorykstes efektas
		bool setTensity(short);
		bool setHue(short);
		bool setRainbowEffect(bool);
		short getTensity();
		short getHue();
		void interpretIndicator();	// interpretuojame pranesima lange
	};

	class TextOutputControler : public WindowBorderStyleControler {		// langas su tekstu (multiline)
	private:
		string message;		// tekstas
		short textColor;	// teksto spalva
		short allign;		// lygiavimo stilius (0-2)
		friend class MenuControler;		// draugiska klase
	public:
		TextOutputControler();	// konstruktorius
		bool setMessage(string);	// nustatyti, su kokiu tekstu bus dirbama
		string getMessage();
		void interpretText();		// { langasClass::show(); };	// teksto interpretacija lange
		string wrapText(short, short);	// "ipakuoja" teksta i remeli
		bool setTextColor(short);
		short getTextColor();
		bool setAllignStyle(short);
		short getAllignStyle();
	};

	class MenuControler : public WindowBorderStyleControler {
	private:
		short activeMenuItemColor, nonActiveMenuItemColor, menuTitleColor;	// aktyvaus ir neaktyvaus meniu objekto spalva
		vector <string> menuItemList;	// objektu sarasas [masyvas/vektorius]
		string menuTitle;	//	meniu pavadinimas, rodomas virsuje - centruotas
		bool menuActive, menuNumbering;		// ar meniu aktyvus ir ar punktai sunumeruoti
		int menuItemsSeparator; // nurodo, kokiais tarpais bus isdestyti meniu punktai lange
	public:
		MenuControler();	// konstruktorius
		void  interpretMenu(); //	 rodymui ir naudojimui // aktyvumas nustatomas per boolean kintamaji menuActive
		void  addMenuItem(string);	// vektoriu papildyti nauju meniu punktu
		bool  setMenuItemList(vector <string>);	// isgauti visa meniu punktu sarasa
		bool  setActiveMenuItemColor(short);	// nustatyti aktyvaus meniu objekto spalva
		vector <string> getMenuItemList();
		bool setMenuTitle(string);
		string getMenuTitle();
		void activeMenuFrame(vector <string>);	// valdo meniu aktyvuma arba ne-aktyvuma
		bool setMenuActive(bool);
		bool getMenuActive();
		bool setMenuNumbering(bool);
		bool getMenuNumbering();
		bool setNonActiveMenuItemColor(short);
		short getNonActiveMenuItemColor();
		bool setMenuTitleColor(short);
		short getMenuTitleColor();
		bool setMenuItemsSeparator(int);
		int getMenuItemsSeparator();
		short getActiveMenuItemColor();
	}; /*Objektas buna aktyvus, kai yra interpretuojamas jo pasirinkimo momentas*/
}
//#endif
