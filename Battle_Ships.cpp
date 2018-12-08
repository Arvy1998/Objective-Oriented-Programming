#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <chrono>
#include <windows.h>
#include <thread>
#include <bitset>
#include <algorithm>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

const char LANG_TUSCIAS = char(176);
const char LANG_LAIVAS = char(219);
const char LANG_SPROGES = 'X';
const char LANG_KIAURAS = 'o';
const char LANG_ATMESTAS = 'x';
const char KLAIDA = char(7);
int pataikyta_kartu_player = 0;
int pataikyta_kartu_AI = 0;
int ejimu_kiekis;
int rezimas = 1; // default rezimas yra lengvas

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

class C_laukas {
private:
	char laukas[12][12];
	int counteris = 0;
	int color;

public:
	void print_field(int color) {
		cout << "   ";
		for (auto j = 0; j < 10; j++) {
			if (j % 2 == 0) {
				SetConsoleTextAttribute(console, 0b11111100);
				cout << j;
			}
			else {
				SetConsoleTextAttribute(console, 0b11110000);
				cout << j;
			}
		}
		cout << endl << "  ";
		for (int g = 0; g < 12; g++) {
			SetConsoleTextAttribute(console, 0b11110100);
			cout << char(220);
		}
		cout << endl;
		for (int y = 0; y < 10; y++) {
			if (y % 2 == 0) {
				SetConsoleTextAttribute(console, 0b11111100);
				cout << " " << y;
			}
			else {
				SetConsoleTextAttribute(console, 0b11110000);
				cout << " " << y;
			}
			SetConsoleTextAttribute(console, 0b11110100);
			cout << char(219);
			for (int x = 0; x < 10; x++) {
				if (laukas[x][y] == LANG_LAIVAS) {
					if (color == 0b11111100) {
						SetConsoleTextAttribute(console, 0b10010111);
						cout << char(176);
						SetConsoleTextAttribute(console, 0b11110000);
					}
					else {
						SetConsoleTextAttribute(console, color);
						cout << laukas[x][y];
						SetConsoleTextAttribute(console, 0b11110000);
					}
				}
				else {
					if (laukas[x][y] == LANG_SPROGES) {
						if (color == 0b11111100) {
							SetConsoleTextAttribute(console, 0b10011010);
							cout << laukas[x][y];
						}
						else {
							SetConsoleTextAttribute(console, 0b10011100);
							cout << laukas[x][y];
						}
					}
					else if (laukas[x][y] == LANG_ATMESTAS) {
						SetConsoleTextAttribute(console, 0b10011101);
						cout << laukas[x][y];
					}
					else {
						SetConsoleTextAttribute(console, 0b10010111);
						cout << laukas[x][y];
						SetConsoleTextAttribute(console, 0b11110000);
					}
				}
				if (x == 9) {
					SetConsoleTextAttribute(console, 0b11110100);
					cout << char(219);
					SetConsoleTextAttribute(console, 0b11110000);
				}
			}
			if (y == 4) {
				SetConsoleTextAttribute(console, 0b11110000);
				cout << "       Kartu ";
			}
			if (y == 5) {
				SetConsoleTextAttribute(console, 0b11110000);
				cout << "     pataikyta:";
			}
			if (y == 6) {
				SetConsoleTextAttribute(console, 0b11110000);
				cout << "         ";
				SetConsoleTextAttribute(console, 0b11111100);
				cout << counteris;
			}
			SetConsoleTextAttribute(console, 0b11110000);
			cout << endl;
		}
		cout << "  ";
		for (int g = 0; g < 12; g++) {
			SetConsoleTextAttribute(console, 0b11110100);
			cout << char(223);
		}
		cout << endl;
		SetConsoleTextAttribute(console, 0b11110000);
	}

	void clear() {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				laukas[x][y] = LANG_TUSCIAS;
			}
		}
	}

	bool place_ship(int x1, int y1, int x2, int y2) {
		bool OK = true;
		int x;
		if (x1 > x2) {
			x = x1;
			x1 = x2;
			x2 = x;
		}
		if (y1 > y2) {
			x = y1;
			y1 = y2;
			y2 = x;
		}
		if (x1 < 0 || x1 > 9 || x2 < 0 || x2 > 9 ||
			y1 < 0 || y1 > 9 || y2 < 0 || y2 > 9) {
			OK = false;
		}
		for (int y = y1; y <= y2; y++) {
			for (int x = x1; x <= x2; x++) {
				if (
					laukas[x][y] != LANG_TUSCIAS ||
					laukas[x + 1 - (x + 1) / 10][y] != LANG_TUSCIAS ||
					laukas[x + 1 - (x + 1) / 10][y + 1 - (y + 1) / 10] != LANG_TUSCIAS ||
					laukas[x + 1 - (x + 1) / 10][int(abs(y - 1))] != LANG_TUSCIAS ||
					laukas[int(abs(x - 1))][y] != LANG_TUSCIAS ||
					laukas[int(abs(x - 1))][y + 1 - (y + 1) / 10] != LANG_TUSCIAS ||
					laukas[int(abs(x - 1))][int(abs(y - 1))] != LANG_TUSCIAS ||
					laukas[x][y + 1 - (y + 1) / 10] != LANG_TUSCIAS ||
					laukas[x][int(abs(y - 1))] != LANG_TUSCIAS
					) {
					OK = false;
				}
			}
		}
		if (OK)
			for (int y = y1; y <= y2; y++) {
				for (int x = x1; x <= x2; x++) {
					laukas[x][y] = LANG_LAIVAS;
				}
			}
		return OK;
	}

	void place_ships() {
		int x1, x2, y1, y2;
		bool krypt;
		for (int i = 4; i >= 1; i--) {
			for (int k = 1; k <= 5 - i; k++) {
				x1 = rand() % 10;
				y1 = rand() % 10;
				krypt = rand() % 2 == 0;
				if (krypt) {
					x2 = x1 + i - 1;
					y2 = y1;
				}
				else {
					y2 = y1 + i - 1;
					x2 = x1;
				}
				if (!place_ship(x1, y1, x2, y2))
					k--;
			}
		}
	}

	char shooting(int x, int y) {
		if (x >= 0 || x < 10 || y >= 0 || y < 10) {
			if (laukas[x][y] == LANG_LAIVAS) {
				laukas[x][y] = LANG_SPROGES;
				pataikyta_kartu_player++;
				counteris++;
			}
			else if (laukas[x][y] == LANG_TUSCIAS) {
				laukas[x][y] = LANG_KIAURAS;
			}
		}
		return laukas[x][y];
	}

	char shootingAI(int x, int y) {
		if (laukas[x][y] == LANG_LAIVAS) {
			laukas[x][y] = LANG_SPROGES;
			pataikyta_kartu_AI++;
			counteris++;
		}
		else if (laukas[x][y] == LANG_TUSCIAS) {
			laukas[x][y] = LANG_KIAURAS;
		}
		return laukas[x][y];
	}

	void zaidejo_valdymas() {
		int x, y;
		bool OK = false;
		while (OK == false) {
			cout << "Jusu spejamos X ir Y koordinates [0; 9]?: ";
			cin >> x >> y;
			if (x > -1 && y > -1 && x < 10 && y < 10) {
				OK = true;
			}
			else {
				SetConsoleTextAttribute(console, 0b11111100);
				cout << "Koordinates ivestos neteisingai, meginkite dar karta..." << endl;
				SetConsoleTextAttribute(console, 0b11110000);
			}
		}
		y = y;
		x = x;
		shooting(x, y);
	}

	void AI_valdymas_lengvas() {
		int x, y;
		bool kartojasi = true;
		x = rand() % 10;
		y = rand() % 10;
		while (kartojasi) {
			if (laukas[x][y] == LANG_KIAURAS || laukas[x][y] == LANG_SPROGES) {
				x = rand() % 10;
				y = rand() % 10;
				kartojasi = true;
			}
			else {
				kartojasi = false;
			}
		}
		shootingAI(x, y);
		cout << "I Jus sove koordinatemis (" << x + 1 << ", " << y + 1 << ")" << endl;
	}

	void AI_valdymas_normalus() {
		int x, y, spejimas;
		bool kartojasi = true;
		bool RASTAS = false;
		x = rand() % 10;
		y = rand() % 10;
		while (kartojasi) {
			if (RASTAS == false) {
				for (auto j = 0; j < 10; j++) {
					for (auto i = 0; i < 10; i++) {
						if ((laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i][j - 1] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i - 1][j] == LANG_SPROGES)) {
							if (laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES) {
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
								else if (laukas[i + 2][j] == LANG_TUSCIAS || laukas[i + 2][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 2;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES) {
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
								else if (laukas[i][j + 2] == LANG_TUSCIAS || laukas[i][j + 2] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 2;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i][j - 1] == LANG_SPROGES) {
								if (laukas[i][j - 2] == LANG_TUSCIAS || laukas[i][j - 2] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 2;
									RASTAS = true; i = 9; j = 9;
								}
								else if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i - 1][j] == LANG_SPROGES) {
								if (laukas[i - 2][j] == LANG_TUSCIAS || laukas[i - 2][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 2;
									RASTAS = true; i = 9; j = 9;
								}
								else if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
						}
					}
				}
				for (auto j = 0; j < 10; j++) {
					for (auto i = 0; i < 10; i++) {
						if ((laukas[i][j] == LANG_SPROGES && laukas[i][j + 2] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i][j - 2] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i - 2][j] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i + 2][j] == LANG_SPROGES)
							) {
							if (laukas[i][j] == LANG_SPROGES && laukas[i][j + 2] == LANG_SPROGES) {
								if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i][j - 2] == LANG_SPROGES) {
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i - 2][j] == LANG_SPROGES) {
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i + 2][j] == LANG_SPROGES) {
								if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
						}
					}
				}
				for (auto j = x; j < 10; j++) {
					for (auto i = y; i < 10; i++) {
						if (laukas[i][j] == LANG_SPROGES) {
							spejimas = rand() % 4;
							if (spejimas == 0) {
								if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (spejimas == 1) {
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (spejimas == 2) {
								if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
								i = 9; j = 9;
							}
							if (spejimas == 3) {
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
						}
					}
				}
			}
			if (laukas[x][y] == LANG_KIAURAS || laukas[x][y] == LANG_SPROGES) {
				x = rand() % 10;
				y = rand() % 10;
				kartojasi = true;
				RASTAS = false;
			}
			else {
				kartojasi = false;
				RASTAS = true;
			}
		}
		shootingAI(x, y);
		cout << "I Jus sove koordinatemis (" << x + 1 << ", " << y + 1 << ")" << endl;
	}

	void AI_valdymas_sunkus() {
		int x, y, spejimas;
		bool kartojasi = true;
		bool RASTAS = false;
		x = rand() % 10;
		y = rand() % 10;
		while (kartojasi) {
			for (auto j = 0; j < 10; j++) {
				for (auto i = 0; i < 10; i++) {
					if (RASTAS == false) {
						if ((laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i][j - 1] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i - 1][j] == LANG_SPROGES)) {
							if (laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES) {
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
								else if (laukas[i + 2][j] == LANG_TUSCIAS || laukas[i + 2][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 2;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES) {
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
								else if (laukas[i][j + 2] == LANG_TUSCIAS || laukas[i][j + 2] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 2;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i][j - 1] == LANG_SPROGES) {
								if (laukas[i][j - 2] == LANG_TUSCIAS || laukas[i][j - 2] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 2;
									RASTAS = true; i = 9; j = 9;
								}
								else if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i - 1][j] == LANG_SPROGES) {
								if (laukas[i - 2][j] == LANG_TUSCIAS || laukas[i - 2][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 2;
									RASTAS = true; i = 9; j = 9;
								}
								else if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
						}
						else if ((laukas[i][j] == LANG_SPROGES && laukas[i][j + 2] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i][j - 2] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i - 2][j] == LANG_SPROGES) ||
							(laukas[i][j] == LANG_SPROGES && laukas[i + 2][j] == LANG_SPROGES)
							) {
							if (laukas[i][j] == LANG_SPROGES && laukas[i][j + 2] == LANG_SPROGES) {
								if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i][j - 2] == LANG_SPROGES) {
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i - 2][j] == LANG_SPROGES) {
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (laukas[i][j] == LANG_SPROGES && laukas[i + 2][j] == LANG_SPROGES) {
								if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
						}
						else if (laukas[i][j] == LANG_SPROGES) {
							spejimas = rand() % 4;
							if (spejimas == 0) {
								if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (spejimas == 1) {
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
							if (spejimas == 2) {
								if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
								i = 9; j = 9;
							}
							if (spejimas == 3) {
								if (laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x - 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_LAIVAS) {
									x = i;
									y = j;
									y = y + 1;
									RASTAS = true; i = 9; j = 9;
								}
								if (laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_LAIVAS) {
									x = i;
									y = j;
									x = x + 1;
									RASTAS = true; i = 9; j = 9;
								}
							}
						}
					}
				}
			}
			if (laukas[x][y] == LANG_KIAURAS || laukas[x][y] == LANG_SPROGES || laukas[x][y] == LANG_ATMESTAS) {
				x = rand() % 10;
				y = rand() % 10;
				kartojasi = true;
				RASTAS = false;
			}
			else {
				kartojasi = false;
				RASTAS = true;
			}
		}
		shootingAI(x, y);
		laivu_tikrinimas();
		cout << "I Jus sove koordinatemis (" << x + 1 << ", " << y + 1 << ")" << endl;
	}

	bool laivu_tikrinimas() {
		bool sunaikintas_keturvietis = false;
		int sunaikinta_trivieciu = 0;
		int pirmas_atvejis = 0, antras_atvejis = 0, trecias_atvejis = 0, ketvirtas_atvejis = 0;
		bool OK = true;
		for (auto i = 0; i < 10; i++) {
			for (auto j = 0; j < 10; j++) {
				if (laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES && laukas[i][j + 2] == LANG_SPROGES && laukas[i][j + 3] == LANG_SPROGES) {
					if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS || laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
						laukas[i - 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS && laukas[i][j - 1] != NULL && j != 0) {
						laukas[i][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS && laukas[i + 1][j - 1] != NULL && j != 0) {
						laukas[i + 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
						laukas[i - 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
						laukas[i - 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j + 2] == LANG_ATMESTAS || laukas[i - 1][j + 2] == LANG_TUSCIAS || laukas[i - 1][j + 2] == LANG_KIAURAS && laukas[i - 1][j + 2] != NULL && i != 0) {
						laukas[i - 1][j + 2] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j + 3] == LANG_ATMESTAS || laukas[i - 1][j + 3] == LANG_TUSCIAS || laukas[i - 1][j + 3] == LANG_KIAURAS && laukas[i - 1][j + 3] != NULL && i != 0) {
						laukas[i - 1][j + 3] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j + 4] == LANG_ATMESTAS || laukas[i - 1][j + 4] == LANG_TUSCIAS || laukas[i - 1][j + 4] == LANG_KIAURAS && laukas[i - 1][j + 4] != NULL && i != 0) {
						laukas[i - 1][j + 4] = LANG_ATMESTAS;
					}
					if (laukas[i][j + 4] == LANG_ATMESTAS || laukas[i][j + 4] == LANG_TUSCIAS || laukas[i][j + 4] == LANG_KIAURAS && laukas[i][j + 4] != NULL) {
						laukas[i][j + 4] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j] == LANG_ATMESTAS || laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_KIAURAS && laukas[i + 1][j] != NULL) {
						laukas[i + 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS && laukas[i + 1][j + 1] != NULL) {
						laukas[i + 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 2] == LANG_ATMESTAS || laukas[i + 1][j + 2] == LANG_TUSCIAS || laukas[i + 1][j + 2] == LANG_KIAURAS && laukas[i + 1][j + 2] != NULL) {
						laukas[i + 1][j + 2] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 3] == LANG_ATMESTAS || laukas[i + 1][j + 3] == LANG_TUSCIAS || laukas[i + 1][j + 3] == LANG_KIAURAS && laukas[i + 1][j + 3] != NULL) {
						laukas[i + 1][j + 3] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 4] == LANG_ATMESTAS || laukas[i + 1][j + 4] == LANG_TUSCIAS || laukas[i + 1][j + 4] == LANG_KIAURAS && laukas[i + 1][j + 4] != NULL) {
						laukas[i + 1][j + 4] = LANG_ATMESTAS;
					}
					sunaikintas_keturvietis = true;
				}
				if (laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES && laukas[i + 2][j] == LANG_SPROGES && laukas[i + 3][j] == LANG_SPROGES) {
					if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
						laukas[i - 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
						laukas[i - 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS || laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
						laukas[i - 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] != NULL && j != 0) {
						laukas[i][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j + 1] == LANG_ATMESTAS || laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] != NULL) {
						laukas[i][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS || laukas[i + 1][j + 1] != NULL) {
						laukas[i + 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 2][j + 1] == LANG_ATMESTAS || laukas[i + 2][j + 1] == LANG_TUSCIAS || laukas[i + 2][j + 1] == LANG_KIAURAS || laukas[i + 2][j + 1] != NULL) {
						laukas[i + 2][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 3][j + 1] == LANG_ATMESTAS || laukas[i + 3][j + 1] == LANG_TUSCIAS || laukas[i + 3][j + 1] == LANG_KIAURAS || laukas[i + 3][j + 1] != NULL) {
						laukas[i + 3][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 4][j + 1] == LANG_ATMESTAS || laukas[i + 4][j + 1] == LANG_TUSCIAS || laukas[i + 4][j + 1] == LANG_KIAURAS || laukas[i + 4][j + 1] != NULL) {
						laukas[i + 4][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 4][j] == LANG_ATMESTAS || laukas[i + 4][j] == LANG_TUSCIAS || laukas[i + 4][j] == LANG_KIAURAS || laukas[i + 4][j] != NULL) {
						laukas[i + 4][j] = LANG_ATMESTAS;
					}
					if (laukas[i + 4][j - 1] == LANG_ATMESTAS || laukas[i + 4][j - 1] == LANG_TUSCIAS || laukas[i + 4][j - 1] == LANG_KIAURAS || laukas[i + 4][j - 1] != NULL && j != 0) {
						laukas[i + 4][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 3][j - 1] == LANG_ATMESTAS || laukas[i + 3][j - 1] == LANG_TUSCIAS || laukas[i + 3][j - 1] == LANG_KIAURAS || laukas[i + 3][j - 1] != NULL && j != 0) {
						laukas[i + 3][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 2][j - 1] == LANG_ATMESTAS || laukas[i + 2][j - 1] == LANG_TUSCIAS || laukas[i + 2][j - 1] == LANG_KIAURAS || laukas[i + 2][j - 1] != NULL && j != 0) {
						laukas[i + 2][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS || laukas[i + 1][j - 1] != NULL && j != 0) {
						laukas[i + 1][j - 1] = LANG_ATMESTAS;
					}
					sunaikintas_keturvietis = true;
				}
				if (sunaikintas_keturvietis == true) {
					if (laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES && laukas[i][j + 2] == LANG_SPROGES) {
						pirmas_atvejis++;
						if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS || laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
							laukas[i - 1][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS && laukas[i][j - 1] != NULL && j != 0) {
							laukas[i][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS && laukas[i + 1][j - 1] != NULL && j != 0) {
							laukas[i + 1][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
							laukas[i - 1][j] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
							laukas[i - 1][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j + 2] == LANG_ATMESTAS || laukas[i - 1][j + 2] == LANG_TUSCIAS || laukas[i - 1][j + 2] == LANG_KIAURAS && laukas[i - 1][j + 2] != NULL && i != 0) {
							laukas[i - 1][j + 2] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j + 3] == LANG_ATMESTAS || laukas[i - 1][j + 3] == LANG_TUSCIAS || laukas[i - 1][j + 3] == LANG_KIAURAS && laukas[i - 1][j + 3] != NULL && i != 0) {
							laukas[i - 1][j + 3] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j] == LANG_ATMESTAS || laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_KIAURAS && laukas[i + 1][j] != NULL) {
							laukas[i + 1][j] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS && laukas[i + 1][j + 1] != NULL) {
							laukas[i + 1][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j + 2] == LANG_ATMESTAS || laukas[i + 1][j + 2] == LANG_TUSCIAS || laukas[i + 1][j + 2] == LANG_KIAURAS && laukas[i + 1][j + 2] != NULL) {
							laukas[i + 1][j + 2] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j + 3] == LANG_ATMESTAS || laukas[i + 1][j + 3] == LANG_TUSCIAS || laukas[i + 1][j + 3] == LANG_KIAURAS && laukas[i + 1][j + 3] != NULL) {
							laukas[i + 1][j + 3] = LANG_ATMESTAS;
						}
						if (laukas[i][j + 3] == LANG_ATMESTAS || laukas[i][j + 3] == LANG_TUSCIAS || laukas[i][j + 3] == LANG_KIAURAS && laukas[i][j + 3] != NULL && i != 0) {
							laukas[i][j + 3] = LANG_ATMESTAS;
						}
						if (pirmas_atvejis == 1) {
							sunaikinta_trivieciu++;
						}
					}
				}
				if (((laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] == LANG_ATMESTAS) && laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES && laukas[i][j + 2] == LANG_SPROGES && (laukas[i][j + 3] == LANG_KIAURAS || laukas[i][j + 3] == LANG_ATMESTAS)) ||
					(laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES && laukas[i][j + 2] == LANG_SPROGES && (laukas[i][j + 3] == LANG_KIAURAS || laukas[i][j + 3] == LANG_ATMESTAS) && j - 1 < 0) ||
					((laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] == LANG_ATMESTAS) && laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES && laukas[i][j + 2] == LANG_SPROGES && j + 3 > 9)
					) {
					antras_atvejis++;
					if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS || laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
						laukas[i - 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS && laukas[i][j - 1] != NULL && j != 0) {
						laukas[i][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS && laukas[i + 1][j - 1] != NULL && j != 0) {
						laukas[i + 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
						laukas[i - 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
						laukas[i - 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j + 2] == LANG_ATMESTAS || laukas[i - 1][j + 2] == LANG_TUSCIAS || laukas[i - 1][j + 2] == LANG_KIAURAS && laukas[i - 1][j + 2] != NULL && i != 0) {
						laukas[i - 1][j + 2] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j + 3] == LANG_ATMESTAS || laukas[i - 1][j + 3] == LANG_TUSCIAS || laukas[i - 1][j + 3] == LANG_KIAURAS && laukas[i - 1][j + 3] != NULL && i != 0) {
						laukas[i - 1][j + 3] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j] == LANG_ATMESTAS || laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_KIAURAS && laukas[i + 1][j] != NULL) {
						laukas[i + 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS && laukas[i + 1][j + 1] != NULL) {
						laukas[i + 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 2] == LANG_ATMESTAS || laukas[i + 1][j + 2] == LANG_TUSCIAS || laukas[i + 1][j + 2] == LANG_KIAURAS && laukas[i + 1][j + 2] != NULL) {
						laukas[i + 1][j + 2] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 3] == LANG_ATMESTAS || laukas[i + 1][j + 3] == LANG_TUSCIAS || laukas[i + 1][j + 3] == LANG_KIAURAS && laukas[i + 1][j + 3] != NULL) {
						laukas[i + 1][j + 3] = LANG_ATMESTAS;
					}
					if (laukas[i][j + 3] == LANG_ATMESTAS || laukas[i][j + 3] == LANG_TUSCIAS || laukas[i][j + 3] == LANG_KIAURAS && laukas[i][j + 3] != NULL && i != 0) {
						laukas[i][j + 3] = LANG_ATMESTAS;
					}
					if (antras_atvejis == 1) {
						sunaikinta_trivieciu++;
					}
				}
				if (sunaikintas_keturvietis == true) {
					if (laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES && laukas[i + 2][j] == LANG_SPROGES) {
						trecias_atvejis++;
						if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
							laukas[i - 1][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
							laukas[i - 1][j] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS || laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
							laukas[i - 1][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] != NULL && j != 0) {
							laukas[i][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i][j + 1] == LANG_ATMESTAS || laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] != NULL) {
							laukas[i][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS || laukas[i + 1][j + 1] != NULL) {
							laukas[i + 1][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 2][j + 1] == LANG_ATMESTAS || laukas[i + 2][j + 1] == LANG_TUSCIAS || laukas[i + 2][j + 1] == LANG_KIAURAS || laukas[i + 2][j + 1] != NULL) {
							laukas[i + 2][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 3][j + 1] == LANG_ATMESTAS || laukas[i + 3][j + 1] == LANG_TUSCIAS || laukas[i + 3][j + 1] == LANG_KIAURAS || laukas[i + 3][j + 1] != NULL) {
							laukas[i + 3][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 3][j - 1] == LANG_ATMESTAS || laukas[i + 3][j - 1] == LANG_TUSCIAS || laukas[i + 3][j - 1] == LANG_KIAURAS || laukas[i + 3][j - 1] != NULL && j != 0) {
							laukas[i + 3][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 2][j - 1] == LANG_ATMESTAS || laukas[i + 2][j - 1] == LANG_TUSCIAS || laukas[i + 2][j - 1] == LANG_KIAURAS || laukas[i + 2][j - 1] != NULL && j != 0) {
							laukas[i + 2][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS || laukas[i + 1][j - 1] != NULL && j != 0) {
							laukas[i + 1][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 3][j] == LANG_ATMESTAS || laukas[i + 3][j] == LANG_TUSCIAS || laukas[i + 3][j] == LANG_KIAURAS || laukas[i + 3][j] != NULL) {
							laukas[i + 3][j] = LANG_ATMESTAS;
						}
						if (trecias_atvejis == 1) {
							sunaikinta_trivieciu++;
						}
					}
				}
				if (((laukas[i - 1][j] == LANG_KIAURAS || laukas[i - 1][j] == LANG_ATMESTAS) && laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES && laukas[i + 2][j] == LANG_SPROGES && (laukas[i + 3][j] == LANG_KIAURAS || laukas[i + 3][j] == LANG_ATMESTAS)) ||
					((laukas[i - 1][j] == LANG_KIAURAS || laukas[i - 1][j] == LANG_ATMESTAS) && laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES && laukas[i + 2][j] == LANG_SPROGES && i + 3 > 9) ||
					(laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES && laukas[i + 2][j] == LANG_SPROGES && (laukas[i + 3][j] == LANG_KIAURAS || laukas[i + 3][j] == LANG_ATMESTAS) && i - 1 < 0)
					) {
					ketvirtas_atvejis++;
					if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
						laukas[i - 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
						laukas[i - 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS || laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
						laukas[i - 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] != NULL && j != 0) {
						laukas[i][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j + 1] == LANG_ATMESTAS || laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] != NULL) {
						laukas[i][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS || laukas[i + 1][j + 1] != NULL) {
						laukas[i + 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 2][j + 1] == LANG_ATMESTAS || laukas[i + 2][j + 1] == LANG_TUSCIAS || laukas[i + 2][j + 1] == LANG_KIAURAS || laukas[i + 2][j + 1] != NULL) {
						laukas[i + 2][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 3][j + 1] == LANG_ATMESTAS || laukas[i + 3][j + 1] == LANG_TUSCIAS || laukas[i + 3][j + 1] == LANG_KIAURAS || laukas[i + 3][j + 1] != NULL) {
						laukas[i + 3][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 3][j - 1] == LANG_ATMESTAS || laukas[i + 3][j - 1] == LANG_TUSCIAS || laukas[i + 3][j - 1] == LANG_KIAURAS || laukas[i + 3][j - 1] != NULL && j != 0) {
						laukas[i + 3][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 2][j - 1] == LANG_ATMESTAS || laukas[i + 2][j - 1] == LANG_TUSCIAS || laukas[i + 2][j - 1] == LANG_KIAURAS || laukas[i + 2][j - 1] != NULL && j != 0) {
						laukas[i + 2][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS || laukas[i + 1][j - 1] != NULL && j != 0) {
						laukas[i + 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 3][j] == LANG_ATMESTAS || laukas[i + 3][j] == LANG_TUSCIAS || laukas[i + 3][j] == LANG_KIAURAS || laukas[i + 3][j] != NULL) {
						laukas[i + 3][j] = LANG_ATMESTAS;
					}
					if (ketvirtas_atvejis == 1) {
						sunaikinta_trivieciu++;
					}
				}
				if (sunaikinta_trivieciu >= 2) {
					if (laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES) {
						if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS || laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
							laukas[i - 1][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS && laukas[i][j - 1] != NULL && j != 0) {
							laukas[i][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS && laukas[i + 1][j - 1] != NULL && j != 0) {
							laukas[i + 1][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
							laukas[i - 1][j] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
							laukas[i - 1][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j + 2] == LANG_ATMESTAS || laukas[i - 1][j + 2] == LANG_TUSCIAS || laukas[i - 1][j + 2] == LANG_KIAURAS && laukas[i - 1][j + 2] != NULL && i != 0) {
							laukas[i - 1][j + 2] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j] == LANG_ATMESTAS || laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_KIAURAS && laukas[i + 1][j] != NULL) {
							laukas[i + 1][j] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS && laukas[i + 1][j + 1] != NULL) {
							laukas[i + 1][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j + 2] == LANG_ATMESTAS || laukas[i + 1][j + 2] == LANG_TUSCIAS || laukas[i + 1][j + 2] == LANG_KIAURAS && laukas[i + 1][j + 2] != NULL) {
							laukas[i + 1][j + 2] = LANG_ATMESTAS;
						}
						if (laukas[i][j + 2] == LANG_ATMESTAS || laukas[i][j + 2] == LANG_TUSCIAS || laukas[i][j + 2] == LANG_KIAURAS && laukas[i][j + 2] != NULL) {
							laukas[i][j + 2] = LANG_ATMESTAS;
						}
					}
				}
				if (((laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] == LANG_ATMESTAS) && laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES && (laukas[i][j + 2] == LANG_KIAURAS || laukas[i][j + 2] == LANG_ATMESTAS)) ||
					((laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] == LANG_ATMESTAS) && laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES && j + 1 > 9) ||
					(laukas[i][j] == LANG_SPROGES && laukas[i][j + 1] == LANG_SPROGES && (laukas[i][j + 2] == LANG_KIAURAS || laukas[i][j + 2] == LANG_ATMESTAS) && j - 1 < 0)
					) {
					if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS || laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
						laukas[i - 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS && laukas[i][j - 1] != NULL && j != 0) {
						laukas[i][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS && laukas[i + 1][j - 1] != NULL && j != 0) {
						laukas[i + 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
						laukas[i - 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
						laukas[i - 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j + 2] == LANG_ATMESTAS || laukas[i - 1][j + 2] == LANG_TUSCIAS || laukas[i - 1][j + 2] == LANG_KIAURAS && laukas[i - 1][j + 2] != NULL && i != 0) {
						laukas[i - 1][j + 2] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j] == LANG_ATMESTAS || laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_KIAURAS && laukas[i + 1][j] != NULL) {
						laukas[i + 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS && laukas[i + 1][j + 1] != NULL) {
						laukas[i + 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 2] == LANG_ATMESTAS || laukas[i + 1][j + 2] == LANG_TUSCIAS || laukas[i + 1][j + 2] == LANG_KIAURAS && laukas[i + 1][j + 2] != NULL) {
						laukas[i + 1][j + 2] = LANG_ATMESTAS;
					}
					if (laukas[i][j + 2] == LANG_ATMESTAS || laukas[i][j + 2] == LANG_TUSCIAS || laukas[i][j + 2] == LANG_KIAURAS && laukas[i][j + 2] != NULL) {
						laukas[i][j + 2] = LANG_ATMESTAS;
					}
				}
				if (sunaikinta_trivieciu >= 2) {
					if (laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES) {
						if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
							laukas[i - 1][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
							laukas[i - 1][j] = LANG_ATMESTAS;
						}
						if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS || laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
							laukas[i - 1][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] != NULL && j != 0) {
							laukas[i][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i][j + 1] == LANG_ATMESTAS || laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] != NULL) {
							laukas[i][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS || laukas[i + 1][j + 1] != NULL) {
							laukas[i + 1][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 2][j + 1] == LANG_ATMESTAS || laukas[i + 2][j + 1] == LANG_TUSCIAS || laukas[i + 2][j + 1] == LANG_KIAURAS || laukas[i + 2][j + 1] != NULL) {
							laukas[i + 2][j + 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 2][j - 1] == LANG_ATMESTAS || laukas[i + 2][j - 1] == LANG_TUSCIAS || laukas[i + 2][j - 1] == LANG_KIAURAS || laukas[i + 2][j - 1] != NULL && j != 0) {
							laukas[i + 2][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS || laukas[i + 1][j - 1] != NULL && j != 0) {
							laukas[i + 1][j - 1] = LANG_ATMESTAS;
						}
						if (laukas[i + 2][j] == LANG_ATMESTAS || laukas[i + 2][j] == LANG_TUSCIAS || laukas[i + 2][j] == LANG_KIAURAS || laukas[i + 2][j] != NULL) {
							laukas[i + 2][j] = LANG_ATMESTAS;
						}
					}
				}
				if (((laukas[i - 1][j] == LANG_KIAURAS || laukas[i - 1][j] == LANG_ATMESTAS) && laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES && (laukas[i + 2][j] == LANG_KIAURAS || laukas[i + 2][j] == LANG_ATMESTAS)) ||
					((laukas[i - 1][j] == LANG_KIAURAS || laukas[i - 1][j] == LANG_ATMESTAS) && laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES && i + 1 > 9) ||
					(laukas[i][j] == LANG_SPROGES && laukas[i + 1][j] == LANG_SPROGES && (laukas[i + 2][j] == LANG_KIAURAS || laukas[i + 2][j] == LANG_ATMESTAS) && i - 1 < 0)
					) {
					if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
						laukas[i - 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
						laukas[i - 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS || laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
						laukas[i - 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] != NULL && j != 0) {
						laukas[i][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j + 1] == LANG_ATMESTAS || laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] != NULL) {
						laukas[i][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS || laukas[i + 1][j + 1] != NULL) {
						laukas[i + 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 2][j + 1] == LANG_ATMESTAS || laukas[i + 2][j + 1] == LANG_TUSCIAS || laukas[i + 2][j + 1] == LANG_KIAURAS || laukas[i + 2][j + 1] != NULL) {
						laukas[i + 2][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 2][j - 1] == LANG_ATMESTAS || laukas[i + 2][j - 1] == LANG_TUSCIAS || laukas[i + 2][j - 1] == LANG_KIAURAS || laukas[i + 2][j - 1] != NULL && j != 0) {
						laukas[i + 2][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS || laukas[i + 1][j - 1] != NULL && j != 0) {
						laukas[i + 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 2][j] == LANG_ATMESTAS || laukas[i + 2][j] == LANG_TUSCIAS || laukas[i + 2][j] == LANG_KIAURAS || laukas[i + 2][j] != NULL) {
						laukas[i + 2][j] = LANG_ATMESTAS;
					}
				}
				if ((laukas[i][j] == LANG_SPROGES && (laukas[i - 1][j] == LANG_KIAURAS || laukas[i - 1][j] == LANG_ATMESTAS) 
												  && (laukas[i + 1][j] == LANG_KIAURAS || laukas[i + 1][j] == LANG_ATMESTAS)
												  && (laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] == LANG_ATMESTAS)
												  && (laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] == LANG_ATMESTAS)) ||
					(laukas[i][j] == LANG_SPROGES && (laukas[i + 1][j] == LANG_KIAURAS || laukas[i + 1][j] == LANG_ATMESTAS)
												  && (laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] == LANG_ATMESTAS)
												  && (laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] == LANG_ATMESTAS) && i - 1 < 0) ||
					(laukas[i][j] == LANG_SPROGES && (laukas[i - 1][j] == LANG_KIAURAS || laukas[i - 1][j] == LANG_ATMESTAS)
											      && (laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] == LANG_ATMESTAS)
												  && (laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] == LANG_ATMESTAS) && i + 1 > 9) ||
					(laukas[i][j] == LANG_SPROGES && (laukas[i + 1][j] == LANG_KIAURAS || laukas[i + 1][j] == LANG_ATMESTAS)
												  && (laukas[i - 1][j] == LANG_KIAURAS || laukas[i - 1][j] == LANG_ATMESTAS)
												  && (laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] == LANG_ATMESTAS) && j - 1 < 0) ||
					(laukas[i][j] == LANG_SPROGES && (laukas[i + 1][j] == LANG_KIAURAS || laukas[i + 1][j] == LANG_ATMESTAS)
												  && (laukas[i - 1][j] == LANG_KIAURAS || laukas[i - 1][j] == LANG_ATMESTAS)
												  && (laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] == LANG_ATMESTAS) && j + 1 > 9) ||
					(laukas[i][j] == LANG_SPROGES && (laukas[i + 1][j] == LANG_KIAURAS || laukas[i + 1][j] == LANG_ATMESTAS)
												  && (laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] == LANG_ATMESTAS) && j + 1 > 9 && i - 1 < 0) ||
					(laukas[i][j] == LANG_SPROGES && (laukas[i + 1][j] == LANG_KIAURAS || laukas[i + 1][j] == LANG_ATMESTAS)
												  && (laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] == LANG_ATMESTAS) && j - 1 < 0 && i - 1 < 0) ||
					(laukas[i][j] == LANG_SPROGES && (laukas[i - 1][j] == LANG_KIAURAS || laukas[i - 1][j] == LANG_ATMESTAS)
												  && (laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] == LANG_ATMESTAS) && j + 1 > 9 && i + 1 > 9) ||
					(laukas[i][j] == LANG_SPROGES && (laukas[i - 1][j] == LANG_KIAURAS || laukas[i - 1][j] == LANG_ATMESTAS)
												  && (laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] == LANG_ATMESTAS) && j - 1 < 0 && i + 1 > 9)
					) {
					if (laukas[i - 1][j] == LANG_ATMESTAS || laukas[i - 1][j] == LANG_TUSCIAS || laukas[i - 1][j] == LANG_KIAURAS && laukas[i - 1][j] != NULL && i != 0) {
						laukas[i - 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j - 1] == LANG_ATMESTAS || laukas[i - 1][j - 1] == LANG_TUSCIAS || laukas[i - 1][j - 1] == LANG_KIAURAS && laukas[i - 1][j - 1] != NULL && i != 0 && j != 0) {
						laukas[i - 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i - 1][j + 1] == LANG_ATMESTAS || laukas[i - 1][j + 1] == LANG_TUSCIAS || laukas[i - 1][j + 1] == LANG_KIAURAS && laukas[i - 1][j + 1] != NULL && i != 0) {
						laukas[i - 1][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j - 1] == LANG_ATMESTAS || laukas[i][j - 1] == LANG_TUSCIAS || laukas[i][j - 1] == LANG_KIAURAS || laukas[i][j - 1] != NULL && j != 0) {
						laukas[i][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i][j + 1] == LANG_ATMESTAS || laukas[i][j + 1] == LANG_TUSCIAS || laukas[i][j + 1] == LANG_KIAURAS || laukas[i][j + 1] != NULL) {
						laukas[i][j + 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j] == LANG_ATMESTAS || laukas[i + 1][j] == LANG_TUSCIAS || laukas[i + 1][j] == LANG_KIAURAS && laukas[i + 1][j] != NULL) {
						laukas[i + 1][j] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j - 1] == LANG_ATMESTAS || laukas[i + 1][j - 1] == LANG_TUSCIAS || laukas[i + 1][j - 1] == LANG_KIAURAS && laukas[i + 1][j - 1] != NULL && j != 0) {
						laukas[i + 1][j - 1] = LANG_ATMESTAS;
					}
					if (laukas[i + 1][j + 1] == LANG_ATMESTAS || laukas[i + 1][j + 1] == LANG_TUSCIAS || laukas[i + 1][j + 1] == LANG_KIAURAS && laukas[i + 1][j + 1] != NULL) {
						laukas[i + 1][j + 1] = LANG_ATMESTAS;
					}
				}
			}
		}
		return OK;
	}

	void print_field_nesaziningas(int color) {
		cout << "    ";
		for (auto j = 0; j < 10; j++) {
			if (j % 2 == 0) {
				SetConsoleTextAttribute(console, 0b11111100);
				cout << j;
			}
			else {
				SetConsoleTextAttribute(console, 0b11110000);
				cout << j;
			}
		}
		cout << endl << "   ";
		for (int g = 0; g < 12; g++) {
			SetConsoleTextAttribute(console, 0b11110100);
			cout << char(220);
		}
		cout << endl;
		for (int y = 0; y < 10; y++) {
			if (y % 2 == 0) {
				SetConsoleTextAttribute(console, 0b11111100);
				cout << y;
			}
			else {
				SetConsoleTextAttribute(console, 0b11110000);
				cout << y;
			}
			cout << "  ";
			SetConsoleTextAttribute(console, 0b11110100);
			cout << char(219);
			for (int x = 0; x < 10; x++) {
				if (laukas[x][y] == LANG_LAIVAS) {
					SetConsoleTextAttribute(console, color);
					cout << laukas[x][y];
					SetConsoleTextAttribute(console, 0b11110000);
				}
				else {
					if (laukas[x][y] == LANG_SPROGES) {
						if (color == 0b11111100) {
							SetConsoleTextAttribute(console, 0b10011010);
							cout << laukas[x][y];
						}
						else {
							SetConsoleTextAttribute(console, 0b10011100);
							cout << laukas[x][y];
						}
					}
					else if (laukas[x][y] == LANG_ATMESTAS) {
						SetConsoleTextAttribute(console, 0b10011101);
						cout << laukas[x][y];
					}
					else {
						SetConsoleTextAttribute(console, 0b10010111);
						cout << laukas[x][y];
						SetConsoleTextAttribute(console, 0b11110000);
					}
				}
				if (x == 9) {
					SetConsoleTextAttribute(console, 0b11110100);
					cout << char(219);
					SetConsoleTextAttribute(console, 0b11110000);
				}
			}
			if (y == 4) {
				SetConsoleTextAttribute(console, 0b11110000);
				cout << "       Kartu ";
			}
			if (y == 5) {
				SetConsoleTextAttribute(console, 0b11110000);
				cout << "     pataikyta:";
			}
			if (y == 6) {
				SetConsoleTextAttribute(console, 0b11110000);
				cout << "         ";
				SetConsoleTextAttribute(console, 0b11111100);
				cout << counteris;
			}
			SetConsoleTextAttribute(console, 0b11110000);
			cout << endl;
		}
		cout << "   ";
		for (int g = 0; g < 12; g++) {
			SetConsoleTextAttribute(console, 0b11110100);
			cout << char(223);
		}
		cout << endl;
		SetConsoleTextAttribute(console, 0b11110000);
	}	
};

int main()
{
	system("color F0");
	srand(time(NULL));
	bool GAME_RUNNING = true;
	C_laukas mano;
	C_laukas ne_mano;
	mano.clear();
	ne_mano.clear();
	mano.place_ships();
	ne_mano.place_ships();
	while (rezimas > -1 && rezimas < 4) {
		cout << "Sveiki, tai \"Laivu Musis\". Prasau pasirinkti zaidymo rezima, jei norite testi: " << endl;
		cout << "0. NESAZININGAS (Matote prieso laivus...)" << endl << "1. LENGVAS (Priesas negalvoja...)" << endl << "2. NORMALUS (Priesas minimaliai masto...)" << endl << "3. SUNKUS (Sekmes :)...)" << endl;
		cin >> rezimas;
		system("cls");
		if (rezimas == 0) {
			cout << "Sekmingai pasirinkote nesazininga zaidymo rezima, spauskite ENTER, noredami testi!" << endl;
			system("PAUSE");
			break;
		}
		else if (rezimas == 1) {
			cout << "Sekmingai pasirinkote lengva zaidymo rezima, spauskite ENTER, noredami testi!" << endl;
			system("PAUSE");
			break;
		}
		else if (rezimas == 2) {
			cout << "Sekmingai pasirinkote normalu zaidymo rezima, spauskite ENTER, noredami testi!" << endl;
			system("PAUSE");
			break;
		}
		else if (rezimas == 3) {
			cout << "Sekmingai pasirinkote sunku zaidymo rezima, spauskite ENTER, noredami testi!" << endl;
			system("PAUSE");
			break;
		}
		else {
			SetConsoleTextAttribute(console, 0b11111100);
			cout << "Atsiprasome, jusu pasirinkimas nesuprastas, prasome pasirinkti egzistuojanti varianta!" << endl;
			SetConsoleTextAttribute(console, 0b11110000);
			rezimas = 1;
			sleep_for(seconds(2));
			system("cls");
		}
	}
	system("cls");
	while (GAME_RUNNING) {
		if (rezimas == 0) {
			cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
			mano.print_field_nesaziningas(0b11111010);
			cout << endl;
			ne_mano.print_field_nesaziningas(0b11111100);
			ne_mano.zaidejo_valdymas();
			mano.AI_valdymas_sunkus();
			sleep_for(seconds(1));
			system("cls");
			if (pataikyta_kartu_AI == 20) {
				cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
				mano.print_field(0b11111010);
				ne_mano.print_field(0b11111100);
				cout << "Jus pralaimejote!" << endl;
				GAME_RUNNING = false;
			}
			else if (pataikyta_kartu_player == 20) {
				cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
				mano.print_field(0b11111010);
				ne_mano.print_field(0b11111100);
				cout << "Jus esate laimetojas, sveikiname!" << endl;
				GAME_RUNNING = false;
			}
			ejimu_kiekis++;
		}
		if (rezimas == 1) {
			cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
			mano.print_field(0b11111010);
			cout << endl;
			ne_mano.print_field(0b11111100);
			ne_mano.zaidejo_valdymas();
			mano.AI_valdymas_lengvas();
			sleep_for(seconds(1));
			system("cls");
			if (pataikyta_kartu_AI == 20) {
				cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
				mano.print_field(0b11111010);
				ne_mano.print_field(0b11111100);
				cout << "Jus pralaimejote!" << endl;
				GAME_RUNNING = false;
			}
			else if (pataikyta_kartu_player == 20) {
				cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
				mano.print_field(0b11111010);
				ne_mano.print_field(0b11111100);
				cout << "Jus esate laimetojas, sveikiname!" << endl;
				GAME_RUNNING = false;
			}
			ejimu_kiekis++;
		}
		if (rezimas == 2) {
			cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
			mano.print_field(0b11111010);
			cout << endl;
			ne_mano.print_field(0b11111100);
			ne_mano.zaidejo_valdymas();
			mano.AI_valdymas_normalus();
			sleep_for(seconds(1));
			system("cls");
			if (pataikyta_kartu_AI == 20) {
				cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
				mano.print_field(0b11111010);
				ne_mano.print_field(0b11111100);
				cout << "Jus pralaimejote!" << endl;
				GAME_RUNNING = false;
			}
			else if (pataikyta_kartu_player == 20) {
				cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
				mano.print_field(0b11111010);
				ne_mano.print_field(0b11111100);
				cout << "Jus esate laimetojas, sveikiname!" << endl;
				GAME_RUNNING = false;
			}
			ejimu_kiekis++;
		}
		if (rezimas == 3) {
			cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
			mano.print_field(0b11111010);
			cout << endl;
			ne_mano.print_field(0b11111100);
			ne_mano.zaidejo_valdymas();
			mano.AI_valdymas_sunkus();
			sleep_for(seconds(1));
			system("cls");
			if (pataikyta_kartu_AI == 20) {
				cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
				mano.print_field(0b11111010);
				ne_mano.print_field(0b11111100);
				cout << "Jus pralaimejote!" << endl;
				GAME_RUNNING = false;
			}
			else if (pataikyta_kartu_player == 20) {
				cout << "          Ejimu kiekis: " << ejimu_kiekis << "." << endl;
				mano.print_field(0b11111010);
				ne_mano.print_field(0b11111100);
				cout << "Jus esate laimetojas, sveikiname!" << endl;
				GAME_RUNNING = false;
			}
			ejimu_kiekis++;
		}
	}
	system("PAUSE");
	return 0;
}
