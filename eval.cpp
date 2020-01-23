//Shiyu Liu, Pledged

#include <string>
#include <map>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
using std::to_string;
using std::stod;


string transfer(string expr) {
	 	if(expr.find("+-")!=string::npos){
		    return expr.substr(0,expr.find("+-"))+"-"+transfer(expr.substr(expr.find("+-")+2));
		}if(expr.find("*-")!=string::npos){
		    return "-"+expr.substr(0,expr.find("*-"))+"*"+transfer(expr.substr(expr.find("*-")+2));
		}if(expr.find("/-")!=string::npos){
		    return "-"+expr.substr(0,expr.find("/-"))+"/"+transfer(expr.substr(expr.find("+-")+2));
		}else if(expr.find("+")!=string::npos){
	    	return expr.substr(0,expr.find("+"))+"-"+transfer(expr.substr(expr.find("+")+1));
	    } else if (expr.find("-")!=string::npos) {
	    	return expr.substr(0,expr.find("-"))+"+"+transfer(expr.substr(expr.find("-")+1));
	    } else {
	    	return expr;
	    }
}

double evalHelper(const std::string &expr) {
	if(expr.find("sqrt(")!=string::npos) {
		size_t pre = expr.find("sqrt(");
		size_t nxt = expr.substr(pre).find(")");
		string num = expr.substr(pre+5,nxt-pre-5);
		string bef = expr.substr(0,pre);
		string aft = expr.substr(nxt+pre+1);
		string calc = std::to_string(pow(stod(num),0.5));
		return evalHelper(bef+calc+aft);
 	} else  if(expr.find("tan(")!=string::npos) {
		size_t pre = expr.find("tan(");
		size_t nxt = expr.substr(pre).find(")");
		string num = expr.substr(pre+4,nxt-pre-4);
		string bef = expr.substr(0,pre);
		string aft = expr.substr(nxt+pre+1);
		return evalHelper(bef+to_string(tan(stod(num)))+aft);
 	} else if (expr.find("sin(")!=string::npos) {
		size_t pre = expr.find("sin(");
		size_t nxt = expr.substr(pre).find(")");
		string num = expr.substr(pre+4,nxt-pre-4);
		string bef = expr.substr(0,pre);
		string aft = expr.substr(nxt+pre+1);
		return evalHelper(bef+to_string(sin(stod(num)))+aft);
 	}  else  if (expr.find("cos(")!=string::npos) {
		size_t pre = expr.find("cos(");
		size_t nxt = expr.substr(pre).find(")");
		string num = expr.substr(pre+4,nxt-pre-4);
		string bef = expr.substr(0,pre);
		string aft = expr.substr(nxt+pre+1);
		return evalHelper(bef+to_string(cos(stod(num)))+aft);
 	}  else if(expr.find("(")!=string::npos) {
		  string withinParenthe = expr.substr(expr.find("(")+1, expr.find(")")-expr.find("(")-1);
		  string before = expr.substr(0, expr.find("("));
		  string after = expr.substr(expr.find(")")+1);
		  string calc = to_string(evalHelper(withinParenthe));
		  return evalHelper(before+calc+after);
	} else {
		if(expr.find("--")!=string::npos) {
			string before = expr.substr(0, expr.find("--"));
			string after = expr.substr(expr.find("--")+2);
			return evalHelper(before)+evalHelper(after);
		} else if(expr.find("+-")!=string::npos) {
			string transfered = transfer(expr);
			return evalHelper(transfered);
		} else if(expr.find("*-")!=string::npos) {
			string transfered = transfer(expr);
			return evalHelper(transfered);
		} else if(expr.find("/-")!=string::npos) {
			string transfered = transfer(expr);
			return evalHelper(transfered);
		} else if(expr.find("+")!=string::npos) {
			string before = expr.substr(0, expr.find("+"));
			string after = expr.substr(expr.find("+")+1);
			return evalHelper(before)+evalHelper(after);
		} else if(expr.find("-")!=string::npos) {
			string before = expr.substr(0,expr.find("-"));
			string after = expr.substr(expr.find("-")+1);
			string transfered = transfer(after);
			if(before.length() ==0) return -evalHelper(transfered);
			else return evalHelper(before)-evalHelper(transfered);
		} else if (expr.find("*")!=string::npos) {
			string before = expr.substr(0,expr.find("*"));
			string after = expr.substr(expr.find("*")+1);
			return evalHelper(before)*evalHelper(after);
		} else if(expr.find("/")!=string::npos) {
			string before = expr.substr(0,expr.find("/"));
			string after = expr.substr(expr.find("/")+1);
			return evalHelper(before)/evalHelper(after);
		} else {
			return std::stod(expr);
		}
	}
}

string transform (string expr, std::map<string, double> vars) {
	std::map<std::string,double>::iterator it = vars.begin();
	while(it!=vars.end()){
		if (expr.find(it->first)!=string::npos){
			while(expr.find(it->first)!=string::npos){
				string bef = expr.substr(0,expr.find(it->first));
				string aft = expr.substr(expr.find(it->first)+it->first.length());
				expr =bef+to_string(it->second)+aft;
			}
			it++;
		} else {
			it++;
		}
	}
	return expr;
}

double eval(const std::string &expr,const std::map<std::string,double> &vars) {
		return evalHelper(transform(expr,vars));
}
