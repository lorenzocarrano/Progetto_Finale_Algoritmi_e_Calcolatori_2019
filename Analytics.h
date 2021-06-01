    //
    // Created by Lorenzo Carrano on 14/06/18.
    //

    #ifndef PROGETTO_INFORMATICA_V1_ANALYTICS_H
    #define PROGETTO_INFORMATICA_V1_ANALYTICS_H
    #include <iostream>
    #include <fstream>
    #include <cmath>
    #include "Basic_Features.h"
    #include "Ancestors.h"
    using namespace std;

    void Display_Users_Relations_Number(vector<Simple_User>::iterator it,vector<Simple_User>::iterator end){


        for(it;it<end;it++){

            cout<< (*it).Get_ID() <<"     "<<(*it).Get_nRelations()<<endl;



        }

    }

    int Employees_Number(vector<Company>::iterator Cbegin,vector<Company>::iterator end,vector<Company>::iterator current_obj,char &mode){

        int n_Empl = 0;
        vector<Company>::iterator it;
        vector<Company>::iterator Cfind;
        vector<string> ID_Consociated;

        switch (mode) {

            case '0':


                   n_Empl = (*current_obj).Get_nEmployees();


                break;

            case '1':



                    n_Empl += (*current_obj).Get_nEmployees();
                    ID_Consociated = (*current_obj).Get_All_Consociated();
                    for(vector<string>::iterator i = ID_Consociated.begin(); i < ID_Consociated.end(); i++){

                        if(Search_Profile((*i),Cbegin,end,Cfind)){

                            n_Empl += (*Cfind).Get_nEmployees();

                        }
                    }

                    ID_Consociated.clear();

                break;
            default:break;

        }


       return n_Empl;
    }

    vector<Company>::iterator Company_with_more_Employees(vector<Company>::iterator begin, vector<Company>::iterator end,char ans){

        vector<Company>::iterator max_employee_it = begin;

        for(vector<Company>::iterator it = begin; it < end; it++) {

            if(Employees_Number(begin, end,it, ans) > (*max_employee_it).Get_nEmployees())
                max_employee_it = it;

        }

        return max_employee_it;
    }

    void Display_Employees_and_Consociated_Number(vector<Company>::iterator begin, vector<Company>::iterator end,char ans){

        for(vector<Company>::iterator it = begin; it < end; it++) {

            cout<<endl<<(*it).Get_ID()<<" --> Employee number: "<<Employees_Number(begin, end,it, ans)<<"    Consociated Company number: "<<((*it).Get_All_Consociated()).size();

        }



    }

    int Members_Count_for_every_Group(vector<Group>::iterator it,vector<Group>::iterator end){

        for(it;it<end;it++){

            cout<<(*it).Get_ID()<<"    number of members: "<<(*it).Get_nMembers()<<endl;


        }



    }

    vector<Post>::iterator Most_Liked_Post(vector<Post>::iterator it,vector<Post>::iterator end) { ///Probabilimente meglio farla nel main così

        vector<Post>::iterator MostLikedPost_it;
        MostLikedPost_it = it;

        for(++it;it<end;it++){

            if((*it).Get_nLikes() > (*MostLikedPost_it).Get_nLikes())
                MostLikedPost_it = it;

        }

        return MostLikedPost_it;
    }

    vector<Post>::iterator Most_Disliked_Post(vector<Post>::iterator it,vector<Post>::iterator end) {

            vector<Post>::iterator MostDislikedPost_it;
            MostDislikedPost_it = it;

            for(++it;it<end;it++){

                if((*it).Get_nDislikes() > (*MostDislikedPost_it).Get_nDislikes())
                    MostDislikedPost_it = it;

            }

            return MostDislikedPost_it;







        }

    vector<Simple_User>::iterator User_with_more_friends(vector<Simple_User>::iterator it,vector<Simple_User>::iterator end){

            int maxFriends = 0,temp;
            vector<Simple_User>::iterator it_max;

            for(it;it<end;it++){

                temp = (*it).Get_nFriends();

                if(temp >= maxFriends) {

                    maxFriends = temp;

                    it_max = it;
                }
            }

            return it_max;
        }

    vector<Simple_User>::iterator User_with_more_acquaintances(vector<Simple_User>::iterator it,vector<Simple_User>::iterator end){

            int maxAcquaintance = 0,temp;
            vector<Simple_User>::iterator it_max;

            for(it;it<end;it++){
                temp = (*it).Get_nAcquaintances();
                if(temp >= maxAcquaintance) {

                    maxAcquaintance = temp;

                    it_max = it;


                }



            }



    return it_max;


        }

    float Average_Users_Age(vector<Simple_User>::iterator it,vector<Simple_User>::iterator end) {
            int cont = 0;
            float sum = 0;

            for(it;it<end;it++){

              sum += (*it).Get_Age();
              cont++;


            }

            return sum/cont;

        }

    int nBorn_After_Date(Date refDate, vector<Simple_User>::iterator it, vector<Simple_User>::iterator end){
            int cont = 0;

            for(it;it<end;it++){

                if((*it).Get_BirthDate()>refDate)
                    cont++;


            }

            return cont;
        }

    void Sorting_Companies_by_Likes(vector<Company>::iterator Cit,vector<Company>::iterator Cend){

        vector<Company>::iterator Cjt,pos_max;

        for(Cit;Cit<Cend;Cit++){

            pos_max = Cit;

            for(Cjt = Cit;Cjt<Cend;Cjt++){

                if((*Cjt).Get_Feedback() > (*pos_max).Get_Feedback())
                    pos_max = Cjt;

            }

            Company tempC;

            tempC = *pos_max;
            *pos_max = *Cit;
            *Cit = tempC;


        }


    }

    int Find_Genealogy(vector<Simple_User> &U,vector<string> &Parents_id,int size,vector<Ancestors> &Sons,int &cont){
        string Last;
        vector<Simple_User>::iterator find;
        vector<string> temp_S;
        Ancestors tempAncestor;
        string P1,P2;
        if (size == 1 && cont == 0){ //sono al I giro

            tempAncestor.Set_id(*Parents_id.begin());
            tempAncestor.Set_Gnt_level(cont+1);
            Sons.push_back(tempAncestor);
            Search_Profile(*Parents_id.begin(),U.begin(),U.end(),find); //cerco oggetto utente corrispondente all'ID
            (*find).Parents(P1,P2);
            if(P1 != "") {                          //ho trovato il I genitore
                temp_S.push_back(P1);               //aggiungo l'ID di P1 dentro il temporaneo
                tempAncestor.Set_id(P1);
                tempAncestor.Set_Gnt_level(cont+2);
                Sons.push_back(tempAncestor);
            }

            if(P2 != "") {                         //ho trovato il II genitore
                temp_S.push_back(P2);              //aggiungo l'ID di P2 dentro il temporaneo
                tempAncestor.Set_id(P2);
                tempAncestor.Set_Gnt_level(cont+2);
                Sons.push_back(tempAncestor);
            }

            cont++;
        }
        else {
            vector<string>::iterator it;
            for(it = Parents_id.begin();it<Parents_id.end();it++){

                Search_Profile(*it,U.begin(),U.end(),find); //passo dalla stringa ID all'oggetto Simple_User relativo
                (*find).Parents(P1,P2);
                if(P1 != "") {
                    temp_S.push_back(P1);
                    tempAncestor.Set_id(P1);
                    tempAncestor.Set_Gnt_level(cont+2);
                    Sons.push_back(tempAncestor);

                }

                if(P2 != "") {
                    temp_S.push_back(P2);
                    tempAncestor.Set_id(P2);
                    tempAncestor.Set_Gnt_level(cont+2);
                    Sons.push_back(tempAncestor);

                }


            }

            cont++;
        }





        if(temp_S.size()>0) {
            Parents_id.clear();
            Parents_id = temp_S; //copio il temporaneo dentro Parents_id
            temp_S.clear();
            Find_Genealogy(U, Parents_id, Parents_id.size(),Sons,cont);
        }
        else{ //prima di uscire dalla funzione dealloco i vettori dinamici

            Parents_id.clear();
            temp_S.clear();


        }


        return cont;              //se cont >1 sarà possibile creare l'albero, altrimenti no
    }

    string Build_Albero(vector<Simple_User> &users,vector<Ancestors> &Sons,int cont) {

        string buffer = "";
        string Albero = "";
        int initial_spaces = 0;
        int n_people_first_row = 0;
        int i;
        vector<int> spaces_between_parents;
        vector<int> spaces_between_couples;
        vector<int> temp_spaces_between_parents;
        vector<int> temp_spaces_between_couples;
        vector<int> temp_ID_lenghts;
        vector<int> ID_lenghts;


        for(vector<Ancestors>::iterator it = (Sons.end() - 1); it >= Sons.begin() && (*it).Get_Gnt_level() == cont; it--){ //stampa della I riga

        if((*it).Get_Gnt_level() == cont) {
            n_people_first_row++;
            ID_lenghts.push_back((int)(*it).Get_id().size());
        }
            if(it>=Sons.begin()+1){

                string id1 = (*it).Get_id(), id2 = (*(it-1)).Get_id();
                if(Has_Common_Child(id1,id2,users) && ((*it).Get_Gnt_level() == (*(it-1)).Get_Gnt_level())){

                    Albero += id1 + "                  " + id2 + "                              ";
                    n_people_first_row++;
                    ID_lenghts.push_back((int)id2.size());

                    it--;


                }
                else{

                    Albero += id1 + "                  ????                              ";
                    ID_lenghts.push_back(4);




                }

            }

        }

        Albero += "\n\n\n\n\n";

        int n_max_people_row = (int)pow(2,cont-1);
        for(i = 0; i < n_max_people_row-1;i++){         //Salvo numero di caratteri su cui calcolare gli sapzi della II riga in poi successiva

            if(i%2==0)
                spaces_between_parents.push_back(18);
            else spaces_between_couples.push_back(30);


        }



        vector<int>::iterator it_spaces_between_parents = spaces_between_parents.begin();
        vector<int>::iterator it_spaces_between_couples = spaces_between_couples.begin();
        vector<int>::iterator it_ID_lenghts = ID_lenghts.begin();
        cont--;
        int n_giro = 0;

        while(cont > 0) {
            int actual_value = cont;
            bool first_of_the_row = true;

            for (vector<Ancestors>::iterator it = (Sons.end() - 1 - n_people_first_row); it >= Sons.begin() && (*it).Get_Gnt_level() == actual_value; it--) {

                if(first_of_the_row){

                    initial_spaces += *it_ID_lenghts + *it_spaces_between_parents/2 - ((*it).Get_id()).size()/2;
                    for(i = 0;i < initial_spaces;i++){
                        Albero += " ";

                    }

                    Albero += (*it).Get_id();
                    temp_ID_lenghts.push_back((int)(*it).Get_id().size());
                    if(it_spaces_between_parents < (spaces_between_parents.end()-1))
                        it_spaces_between_parents++;
                    if(it_ID_lenghts < (ID_lenghts.end()-1))
                        it_ID_lenghts++;

                    n_people_first_row++;

                    first_of_the_row = false;
                }
                    else{
                    int value = (*it_spaces_between_parents-((*it).Get_id()).size())/2 + *(it_ID_lenghts+1) + *it_spaces_between_couples + (*(it_spaces_between_parents+1))/2 - ((*it).Get_id()).size()/2;
                    for(i = 0; i < value;i++){

                        Albero += " ";
                    }

                    if(n_giro%2 == 0)
                        temp_spaces_between_parents.push_back(i);
                    else temp_spaces_between_couples.push_back(i);


                    Albero += (*it).Get_id();
                    temp_ID_lenghts.push_back((int)((*it).Get_id()).size());
                    n_people_first_row++;
                    if(it_spaces_between_parents < (spaces_between_parents.end()-1))
                    it_spaces_between_parents++;
                    if(it_spaces_between_couples < (spaces_between_couples.end()-1))
                    it_spaces_between_couples++;
                    if(it_ID_lenghts < (ID_lenghts.end()-1))
                    it_ID_lenghts++;

                }

                if((*(it-1)).Get_Gnt_level() != actual_value){
                    Albero += "\n\n\n\n\n";
                    cont--;                                    //perchè cambio riga

                    //preparo i vettori per il calcolo degli spazi per la prossima riga
                    spaces_between_couples.clear();
                    spaces_between_couples = temp_spaces_between_couples;
                    temp_spaces_between_couples.clear();
                    spaces_between_parents.clear();
                    spaces_between_parents = temp_spaces_between_parents;
                    temp_spaces_between_parents.clear();
                    ID_lenghts.clear();
                    ID_lenghts = temp_ID_lenghts;
                    temp_ID_lenghts.clear();
                    it_spaces_between_parents = spaces_between_parents.begin();
                    it_spaces_between_couples = spaces_between_couples.begin();
                    it_ID_lenghts = ID_lenghts.begin();


                }

                    n_giro++;
            }

        }


        return Albero;

    }

    int Count_Family_Member(vector<Simple_User>::iterator &Uit,vector<Simple_User> &users) {

        vector<string> Parents_id;
        vector<Ancestors> Sons;
        vector<string> to_Size;
        vector<string> buffer;
        vector<string> temp_S;
        vector<Simple_User>::iterator find;
        int cont,n = 0;
        bool doesnt_appear = true;
        Inizializer(Parents_id,Sons,cont);
        Parents_id.push_back((*Uit).Get_ID());
        Find_Genealogy(users,Parents_id,Parents_id.size(),Sons,cont);
        auto i = Sons.end()-1;

        while(i>= Sons.begin() &&(*i).Get_Gnt_level() == cont){

            buffer.push_back((*i).Get_id());
            i--;
        }
        for(auto j = Sons.begin(); j < Sons.end();j++){
            to_Size.push_back((*j).Get_id());
        }


        Sons.clear();
        Parents_id.clear();

        while(buffer.begin() != buffer.end()){ //finchè il buffer non è vuoto

            for(vector<string>::iterator it = buffer.begin(); it < buffer.end(); it++){

                Search_Profile(*it,users.begin(),users.end(),find);
                vector<string> temp_Children = (*find).Get_Children();

                for(vector<string>::iterator jt = temp_Children.begin(); jt < temp_Children.end(); jt++){

                    temp_S.push_back(*jt);

                    for(vector<string>::iterator kt = to_Size.begin(); kt < to_Size.end(); kt++){

                        if(*jt == *kt)
                            doesnt_appear = false;


                    }

                    if(doesnt_appear) {
                        to_Size.push_back(*jt);

                    }

                }

                temp_Children.clear();

            }

            buffer.clear();
            buffer = temp_S;
            temp_S.clear();

        }


        n += to_Size.size() -1;

        return n;
    }

    bool LoneWolf(vector<Simple_User>::iterator it,vector<Simple_User>::iterator end,int min_relations,int min_posts,int min_reactions,float feedback_rapport,vector<int> &positions){
    int pos = 0;
    bool ans = false;

        for(it; it < end; it++){

         if((*it).Get_nRelations() < min_relations && (*it).Get_nPosts() < min_posts && (*it).Get_TotGivedReactions() < min_reactions && !(*it).Has_a_Job() && !(*it).Member_of_a_Group() && (*it).Get_Feedback() < feedback_rapport){

                    positions.push_back(pos);
                    ans = true;

                }

            pos++;


        }

        return ans;
    }


    #endif //PROGETTO_INFORMATICA_V1_ANALYTICS_H
