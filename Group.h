//
// Created by Lorenzo Carrano on 28/05/18.
//

#ifndef PROGETTO_INFORMATICA_V1_GROUP_H
#define PROGETTO_INFORMATICA_V1_GROUP_H

#include "Profile.h"

class Group : public Profile {

    string _profile_tipe = "Group";

public:
    Group();

    Group(string&,string&,string&,string&);

    ~Group();

    void Set_Address(string&);

    string InformationsStream();

    string Connections_Stream();

    bool New_Member(string&);

    bool Remove_Relation(string&);

    string Get_Address();

    void Copy(Group);

    vector<string> Get_Members();

    int Get_nMembers();

    Group &operator = (Group& G2); ///Overload Operatore '='

};


#endif //PROGETTO_INFORMATICA_V1_GROUP_H
