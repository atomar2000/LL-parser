#include<bits/stdc++.h>
using namespace std;
unordered_map<string, vector<string>> prods;
unordered_map<string, set<string>> first;
unordered_map<string, set<string>> follow;
unordered_map<string, set<string>> rprod_lprod;
unordered_map<string , vector<pair<string,string>>> parsing_table; 
unordered_map<string , vector<pair<string,string>>> parsing_table_lprod; 

map<char,int> terminals;
char lambda = '$';

set<string> firstof(string leftprod){
    if(first[leftprod].size() != 0) return first[leftprod];
    for(auto x : prods[leftprod]){
        //cout << "left prod: " << leftprod << " x: " << x << "\n";
        if(x.size() == 1 && x[0] == lambda) first[leftprod].insert("$");
        if(terminals.find(x[0]) == terminals.end() && x[0] != lambda){
            //cout << x[0] << "<- non-terminal found" << "\n";
            string c = "";c += x[0];
            set<string> st = firstof(c);
            for(auto as : st){
                if(as == "$"){
                    for(int i = 1; i < (int)x.size() ; i++){
                          if(terminals.find(x[i]) == terminals.end()){
                    //cout << x[i] << "<- non-terminal found" << "\n";
                    string c = "";c += x[i];;
                    set<string> st = firstof(c);
            for(auto as : st)
            first[leftprod].insert(as);
                }
                else{
                   // cout << x[0] << "<- terminal found" << "\n";
                    string a = ""; a += x[0];
                    first[leftprod].insert(a);
                }

                    }
                }
                else{
                    first[leftprod].insert(as);
                }
            }
        }
        else if(x[0] == lambda){
            if(x.size() == 1) first[leftprod].insert("$");
            else{
            for(int i = 1 ; i < (int)x.size() ; i++){
               // cout << leftprod << " " << x[i] << "<----\n";
                if(terminals.find(x[i]) == terminals.end()){
                   // cout << x[i] << "<- non-terminal found" << "\n";
                    string c = "";c += x[i];;
                    set<string> st = firstof(c);
            for(auto as : st)
            first[leftprod].insert(as);
                }
                else{
                    //cout << x[0] << "<- terminal found" << "\n";
                    string a = ""; a += x[0];
                    first[leftprod].insert(a);
                }
            }
            }
        }
        else{
           // cout << x[0] << "<- terminal found" << "\n";
            string a = ""; a += x[0];
            first[leftprod].insert(a);
        }
    }
    return first[leftprod];
}



int main(){
    vector<string> lambda_prod;
    vector<string> r_prod_check;
    int n_prod;cout << "enter no productions" << "\n";cin >> n_prod;
    vector<string> prod_strings;
    cout << "enter the productions" << "\n";
    for(int i = 0 ; i < n_prod ; i++){
        string bs;cin >> bs;
        prod_strings.push_back(bs);
    } 
    cout << "enter the number of states: " << "\n";
    int n;        
    cin >> n;
    cout << "now enter the states: " << "\n";
    map<char,int> states;
    for(int i = 0 ; i < n ; i++){
        char c;       
        cin >> c;
        states[c]++;
    }
    cout << "enter the number of terminals" << "\n";
    int n1;
    cin >> n1;
    cout << "now enter the terminals" << "\n";
    for(int i = 0 ; i < n1 ; i++){
        char c; cin >> c;
        terminals[c]++;
    }
    cout << "enter the start symbol" << "\n";
    string start_sy;
    cin >> start_sy;
    follow[start_sy].insert("$");
    for(auto prod : prod_strings){ 
    string left = "";
    string right = "";
    vector<string> rprod;
    int i;    
    for(i = 0 ; prod[i] != '-' ; i++ ){
        left += prod[i];
    }
    i+=2;
    for(; i < (int)prod.size() ; i++){
        if(prod[i] == '|'){
            //cout << right << "\n";
            rprod.push_back(right);
            right = "";
        }
        else{    
            right += prod[i];
        }    
}
    rprod.push_back(right);

//cout << left << "<- left production    right production-> ";
for(auto x : rprod){
    //cout << x << " ";
    r_prod_check.push_back(x);
prods[left] = rprod;

for(auto y : x){    
       string sss = "";sss += y; 
        rprod_lprod[sss].insert(left);
    if(y == lambda){
            lambda_prod.push_back(left);
       } 
}
}
//cout << "\n";

}
cout << "\n\n";
//check right sub string

for(auto x : prods){
   // cout << "called for " << x.first << "\n";
    firstof(x.first);
}
/*
cout << "checking left prods " << "\n";
    for(auto x : rprod_lprod) cout << x.first << " " << x.second << "\n";
cout << "*************\n";
*/
int nn = 5;

while(nn--){
    for(auto x : r_prod_check){
        for(int i = 0 ; i < (int)x.size() ;i++){
            string xi = "";xi += x[i];
                //cout<< "analysing: " << xi << "\n";
            if(terminals.find(x[i]) == terminals.end() && x[i] != lambda){
                if(i == (int)x.size()-1){
                        for(auto it : rprod_lprod[xi]){
                        //cout << "b entered here: " << xi <<" left prod =  "<< it << "\n";
                            for(auto y : follow[it]){
                                string nextfollow = "";nextfollow += y;
                                follow[xi].insert(nextfollow);       
                            }
                        }
                }
                else{
                    string nextxi = "";nextxi += x[i+1];
                    if(terminals.find(x[i+1]) != terminals.end()) {
                        follow[xi].insert(nextxi);
                        continue;
                    }
                    bool flagz = false;
                    for(auto y : first[nextxi]){
                        string nextfollow = "";nextfollow += y;
                        follow[xi].insert(nextfollow);
                        if(nextfollow == "$"){
                           flagz = true;
                            for(auto yy : follow[nextxi]){
                                string spt = "";spt += yy;
                                follow[xi].insert(spt);
                            } 
                        }
                    }
                }
            }
        }
    }
}

/*
cout << "inside rprod_lprod" << "\n";
for(auto x : rprod_lprod){
 cout << x.first << " ";
d    for(auto y : x.second){
        cout << y << " " ;
    }
    cout << "\n";
}
cout << "*****************\n";
*/

/*cout << "state" << "   " << "first"  << "\n";
for(auto x : first){
    cout << x.first << "        ";
    for(auto y : x.second) cout << y << " ";
    cout << "\n";
}

cout << "state" << "    " << "follow"  << "\n";
for(auto x : follow){
    cout << x.first << "        ";
    for(auto y : x.second) cout << y << " ";
    cout << "\n";
}
for(auto x : prods){
    cout << x.first << " : ";
    for(auto y : x.second) cout << y << " " ;
    cout << "\n";
}*/
cout << "Non-terminal\t" << "first\t" << "follow\t" << "\n";

for(auto x : prods){
    cout << x.first << "\t\t";
    for(auto y : first[x.first]){
    for(auto xx : y)
 cout << xx << " ";
}cout << "\t";
    for(auto y : follow[x.first])
    for(auto xx : y)
 cout << xx << " ";

cout << "\n";
}
cout << "\n\n";




for(auto x: prods){
        //cout << "analysing: " << x.first << " ";
    for(auto y : x.second){
        //cout << y << "\n";
        vector<pair<string,string>> v;
        string sss = "";sss += y[0];
        if(y.size() == 1 && y[0] == lambda){
           // cout << "lambda  production" << "\n";
            for(auto x2 : follow[x.first]){
                //cout << x2 << " ";  
                v.push_back({x.first,x2});
            }
            //cout << "\n";
        } 

        else if(terminals.find(y[0]) != terminals.end()){
           // cout << sss << "<-- terminal in right's first" << "\n";
            v.push_back({x.first,sss});
        }
        else{
            //cout << "activated" << "\n";
        for(int i = 0 ; i < (int)y.size() ; i++){
            string s = "";s += y[i];
            bool flag = false;
           // cout << y[i] << "<---->" << s << "\n"; 
            for(auto xx : first[s]){
              //  cout << x.first <<"*************hello********* " << xx << "<--" << "\n";
                if(xx[0] == lambda){
                     flag = true;
                }
                else{
                   // cout << xx << " ";
                    v.push_back({x.first,xx});
                }
               // cout << "\n";
            }
            if(!flag) break;
        }
}
        string lef = "";
        lef = lef + x.first +"->"+y;
        string pp = y;
        for(auto xy : v){
            //if(xy.second != "$")
            parsing_table_lprod[pp].push_back(xy);
            parsing_table[lef].push_back(xy); 
        }
    }
}
//    cout << 
    cout << "\n";
    cout << "parse table: - " << "\n";
    for(auto x : parsing_table){
        cout << x.first << "\t:\t";
        for(auto xx : x.second){
            cout <<" { " <<  xx.first << ","<< xx.second << " }\t";
        }
        cout << "\n";
    }
//}
    
    cout << "enter the string to parse" << "\n";
    string input ;
    cin >> input;
    input += "$";
    stack<char> stac;
    stac.push('$');
    stac.push(start_sy[0]);
    int i = 0;
    while(stac.top() != '$' || !stac.empty()){
            cout << "stack top "  << stac.top() << "\n";
        for(auto x : parsing_table_lprod){
                bool flag = false;
            for(auto y : x.second){
                if(y.first[0] == stac.top() && y.second[0] == input[i]){
                    cout << stac.top() << "<-stack top = character on tape-> " << input[i] << " so pop() and pushing:-\n";
                    stac.pop();
                    cout << "-->" << x.first << " : " ;
                    vector<char> temp;
                    
                    for(auto xx : x.first){
                        //cout << xx << " ";
                        temp.push_back(xx);
                    }
                    if(temp.size() == 1 && temp[0] == lambda){
                        cout << "lambda production so only popping" << "\n";;
                    }
                    else{
                    reverse(temp.begin(), temp.end());
                    for(auto xx : temp){
                        cout << xx << " ";
                        stac.push(xx);
                    }
                    cout << "\n";
                    flag = true;
                    }
                    break;
                }
                else if(stac.top() == input[i] && input[i] != '$'){
                    stac.pop();i++;
                    cout << "stack top terminal matches input tape terminal so pop" << "\n";
                    flag = true;
                    break;
                }
                else if(input[i] == '$'){
                    cout << "top of stack is $ and input tape's character is $ so:-" << "\n";
                    cout << "parsed" << "\n";
                    flag = true;
                    return 0;
                    break;
                }
            }
            if(flag) break;
        }
    } 
    





}

