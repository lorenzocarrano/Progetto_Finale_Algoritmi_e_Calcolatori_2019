//
// Created by Lorenzo Carrano on 24/05/18.
//

#ifndef PROGETTO_INFORMATICA_V1_COMPANY_H
#define PROGETTO_INFORMATICA_V1_COMPANY_H

#include "Profile.h"

class Company : public Profile {
    const string _profile_tipe = "Company";
    vector<string> _ID_consociated_Companies;

public:
    Company();

    Company(string&, string&, string&,string&, string&);

    ~Company();
    void Set_Address(string &,string &);

    void Copy(Company);

    bool New_Employee(string&);

    bool Remove_Employee(string&);

    bool Remove_Consociated(string&ID_to_remove);

    bool Remove_Relation(string &ID_to_remove);

    bool Add_Consociated_Company(string&);

    int Get_nEmployees();

    vector<string> Get_All_Consociated();

    vector<string> Get_All_Employees();

    vector<string> Get_Connected_IDs();

    string Get_Address();

    int Get_nConsociated();

    string InformationsStream();

    string Connections_Stream();

    vector<string> Get_Network();

    Company &operator = (Company& C2); ///Overload Operatore '='

};


#endif //PROGETTO_INFORMATICA_V1_COMPANY_H
