#include <stdio.h>
#include "types.h"
#include<string.h>
#include "common.h"
#include "decode.h"

Status Do_Decoding(char** argv, decode_Info* decInfo)
{
    UserPrompts(2,3);
    if(Validation_Decoding(argv[2], 1, decInfo) == e_failure)
    {
        ErrorCodes(2,2);
        return e_failure;
    }
    

    UserPrompts(2,6);
    if(OpenFiles(decInfo, 1) == e_failure)
    {
        ErrorCodes(2,3);
        return e_failure;
    }
    

    UserPrompts(2,9);
    fseek(decInfo ->Input_bmpFile_ptr, 54, SEEK_SET);
    
    UserPrompts(2,10);
    if(Extract_MagicStr(2,decInfo) == e_failure)
    {
        ErrorCodes(2,4);
        return e_failure;
    }
   
    
    UserPrompts(2,11);
    if(Validation_Decoding(decInfo ->magicStr, 2, decInfo) == e_failure)
    {
        ErrorCodes(2,5);
        return e_failure;
    }
    

    UserPrompts(2,12);
    if(Extract_SecreteFile_ExtnSize(decInfo) == e_failure)
    {
        ErrorCodes(2,6);
        return e_failure;
    }
    

  
    
   UserPrompts(2,13);
    if ( Extract_SecreteFile_Extn(decInfo ->SecreteFile_ExtnSize, decInfo) == e_failure)
    {
        ErrorCodes(2,7);
        return e_failure;
    }
   

  
    UserPrompts(2,14);
    if(Create_OPfileName(argv[3], decInfo) == e_failure)
    {
        ErrorCodes(2,8);
        return e_failure;
    }
    

   // printf("OpFile Name is %s\n", decInfo ->OutputFileName);
    UserPrompts(2,15);
    if(OpenFiles(decInfo, 2) == e_failure)
    {
        ErrorCodes(2,9);
        return e_failure;
    }
    

    UserPrompts(2,16);
    if(Extract_SecreteFile_MsgSize(decInfo) == e_failure)
    {
        ErrorCodes(2,10);
        return e_failure;
    }
    

 

   UserPrompts(2,17);
   if( Write_SecreteMsg_toFile(decInfo ->secreteFileData_Size, decInfo) == e_failure)
   {
      ErrorCodes(2,11);
      return e_failure;
   }
   

  

   return e_success;
}

Status Create_OPfileName(char* FileName, decode_Info* decInfo)
{
     if(FileName != NULL)
    {
        UserPrompts(2,20);
        char* GetName = strtok(FileName, ".");
        strcat(GetName, decInfo ->SecreteFile_ExtName);
        strcpy(decInfo ->OutputFileName, GetName);
    }

    else
    {
        UserPrompts(2,21);
        char temp[20] = "File";
        strcat(temp, decInfo->SecreteFile_ExtName);
       

        strcpy(decInfo ->OutputFileName, temp);
    }

    return e_success;
}


Status OpenFiles(decode_Info* decInfo, int FileCode)
{
    if(FileCode == 1)
    {
       // UserPrompts(2,7);
        decInfo ->Input_bmpFile_ptr = fopen(decInfo ->InputImgFle_Name, "rb");

        if(decInfo ->Input_bmpFile_ptr == NULL)
        {
          
           return e_failure;
        }
        
        UserPrompts(2,8);
        return e_success;
    }

    else if(FileCode == 2)
    {
        decInfo ->OutputFile_ptr = fopen(decInfo ->OutputFileName, "wb");

        if(decInfo ->OutputFile_ptr == NULL)
        {
           return e_failure;
        }

        UserPrompts(2,22);
        return e_success;
    }

    return e_failure;


    
}

Status Validation_Decoding(char* FileName, int ValidationCode, decode_Info* decInfo)
{
    if (ValidationCode == 1) //chk for input file extn it should be .bmp
    {
        
        char* str = (strstr(FileName, ".bmp"));
        if(str == NULL || strcmp(str, ".bmp"))
        {
            return e_failure;
        }
       
        UserPrompts(2,5);
        decInfo ->InputImgFle_Name = FileName;

         return e_success;
        
    }
    else if (ValidationCode == 2) //Chk for Magic String Validation
    {
         
        int size = strlen(decInfo ->magicStr);
        char str[size + 1];
        printf("Enter the magic string\n");
        fgets(str, size + 1, stdin);

        

        if(strcmp(str, decInfo ->magicStr))
        {
           
            return e_failure;
        }
        

        return e_success;
    }


    return e_failure;
}

Status Extract_MagicStr(int MagicStrSize, decode_Info* decInfo)
{
    char buffer[MagicStrSize + 1];
    

    for(int i = 0; i < MagicStrSize; i++)
    {
        buffer[i] = 0;
        if(Decode_Byte(buffer + i, decInfo) == e_failure)
        return e_failure;
       
    }

    buffer[MagicStrSize] = '\0';

   
    strcpy(decInfo ->magicStr, buffer);
    

    return e_success;
}

Status Extract_SecreteFile_ExtnSize(decode_Info* decInfo)
{
    int size = 0;

    if(Decode_Int(&size, decInfo) == e_failure)
    return e_failure;

    decInfo ->SecreteFile_ExtnSize = size;

    return e_success;

}

Status Extract_SecreteFile_Extn(int ExtnSize, decode_Info* decInfo)
{
    char buffer[ExtnSize + 1];

    
    for(int i = 0; i < ExtnSize; i++)
    {
        buffer[i] = 0;
        if(Decode_Byte(buffer + i , decInfo) == e_failure)
        return e_failure;
    }

    buffer[ExtnSize] = '\0';
   // printf("%s\n", buffer);
    strcpy(decInfo ->SecreteFile_ExtName, buffer);

    return e_success;
}

Status Extract_SecreteFile_MsgSize(decode_Info* decInfo)
{
    int size = 0;
   
    if(Decode_Int(&size, decInfo) == e_failure)
    return e_failure;

    decInfo ->secreteFileData_Size = size;

    return e_success;
    
}

Status Decode_Byte(char* ch, decode_Info* decInfo)
{
   
    char Buffer[8];

    if(fread(Buffer, 1, 8, decInfo->Input_bmpFile_ptr) != 8)
    return e_failure;

    unsigned char RetriveData = 0;
    
    for(int i = 7; i >= 0; i--)
    {
        if(Buffer[7 - i] & 1)
        {
            RetriveData = RetriveData | (1 << i);
        }
    }

    *ch = RetriveData;

    
    return e_success;
}

Status Decode_Int(int* num, decode_Info* decInfo)
{
    char Buffer[32];

    if(fread(Buffer, 1, 32, decInfo->Input_bmpFile_ptr) != 32)
    return e_failure;

    int RetriveData = 0;
    
    for(int i = 31; i >= 0; i--)
    {
        if(Buffer[31 - i] & 1)
        {
            RetriveData = RetriveData | (1U << i);
        }
    }

    *num = RetriveData;

    return e_success;
}

Status Write_SecreteMsg_toFile(int msgSize, decode_Info* decInfo)
{
    unsigned char ch;
    //printf("Size = %d\n", msgSize);
    for(int i = 0; i < msgSize; i++)
    {
        ch = 0;
        if(Decode_Byte(&ch, decInfo) == e_failure)
        return e_failure;

        //printf("%c",ch);

        if(fwrite(&ch, 1, 1, decInfo ->OutputFile_ptr) != 1)
        return e_failure;
    }

   
}

void DisplayDecodedMsg(decode_Info* Show)
{
    if(Show ->OutputFile_ptr != NULL)
    {
        printf("Error : Two File Pointers Opend in two Differnt Mode\n");
        return;
    }

    FILE* showMsg = fopen(Show ->OutputFileName, "rb");
    char ch = 0;
    
    if(showMsg == NULL)
    {
        printf("Unable to Open File");
        return;
    }
   
   printf("\n----------------------------------------------\n");
    
    while(fread(&ch, 1, 1, showMsg))
    {
        putchar(ch);
    }

    fclose(showMsg);
    printf("\n----------------------------------------------\n");
}

void CloseAllFilesfterDecoding(decode_Info* closeFiles)
{
    fclose(closeFiles ->Input_bmpFile_ptr);
    fclose(closeFiles ->OutputFile_ptr);

    closeFiles ->Input_bmpFile_ptr = NULL;
    closeFiles ->OutputFile_ptr = NULL;
}