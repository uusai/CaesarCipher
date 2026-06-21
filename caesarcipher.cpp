#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

struct LetterAndValue{
    int Value;
    char Letter;
    LetterAndValue& operator++(int){
        LetterAndValue temp = *this;
        Value++;
        return *this;
    }
    LetterAndValue(){
        Value = 0;
        Letter = '-';
    }
    bool Set_Letter(char Letter){
        this->Letter = Letter;
        return true;
    }
    int Get_Value(){
        return Value;
    }
    char Get_Letter(){
        return Letter;
    }
    void Print(){
        cout << Letter << " val: " << Value;
    }
};

class CaesarCipher{
    static int Value;
public:
    static string Encrypt(string text, int Value){
        string Output;
        for(int i = 0; i < text.size(); i++){
            if(text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?'){
                Output.push_back(text[i]);
                continue;
            } 
            int a = text[i];
            for(int j = 0; j < Value; j++){
                if(isalpha(!text[i])){
                    if(a > 57){
                        a = 48;
                    }
                }
                if(isupper(text[i])){
                    if(a > 90){
                        a = 65;
                    }
                }
                if(islower(text[i])){
                    if(a > 122){
                        a = 97;
                    }
                }
                a++;
            }
            Output.push_back(static_cast<char>(a));
        }
        return Output;
    }
    static string Decipher(string text, int Value){
        string Output;
        for(int i = 0; i < text.size(); i++){
            if(text[i] == ' ' || text[i] == '.' || text[i] == ','){
                Output.push_back(text[i]);
                continue;
            } 
            int a = text[i];
            for(int j = 0; j < Value; j++){
                a--;
                if(isalpha(!text[i])){
                    if(a < 48){
                        a = 57;
                    }
                }
                if(isupper(text[i])){
                    if(a < 65){
                        a = 90;
                    }
                }
                if(islower(text[i])){
                    if(a < 97){
                        a = 122;
                    }
                }
            }
            Output.push_back(static_cast<char>(a));
        }
        return Output;
    }
};

class AutoEncrypt{
    vector<LetterAndValue> value = {};
public:
    AutoEncrypt(string text){
        for(int i = 0; i < text.size(); i++){
            if(text[i] == ' ' || text[i] == '.' || text[i] == ',') continue;
            bool Check = false;
            for(int j = 0; j < value.size(); j++){
                if(value[j].Get_Letter() == text[i]){
                    value[j]++;
                    Check = true;
                    break;
                }
            }
            if(Check == false){
                    value.emplace_back();
                    value[value.size()-1]++;
                    value[value.size()-1].Set_Letter(text[i]);
            }
        }
        sort(value.begin(), value.end(), [](const LetterAndValue& a, const LetterAndValue& b) {
            return a.Value > b.Value; 
        });
    }
    void Print(){
        for(int i = 0; i < value.size(); i++){
            value[i].Print();
            cout << '\n';
        }
    }
};

int main(){
    //cout << CaesarCipher::Encrypt("Hello World! 3232", 3);
    string text = "Hi. My names John Miller, Im from Francisco.";
    //cout << text.size();
    AutoEncrypt A(text);
    A.Print();
    // while(true){
    //     string Command;
    //     cin >> Command;
    //     if(Command == "/Exit") return 0;
    //     else if(Command == "/Encrypt"){
    //         cout << '\n' << "Input text: ";
    //         string text;
    //         cin >> text;
    //         cout << "Input value: ";
    //         int value;
    //         cin >> value;
    //         cout << '\n' << CaesarCipher::Encrypt(text,value);
    //     }
    // }
}