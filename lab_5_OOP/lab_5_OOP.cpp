/*
Створити базовий клас ПУТІВКА (задаються пункт призначення та тривалість).
Створити похідні класи ВІДПОЧИНОК ЗА КОРДОНОМ (задаються вартість за 1 добу
у валюті, вартість проїзду у валюті) та АВТОБУСНИЙ ТУР ВСЕРЕДИНІ КРАЇНИ І ЗА КОРДОН
(задаються тривалість всередині країни, вартість за 1 добу в гривнях, тривалість за
кордоном, вартість за 1 добу у валюті). Для заданих прикладів путівок і курсів валют
обчислити вартість кожної з них у гривнях, впорядкувати путівки за зростанням вартості
і обчислити їх середню вартість. Для перевірки використати масив вказівників на
об’єкти базового класу, яким присвоїти адреси об’єктів похідних класів.
*/

#include <iostream>
#include <string>
#define NAME 30

using namespace std;

enum currency {
	DOLLAR = 2772,
	EURO = 3301,
	POUND = 3843,
};

class pass {
protected:
	string destination;
	int duration;
public:
	pass() {
		destination = "";
		duration = 0;
	}
	pass(string str, int dur) : destination(str), duration(dur) {}
	~pass() {}
	string get_destination() { return destination; }
	int get_duration() { return duration; }
	virtual double total() { return 0; }
	bool operator<(pass& p) {
		return this->total() < p.total();
	}
	bool operator>(pass& p) {
		return this->total() > p.total();
	}
	virtual void output() {
		cout << "Destination: " << this->get_destination() << "\t\tduration: " << this->get_duration() << endl;
	}
	friend void SwapValues(pass*& a, pass*& b) {
		swap(a, b);
	}
};

class vacation : public pass {
private:
	double day_price;
	double journey_price;
	currency cur;
public:
	vacation() : pass(), day_price(0), journey_price(0), cur(DOLLAR) {}
	vacation(string str, int dur, double d_price, double j_price, currency c) : pass(str, dur), day_price(d_price), journey_price(j_price), cur(c) {}
	~vacation() {}
	double get_day_p() { return day_price; }
	double get_journey_p() { return journey_price; }
	void set_day_p(double p) { day_price = p; }
	void set_journey_p(double p) { journey_price = p; }
	currency get_currency() { return cur; }
	double total() { return (day_price * duration + journey_price * 2) * cur / 100; }
	void output() {
		char c[5];
		switch (this->get_currency())
		{
		case DOLLAR:
			strcpy_s(c, " USD");
			break;
		case EURO:
			strcpy_s(c, " EUR");
			break;
		case POUND:
			strcpy_s(c, " GBP");
			break;
		default:
			break;
		}
		cout << "Destination: " << this->get_destination() << "\tduration: " << this->get_duration() << "\n\tprice per day: " << this->get_day_p() << c << "\tjourney price: " << this->get_journey_p() << c << "\n\t\t\ttotal price: " << this->total() << " UAH" << endl;
	}
};

class bus_tour : public pass {
private:
	int duration_in_country;
	double price_in_country;
	int duration_abroad;
	double price_aboard;
	currency cur;
public:
	bus_tour(): pass(), price_in_country(0), price_aboard(0), duration_in_country(0), duration_abroad(0), cur(DOLLAR) {}
	bus_tour(string str, int d_c, double p_c, int d_a, double p_a, currency c) : pass(str, d_a + d_c), price_in_country(p_c), price_aboard(p_a), duration_in_country(d_c), duration_abroad(d_a), cur(c) {}
	~bus_tour() {}
	double total() { return (price_aboard*duration_abroad * cur/100) + (price_in_country*duration_in_country); }
	double get_price_in_country() { return price_in_country; }
	double get_price_abroad() { return price_aboard; };
	int get_duration_in_country() { return duration_in_country; }
	int get_duration_abroad() { return duration_abroad; }
	currency get_currency() { return cur; };
	void output() {
		char c[5];
		switch (this->get_currency())
		{
		case DOLLAR:
			strcpy_s(c, " USD");
			break;
		case EURO:
			strcpy_s(c, " EUR");
			break;
		case POUND:
			strcpy_s(c, " GBP");
			break;
		default:
			break;
		}
		cout << "Destination: " << this->get_destination() << "\tduration: " << this->get_duration() <<"(in country: " << this->get_duration_in_country() << "  abroad: " << this->get_duration_abroad() << ")\n\tprice per day in country: " << this->get_price_in_country() << " UAH" << "\tprice per day in country: " << this->get_price_abroad() << c << "\n\t\t\ttotal price: " << this->total() << " UAH" << endl;

	}
};

ostream& operator<<(ostream& o, pass p) {
	o << "Destination: " << p.get_destination() << "\t\tduration: " << p.get_duration() << endl;
	return o;
}

ostream& operator<<(ostream& o, vacation v) {
	char c[5];
	switch (v.get_currency())
	{
	case DOLLAR:
		strcpy_s(c, " USD");
		break;
	case EURO:
		strcpy_s(c, " EUR");
		break;
	case POUND:
		strcpy_s(c, " GBP");
		break;
	default:
		break;
	}
	o << "Destination: " << v.get_destination() << "\tduration: " << v.get_duration() << "\n\tprice per day: " << v.get_day_p() << c << "\tjourney price: " << v.get_journey_p() << c << "\n\t\t\ttotal price: " << v.total() << " UAH" << endl;
	return o;
}

void input_pass(pass** p, int n) {
	cout << "\n\tEnter pass:\n";
	for (int i = 0; i < n; i++) {
		char s[NAME];
		int l, d_p, j_p, c, t;
		currency cur;
		cout << "Enter type of pass(1 -- vacation, 2 -- bus_tour): "; cin >> t;
		cout << "Destination: "; cin >> s;
		cout << "currency(dollar -- 1, euro -- 2, pound -- 3): "; cin >> c;
		switch (c) {
		case 1:
			cur = DOLLAR;
			break;
		case 2:
			cur = EURO;
			break;
		case 3:
			cur = POUND;
		default:
			cur = DOLLAR;
			break;
		}
		if (t == 1) {
			cout << "Duration: "; cin >> l;
			cout << "day price: "; cin >> d_p;
			cout << "journey price: "; cin >> j_p;
			p[i] = new vacation(s, l, d_p, j_p, cur);
		}
		else if (t == 2) {
			int d_c, d_a, p_c, p_a;
			cout << "duration in country: "; cin >> d_c;
			cout << "price in country: "; cin >> p_c;
			cout << "duration aboard: "; cin >> d_a;
			cout << "price aboard: "; cin >> p_a;
			p[i] = new bus_tour(s, d_c, p_c, d_a, p_a, cur);
		}
		cout << "\n\n";
	}
}

void print_pass(pass** p, int n) {
	cout << "\n\t***pass***\n";
	for (int i = 0; i < n; i++) {
		cout << i + 1 << ". ";
		p[i]->output();
		cout << endl;
	}
}

void sort(pass** p, int n) {
	pass** ptrpass;
	pass* temp = new pass;
	int i, t = 0;
	for (i = 1; i < n; i++) {
		if (*p[i] > *p[i - 1])
			continue;
		SwapValues(temp, p[i]);
		ptrpass = p + i - 1;
		while (*temp < **ptrpass) {
			SwapValues(*(ptrpass + 1), *ptrpass);
			if(--ptrpass < p) break;
		}
		SwapValues(*(ptrpass + 1), temp);
	}
}

double average(pass** p, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += p[i]->total();
	}
	return sum / n;
}

int main() {
	pass* (*p);
	int n;
	cout << "Enter number of pass: ";
	cin >> n;
	p = new pass * [n];
	input_pass(p, n);
	print_pass(p, n);
	sort(p, n);
	cout << "\n\tAfter sort:\n";
	print_pass(p, n);
	cout << "\n\tAverage price: " << average(p, n) << " UAH" << endl;
	return 0;
}

/*Input template:
6
2
USA
1
2
200
25
50
1
Lviv
2
3
11
10
2
Antananarivo
1
2
200
14
70
2
Krakow
2
3
250
7
20
1
Kahovka
3
4
5
53
1
Kyiv
2
30
10
10
*/