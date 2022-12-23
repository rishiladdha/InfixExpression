#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include <string>
using namespace std;

bool parenthesis_checker(string s){
    stack<char> stack;
    for(int i=0;i<s.length();i++){
        if(s[i]=='('){
            stack.push(s[i]);
        }
        if(s[i]==')'){
            stack.pop();
        }
    }
    if(stack.empty()){
        return 1;
    }
    else{
        return 0;
    }
}

bool isnum(string s){
    for(int i=0;i<s.length();i++){
        if(!isdigit(s[i])){
            return 0;
        }
    }
    return 1;
}

float postfix_eval(vector<string> s){
    stack<float> stack;
    for(int i=0;i<s.size();i++){
        if(isnum(s[i])){
            stack.push(stoi(s[i]));
        }
        else{
            float o2 = stack.top();
            stack.pop();
            float o1 = stack.top();
            stack.pop();

            if(s[i] == "+"){
                stack.push(o1+o2);
            }
            else if(s[i] == "-"){
                stack.push(o1-o2);
            }
            else if(s[i] == "*"){
                stack.push(o1*o2);
            }
            else if(s[i] == "/"){
                stack.push(o1/o2);
            }
            else if(s[i] == "^"){
                stack.push(pow(o1,o2));
            }
        }
    }
    return stack.top();
}

int precedence(char x){
    char ans;
    if(x == '+' or x == '-'){
        ans = 1;
    }
    else if(x == '*' or x == '/'){
        ans = 2;
    }
    else if(x == '^'){
        ans = 3;
    }
    else{
        ans = -1;
    }
    return ans;
}

vector<string> infix_to_postfix(string s){
    s = s+'#';
    stack<char> stack;
    vector<string> sol;

    for(int i=0;i<s.length();i++){

        if(isdigit(s[i])){
            string num;
            for(int j=i;j<s.length();j++){
                if(isdigit(s[j])){
                    num += s[j];
                }
                else{
                    sol.push_back(num);
                    num.clear();
                    break;
                }
                i=j;
            }
        }
        else if(s[i] == '('){
            stack.push(s[i]);
        }
        else if(s[i] == ')'){
            while(!stack.empty() and stack.top() != '('){
                string str1(1,stack.top());
                sol.push_back(str1);
                stack.pop();
            }
            if(!stack.empty()){
                stack.pop();
            }
        }
        else{
            while(!stack.empty() and precedence(stack.top())>precedence(s[i])){
                string str1(1,stack.top());
                sol.push_back(str1);
                stack.pop();
            }
            stack.push(s[i]);
        }
    }
    while(!stack.empty()){
        string str1(1,stack.top());
        sol.push_back(str1);
        stack.pop();
    }
    sol.pop_back();
    return sol;
}

string floatTostring(float num){
    string s = to_string(num);
    return s;
}

int __gcd(int a, int b){
    if (b == 0)
        return a;
    return __gcd(b, a % b);
}
void findFraction(string s)
{
    // Initialize variables
    string be_deci = "",
            af_deci = "",
            reccu = "";

    bool x = true, y = false,
            z = false;

    // Traverse the floating string
    for (int i = 0; i < s.size(); ++i) {

        // Check if decimal part exist
        if (s[i] == '.') {
            x = false;
            y = true;
            continue;
        }

        // Check if recurrence
        // sequence exist
        if (s[i] == '(') {
            z = true;
            y = false;
            continue;
        }

        // Retrieve decimal part
        // and recurrence re sequence
        if (x)
            be_deci += s[i];

        if (y)
            af_deci += s[i];

        if (z) {

            // Traverse the string
            for (; i < s.size()
                   && s[i] != ')';
                   ++i)
                reccu += s[i];
            break;
        }
    }

    // Convert string to integer
    int num_be_deci = stoi(be_deci);
    int num_af_deci = 0;

    // If no recurrence sequence exist
    if (af_deci.size() != 0)
        num_af_deci = stoi(af_deci);

    // Initialize numerator & denominator
    int numr = num_be_deci
               * pow(10, af_deci.size())
               + num_af_deci;

    int deno = pow(10, af_deci.size());

    // No recurring term
    if (reccu.size() == 0) {
        int gd = __gcd(numr, deno);

        // Print the result
        cout << numr / gd << "/"
             << deno / gd;
    }

        // If recurring term exist
    else {

        // Convert recurring term to integer
        int reccu_num = stoi(reccu);

        // reccu.size() is num of
        // digit in reccur term
        int numr1
                = numr
                  * pow(10, reccu.size())
                  + reccu_num;

        int deno1 = deno
                    * pow(10, reccu.size());

        // eq 2 - eq 1
        int res_numr = numr1 - numr,
                res_deno = deno1 - deno;

        int gd = __gcd(res_numr,
                       res_deno);
        // Print the result
        cout << res_numr / gd << "/"
             << res_deno / gd;
    }
}

int main()
{


    string ex;
    cin>>ex;
    if(ex.length()==1){
        if(isdigit(ex[0])){
            cout<<"only one number";
        }
        else{
            cout<<"only operator";
        }
    }
    else if(parenthesis_checker(ex)){
        infix_to_postfix(ex);

        vector<string> ans;
        ans = infix_to_postfix(ex);
        float a = postfix_eval(ans);

        if(a>-2147483647-1 and a<2147483647){
            //string b = floatTostring(a);
            //findFraction(b);
            cout << a;
        }
        else{
            cout<<"not defined"<<endl;
        }
    }
    return 0;
}