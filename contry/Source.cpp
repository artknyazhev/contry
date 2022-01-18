#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"

using namespace nlohmann;
using namespace std;

class Country
{
public:
	Country() {
		Load();
	}
	void Add(string country, string city) {
		base[country].push_back(city);
	}
	void Load() {
		ifstream fout("base.json");
		if (fout.is_open() && fout.peek() != EOF) {
			string str, temp;
			while (getline(fout, str))
				temp += str;
			if (!temp.empty())
				base = json::parse(temp);
		}
		fout.close();
	}
	void Show() {
		for (const auto& n : base.items()) {
			cout <<"\n\n" << (string)n.key() << "\n------------\n";
			for (int i = 0; i < base[n.key()].size(); i++)
				cout << (string)base[n.key()][i] << endl;
		}
	}
	void DeleteCity(string city) {
		for (const auto& n : base.items()) {
			for (int i = 0; i < base[n.key()].size(); i++)
				if ((string)base[n.key()][i] == city)
					base[n.key()].erase(base[n.key()].begin() + i);
		}
	}
	void DeleteCountry(string country) {
		
			if (base.contains(country))
				base.erase(country);
	
	}
	void Count() {
		int cnt = 0;
		for (const auto& n : base.items()) {
			for (int i = 0; i < base[n.key()].size(); i++)
				cnt++;
		}
		cout << "Всего городов: " << cnt;
	}
	void Search(string city) {
		for (const auto& n : base.items()) {
			for (int i = 0; i < base[n.key()].size(); i++)
				if ((string)base[n.key()][i] == city)
					cout << endl << n.key() << " - " << base[n.key()][i] << endl;
		}
	
	}
	~Country() {
		ofstream fout("base.json");
		fout << base.dump(2);
		fout.close();
	};

private:
	json base;
};


int main() {
	setlocale(LC_ALL, "rus");
	Country c;
	c.Show();
	cout << "\n-----Delete Kiev------\n";
	c.DeleteCity("Kiev");
	c.Show();
	cout << "\n-----Delete Poland------\n";
	c.DeleteCountry("Poland");
	c.Show();
	cout << "\n-----Count------\n";
	c.Count();
	cout << "\n-----Search------\n";
	c.Search("Odessa");
	return 0;
}