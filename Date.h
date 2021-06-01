//
// Created by Lorenzo Carrano on 30/05/18.
//

#ifndef PROGETTO_INFORMATICA_V1_DATE_H
#define PROGETTO_INFORMATICA_V1_DATE_H

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Date {
public :

    Date(); //Setta alla Data Attuale

    Date(int d, int m, int y);

    Date(string &str); //Legge data da stringa nel formato dd/mm/yyyy e vi si imposta

    Date(const Date &to_copy); //Copy Constructor

    int year() const;

    int month() const;

    int day() const;

    void Copy(Date);

    int yearsFrom(Date d = Date()) const;

    bool Date_Check();      //verifica che la data inserita sia corretta

    void SetDate(int&,int&,int&);

    void SetDate(string &str);

    string printyearsFrom(Date d = Date()) const;

    std::string DateString() const;       //ritorna una stringa della data

    friend std::ostream &operator<<(std::ostream &stream, const Date &d); // overload dell'operatore <<

    friend bool &operator>(const Date &d1, const Date &d2); //overload operatore > --> Se data1>data2, data1 è più recente

private :

    int _day;
    int _month;
    int _year;
    bool _leap;
    bool _date_Check;
    bool is_leap_year(int y);

};





#endif //PROGETTO_INFORMATICA_V1_DATE_H
