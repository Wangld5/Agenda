#include "Storage.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;
shared_ptr<Storage> Storage::m_instance=NULL;
Storage::Storage():m_dirty(0){
    readFromFile();
}
std::shared_ptr<Storage> Storage::getInstance(void){
    if(m_instance==NULL){
    	m_instance=shared_ptr<Storage>(new Storage());
    }
    return m_instance;
}
void Storage::createUser(const User &t_user){
    m_userList.push_back(t_user);
    m_dirty=1;
}
void Storage::createMeeting(const Meeting &t_meeting){
    m_meetingList.push_back(t_meeting);
    m_dirty=1;
}
std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const{
    list<User> temp;
    list<User>::const_iterator it=m_userList.begin();
    while(it!=m_userList.end()){
        if(filter(*it)){
            User m(*it);
            temp.push_back(m);
        }
        it++;
    }
    return temp;
}
int Storage::updateUser(std::function<bool(const User &)> filter,std::function<void(User &)> switcher){
    int num=0;
    list<User>::iterator it=m_userList.begin();
    while(it!=m_userList.end()){
        if(filter(*it)){
            User temp(*it);
            switcher(temp);
            m_dirty=1;
            num++;
        }
        it++;
    }
    return num;
}
int Storage::deleteUser(std::function<bool(const User &)> filter){
    int num=0;
    list<User>::iterator it=m_userList.begin();
    while(it!=m_userList.end()){
        if(filter(*it)){
            num++;
            m_userList.erase(it++);
            m_dirty=1;
        }
        else it++;
    }
    return num;
}
std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const{
    list<Meeting> temp;
    list<Meeting>::const_iterator it=m_meetingList.begin();
    while(it!=m_meetingList.end()){
        if(filter(*it)){
            Meeting m(*it);
            temp.push_back(m);
        }
        it++;
    }
    return temp;
}
int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,std::function<void(Meeting &)> switcher){
    int num=0;
    int check=0;
    list<Meeting>::iterator it=m_meetingList.begin();
    while(it!=m_meetingList.end()){
        if(filter(*it)){
            switcher(*it);
            m_dirty=1;
            num++;
        }
        it++;
    }
    list<Meeting>::iterator it2=m_meetingList.begin();
    while(it2!=m_meetingList.end()){
        if((*it2).getParticipator().size()==0){
            m_meetingList.erase(it2);
            it2--;
        }
        it2++;
    }
    return num;
}
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter){
    int num=0;
    list<Meeting>::iterator it=m_meetingList.begin();
    while(it!=m_meetingList.end()){
        if(filter(*it)){
            num++;
            m_meetingList.erase(it++);
            m_dirty=1;
        }
        else it++;
    }
    return num; 
}
bool Storage::readFromFile(void){
    ifstream fuck;
    fuck.open("users.csv");
    ifstream suck;
    suck.open("meetings.csv");
    if(!fuck || !suck) return false;
    else{
        while(!fuck.eof()){
            User tem;
            string m;
            getline(fuck, m);
            if(m.size()!=0){
                string::iterator a=m.begin()+1;
                string::iterator b=find(a,m.end(),'"');
                string temp1(a,b);
                tem.setName(temp1);
                a=b+3;
                b=find(a,m.end(),'"');
                string temp2(a,b);
                tem.setPassword(temp2);
                a=b+3;
                b=find(a,m.end(),'"');
                string temp3(a,b);
                tem.setEmail(temp3);
                a=b+3;
                b=find(a,m.end(),'"');
                string temp4(a,b);
                tem.setPhone(temp4);
                m_userList.push_back(tem);
            }
        }
        fuck.close();
        while(!suck.eof()){
            Meeting tem;
            string m;
            getline(suck, m);
            if(m.size()!=0){
                string::iterator a=m.begin()+1;
                string::iterator b=find(a,m.end(),'"');
                string temp1(a,b);
                tem.setSponsor(temp1);
                a=b+3;
                b=find(a,m.end(),'"');
                string temp2(a,b);
                string::iterator fir=temp2.begin();
                string::iterator las=temp2.begin();
                for(int i=0;i<temp2.size();i++){
                    if(temp2[i]=='&'){
                        string name(fir, las+i);
                        fir=las+i+1;
                        tem.addParticipator(name);
                    }
                }
                string name(fir, temp2.end());
                tem.addParticipator(name);
                a=b+3;
                b=find(a,m.end(),'"');
                string temp3(a,b);
                Date f(temp3);
                tem.setStartDate(f);
                a=b+3;
                b=find(a,m.end(),'"');
                string temp4(a,b);
                f=Date::stringToDate(temp4);
                tem.setEndDate(f);
                a=b+3;
                b=find(a,m.end(),'"');
                string temp5(a,b);
                tem.setTitle(temp5);
                m_meetingList.push_back(tem);
            }
        }
        suck.close();
    }
    return true;
}
bool Storage::writeToFile(void){
    ofstream fuck;
    fuck.open("users.csv",ios::out|ios::trunc);
    list<User>::iterator it=m_userList.begin();
    for(it;it!=m_userList.end();it++){
        fuck<<"\""<<(*it).getName()<<"\""<<","<<"\""<<(*it).getPassword()<<"\""<<","<<"\""<<(*it).getEmail()<<"\""<<","<<"\""<<(*it).getPhone()<<"\"";
        fuck<<endl;
    }
    fuck.close();
    ofstream suck;
    suck.open("meetings.csv",ios::out|ios::trunc);
    list<Meeting>::iterator it2=m_meetingList.begin();
    for(it2;it2!=m_meetingList.end();it2++){
        string par;
        for(int i=0;i<(*it2).getParticipator().size()-1;i++){
            par+=(*it2).getParticipator()[i];
            par+="&";
        }
        par+=(*it2).getParticipator()[(*it2).getParticipator().size()-1];
        suck<<"\""<<(*it2).getSponsor()<<"\""<<","<<"\""<<par<<"\""<<","<<"\""<<Date::dateToString((*it2).getStartDate())<<"\""<<","<<"\""<<Date::dateToString((*it2).getEndDate())<<"\""<<","<<"\""<<(*it2).getTitle()<<"\"";
    	suck<<endl;
    }
    suck.close();
}
bool Storage::sync(void){
    if(m_dirty){
        writeToFile();
        m_dirty=0;
    }
    return 1;
}
Storage::~Storage(){
    sync();
}