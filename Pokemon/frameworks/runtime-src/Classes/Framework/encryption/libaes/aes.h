#ifndef AES_H_
#define AES_H_

class AES
{
public:
    typedef unsigned char byte;
    static const int KEY_SIZE = 16;    //    密钥长度为128位
    static const int N_ROUND = 11;
    byte plainText[160];    //    明文
    byte state[16];    //    当前分组。
    byte cipherKey[16];    //    密钥
    byte roundKey[N_ROUND][16];    //轮密钥
    byte cipherText[160];    //密文
    byte SBox[16][16];    //    S盒
    byte InvSBox[16][16];    //    逆S盒  
    void EncryptionProcess();  
    void DecryptionProcess();
    void Round(const int& round);
    void InvRound(const int& round);
    void FinalRound();
    void InvFinalRound();
    void KeyExpansion();
    void AddRoundKey(const int& round);  
    void SubBytes();  
    void InvSubBytes();
    void ShiftRows();  
    void InvShiftRows();
    void MixColumns();  
    void InvMixColumns();
    void BuildSBox();
    void BuildInvSBox();
    void InitialState(const byte* text);
    void InitialCipherText();  
    void InitialplainText();      
    byte GFMultplyByte(const byte& left, const byte& right);
    const byte* GFMultplyBytesMatrix(const byte* left, const byte* right);
public:  
    AES();  
    const byte* Cipher(const byte* text, const byte* key, const int& keySize);  
    const byte* InVCipher(const byte* text, const byte* key, const int& keySize);
};

#endif