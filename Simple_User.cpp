    //
    // Created by Lorenzo Carrano on 24/05/18.
    //

    #include "Simple_User.h"

    Simple_User::Simple_User() {
        string void_s = "";
        Date d;
        Set_Name(void_s);
        Set_Surname(void_s);
        Set_ID(void_s);
        Set_Address(void_s);
        Set_Activity(void_s);
        Set_Gender(void_s);
        Set_Birth_Date(d);
        _nPosts = 0;
        _nParents = 0;
    }

     Simple_User::Simple_User(string &name, string &surname, string &ID, string &address, string &job,Date bDate,string &gender){

        if(job == ""){
            job = "Unspecified";
        }

        if(address == ""){
            address = "Unspecified";
        }

        Set_Name(name);
        Set_Surname(surname);
        Set_ID(ID);
        Set_Address(address);
        Set_Activity(job);
        Set_Gender(gender);
        Set_Birth_Date(bDate);
         _nPosts = 0;
         _nParents = 0;

    }

    Simple_User::~Simple_User() {

        _RelationTipe.clear();

    }

    void Simple_User::Set_Address(string &Address) {

        _address = Address;

    }

    void Simple_User::Set_Birth_Date(Date bDate){

        _birthDate = bDate;


    }

    string Simple_User::Get_Address()const {

        return _address;

    }

    string Simple_User::Get_Surname()const {
        return _surname;
    }

    string Simple_User::Get_Gender()const {
        return _gender;
    }

    void Simple_User::Set_Surname(string &Surname) {

        _surname = Surname;

    }

    void Simple_User::Set_Gender(string &Gender) {

        _gender = Gender;

    }

    void Simple_User::Copy(Simple_User ogg) {

        _id = ogg.Get_ID();
        _name = ogg.Get_Name();
        _surname = ogg.Get_Surname();
        _address = ogg.Get_Address();
        _activity = ogg.Get_Activity();
        _gender = ogg.Get_Gender();
        _birthDate = ogg._birthDate;


    }

    string Simple_User::InformationsStream() {





        return _id + ", " + _profile_tipe + ", Name: " + _name + ", Surname: " + _surname + ", Address: " + _address + ", Job: " + _activity + ", BirthDate: " + _birthDate.DateString() + ", Gender: " + Get_Gender();



    }

    bool Simple_User::Add_Relation(string userID,string RelationTipe) {
        bool duplicate = false;
        bool process_completed = false;

        auto itID = _userIDs.begin(), itRel = _RelationTipe.begin();


        while(itID<_userIDs.end() && itRel < _RelationTipe.end()){

            if (userID == *itID && RelationTipe == *itRel)
                duplicate = true;


            itID++;
            itRel++;


        }

        if(!duplicate) {
            _userIDs.push_back(userID);
            _RelationTipe.push_back(RelationTipe);


            if(RelationTipe == "Parent") {

                _nParents++;
            }

            process_completed = true;

        }
    return process_completed;
    }

    int Simple_User::Get_nPosts()const {
        return _nPosts;
    }

    void Simple_User::Add_GivedLike() {

        _givedReactions.totLikes++;


    }

    void Simple_User::Add_GivedDislike() {

        _givedReactions.totDisLikes++;

    }

    int Simple_User::Get_GivedLike() {

        return _givedReactions.totLikes;

    }

    int Simple_User::Get_GivedDislike() {

        return _givedReactions.totDisLikes;

    }

    int Simple_User::Get_TotGivedReactions() {

        return _givedReactions.totLikes+_givedReactions.totDisLikes;

    }

    void Simple_User::Copy(vector<Simple_User>::iterator it) {



        _id = (*it).Get_ID();
        _name = (*it).Get_Name();
        _surname = (*it).Get_Surname();
        _address = (*it).Get_Address();
        _activity = (*it).Get_Activity();
        _gender = (*it).Get_Gender();



    }

    Date Simple_User::Get_BirthDate() {
        return _birthDate;
    }

    int Simple_User::Get_Age() {

        Date Actual_Date;


    return Actual_Date.yearsFrom(_birthDate);

    }

    int Simple_User::Get_nFriends() {
        int cont = 0;

        for(vector<string>::iterator it = _RelationTipe.begin(); it<_RelationTipe.end();it++){


            if((*it) == "Friend" )
                cont++;


        }

        return cont;
    }

    int Simple_User::Get_nAcquaintances() {
        int cont = 0;
        for(vector<string>::iterator it_Rel = _RelationTipe.begin(); it_Rel < _RelationTipe.end(); it_Rel++){

            if(*it_Rel == "Friend" || *it_Rel == "Followed" || *it_Rel == "Follower")
                cont++;

        }

        return cont;

    }

    int Simple_User::Get_nRelations() {

        return _userIDs.size();


    }

    vector<string> Simple_User::Get_Network(){
        vector<string> to_return;
        bool Connected;

        auto it_ID = _userIDs.begin(), it_Rel = _RelationTipe.begin();

        for(it_ID; it_ID < _userIDs.end() && it_Rel < _RelationTipe.end(); it_ID ++, it_Rel++){

            Connected = false;

            for(int i = 0; i < 3 &&! Connected; i++){

                if(*it_Rel == Network_Relations[i]){

                    Connected = true;
                    to_return.push_back(*it_ID);

                }

            }

        }

        return to_return;
    }

    string Simple_User::Connections_Stream() {

        string rel_stream = "";
        auto itID = _userIDs.begin(), itRl = _RelationTipe.begin();

        while(itID < _userIDs.end()){             ///Basta questa condizione perchè _userIDs e _RelationTipe sono di ugual lunghezza 'per costruzione'

            if(*itRl == "Child" || *itRl == "Parent" || *itRl == "Follower" || *itRl == "Followed")
            rel_stream += *itID + ',' + _id + ',' + *itRl;
            else rel_stream += _id + ',' + *itID + ',' + *itRl;

            if(itID < _userIDs.end()-1)
                rel_stream += '\n';

            itID++; itRl++;
        }


        return rel_stream;

    }

    int Simple_User::Get_nParents() {
        return _nParents;
    }

    bool Simple_User::HasChildren() {

        return ((*this).Get_n_Children() > 0)? true : false;


    }

    void Simple_User::Parents(string &Parent1, string &Parent2) {

        Parent1 = ""; Parent2 = "";


        auto itID = _userIDs.begin(), itRl = _RelationTipe.begin();
        while(itID < _userIDs.end() && (Parent1 == "" || Parent2 == "")){

            bool P1filled = false;

            if((*itRl) == "Parent"){

                if(Parent1 == ""){

                    Parent1 = (*itID);
                    P1filled = true;

                }
                else if(Parent2 == "" && !P1filled){

                    Parent2 = (*itID);

                }

            }

            P1filled = false;

            itID++; itRl++;
        }










    }

    vector<string> Simple_User::Get_Children() {

        vector<string> to_return;
        vector<string>::iterator it_IDs = _userIDs.begin();

        for(vector<string>::iterator it = _RelationTipe.begin();it<_RelationTipe.end();it++){

            if(*it == "Child")
                to_return.push_back(*it_IDs);

            it_IDs++;

        }



    return to_return;

    }

    void Simple_User::Set_Company_Work(string &Company_id) {
        bool already_employee = false;
        for(vector<string>::iterator it = _userIDs.begin(); it < _userIDs.end() && !already_employee;it++){

            if(*it == Company_id)
                already_employee = true;

            if(!already_employee){
                Add_Relation(Company_id,"Employee");

            }
        }

    }

    bool Simple_User::New_Group(string & GroupID) {

        return  Add_Relation(GroupID, "Member");
    }

    int Simple_User::Get_n_Children() {

        return (Get_Children()).size();
    }

    bool Simple_User::Has_a_Job() {
        bool ans = false;

        vector<string>::iterator it_Rel = _RelationTipe.begin();

        while(it_Rel < _RelationTipe.end() && !ans){

            if(*it_Rel == "Employee")
                ans = true;


            it_Rel++;

        }


       return ans;
    }

    bool Simple_User::Member_of_a_Group() {
        bool ans = false;

        vector<string>::iterator it_Rel = _RelationTipe.begin();

        while(it_Rel < _RelationTipe.end() && !ans){

            if(*it_Rel == "Member")
                ans = true;


            it_Rel++;

        }

    return ans;
    }

    bool Simple_User::Remove_Relation(string &rel_id, string def_relation) {
       bool process_completed = false;

        auto id_it = _userIDs.begin(), rel_it = _RelationTipe.begin();

        if(def_relation == "default") {
            while (id_it < _userIDs.end() && !process_completed) {

                if (*id_it == rel_id) {

                    _userIDs.erase(id_it);
                    _RelationTipe.erase(rel_it);
                    process_completed = true;
                } else {
                    id_it++;
                    rel_it++;

                }
            }
        }

        else{

            rel_it = _RelationTipe.begin();
            for(id_it = _userIDs.begin(); id_it < _userIDs.end() && rel_it < _RelationTipe.end(); id_it++, rel_it++){

                if (*id_it == rel_id && *rel_it == def_relation){

                    _userIDs.erase(id_it);
                    _RelationTipe.erase(rel_it);
                    process_completed = true;
                }

            }

        }

        if(process_completed){

                if(*rel_it == "Parent")
                    _nParents--;

        }

        return process_completed;
    }

    bool Simple_User::Has_Common_Child(Simple_User user2) {


        bool found = false;

        vector<string> Children_of_id1;
        vector<string> Children_of_id2;


        Children_of_id1 = (*this).Get_Children();
        Children_of_id2 = (user2).Get_Children();

        for(vector<string>::iterator it1 = Children_of_id1.begin();it1<Children_of_id1.end() && !found;it1++) {
            for(vector<string>::iterator it2 = Children_of_id2.begin();it2<Children_of_id2.end() && !found;it2++){

                if(*it1 == *it2)
                    found = true;

            }

        }

        Children_of_id1.clear();
        Children_of_id2.clear();
        return found;


    }

    Simple_User &Simple_User::operator=(Simple_User &U2) {

        (*this).Copy(U2);
        return (*this);

    }

    vector<string> Simple_User::Get_Relation_with(string & ID) {
        vector<string> to_return;

        auto it_ID = _userIDs.begin(), it_Rel = _RelationTipe.begin();

        for(it_ID; it_ID < _userIDs.end() && it_Rel < _RelationTipe.end(); it_ID++,it_Rel++){

            if(*it_ID == ID)
                to_return.push_back(*it_Rel);

        }

        return to_return;
    }































