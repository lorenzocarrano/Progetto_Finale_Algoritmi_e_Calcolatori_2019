    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <cmath>
    #include "Profile.h"
    #include "Post.h"
    #include "Basic_Features.h"
    #include "Analytics.h"
    #include "Ancestors.h" //

    string Create_String_Error(string&);
    void Load_Ascii(vector<char> &Unwanted,int except_from = -1, int to = -1);
    using namespace std;

    int main(int argc, char *argv[]) {


        string Searched_id;
        char profile_tipe;
        vector<Simple_User> users;
        vector<Company> companies;
        vector<Group> groups;
        vector<Post> posts;
        ifstream p;
        ofstream p1;
        string fileNames[argc-1];
        string bestPost,worstPost,ID_bestPost,ID_worstPost;
        bool errors[argc-1];


        for (int i = 1; i < argc; i++) {    //Vettorizzo i nomi dei file

            fileNames[i - 1] = argv[i];

        }


        if(!Files_Check(fileNames,argc-1,errors)) {

            for (int i = 0; i < argc - 1; i++) {

                    if(!errors[i])

                        cerr<<"An issue was occurred opening File " + to_string(i + 1) + ": " + argv[i+1] + " was not found"<<endl;
         }


            return -1;
        }
        else {

            string error;

            if(!Read_Files(p,fileNames,argc-1,users,companies,groups,posts,error)){

                ///cerr<<error;
                cerr<<Create_String_Error(error);
                return -1;

            }


            else { //Da qui in poi tutti i vettori sono inizializzati e i dati controllati


                cout << "All Files where Correctly Opened and File Formatting is fine. Data Structures are been inizialized" << endl
                        << "Press H for Help" << endl;

                vector<char> Unwanted;   //Vettore dei caratteri 'proibiti'
                Unwanted.push_back(',');

                bool end = false;
                bool F1 = false,F2 = false, F3 = false; ///Booleane che mi dicono se il File 1,2 o 3 Necessita Aggiornamento
                string action,ans;
                int dd = 1,mm = 1,yyyy = 1900;
                Date date(dd,mm,yyyy);

                string ID,FindTipe,message;
                vector<Simple_User>::iterator Ufind;
                vector<Company>::iterator Cfind;
                vector<Group>::iterator Gfind;
                vector<string> Parents_ID;
                vector<Ancestors> Sons;
                vector<int> position;      ///Utile per interagire con elementi indicizzati a schermo filtrati dal database totale
                string riga_Albero;
                int cont,min_rel,min_reac,min_posts;
                float feedback_rapport;


                while (!end) {


                    cout << endl << "Enter Action:" << endl;
                    cin >> action;
                    if((action).size()>1){
                        cout<<"Only a Char, not Strings :-)"<<endl;
                        action[0] = '_';

                    }
                    switch (action[0]) {

                        case 'N':
                            cout << "New User:" << endl;
                            cout
                                    << "type S to create a  Simple User profile, C for a Company Profile, G for a Group Profile."
                                    << endl;
                            cin >> profile_tipe;

                            if (profile_tipe == 'S') {


                                string name, surname, address, activity, gender;
                                int ddB, mmB, yyyyB;
                                bool check = false, available = false;
                                cout
                                        << "Informations that are contrassigned with a * are obligatorie, you can't let them blank. USE UNDERSCORES INSTEAD OF SPACES."
                                        << endl;
                                while (!check) {
                                    cout << endl << "Name*: ";
                                    cin >> name;
                                    if (name != " " && No_Unwanted_Chars(name, Unwanted))
                                        check = true;
                                }
                                check = false;
                                while (!check) {
                                    cout << endl << "Surname*: ";
                                    cin >> surname;
                                    if (surname != " " && No_Unwanted_Chars(surname, Unwanted))
                                        check = true;
                                }
                                check = false;
                                while (!check || !available) {

                                    cout << endl << "Chose an Username (ID)*: ";
                                    cin >> ID;
                                    if (ID != " " && No_Unwanted_Chars(ID, Unwanted)) {
                                        check = true;
                                    }

                                    available = !Profile_Exists(ID, users.begin(), users.end(), companies.begin(),
                                                                companies.end(), groups.begin(), groups.end());
                                    if (!check)
                                        cerr << "You can't let this parameter blank" << endl;
                                    if (!available)
                                        cerr << "ID in use for another profile, Please Choose another one" << endl;


                                }

                                check = false;
                                while (!check) {

                                    cout << endl << "Address: ";
                                    cin >> address;

                                    if (No_Unwanted_Chars(address, Unwanted))
                                        check = true;
                                    else {
                                        cerr << endl << "Don't use ',' ";
                                    }
                                }

                                check = false;
                                while (!check) {
                                    cout << endl << "Job: ";
                                    cin >> activity;
                                    if (No_Unwanted_Chars(activity, Unwanted))
                                        check = true;
                                    else cerr << endl << "Don't use ','";

                                }

                                check = false;

                                Date bDate(01, 01, 1900);
                                Unwanted.clear();
                                Load_Ascii(Unwanted, 47, 57);
                                while (!check) {
                                    cout << endl << "Brith Date: (type as: dd/mm/yyyy)" << endl;
                                    string temp;
                                    cin >> temp;

                                    if (No_Unwanted_Chars(temp, Unwanted)) {

                                        bDate.SetDate(temp);
                                        check = bDate.Date_Check();

                                    }


                                    if (!check) {
                                        cerr << "Invalid Date: Tipe one in a correct format" << endl;
                                    }

                                }

                                check = false;
                                Unwanted.clear();
                                Unwanted.push_back(',');


                                while (!check) {
                                    cout << endl << "Gender*: Digit 'M' for Male, 'F' for Female: ";
                                    cin >> gender;
                                    if (gender == "M") {
                                        gender = "Male";
                                        check = true;
                                    } else if (gender == "F") {
                                        gender = "Female";
                                        check = true;
                                    }
                                }

                                Simple_User tempUser(name, surname, ID, address, activity, bDate, gender);
                                printonfile(tempUser.InformationsStream(), argv[1]);
                                users.push_back(tempUser);


                            }
                            if (profile_tipe == 'C') {
                                string name, address1, address2, activity;
                                bool check = false, available = false;
                                cout
                                        << "Informations that are contrassigned with a * are obligatorie, you can let them blank"
                                        << endl;
                                while (!check) {
                                    cout << endl << "Name*: ";
                                    cin >> name;
                                    if (name != " " && No_Unwanted_Chars(name, Unwanted))
                                        check = true;
                                }
                                check = false;

                                while (!check || !available) {

                                    cout << "Chose an Username (ID)*: ";
                                    cin >> ID;
                                    if (ID != " " && No_Unwanted_Chars(ID, Unwanted)) {
                                        check = true;
                                    }

                                    available = !Profile_Exists(ID, users.begin(), users.end(), companies.begin(),
                                                                companies.end(), groups.begin(), groups.end());
                                    if (!check)
                                        cerr << "You can't let this parameter blank" << endl;
                                    if (!available)
                                        cerr << "ID in use for another profile, Please Choose another one" << endl;


                                }
                                check = false;

                                while (!check) {

                                    cout << endl << "Legal Address*: ";
                                    cin >> address1;
                                    if (address1 != " " && No_Unwanted_Chars(address1, Unwanted)) {
                                        check = true;
                                    }
                                }
                                check = false;
                                while (!check) {

                                    cout << endl << "Amministrative Address*: ";
                                    cin >> address2;
                                    if (address2 != " " && No_Unwanted_Chars(address2, Unwanted)) {
                                        check = true;
                                    }
                                }
                                check = false;

                                while (!check) {

                                    cout << endl << "Activity/Products Tipe*: ";
                                    cin >> activity;
                                    if (activity != " " && No_Unwanted_Chars(activity, Unwanted)) {
                                        check = true;
                                    }
                                }

                                Company tempCompany(name, ID, address1, address2, activity);
                                printonfile(tempCompany.InformationsStream(), argv[1]);
                                companies.push_back(tempCompany);


                            }
                            if (profile_tipe == 'G') {

                                string name, address, activity;
                                bool check = false, available;
                                cout
                                        << "Informations that are contrassigned with a * are obligatorie, you can let them blank"
                                        << endl;
                                while (!check) {
                                    cout << endl << "Name*: ";
                                    cin >> name;
                                    if (name != " " && No_Unwanted_Chars(name, Unwanted))
                                        check = true;
                                }

                                check = false;
                                while (!check || !available) {

                                    cout << "Chose an Username (ID)*: ";
                                    cin >> ID;
                                    if (ID != " " && No_Unwanted_Chars(ID, Unwanted)) {
                                        check = true;
                                    }

                                    available = !Profile_Exists(ID, users.begin(), users.end(), companies.begin(),
                                                                companies.end(), groups.begin(), groups.end());
                                    if (!check)
                                        cerr << "You can't let this parameter blank" << endl;
                                    if (!available)
                                        cerr << "ID in use for another profile, Please Choose another one" << endl;


                                }

                                check = false;
                                available = false;
                                cout << endl << "Address: ";
                                cin >> address;
                                while (!check) {
                                    cout << endl << "Activity/Group Topics*: " << endl;
                                    cin >> activity;

                                    if (activity != " " && No_Unwanted_Chars(activity, Unwanted)) {
                                        check = true;
                                    }
                                }
                                check = false;

                                Group tempGroup(name, ID, address, activity);
                                printonfile(tempGroup.InformationsStream(), argv[1]);
                                groups.push_back(tempGroup);


                            }


                            break;
                        case 'D':

                            cout << "Display: " << endl;

                            cout << "Simple Users Profiles: " << users.size() << ", Company Profiles: "
                                 << companies.size()
                                 << ", Group Profiles: " << groups.size() << ", Total Profiles: " <<

                                 users.size() + companies.size() + groups.size();
                            if (users.size() > 0) {
                                cout << endl << endl << endl << "Simple Users:" << endl << endl;

                                vector<Simple_User>::iterator beg = users.begin(), _end = users.end();
                                Display_Profile(beg, _end);

                            }
                            if (companies.size() > 0) {
                                cout << endl << endl << "Companies:" << endl << endl;

                                vector<Company>::iterator beg = companies.begin(), _end = companies.end();
                                Display_Profile(beg, _end);

                            }

                            if (groups.size() > 0) {
                                cout << endl << endl << "Groups:" << endl << endl;

                                vector<Group>::iterator beg = groups.begin(), _end = groups.end();
                                Display_Profile(beg, _end);

                            }

                            break;

                        case 'S':

                            Sorting_Companies_by_Likes(companies.begin(), companies.end());
                            cout
                                    << "Sorted Companies by Feedback (Likes/Dislikes on posts. Do you want to visualize it on screen?"
                                    << endl << "Y or N: ";
                            cin >> ans;
                            cout << endl << endl;
                            switch (ans[0]) {
                                case 'Y':

                                    for (vector<Company>::iterator it = companies.begin(); it < companies.end(); it++) {

                                        cout << endl << (*it).InformationsStream() << " Likes/Dislikes: "
                                             << (*it).Get_Feedback();


                                    }


                                    break;
                                case 'N':
                                    break;
                                default:
                                    break;
                            }

                            File_Informations_Update(argv[1], argv[2], argv[3], true, false, false, users.begin(),
                                                     users.end(), companies.begin(), companies.end(), groups.begin(),
                                                     groups.end(), posts.begin(), posts.end());
                            //ossia riordino anche nel file le companies.

                            break;


                        case 'W':
                            cout << "Lone Wolf:" << endl
                                 << "Set the Parameters to define a Lone Wolf inside users in the format: <min_relations> <min_posts> <min_reactions> <feedback_rapport>: "
                                 << endl
                                 << "Note: feedback_rapport has to be values >= 0 and <= 1:"
                                 << endl;

                            cin >> min_rel >> min_posts >> min_reac >> feedback_rapport;

                            if(min_rel >= 0 || min_posts >= 0 || min_reac >=0 || feedback_rapport <= 1 || feedback_rapport >= 0){

                            if (position.begin() != position.end())
                                position.clear();

                            if (LoneWolf(users.begin(), users.end(), min_rel, min_posts, min_reac, feedback_rapport,
                                         position)) {
                                int i = 0;
                                cout << "Lone Wolves inside the Database: ";
                                vector<Simple_User>::iterator Uit;
                                for (vector<int>::iterator it = position.begin(); it < position.end(); it++, i++) {

                                    Uit = users.begin() + (*it);
                                    cout << endl << i << "." << " " << (*Uit).InformationsStream() << " feedback: "
                                         << (*Uit).Get_Feedback();
                                    if ((*Uit).Get_nRelations() == 0 && (*Uit).Get_nPosts() == 0 &&
                                        (*Uit).Get_TotGivedReactions() == 0)
                                        cout << "   --->Empty Profile";

                                }


                            }
                            else cout << endl << "No Lone Wolves were found with the specified parameters" << endl;
                        }
                            else{
                                cerr << endl << "Invalid Parameters --> Exit Function" << endl;
                            }



                            break;

                        case 'M':

                            cout << "Modify Profile: " << endl << "write the ID  that you want modify: ";

                            cin >> ID;

                            if (Search_ID(ID, users.begin(), users.end(), companies.begin(), companies.end(),
                                          groups.begin(), groups.end(), Ufind, Cfind, Gfind, FindTipe)) {

                                if (FindTipe == "Simple_User") {

                                    bool check = false, Editing_isDone = false;
                                    char parameter;
                                    string temp, name, surname, address, job, gender, RelationTipe;
                                    vector<Simple_User>::iterator Ufind_t;
                                    Date bDate;
                                    while (!Editing_isDone) {

                                        Unwanted.clear();
                                        Unwanted.push_back(',');
                                        cout << "What do you wanto to modify? " << endl << "type:   to modify:" << endl;
                                        cout << "'n'     Name" << endl << "'s'     Surname" << endl << "'a'     Address"
                                             << endl << "'j'     Job" << endl << "'g'     Gender" << endl
                                             << "A to add a new relation" << endl <<"'F'     Start to follow someone" << endl
                                             << "'G'     Enter in a new group" << endl
                                             << "'R     to remove a relation / remove a Company as job / exit from a group";
                                        cout << endl << "Tipe 'e' to exit this function" << endl;
                                        cin >> parameter;

                                        switch (parameter) {

                                            case 'n':
                                                cout << "Type a new Name: ";

                                                while(!check) {
                                                    cin >> temp;
                                                    if (temp != " " && No_Unwanted_Chars(temp, Unwanted))
                                                       check = true;
                                                    else cerr << "Type a valid parameter. Don't use ','";
                                                }
                                                (*Ufind).Set_Name(temp);
                                                F1 = true;
                                                check = false;
                                                break;
                                            case 's':
                                                cout << "Type a new Surname: ";

                                                while(!check) {
                                                    cin >> temp;
                                                    if (temp != " " && No_Unwanted_Chars(temp, Unwanted))
                                                        check = true;
                                                    else cerr << "Type a valid parameter. Don't use ','";
                                                }

                                                (*Ufind).Set_Surname(temp);
                                                F1 = true;
                                                check = false;
                                                break;
                                            case 'a':
                                                cout << "Type a new Address: ";

                                                while(!check) {
                                                    cin >> temp;
                                                    if (temp != " " && No_Unwanted_Chars(temp, Unwanted))
                                                        check = true;
                                                    else cerr << "Type a valid parameter. Don't use ','";
                                                }
                                                (*Ufind).Set_Address(temp);
                                                F1 = true;
                                                check = false;
                                                break;
                                            case 'j':
                                                cout << "Type a new Job: ";
                                                while(!check) {
                                                    cin >> temp;
                                                    if (temp != " " && No_Unwanted_Chars(temp, Unwanted))
                                                        check = true;
                                                    else cerr << "Type a valid parameter. Don't use ','";
                                                }
                                                (*Ufind).Set_Activity(temp);
                                                cout << endl << "Want to set the Company where you work? (Y or N): ";
                                                cin >> ans;
                                                if (ans[0] == 'Y') {

                                                    cout << endl << "Company id: ";
                                                    cin >> ID;

                                                    if (Search_Profile(ID, companies.begin(), companies.end(), Cfind)) {
                                                        (*Ufind).Set_Company_Work(ID);
                                                        string new_empl_ID = (*Ufind).Get_ID();
                                                        (*Cfind).New_Employee(new_empl_ID);
                                                    } else cout << endl << "This Company ID does not exist." << endl;
                                                }


                                                F1 = true;
                                                F2 = true;
                                                check = false;
                                                break;
                                            case 'g':

                                                gender = ((*Ufind).Get_Gender() == "Male") ? "Female" : "Male";

                                                (*Ufind).Set_Gender(gender);
                                                F1 = true;

                                                break;

                                            case 'b':    ///Modifica della data di nascita
                                                check = false;
                                                Unwanted.clear();
                                                Load_Ascii(Unwanted,47,57);
                                                cout << "Type a new BirthDate in the format: dd/mm/yyyy: ";
                                                while (!check) {

                                                    cin >> temp;
                                                    if (No_Unwanted_Chars(temp, Unwanted)){

                                                            bDate.SetDate(dd, mm, yyyy);

                                                             if (bDate.Date_Check()) {

                                                                 check = true;

                                                                         }
                                                         }
                                                     if(!check)
                                                         cerr << endl << "Invalid Date: please tipe another one." << endl;
                                                }
                                                (*Ufind).Set_Birth_Date(bDate);
                                                Unwanted.clear();
                                                Unwanted.push_back(',');
                                                check = false;
                                                F1 = true;

                                                break;
                                            case 'A':

                                                while (!check) {
                                                    cout
                                                            << "Type an ID where add the relation and a Relation Tipe in the format: ID RelationTipe "
                                                            << endl;
                                                    cin >> ID >> RelationTipe;


                                                    if (Search_Profile(ID, users.begin(), users.end(), Ufind_t) && Relation_isValid(RelationTipe)) {

                                                        check = true;

                                                        if (RelationTipe == "Parent" && (*Ufind).Get_nParents() > 1) {

                                                            cerr << "This User already has two parents setted" << endl;
                                                            break;


                                                        } else {

                                                            (*Ufind).Add_Relation(ID, RelationTipe);
                                                            (*Ufind_t).Add_Relation((*Ufind).Get_ID(),
                                                                                    Relation_Converter(RelationTipe));


                                                        }
                                                    } else {
                                                        cerr
                                                                << "No corresponding ID / Invalid Relation Tipe, exit function..."
                                                                << endl;
                                                        break;
                                                    }


                                                }
                                                check = false;

                                                F2 = true;

                                                break;


                                            case 'G':

                                                cout << "Type a group ID: ";
                                                cin >> temp;

                                                if (Search_Profile(temp, groups.begin(), groups.end(), Gfind)) {

                                                    if ((*Ufind).New_Group(temp) && (*Gfind).New_Member(ID)) {

                                                        cout << endl << "done." << endl;
                                                        F2 = true;
                                                    } else
                                                        cerr << endl << "This user was already a member of this group"
                                                             << endl;

                                                } else cout << endl << "This Group does not exist." << endl;


                                                break;

                                            case 'F':

                                                cout << "User's ID to follow: "<<endl;
                                                cin >>temp;
                                                if(Search_Profile(temp,users.begin(),users.end(),Ufind_t)){

                                                    (*Ufind).Add_Relation(temp,"Followed");
                                                    (*Ufind_t).Add_Relation((*Ufind).Get_ID(),"Follower");
                                                    F2 = true;

                                                }
                                                else cerr << "Not existing ID --> Exit Function"<<endl;

                                                break;

                                            case 'R':

                                                cout << "ID to remove: ";
                                                cin >> temp;
                                                Ufind_t = Ufind;


                                                if (Search_ID(temp, users.begin(), users.end(), companies.begin(),
                                                              companies.end(), groups.begin(), groups.end(), Ufind, Cfind,
                                                              Gfind, FindTipe)) {


                                                    if (FindTipe == "Simple_User") {
                                                       vector<string> Relation_with = (*Ufind_t).Get_Relation_with(temp);
                                                        if (Relation_with.size() == 1) {
                                                            (*Ufind_t).Remove_Relation(temp);
                                                            temp = (*Ufind_t).Get_ID();
                                                            (*Ufind).Remove_Relation(temp);
                                                            cout << endl << "done." << endl;
                                                            F2 = true;
                                                        }
                                                        else if(Relation_with.size()>1){

                                                            cout << "What Relation do you want to remove?";
                                                            int ind = 0;
                                                            for(auto it = Relation_with.begin(); it < Relation_with.end(); it++,ind++){

                                                                cout<<endl<<ind<<") "<<*it;

                                                            }
                                                            cin >> ind;
                                                            if(ind >= 0 && ind <= Relation_with.size()-1){

                                                                (*Ufind_t).Remove_Relation(temp,(*(Relation_with.begin()+ind)));
                                                                temp = (*Ufind_t).Get_ID();
                                                                (*Ufind).Remove_Relation(temp,Relation_Converter((*(Relation_with.begin()+ind))));
                                                                cout << endl << "done." << endl;
                                                                F2 = true;

                                                            }

                                                            else cerr<< endl << "Invalid Option --> Exit Function"<< endl;

                                                        }

                                                        else if(Relation_with.size() == 0) {
                                                            cerr
                                                                    << "These users have not any relation: process was not completed";
                                                        }

                                                    } else if (FindTipe == "Company") {
                                                        if ((*Ufind).Remove_Relation(temp)) {
                                                            temp = (*Ufind_t).Get_ID();
                                                            (*Cfind).Remove_Employee(temp);
                                                            cout << endl << "done." << endl;
                                                            F2 = true;
                                                        } else
                                                            cerr << endl << (*Ufind).Get_ID()
                                                                 << " was not an employee of " << temp
                                                                 << ": process was not completed." << endl;

                                                    } else if (FindTipe == "Group") {
                                                        if ((*Ufind).Remove_Relation(temp)) {
                                                            temp = (*Ufind_t).Get_ID();
                                                            (*Gfind).Remove_Relation(temp);
                                                            cout << endl << "done." << endl;
                                                            F2 = true;
                                                        } else
                                                            cerr << endl << "This user is not a member of "
                                                                 << (*Gfind).Get_ID()
                                                                 << " group: process was not completed." << endl;
                                                    }
                                                } else cout << endl << "This ID does not exist." << endl;
                                                break;

                                            case 'e':
                                                Editing_isDone = true;
                                                break;

                                            default:
                                                break;

                                        }


                                    }


                                }
                                else if (FindTipe == "Company") {

                                    bool Editing_isDone = false, check = false;
                                    char parameter;
                                    string temp, name, address1, address2, job, gender;
                                    vector<Company>::iterator company_Address_Backup = Cfind;
                                    while (!Editing_isDone) {

                                        cout << "What do you wanto to modify? " << endl << "type:   to modify:" << endl;
                                        cout << "'n'     Name" << endl << "'a'     Address" << endl
                                             << "'j'     Activity/Products" << endl << "'A'     Add a Consociated Company"
                                             << endl << "'R'     to remove an employee/consociated company" << endl;
                                        cout << "Tipe 'e' to exit this function" << endl;
                                        cin >> parameter;

                                        switch (parameter) {

                                            case 'n':
                                                cout << "Type a new Name: ";
                                                while(!check) {
                                                    cin >> temp;
                                                    if (temp != " " && No_Unwanted_Chars(temp, Unwanted))
                                                        check = true;
                                                    else cerr << "Type a valid parameter. Don't use ','";
                                                }
                                                (*Cfind).Set_Name(temp);
                                                F1 = true;
                                                check = false;
                                                break;

                                            case 'a':
                                                cout << "Type a new Address in the format 'Legal_Address Amministrative_Address': ";

                                                while(!check) {
                                                    cin >> temp;
                                                    if (temp != " " && No_Unwanted_Chars(temp, Unwanted))
                                                        check = true;
                                                    else cerr << "Type a valid parameter. Don't use ','";
                                                }
                                                (*Cfind).Set_Address(address1, address2);
                                                F1 = true;
                                                check = false;
                                                break;


                                            case 'j':
                                                cout << "Type a new activity: ";
                                                while(!check) {
                                                    cin >> temp;
                                                    if (temp != " " && No_Unwanted_Chars(temp, Unwanted))
                                                        check = true;
                                                    else cerr << "Type a valid parameter. Don't use ','";
                                                }
                                                (*Cfind).Set_Activity(temp);
                                                F1 = true;
                                                F2 = true;
                                                check = false;
                                                break;
                                            case 'N':
                                                cout << "New Employee ID: ";
                                                cin >> ID;
                                                if (Search_Profile(ID, users.begin(), users.end(), Ufind)) {

                                                    if ((*company_Address_Backup).New_Employee(ID)) {

                                                        string new_Company_id = (*company_Address_Backup).Get_ID();
                                                        (*Ufind).Set_Company_Work(new_Company_id);

                                                    } else
                                                        cerr << endl << "This user is already an employee of "
                                                             << (*company_Address_Backup).Get_ID() << " company" << endl;
                                                }

                                                F2 = true;
                                                F1 = true;

                                                break;

                                            case 'A':

                                                cout << "Write the consociated company ID: ";
                                                cin >> temp;

                                                if (Search_Profile(temp, companies.begin(), companies.end(), Cfind)) {
                                                    F2 = true;
                                                    if ((*company_Address_Backup).Add_Consociated_Company(temp) &&
                                                        (*Cfind).Add_Consociated_Company(ID))
                                                        cout << endl << "done." << endl;
                                                    else
                                                        cerr
                                                                << "These companies are already consociated, process was not completed."
                                                                << endl;


                                                } else cout << "Invalid ID." << endl;


                                                break;

                                            case 'R':

                                                cout << "ID to remove: ";
                                                cin >> temp;
                                                if (Search_ID(temp, users.begin(), users.end(), companies.begin(),
                                                              companies.end(), groups.begin(), groups.end(), Ufind, Cfind,
                                                              Gfind, FindTipe)) {
                                                    if (FindTipe == "Simple_User") {

                                                        (*company_Address_Backup).Remove_Employee(temp);
                                                        (*Ufind).Remove_Relation(ID);
                                                        F2 = true;
                                                    }
                                                    if (FindTipe == "Company") {
                                                        if ((*company_Address_Backup).Remove_Consociated(temp) &&
                                                            (*Cfind).Remove_Consociated(ID)) {
                                                            F2 = true;
                                                            cout << endl << "done." << endl;

                                                        } else
                                                            cerr
                                                                    << "These companies were not consociated: process was not completed."
                                                                    << endl;
                                                    }
                                                    if (FindTipe == "Group") {
                                                        cout << "Error: this ID is correlated with a group";
                                                        break;
                                                    }
                                                } else cout << endl << "This ID does not exist." << endl;

                                                break;

                                            case 'e':
                                                Editing_isDone = true;
                                                break;


                                            default:
                                                break;


                                        }


                                    }

                                }
                                else if (FindTipe == "Group") {
                                    F1 = true;
                                    bool Editing_isDone = false, check = false;
                                    char parameter;
                                    string temp, name, topic;
                                    while (!Editing_isDone) {

                                        cout << "What do you wanto to modify? " << endl << "type:   to modify:" << endl;
                                        cout << "'n'     Name" << endl << "'a'     Address" << endl << "'t'     Topic"
                                             << endl << "'R'     Remove Member" << endl;
                                        cout << "Tipe 'e' to exit this function" << endl;
                                        cin >> parameter;
                                        vector<Group>::iterator G_address_backup = Gfind;
                                        switch (parameter) {

                                            case 'n':
                                                cout << "Type a new Name: ";
                                                while(!check) {
                                                    cin >> temp;
                                                    if (temp != " " && No_Unwanted_Chars(temp, Unwanted))
                                                        check = true;
                                                    else cerr << "Type a valid parameter. Don't use ','";
                                                }
                                                (*Gfind).Set_Name(temp);
                                                F1 = true;
                                                check = false;

                                                break;

                                            case 'a':
                                                cout << "Type a new Address in the format 'Legal_Address Amministrative_Address': ";

                                                while(!check) {
                                                    cin >> temp;
                                                    if (temp != " " && No_Unwanted_Chars(temp, Unwanted))
                                                        check = true;
                                                    else cerr << "Type a valid parameter. Don't use ','";
                                                }
                                                (*Gfind).Set_Address(temp);
                                                F1 = true;
                                                check = false;

                                                break;

                                            case 'j':
                                                cout << "Type a new Topic: ";
                                                while(!check) {
                                                    cin >> temp;
                                                    if (temp != " " && No_Unwanted_Chars(temp, Unwanted))
                                                        check = true;
                                                    else cerr << "Type a valid parameter. Don't use ','";
                                                }
                                                (*Gfind).Set_Activity(temp);
                                                F1 = true;
                                                check = false;

                                                break;

                                            case 'R':
                                                cout << "Member ID to remove: ";
                                                cin >> ID;

                                                if (Search_Profile(ID, users.begin(), users.end(), Ufind)) {

                                                    if ((*G_address_backup).Remove_Relation(ID)) {
                                                        F2 = true;
                                                        string group_id = (*G_address_backup).Get_ID();
                                                        (*Ufind).Remove_Relation(group_id);
                                                        cout << endl << "done" << endl;

                                                    } else cout << "This user was not a member of this group" << endl;

                                                } else cout << "This ID does not exist";

                                                break;

                                            case 'e':
                                                Editing_isDone = true;
                                                break;

                                            default:
                                                break;

                                        }

                                    }


                                }

                                File_Informations_Update(argv[1], argv[2], argv[3], F1, F2, F3, users.begin(), users.end(),
                                                         companies.begin(), companies.end(), groups.begin(), groups.end(),
                                                         posts.begin(), posts.end());
                            } else {
                                cerr << "This ID isn't associated to an existing profile, please type another one." << endl;
                            }

                            break;

                        case 'E':
                            cout << "Erase Profile:    Type an ID to delete the corrispondent profile: ";

                            cin >> ID;
                            if (Search_ID(ID, users.begin(), users.end(), companies.begin(), companies.end(), groups.begin(), groups.end(), Ufind, Cfind, Gfind, FindTipe)) {

                                F1 = true;
                                F2 = true;
                                bool done = false;
                                vector<Simple_User>::iterator Uto_erase;
                                vector<Company>::iterator Cto_erase;
                                vector<Group>::iterator Gto_erase;



                                if(FindTipe == "Simple_User"){

                                    Uto_erase = Ufind;

                                   vector<string> Connected_IDs = (*Uto_erase).Get_Connected_IDs();

                                    for(vector<string>::iterator it = Connected_IDs.begin(); it < Connected_IDs.end(); it++){


                                        Search_ID(*it,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end(),Ufind,Cfind,Gfind,FindTipe);

                                        string temp = *it;


                                        if(FindTipe == "Simple_User"){

                                            (*Ufind).Remove_Relation(ID);

                                        }
                                        if(FindTipe == "Company"){

                                            (*Cfind).Remove_Relation(ID);

                                        }
                                        if(FindTipe == "Group"){

                                            (*Gfind).Remove_Relation(ID);

                                        }


                                        done = true;
                                    }
                                    vector<Simple_User>::iterator beg = users.begin(), _end = users.end();
                                    Erase_Profile(beg,_end,Uto_erase,users);
                                }

                                else if(FindTipe == "Company" && !done){

                                    Cto_erase = Cfind;

                                        vector<string> Connected_IDs = (*Cfind).Get_Connected_IDs();

                                        for(vector<string>::iterator it = Connected_IDs.begin(); it < Connected_IDs.end(); it++){


                                            Search_ID(*it,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end(),Ufind,Cfind,Gfind,FindTipe);

                                            if(FindTipe == "Simple_User"){

                                                (*Ufind).Remove_Relation(ID);

                                            }
                                            if(FindTipe == "Company"){

                                                (*Cfind).Remove_Relation(ID);

                                            }
                                            if(FindTipe == "Group"){

                                                (*Gfind).Remove_Relation(ID);

                                            }


                                            done = true;
                                        }



                                    vector<Company>::iterator beg = companies.begin(), _end = companies.end();
                                    Erase_Profile(beg,_end,Cto_erase,companies);
                                }

                                else if(FindTipe == "Group" && ! done){

                                    Gto_erase = Gfind;


                                        vector<string> Connected_IDs = (*Gfind).Get_Connected_IDs();

                                        for(vector<string>::iterator it = Connected_IDs.begin(); it < Connected_IDs.end(); it++){


                                            Search_ID(*it,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end(),Ufind,Cfind,Gfind,FindTipe);

                                            if(FindTipe == "Simple_User"){

                                                (*Ufind).Remove_Relation(ID);

                                            }
                                            if(FindTipe == "Company"){

                                                (*Cfind).Remove_Relation(ID);

                                            }
                                            if(FindTipe == "Group"){

                                                (*Gfind).Remove_Relation(ID);

                                            }


                                            done = true;
                                        }



                                    vector<Group>::iterator beg = groups.begin(), _end = groups.end();
                                    Erase_Profile(beg,_end,Gto_erase,groups);
                                }


                                done = false;

                                cout << "profile eliminated √" << endl;

                                File_Informations_Update(argv[1],argv[2],argv[3],F1,F2,F3,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end(),posts.begin(),posts.end());

                            }

                            else cerr<<"no profile associated to this ID"<<endl;


                            break;


                        case 'n':

                            cout<<"Type a Date to calculate the number of users born after that day: "<<endl<<
                                "Date (dd,mm,yyyy)  : ";

                            cin>>dd>>mm>>yyyy;
                            date.SetDate(dd,mm,yyyy);
                            if(date.Date_Check()) {
                                cout << "Users Born After " << date.DateString() << ": "
                                     << nBorn_After_Date(date, users.begin(), users.end());
                            }
                            else
                                cerr<<"Incorrect Date requested for this control, exit function..."<<endl;


                            break;

                        case 'G':
                            cout << "Genealogy: Write an ID to find the user's genealogy and visualize a scheme of it."<<endl;
                            cout<<"write the command '@All' to print all users' genealogyc threes. They will be saved on different files."<<endl;
                            cout<<"ID: ";
                            cin>>ID;
                            if (ID != "@All") {
                                vector<Simple_User>::iterator f;
                                Inizializer(Parents_ID,Sons,cont);
                                if(Search_Profile(ID,users.begin(),users.end(),f)) {
                                    Parents_ID.push_back(ID);
                                    if (Find_Genealogy(users, Parents_ID, Parents_ID.size(), Sons, cont) < 2) {
                                        cout << "This user has not sufficient informations to determine his genealogy"
                                             << endl
                                             << "exit function...";
                                    } else {
                                        string temp_Albero = Build_Albero(users, Sons, cont);
                                        cout << endl << endl << "Do you want to save it into a file? Type Y or N: ";
                                        char param;
                                        cin >> param;
                                        if (param == 'Y') {
                                            ofstream f;
                                            string filename = ID + "Gen_Tree";
                                            f.open(filename);
                                            f << temp_Albero;
                                        }
                                        cout << endl << "Genealogic Three of " << ID << ":" << endl;
                                        cout << endl << endl << endl;
                                        cout << temp_Albero;

                                    }
                                    Sons.clear();
                                    cont = 0;
                                    Parents_ID.clear();
                                }
                                else cout<<"This ID does not exist."<<endl;
                            }
                            else{
                                int cont_creati = 0, ngiri = 0;
                                cout << endl << "All Genealogic Trees will be saved directly on different files, if they not already exist, without be printed on this program."<<endl;
                                ofstream punt;
                                for(vector<Simple_User>::iterator it_us = users.begin();it_us < users.end();it_us++){
                                    Inizializer(Parents_ID,Sons,cont);
                                    string filename = (*it_us).Get_ID() + "Gen_Tree";
                                    ifstream check (filename);
                                    Parents_ID.push_back((*it_us).Get_ID());
                                    if(!check && Find_Genealogy(users, Parents_ID, Parents_ID.size(), Sons, cont)>1) {
                                        punt.open(filename);
                                        Parents_ID.push_back((*it_us).Get_ID());
                                        punt << Build_Albero(users, Sons, cont);
                                        punt.close();
                                        cont_creati++;

                                    }

                                    ngiri++;
                                    cout<<ngiri/users.size()*100<<"% Completed"<<endl;

                                }
                                cout<<"file creati: "<<cont_creati;
                            }
                            break;

                        case 'A':

                            cout<<"Analytics Features: "<<endl;

                           if(companies.size() > 0) {

                               cout << endl << "COMPANIES:" << endl << endl;

                               cout<<" For Company tasks, tipe 0 to consider only the effective employees, 1 to consider even the consocited companies' employees: ";
                               cin>>ans;
                               cout <<endl<< "Company with more Employee ID: " ;

                               vector<Company>::iterator max_employee_it = Company_with_more_Employees(companies.begin(),companies.end(),ans[0]);

                               cout<<(*max_employee_it).Get_ID()<<endl;

                               cout << endl <<  "Companies' Employees and Consociated Number:";

                               Display_Employees_and_Consociated_Number(companies.begin(),companies.end(),ans[0]);
                               cout<<endl;
                           }

                            if(users.size() > 0) {

                                cout << endl << "SIMPLE USERS:" << endl << endl;

                                cout<< endl <<"Average Users' Age: " << round(Average_Users_Age(users.begin(),users.end()))<<endl;

                                cout << endl << "User:   Number of (explicit) Relations: " << endl;

                                Display_Users_Relations_Number(users.begin(), users.end());

                                cout<<endl << endl<<"Users with more friends: "<<(*User_with_more_friends(users.begin(),users.end())).Get_ID();

                                cout<<endl<<"Users with more Acquaintances: "<<(*User_with_more_acquaintances(users.begin(),users.end())).Get_ID();

                                cout<<endl << endl<<"Users' Family Member Number: "<<endl;

                                for(vector<Simple_User>::iterator iterat = users.begin();iterat<users.end();iterat++) {
                                    Inizializer(Parents_ID,Sons,cont);
                                    Parents_ID.push_back((*iterat).Get_ID());
                                    cout<<(*iterat).Get_ID()<<": "<<Count_Family_Member(iterat,users)<<endl;

                                }
                              }

                            if(groups.size()>0){

                                cout << endl << "GROUPS:" << endl << endl;

                                Members_Count_for_every_Group(groups.begin(),groups.end());


                            }

                            if(posts.size()>0){
                                cout << endl << endl << "POSTS:" <<endl;
                                cout<<"Most Liked Post:  " << ((*Most_Liked_Post(posts.begin(),posts.end())).PostData())<< "     number of likes: "<<((*Most_Liked_Post(posts.begin(),posts.end())).Get_nLikes())<<endl;
                                cout<<"Most Dsiliked Post:  " << ((*Most_Disliked_Post(posts.begin(),posts.end())).PostData())<< "     number of dislikes: "<<((*Most_Liked_Post(posts.begin(),posts.end())).Get_nDislikes())<<endl;

                            }


                            break;

                        case 'O':
                            cout<<"Overview:"<<endl<<"Type an ID: ";
                            cin>>ID;
                            cout<<endl<<endl;

                            if(Search_ID(ID,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end(),Ufind,Cfind,Gfind,FindTipe)){


                                if(FindTipe == "Simple_User"){

                                    cout<<ID<<" "<<FindTipe<<":"<<endl<<(*Ufind).InformationsStream()<<endl;
                                    Inizializer(Parents_ID,Sons,cont);
                                    Parents_ID.push_back(ID);
                                    if (Find_Genealogy(users,Parents_ID,Parents_ID.size(),Sons,cont)<2){
                                        cout<<"Genealogyc Informations are not available"<<endl;
                                    }
                                    else cout<< Build_Albero(users,Sons,cont);
                                    Inizializer(Parents_ID,Sons,cont);
                                    cout<<endl<<"number of family Members (including all children and gradnchildren: "<<Count_Family_Member(Ufind,users);

                                }
                                if(FindTipe == "Company"){

                                    vector<string> temp;

                                    cout<<ID<<" --> "<<FindTipe<<" profile"
                                        <<endl<<endl <<"Name: "<<(*Cfind).Get_Name()<<"   Feedback: "<<(*Cfind).Get_Feedback()<<endl<<endl<<"Address: "<<(*Cfind).Get_Address()<<endl<<endl<<"Topic: "<<(*Cfind).Get_Activity()
                                        <<endl<<endl<<"Number of employees: ";
                                    temp = (*Cfind).Get_All_Employees();
                                    cout<<(temp.size())<<endl<<"Employees:"<<endl;

                                    for(vector<string>::iterator it = temp.begin(); it < temp.end(); it++){

                                        cout<<endl<<*it;
                                    }
                                    temp.clear();
                                    temp = (*Cfind).Get_All_Consociated();
                                    cout<<endl<<endl<<"Number of consociated companies: "<<temp.size()<<endl<<"Consociated Companies:"<<endl<<endl;

                                    for(vector<string>::iterator it = temp.begin(); it < temp.end(); it++){

                                        cout<<endl<<*it;
                                    }

                                    temp.clear();
                                    cout<<endl<<endl;
                                }
                                if(FindTipe == "Group") {

                                    cout << ID << " --> " << FindTipe << " profile"
                                         << endl << endl << "Name: " << (*Gfind).Get_Name() << "   Feedback"
                                         << (*Gfind).Get_Feedback() << endl << endl << "Address: " << (*Gfind).Get_Address()
                                         << endl << endl << "Products: " << (*Gfind).Get_Activity()
                                         << endl << endl << "Number of members: " << (*Gfind).Get_nMembers() << endl;

                                    vector<string> temp = (*Gfind).Get_Members();
                                    if(temp.size() > 0){
                                        cout <<"Members:" << endl;
                                        for (vector<string>::iterator it = temp.begin(); it < temp.end(); it++) {

                                              cout << endl << *it;

                                        }

                                    }

                                    cout<<endl;
                                    temp.clear();

                                }


                            }

                            break;

                        case 'L':
                              cout<<"ID you want to login: ";
                              cin>>ID;

                            if(Search_ID(ID,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end(),Ufind,Cfind,Gfind,FindTipe)){
                                int op,i;
                                vector<string> ID_Network;
                                string auth;
                                cout<<"Operations:"<<endl<<"1. Show Posts"<<endl<<"2. Show Your Posts"<<endl<<"3. New Post"<<endl;
                                cin>>op;

                                vector<Post>::iterator postIt;
                                if(position.begin() != position.end())
                                    position.clear();
                                switch(op) {
                                    case 1:
                                        i = 0;

                                        if(FindTipe == "Simple_User")
                                         ID_Network = (*Ufind).Get_Network();

                                        else if(FindTipe == "Company")
                                             ID_Network = (*Cfind).Get_Network();

                                        else if(FindTipe == "Group")
                                                 ID_Network = (*Gfind).Get_Network();

                                        Search_Posts(ID, ID_Network, posts.begin(), posts.end(),companies, position, op);

                                        if (position.size() > 0) {

                                            for (vector<int>::iterator it = position.begin(); it < position.end(); it++) {

                                                vector<Post>::iterator Pit = posts.begin() + (*it);

                                                cout << endl << i << "." << " " << (*Pit).PostData();

                                                i++;
                                            }
                                            cout << endl << "choose a post to interact with: " << endl;

                                            cin >> op;
                                                if(op >= 0 && op <= position.size()-1) {
                                                    postIt = (posts.begin() + (*(position.begin() + op)));
                                                    ///^ Abbiamo spezzato in due dichiarando un apposito iteratore perchè non lo riconosceva come tale

                                                    cout
                                                            << "type 'L' to like this Post, 'D' to dislike it, 'e' to exit this function: ";
                                                    cin >> action;
                                                    if(action.size() == 1){
                                                        switch (action[0]) {
                                                            case 'L':
                                                                F3 = true;
                                                                (*postIt).New_Like(ID);
                                                                auth = (*postIt).Get_Author();
                                                                if (Search_ID(auth, users.begin(), users.end(),
                                                                              companies.begin(),
                                                                              companies.end(), groups.begin(), groups.end(),
                                                                              Ufind,
                                                                              Cfind, Gfind, FindTipe)) {

                                                                    if (FindTipe == "Simple_User")
                                                                        (*Ufind).Add_Received_Like();

                                                                    else if (FindTipe == "Company")
                                                                        (*Cfind).Add_Received_Like();

                                                                    else if (FindTipe == "Group")
                                                                        (*Gfind).Add_Received_Like();

                                                                }

                                                                break;
                                                            case 'D':
                                                                F3 = true;
                                                                (*postIt).New_Dislike(ID);
                                                                auth = (*postIt).Get_Author();
                                                                if (Search_ID(auth, users.begin(), users.end(),
                                                                              companies.begin(),
                                                                              companies.end(), groups.begin(), groups.end(),
                                                                              Ufind,
                                                                              Cfind,
                                                                              Gfind, FindTipe)) {

                                                                    if (FindTipe == "Simple_User")
                                                                        (*Ufind).Add_Received_Dislike();

                                                                    else if (FindTipe == "Company")
                                                                        (*Cfind).Add_Received_Dislike();

                                                                    else if (FindTipe == "Group")
                                                                        (*Gfind).Add_Received_Dislike();

                                                                }

                                                                break;
                                                            case 'e':
                                                                break;
                                                            default:
                                                                break;
                                                        }
                                                }
                                                    else{
                                                        cerr << endl << "Invalid Command --> Exit Function" << endl;
                                                    }
                                            }
                                                else{
                                                    cerr << endl << "Invalid Selection --> Exit Function" << endl;
                                                }
                                        }
                                        else cout<< endl << "No posts here." << endl;


                                        break;
                                    case 2:


                                        i = 0;
                                        Search_Posts(ID,  posts.begin(), posts.end(), position, op);
                                            if (position.size() > 0) {

                                                    for (vector<int>::iterator it = position.begin(); it < position.end(); it++,i++) {

                                                        vector<Post>::iterator Pit = posts.begin() + (*it);

                                                        cout << endl << i << "." << " " << (*Pit).PostData();

                                                    }
                                                    cout << endl << "choose a post to interact with: " << endl;
                                                    cin >> op;

                                                    if(op >= 0 && op <= position.size()-1){

                                                        postIt = (posts.begin() + (*(position.begin() + op)));
                                                        cout
                                                                << "type 'M' to modify your message, type 'E' to erase it, 'e' to exit this function"
                                                                << endl;
                                                        cin >> action;
                                                        switch (action[0]) {
                                                            case 'M':
                                                                F3 = true;
                                                                cout << "New Message: ";
                                                                getline(cin, message, '~');
                                                                i = 0;
                                                                while(i<message.size()){     //toglie l' "a capo"
                                                                    message[i]=message[i+1];
                                                                    i++;
                                                                }
                                                                (*postIt).Modify_message(message);
                                                                cout << endl << "Post Modified:"<<endl << "New Message: "<< (*postIt) << endl;
                                                                break;
                                                            case 'E':
                                                                F3 = true;
                                                                posts.erase(postIt);
                                                                cout << endl << "done." << endl;
                                                                break;
                                                            case 'e':
                                                                break;
                                                                break;
                                                            default:
                                                                    break;
                                                        }
                                                    }
                                                    else{
                                                        cerr << endl << "Invalid Selection --> Exit Function" << endl;
                                                    }
                                            }
                                            else cout << end <<"No posts here." <<endl;

                                        break;

                                    case 3:

                                        cout<<"New Post:"<<endl;
                                        cout<<"ID: "<<ID<<endl;

                                        if(Search_ID(ID,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end(),Ufind,Cfind,Gfind,FindTipe)){

                                            if(FindTipe == "Simple_User")
                                                (*Ufind).AddPostCont();
                                            else if(FindTipe == "Company")
                                                (*Cfind).AddPostCont();
                                            else if(FindTipe == "Group")
                                                (*Gfind).AddPostCont();


                                            cout<<"Type a message ending with the char '~' (MacOS: alt+5 , Windows: alt+1+2+6):"<<endl;
                                            getline(cin,message,'~');

                                            int i = 0;
                                            Date creation_Date;
                                            while(i<message.size()){     //toglie l' "a capo"
                                                message[i]=message[i+1];
                                                i++;
                                            }


                                            Post TempPost(ID,message,creation_Date);
                                            cout<<"Post Created: " << TempPost;
                                            posts.push_back(TempPost);
                                            printonfile(TempPost.PostData(),argv[3]);

                                        }

                                        break;
                                    default:break;
                                }

                                File_Informations_Update(argv[1],argv[2],argv[3],F1,F2,F3,users.begin(),users.end(),companies.begin(), companies.end(),groups.begin(),groups.end(),posts.begin(),posts.end());


                            }
                            else cout<<"This ID does not exist"<<endl;
                            break;

                        case 'H':
                            cout<<"Help: This functions shows all the main commands you can use."<<endl;
                            Functions_Help();
                            break;
                        case 'e':
                            cout << "Terminating Program ... " << endl;
                            end = true;
                            break;


                        default:
                            cerr<<"Invalid Operation, please type a valid input"<<endl;
                            break;


                    }

                }

            }

        }

        return 0;
    }

    string Create_String_Error(string &Error_Code){

        string Error_Message;
        string type;
        string nFile;
        string nRow;
        int i = 0;
        char temp ='d'; //inizializzata solo per evitare che sia in partenza pari a \0
        int bookmark = 0;
        int cont = 0;
        while(temp != '\0'){



            temp = Error_Code[i];




            if(Error_Code[i] == '_'){

                for(int j = bookmark;j<i;j++){

                    if(cont == 0) {


                        type += Error_Code[j];


                    }
                    else if(cont == 1){

                        nFile += Error_Code[j];


                    }
                    else if(cont ==2){

                        nRow += Error_Code[j];


                    }

                }

                bookmark = i+1;
                cont++;
            }

            i++;

        }

        if(type == "F") {

            Error_Message = "File Formatting Error into File ";

        }
        if(type == "R") {

            Error_Message = "...   to file: ";

        }
        if(type == "NF"){


            Error_Message = "One or more user IDs incongruence between File 1 and File ";

        }

        if(type == "IncD"){

            Error_Message = "Incomplete Data parameter(s) in File ";

        }

        if(type == "IDR"){

            Error_Message = "ID repetition in File ";
        }

        return Error_Message += nFile + " to row: " + nRow;




    }

    void Load_Ascii(vector<char> &Unwanted, int except_from, int to){

        for(int i = 0; i < 255; i++){

            if(i < except_from || i > to)            //il carattere / è consentito
            Unwanted.push_back(i);

        }


    }
















