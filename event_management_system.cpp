#include <bits/stdc++.h>
using namespace std;

void decor(){
    cout<<endl;
    cout<<"-----------------------------------------------------------------------------------------------"<<endl;
}


class User {
protected:
    int userID;
    string name;
    string email;
    string password;
    string usertype;
public:
    User(int id, string n, string e, string p, string ut) : userID(id), name(n), email(e), password(p), usertype(ut) {}

    virtual void viewProfile(){
        cout<<"UserID: "<<userID<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Email: "<<email<<endl;
    }
    virtual void editProfile(){
        cout << "Current Username: " << name << endl;
        cout << "Current Email: " << email << endl;
        
        string newUsername = name, newEmail = email, newPassword = password;
        int ff;
        cout<<"Enter 1 to edit Name otherwise 0 to continue: "; cin>>ff;
        if(ff == 1){
            cout << "Enter new Username: ";
            cin.ignore();
            getline(cin, newUsername);
            ff = 0;
        }
        cout<<"Enter 1 to edit email otherwise 0 to continue: "; cin>>ff;
        if(ff == 1){
            cout << "Enter new Email: ";
            cin.ignore();
            getline(cin, newEmail);
            ff = 0;
        }
        cout<<"Enter 1 to edit password otherwise 0 to continue: "; cin>>ff;
        if(ff == 1){
            cout << "Enter new Password: ";
            cin.ignore();
            getline(cin, newPassword);
            ff = 0;
        }

        name = newUsername;
        email = newEmail;
        password = newPassword;

        cout << "Profile updated successfully!" << endl;
    }
    virtual bool cancelEvent(int eid){return false;}
    

    int getUserID() const{
        return userID;
    }
    string getUserEmail(){
        return email;
    }
    string getUserName(){
        return name;
    }
    string getUserPassword(){
        return password;
    }
    string getUserType(){
        return usertype;
    }


    virtual void saveToFile(ofstream& fout){
        fout << userID <<","<< email <<","<< name <<","<< password <<","<< usertype;
    }

    virtual void loadFromFile(istringstream& ss){
        cout<<"admin"<<endl;
    }
};

class Participant: public User{
private:
    vector<int>registeredEvents;
public:
    Participant(int id, string n, string e, string p, string ut) : User(id,n,e,p,ut) {}

    void registerEvent(int eventID){
        registeredEvents.push_back(eventID);
    }
    bool cancelEvent(int eid) override{
        for(auto it = registeredEvents.begin(); it != registeredEvents.end(); it++){
            if((*it)==eid){
                registeredEvents.erase(it);
                return true;
            }
        }
        return false;
    }
    void editProfile() override{
        cout<<"Editting Participant profile..."<<endl;
        User::editProfile();
    }

    vector<int> viewRegisteredEvents(){
        return registeredEvents;
    }
    

    void saveToFile(ofstream& fout) override{
        User::saveToFile(fout);
        int num = registeredEvents.size();
        fout <<","<<num;
        for(auto it: registeredEvents){
            fout<<","<<it;
        }
        fout<<endl;
    }

    void loadFromFile(istringstream& ss) override{
        string token;
        getline(ss,token,',');
        int num = stoi(token);
        registeredEvents.resize(num);
        // cout<<token<<endl;

        for(int i = 0; i<num; i++){
            getline(ss,token,',');
            // cout<<token<<endl;
            int x = stoi(token);
            registeredEvents[i] = x;
        }
        // for(auto it: registeredEvents) cout<<it<<" ";
        // cout<<endl;
    }
};

class Admin: public User{
private:
    vector<int>admins;
public:
    Admin(int id, string n, string e, string p, string ut) : User(id,n,e,p,ut) {}
    void editProfile() override{
        cout<<"Editting Admin profile..."<<endl;
        User::editProfile();
    }


    void saveToFile(ofstream& fout) override{
        User::saveToFile(fout);
        fout<<endl;
    }
};




class Event{
protected:
    int eventID;
    string eventName;
    string eventDate;
    int budget;
    string eventType;
    vector<string>guests;
public:
    Event(int eid, string ename, string edate, int b, string et) : eventID(eid), eventName(ename), eventDate(edate), budget(b), eventType(et) {}

    int getEventID(){
        return eventID;
    }
    string getEventName(){
        return eventName;
    }
    string getEventDate(){
        return eventDate;
    }
    string getEventType(){
        return eventType;
    }

    void addGuest(string guest){
        guests.push_back(guest);
    }
    void showGuests(){
        for(int i = 0; i<guests.size(); i++){
            cout<<i+1<<". "<<guests[i]<<endl;
        }
        cout<<endl;
    }
    bool delGuest(int ind){
        if(ind>=1 && ind<=guests.size()){
            guests.erase(guests.begin()+(ind-1));
            return true;
        }
        return false;
    }

    virtual void viewEventDetails(){
        cout<<"Event Type: "<<eventType<<endl;
        cout<<"Event ID: "<<eventID<<endl;
        cout<<"Event Name: "<<eventName<<endl;
        cout<<"Event Date: "<<eventDate<<endl;
        cout<<"Event Budget: "<<budget<<endl;
        cout<<"Guests: ";
        if(guests.empty()){
            cout<<"No Guests!";
        }
        else{
            for(int i = 0; i<guests.size(); i++){
                if(i==guests.size()-1){
                    cout<<guests[i]; continue;
                }
                cout<<guests[i]<<", ";
            }
        }
        cout<<endl;
    }

    virtual void editEventDetails(){
        string newname = eventName, date = eventDate; double bud = budget;
        int ff;
        cout<<"Enter 1 to edit name otherwise 0 to continue: "; cin>>ff;
        if(ff == 1){
            cout<<"Enter new name: ";
            cin.ignore();
            getline(cin,newname);
            ff = 0;
        }
        cout<<"Enter 1 to edit date otherwise 0 to continue: "; cin>>ff;
        if(ff == 1){
            cout<<"Enter new date: ";
            cin.ignore();
            getline(cin,date);
            ff = 0;
        }
        cout<<"Enter 1 to edit budget otherwise 0 to continue: "; cin>>ff;
        if(ff == 1){
            cout<<"Enter new budget: ";
            cin>>bud;
            ff = 0;
        }

        while(1){
            cout<<"Enter 1 to edit guest list otherwise 0 to continue: "; cin>>ff;
            if(ff == 1){
                cout<<"Current Guests list: "<<endl;
                showGuests();
                int choice;
                cout<<"1. Add guests"<<endl;
                cout<<"2. Delete guests"<<endl;
                cout<<"3. Edit guest info"<<endl;
                cout<<"Enter choice: "; cin>>choice;
                if(choice == 1){
                    string g;
                    cout<<"Enter Guest name: ";
                    cin.ignore();
                    getline(cin,g);
                    addGuest(g);
                }
                else if(choice == 2){
                    int ind;
                    cout<<"Enter Guest index to delete: "; cin>>ind;
                    if(delGuest(ind)){
                        cout<<"Guest deleted successfully!"<<endl;
                    }
                    else{
                        cout<<"No such Guest exists!"<<endl;
                    }
                }
                else if(choice == 3){
                    int ind;
                    cout<<"Enter Guest index to edit: "; cin>>ind;
                    if(ind>=1 && ind<=guests.size()){
                        string ng;
                        cout<<"Enter new name: ";
                        cin.ignore();
                        getline(cin,ng);
                        guests[ind-1] = ng;
                    }
                    else{
                        cout<<"Invalid index!"<<endl;
                    }
                }
                else{
                    cout<<"Wrong choice!"<<endl;
                }
            }
            else{
                break;
            }
        }

        eventName = newname;
        eventDate = date;
        budget = bud;
    }

    

    virtual void viewEventDetailsForParticipant(){
        cout<<"|"<<"Event Name: "<<eventName<<endl;
        cout<<"|"<<"Event Type: "<<eventType<<endl;
        cout<<"|"<<"Event Date: "<<eventDate<<endl;
        cout<<"|"<<"Event ID: "<<eventID<<endl;
    }


    virtual void saveToFile(ofstream &fout){
        fout<<eventID<<','<<eventName<<','<<eventDate<<','<<budget<<','<<eventType;
        
    }
    virtual void loadFromFile(istringstream &ss){
        string token;
        getline(ss,token,',');
        int num = stoi(token);
        for(int i = 0; i<num; i++){
            getline(ss,token,',');
            guests.push_back(token);
        }
    }
};

class Competition : public Event {
private:
    double prize;
public:
    Competition(int id, string name, string date, double bud, double p, string et) : Event(id, name, date, bud, et), prize(p) {}

    void viewEventDetails() {
        Event::viewEventDetails();
        cout << "Prize: " << prize << endl;
    }
    
    void viewEventDetailsForParticipant(){
        Event::viewEventDetailsForParticipant();
        cout<<"|Prize: "<<prize<<endl;
    }

    void editEventDetails() override{
        Event::editEventDetails();
        double newprize = prize;
        int ff;
        cout<<"Enter 1 to edit prize otherwise 0 to continue: "; cin>>ff;
        if(ff == 1){
            cout<<"Enter new prize: "; cin>>newprize;
            ff = 0;
        }
        prize = newprize;
    }


    void saveToFile(ofstream &fout) override{
        Event::saveToFile(fout);
        fout<<','<<prize<<','<<guests.size();
        for(int i = 0; i<guests.size(); i++){
            fout<<','<<guests[i];
        }
        fout<<endl;
    }
    
};

class Program : public Event {
private:
    string programType;
public:
    Program(int id, string name, string date, double bud, string type, string et) : Event(id, name, date, bud, et), programType(type) {}

    void viewEventDetails() {
        Event::viewEventDetails();
        cout << "Program Type: " << programType << endl;
    }
    
    void viewEventDetailsForParticipant(){
        Event::viewEventDetailsForParticipant();
        cout<<"|Program Type: "<<programType<<endl;
    }

    void editEventDetails() override{
        Event::editEventDetails();
        string newprogtype = programType;
        int ff;
        cout<<"Enter 1 to edit program type otherwise 0 to continue: "; cin>>ff;
        if(ff == 1){
            cout<<"Enter new program type: ";
            cin.ignore();
            getline(cin,newprogtype);
            ff = 0;
        }
        programType = newprogtype;
    }


    void saveToFile(ofstream &fout) override{
        Event::saveToFile(fout);
        fout<<','<<programType<<','<<guests.size();
        for(int i = 0; i<guests.size(); i++){
            fout<<','<<guests[i];
        }
        fout<<endl;
    }

};

class Session : public Event {
private:
    string speaker;
public:
    Session(int id, string name, string date, double bud, string spk, string et) : Event(id, name, date, bud, et), speaker(spk) {}

    void viewEventDetails() {
        Event::viewEventDetails();
        cout << "Speaker: " << speaker << endl;
    }
    
    void viewEventDetailsForParticipant(){
        Event::viewEventDetailsForParticipant();
        cout<<"|Speaker: "<<speaker<<endl;
    }

    void editEventDetails() override{
        Event::editEventDetails();
        string newspkr = speaker;
        int ff;
        cout<<"Enter 1 to edit speaker otherwise 0 to continue: "; cin>>ff;
        if(ff == 1){
            cout<<"Enter new speaker: ";
            cin.ignore();
            getline(cin,newspkr);
            ff = 0;
        }
        speaker = newspkr;
    }



    void saveToFile(ofstream &fout) override{
        Event::saveToFile(fout);
        fout<<','<<speaker<<','<<guests.size();
        for(int i = 0; i<guests.size(); i++){
            fout<<','<<guests[i];
        }
        fout<<endl;
    }

};



class EventManager {
private:
    vector<Event*> events;
    vector<User*> users;
    vector<Participant*> participants;
    vector<Admin*> admins;
public:
    void addUser(User* user) {
        if(user->getUserType() == "Participant"){
            Participant* p = new Participant(user->getUserID(), user->getUserName(), user->getUserEmail(), user->getUserPassword(), user->getUserType());

            participants.push_back(p); 
        }
        if(user->getUserType() == "Admin"){
            Admin* a = new Admin(user->getUserID(), user->getUserName(), user->getUserEmail(), user->getUserPassword(), user->getUserType());

            admins.push_back(a); 
        }

        users.push_back(user);
    }
    void displayAllUsers(){
        for(auto it: users){
            decor();
            it->viewProfile();
        }
        decor();
    }

    void addEvent(Event* event) {
        events.push_back(event);
    }

    bool deleteEventById(int eid) {

        for(auto it = events.begin(); it != events.end(); it++){
            if((*it)->getEventID() == eid){
                delete *it;
                events.erase(it);
                for(auto jt: users){
                    jt->cancelEvent(eid);
                }
                return true;
            }
        }
        return false;
    }

    void displayAllEvents(){
        for(auto it: events){
            decor();
            it->viewEventDetails();
        }
        decor();
    }



    User* findUser(string userEmail) {
        for (User* user : users) {
            if (user->getUserEmail() == userEmail) {
                return user;
            }
        }
        return nullptr;
    }
    User* findUserId(int userID) {
        for (User* user : users) {
            if (user->getUserID() == userID) {
                return user;
            }
        }
        return nullptr;
    }

    Event* findEventId(int eventID) {
        for (Event* event : events) {
            if (event->getEventID() == eventID) {
                return event;
            }
        }
        return nullptr;
    }
    vector<Event*> findEvents(string etype){
        vector<Event*>v;
        for(auto it: events){
            if(it->getEventType() == etype) v.push_back(it);
        }
        return v;
    }

    
    
    void saveData(){
        ofstream userfile("users.txt");
        for(auto it: users){
            it->saveToFile(userfile);
        }
        userfile.close();

        ofstream eventfile("events.txt");
        for(auto it: events){
            it->saveToFile(eventfile);
        }
        eventfile.close();
    }

    void loadData(){
        ifstream userfile("users.txt");
        string line;
        while(getline(userfile,line)){
            // cout<<line<<endl;
            // continue;
            User* user = NULL;
            int id;
            string email, name, password, ut;
            istringstream ss(line);
            string token;

            getline(ss,token,',');
            id = stoi(token);
                
            getline(ss,email,',');
            getline(ss,name,',');
            getline(ss,password,',');
            getline(ss,ut,',');

            // cout<<id<<" "<<email<<" "<<name<<" "<<password<<" "<<ut<<endl;

            if(line.find("Admin")==string::npos){
                user = new Participant(id,name,email,password,ut);
                user->loadFromFile(ss);
                // cout<<id<<" "<<email<<" "<<name<<" "<<password<<" "<<ut<<" "<<x<<" "<<y<<" "<<z<<endl;
            }
            else{
                user = new Admin(id,name,email,password,ut);
            }
            
            users.push_back(user);
        }
        userfile.close();

        ifstream eventfile("events.txt");
        while(getline(eventfile,line)){
            Event* event = NULL;
            int eid;
            string ename, edate, etype;
            double ebud;
            

            istringstream ss(line);
            string token;
            getline(ss,token,',');
            eid = stoi(token);

            getline(ss,ename,',');
            getline(ss,edate,',');

            getline(ss,token,',');
            ebud = stod(token);

            getline(ss,etype,',');

            if(etype == "Competition"){
                int eprize;
                getline(ss,token,',');
                eprize = stod(token);

                event = new Competition(eid,ename,edate,ebud,eprize,etype);
            }
            else if(etype == "Program"){
                string pt;
                getline(ss,pt,',');

                event = new Program(eid,ename,edate,ebud,pt,etype);
            }
            else{
                string spk;
                getline(ss,spk,',');

                event = new Session(eid,ename,edate,ebud,spk,etype);
            }
            event->loadFromFile(ss);

            events.push_back(event);
        }
        eventfile.close();
    }
};


int uniqueIdGenerator(){
    int suffix = rand()%10000;
    return suffix;
}

void participantDashboard(User* user, EventManager ems){
// --------------------------------------------------------------------------------------------------------------
// dynamic_cast is used to typecast one class to another. Here I've casted User* user to Participant* as I'm sure that user is a Participant and can be sucessfully casted.
// --------------------------------------------------------------------------------------------------------------
    Participant* puser = dynamic_cast<Participant*>(user);
    decor();
    cout<<"Welcome Participant! Here is your profile: "<<endl;
    puser->viewProfile();
    decor();

    int choice;
    while(1){
        decor();
        cout<<"1. Show all events"<<endl;
        cout<<"2. Register for an event"<<endl;
        cout<<"3. View registered events"<<endl;
        cout<<"4. Edit profile"<<endl;
        cout<<"5. Cancel registration"<<endl;
        cout<<"6. Log out"<<endl;
        cin>>choice;
        switch (choice){
            case 1 :{
                decor();

                cout<<"Competitions: "<<endl<<endl;
                vector<Event*>v = ems.findEvents("Competition");
                if(v.empty()) cout<<"No Competitions!"<<endl<<endl;
                else{
                    for(auto it: v) {it->viewEventDetails(); cout<<endl;}
                }

                cout<<"Programs: "<<endl<<endl;
                v = ems.findEvents("Program");
                if(v.empty()) cout<<"No Programs!"<<endl<<endl;
                else{
                    for(auto it: v) {it->viewEventDetails(); cout<<endl;}
                }

                cout<<"Sessions: "<<endl<<endl;
                v = ems.findEvents("Session");
                if(v.empty()) cout<<"No Sessions!"<<endl<<endl;
                else{
                    for(auto it: v) {it->viewEventDetails(); cout<<endl;}
                }

                break;
            }
            case 2 :{
                decor();

                int eid;
                cout<<"Enter event ID to register: "; cin>>eid;
                vector<int>vid = puser->viewRegisteredEvents();
                int flag = 0;
                for(auto it: vid){
                    if(it==eid){
                        cout<<"Already registered!"<<endl;
                        flag = 1;
                        break;
                    }
                }
                if(flag) break;
                puser->registerEvent(eid);
                cout<<"Successfully registered!"<<endl;

                break;
            }
            case 3 :{
                decor();

                vector<int>vid = puser->viewRegisteredEvents();
                if(vid.empty()){
                    cout<<"No registrations yet!"<<endl;
                    break;
                }
                for(auto it: vid){
                    Event* regevent = ems.findEventId(it);
                    regevent->viewEventDetailsForParticipant();
                    cout<<endl;
                }

                break;
            }
            case 4 :{
                decor();

                user->editProfile();
                cout<<"Please re-login!"<<endl;
                return;

                break;
            }
            case 5 :{
                decor();

                int eid;
                cout<<"Enter event ID to cancel registration: "; cin>>eid;
                if(user->cancelEvent(eid)) cout<<"Event successfully unregistered!"<<endl;
                else cout<<"No such event registered!"<<endl;

                break;
            }
            case 6 :{
                decor();
                
                cout<<"Successfully Logged Out"<<endl;
                return;
            }
            default:
                break;
        }
    }

}

void adminDashboard(User* user, EventManager &ems){
    decor();
    Admin* auser = dynamic_cast<Admin*>(user);
    auser->viewProfile();

    int choice;
    while(1){
        decor();
        cout<<"1. Show all events"<<endl;
        cout<<"2. Edit an event"<<endl;
        cout<<"3. Add an event"<<endl;
        cout<<"4. Delete an event"<<endl;
        cout<<"5. Edit profile"<<endl;
        cout<<"6. Log out"<<endl;
        cin>>choice;
        switch (choice){
            case 1 :{
                decor();

                cout<<"Competitions: "<<endl<<endl;
                vector<Event*>v = ems.findEvents("Competition");
                if(v.empty()) cout<<"No Competitions!"<<endl<<endl;
                else{
                    for(auto it: v) {it->viewEventDetails(); cout<<endl;}
                }

                cout<<"Programs: "<<endl<<endl;
                v = ems.findEvents("Program");
                if(v.empty()) cout<<"No Programs!"<<endl<<endl;
                else{
                    for(auto it: v) {it->viewEventDetails(); cout<<endl;}
                }

                cout<<"Sessions: "<<endl<<endl;
                v = ems.findEvents("Session");
                if(v.empty()) cout<<"No Sessions!"<<endl<<endl;
                else{
                    for(auto it: v) {it->viewEventDetails(); cout<<endl;}
                }

                break;
            }
            case 2 :{
                decor();

                int eid;
                cout<<"Enter event ID to edit: "; cin>>eid;

                Event* event = ems.findEventId(eid);
                if(event == NULL){
                    cout<<"No such event exists!"<<endl;
                    break;
                }
                
                event->editEventDetails();
                cout<<"Event details updated!"<<endl;

                break;
            }
            case 3 :{
                decor();

                int id, budget;
                string name, date, eventType;

                while(1){
                    id = uniqueIdGenerator();
                    if(!ems.findEventId(id)) break;
                }
                
                Event* e = NULL;
                
                cout << "Enter Event Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Event Date: "; getline(cin, date);
                cout << "Enter Event Budget: "; cin >> budget;
                cout << "Enter Event Type (Competition/Program/Session): "; cin >> eventType;
                
                if(eventType == "Competition") {
                    double prize;
                    cout << "Enter Prize: "; cin >> prize;
                    e = new Competition(id, name, date, budget, prize, eventType);
                    ems.addEvent(e);
                } else if(eventType == "Program") {
                    string progtype; 
                    cout<<"Enter program type: ";
                    cin.ignore(); getline(cin,progtype);
                    e = new Program(id, name, date, budget, progtype, eventType);
                    ems.addEvent(e);
                } else if(eventType == "Session") {
                    string speaker;
                    cout<<"Enter speaker name: ";
                    cin.ignore(); getline(cin,speaker);
                    e = new Session(id, name, date, budget, speaker, eventType);
                    ems.addEvent(e);
                } else {
                    cout << "Invalid event type!" << endl;
                    break;
                }
                int num; cout<<"Number of Guests: "; cin>>num;
                cin.ignore();
                string g;
                for(int i = 0; i<num; i++){
                    cout<<"Enter guest name: ";
                    getline(cin,g);
                    e->addGuest(g);
                }

                cout << "Event added successfully!" << endl;
                break;
            }
            case 4 :{
                decor();

                int eid;
                cout<<"Enter event ID to delete: "; cin>>eid;
                if(ems.deleteEventById(eid)) cout<<"Event deleted successfully!"<<endl;
                else cout<<"No such event exists!"<<endl;

                break;
            }
            case 5 :{
                decor();

                user->editProfile();
                cout<<"Pleaser re-login!"<<endl;
                return;

                break;
            }
            case 6 :{
                decor();
                
                cout<<"Successfully Logged Out"<<endl;
                return;
            }
            default:
                break;
        }
    }
}

int main(){
    EventManager ems;
    ems.loadData();
    // Competition* c1 = new Competition(1,"codecon","23-10-2003",5000.0,500.0,"Competition");

    Admin* a1 = new Admin(69,"metro","metro@gmail.com","metro23","Admin");
    ems.addUser(a1);

    // ems.addEvent(c1);
    // ems.addEvent(p1);
    // ems.addEvent(s1);

    int flag = 1;
    while(flag){
        decor();
        int choice;
        cout<<"1. Log In"<<endl;        
        cout<<"2. Sign Up"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter Your Choice: "; cin>>choice;

        switch (choice)
        {
            case 1: {
                decor();
                string email; string password;
                cout<<"Enter email: "; cin>>email;
                cout<<"Enter password: "; cin>>password;
                User* user = ems.findUser(email);

                if(!user){
                    cout<<"No such user exists!"<<endl;
                    break;
                }
                if(user->getUserPassword() != password){
                    cout<<"Wrong Password!"<<endl;
                    break;
                }

                cout<<"You're logged in as "<<user->getUserName()<<"!"<<endl;
                if(user->getUserType() == "Participant"){
                    participantDashboard(user,ems);
                }
                else if(user->getUserType() == "Admin"){
                    adminDashboard(user,ems);
                    
                }

                break;
            }
            
            case 2: {
                decor();
                string name, email, password;
                cout<<"Enter Name: "; cin.ignore(); getline(cin,name);
                cout<<"Enter email: "; cin>>email;
                cout<<"Enter password: "; cin>>password;
                string ut = "Participant";
                int uid;
                while(1){
                    uid = uniqueIdGenerator();
                    if(!ems.findUserId(uid)) break;
                }
                Participant* p = new Participant(uid, name, email, password, ut);
                ems.addUser(p);
                cout<<"Account successfully created!"<<endl;
                
                participantDashboard(p,ems);

                break;
            }

            case 3: {
                decor();
                cout<<endl;
                cout<<"Adieu!"<<endl;
                decor();
                flag = 0;
                break;
            }

            default:
                break;

        }

    }
    
    ems.saveData();

    return 0;
}