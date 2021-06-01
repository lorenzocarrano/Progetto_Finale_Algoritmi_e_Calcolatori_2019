    //
    // Created by Lorenzo Carrano on 24/05/18.
    //

    #include "Profile.h"

    Profile::Profile() {

        _activity = "Unspecified";
        _address = "Unspecified";
        _receivedReactions.totLikes = 0;
        _receivedReactions.totDisLikes = 0;
        _givedReactions.totLikes = 0;
        _givedReactions.totDisLikes = 0;




    }

    Profile::~Profile() {

        _userIDs.clear();

    }

    void Profile::Set_ID(string &ID){

        _id = ID;


    }

    void Profile::Set_Activity(string &Activity) {

        _activity = Activity;


    }

    string Profile::Get_ID()const {

        return _id;
    }

    string Profile::Get_Activity()const {

        return _activity;
    }

    void Profile::Set_Name(string &Name) {

        _name = Name;

    }

    string Profile::Get_Name()const {

        return _name;
    }

    void Profile::AddPostCont() {


            _nPosts++;


    }

    void Profile::Add_Received_Like() {

        _receivedReactions.totLikes++;

    }

    void Profile::Add_Received_Dislike() {

        _receivedReactions.totDisLikes++;
    }

    void Profile::Copy(Profile &) {

    }

    int Profile::Get_nPosts() {
        return _nPosts;
    }

    int Profile::Get_Gived_Likes() {

        return _givedReactions.totLikes;

    }

    int Profile::Get_Gived_Dislikes() {

        return _givedReactions.totDisLikes;

    }

    int Profile::Get_Received_Likes() {
        return _receivedReactions.totLikes;
    }

    int Profile::Get_Received_Dislikes() {
        return _receivedReactions.totDisLikes;
    }

    float Profile::Get_Feedback() {

        return (_receivedReactions.totDisLikes != 0) ? round((float)_receivedReactions.totLikes / _receivedReactions.totDisLikes *100)/100 : 0;

    }

    float Profile::Get_popularity_rapport() {

        return (_givedReactions.totDisLikes + _givedReactions.totLikes != 0) ? round((float)((_receivedReactions.totLikes + _receivedReactions.totDisLikes)) / (_givedReactions.totLikes + _givedReactions.totDisLikes) *100)/100 : 0;

    }

    void Profile::Set_Address(string &) {

    }

    string Profile::Get_Address() {
        return _address;
    }

    string Profile::Connections_Stream() {
        return std::string();
    }

    vector<string> Profile::Get_Connected_IDs() {
        return _userIDs;
    }

    string Profile::Get_Profile_Type() {
        return _profile_tipe;
    }

    bool Profile::Remove_Relation(string& ID_to_remove) {
        return false;
    }

    Profile &Profile::operator=(Profile &P2) {

        (*this).Copy(P2);

        return (*this);
    }

    vector<string> Profile::Get_Network() {
        return _userIDs;
    }

    vector<string> Profile::Get_Relation_with(string& ID) {

        return vector<string>();
    }











