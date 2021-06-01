    //
    // Created by Lorenzo Carrano on 28/05/18.
    //

    #include "Group.h"

    Group::Group() {

    }

    Group::Group(string &name, string &ID, string &address, string &activity) {

        Set_Name(name);
        Set_ID(ID);
        Set_Address(address);
        Set_Activity(activity);

    }

    Group::~Group() {

    }

    void Group::Set_Address(string &Address) {

        _address = Address;

    }

    void Group::Copy(Group ogg) {

        _id = ogg.Get_ID();
        _name = ogg.Get_Name();
        _address = ogg.Get_Address();
        _activity = ogg.Get_Activity();

    }

    string Group::InformationsStream() {

        return _id+", "+_profile_tipe+", "+"Name: "+_name+","+" Address: "+_address+","+" Topic: "+_activity;

    }

    string Group::Get_Address() {
        return _address;
    }

    bool Group::New_Member(string & NewMemberID) {
        bool duplicate = false;
        bool completed_process = false;
        vector<string>::iterator it = _userIDs.begin();
        while(it != _userIDs.end()&&!duplicate){

            if(NewMemberID == *it)
                duplicate = true;
                it++;
        }

        if(!duplicate){
             _userIDs.push_back(NewMemberID);
             completed_process = true;
        }

        return completed_process;
    }

    bool Group::Remove_Relation(string &ID_to_remove) {

       bool completed_process = false;

        vector<string>::iterator it = _userIDs.begin();
        while(it<_userIDs.end()&&!completed_process){

            if(*it == ID_to_remove) {

                _userIDs.erase(it);
                completed_process = true;

            }

             it++;
        }


        return completed_process;
    }

    int Group::Get_nMembers() {

        return _userIDs.size();

    }

    vector<string> Group::Get_Members() {
        return _userIDs;
    }

    string Group::Connections_Stream() {

        string to_return = "";

        for(vector<string>::iterator it = _userIDs.begin(); it < _userIDs.end(); it++){

                to_return += _id + ',' + *it + ",Group";
                if (it < _userIDs.end() - 1)
                    to_return += '\n';


            }

        return to_return;
    }

    Group &Group::operator=(Group &G2) {

        (*this).Copy(G2);

        return (*this);
    }










