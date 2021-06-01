    //
    // Created by Lorenzo Carrano on 03/12/2018.
    //

    #include "Post.h"

    Post::Post(string& authorID, string& message) {

        _authorID = authorID;
        _message = message;


    }

    Post::Post(string& authorID,string& message,Date& creation_Date) {

        _authorID = authorID;
        _message = message;
        _Creation_Date.Copy(creation_Date);

    }

    Post::~Post() {

    }

    void Post::New_Dislike(string& ID) {
    bool not_repetition = true;
        for(vector<string>::iterator it = _Dislikes.begin();it < _Dislikes.end() && not_repetition;it++){

            if(*it == ID)
                not_repetition = false;



        }


        if(not_repetition)
            _Dislikes.push_back(ID);
        else
            Remove_Dislike(ID);

        not_repetition = true;

        for(vector<string>::iterator it = _Likes.begin(); it < _Likes.end() && not_repetition; it++){

            if(ID == *it) {
                Remove_Like(ID);
                not_repetition = false;
            }
        }

    }

    void Post::New_Like(string& ID) {
        bool not_repetition = true;
        for(vector<string>::iterator it = _Likes.begin();it < _Likes.end() && not_repetition;it++){

            if(*it == ID)
                not_repetition = false;
        }


        if(not_repetition)
            _Likes.push_back(ID);
        else
            Remove_Like(ID);

        not_repetition = true;

        for(vector<string>::iterator it = _Dislikes.begin(); it < _Dislikes.end() && not_repetition; it++){

            if(ID == *it) {
                Remove_Dislike(ID);
                not_repetition = false;
            }
        }

    }

    void Post::Remove_Like(string& ID) {

      bool removed = false;

        for(vector<string>::iterator it = _Likes.begin();it < _Likes.end() &&  !removed;it++){

            if(*it == ID){

                _Likes.erase(it);
                removed = true;

            }

        }



    }

    void Post::Remove_Dislike(string& ID) {


        bool removed = false;

        for(vector<string>::iterator it = _Dislikes.begin();it < _Dislikes.end() &&  !removed;it++){

            if(*it == ID){

                _Dislikes.erase(it);
                removed = true;

            }

        }


    }

    int Post::Get_nLikes() {
        return _Likes.size();
    }

    int Post::Get_nDislikes() {
        return _Dislikes.size();
    }

    void Post::Modify_message(string& modified_text) {

        _message = modified_text;

    }

    string Post::PostData() {

        string string_to_return = "";
        vector<string>::iterator it = _Likes.begin();
        int i = 0;
        string mex = "";

        while((*this)._message[i] != '\0' ){
            mex += (*this)._message[i];
            i++;
        }

        string_to_return = _authorID + ',' + mex + '~' + "likes:{";

        for(it;it< _Likes.end();it++){

            string_to_return += *it;
            if(it != (_Likes.end())-1)
                string_to_return += ',';

        }
        string_to_return += "} dislikes:{";

        for(it = _Dislikes.begin();it< _Dislikes.end();it++){

            string_to_return += *it;
            if(it != (_Dislikes.end())-1)
                string_to_return += ',';

        }

        string_to_return += "} Creation_Date: ";
        string_to_return += _Creation_Date.DateString();

        return string_to_return;
    }

    string Post::Get_Author() {
        return _authorID;
    }

    void Post::Set_Creation_Date(Date creation_Date) {

        _Creation_Date.Copy(creation_Date);

    }

    std::ostream &operator<<(std::ostream &stream, const Post &p) {

        string to_stream = "";
        int i = 0;
        while(p._message[i] != '\0' ){
            to_stream += p._message[i];
            i++;
        }

        stream << to_stream;

        return stream;
    }


