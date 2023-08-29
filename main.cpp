#include<bits/stdc++.h>
#include <openssl/des.h>
using namespace std;
// Caesar Cipher
//plain:fatma
//enc:IDWPD
//dec:CXQJX
//key:3
string caesarCipher(string message, int key, bool encrypt) {
    string result = "";
    int factor = encrypt ? 1 : -1;
    for (int i = 0; i < message.length(); i++) {
        char c = message[i];
        if (isalpha(c)) {
            c = toupper(c);
            c = ((c - 65 + factor * key + 26) % 26) + 65;
        }
        result += c;
    }
    return result;
}

// Playfair Cipher
string playfairCipher(string message, string key, bool encrypt) {
    string result = "";
    int k = 0;
    char matrix[5][5];
    bool used[26] = {false};
    for (int i = 0; i < key.length(); i++) {
        char c = toupper(key[i]);
        if (isalpha(c) && !used[c - 'A']) {
            used[c - 'A'] = true;
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }
    for (int i = 0; i < 26; i++) {
        char c = 'A' + i;
        if (c != 'J' && !used[c - 'A']) {
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }
    for (int i = 0; i < message.length(); i += 2) {
        char a = toupper(message[i]);
        char b = i + 1 < message.length() ? toupper(message[i + 1]) : 'X';
        if (a == b) {
            b = 'X';
            i--;
        }
        int r1, c1, r2, c2;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (matrix[j][k] == a) {
                    r1 = j;
                    c1 = k;
                } else if (matrix[j][k] == b) {
                    r2 = j;
                    c2 = k;
                }
            }
        }
        if (r1 == r2) {
            result += matrix[r1][(c1 + (encrypt ? 1 : -1) + 5) % 5];
            result += matrix[r2][(c2 + (encrypt ? 1 : -1) + 5) % 5];
        } else if (c1 == c2) {
            result += matrix[(r1 + (encrypt ? 1 : -1) + 5) % 5][c1];
            result += matrix[(r2 + (encrypt ? 1 : -1) + 5) % 5][c2];
        } else {
            result += matrix[r1][c2];
            result += matrix[r2][c1];
        }
    }
    return result;
}

// Vigenere Cipher
//plain:wearediscoveredsaveyourself
//cipher:zicvtwqngrzgvtwavzhcqyglmgj
//key:deceptive
string vigenere_encrypt(string message, string key) {
    string result = "";
    for(int i =0; i<message.length(); i++)
    {
        result+= (((toupper(message[i])- 'A') +((toupper(key[i % key.length()]))- 'A')) % 26) + 'A';
    }
    return result;
}
string vigenere_decrypt(string ciphertext,string keyy)
{
    string  plaintext=" ";

    for(int i =0; i<ciphertext.length(); i++)
    {
        plaintext+= (((ciphertext[i])- 'A' - (keyy[i % keyy.length()]- 'A')+26) % 26) + 'A';
    }
    return plaintext;
}

// DES
string desEncrypt(string message, string key, bool encrypt) {
    string result = "";
    DES_cblock keyEncrypt;
    memset(keyEncrypt, 0, 8);
    strncpy((char *)keyEncrypt, key.c_str(), 8);
    DES_key_schedule schedule;
    DES_set_key(&keyEncrypt, &schedule);
    DES_cblock input;
    DES_cblock output;
    for (int i = 0; i < message.length(); i += 8) {
        memset(input, 0, 8);
        memset(output, 0, 8);
        strncpy((char *)input, message.c_str() + i, 8);
        if (encrypt) {
            DES_ecb_encrypt(&input, &output, &schedule, DES_ENCRYPT);
        } else {
            DES_ecb_encrypt(&input, &output, &schedule, DES_DECRYPT);
        }
        result += string((char *)output, 8);
    }
    return result;
}



int main() {
    string message,key;
    cout << "Enter message: ";
    getline(cin, message);
    int choice;
    cout << "Select algorithm:" << "\n";
    cout << "1 Caesar Cipher" << "\n";
    cout << "2 Playfair Cipher" << "\n";
    cout << "3 Vigenere Cipher" << "\n";
    cout << "4 DES" << "\n";
    cout << "Enter choice: ";
    cin >> choice;
    bool encrypt;
    if (choice == 1) {
        int shift;
        cout << "Enter shift amount from 1 to 25: ";
        cin >> shift;
        key = to_string(shift);
        cout << "press 1 for encrypt and 0 for decrypt: ";
        cin >> encrypt;
        message = caesarCipher(message, shift, encrypt);
    } else if (choice == 2) {
        cout << "Enter key about 25 letters: ";
        cin >> key;
        cout << "press 1 for encrypt and 0 for decrypt: ";
        cin >> encrypt;
        message = playfairCipher(message, key, encrypt);
    } else if (choice == 3) {
        cout << "Enter key: ";
        cin >> key;
        cout << "press 1 for encrypt and 0 for decrypt: ";
        cin >> encrypt;
        if(encrypt==0){
            message = vigenere_decrypt(message, key);
        }
        else if(encrypt==1){
            message= vigenere_encrypt(message,key);
        }

    }
    else if (choice == 4) {
        cout << "Enter key (8 characters): ";
        cin >> key;
        cout << "press 1 for encrypt and 0 for decrypt: ";
        cin >> encrypt;
        message = desEncrypt(message, key, encrypt);
    }



    if(encrypt==1){
        cout<<"Encrypted message: "<<message<<"\n";
    }
    else{
        cout<<"Decrypted message: "<<message<<"\n";
    }

    return 0;
}

//    cout << (encrypt? "Encrypted" : "Decrypted") << " message: " << message << "\n";