    //
    // Created by Lorenzo Carrano on 24/05/18.
    //

    #include "Company.h"
    #include "Profile.h"

    void Company::Set_Address(string &Legal,string &Amministrative) {


    _address = Legal+"(Legal) "+Amministrative+"(Amministrative)";



    }

    string Company::Get_Address() {

        return _address;
    }

    Company::Company() {

    }

    Company::Company(string &name, string &ID, string &address1, string &address2, string &activity) {


        Set_Name(name);
        Set_ID(ID);
        Set_Address(address1,address2);
        Set_Activity(activity);
        //p1.open("profile_informations.txt",ios::app);
        //p1<<_profile_tipe<<",ID:"<<_id<<","<<"Name:"<<_name<<","<<"Address:"<<_address<<","<<"Activity/Products:"<<_activity<<endl;




    }

    bool Company::New_Employee(string & NewEmployee_ID) {
        bool duplicate = false;
        bool completed_process = false;
        vector<string>::iterator it = _userIDs.begin();
        while(it != _userIDs.end()&&!duplicate){

            if(NewEmployee_ID == *it)
                duplicate = true;
            it++;
        }

        if(!duplicate){
            _userIDs.push_back(NewEmployee_ID);
            completed_process = true;
        }

        return completed_process;
    }

    bool Company::Remove_Employee(string &ID_to_remove) {
        bool found = false;
        bool completed_process = false;
        vector<string>::iterator it = _userIDs.begin();
        while(it<_userIDs.end()&&!found){

            if(ID_to_remove == *it)
                found = true;
            it++;
        }
        _userIDs.erase(it-1);

        return completed_process;
    }

    Company::~Company() {

    }

    void Company::Copy(Company obj){

        _id = obj.Get_ID();
        _name = obj.Get_Name();
        _address = obj.Get_Address();
        _activity = obj.Get_Activity();
        _ID_consociated_Companies = obj.Get_All_Consociated();
        _userIDs = obj.Get_All_Employees();
        _nPosts = obj.Get_nPosts();
        _receivedReactions.totLikes = obj.Get_Received_Likes();
        _receivedReactions.totDisLikes = obj.Get_Received_Dislikes();
        _givedReactions.totLikes = obj.Get_Gived_Likes();
        _givedReactions.totDisLikes = obj.Get_Gived_Dislikes();

    }

    string Company::InformationsStream() {

        return _id+", "+_profile_tipe+", Name: "+_name+", "+"Address: "+_address+", "+"Activity/Products: "+_activity;
    }

    bool Company::Add_Consociated_Company(string &ID) {
        bool find = false, process_completed = false;
        for(vector<string>::iterator it = _ID_consociated_Companies.begin();it<_ID_consociated_Companies.end() && !find;it++){

            if(ID == *it)
                find = true;


        }
        if(!find){

            _ID_consociated_Companies.push_back(ID);
            process_completed = true;
        }

        return process_completed;
    }

    int Company::Get_nEmployees() {





        return _userIDs.size();

    }

    vector<string> Company::Get_All_Consociated() {

        return _ID_consociated_Companies;


    }

    vector<string> Company::Get_All_Employees() {


        return _userIDs;
    }

    Company &Company::operator=(Company &C2) {

        (*this).Copy(C2);

        return *this;
    }

    string Company::Connections_Stream() {
        string to_return = "";

           for(vector<string>::iterator it = _userIDs.begin(); it < _userIDs.end(); it++){

               if(_ID_consociated_Companies.size() == 0) {
                   to_return += _id + ',' + *it + ",Job";
                   if (it < _userIDs.end() - 1)
                       to_return += '\n';
               }
               else{
                   to_return += _id + ',' + *it + ",Job" + '\n';
               }
            }

            for (vector<string>::iterator it = _ID_consociated_Companies.begin();
                 it < _ID_consociated_Companies.end(); it++) {

                to_return += _id + ',' + *it + ',' + "Consociated";
                if( it < _ID_consociated_Companies.end() -1)
                    to_return += '\n';

            }




        return to_return;
    }

    int Company::Get_nConsociated() {

        return _ID_consociated_Companies.size();

    }

    bool Company::Remove_Consociated(string &ID_to_remove) {
        bool found = false;
        bool completed_process = false;
        vector<string>::iterator it = _ID_consociated_Companies.begin();
        while(it<_ID_consociated_Companies.end()&&!found){

            if(ID_to_remove == *it)
                found = true;
            it++;
        }
        _ID_consociated_Companies.erase(it-1);

        return completed_process;

    }

    vector<string> Company::Get_Connected_IDs() {
        vector<string> Connected_IDs;
        vector<string>::iterator it;

        for(it = _userIDs.begin(); it < _userIDs.end(); it++){

            Connected_IDs.push_back((*it));

        }

        for(it = _ID_consociated_Companies.begin(); it < _ID_consociated_Companies.end(); it++){

            Connected_IDs.push_back((*it));

        }


        return Connected_IDs;
    }

    bool Company::Remove_Relation(string &ID_to_remove) {
        vector<string>::iterator it = _userIDs.begin();
        bool done = false;

        for(it; it < _userIDs.end() && !done; it++){


            if(*it == ID_to_remove){

                _userIDs.erase(it);
                done = true;
            }
        }
        for(it = _ID_consociated_Companies.begin(); it < _ID_consociated_Companies.end() && !done; it++){

            if(*it == ID_to_remove){

                _ID_consociated_Companies.erase(it);
                done = true;
            }

        }

        return done;
    }

    vector<string> Company::Get_Network() {

        vector<string> to_return = _userIDs;
        for(auto it = _ID_consociated_Companies.begin(); it < _ID_consociated_Companies.end(); it++){

            to_return.push_back(*it);

        }

        return to_return;
    }


