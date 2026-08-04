
#include<stdio.h>
#include"common.h"
void UserPrompts(int FUNCTION_ID, int PROMPT_ID)
{
    printf("INFO : ");

    if(FUNCTION_ID == 1)
    switch(PROMPT_ID)
    {
        case 1:
        {
            printf("Checking Number of arguements Entered\n");
            break;
        }

         case 2:
        {
            printf("Encoding Operation Identified Checking Number of arguements Required\n");
            break;
        }

         case 3:
        {
            printf("Found ok...Now Validating and Reading Aruguements\n");
            break;
        }

         case 4:
        {
            printf("checking for .bmp extn in 2nd arguement which src img file name\n");
            break;
        }

         case 5:
        {
            printf("chk for '.'  in 3nd arguement which secreate file name\n");
            break;
        }

         case 6:
        {
            printf("Checking whether 4rth arguement Present or Not\n");
            break;
        }

         case 7:
        {
            printf("4rth Arguement Present..Validating in Prgress...\n");
            break;
        }

         case 8:
        {
            printf("Found OK\n");
            break;
        }

         case 9:
        {
            printf("4rth Arguement Not Present..Creating Bydefault Stego.bmp name\n");
            break;
        }

         case 10:
        {
            printf("All Files Names are Validated and Found OK\n");
            break;
        }

         case 11:
        {
            printf("Opening Files In Prgress\n");
            break;
        }

         case 12:
        {
            printf("***ENCOADING HAS BEEN STARTING****\n");
            break;
        }

         case 13:
        {
            printf("Checking Capacity and Validating Sizes of Files\n");
            break;
        }


         case 14:
        {
            printf("File Capacity Found Ok..Copying BMP Header to Destination bmp file\n");
            break;
        }


         case 15:
        {
            printf("Encoading Magic String\n");
            break;
        }

         case 16:
        {
            printf("Encoding Secrete File Extention Size\n");
            break;
        }
        case 17:
        {
            printf("Encoding Secrete File Extention \n");
            break;
        }
        case 18:
        {
            printf("Encoading Secrete File Size\n");
            break;
        } 

        case 19:
        {
            printf("Encoading Secrete File Data\n");
            break;
        }
        
        case 20:
        {
            printf("Copying Remaining File Bytes..\n");
            break;
        } 

        case 21:
        {
            printf("Encoding Done...Now Closing all Files\n");
            break;
        }


    }

    else if(FUNCTION_ID == 2)
    {
        switch(PROMPT_ID)
     {
         case 1:
        {
            printf("Decoding Operation Recognised...Validating Arguements Specific to Decoding\n");
            break;
        }

         case 2:
        {
            printf("Found Ok... Starting Decoding Operations and Further Validations\n");
            break;
        }

         case 3:
        {
            printf("Validating 2nd Arguement Entered\n");
            break;
        }

         case 4:
        {

            break;
        }

         case 5:
        {
            printf("Arguement 2 (Input .bmp img file Name) Found Ok)\n");
            break;
        }

         case 6:
        {
            printf("Opening input .bmp img File in Progress...\n");
            break;
        }

         case 7:
        {
            
            break;
        }

         case 8:
        {
            printf("input.bmp File Opened Success...\n");
            break;
        }
         case 9:
        {
            printf("Skipping First 54 Byte Header\n");
            break;
        }
         case 10:
        {
            printf("Done..Decrypting Magic String in Prgress\n");
            break;
        }
         case 11:
        {
            printf("Done..Validation for Magic string and User Identification in Progress\n");
            break;
        }
         case 12:
        {
            printf("User Identified...Decrypting Secrete File Extension Size\n");
            break;
        }
         case 13:
        {
            printf("Decrypting Secrete File Extension\n");
            break;
        }
         case 14:
        {
            printf("Creating Output File Name\n");
            break;
        }

         case 15:
        {
            printf("Opening Output File\n");
            break;
        }

         case 16:
        {
            printf("Decrypting Secrete File Msg Size\n");
            break;
        }

         case 17:
        {
            printf("Decrypting Msg and Writing it into Output File in Progress\n");
            break;
        }

         case 18:
        {
            printf("Msg Decrypted Done, now Closing all Files Open\n");
            break;
        }

         case 19:
        {
            printf("Displaying Decoded Msg....\n");
            break;
        }

         case 20:
        {
            printf("Decoading Operation Done Successfully u can refer the Files to see Massage\n");
            break;
        }

         case 21:
        {
            printf("Output File Name has been Not Provided...Creating Default File Name\n");
            break;
        }

        case 22 :
        {
            printf("Output file has been open Successfully\n");
            break;
        }

        case 23 :
        {
            printf("Output File name has been Provided Processing Further\n");
            break;
        }
     }

    }
}

void  ErrorCodes(int FUNCTION_ID, int ERROR_CODE)
{
    if(FUNCTION_ID == 1)
    printf("ERROR : ENCODING : ");
    
    if(FUNCTION_ID == 1)
    switch(ERROR_CODE)
    {
        
         case 1:
        {
            printf("Arguements are Incorrect..\n");
            break;
        }

         case 2:
        {
            printf("Arguements Required Encoding are not Correct\n");
            break;
        }

         case 3:
        {
             printf("Invalid Src File, only .bmp file is Supported..\n");
            break;
        }

         case 4:
        {
            printf("No '.' Found in Input Seret File name ..\n");
            break;
        }

         case 5:
        {
            printf("OutPut Source File Provided is not supported, only .bmp Files are Allowed\n");
            break;
        }

         case 6:
        {
            printf("Error Occured while copying Header\n");
            break;
        }

         case 7:
        {
            printf("Error Occured while Encoding Magic String\n");
            break;
        }

        case 8:
        {
            printf("Error Occured while Encoding File Extn Size\n");
            break;
        }

        case 9:
        {
            printf("Error Occured while Encoding Secrete File Extension\n");
            break;
        }
        case 10:
        {
            printf("Error Occured while Encoding Secrete File Size\n");
            break;
        }

        case 11:
        {
            printf("Error Occured while Secrete File Data\n");
            break;
        }

        case 12:
        {
            printf("Error Occured while Copying Remaining Bytes From src img o destination img file\n");
            break;
        }
        case 13 :
        {
            printf("Capacity of input Img Source File is not Sufficient to Encode Complete Data\n");
            break;
        }


    }

    else if(FUNCTION_ID == 2)
    {
        printf("ERROR : DECODING : ");
        switch(ERROR_CODE)
        {
            case 1:
            {
                printf("Arguements Specific to Decoding are not Correct\n");
                break;
            }

            case 2:
            {
                printf("Incorrect 2nd Arguement\n");
                break;
            }

            case 3:
            {
                printf("Error occured While Opening input (.bmp) File\n");
                break;
            }

            case 4:
            {
                printf("Error Occured while Decoding Magic string\n");
                break;
            }

            case 5:
            {
                printf("Magic string Verification From User Failed\n");
                break;
            }

            case 6:
            {
                printf("Error Occured while Decoding Sercret file Extn Size\n");
                break;
            }

            case 7:
            {
                printf("Error Occured while Decoding Secrete File Extn\n");
                break;
            }

            case 8:
            {
                printf("Error Occured while Creating Output File Name\n");
                break;
            }
             case 9:
            {
                printf("Error Occured while Opening Output File\n");
                break;
            }
             case 10:
            {
                printf("Error Occured while Decoding Secrete Massege\n");
                break;
            }
             case 11:
            {
                printf("Error Occured while Writing Secrte msg into Output File\n");
                break;
            }
        }
    }
}