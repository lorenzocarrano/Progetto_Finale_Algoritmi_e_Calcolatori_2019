    //
    // Created by Lorenzo Carrano on 17/07/18.
    //

    #include "Ancestors.h"
    Ancestors::Ancestors() {

        _generation_level = 0;

    }

    Ancestors::~Ancestors() {

    }

    void Ancestors::Set_Gnt_level(const int &gnt_lvl) {

        _generation_level = gnt_lvl;

    }

    void Ancestors::Set_id(const string &ID) {

        _id = ID;

    }

    int Ancestors::Get_Gnt_level() {
        return _generation_level;
    }

    string Ancestors::Get_id() {
        return _id;
    }

