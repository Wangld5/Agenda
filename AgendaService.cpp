#include "AgendaService.hpp"
#include <functional>
#include <list>
#include <memory>
#include <string>
using namespace std;
AgendaService::AgendaService(){
	startAgenda();
}
AgendaService::~AgendaService(){
	quitAgenda();
}
bool AgendaService::userLogIn(const std::string &userName, const std::string &password){
	list<User> find=m_storage->queryUser([&](const User& a){ return (a.getName()==userName && a.getPassword()==password);});
	if(find.size()==1) return 1;
	else return 0;
}
bool AgendaService::userRegister(const std::string &userName, const std::string &password,
                    const std::string &email, const std::string &phone){
	User temp(userName,password,email,phone);
	list<User> find=m_storage->queryUser([&](const User &a){
		return (a.getName()==userName && a.getPassword()==password);
	});
	if(find.size()==1) return 0;
	else{
		m_storage->createUser(temp);
		return true;
	}
}
bool AgendaService::deleteUser(const std::string &userName, const std::string &password){
	int find=m_storage->deleteUser([&](const User &a){
		return (a.getName()==userName && a.getPassword()==password);
	});
	if(find==1){
		deleteAllMeetings(userName);
		m_storage->updateMeeting([&](const Meeting &a){
			for(int i=0;i<a.getParticipator().size();i++){
				if(a.getParticipator()[i]==userName) return 1;
			}
			return 0;
		}, [&](Meeting &a){
			a.removeParticipator(userName);
		});
	}
	return find;
}
std::list<User> AgendaService::listAllUsers(void) const{
	list<User> find=m_storage->queryUser([](const User& a){return 1;});
	return find;
}
bool AgendaService::createMeeting(const std::string &userName, const std::string &title,
                     const std::string &startDate, const std::string &endDate,
                     const std::vector<std::string> &participator){
	Date t1(startDate), t2(endDate);
	if(t1>t2 || t1==t2) return 0;
	list<User> find1=m_storage->queryUser([](const User& a){return 1;});
	list<User>::iterator it=find1.begin();
	int T_ch=0;
	while(it!=find1.end()){
		for(int i=0;i<participator.size();i++){
			if((*it).getName()==participator[i]) T_ch=1;
		}
		if(T_ch==0) return 0;
		it++;
	}
	list<Meeting> find2 = listAllMeetings(userName);
	if(find2.size()==0){
		Meeting temp(userName, participator,t1, t2, title);
		m_storage->createMeeting(temp);
		return 1;
	}
	list<Meeting> find_m=m_storage->queryMeeting([&](const Meeting &a){
		if(a.getTitle()==title) return 1;
		else{
			if(a.getStartDate()>=t2 || a.getEndDate()<=t1){
				int num=0;
				for(int i=0;i<participator.size();i++){
					if(userName==participator[i]) num=1;
				}
				if(num==0) return 0;
				else return 1;
			}
			else return 0; 
		}
	});
	if(find_m.size()==1) return 0;
	else{
		Meeting temp(userName, participator,t1, t2, title);
		m_storage->createMeeting(temp);
		return 1;
	}
}
bool AgendaService::addMeetingParticipator(const std::string &userName,
                              const std::string &title,
                              const std::string &participator){
	int find=m_storage->updateMeeting([&](const Meeting& a){
		if(a.getSponsor()==userName && a.getTitle()==title){
			int num=0;
			for(int i=0;i<a.getParticipator().size();i++){
				if(a.getParticipator()[i]==participator) num++;
			}
			if(num) return 0;
			list<Meeting> temp=m_storage->queryMeeting([&](const Meeting &a){
				for(int i=0;i<a.getParticipator().size();i++){
					if(a.getParticipator()[i]==participator) return 1;
				}
				return 0;
			});
			list<Meeting>::iterator it=temp.begin();
			for(it;it!=temp.end();it++){
				if(!(a.getStartDate()>=(*it).getEndDate() || a.getEndDate()<=(*it).getStartDate())) return 0;
			}
			return 1;
		}
		return 0;
	}, [&](Meeting &a){
		a.addParticipator(participator);
	});
	return find;
}
bool AgendaService::removeMeetingParticipator(const std::string &userName,
                                 const std::string &title,
                                 const std::string &participator){
	int find=m_storage->updateMeeting([&](const Meeting& a){
		if(a.getSponsor()==userName && a.getTitle()==title){
			int num=0;
			for(int i=0;i<a.getParticipator().size();i++){
				if(a.getParticipator()[i]==participator) num++;
			}
			if(num) return 1;
		}
		return 0;
	}, [&](Meeting &a){
		a.removeParticipator(participator);
	});
	return find;
}
bool AgendaService::quitMeeting(const std::string &userName, const std::string &title){
	int find=m_storage->updateMeeting([&](const Meeting &a){
		if(a.getTitle()==title){
			for(int i=0;i<a.getParticipator().size();i++){
				if(a.getParticipator()[i]==userName) return 1;
			}
		}
		return 0;
	}, [&](Meeting &a){
		a.removeParticipator(userName);
	});
	return find;
}
std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &title) const{
	list<Meeting> find=m_storage->queryMeeting([&](const Meeting &a){
		return (a.getSponsor()==userName && a.getTitle()==title);
	});
	return find;
}
std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &startDate,
                                  const std::string &endDate) const{
	Date t1(startDate), t2(endDate);
	list<Meeting> find=m_storage->queryMeeting([&](const Meeting &a){
		return (a.getSponsor()==userName && t1<=a.getStartDate() && t2>=a.getEndDate());
	});
	return find;
}
std::list<Meeting> AgendaService::listAllMeetings(const std::string &userName) const{
	list<Meeting> find = m_storage->queryMeeting([&](const Meeting &a){
		int num=0;
		for(int i=0;i<a.getParticipator().size();i++){
			if(a.getParticipator()[i]==userName) num=1;
		}
		if(a.getSponsor()==userName || num==1) return 1;
		else return 0;
	});
	return find;
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string &userName) const{
	list<Meeting> find = m_storage->queryMeeting([&](const Meeting &a){
		return (a.getSponsor()==userName);
	});
	return find;
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(
      const std::string &userName) const{
	list<Meeting> find=m_storage->queryMeeting([&](const Meeting &a){
		if(a.getSponsor()!=userName){
			for(int i=0;i<a.getParticipator().size();i++){
				if(a.getParticipator()[i]==userName) return 1;
			}
		}
		return 0;
	});
	return find;
}
bool AgendaService::deleteMeeting(const std::string &userName, const std::string &title){
	int find=m_storage->deleteMeeting([&](const Meeting& a){return (userName==a.getSponsor() && title==a.getTitle());});
	if(find==1) return 1;
	else return 0;
}

bool AgendaService::deleteAllMeetings(const std::string &userName){
	int find=m_storage->deleteMeeting([&](const Meeting& a){return (userName==a.getSponsor());});
	if(find==1) return 1;
	else return 0;
}

void AgendaService::startAgenda(void){
	m_storage=Storage::getInstance();
}
void AgendaService::quitAgenda(void){
	m_storage->sync();
}