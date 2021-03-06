/*
 * StringOperations.h
 *
 *  Created on: Oct 4, 2012
 *      Author: dan
 */

#ifndef STRINGOPERATIONS_H_
#define STRINGOPERATIONS_H_

#include <sstream>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

namespace string_operations{

using namespace std;

inline bool parse(std::string line, string& name, string& params, string& sufix, string parentses="()"){
	if(parentses.size()>2 || parentses.size()<1) return false;
	char op,cp;
	if(parentses.size()==1) op=cp=parentses[0];
	if(parentses.size()==2){ op=parentses[0]; cp=parentses[1]; }
	int state = 1, pcount=0;
	stringstream sname,sparams, ssufix;
	for(int i=0;i<line.size();i++){
		if(line[i]==op){
			pcount+=1;
			if(parentses.size()==1 && state==2){ state=3; continue; }
			if(state==1 && pcount==1){ state=2; continue; }
		}
		if(line[i]==cp){
			pcount-=1;
			if(state<3 && pcount<0) return false;
			if(state==2 && pcount==0){ state=3; continue; }
		}
		if(state==1) sname<<line[i]; else
		if(state==2) sparams<<line[i]; else
		if(state==3) ssufix<<line[i];
	}
	if(state==2) return false;
	name = sname.str(); params = sparams.str(); sufix = ssufix.str();
	return true;
}

inline int split(std::string line, std::vector<string>& list, string del="()"){
	struct _c{ bool contains(string& p, char c){ for(int i=0;i<p.size();i++) if(p[i]==c) return true; return false; } };
	stringstream word;
	for(int i=0;i<line.size();i++){
		if(_c().contains(del,line[i])){
			list.push_back(word.str()); word.str("");
			continue;
		}
		word<<line[i];
	}
	list.push_back(word.str());
	return list.size();
}
inline std::vector<string> split(std::string line, string del="()"){
	std::vector<string> v;
	split(line, v, del);
	return v;
}

inline string join(const std::vector<string>& list, string del="()"){
	if(list.size()<1) return "";
	stringstream line;
	line << list[0];
	for(int i=1;i<list.size();i++){
		line<<del[(i-1)%del.size()]<<list[i];
	}
	return line.str();
}

inline string trim(const string s){
	string t = s;
	boost::trim(t);
	return t;
}
inline string toLower(const string s){
	string t = s;
	boost::to_upper(t);
	return t;
}
inline string toUpper(const string s){
	string t = s;
	boost::to_upper(t);
	return t;
}

inline bool startWith(const std::string& line, const std::string& t){
	if(t.size()>line.size()) return false;
	if(t.size()==line.size()) return t==line;
	for(int i=0;i<t.size();i++){
		if(line[i]!=t[i]) return false;
	}
	return true;
}
inline bool endWith(const std::string& line, const std::string& t){
	if(t.size()>line.size()) return false;
	if(t.size()==line.size()) return t==line;
	for(int i=t.size()-1;i>=0;i--){
		if(line[i]!=t[i]) return false;
	}
	return true;
}

typedef std::map<std::string,std::string> Arguments;
struct Function{
private:
	bool undef;
public:
	string name;
	string suffix;
	Arguments args;
	Function():undef(true),name(""){}
	string str(){
		if(undef) return "undefined";
		stringstream out;
		out<<name<<"(";
		string d = "";
		for(map<string,string>::iterator i=args.begin();i!=args.end();i++){
			out<<d<<i->first<<"="<<i->second; d=",";
		}
		out<<")"<<suffix;
		return out.str();
	}
	bool isUndefined()const{ return undef; }
	void setDefined(){ undef = false; }
};
inline void trimAll(std::vector<string>& v){
	for(int i=0;i<v.size();i++) v[i]=trim(v[i]);
}
static Function parse(std::string line){
	string name,params,suf;
	if(!parse(line,name,params,suf,"()")) return Function();
	if(trim(name)=="") return Function();
	Function f; f.name=trim(name); f.suffix = trim(suf);
	f.setDefined();
	vector<string> vars = split(params,",");
	for(size_t i=0;i<vars.size();i++){
		if(trim(vars[i])=="") continue;
		vector<string> pair;
		int c = split(vars[i], pair, "=");
		trimAll(pair);
		if(c==1){ stringstream s; s<<"#"<<i; f.args[s.str()] = pair[0]; }
		else if(c==2){ f.args[pair[0]]=pair[1]; }
		else continue;
	}
	return f;
}

static Arguments parse_arguments(std::string line){
	std::map<std::string,std::string> args;
	vector<string> vars = split(line,",");
	for(size_t i=0;i<vars.size();i++){
		if(trim(vars[i])=="") continue;
		vector<string> pair;
		int c = split(vars[i], pair, "=");
		trimAll(pair);
		if(c==1){ stringstream s; s<<"#"<<i; args[s.str()] = pair[0]; }
		else if(c==2){ args[pair[0]]=pair[1]; }
		else continue;
	}
	return args;
}

static int month(char m[]){
	switch(m[0]){
	case 'J':
		switch(m[1]){
		case 'a' : return 1;
		case 'u' :
			switch(m[2]){
			case 'n' : return 6;
			case 'l' : return 7;
			};
			return 0;
		};
		return 0;
	case 'F': return 2;
	case 'M':
		switch(m[2]){
		case 'r' : return 3;
		case 'y' : return 5;
		};
		return 0;
	case 'A':
		switch(m[1]){
		case 'p' : return 4;
		case 'u' : return 8;
		};
		return 0;
	case 'S': return 9;
	case 'O': return 10;
	case 'N': return 11;
	case 'D': return 12;
	};
	return 0;
}
static long buildNumber(){
	std::stringstream d; d<<__DATE__;
	std::stringstream t; t<<__TIME__;
	char s;
	char mon[3]; d>>mon[0]>>mon[1]>>mon[2];
	d>>s;
	long day; d>>day;
	d>>s;
	long yr; d>>yr;
	long h; t>>h; t>>s;
	long m; t>>m; t>>s;
	long sec; t>>sec;
	return sec+60*(m+60*(h+24*(day+31*(month(mon)+12*yr))));
}

}

#endif /* STRINGOPERATIONS_H_ */
