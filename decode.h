#include"types.h"

typedef struct Decode
{
    //Arranged Such That Less Padding will be done by compiler
    
    int secreteFileData_Size;
    int SecreteFile_ExtnSize;
    char magicStr[2];             
    char SecreteFile_ExtName[5];
    char* InputImgFle_Name;
    char OutputFileName[20];
    FILE* Input_bmpFile_ptr;
    FILE* OutputFile_ptr;
    

}decode_Info;

Status Create_OPfileName(char* GetName, decode_Info* );

Status OpenFiles(decode_Info* decInfo, int FileCode);

Status Validation_Decoding(char* FileName, int ValidationCode, decode_Info* decInfo);

Status Do_Decoding(char** argv, decode_Info* decInfo);

Status Extract_MagicStr(int MagicStrSize, decode_Info* decInfo);

Status Extract_SecreteFile_ExtnSize(decode_Info* decInfo);

Status Extract_SecreteFile_Extn(int ExtnSize, decode_Info* decInfo);

Status Extract_SecreteFile_MsgSize(decode_Info* decInfo);

Status Write_SecreteMsg_toFile();

Status Decode_Byte(char* ch, decode_Info* decInfo);

Status Decode_Int(int* num, decode_Info* decInfo);

Status WriteDataintoFile(int, decode_Info*);

void DisplayDecodedMsg();

void CloseAllFilesfterDecoding(decode_Info* );