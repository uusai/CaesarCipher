#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cmath>

using namespace std;

struct LetterAndValue{
private:
    int Value;
    char Letter;
public:
    LetterAndValue(char Letter){
        Value = 1;
        this->Letter = Letter;
    }
    int Up_Value(){
        return ++Value;
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
    static inline const vector<double> ReferenceFrequency = { // Эталонная таблица с частотой появления букв в тексте
        8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
        0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
        2.758, 0.978, 2.360, 0.150, 1.974, 0.074
    };
    static double Divergence(vector<double> a, vector<double> b){
        if(a.size() != b.size()) return -1;
        double Counter = 0;
        for(int i = 0; i < 26; i++){
            Counter+=pow(a[i]-b[i],2);
        }
        return Counter;
    }

public:
    static string Encrypt(string text, int Value){
        string Output;
        for(size_t i = 0; i < text.size(); i++){
            if(text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?'){
                Output.push_back(text[i]);
                continue;
            } 
            int a = text[i];
            for(int j = 0; j < Value; j++){
                a++;
                if(isalpha(!text[i])){
                    if(a > 57) a = 48;
                }
                if(isupper(text[i])){
                    if(a > 90) a = 65;
                }
                if(islower(text[i])){
                    if(a > 122) a = 97;
                }
            }
            Output.push_back(static_cast<char>(a));
        }
        return Output;
    }
    static string Decipher(string text, int Value){
        string Output;
        for(size_t i = 0; i < text.size(); i++){
            if(text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?'){
                Output.push_back(text[i]);
                continue;
            } 
            int a = text[i];
            for(int j = 0; j < Value; j++){
                a--;
                if(isalpha(!text[i])){
                    if(a < 48) a = 57;
                }
                if(isupper(text[i])){
                    if(a < 65) a = 90;
                }
                if(islower(text[i])){
                    if(a < 97) a = 122;
                }
            }
            Output.push_back(static_cast<char>(a));
        }
        return Output;
    }
    static int NumberConvertion(int Number){
        int rem = Number % 26;
        if (rem < 0) rem += 26;
        return rem;
    }
    static vector<double> LetterFrequency(string text){
        vector<double> LetFreq(26);
        int Counter = 0;
        for(size_t i = 0; i < text.size(); i++){
            char temp = text[i];
            if(!isalpha(temp)) continue;
            if(isupper(temp)) temp+=32;
            Counter++;
            LetFreq[temp-97]++;
        }
        if(Counter == 0) return LetFreq;
        for(size_t i = 0; i < LetFreq.size(); i++){
            LetFreq[i] = (LetFreq[i]/static_cast<double>(Counter))*100;
        }
        return LetFreq;
    }
    static int BetterShift(string text){
        int TempBetterShift = 0;
        double Score = Divergence(LetterFrequency(Decipher(text,0)), ReferenceFrequency);
        for(int i = 1; i < 26; i++){
            string tempText = Decipher(text,i);
            double tempScore = Divergence(LetterFrequency(tempText), ReferenceFrequency);
            if(tempScore < Score){
                Score = tempScore;
                TempBetterShift = i;
            }
        }
        return TempBetterShift;
    }
};

class AutoEncrypt{
    vector<LetterAndValue> value = {};
    vector<int> LikelyShift = {}; 
    vector<char> MostPopularLetter = {'e','t','a','o','i','n','s','r','h','l'};
public:
    AutoEncrypt(string text){
        for(size_t i = 0; i < text.size(); i++){
            if(text[i] == ' ' || text[i] == '.' || text[i] == ',') continue;
            char temp = text[i];
            if(isupper(temp)) temp+=32;
            bool Check = false;
            for(size_t j = 0; j < value.size(); j++){
                if(value[j].Get_Letter() == temp){
                    value[j].Up_Value();
                    Check = true;
                    break;
                }
            }
            if(Check == false){
                    value.emplace_back(temp);
            }
        }
        sort(value.begin(), value.end(), [](const LetterAndValue& a, const LetterAndValue& b) {
            return a.Get_Value() > b.Get_Value(); 
        });
        ConsiderVariant();
    }
    void ConsiderVariant(){
        for(size_t i = 0; i < MostPopularLetter.size(); i++){
            LikelyShift.emplace_back(CaesarCipher::NumberConvertion(static_cast<int>(value[i].Get_Letter())-static_cast<int>(MostPopularLetter[i])));
        }
    }

    vector<int> GetLikelyShift(){
        return LikelyShift;
    }
};

int main(){
    string text = "the quick brown fox jumps over the lazy dog while the sun sets behind the distant hills. many people enjoy walking through the forest during autumn when the leaves turn golden and red. some prefer to stay inside and read a good book near a warm fire instead of venturing outside. either way the weather often determines how someone spends their free time on a calm evening.";
    string Crypttext = CaesarCipher::Encrypt(text,7);
    cout << CaesarCipher::Decipher(Crypttext,CaesarCipher::BetterShift(Crypttext));
}