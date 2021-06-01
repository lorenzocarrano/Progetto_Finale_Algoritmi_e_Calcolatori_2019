    //
    // Created by Lorenzo Carrano on 03/12/2018.
    //

    #ifndef PROGETTO_INFORMATICA_V1_POST_H
    #define PROGETTO_INFORMATICA_V1_POST_H

    #include <iostream>
    #include <vector>
    #include "Date.h"
    using namespace std;
    class Post {

    public:
        Post(string&,string&);

        Post(string&,string&,Date&);

        ~Post();

        void New_Like(string&);

        void New_Dislike(string&);

        void Remove_Like(string&);

        void Remove_Dislike(string&);

        int Get_nLikes();

        int Get_nDislikes();

        string Get_Author();

        void Modify_message(string&);

        string PostData();

        void Set_Creation_Date(Date);

        friend std::ostream &operator<<(std::ostream &stream, const Post &p);

    private:

        Date _Creation_Date;
        string _authorID, _message;
        vector<string> _Likes, _Dislikes;



    };


    #endif //PROGETTO_INFORMATICA_V1_POST_H
