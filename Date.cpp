    //
    // Created by Lorenzo Carrano on 30/05/18.
    //

    #include "Date.h"


    Date::Date(){

        time_t rawtime;
        time (&rawtime);
        struct tm* leggibile;
        leggibile = localtime(&rawtime);

        _day = leggibile->tm_mday;
        _month = leggibile->tm_mon+1;
        _year = leggibile->tm_year+1900;

    }

    Date::Date ( int dd , int mm , int yyyy){

        _date_Check = true;

        is_leap_year(yyyy);
        if((mm<0)||(dd<0)||(yyyy<0))
            _date_Check = false;


        if((mm == 11 || mm == 4 || mm ==6||mm == 9)&&(dd>30)){

            _date_Check = false;


        }
        if(mm == 2 ){
            if((!_leap)&&(dd>28)){
                _date_Check = false;
            }
            if((_leap)&&(dd>29)){
                _date_Check = false;
            }

        }


        if((mm == 1 || mm == 3 || mm ==5||mm == 7 || mm==8 || mm==10|| mm==12)&&(dd>31)){

            _date_Check = false;


        }

            _day = dd;
            _month = mm;
            _year = yyyy;


    }

    string Date::DateString () const {

        return to_string(_day)+"/"+to_string(_month)+"/"+to_string(_year);

    }

    Date::Date ( const Date & to_copy ){

        _day = to_copy._day;
        _month = to_copy._month;
        _year = to_copy._year;

    }

    int Date::yearsFrom(Date d) const{


        return abs(d._year-_year);



    }

    string Date::printyearsFrom(Date d) const{

        int nYears;
        bool past = false;
        string yearFromDate;

        yearFromDate = (d._year>_year) ? "Anni dalla data inserita:" : "Anni alla data inserita: " + to_string(yearsFrom());

        return yearFromDate;

    }

    bool Date::is_leap_year(int y){
        _leap = (y%4==0&&y%400==0&&y%100!=0) ? true : false;
        return _leap;




    }

    int Date::year () const {

        return _year;


    }

    int Date::month () const{
        return _month;
    }

    int Date::day () const {
        return _day;
    }

    std::ostream &operator<<(std::ostream &stream, const Date &d) {

        stream<<d.DateString();

        return stream;

    }

    bool & operator > (const Date &d1 , const Date &d2){

        bool after;

        after = ((d1._year > d2._year) || (d1._year == d2._year && d1._month > d2._month) ||(d1._year == d1._year && d1._month == d2._month &&d1._day > d2._day) ) ? true : false;   ///past = dIn._year <= dNow._year; La potevo scrivere anche così


        return after;





    }

    void Date::Copy(Date temp) {

        _day = temp._day;
        _month = temp._month;
        _year = temp._year;

    }

    void Date::SetDate(int &dd, int &mm, int &yyyy) {


        _day = dd;
        _month = mm;
        _year = yyyy;





    }

    bool Date::Date_Check() {

        bool verified = false;

        verified = (((_month == 11 || _month == 4 || _month == 6 || 9) &&(_day > 0 && _day < 30))||
                    ((_month == 2)&&(_day > 0 &&_day < 28))||((_month == 2)&&((_year%100 == 0 && _year%400 == 0 ) ||
                                                                  (_year%100 != 0 && _year%4 == 0))&&(_day > 0 &&_day < 28)) || ((_month == 1 || _month == 3 || _month == 5 || _month == 7 || _month == 8 || _month == 10)&&(_day>0&&_day<31)))

                   ? true : false;




        return verified;

    }

    Date::Date(string &str) {

        SetDate(str);

    }

    void Date::SetDate(string &str) {

        int cont = 0,bookmark = 0;
        string to_convert = "";
        for(int i = 0; i <= str.size(); i++){

            if(str[i] == '/' || str[i] == '\0'){
                for(int j = bookmark; j < i; j++){

                    to_convert += str[j];

                }
                bookmark = i+1;

                switch(cont){
                    case 0:
                        _day = atoi(to_convert.c_str());
                        break;
                    case 1:
                        _month = atoi(to_convert.c_str());
                        break;
                    case 2:
                        _year = atoi(to_convert.c_str());
                        break;

                    default:break;
                }

                cont++;
                to_convert = "";
            }


        }




    }

