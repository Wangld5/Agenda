#include "Date.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
using namespace std;
bool is_true(string a){
    for(int i=0;i<4;i++){
        if(a[i]<'0' || a[i]>'9') return false;
    }
    if(a[4]!='-') return false;
    for(int i=5;i<7;i++){
        if(a[i]<'0' || a[i]>'9') return false;
    }
    if(a[7]!='-') return false;
    for(int i=8;i<10;i++){
        if(a[i]<'0' || a[i]>'9') return false;
    }
    if(a[10]!='/') return false;
    for(int i=11;i<13;i++){
        if(a[i]<'0' || a[i]>'9') return false;
    }
    if(a[13]!=':') return false;
    for(int i=14;i<16;i++){
        if(a[i]<'0' || a[i]>'9') return false;
    }
    return true;
}
bool isTrue(int t_day, int t_month, int t_year, int t_hour, int t_minute){
    if(t_minute>59 || t_minute<0) return false;
    else if(t_hour>23 || t_hour<0) return false;
    else if(t_year<1000 || t_year>9999) return false;
    else if(t_month>12 || t_month<=0) return false;
    else if(t_month<=12 && t_month>0){
        switch(t_month){
            case 4:case 6:case 9:case 11:
            if(t_day>30 || t_day<=0) return false;
            case 2:
            if((t_year%4==0 && t_year%100!=0) || t_year%400==0){
                if(t_day>29 || t_day<=0) return false;
            }
            else{
                if(t_day>28 || t_day<=0) return false;
            }
            default:
            if(t_day>31 || t_day<=0) return false;
        }
    }
    return true;
}
Date::Date():m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0){}
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute){
    m_year=t_year;
    m_month=t_month;
    m_day=t_day;
    m_hour=t_hour;
    m_minute=t_minute;
}
Date::Date(const std::string &dateString){
    if(is_true(dateString)){
        int a=0, b=0, c=0, d=0, e=0;
        istringstream temp(dateString);
        char i=0, j=0, k=0, f=0;
        temp>>a>>f>>b>>i>>c>>j>>d>>k>>e;
        m_year=a;
        m_month=b;
        m_day=c;
        m_hour=d;
        m_minute=e;
        if(isTrue(m_day, m_month, m_year, m_hour, m_minute)){}
        else{
            m_year=0;
            m_month=0;
            m_day=0;
            m_hour=0;
            m_minute=0;
        }
    }
    else{
         m_year=0;
        m_month=0;
        m_day=0;
        m_hour=0;
        m_minute=0;
    }
}
int Date::getYear(void) const{
    return m_year;
}
int Date::getMonth(void) const{
    return m_month;
}
int Date::getDay(void) const{
    return m_day;
}
int Date::getHour(void) const{
    return m_hour;
}
int Date::getMinute(void) const{
    return m_minute;
}
void Date::setYear(const int t_year){
    m_year=t_year;
}
void Date::setMonth(const int t_month){
    m_month=t_month;
}
void Date::setDay(const int t_day){
    m_day=t_day;
}
void Date::setHour(const int t_hour){
    m_hour=t_hour;
}
void Date::setMinute(const int t_minute){
    m_minute=t_minute;
}
bool Date::isValid(const Date &t_date){
    if(t_date.m_minute>59 || t_date.m_minute<0) return false;
    else if(t_date.m_hour>23 || t_date.m_hour<0) return false;
    else if(t_date.m_year<1000 || t_date.m_year>9999) return false;
    else if(t_date.m_month>12 || t_date.m_month<=0) return false;
    else if(t_date.m_month<=12 && t_date.m_month>0){
        switch(t_date.m_month){
            case 4:case 6:case 9:case 11:
            if(t_date.m_day>31 || t_date.m_day<=0) return false;
            break;
            case 2:
            if((t_date.m_year%4==0 && t_date.m_year%100!=0) || t_date.m_year%400==0){
                if(t_date.m_day>29 || t_date.m_day<=0) return false;
            }
            else{
                if(t_date.m_day>28 || t_date.m_day<=0) return false;
            }
            break;
            default:
            if(t_date.m_day>30 || t_date.m_day<=0) return false;
            break;          
        }
    }
    return true;
}
Date Date::stringToDate(const std::string &t_dateString){
    if(is_true(t_dateString)){
        Date temp1;
        int a=0, b=0, c=0, d=0, e=0;
        istringstream temp(t_dateString);
        char i=0, j=0, k=0, f=0;
        temp>>a>>f>>b>>i>>c>>j>>d>>k>>e;
        temp1.m_year=a;
        temp1.m_month=b;
        temp1.m_day=c;
        temp1.m_hour=d;
        temp1.m_minute=e;
        if(isTrue(c,b,a,d,e)){
            return temp1;
        }    
        else{
            Date temp2;
            return temp2;
        }
    }
    else {
        Date temp2;
        return temp2;
    }
}
std::string Date::dateToString(const Date &t_date){
    if(isValid(t_date)){
        char* temp;
        temp=(char*)malloc(sizeof(char)*17);
        snprintf(temp,17,"%04d-%02d-%02d/%02d:%02d", t_date.m_year, t_date.m_month, t_date.m_day, t_date.m_hour, t_date.m_minute);
        string a=temp;
        return a;
    }
    else{
        return "0000-00-00/00:00";
    }
}
Date &Date::operator=(const Date &t_date){
    m_year=t_date.m_year;
    m_month=t_date.m_month;
    m_day=t_date.m_day;
    m_hour=t_date.m_hour;
    m_minute=t_date.m_minute;
}
bool Date::operator==(const Date &t_date) const{
    if(m_day==t_date.m_day && m_hour==t_date.m_hour && m_minute==t_date.m_minute && m_month==t_date.m_month && m_year==t_date.m_year)
        return true;
    else return false;
}
bool Date::operator>(const Date &t_date) const{
    if(m_year>t_date.m_year) return true;
    else if(m_year==t_date.m_year && m_month>t_date.m_month) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day>t_date.m_day) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day==t_date.m_day && m_hour>t_date.m_hour) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day==t_date.m_day && m_hour==t_date.m_hour && m_minute>t_date.m_minute) return true;
    else return false; 
}
bool Date::operator<(const Date &t_date) const{
    if(m_year<t_date.m_year) return true;
    else if(m_year==t_date.m_year && m_month<t_date.m_month) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day<t_date.m_day) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day==t_date.m_day && m_hour<t_date.m_hour) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day==t_date.m_day && m_hour==t_date.m_hour && m_minute<t_date.m_minute) return true;
    return false;
}
bool Date::operator>=(const Date &t_date) const{
    if(m_year>t_date.m_year) return true;
    else if(m_year==t_date.m_year && m_month>t_date.m_month) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day>t_date.m_day) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day==t_date.m_day && m_hour>t_date.m_hour) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day==t_date.m_day && m_hour==t_date.m_hour && m_minute>=t_date.m_minute) return true;
    else return false; 
}
bool Date::operator<=(const Date &t_date) const{
    if(m_year<t_date.m_year) return true;
    else if(m_year==t_date.m_year && m_month<t_date.m_month) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day<t_date.m_day) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day==t_date.m_day && m_hour<t_date.m_hour) return true;
    else if(m_year==t_date.m_year && m_month==t_date.m_month && m_day==t_date.m_day && m_hour==t_date.m_hour && m_minute<=t_date.m_minute) return true;
    return false;
}