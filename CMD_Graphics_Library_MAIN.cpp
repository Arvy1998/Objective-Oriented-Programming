// LAB2 OOP.cpp : Defines the entry point for the console application.
// REKOMENDUOTINA Naudoti VISUAL STUDIO 2017
// ARVYDAS BARANAUSKAS PRIF-17/2
#include "stdafx.h"
#include "cmdInterface.h"

int main(int argc, char *argv[]) { // pirmiausiai sukuriame objektus
	//windowsLibraryControler::CoordinatesXY coordinates; // koordinates valdantysis objektas [jo greiciausiai neprireiks]
	//windowsLibraryControler::WindowColorControler colorBrush; // spalvos valdiklis [jo greiciausiai neprireiks]
	windowsLibraryControler::WindowBorderStyleControler newWindow; // lango remelio tipas, spalva, pozicija, dydis, uzpildo spalva
	windowsLibraryControler::IndicatorControler indicator;
	windowsLibraryControler::IndicatorControler indicator1;
	windowsLibraryControler::IndicatorControler indicator2;
	windowsLibraryControler::TextOutputControler outputText;
	windowsLibraryControler::TextOutputControler outputText1;	// galima piesti skirtingus langus tik su vienu objektu, taciau noredami
	windowsLibraryControler::TextOutputControler outputText2;	// pakeiti kazkuri parametra, jis pasikeis visiems langams -> to pasakoje sukuriu
	windowsLibraryControler::TextOutputControler outputText3;	// daug skirtingu objektu to pacio tipo langams
	windowsLibraryControler::MenuControler menuWindow;
	windowsLibraryControler::MenuControler menuWindow1;

	/*DEFAULT KOORDINACIU VALDYMAS #####################################################################################################*/
	//coordinates.setCoordinatesXY(10, 30);

	/*SPALVU VALDIKLIS*/ // tai bazine klase, todel jos main funkcijoje prireiks retai
	//colorBrush.setFillColor(0b11010001); // objektu, kurie patenka i tam tikra diapazona, spalva
	//colorBrush.setWindowColor(0b11010001); // objektu, kurie patenka i tam tikra diapazona, spalva

	/*REMELIO VALDYMAS, VIDAUS LAUKO SPALVA #####################################################################################################*/
	newWindow.setFillColor(0b00100110); // remeliu apriboto konturo spalva
	newWindow.setWindowColor(0b11010001); // pacio remelio spalva
	// jei [setBorder => true]  ir  [setBorderDouble => true], piesiamas dvigubas remelis
	// jei [setBorder => false]  ir  [setBorderDouble => false], tai remelio nera
	newWindow.setBorder(false); // nustato vienguba remeli
	newWindow.setBorderDouble(true); // nustato dviguba remeli
	newWindow.setWindowPosition(10, 3); // tasko, nuo kurio i apacia ir i desine bus piesiamas remelis
	newWindow.setWindowSize(30, 15); // remelio plotis ir aukstis
	newWindow.interpretBorder(); // funkcija, atvaizduojanti remeli

	/*INDIKATORIAUS VALDIKLIAI #####################################################################################################*/
	indicator.setCoordinatesXY(18, 10); // nustato vienos eilutes teksto pozicija lange
	indicator.setTextMessage(DEFAULT_TEXT_MESSAGE); // nustatome, koks pranesimas bus isvestas
	// jei pranesimas didesnis uz nurodyta max jo ilgio reiksme, jis yra apkarpomas iki maksimaliai galimos ribos
	indicator.setTextLength(DEFAULT_TEXT_MESSAGE_LENGTH); // nustatome pranesimo ilgio reiksme
	indicator.setWindowColor(0b10011010); // indikatoriaus spalvos valdiklis
	indicator.setRainbowEffect(true); // ar efektas bus paleistas nustato kintamasis boolean tipo
	// jei objektas paleidziamas, nustatome, kokiu reiksmiu norime, nenustacius reiksmiu bus naudojami konstruktoriai
	indicator.drawRainbowEffect(indicator.setTensity(0b00010001), indicator.setWindowColor(0b10010010)); // i argumenta ivedamas spalvu keitimo intensyvumas (intensyvumas 0 = efektas neaktyvus)
	// i argumenta taip pat ieina ir paskutiniu momentu buvusi spalva
	indicator.setHue(0b00010001); // hue (saturacijos laipsnis) reikalingas tam kad, kai po daug iteraciju lango ir simbolio spalva tampa vienoda, ju nesimato, todel kas keleta zingsniu reikia atnaujinti
	// "atskaitos" spalva atimant HUE reiksme // pvz. turime ilga string reiksme, ir po 5 simboliu, pritaikius vaivorykstes efekta, ju nematysime, nes tiek ekrano, tiek simbolio reiksmes tampa vienodos
	indicator.interpretIndicator(); // indikatoriaus interpretacine funkcija

	indicator1.setCoordinatesXY(12, 12);
	indicator1.setTextMessage("As esu indikatorius! :) OI NETELPU!! :( AAAAAAAAA");
	indicator1.setTextLength(23);
	indicator1.setWindowColor(0b01000111);
	indicator1.setRainbowEffect(false);
	//indicator1.drawRainbowEffect(indicator.setTensity(0b00010001), indicator.setWindowColor(0b10010010));
	//indicator1.setHue(0b00010001);
	indicator1.interpretIndicator();

	/*TEKSTINIO PRANESIMO LANGE VALDYMAS IR JO SKAIDYMAS PASIRINKTAME DIAPAZONE #####################################################################################################*/
	outputText.setWindowPosition(42, 3);
	outputText.setWindowSize(30, 15);
	outputText.setMessage("Be GIS nezinotumete, kur esate, net jei nezinote, kas tai yra: ESRI technologijos, kurias naudoja 75 % Fortune 500 kompaniju ir stai ka apie tai pasakoja isskirtine asmenybe - jos ikurejas ir vadovas Jackas Dangermondas LYGIAVIMAS KAIREJE!\n"); // nustatyti busima teksta lange
	outputText.setBorder(true);
	outputText.setBorderDouble(false);
	outputText.setFillColor(0b10010100);
	outputText.setWindowColor(0b01011011);
	outputText.setTextColor(0b01111101); // specifine teksto spalva
	outputText.setAllignStyle(0); // nustatyti lygiavimo stiliu
	outputText.interpretText(); // isveda teksta i ekrana su nurodytu stiliumi
	// 0 - lygiavimas kaireje // 1 - lygiavimas desineje // 2 - lygiavimas centre
	outputText1.setWindowPosition(10, 20);
	outputText1.setWindowSize(62, 15);
	outputText1.setMessage("Teksto langas - Lango atmaina turinti tas pacias savybes kaip ir langas. Papildoma savybe - tekstas, kuris atvaizduojamas lange. LYGIAVIMAS desiNEJe!\n"); // nustatyti busima teksta lange
	outputText1.setBorder(true);
	outputText1.setBorderDouble(true);
	outputText1.setFillColor(0b10000110);
	outputText1.setWindowColor(0b01001011);
	outputText1.setTextColor(0b10110011); // specifine teksto spalva
	outputText1.setAllignStyle(1);
	outputText1.interpretText();	// lygiavimo desineje pavyzdys

	// iaiterper indikatorius sugeba perdengti langa, jei atsiranda poreikis ta padaryti
	indicator2.setCoordinatesXY(11, 6);
	indicator2.setTextMessage("As esu indikatorius! :) DABAR TELPU, perdenGIU LANga ir esu SPALVINGAS! :) AAAAAAAAA");
	indicator2.setTextLength(82);
	indicator2.setWindowColor(0b01000111);
	indicator2.setRainbowEffect(true);
	indicator2.drawRainbowEffect(indicator.setTensity(0b11000001), indicator.setWindowColor(0b10010001));
	indicator2.setHue(0b01011001);
	indicator2.interpretIndicator();

	outputText2.setWindowPosition(10, 36);
	outputText2.setWindowSize(80, 10);
	outputText2.setMessage("Tekstas OOO NETURIU REMELIO :D (angl. text, pranc. texte) - duomenys, pateikiami zenklais, simboliais, zodziais, zodziu junginiais, MAN NEPATINKA BUTI DEMESIO CENTRE! sakiniais, pastraipomis, lentelemis, isnasomis ar kitais zenklu junginiais, parengti siekiant perteikti prasme ir darant prielaida, jog jie suvokiami skaitytoju, mokanciu tam tikra naturaliaja arba dirbtine kalba.\n"); // nustatyti busima teksta lange
	outputText2.setBorder(false);
	outputText2.setBorderDouble(false);
	outputText2.setFillColor(0b00100110);
	outputText2.setWindowColor(0b01101001);
	outputText2.setTextColor(0b10110100); // specifine teksto spalva
	outputText2.setAllignStyle(2);
	outputText2.interpretText();	// lygiavimo centre be remelio pavyzdys

	outputText3.setWindowPosition(14, 26);
	outputText3.setWindowSize(40, 8);
	outputText3.setMessage("ARVYDAS BARANAUSKAS paiso langa ant kito lango :o            (didelis tarpas)           PRIF-17/2"); // nustatyti busima teksta lange
	outputText3.setBorder(true);
	outputText3.setBorderDouble(false);
	outputText3.setFillColor(0b11000000);
	outputText3.setWindowColor(0b10010011);
	outputText3.setTextColor(0b00001100); // specifine teksto spalva
	outputText3.setAllignStyle(2);
	outputText3.interpretText();

	/*MENIU VALDYKLIAI    #####################################################################################################*/
	menuWindow.setWindowPosition(10, 48);		// trys pavyzdiniai langai be funkcionalumo //
	menuWindow.setWindowSize(24, 12);
	menuWindow.setBorderDouble(true);
	menuWindow.setBorder(false);
	menuWindow.setMenuNumbering(false);
	menuWindow.setMenuTitle("MENIU pavadinimas!");
	menuWindow.setMenuActive(false);	// active = false, todel setActiveMenuColor mums nereikia
	menuWindow.addMenuItem("papildomas punktas");
	//menuWindow.setActiveMenuItemColor(DEFAULT_ACTIVE_COLOR);
	menuWindow.setWindowColor(0b00010100);
	menuWindow.setFillColor(0b10001100);
	menuWindow.setNonActiveMenuItemColor(0b00001111);
	menuWindow.setMenuTitleColor(0b01001001);
	menuWindow.setMenuItemsSeparator(1);	// kiek langu skirs kiekviena meniu punkta
	menuWindow.interpretMenu();

	menuWindow.setWindowPosition(36, 48);
	menuWindow.setWindowSize(24, 12);
	menuWindow.setBorderDouble(false);
	menuWindow.setBorder(true);
	menuWindow.setMenuNumbering(false);
	menuWindow.setMenuTitle("as neturiu tarpu!");
	menuWindow.setMenuActive(false);	// active = false, todel setActiveMenuColor mums nereikia
	menuWindow.setMenuItemList({"START PLAYING", "INSTRUCTIONS", "EXIT"});
	menuWindow.addMenuItem("ABOUT");
	//menuWindow.setActiveMenuItemColor(DEFAULT_ACTIVE_COLOR);
	menuWindow.setWindowColor(0b01010001);
	menuWindow.setFillColor(0b10001000);
	menuWindow.setNonActiveMenuItemColor(0b11001111);
	menuWindow.setMenuTitleColor(0b11001101);
	menuWindow.setMenuItemsSeparator(0);	// kiek langu skirs kiekviena meniu punkta
	menuWindow.interpretMenu();

	menuWindow.setWindowPosition(62, 48);
	menuWindow.setWindowSize(24, 22);
	menuWindow.setBorderDouble(false);
	menuWindow.setBorder(true);
	menuWindow.setMenuNumbering(true);
	menuWindow.setMenuTitle("as sunumeruotas");
	menuWindow.setMenuActive(false);	// active = false, todel setActiveMenuColor mums nereikia
	menuWindow.setMenuItemList({ "STARTAS", "INSTRUKCIJOS", "PAGALBA" });
	menuWindow.addMenuItem("ISEITI");
	menuWindow.addMenuItem("Dideli TARPAI");
	//menuWindow.setActiveMenuItemColor(DEFAULT_ACTIVE_COLOR);
	menuWindow.setWindowColor(0b11010001);
	menuWindow.setFillColor(0b11101000);
	menuWindow.setNonActiveMenuItemColor(0b11001011);
	menuWindow.setMenuTitleColor(0b11101001);
	menuWindow.setMenuItemsSeparator(3);	// kiek langu skirs kiekviena meniu punkta
	menuWindow.interpretMenu();

	//paaiskinimas, kaip valdyti aktyvu meniu, idetas i indikatoriu
	outputText1.setWindowPosition(10, 61);
	outputText1.setWindowSize(50, 9);
	outputText1.setMessage("jei aktyvus meniu veikia lange, ji galima valdyti rodyklemis atitinkamai judant i virsu arba apacia. valdymas imanomas ir raidemis W bei S (UP/DOWN).\n");
	outputText1.setBorder(false);	// neimanoma uzeiti uz meniu, nes punktu kiekis yra ribojamas turimu punktu skaiciumi (veikia kaip konstanta)
	outputText1.setBorderDouble(true);
	outputText1.setFillColor(0b11101000);
	outputText1.setWindowColor(0b10101001);
	outputText1.setTextColor(0b00110000);
	outputText1.setAllignStyle(1);
	outputText1.interpretText();

	/*AKTYVAUS MENIU VALDYKLIAI    #####################################################################################################*/
	menuWindow1.setWindowPosition(10, 71);
	menuWindow1.setWindowSize(24, 22);
	menuWindow1.setBorderDouble(true);
	menuWindow1.setBorder(false);
	menuWindow1.setMenuNumbering(true);
	menuWindow1.setMenuTitle("AKTYVUSIS MENIU");
	menuWindow1.setMenuActive(true);	// active = true, todel setActiveMenuColor atkomentavome
	menuWindow1.setMenuItemList({ "STARTAS", "INSTRUKCIJOS", "PAGALBA" });
	menuWindow1.addMenuItem("ISEITI");
	menuWindow1.addMenuItem("ISEITI, BET PRO KITUR");
	menuWindow1.setActiveMenuItemColor(DEFAULT_ACTIVE_COLOR);
	menuWindow1.setWindowColor(0b10010001);
	menuWindow1.setFillColor(0b00001100);
	menuWindow1.setNonActiveMenuItemColor(0b11001011);
	menuWindow1.setMenuTitleColor(0b01101001);
	menuWindow1.setMenuItemsSeparator(2);	// kiek langu skirs kiekviena meniu punkta
	menuWindow1.interpretMenu();
    return 0;
}
