#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

struct LetterAndValue{
private:
    int Value;
    char Letter;
public:
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
    int Get_Value() const{
        return Value;
    }
    char Get_Letter() const{
        return Letter;
    }
    void Print(){
        cout << Letter << " val: " << Value;
    }
};

class CaesarCipher{
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
                    if(a > 57) a = 48;
                }
                if(isupper(text[i])){
                    if(a > 90) a = 65;
                }
                if(islower(text[i])){
                    if(a > 122) a = 97;
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
    vector<int> LikelyShift = {}; 
    vector<char> MostPopularLetter = {'e','t','a','o','i','n','s','r','h','l'};
public:
    AutoEncrypt(string text){
        for(int i = 0; i < text.size(); i++){
            if(text[i] == ' ' || text[i] == '.' || text[i] == ',') continue;
            char temp = text[i];
            if(isupper(temp)) temp+=32;
            bool Check = false;
            for(int j = 0; j < value.size(); j++){
                if(value[j].Get_Letter() == temp){
                    value[j]++;
                    Check = true;
                    break;
                }
            }
            if(Check == false){
                    value.emplace_back();
                    value[value.size()-1]++;
                    value[value.size()-1].Set_Letter(temp);
            }
        }
        sort(value.begin(), value.end(), [](const LetterAndValue& a, const LetterAndValue& b) {
            return a.Get_Value() > b.Get_Value(); 
        });
    }
    void ConsiderVariant(){
        for(int i = 0; i < MostPopularLetter.size(); i++){
            LikelyShift.emplace_back(static_cast<int>(value[i].Get_Letter())-static_cast<int>(MostPopularLetter[i]));
        }
    }

    vector<int> GetLikelyShift(){
        return LikelyShift;
    }

    void PrintLikelyShift(){
        for(int i = 0; i < LikelyShift.size(); i++){
            cout << LikelyShift[i] << ' ';
        }
    }
    void Print(){
        for(int i = 0; i < value.size(); i++){
            value[i].Print();
            cout << '\n';
        }
    }
};

int main(){
    string text = "the quick brown fox jumps over the lazy dog while the sun sets behind the distant hills. many people enjoy walking through the forest during autumn when the leaves turn golden and red. some prefer to stay inside and read a good book near a warm fire instead of venturing outside. either way the weather often determines how someone spends their free time on a calm evening.";
    string Crypttext = CaesarCipher::Encrypt(text,7);
    AutoEncrypt A(Crypttext);
    A.ConsiderVariant();
    for(int i = 0; i < A.GetLikelyShift().size(); i++){
        cout << CaesarCipher::Decipher(Crypttext, A.GetLikelyShift()[i]) << '\n';
    }
}