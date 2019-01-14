#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<cctype>

bool open_r_file(std::ifstream & file, const char* file_name);
bool open_w_file(std::ofstream & file, const char* file_name);
std::string get_name(int number);
void file_to_vector(std::ifstream & file, std::vector<std::string> & name_list);
void Write_file(std::ostream & destination, std::vector<std::string> & name_list);
bool string_compare(std::string & s1, std::string & s2);
bool equal(std::string s1, std::string s2);


////
////
int main()
{
	std::ifstream bolek, lolek;
	std::ofstream lista_gosci;
	if (!open_r_file(bolek, "bolek.txt"))
	{
		std::cout << "plik bolek.txt nie istnieje w odpowiednim katalogu.\nKoniec programu";
		std::cin.get();
		return 1;
	}
	if (!open_r_file(lolek, "lolek.txt"))
	{
		std::cout << "plik lolek.txt nie istnieje w odpowiednim katalogu.\nKoniec programu";
		std::cin.get();
		return 1;
	}
	std::vector<std::string> bolek_list, lolek_list, guest_list;

	file_to_vector(bolek, bolek_list);
	file_to_vector(lolek, lolek_list);

	std::sort(bolek_list.begin(), bolek_list.end(), string_compare);
	std::sort(lolek_list.begin(), lolek_list.end(), string_compare);

	std::ostream & os(std::cout);		// deklaracja obiektu ostrream!!!!
	Write_file(os, bolek_list);
	std::cout << "\n\n";
	Write_file(os, lolek_list);
	std::cout << "\n\n";
	std::back_insert_iterator<std::vector<std::string>> iiter(guest_list);
	std::copy(bolek_list.begin(), bolek_list.end(), iiter);
	std::copy(lolek_list.begin(), lolek_list.end(), iiter);
	std::sort(guest_list.begin(), guest_list.end(), string_compare);
	
	std::vector<std::string>::iterator iv = std::unique(guest_list.begin(), guest_list.end(), equal);
	guest_list.erase(iv, guest_list.end());

	if (!open_w_file(lista_gosci, "lista_gosci.txt"))
	{
		std::cout << "nie udalo sie otworzyc pliku lista_gosci.txt.\nKoniec programu";
		std::cin.get();
		return 1;
	}

	Write_file(os, guest_list);
	Write_file(lista_gosci, guest_list);
	lista_gosci.close();
	std::cin.get();
	return 0;
}



/////
/////


bool open_r_file(std::ifstream & file, const char* file_name)
{
	file.open(file_name);
	if (!file.good())
	{
		std::cout << "Nie mozna otworzyc pliku, " << file_name << ".\n";
		return false;
	}
	return true;
}

bool open_w_file(std::ofstream & file, const char* file_name)
{
	file.open(file_name);
	if (!file.good())
	{
		std::cout << "Nie mozna otworzyc pliku, " << file_name << ".\n";
		return false;
	}
	return true;	
}

std::string get_name(int number)
{
	std::string name;
	if (number > 0)
	{
		std::cout << "podaj nazwe " << number << " pliku do odczytu: ";
		std::cin >> name;
	}
	if (number == 0)
	{
		std::cout << "podaj nazwe pliku do zapisu: ";
		std::cin >> name;
	}
	while (std::cin.get() != '\n')
		continue;
	return name;
}

void file_to_vector(std::ifstream & file, std::vector<std::string> & name_list)
{
	std::string temp;
	while (!file.eof())
	{
		getline(file, temp);
		name_list.push_back(temp);
		file.peek();		//sprawdzamy czy to koniec pliku
	}
	file.close();
}

void Write_file(std::ostream & destination,std::vector<std::string> & name_list)
{
	
	for (std::vector<std::string>::iterator it = name_list.begin(); it != name_list.end(); ++it)
		destination << *it<<'\n';
}



bool string_compare(std::string & s1, std::string & s2)
{
	std::transform(s1.begin(), s1.end(), s1.begin(), std::tolower);
	std::transform(s1.begin(), s1.begin()+1, s1.begin(), std::toupper);
	std::transform(s2.begin(), s2.end(), s2.begin(), std::tolower);
	std::transform(s2.begin(), s2.begin() + 1, s2.begin(), std::toupper);
	return s1 < s2;
}

bool equal(std::string s1, std::string s2)
{
	//std::transform(s1.begin(), s1.end(), s1.begin(), std::tolower);
	//std::transform(s2.begin(), s2.end(), s2.begin(), std::tolower);
	return s1 == s2;
}