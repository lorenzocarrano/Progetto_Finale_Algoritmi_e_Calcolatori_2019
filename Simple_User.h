//
// Created by Lorenzo Carrano on 24/05/18.
//

#ifndef PROGETTO_INFORMATICA_V1_SIMPLE_USER_H
#define PROGETTO_INFORMATICA_V1_SIMPLE_USER_H
#include "Profile.h"

class Simple_User : public Profile {


    vector<string> _RelationTipe;
    string _surname;
    const string _profile_tipe = "Simple_User";
    string _gender;
    Date _birthDate;
    int _nParents;
    string Network_Relations[3]={"Followed","Friend","Member"};


public:
    Simple_User();

    Simple_User(string &, string &, string &, string &, string &,Date, string &/*...*/);

    ~Simple_User();

    void Set_Surname(string &);

    void Set_Address(string &);

    void Set_Gender(string &);

    void Set_Birth_Date(Date);

    void Set_Company_Work(string &);

    bool New_Group(string&);

    string Get_Address()const;

    string Get_Surname()const;

    string Get_Gender()const;

    Date Get_BirthDate();

    int Get_Age();

    int Get_nFriends();

    int Get_nAcquaintances();

    int Get_nRelations();

    int Get_nParents();

    int Get_n_Children();

    vector<string> Get_Children();

    void Parents(string &, string &);

    bool HasChildren();

    void Copy(Simple_User);

    void Copy(vector<Simple_User>::iterator it);

    bool Add_Relation(string, string);

    void Add_GivedLike();

    void Add_GivedDislike();

    int Get_GivedLike();

    int Get_GivedDislike();

    int Get_TotGivedReactions();

    string InformationsStream();

    string Connections_Stream();

    int Get_nPosts()const;

    bool Has_a_Job();

    bool Member_of_a_Group();

    bool Remove_Relation(string&,string def_relation = "default");

    bool Has_Common_Child(Simple_User);

    vector<string> Get_Network();

    vector<string> Get_Relation_with(string&);

    Simple_User &operator = (Simple_User& U2); ///Overload Operatore '='

};
#endif //PROGETTO_INFORMATICA_V1_SIMPLE_USER_H
