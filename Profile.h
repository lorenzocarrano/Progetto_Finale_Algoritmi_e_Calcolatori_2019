//
// Created by Lorenzo Carrano on 24/05/18.
//

#ifndef PROGETTO_INFORMATICA_V1_PROFILE_H
#define PROGETTO_INFORMATICA_V1_PROFILE_H
#include <iostream>
#include <fstream>
#include <vector>
#include "Date.h"
#include <cmath>

using namespace std;
class Profile {
protected:

    typedef struct { ///per lupo solitario serve

        int totLikes;
        int totDisLikes;

    }Reactions;

    Reactions _givedReactions,_receivedReactions;

    string _name;
    string _id;
    string _address;
    string _activity;
    const string _profile_tipe = "Profile";
    vector<string> _userIDs;
    int _nPosts;

public:
    Profile();

    ~Profile();

      void Set_Name(string &);

      void Set_ID(string &);

      void Set_Activity(string &);

      void Set_Address(string &);

      void AddPostCont();

      void Add_Received_Like();

      void Add_Received_Dislike();

      virtual void Copy(Profile&);

     string Get_ID()const;

     string Get_Name()const;

     string Get_Activity()const;

     string Get_Address();

     int Get_nPosts();

     int Get_Gived_Likes();

     int Get_Gived_Dislikes();

     int Get_Received_Likes();

     int Get_Received_Dislikes();

     float Get_Feedback();

     string Get_Profile_Type();

     float Get_popularity_rapport();

    virtual vector<string> Get_Network();

    virtual string Connections_Stream();

    virtual vector<string> Get_Connected_IDs();

    virtual bool Remove_Relation(string&);

    virtual Profile &operator = (Profile& P2);

    virtual vector<string> Get_Relation_with(string&);

};


#endif //PROGETTO_INFORMATICA_V1_PROFILE_H
