
/* Project Title :- Stagnography
Project Done & Submitted by
Prathamesh Bhaskar Deore
batch :- 25044
ID :- 003
*/
//Do Refer Documentation PDF Provided to Understand Functionality and Additional Features added

#include <stdio.h>
#include "encode.h" // encoding operation Header File :- struct, Encoding Function Declarations
#include "decode.h" // Decoding operation Header File :- struct, Decoding Function Declarations
#include "types.h"
#include "common.h" //Common Opern (Error Codes and User Prompts Magic str Declare here)

int main(int argc, char* argv[])
{
    UserPrompts(1,1); //chk User Prompts Documentation to know more about this codes and there meaning
    if(argc < 2)   
    {
        ErrorCodes(1,1);  //if arg are less than 2 than return error
        return e_failure;
    }
    
    EncodeInfo encInfo;  //Creating Encode Structure Variable all Information Related with encoding opern will be done using this variable 
    decode_Info decInfo; //Creating Decode Structure Variable all Information Related with Decoding opern will be done using this variable 
    
    int OperationType = check_operation_type(argv); //Checking which Operation to Perform encoding or decoding

    if(OperationType == e_encode)
    {
        UserPrompts(1,2);

        if(argc < 4)
        {                         //min 4 arg required for encoding if not than give error
            ErrorCodes(1,2);
            return e_failure;
        }

        UserPrompts(1,3);

        if(read_and_validate_encode_args(argv, &encInfo) == e_failure)
        {
            return e_failure;    //Validation and Reading of User entered arg
        }

        UserPrompts(1,11);
        if(do_encoding(&encInfo) == e_failure)   // Calling Do encoding and checking  & Validating Encoding Operation
        {
            printf("Some Error Occured\n");
        }
        else
        {
            UserPrompts(1,21);
            CloseAllFilesfterEncoding(&encInfo);  //After All Functions Successfull Execution Close all Files
        }
        
    }

    else if(OperationType == e_decode)    //Decoding Operation
    {
        UserPrompts(2,1);

        if(argc < 3)
        {
            ErrorCodes(2,1);   //Minimum 3 arg Required for Performing Decoding Operation
            return e_failure;
        }
        
        UserPrompts(2,2);
        if(Do_Decoding(argv, &decInfo) == e_success)   // Calling Decoding Function& Validating
        {
            UserPrompts(2,18);
            CloseAllFilesfterDecoding(&decInfo);    //Closing Files After Successful Execution of Decoding
            UserPrompts(2,19);
            DisplayDecodedMsg(&decInfo); //Displaying Secrete Msg Extracted from input encoded .bmp file
            UserPrompts(2,20);
           
            return e_success;
        }
        else
        {
            return e_failure;
        }

        

        
    }

    else if(OperationType == e_unsupported)
    {
       return 0;
    }

    return 0;
}


