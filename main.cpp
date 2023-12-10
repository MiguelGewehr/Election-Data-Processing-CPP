#include <iostream> 
#include <fstream>  
#include <sstream>  
#include <map>

using namespace std;

int main(){

    ifstream inputStream("candidatos.csv");
    string linha;
    getline(inputStream,linha); // cabeçalho
    cout << linha << endl;
    while (getline(inputStream,linha))
    {
        
    }
    inputStream.close();

    return 0;
}