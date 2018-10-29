#include "AgendaUI.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
using namespace std;
/*std::string m_userName;
  std::string m_userPassword;
  AgendaService m_agendaService;*/
void AgendaUI::OperationLoop(void){
	startAgenda();
	while(1){
		cout<<"----------------------Agenda--------------------------------"<<endl;
		cout<<"Action :"<<endl;
		cout<<"l    - log in Agenda by user name and password"<<endl;
		cout<<"r    - register an Agenda account"<<endl;
		cout<<"q    - quit Agenda"<<endl;
		cout<<"-------------------------------------------------------------"<<endl;
		cout<<endl;
		cout<<"Agenda :~$ ";
		executeOperation(getOperation());
	}
}
AgendaUI::AgendaUI(){
	m_userName="";
	m_userPassword="";
}
void AgendaUI::startAgenda(void){
	m_agendaService.startAgenda();
}
std::string AgendaUI::getOperation(){
	string order;
	cin>>order;
	return order;
}
bool AgendaUI::executeOperation(const std::string &t_operation){
	if(t_operation=="l"){
		userLogIn();
	}
	else if(t_operation=="r"){
		userRegister();
	}
	else if(t_operation=="q"){
		quitAgenda();
	}
}
void AgendaUI::userLogIn(void){
	cout<<endl;
	cout<<"[log in] [username] [password]"<<endl;
	string m_name, m_password;
	cout<<"[log in] ";
	cin>>m_name>>m_password;
	m_userName=m_name;
	m_userPassword=m_password;
	if(m_agendaService.userLogIn(m_name, m_password)){
		cout<<"[log in] succeed!"<<endl;
		cout<<endl;
		cout<<"-------------------------------------------------------"<<endl;
		cout<<"Action :"<<endl;
		cout<<"o    - log out Agenda"<<endl;
		cout<<"dc   - delete Agenda account"<<endl;
		cout<<"lu   - list all Agenda user"<<endl;
		cout<<"cm   - create a meeting"<<endl;
		cout<<"amp  - add meeting participator"<<endl;
		cout<<"rmp  - remove meeting participator"<<endl;
		cout<<"rqm  - request to quit meeting"<<endl;
		cout<<"la   - list all meeting"<<endl;
		cout<<"las  - list all sponsor meeting"<<endl;
		cout<<"lap  - list all participator meeting"<<endl;
		cout<<"qm   - query meeting by title"<<endl;
		cout<<"qt   - query meeting by time interval"<<endl;
		cout<<"dm   - delete meeting by title"<<endl;
		cout<<"da   - delete all meetings"<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		while(1){
			cout<<endl;
			cout<<"Agenda@"<<m_name<<" :~# ";
			string m=getOperation();
			if(m=="o"){
				userLogOut();
				break;
			}
			else if(m=="dc"){
				deleteUser();
				break;
			}
			else if(m=="lu"){
				listAllUsers();
			}
			else if(m=="cm"){
				createMeeting();
			}
			else if(m=="amp"){
				addMeetingParticipator();
			}
			else if(m=="rmp"){
				removeMeetingParticipator();
			}
			else if(m=="rqm"){
				quitMeeting();
			}
			else if(m=="la"){
				listAllMeetings();
			}
			else if(m=="las"){
				listAllSponsorMeetings();
			}
			else if(m=="lap"){
				listAllParticipateMeetings();
			}
			else if(m=="qm"){
				queryMeetingByTitle();
			}
			else if(m=="qt"){
				queryMeetingByTimeInterval();
			}
			else if(m=="dm"){
				deleteMeetingByTitle();
			}
			else if(m=="da"){
				deleteAllMeetings();
			}
		}
	}
	else{
		cout<<"[log in] Password error or user doesn't exist"<<endl;
	}
}
void AgendaUI::userRegister(void){
	cout<<"[register] [username] [password] [email] [phone]"<<endl;
	cout<<"[register] ";
	string m_name,m_password,m_email,m_phone;
	cin>>m_name>>m_password>>m_email>>m_phone;
	if(m_agendaService.userRegister(m_name, m_password, m_email, m_phone)){
		cout<<"[register] succeed"<<endl;
	}
	else{
		cout<<"[register] This username has been registered!"<<endl;
	}
}
void AgendaUI::userLogOut(void){
	
}
void AgendaUI::quitAgenda(void){
	exit(0);
}
void AgendaUI::deleteUser(void){
	if(m_agendaService.deleteUser(m_userName, m_userPassword)){
		cout<<"[delete agenda account] succeed!"<<endl;
	}
	else{
		cout<<"[delete agenda account] error!"<<endl;
	}
}
void AgendaUI::listAllUsers(void){
	cout<<endl;
	cout<<"[list all users]"<<endl;
	cout<<endl;
	cout<<left;
	cout<<setw(20)<<"name"<<setw(20)<<"email"<<setw(20)<<"phone"<<endl;
	list<User> temp=m_agendaService.listAllUsers();
	list<User>::iterator it=temp.begin();
	while(it!=temp.end()){
		cout<<setw(20)<<(*it).getName()<<setw(20)<<(*it).getEmail()<<setw(20)<<(*it).getPhone()<<endl;
		it++;
	}
}
void AgendaUI::createMeeting(void){
	cout<<endl;
	cout<<"[create meeting] [the number of participator]"<<endl;
	int num=0;
	cout<<"[create meeting] ";
	cin>>num;
	vector<string> par;
	for(int i=0;i<num;i++){
		cout<<"[create meeting] [please enter the participator "<<i+1<<"]"<<endl;
		cout<<"[create meeting] ";
		string m_name;
		cin>>m_name;
		par.push_back(m_name);
	}
	string m_title, m_sT, m_eT;
	cout<<"[create meeting] [title][start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"<<endl;
	cout<<"[create meeting] ";
	cin>>m_title>>m_sT>>m_eT;
	if(m_agendaService.createMeeting(m_userName, m_title, m_sT, m_eT, par)){
		cout<<"[create meeting] succeed!"<<endl;
	}
	else{
		cout<<"[create meeting] error!"<<endl;
	}
}
void AgendaUI::addMeetingParticipator(void){
	cout<<endl;
	cout<<"[add participator] [meeting title] [participator username]"<<endl;
	string m_tL, m_nM;
	cout<<"[add participator] ";
	cin>>m_tL>>m_nM;
	if(m_agendaService.addMeetingParticipator(m_userName,m_tL,m_nM)){
		cout<<"[add participator] succeed!"<<endl;
	}
	else{
		cout<<"[add participator] error!"<<endl;
	}
}
void AgendaUI::removeMeetingParticipator(void){
	cout<<endl;
	cout<<"[remove participator] [meeting title] [participator username]"<<endl;
	cout<<"[remove participator] ";
	string m_tL, m_nM;
	cin>>m_tL>>m_nM;
	if(m_agendaService.removeMeetingParticipator(m_userName,m_tL,m_nM)){
		cout<<"[remove participator] succeed!"<<endl;
	}
	else{
		cout<<"[remove participator] error!"<<endl;
	}
}
void AgendaUI::quitMeeting(void){
	cout<<endl;
	cout<<"[quit meeting] [meeting title]"<<endl;
	cout<<"[quit meeting] ";
	string m_tL;
	cin>>m_tL;
	if(m_agendaService.quitMeeting(m_userName, m_tL)){
		cout<<"[quit meeting] succeed!"<<endl;
	}
	else{
		cout<<"[quit meeting] error!"<<endl;
	}
}
void AgendaUI::listAllMeetings(void){
	cout<<endl;
	cout<<"[list all meetings]"<<endl;
	cout<<endl;
	cout<<left;
	cout<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(15)<<"start time"<<setw(15)<<"end time"<<setw(15)<<"participators"<<endl;
	list<Meeting> temp=m_agendaService.listAllMeetings(m_userName);
	printMeetings(temp);
}
void AgendaUI::listAllSponsorMeetings(void){
	cout<<endl;
	cout<<"[list all sponsor meetings]"<<endl;
	cout<<endl;
	cout<<left;
	cout<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(15)<<"start time"<<setw(15)<<"end time"<<setw(15)<<"participators"<<endl;
	list<Meeting> temp=m_agendaService.listAllSponsorMeetings(m_userName);
	printMeetings(temp);
}
void AgendaUI::listAllParticipateMeetings(void){
	cout<<endl;
	cout<<"[list all participator meetings]"<<endl;
	cout<<endl;
	cout<<left;
	cout<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(15)<<"start time"<<setw(15)<<"end time"<<setw(15)<<"participators"<<endl;
	list<Meeting> temp=m_agendaService.listAllParticipateMeetings(m_userName);
	printMeetings(temp);
}
void AgendaUI::queryMeetingByTitle(void){
	cout<<endl;
	cout<<"[query meeting] [title]:"<<endl;
	cout<<"[query meeting] ";
	string T_name;
	cin>>T_name;
	cout<<left;
	cout<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(15)<<"start time"<<setw(15)<<"end time"<<setw(15)<<"participators"<<endl;
	list<Meeting> temp=m_agendaService.meetingQuery(m_userName, T_name);
	printMeetings(temp);
}
void AgendaUI::queryMeetingByTimeInterval(void){
	cout<<endl;
	cout<<"[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]:"<<endl;
	cout<<"[query meeting] ";
	string S_time, E_time;
	cin>>S_time>>E_time;
	cout<<left;
	cout<<setw(15)<<"title"<<setw(15)<<"sponsor"<<setw(15)<<"start time"<<setw(15)<<"end time"<<setw(15)<<"participators"<<endl;
	list<Meeting> temp=m_agendaService.meetingQuery(m_userName, S_time, E_time);
	printMeetings(temp);
}
void AgendaUI::deleteMeetingByTitle(void){
	cout<<endl;
	cout<<"[delete meeting] [title]"<<endl;
	cout<<"[delete meeting] ";
	string D_title;
	cin>>D_title;
	if(m_agendaService.deleteMeeting(m_userName, D_title)){
		cout<<"[delete meeting] succeed!"<<endl;
	}
	else cout<<"[error] delete meeting fail!"<<endl;
}
void AgendaUI::deleteAllMeetings(void){
	cout<<endl;
	if(m_agendaService.deleteAllMeetings(m_userName)){
		cout<<"[delete all meeting] succeed!"<<endl;
	}
	else cout<<"[error] delete meeting fail!"<<endl;
}
void AgendaUI::printMeetings(const std::list<Meeting> &t_meetings){
	list<Meeting>::const_iterator it=t_meetings.begin();
	while(it!=t_meetings.end()){
		vector<string> par=(*it).getParticipator(); 
		cout<<setw(15)<<(*it).getTitle()<<setw(15)<<(*it).getSponsor()<<setw(15)<<Date::dateToString((*it).getStartDate())<<setw(15)<<Date::dateToString((*it).getEndDate());
		for(int i=0;i<par.size()-1;i++){
			cout<<par[i]<<",";
		}
		cout<<par[par.size()-1]<<endl;
		it++;
	}
}