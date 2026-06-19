#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class CaesarCipher{
    int Value;
public:
    CaesarCipher( int value){
        Value=value;
    }
    string Encrypt(string text){
        string Output;
        for(int i = 0; i < text.size(); i++){
            if(text[i] == ' ' || text[i] == '.' || text[i] == ','){
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
    string Decipher(string text){
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

int main(){
    CaesarCipher a(6);
    cout << a.Decipher(a.Encrypt("za 2"));
}