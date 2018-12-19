#include "stdafx.h"
#include "cmdInterface.h"	// ARVYDAS BARANAUSKAS PRIF-17/2

HANDLE consoleControl = GetStdHandle(STD_OUTPUT_HANDLE);
/*FUNKCIJU APRASAI*/
namespace windowsLibraryControler {
	CoordinatesXY::CoordinatesXY() {
		coordinateX = DEFAULT_COORDINATE_RANGE;
		coordinateY = DEFAULT_COORDINATE_RANGE;
	};

	bool CoordinatesXY::setCoordinatesXY(short screenPositionX, short screenPositionY) {
		this->coordinateX = screenPositionX;
		this->coordinateY = screenPositionY;
		return true;
	};

	short CoordinatesXY::getCoordinateX() {
		return coordinateX;
	};

	short CoordinatesXY::getCoordinateY() {
		return coordinateY;
	};

	WindowColorControler::WindowColorControler() {
		windowColor = DEFAULT_COLOR;
		fillColor = DEFAULT_COLOR;
	};

	WindowColorControler::~WindowColorControler() {
		SetConsoleTextAttribute(consoleControl, DEFAULT_COLOR);
	};

	bool WindowColorControler::setWindowColor(short currentColor) {
		this->windowColor = currentColor;
		return true;
	};

	short WindowColorControler::getWindowColor() {
		return windowColor;
	};

	bool WindowColorControler::setFillColor(short currentColor) {
		this->fillColor = currentColor;
		return true;
	};

	short WindowColorControler::getFillColor() {
		return fillColor;
	};

	WindowBorderStyleControler::WindowBorderStyleControler() {
		borderActive = true;
		borderDouble = true;
	};

	bool WindowBorderStyleControler::setWindowSize(short screenPositionX, short screenPositionY) {
		this->windowSize.setCoordinatesXY(screenPositionX, screenPositionY);
		return true;
	};

	bool WindowBorderStyleControler::setWindowPosition(short screenPositionX, short screenPositionY) {
		this->windowPosition.setCoordinatesXY(screenPositionX, screenPositionY);
		return true;
	};

	bool WindowBorderStyleControler::setBorder(bool isActive) {
		this->borderActive = isActive;
		return true;
	};

	bool WindowBorderStyleControler::setBorderDouble(bool isActive) {
		this->borderDouble = isActive;
		return true;
	};

	void WindowBorderStyleControler::drawWindowBorder(bool borderActive, bool borderDouble) {
		short temporaryCoordinateX, temporaryCoordinateY, temporaryPositionX, temporaryPositionY;
		//this->windowPosition.setCoordinatesXY(1, 4);
		temporaryPositionX = this->windowPosition.getCoordinateX();
		temporaryPositionY = this->windowPosition.getCoordinateY();
		//this->windowSize.setCoordinatesXY(30, 15);
		temporaryCoordinateX = this->windowSize.getCoordinateX();
		temporaryCoordinateY = this->windowSize.getCoordinateY();
		windowPosition.setCoordinatesXY(temporaryCoordinateX, temporaryCoordinateY);
		windowSize.setCoordinatesXY(temporaryCoordinateX, temporaryCoordinateY);
		setWindowPosition(temporaryPositionX, temporaryPositionY);
		setWindowSize(temporaryCoordinateX, temporaryCoordinateY);
		COORD drawingPositionCoordinates = { temporaryCoordinateX,
											 temporaryCoordinateY };
		SetConsoleTextAttribute(consoleControl, this->getWindowColor());
		if (borderActive && !borderDouble) {
			for (auto iteratorForY = 1; iteratorForY <= temporaryCoordinateY; iteratorForY++) {
				for (auto iteratorForX = 1; iteratorForX <= temporaryCoordinateX; iteratorForX++) {
					if ((iteratorForY == 1 || iteratorForY == temporaryCoordinateY)
						&& (iteratorForX != 1 || iteratorForX != temporaryCoordinateX)) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX() + iteratorForX - 1;
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY() + iteratorForY - 1;
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << HORIZONTAL_LINE;
					}
					if ((iteratorForY != 1 || iteratorForY != temporaryCoordinateY)
						&& (iteratorForX == 1 || iteratorForX == temporaryCoordinateX)) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX() + iteratorForX - 1;
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY() + iteratorForY - 1;
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << VERTICAL_LINE;
					}
					if (iteratorForY == 1 && iteratorForX == 1) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX();
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY();
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << TOP_LEFT_CORNER;
					}
					if (iteratorForY == temporaryCoordinateY && iteratorForX == 1) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX();
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY() + temporaryCoordinateY - 1;
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << BOTTOM_LEFT_CORNER;
					}
					if (iteratorForY == 1 && iteratorForX == temporaryCoordinateX) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX() + temporaryCoordinateX - 1;
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY();
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << TOP_RIGHT_CORNER;
					}
					if (iteratorForY == temporaryCoordinateY && iteratorForX == temporaryCoordinateX) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX() + temporaryCoordinateX - 1;
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY() + temporaryCoordinateY - 1;
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << BOTTOM_RIGHT_CORNER;
					}
				}
			}
		}
	};

	void WindowBorderStyleControler::drawWindowBorderDouble(bool borderDouble) {
		short temporaryCoordinateX, temporaryCoordinateY, temporaryPositionX, temporaryPositionY;
		//this->windowPosition.setCoordinatesXY(1, 4);
		temporaryPositionX = this->windowPosition.getCoordinateX();
		temporaryPositionY = this->windowPosition.getCoordinateY();
		//this->windowSize.setCoordinatesXY(30, 15);
		temporaryCoordinateX = this->windowSize.getCoordinateX();
		temporaryCoordinateY = this->windowSize.getCoordinateY();
		windowPosition.setCoordinatesXY(temporaryCoordinateX, temporaryCoordinateY);
		windowSize.setCoordinatesXY(temporaryCoordinateX, temporaryCoordinateY);
		setWindowPosition(temporaryPositionX, temporaryPositionY);
		setWindowSize(temporaryCoordinateX, temporaryCoordinateY);
		COORD drawingPositionCoordinates = { temporaryCoordinateX,
											temporaryCoordinateY };
		SetConsoleTextAttribute(consoleControl, this->getWindowColor());
		if (borderDouble) {
			for (auto iteratorForY = 1; iteratorForY <= temporaryCoordinateY; iteratorForY++) {
				for (auto iteratorForX = 1; iteratorForX <= temporaryCoordinateX; iteratorForX++) {
					if ((iteratorForY == 1 || iteratorForY == temporaryCoordinateY)
						&& (iteratorForX != 1 || iteratorForX != temporaryCoordinateX)) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX() + iteratorForX - 1;
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY() + iteratorForY - 1;
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << HORIZONTAL_LINE_DOUBLE;
					}
					if ((iteratorForY != 1 || iteratorForY != temporaryCoordinateY)
						&& (iteratorForX == 1 || iteratorForX == temporaryCoordinateX)) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX() + iteratorForX - 1;
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY() + iteratorForY - 1;
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << VERTICAL_LINE_DOUBLE;
					}
					if (iteratorForY == 1 && iteratorForX == 1) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX();
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY();
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << TOP_LEFT_CORNER_DOUBLE;
					}
					if (iteratorForY == temporaryCoordinateY && iteratorForX == 1) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX();
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY() + temporaryCoordinateY - 1;
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << BOTTOM_LEFT_CORNER_DOUBLE;
					}
					if (iteratorForY == 1 && iteratorForX == temporaryCoordinateX) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX() + temporaryCoordinateX - 1;
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY();
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << TOP_RIGHT_CORNER_DOUBLE;
					}
					if (iteratorForY == temporaryCoordinateY && iteratorForX == temporaryCoordinateX) {
						drawingPositionCoordinates.X = this->windowPosition.getCoordinateX() + temporaryCoordinateX - 1;
						drawingPositionCoordinates.Y = this->windowPosition.getCoordinateY() + temporaryCoordinateY - 1;
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						cout << BOTTOM_RIGHT_CORNER_DOUBLE;
					}
				}
			}
		}
	};

	void WindowBorderStyleControler::interpretBorder() {
		short temporaryCoordinateX, temporaryCoordinateY, temporaryPositionX, temporaryPositionY;
		temporaryPositionX = this->windowPosition.getCoordinateX();
		temporaryPositionY = this->windowPosition.getCoordinateY();
		temporaryCoordinateX = this->windowSize.getCoordinateX();
		temporaryCoordinateY = this->windowSize.getCoordinateY();
		windowPosition.setCoordinatesXY(temporaryCoordinateX, temporaryCoordinateY);
		windowSize.setCoordinatesXY(temporaryCoordinateX, temporaryCoordinateY);
		setWindowPosition(temporaryPositionX, temporaryPositionY);
		setWindowSize(temporaryCoordinateX, temporaryCoordinateY);
		COORD drawingPositionCoordinates = { temporaryPositionX,
											temporaryPositionY };
		for (auto iterator = 1; iterator < temporaryCoordinateY; iterator++) {
			drawingPositionCoordinates.Y = temporaryPositionY + iterator;
			SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
			SetConsoleTextAttribute(consoleControl, this->getFillColor());
			cout << setw(temporaryCoordinateX) << ' ';
			SetConsoleTextAttribute(consoleControl, this->getWindowColor());
		}
		drawWindowBorder(borderActive, borderDouble);
		drawWindowBorderDouble(borderDouble);
	};

	IndicatorControler::IndicatorControler() {
		textMessage = DEFAULT_TEXT_MESSAGE;
		textLength = DEFAULT_TEXT_MESSAGE_LENGTH;
		tensity = DEFAULT_TENSITY_VALUE;
		hue = DEFULT_HUE_VALUE;
		rainbowActive = false;
	};

	bool IndicatorControler::setTextLength(short textLength) {
		this->textLength = textLength;
		return true;
	};

	short IndicatorControler::getTextLength() {
		return textLength;
	};

	bool IndicatorControler::setTextMessage(string textMessage) {
		this->textMessage = textMessage;
		return true;
	};

	string IndicatorControler::getTextMessage() {
		return textMessage;
	};

	short IndicatorControler::drawRainbowEffect(short tensity, short currentColor) {
		currentColor += tensity;
		return currentColor;
	};

	bool IndicatorControler::setTensity(short tensity) {
		this->tensity = tensity;
		return true;
	};

	short IndicatorControler::getTensity() {
		return tensity;
	};

	bool IndicatorControler::setHue(short hue) {
		this->hue = hue;
		return true;
	};

	short IndicatorControler::getHue() {
		return hue;
	};

	bool IndicatorControler::setRainbowEffect(bool isActive) {
		this->rainbowActive = isActive;
		return true;
	};

	void IndicatorControler::interpretIndicator() {
		short temporaryPositionX, temporaryPositionY;
		char temporaryMessageCharArray[254]; // default laikinojo kintamojo dydis - 254 simboliu
		temporaryPositionX = this->getCoordinateX();
		temporaryPositionY = this->getCoordinateY();
		this->setCoordinatesXY(temporaryPositionX, temporaryPositionY);
		COORD drawingPositionCoordinates = { temporaryPositionX,
											temporaryPositionY };
		strcpy_s(temporaryMessageCharArray, this->getTextMessage().c_str());
		for (auto iterator = 0; iterator < this->getTextLength(); iterator++) {
			drawingPositionCoordinates.X += 1;
			if (this->rainbowActive) {
				if (iterator % 5 != 0) {
					this->setWindowColor(drawRainbowEffect(this->getTensity(), this->getWindowColor()));
				}
				else this->setWindowColor(drawRainbowEffect(this->getTensity(), this->getWindowColor() - this->getHue()));
			}
			SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
			SetConsoleTextAttribute(consoleControl, this->getWindowColor());
			cout << temporaryMessageCharArray[iterator];
		}
	};

	TextOutputControler::TextOutputControler() {
		message = DEFAULT_TEXT_MESSAGE;
		allign = DEFAULT_ALLIGNMENT_STYLE;
		textColor = DEFAULT_COLOR;
	};

	bool TextOutputControler::setMessage(string message) {
		this->message = message;
		return true;
	};

	string TextOutputControler::getMessage() {
		return message;
	};

	void TextOutputControler::interpretText() {
		short temporaryCoordinateX, temporaryCoordinateY, temporaryPositionX, temporaryPositionY;
		string temporaryText = this->getMessage();
		vector <string> temporaryTextSliced;
		WindowBorderStyleControler::interpretBorder();
		temporaryPositionX = this->windowPosition.getCoordinateX();
		temporaryPositionY = this->windowPosition.getCoordinateY();
		temporaryCoordinateX = this->windowSize.getCoordinateX();
		temporaryCoordinateY = this->windowSize.getCoordinateY();
		this->setWindowPosition(temporaryPositionX, temporaryPositionY);
		this->setWindowSize(temporaryCoordinateX, temporaryCoordinateY);
		COORD drawingPositionCoordinates = { temporaryPositionX + 1,
											 temporaryPositionY + 1 };
		temporaryText = wrapText(temporaryCoordinateX - 2, temporaryCoordinateY);
		if (this->getAllignStyle() == 0) {
			SetConsoleTextAttribute(consoleControl, this->getTextColor());
			for (auto iterator = 0; iterator < temporaryText.length(); iterator++) {
				SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
				cout << temporaryText[iterator];
				drawingPositionCoordinates.X++;
				if (temporaryText[iterator] == '\n') {
					drawingPositionCoordinates.Y++;
					drawingPositionCoordinates.X = temporaryPositionX + 1;
				}
			}
		}
		if (this->getAllignStyle() == 1) {
			istringstream IOStringStream(temporaryText);
			size_t position;
			for (string textLine; getline(IOStringStream, textLine); ) {
				SetConsoleTextAttribute(consoleControl, this->getTextColor());
				SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
				position = temporaryCoordinateX - 2 - textLine.length();
				drawingPositionCoordinates.X += position;
				SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
				cout << textLine << endl;
				drawingPositionCoordinates.Y++;
				drawingPositionCoordinates.X = temporaryPositionX + 1;
			}
		}
		if (this->getAllignStyle() == 2) {
			istringstream IOStringStream(temporaryText);
			size_t position;
			for (string textLine; getline(IOStringStream, textLine); ) {
				SetConsoleTextAttribute(consoleControl, this->getTextColor());
				SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
				position = ((temporaryCoordinateX - 2) / 2) - textLine.length() / 2;
				drawingPositionCoordinates.X += position;
				SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
				cout << textLine << endl;
				drawingPositionCoordinates.Y++;
				drawingPositionCoordinates.X = temporaryPositionX + 1;
			}
		}
	};

	string TextOutputControler::wrapText(short lineLength, short rowsCount) {
		int spaceLocation, position, subCounter = 0;
		string temporaryText = this->getMessage(), wrappedText;
		for (auto iterator = 0; iterator < rowsCount; iterator++) {
			spaceLocation = temporaryText.rfind(' ', lineLength);
			if (spaceLocation != string::npos) {
				temporaryText.at(spaceLocation) = '\n';
			}
			position = temporaryText.find('\n');
			if (position != string::npos) {
				wrappedText += "\n" + temporaryText.substr(0, position);
			}
			else if (position == string::npos && subCounter == 0) {
				wrappedText += "\n" + temporaryText;
				subCounter++;
			}
			temporaryText = temporaryText.substr(temporaryText.find("\n") + 1);
		}
		this->setMessage(wrappedText);
		return this->getMessage();
	};

	bool TextOutputControler::setTextColor(short currentColor) {
		this->textColor = currentColor;
		return true;
	};

	short TextOutputControler::getTextColor() {
		return textColor;
	};

	bool TextOutputControler::setAllignStyle(short allign) {
		this->allign = allign;
		return true;
	};

	short TextOutputControler::getAllignStyle() {
		return allign;
	};

	MenuControler::MenuControler() {
		menuItemList = { "FirstDefaultItem", "SecondDefaultItem", "ThirdDefaultItem" };
		menuItemsSeparator = DEFAULT_ALLIGNMENT_STYLE;
		activeMenuItemColor = DEFAULT_ACTIVE_COLOR;
		nonActiveMenuItemColor = DEFAULT_COLOR;
		menuTitleColor = DEFAULT_COLOR;
		menuTitle = DEFAULT_MENU_TITLE;
		menuNumbering = false;
		menuActive = false;
	};

	void MenuControler::interpretMenu() {
		activeMenuFrame(this->getMenuItemList());
	};

	void MenuControler::addMenuItem(string itemID) {
		this->menuItemList.push_back(itemID);
	};

	bool MenuControler::setMenuItemList(vector <string> itemIDList) {
		this->menuItemList = itemIDList;
		return true;
	};

	bool MenuControler::setActiveMenuItemColor(short activeColor) {
		this->activeMenuItemColor = activeColor;
		return true;
	};

	vector <string> MenuControler::getMenuItemList() {
		return menuItemList;
	};

	bool MenuControler::setMenuTitle(string menuTitle) {
		this->menuTitle = menuTitle;
		return true;
	};

	string MenuControler::getMenuTitle() {
		return menuTitle;
	};

	void MenuControler::activeMenuFrame(vector <string> itemIDList) {
		short temporaryCoordinateX, temporaryCoordinateY, temporaryPositionX, temporaryPositionY;
		WindowBorderStyleControler::interpretBorder();
		int reactToKeyboarArrow, controlerIndex = 0; // pagal numatytaji nustatyma pradedantysis pasirinkimo variantas buna pirmasis
		size_t position;
		temporaryPositionX = this->windowPosition.getCoordinateX();
		temporaryPositionY = this->windowPosition.getCoordinateY();
		temporaryCoordinateX = this->windowSize.getCoordinateX();
		temporaryCoordinateY = this->windowSize.getCoordinateY();
		this->setWindowPosition(temporaryPositionX, temporaryPositionY);
		this->setWindowSize(temporaryCoordinateX, temporaryCoordinateY);
		COORD drawingPositionCoordinates = { temporaryPositionX + 1,
											 temporaryPositionY + 1 };		
		position = ((temporaryCoordinateX - 2) / 2) - this->getMenuTitle().length() / 2;
		drawingPositionCoordinates.X += position;
		SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
		SetConsoleTextAttribute(consoleControl, this->getMenuTitleColor());
		cout << this->getMenuTitle();
		drawingPositionCoordinates.Y += 2;
		drawingPositionCoordinates.X = temporaryPositionX + 1;
		if (!this->getMenuActive()) {
			if (this->getMenuNumbering()) {
				for (auto iterator = 0; iterator < this->menuItemList.size(); iterator++) {
					position = ((temporaryCoordinateX - 2) / 2) - menuItemList[iterator].length() / 2;
					drawingPositionCoordinates.X += position;
					SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
					SetConsoleTextAttribute(consoleControl, this->getNonActiveMenuItemColor());
					cout << iterator + 1 << ")" << this->menuItemList[iterator];
					drawingPositionCoordinates.Y += this->getMenuItemsSeparator() + 1;
					drawingPositionCoordinates.X = temporaryPositionX + 1;
				}
			}
			if (!this->getMenuNumbering()) {
				for (auto iterator = 0; iterator < this->menuItemList.size(); iterator++) {
					position = ((temporaryCoordinateX - 2) / 2) - menuItemList[iterator].length() / 2;
					drawingPositionCoordinates.X += position;
					SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
					SetConsoleTextAttribute(consoleControl, this->getNonActiveMenuItemColor());
					cout << this->menuItemList[iterator];
					drawingPositionCoordinates.Y += this->getMenuItemsSeparator() + 1;
					drawingPositionCoordinates.X = temporaryPositionX + 1;
				}
			}
		}
		if (this->getMenuActive()) {
			if (!this->getMenuNumbering()) {
				while (this->getMenuActive()) {
					for (auto iterator = 0; iterator < this->menuItemList.size(); iterator++) {
						position = ((temporaryCoordinateX - 2) / 2) - menuItemList[iterator].length() / 2;
						drawingPositionCoordinates.X += position;
						SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
						if (iterator == controlerIndex) {
							SetConsoleTextAttribute(consoleControl, this->getActiveMenuItemColor());
							cout << this->menuItemList[iterator];
							drawingPositionCoordinates.Y += this->getMenuItemsSeparator() + 1;
							drawingPositionCoordinates.X = temporaryPositionX + 1;
						}
						else {
							SetConsoleTextAttribute(consoleControl, this->getNonActiveMenuItemColor());
							cout << this->menuItemList[iterator];
							drawingPositionCoordinates.Y += this->getMenuItemsSeparator() + 1;
							drawingPositionCoordinates.X = temporaryPositionX + 1;
						}
					}
					reactToKeyboarArrow = _getch();
					switch (reactToKeyboarArrow) {
					case 72: { // rodykle i virsu
						controlerIndex--;
						if (controlerIndex <= 0) {
							controlerIndex = 0;
						} break;
					}
					case 80: { // rodykle i apacia
						controlerIndex++;
						if (controlerIndex >= this->getMenuItemList().size() - 1) {
							controlerIndex = this->getMenuItemList().size() - 1;
						} break;
					}
					default: { break; }
					}
					drawingPositionCoordinates.Y = temporaryPositionY + 3;
					drawingPositionCoordinates.X = temporaryPositionX + 1;
				}
			}
		}
		if (this->getMenuNumbering()) {
			while (this->getMenuActive()) {
				for (auto iterator = 0; iterator < this->menuItemList.size(); iterator++) {
					position = ((temporaryCoordinateX - 2) / 2) - menuItemList[iterator].length() / 2;
					drawingPositionCoordinates.X += position;
					SetConsoleCursorPosition(consoleControl, drawingPositionCoordinates);
					if (iterator == controlerIndex) {
						SetConsoleTextAttribute(consoleControl, this->getActiveMenuItemColor());
						cout << iterator + 1 << ")" << this->menuItemList[iterator];
						drawingPositionCoordinates.Y += this->getMenuItemsSeparator() + 1;
						drawingPositionCoordinates.X = temporaryPositionX + 1;
					}
					else {
						SetConsoleTextAttribute(consoleControl, this->getNonActiveMenuItemColor());
						cout << iterator + 1 << ")" << this->menuItemList[iterator];
						drawingPositionCoordinates.Y += this->getMenuItemsSeparator() + 1;
						drawingPositionCoordinates.X = temporaryPositionX + 1;
					}
				}
				reactToKeyboarArrow = _getch();
				switch (reactToKeyboarArrow) {
				case 72: { // rodykle i virsu
					controlerIndex--;
					if (controlerIndex <= 0) {
						controlerIndex = 0;
					} break;
				}
				case 80: { // rodykle i apacia
					controlerIndex++;
					if (controlerIndex >= this->getMenuItemList().size() - 1) {
						controlerIndex = this->getMenuItemList().size() - 1;
					} break;
				}
				default: { break; }
				}
				drawingPositionCoordinates.Y = temporaryPositionY + 3;
				drawingPositionCoordinates.X = temporaryPositionX + 1;
			}
		}
	};

	bool MenuControler::setMenuActive(bool isActive) {
		this->menuActive = isActive;
		return true;
	};

	bool MenuControler::getMenuActive() {
		return menuActive;
	};

	bool MenuControler::setMenuNumbering(bool isActive) {
		this->menuNumbering = isActive;
		return true;
	};

	bool MenuControler::getMenuNumbering() {
		return menuNumbering;
	};

	bool MenuControler::setNonActiveMenuItemColor(short currentColor) {
		this->nonActiveMenuItemColor = currentColor;
		return true;
	};

	short MenuControler::getNonActiveMenuItemColor() {
		return nonActiveMenuItemColor;
	};

	bool MenuControler::setMenuTitleColor(short currentColor) {
		this->menuTitleColor = currentColor;
		return true;
	};

	short MenuControler::getMenuTitleColor() {
		return menuTitleColor;
	};

	bool MenuControler::setMenuItemsSeparator(int currentIndex) {
		this->menuItemsSeparator = currentIndex;
		return true;
	};

	int MenuControler::getMenuItemsSeparator() {
		return menuItemsSeparator;
	};

	short MenuControler::getActiveMenuItemColor() {
		return activeMenuItemColor;
	};
}
