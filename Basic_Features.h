    //
    // Created by Lorenzo Carrano on 27/05/18.
    //

    #ifndef PROGETTO_INFORMATICA_V1_BASIC_FEATURES_H
    #define PROGETTO_INFORMATICA_V1_BASIC_FEATURES_H

    #include <fstream>
    #include "Simple_User.h"
    #include "Company.h"
    #include "Group.h"
    #include "Ancestors.h"

    using namespace std;

    void Functions_Help(){

        cout<<"Here's all Features and Commands of this Program:"<<endl << endl

        <<" 'N' : New_Profile, will be asked if you would like to create a Simple User, Company or Group profile."<<endl << endl

        <<" 'D': Display, displays on screen all the profiles stored in the SocialNetwork Database with their basic informations, "
                "ordered by tipe (Simple Users,Companies and Groups)"<<endl << endl

        << " 'S' : Sort all companies by likes/dislikes rapport" <<endl << endl

        << " 'W' : Find Lone Wolves by input parameters by keyboard" <<endl << endl

        << " 'M' : Modify Profile and Add/Remove Relations. NOTE: ID can't be modified" << endl << endl

        << " 'E' : Erase a profile selected by ID" << endl << endl

        << " 'n' : Calculate the number of simple users born after a certain date, in input from keyboard" << endl << endl

        << " 'G' : Generate the genealogical tree of a specific user and print it on screen or in a file, or  the genealogical three of all users in different files" <<endl << endl

        << " 'A' : Analytics Analysis of all profiles" << endl << endl

        << " 'O' : Overview, print on screen all the main informations about a researched ID, like relations and genealogical tree" << endl << endl

        << " 'L' : Login as a user to interact with your and others' posts" << endl << endl

        << " 'e' : Exit Program" << endl;


    }

    bool Files_Check(string* fileNames,int nFiles,bool *errors){

        ifstream p;
        bool check = true;



        for(int i = 0;i<nFiles;i++) {

            p.open(*(fileNames + i));

            if (!p.is_open()) {
                check = false;

                *(errors+i) = false;

            }

            if (p.is_open()) {
                *(errors+i) = true;
                p.close();


            }


        }


        return check;


    }

    string Relation_Converter(string &relation){
        bool converted = false;

        if(relation == "Parent" && !converted ) {
            relation = "Child";
            converted = true;
        }

        if(relation == "Child" && !converted ){
            relation = "Parent";
            converted = true;

        }

        if(relation == "Followed" && !converted){
            relation = "Follower";
            converted = true;

        }
        if(relation == "Follower" && ! converted){
            relation = "Followed";
            converted = true;

        }
        return relation;
    } ///Se la relazione in entrata prevede una specularità (es padre/figlio) predispone la relazione in uscita per il secondo utente

    bool Relation_isValid(string &Relation){
        string possible_relations[5] ={"Friend","Partner","Parent","Child","Consociated"};
        //non sono tutte le relazioni, ma solo quelle che un utente semplice può esplicitamente aggiungere: il check delle relazioni vere e proprie è fatto in lettura

        bool isvalid = false;

        for(int i = 0; i < 10 && !isvalid; i++){

            if (Relation == possible_relations[i])
                isvalid = true;

        }

    return isvalid;


    }

    void printonfile(string informations,char* filename){

        ofstream p;
        p.open(filename,ios::app);
        p<<endl<<informations;

    }

    template <typename T>
    bool Search_Profile(string &searchedID, T begin, T end, T &find){
        bool found = false;
        for(T it = begin; it < end && ! found; it++){


            if((*it).Get_ID() == searchedID) {
                found = true;
                find = it;

            }

        }


        return found;
    }

    bool Search_ID(string &searchedID,vector<Simple_User>::iterator Uit,vector<Simple_User>::iterator Uend,vector<Company>::iterator Cit,
                   vector<Company>::iterator Cend,vector<Group>::iterator Git,vector<Group>::iterator Gend,
                   vector<Simple_User>::iterator &Ufind,vector<Company>::iterator &Cfind,vector<Group>::iterator &Gfind,string &FindTipe){

        bool found = false;

        if(Search_Profile(searchedID,Uit,Uend,Ufind)){
            FindTipe = "Simple_User";
            found = true;
        }
        else if(Search_Profile(searchedID,Cit,Cend,Cfind)){
            FindTipe = "Company";
            found = true;
        }
        else if(Search_Profile(searchedID,Git,Gend,Gfind)){
            FindTipe = "Group";
            found = true;
        }


        return found;

    }

    bool Profile_Exists(string ID,vector<Simple_User>::iterator Uit,vector<Simple_User>::iterator Uend,vector<Company>::iterator Cit,vector<Company>::iterator Cend,
                    vector<Group>::iterator Git, vector<Group>::iterator Gend){

        vector<Simple_User>::iterator uf;
        vector<Company>::iterator cf;       ///Sono solo dichiarazioni necessarie a far partire la funzione Search_ID
        vector<Group>::iterator gf;
        string str;


        return (Search_ID(ID,Uit,Uend,Cit,Cend,Git,Gend,uf,cf,gf,str)) ? true : false;

    } ///In inserimento, verifica che l'ID desiderato non sia in uso da un'altro profilo. Se restituisce falso, può essere usata per verificare esistenza di un utente

    void Read(ifstream &p,string &name, string &surname,string &address, string &job,Date & bDate,string &gender,
              bool &CheckFormatting,bool &validID){
        string trashString;
        string ddB,mmB,yyyyB;
        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;
        }

        getline(p, trashString, ' ');
        if (trashString != "Name:") {
            CheckFormatting = false;
        }
        getline(p, name, ',');
        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;
        }
        getline(p, trashString, ' ');
        if (trashString != "Surname:") {
            CheckFormatting = false;
        }
        getline(p, surname, ',');
        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;
        }
        getline(p, trashString, ' ');
        if (trashString != "Address:") {
            CheckFormatting = false;
        }
        getline(p, address, ',');
        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;
        }
        getline(p, trashString, ' ');
        if (trashString != "Job:") {
            CheckFormatting = false;
        }
        getline(p, job,',');
        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;
        }

        getline(p, trashString, ' ');
        if (trashString != "BirthDate:") {
            CheckFormatting = false;
        }
        getline(p,ddB,'/');
        if(ddB == ""){
            CheckFormatting = false;
        }

        getline(p,mmB,'/');
        if(mmB == ""){
            CheckFormatting = false;
        }
        getline(p,yyyyB,',');
        if(yyyyB == ""){
            CheckFormatting = false;
        }


        Date temp(atoi(ddB.c_str()),atoi(mmB.c_str()),atoi(yyyyB.c_str()));
        if(bDate.Date_Check())
        bDate.Copy(temp);

        else CheckFormatting = false;

        getline(p,trashString,' ');
        if(trashString != ""){

            CheckFormatting = false;

        }

        getline(p, trashString, ' ');
        if (trashString != "Gender:") {
            CheckFormatting = false;
        }
        getline(p,gender);
        if(gender != "Male" && gender != "Female" ){
            CheckFormatting = false;
        }

    } ///Per i Simple_Users E' l'unico dove per ora controllo l'ID

    void Read(ifstream &p,string &ID1,string &ID2,string &relation,bool &check){
        string possible_relations[10] ={"Followed","Follower","Friend","Partner","Parent","Child","Consociated","Employee","Job","Member"};
        check = false;
        getline(p,ID1,',');
        getline(p,ID2,',');
        getline(p,relation);
        for(int i = 0;i < 10 && !check;i++){

            if(relation == possible_relations[i])
                check = true;


        }




    } ///per le relazioni fra profili

    void Read(ifstream &p,string &name, string &address1, string &address2, string &activity,
              bool &CheckFormatting,bool &validID){

        string trashString;

        getline(p, trashString, ':');
        if (trashString != " Name") {
            CheckFormatting = false;

        }
        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;

        }
        getline(p, name, ',');
        getline(p, trashString, ':');
        if (trashString != " Address") {
            CheckFormatting = false;

        }
        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;

        }
        getline(p, address1, '(');
        getline(p, trashString, ' ');
        if (trashString != "Legal)") {
            CheckFormatting = false;

        }
        getline(p, address2, '(');
        getline(p, trashString, ':');
        if (trashString != "Amministrative), Activity/Products") {
            CheckFormatting = false;

        }
        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;

        }
        getline(p, activity);

    }      ///Per Companies

    void Read(ifstream &p,string &name,string &address,string &topic,bool &CheckFormatting,bool &validID){

        string trashString;

        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;

        }
        getline(p, trashString, ' ');
        if (trashString != "Name:") {
            CheckFormatting = false;

        }
        getline(p, name, ',');
        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;

        }
        getline(p, trashString, ' ');
        if (trashString != "Address:") {
            CheckFormatting = false;

        }
        getline(p, address, ',');
        getline(p, trashString, ' ');
        if (trashString != "") {
            CheckFormatting = false;

        }
        getline(p, trashString, ' ');
        if (trashString != "Topic:") {
            CheckFormatting = false;

        }
        getline(p, topic);
    }     ///Per i Groups

    bool Read_Files(ifstream &p, string* fileNames,int nFiles,vector<Simple_User> &users,vector<Company> &companies, vector<Group> &groups,vector<Post> &posts, string &stringerror){

        vector<string> stID; ///Salva gli ID letti fino a questo momento. Usata per verificare che non ci siano duplicati --> Errore di Formattazione
        int nrow;

        bool reading_is_right = true,CheckFormatting = true,validID = true;

        for(int i = 0;i<nFiles && reading_is_right;i++) {
            if (p.is_open())
                p.close();
            p.open(*(fileNames + i));
            nrow = 0;


            if (i == 0) {        ///Lettura I file

                bool validData = true; //aggiunta per vedere se i dati letti non sono vuoti, se non vuoti errore (controllo solo sui dati obbligatori*)
                while (!p.eof() && CheckFormatting && validID) {
                    nrow++;
                    string trashString;
                    string id;
                    string tipe;
                    getline(p, id, ',');
                    if(id==""){
                        CheckFormatting = false;
                    }
                    vector<string>::iterator it = stID.begin();

                    while(it < stID.end() && validID){

                        if(*it == id)
                            validID = false;

                        it++;

                    }
                    getline(p,trashString,' ');
                        if(trashString != ""){
                            CheckFormatting = false;
                        }

                    getline(p,tipe,',');

                    if (tipe == "Simple_User") {
                        string name, surname,address, job, gender;
                        Date bDate;
                        Read(p, name, surname,address, job,bDate,gender,CheckFormatting, validID);

                        if(name == "" || surname == "" || id == "" || gender == "") //Controllo sulla completezza dei dati
                            validData = false;

                        if (CheckFormatting && validID && validData) {

                            Simple_User tempUser(name, surname, id, address, job,bDate,gender); //crea oggetto
                            users.push_back(tempUser);                                          //aggiunge oggetto in vettore dinamico
                            stID.push_back(tempUser.Get_ID());                                  //aggiunge ID nell'elenco degli ID già comparsi
                        }

                    }
                    if (tipe == "Company") {

                        string name, address1, address2, activity;
                        Read(p, name, address1, address2, activity, CheckFormatting, validID);

                        if(name == "" || id == "" || address1 == "" || address2 == "" || activity == "") //Controllo sulla completezza dei dati
                            validData = false;

                        if (CheckFormatting && validID && validData) {
                            Company tempCompany(name, id, address1, address2, activity);
                            companies.push_back(tempCompany);
                            stID.push_back(tempCompany.Get_ID());
                        }


                    }
                    if (tipe == "Group") {
                        string name, address, topic;
                        Read(p, name, address, topic,CheckFormatting, validID);

                        if(name == "" || id == "" || address == "" || topic == "") //Controllo sulla completezza dei dati
                            validData = false;

                        if (CheckFormatting && validID && validData) {
                            Group tempGroup(name, id, address, topic);
                            groups.push_back(tempGroup);
                            stID.push_back(tempGroup.Get_ID());
                        }
                    }

                    if (tipe != "Simple_User" && tipe != "Company" && tipe != "Group")
                        CheckFormatting = false;


                }

                stID.clear();


                if (!CheckFormatting)
                    ///stringerror = "File1 Formatting Error to row " + to_string(nrow) ;
                    stringerror = "F_" + to_string(i + 1) + "_" + to_string(nrow) + "_";

                if (!validID)
                    stringerror = "IDR_1_ " + to_string(nrow) + "_";      ///ID repetition to row

                if(!validData){
                    stringerror = "IncD_1_"+to_string(nrow)+"_";       ///Incomplete Data to row ...
                }

                if (!CheckFormatting || !validID || !validData) {
                    reading_is_right = false;

                }
            }


            if (i == 1) {        ///Lettura II file

                if(p.is_open())
                    p.close();
                p.open(*(fileNames + i));

                nrow = 0;
                while (!p.eof() && CheckFormatting) {
                    nrow++;
                    string ID1, ID2, relation,findTipe1,findTipe2;
                    Read(p, ID1, ID2, relation, CheckFormatting);
                    vector<Simple_User>::iterator Ufind;
                    vector<Simple_User>::iterator Ufind2;
                    vector<Company>::iterator Cfind;
                    vector<Company>::iterator Cfind2;
                    vector<Group>::iterator Gfind;


                    if (Search_ID(ID1,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end(),Ufind,Cfind,Gfind,findTipe1)
                        && Search_ID(ID2,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end(),Ufind2,Cfind2,Gfind,findTipe2)) {


                        if(findTipe1 == "Simple_User" && findTipe2 == "Simple_User"){

                            (*Ufind).Add_Relation((*Ufind2).Get_ID(),Relation_Converter(relation));
                            (*Ufind2).Add_Relation((*Ufind).Get_ID(),Relation_Converter(relation));


                        }

                        if(findTipe1 == "Simple_User" && findTipe2 == "Company" && relation == "Employee"){

                            string temp = (*Cfind2).Get_ID();
                            (*Ufind).Add_Relation(temp,relation);
                            temp = (*Ufind).Get_ID();
                            (*Cfind2).New_Employee(temp);

                        }

                        if(findTipe1 == "Company" && findTipe2 == "Simple_User" && relation == "Job"){

                            string temp = (*Ufind2).Get_ID();
                            (*Cfind).New_Employee(temp);
                            temp =(*Cfind).Get_ID();
                            (*Ufind2).Add_Relation(temp,"Employee");


                        }
                        if(findTipe1 == "Company" && findTipe2 == "Company" && relation == "Consociated"){

                            string temp = (*Cfind2).Get_ID();
                            (*Cfind).Add_Consociated_Company(temp);
                            temp = (*Cfind).Get_ID();
                            (*Cfind2).Add_Consociated_Company(temp);

                        }

                        if(findTipe1 == "Simple_User" && findTipe2 == "Group" && relation == "Member"){

                            string temp = (*Ufind).Get_ID();
                            (*Gfind).New_Member(temp);
                            (*Ufind).Add_Relation((*Gfind).Get_ID(),relation);

                        }
                        if(findTipe1 == "Group" && findTipe2 == "Simple_User" && relation == "Group"){

                            string temp = (*Ufind).Get_ID();
                            (*Gfind).New_Member(temp);
                            (*Ufind).Add_Relation((*Gfind).Get_ID(),"Member");

                        }



                    } else {

                        CheckFormatting = false;
                        reading_is_right = false;
                        stringerror = "NF_2_"+to_string(nrow)+"_"; ///One or more user IDs incongruence between File 1 and File 2

                    }


                }


            }


            if (i == 2) {        ///Ossia se sto leggendo III file

                if(p.is_open())
                    p.close();
                p.open(*(fileNames + i));
                while (!p.eof()) {

                    //viene creato l'oggetto solo per post il cui autore è ancora esistente (-->non ha cancellato il profilo)
                    //vengono considerati like e dislike solo da parte di profili ancora esistenti

                    vector<Simple_User>::iterator Ufind;
                    vector<Company>::iterator Cfind;
                    vector<Group>::iterator Gfind;
                    string ID;
                    string trash;
                    string Findtipe;
                    getline(p,ID,',');
                    if(Search_ID(ID,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end(),Ufind,Cfind,Gfind,Findtipe)){ ///Cerca Autore

                       if(Findtipe == "Simple_User"){  ///Se esiste aggiorna il numero di post creati da quel profilo


                            (*Ufind).AddPostCont();



                        }
                       else if(Findtipe == "Company"){


                            (*Cfind).AddPostCont();


                        }
                       else if(Findtipe == "Group"){


                            (*Gfind).AddPostCont();

                        }

                    }  ///Se cancello un utente, i suoi post rimangono in archivio ma non più visualizzati.
                    string temp;
                    getline(p,temp,'~');
                    int dd,mm,yyyy;
                    Post TempPost(ID,temp);
                    trash = "";


                    getline(p,trash,'{');
                    if(trash!="likes:"){
                        CheckFormatting = false;
                        stringerror = "F_3_"+to_string(nrow)+"_";
                    }

                    getline(p,trash,' '); ///Ora in trash ho il resto dei likes sulla riga, termina con \0

                    int ind = 0,bookmark = 0; ///La uso come indice per la lettura della stringa temp, alla ricerca degli ID di likes prima e dislikes dopo
                    vector<Simple_User>::iterator tempU;
                    string tempID = "";
                    while(trash[ind] != '\0'){

                        if(trash[ind] == ',' || trash[ind] == '}'){

                            for(int j = bookmark; j<ind;j++){

                                tempID += trash[j];

                            }
                            bookmark = ind+1;

                            if(Profile_Exists(tempID,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end())){

                                TempPost.New_Like(tempID);

                                if(Findtipe == "Simple_User")
                                    (*Ufind).Add_Received_Like();
                               else if(Findtipe == "Company")
                                    (*Cfind).Add_Received_Like();
                               else  if(Findtipe == "Group")
                                    (*Gfind).Add_Received_Like();


                            }

                           if(Search_Profile(tempID,users.begin(),users.end(),tempU)){   ///Nota: solo gli utenti possono mettere like ai post, mentre tutti possono scrivere post

                                   (*tempU).Add_GivedLike();
                           }

                            tempID = "";

                        }



                        ind++;
                    }


                    getline(p,trash,'{'); ///da qui leggo gli ID dei dislikes, la lettura terminerà al carattere }
                    bookmark = 0;
                    ind = 0;
                    if(trash!="dislikes:"){
                        CheckFormatting = false;
                        stringerror = "F_3_"+to_string(nrow)+"_";
                    }
                    getline(p,trash,' '); ///Ora in trash ho il resto della riga,con i Dislikes, termina con }

                    while(trash[ind] != '\0'){

                        if(trash[ind] == ',' || trash[ind] == '}'){

                            for(int j = bookmark; j<ind;j++){

                                tempID += trash[j];

                            }
                            bookmark = ind+1;

                            if(Profile_Exists(tempID,users.begin(),users.end(),companies.begin(),companies.end(),groups.begin(),groups.end())){

                                TempPost.New_Dislike(tempID);

                                if(Findtipe == "Simple_User")
                                    (*Ufind).Add_Received_Dislike();
                                else if(Findtipe == "Company")
                                    (*Cfind).Add_Received_Dislike();
                                else  if(Findtipe == "Group")
                                    (*Gfind).Add_Received_Dislike();


                            }

                            if(Search_Profile(tempID,users.begin(),users.end(),tempU)){ ///Nota: solo gli utenti possono mettere like ai post, mentre tutti possono scrivere post

                                (*tempU).Add_GivedDislike();
                            }

                            tempID = "";

                        }



                        ind++;
                    }

                    getline(p,trash,' ');
                    if(trash != "Creation_Date: ")
                        CheckFormatting = false;
                    getline(p,trash,'/'); /// Posso leggere così perchè so che mancano solo i tre parametri dd/mm/yyyy e quindi conosco la formattazione esatta del resto della riga
                    dd = atoi(trash.c_str());
                    getline(p,trash,'/');
                    mm = atoi(trash.c_str());
                    getline(p,trash);
                    yyyy = atoi(trash.c_str());
                    Date creation_Date(dd,mm,yyyy);
                    if(!creation_Date.Date_Check())
                        CheckFormatting = false;
                    else TempPost.Set_Creation_Date(creation_Date);
                    posts.push_back(TempPost);

                }


            }




        }


        return reading_is_right;
    }

    template <typename T>
    void Display_Profile(T &begin, T &end){

        for(T it = begin; it < end; it++){

            cout<<(*it).InformationsStream()<<endl<<endl;

        }


    }

    ///Mostra post delle cerchie di ID e ne indicizza la posizione nel vettore originale
    bool Search_Posts(string &ID, vector<string> &ID_Network, vector<Post>::iterator it,vector<Post>::iterator end, vector<Company> &Companies, vector<int> &position,int &mode){
        int indice = 0;
        bool ans = false;

                for(it;it < end;it++) {
                    string author = (*it).Get_Author();
                    bool contained = false,is_a_company = false;

                    for(auto jt = ID_Network.begin(); jt < ID_Network.end() && !contained; jt++){ //controlla faccia parte delle cerchie dell'ID

                        if(*jt == author)
                            contained = true;

                    }

                    for(auto jt = Companies.begin(); jt < Companies.end() && !is_a_company; jt++){

                        if((*jt).Get_ID() == author)
                            contained = true;

                    }

                    if(author != ID && (contained || is_a_company)){

                        position.push_back(indice);
                        ans = true;
                    }

                    indice++;

                }



     return ans;
    }

    ///Mostra post di ID e ne indicizza la posizione nel vettore originale
    bool Search_Posts(string &ID, vector<Post>::iterator it,vector<Post>::iterator end, vector<int> &position,int &mode){

        int indice = 0;
        bool ans = false;

        for(it;it < end;it++) {

            if((*it).Get_Author() == ID){

                position.push_back(indice);
                ans = true;

            }
            indice++;

        }

        return ans;

    }

    template <typename T>
    bool Has_A_Stream(T it, T end){

        bool ans = false;

        for(it;it < end && !ans; it++){

            ans = ((*it).Connections_Stream() != "") ? true : false;

        }



        return ans;
    }

    void File_Informations_Update(const string &nomefile,const string &nomefile2,const string &nomefile3,const bool F1,const bool F2,const bool F3,vector<Simple_User>::iterator Ubegin,vector<Simple_User>::iterator Uend,vector<Company>::iterator Cbegin,
                                  vector<Company>::iterator Cend, vector<Group>::iterator Gbegin,vector<Group>::iterator Gend,vector<Post>::iterator Pit,vector<Post>::iterator Pend) {

        ofstream p;
        vector<Simple_User>::iterator Uit;
        vector<Company>::iterator Cit;
        vector<Group>::iterator Git;
        string stream = "";
        if(F1){
            if(p.is_open())
                p.close();
        p.open(nomefile);


        for (Uit = Ubegin; Uit < Uend; Uit++) {


            if (Cit == Cend && Git == Gend) {


                p << (*Uit).InformationsStream();
                if (Uit != Uend - 1)
                    p << endl;

            } else {

                p << (*Uit).InformationsStream() << endl;

            }


        }
        for (Cit = Cbegin; Cit < Cend; Cit++) {


            if (Git == Gend) {


                p << (*Cit).InformationsStream();
                if (Cit != Cend - 1)
                    cout << endl;


            } else {

                p << (*Cit).InformationsStream() << endl;

            }

        }

        for (Git = Gbegin; Git < Gend; Git++) {

            p << (*Git).InformationsStream();
            if (Git != Gend - 1)
                p << endl;

        }


    }

        if(F2){

            if(p.is_open())
                p.close();
            p.open(nomefile2);



            for (Uit = Ubegin; Uit < Uend; Uit++) {

                stream = (*Uit).Connections_Stream();
                if ((Cbegin == Cend || !Has_A_Stream(Cbegin,Cend)) && (Gbegin == Gend || !Has_A_Stream(Gbegin,Gend))) {

                    p << stream;

                    if (Uit != Uend - 1 && stream != "") {
                        p << endl;


                    }
                } else {
                    p << stream;
                    if (stream != "")
                        p << endl;

                }
            }


            for (Cit = Cbegin; Cit < Cend; Cit++) {

                stream = (*Cit).Connections_Stream();
                if (Gbegin == Gend || !Has_A_Stream(Gbegin,Gend)) {

                    p << stream;

                    if (Cit != Cend - 1 && stream != "") {
                        p << endl;

                    }
                } else {
                    p << stream;
                    if (stream != "")
                        p << endl;

                }
            }


            for(Git = Gbegin; Git < Gend; Git++){

                stream = (*Git).Connections_Stream();

                    p << stream;
                    if(Git < Gend -1 && stream != "") {

                        p << endl;
                    }

            }

        }

        if(F3){
            if(p.is_open())
                p.close();
                        p.open(nomefile3);

            for(Pit;Pit<Pend;Pit++){

                p<<(*Pit).PostData();

                if(Pit != Pend - 1)

                    p<<endl;

            }

        }

    }

    void Inizializer(vector<string>&Parents_ID,vector<Ancestors>&Sons,int &cont){

        if(Parents_ID.size()>0)
            Parents_ID.clear();
        if(Sons.size()>0)
            Sons.clear();
        if(cont>0)
            cont = 0;




    }

    bool Has_Common_Child(string &id1,string &id2,vector<Simple_User> &users){

        vector<Simple_User>::iterator find1,find2,beg = users.begin(), end = users.end();
        Search_Profile(id1,beg,end,find1);
        Search_Profile(id2,beg,end,find2);


        return (*find1).Has_Common_Child(*find2);

    }

    template <typename T,typename Q>
    void Erase_Profile(T &begin, T &end,T &to_erase,vector<Q> &vect){ //Ho definito due tipi generici: T è il tipo iteratore del vettore, Q è il tipo del vettore

        vector<Q> temp;

        for (T it = vect.begin(); it < vect.end(); it++) { //copio tutti tranne l'oggetto da cancellare

            if (it != to_erase)
                temp.push_back(*it);

        }

            vect.clear();
            vect = temp;
            temp.clear();


        }

    bool No_Unwanted_Chars(string &input_str, vector<char> &Unwanted) {
        bool check = true;
        for (int i = 0; i < input_str.size() && check; i++) {

            for (vector<char>::iterator it = Unwanted.begin(); it < Unwanted.end() && check; it++) {


                if (input_str[i] == *it)

                    check = false;
            }
        }


            return check;

    }

    #endif //PROGETTO_INFORMATICA_V1_BASIC_FEATURES_H
