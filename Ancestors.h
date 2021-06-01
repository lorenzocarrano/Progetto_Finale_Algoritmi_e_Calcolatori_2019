    //
    // Created by Lorenzo Carrano on 17/07/18.
    //

    #ifndef PROGETTO_INFORMATICA_V1_ANCESTORS_H
    #define PROGETTO_INFORMATICA_V1_ANCESTORS_H

    #include <iostream>
    using namespace std;
    class Ancestors {

        string _id;

        int _generation_level;

    public:
        Ancestors();

        ~Ancestors();

        void Set_Gnt_level(const int &);

        void Set_id(const string &);

        int Get_Gnt_level();

        string Get_id();

    };


    #endif //PROGETTO_INFORMATICA_V1_ANCESTORS_H
