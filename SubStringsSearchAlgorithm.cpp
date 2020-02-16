 #include <iostream>
 #include <string>
 #include <vector>

 using namespace std;
 void suffixes(string & s,vector<int> & suffix){
     suffix[s.length() - 1] = s.length();
	 int str_len = static_cast<int>(s.length() - 1);
     for(int i=1;i < s.length();i++){
         int len = 0;
         while(str_len - i - len >= 0 && s[str_len - i - len] == s[str_len - len])
             len++;
         suffix[str_len - i] = len;
     }
 }
 
 int main(int argc,char *argv[]){
     string s("ELEMELE");
     vector<int> suffix(s.length(),0);
     suffixes(s,suffix);
     for(int i=0;i<suffix.size();i++){
         cout << suffix[i] << "  ";
     }
     cout << endl;
     return 0;
 }
