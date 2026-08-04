#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    //printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    //printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

OperationType check_operation_type(char *argv[])  // implemented on 31-3-26
{
    /*This Fuction is for checking which Operatio we are performing
    and accordingly returning the respective enum */

    
    if(strcmp(argv[1], "-e") == 0)                 
    return  e_encode;       /*if user enterd arg is -e mence encoding*/
    
    else if(strcmp(argv[1], "-d") == 0)
    return  e_decode;   /*if user enterd arg is -d mence dencoding*/
    //if None of the Option Matches then return unsupported
   
   ErrorCodes(1,1);
    return e_unsupported;
    
}

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo) // implemented on 31-3-26
{
    /*Performs Basic Validation Of enterd arguements
    1. chk for src imag file has .bmp extn or not 
    2. chk secrete msg file has '.' present or not
    3. chk for fourth Optional Arg or not if Present than it should have .bmp extn*/

    //chk for .bmp extn in 2nd arguement which src img file name

    UserPrompts(1,4);
    char* Validn_temp = NULL;
    Validn_temp = strstr(argv[2], ".bmp");

    if(Validn_temp  == NULL || strcmp(Validn_temp, ".bmp"))
    {
        ErrorCodes(1,3);
        return e_failure;
    }
    

    //chk for '.'  in 3nd arguement which secreate file name
     UserPrompts(1,5);
     if(strstr(argv[3], ".")  == NULL)
    {
        ErrorCodes(1,4);
        return e_failure;
    }
    

    //if 4rth arg present than chk whether it is .bmp or not
     UserPrompts(1,6);
    if(argv[4] != NULL)
    {
        UserPrompts(1,7);
        Validn_temp = NULL;
        Validn_temp = strstr(argv[4], ".bmp");
        if(Validn_temp == NULL || strcmp(Validn_temp , ".bmp"))
        {
            ErrorCodes(1,5);
            return e_failure;
        }
        

        else
        encInfo ->stego_image_fname = argv[4];
        UserPrompts(1,8);
    }
    else if(argv[4] == NULL)
    {
        UserPrompts(1,9);
        encInfo ->stego_image_fname = "Stego.bmp";
    }

    //if code Reaches Here it mence all files have correct Extentions, Ready to go ahead 
    UserPrompts(1,10);
    encInfo -> src_image_fname = argv[2];
    encInfo ->secret_fname = argv[3];
    
    return e_success;
}

Status check_capacity(EncodeInfo *encInfo)
{
    //This Function will Validate the size requirement to encode msg and related content into output.bmp file
    encInfo ->size_secret_file = get_file_size(encInfo->fptr_secret);

    encInfo ->image_capacity = get_image_size_for_bmp(encInfo ->fptr_src_image);

    if(encInfo ->image_capacity < ((8 * encInfo ->size_secret_file) + 16 + 32 + 32 + 32 ))
    return e_failure;

    
    return e_success;

}

uint get_file_size(FILE *fptr)
{

    //To get the size of secret file
    if(fptr == NULL)
    return 0;

    fseek(fptr, 0, SEEK_END);
    return ftell(fptr);

}

Status do_encoding(EncodeInfo *encInfo)
{
    //All the Function Calls Has been done in this Function
    UserPrompts(1,12);

    if(open_files(encInfo) == e_failure) //Opening File
    return e_failure;
    
    UserPrompts(1,13);
    int flag = check_capacity(encInfo);

  

    if(flag == e_success)
    {
        UserPrompts(1,14);   //Copy BMP Header Function
        if(copy_bmp_header(encInfo ->fptr_src_image, encInfo ->fptr_stego_image) == e_failure)
        {
            ErrorCodes(1,6);
            return e_failure;
        }

        UserPrompts(1,15);   //Calling Magic Str Encoding Fun
        if(encode_magic_string(MAGIC_STRING, encInfo) == e_failure)
        {
            ErrorCodes(1,7);
            return e_failure;
        }
       
        UserPrompts(1,16);  //Calling Secrete File Extn size
        if(encode_secret_file_extn_size(encInfo ->secret_fname, encInfo) == e_failure)
        {
            ErrorCodes(1,8);
            return e_failure;
        }
        
        UserPrompts(1,17);  //Encode secrete Extn Function
        if(encode_secret_file_extn(encInfo ->extn_secret_file, encInfo) == e_failure)
        {
            ErrorCodes(1,9);
            return e_failure;
        }
       
        UserPrompts(1,18);  //Encode Secrete file size
        if(encode_secret_file_size(encInfo ->size_secret_file, encInfo) == e_failure)
        {
            ErrorCodes(1,10);
            return e_failure;
        }
        
         UserPrompts(1,19); //Encode secret file Data
        if(encode_secret_file_data(encInfo) == e_failure)
        {
            ErrorCodes(1,11);
            return e_failure;
        }

        UserPrompts(1,20);  //Calling Copy Remaing Data Function
        if(copy_remaining_img_data(encInfo ->fptr_src_image, encInfo ->fptr_stego_image) == e_failure)
        {
            ErrorCodes(1,12);
            return e_failure;
        }
       


    }
    
    else
    {
        ErrorCodes(1,13);
        return e_failure;
    }

    return e_success;


}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    //.bmp Files have first 54 byte as Header containg file info this function copy it into out destination img file stego.bmp
    if(fptr_src_image == NULL || fptr_dest_image == NULL)
    {
        printf("Unable to Find File while writing copy Header to stego.bmp\n");
        return e_failure;
    }
    
    rewind(fptr_src_image);
    rewind(fptr_dest_image);

    char Buffer[54];
    if(fread(Buffer, 1, 54, fptr_src_image) != 54)
    {
        printf("Error while Reading File into Buffer\n");
        return e_failure;
    }

    if(fwrite(Buffer, 1, 54, fptr_dest_image) != 54 )
    {
        printf("Error While Writing Header into Buffer\n");
        return e_failure;
    }
    

    return e_success;

    
}


Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    //Encode magic string Function
    if(encode_data_to_image(magic_string, 2, encInfo ->fptr_src_image, encInfo->fptr_stego_image) == e_failure)
    return e_failure;

    return e_success;

}


Status encode_secret_file_extn_size(const char *Secretfile_name, EncodeInfo *encInfo)
{
    char* temp = strstr(Secretfile_name, ".");
    int size = strlen(temp);

    strcpy(encInfo ->extn_secret_file, temp);

    char Buffer[32];
    if(fread(Buffer, 1, 32, encInfo ->fptr_src_image) != 32)
    return e_failure;

    encode_int_to_lsb(size, Buffer);


   if( fwrite(Buffer, 1, 32, encInfo ->fptr_stego_image) != 32)
   return e_failure;

   
  return e_success;

}


Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    int size = strlen(encInfo->extn_secret_file);

    if(encode_data_to_image(file_extn, size,  encInfo ->fptr_src_image, encInfo->fptr_stego_image) == e_failure)
    return e_failure;

    return e_success;
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char Buffer[32];

    if( fread(Buffer, 1, 32, encInfo ->fptr_src_image) != 32)
    return e_failure;

    encode_int_to_lsb(file_size, Buffer);

    if(fwrite(Buffer, 1, 32, encInfo ->fptr_stego_image) != 32)
    return e_failure;

    return e_success;
}


Status encode_secret_file_data(EncodeInfo *encInfo)
{
    rewind(encInfo ->fptr_secret);
    int size = encInfo ->size_secret_file;
    char buffer[size];

 
    if(fread(buffer, 1, size, encInfo ->fptr_secret) != size)
    return e_failure;
    
    /*for(int i = 0;i < size; i++)
    {
        printf("%c ", buffer[i]);
    }*/

   if(encode_data_to_image(buffer, size, encInfo ->fptr_src_image, encInfo ->fptr_stego_image) == e_failure)
   return e_failure;

   return e_success;
}


Status encode_data_to_image(const char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char Buffer[8];

    for(int i = 0; i < size; i++)
    {
       if(fread(Buffer, 1, 8, fptr_src_image) != 8)
       return e_failure;

       if(encode_byte_to_lsb(data[i], Buffer) == e_failure)
       return e_failure;

       if(fwrite(Buffer, 1, 8,fptr_stego_image) != 8)
       return e_failure;
       
    }

    return e_success;
}

Status encode_int_to_lsb( int size, char *image_buffer)
{
    //This Function encodes each bit of passed int number into LSB of img files bytes

    int mask = 1 << 31;  //Creating Mask

    for(int i = 0; i < 32; i++)
    {
        image_buffer[i] = image_buffer[i] & ~1; //Clearing LSB Bit

        if(size & mask)    //if '1' is detected than set the LSB bit of aresp. Img byte
        {
            image_buffer[i] = image_buffer[i] | 1;
        }

        size = size << 1;   //shift oue int bits to left one by one at each torn
    }

    return e_success;
}


Status encode_byte_to_lsb(char data, char *image_buffer)
{
    char mask = 1 << 7;   //Create MASK
    for(int i = 0; i < 8; i++)
    {
        //Write MSB Bit of ip char to LSB of Buffer
        image_buffer[i] = image_buffer[i] & ~1;    //Clear LSB Bit 

        if(data & mask)     //if '1' is detected than set the LSB bit of aresp. mg byte
        {
            image_buffer[i] = image_buffer[i] | 1;
        }
        data = data << 1;  //bit shifting
    }

    return e_success;
}


Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char ch;
    while(fread(&ch, 1, 1, fptr_src) == 1)
    {
        fwrite(&ch, 1, 1, fptr_dest);
        
    }

    return e_success;
}

void CloseAllFilesfterEncoding(EncodeInfo* closeAll)
{
    fclose(closeAll ->fptr_secret);
    fclose(closeAll ->fptr_src_image);
    fclose(closeAll ->fptr_stego_image);

    closeAll ->fptr_secret = NULL;
    closeAll ->fptr_stego_image = NULL;
    closeAll ->fptr_src_image = NULL;

}


