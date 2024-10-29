#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>


//Checks if ascii is True
int is_ascii(char str[])
{
  bool check_ascii = 1;
  int count = strlen(str)-1;

    //Check if ascii
   for (int i=0; i<count; i++)
     {
    //printf("\n%d", str[i]);
       if(str[i] >=0 && str[i] <=128)
       {//printf(" is a letter\n");
       }
       else
       {check_ascii = 0;
        //printf(" is not a letter\n");
       }
     }

    //Output if ascii or not
  /*       if(check_ascii ==1)
          {printf("is ascii   !!\n");}
      else
         {printf("is not an asciii\n");}
  */
  //puts("\n===Output===");
  return check_ascii;
}

//Makes uppercase
char capitalize_ascii(char str[])
{
  __int32_t ret = 0;
  int count = strlen(str);

  for (int i=0; i<count; i++)
     {
   // printf("\n%d", str[i]);
       if(str[i] >=97 && str[i] <=122)
       {
         str[i] = (char) (str[i]-32);
        ret++;
       }

     }
    //printf("=== Output ===");
    return ret;
  
}

//Gets the width of a byte of an index
__int32_t width_from_start_byte(char start_byte)
{
  int bytes=0;
  int binary;
  char total[8]="        ";
  char zero = '0';
  char one = '1';
  int i =0;

      for (int x = 7; x >= 0; x--) 
      {
             binary = (start_byte >> x) & 1;
             

              if (binary==1)
              {
               // printf("\nits a one");
              total[i]='1';
                
                              }      
              else{
                //printf("\nits a zero");
                total[i]='0';
              }
              //printf("%d", binary);
              i++;
          }

//total[0] ='0';

  //printf("\n\n%s", total);

if(total[0] == '0')
{
  bytes++;
}
if(total[0]=='1')
{
  bytes++;
    for(int x = 1; x < 7; x++)
    {
      if(total[x]=='1')
       { bytes++;}
      else
        {break;}
    }

}
if(total[0]=='1'&& total[1]=='0')
{
  bytes = -1;
}



  return bytes;
}

//Number of code points
__int32_t utf8_strlen(char str[])
{
    int binary1 = 0;
    int binary2 = 0;
    int binary3 = 0;
    int binary4 = 0;
    int binary5 = 0;
    int binary6 = 0;
    int length = 0;
    for (int x = 0; x < strlen(str); x++) 
      {      //printf("\n%cchar is: ", str[x]);
             binary1 = (str[x] >> 7) & 1;
             binary2 =(str[x] >> 6) & 1;
             binary3 = (str[x] >> 5) & 1;
             binary4 =(str[x] >> 4) & 1;
             binary5 = (str[x] >> 3) & 1;
             binary6 =(str[x] >> 2) & 1;
             if(binary1==1)
             {
              //length++;
              if(binary2==1)
              {
                length--;
                if(binary3==1)
                {
                length--; 
                  if(binary4==1)
                  {
                  length--; 
                  if(binary5==1)
                    {
                    length--; 
                   if(binary6==1)
                     {
                     length--; 
                     }                      
                    }                    
                  }                 
                }
              }
             }
  //  printf("\nBinary 1:%d", binary1);
  // printf("\nBinary 2: %d", binary2);
        length++;
        }
  //printf("\n=== Output ===\n");
  return length;
      }

//
__int32_t codepoint_index_to_byte_index(char str[], __int32_t cpi)
{
    int byte_Index = 0;
    int current_codepoint_index = 0;
    int length = 0;

    while (str[byte_Index] != '\0') {
        unsigned char byte = (unsigned char)str[byte_Index];
       // printf("unsigned char byte is: %c  \n", byte);
        

        if ((byte & 0x80) == 0) {
            length = 1; 
             } 
          else if ((byte & 0xE0) == 0xC0) {
            length = 2; 
             } 
          else if ((byte & 0xF0) == 0xE0) {
            length = 3; 
             } 
          else if ((byte & 0xF8) == 0xF0) {
            length = 4; 
             } 
          else {
            return -1; 
              }

        
        if (current_codepoint_index == cpi) {
            return byte_Index; 
        }

        
        byte_Index += length;
        current_codepoint_index++;
    }

    return -1; // Index out of bounds
}

//Bytes per code point 
void Bytes_per_code_point(char str[])
{
    int byte_Index = 0;
    int length = 0;
    int stop = 6;
    int counter = (strlen(str)-1);
    //printf("Counter: %d \n" ,counter);

printf("Bytes per code point: ");
    while (str[byte_Index] != '\0') 
    {
        unsigned char byte = (unsigned char)str[byte_Index];
        //printf("unsigned char byte is: %c  \n", byte);


        if ((byte & 0x80) == 0)
        {     
            length = 1;
            printf("1 ");
             } 
          else if ((byte & 0xE0) == 0xC0) {
            length = 2;
            printf("2 ");
             } 
          else if ((byte & 0xF0) == 0xE0) {
            length = 3; 
            printf("3 ");
             } 
          else if ((byte & 0xF8) == 0xF0) {
            length = 4;
            printf("4 ");
             } 
          else {
            break;
              }

        
        byte_Index += length;
        


    }
 // printf("\nbyte index is %d ", byte_Index);
   // return -1; // Index out of bounds
}

//Gets a substring from a longer string
void utf8_substring(char str[], __int32_t cpi_start, __int32_t cpi_end, char result[]) 
{
    int str_len =utf8_strlen(str);
    int index = 0;

    if(cpi_start<0|| cpi_start >= cpi_end||cpi_end > str_len)
    {
  //printf("Invalid start or end index");
  return;
    }
    str+= codepoint_index_to_byte_index(str,cpi_start);

    while(cpi_start < cpi_end)
    {
  int width = width_from_start_byte(*str);
  for (size_t i = 0; i<width; i++)
  {
    result[index++]= str[i];
  }
  str+=width;
  cpi_start+=1;
    }

    result[index]='\0';

}

//Gets the deciminal at a specific code point
__int32_t codepoint_at(char str[], __int32_t cpi)
{
    int byte_Index = 0;
    int current_codepoint_index = 0;
    int length = 0;

    while (str[byte_Index] != '\0') {
        unsigned char byte = (unsigned char)str[byte_Index];
//        printf(" char byte is: %c \n", byte);

            //checks amount of bytes
        if ((byte & 0x80) == 0) {
            length = 1; 
             } 
          else if ((byte & 0xE0) == 0xC0) {
            length = 2; 
             } 
          else if ((byte & 0xF0) == 0xE0) {
            length = 3; 
             } 
          else if ((byte & 0xF8) == 0xF0) {
            length = 4; 
             } 
          else {
            return -1; //broke
              }

        
        if (current_codepoint_index == cpi) {
            //printf("matches!");
            break; // out loop
        }

        
        byte_Index += length;
        current_codepoint_index++;
    }
  //printf("\n\nI am now out of the loop at index: %d\n\n");
  
  return str[byte_Index];

}

//Gets the first 6 char in the string
void utf8_6chars(char str[], char result[]) 
{
    int str_len =utf8_strlen(str);
    int index = 0;
    __int32_t codepi_start = 0;
    __int32_t codepi_end = 6;
    int codepoints = utf8_strlen(str);

    if(codepi_start<0|| codepi_start >= codepi_end||codepi_end > str_len)
    {
  //invalid
  return;
    }
    //Gets the code point indexes
    str+= codepoint_index_to_byte_index(str,codepi_start);
    if(codepoints>=6)
    {
    while(codepi_start < codepi_end)
    {
  int getwidth = width_from_start_byte(*str);
  for (size_t i = 0; i<getwidth; i++)
  {
    result[index++]= str[i];
  }
  str+=getwidth;

  codepi_start +=1;
    }
    }
    result[index]='\0';

    }




//


//gets the codepoint and turns it into a decimal
void codepoint_to_decimal(char str[])
{
int count = strlen(str);
    
    int value = 0;
    for(int x = 0; x < count;)
    {
        unsigned char first_byte = str[x];
        int value = 0;

        
    if ((first_byte & 0x80) == 0) {
        // 1-byte character
        value = first_byte;

        x+=1;
    } else if ((first_byte & 0xE0) == 0xC0) {
        // 2-byte character
                                //0b00011111
        value = (first_byte & 0x1F) << 6 | (str[x+1] & 0x3F);
        x += 2;
        //printf("Decimal value: %d\n", value);
    } else if ((first_byte & 0xF0) == 0xE0) {

         value = (first_byte & 0x0F) << 12 | (str[x+1] & 0x3F) << 6 | (str[x+2] & 0x3F);
        x+= 3;
        //printf("Decimal value: %d\n", value);
    } 
        else if((first_byte & 0xF0) == 0xF0){
            

            value = (first_byte & 0x07) << 18 | (str[x+1] & 0x3F) << 12 | (str[x+2] & 0x3F) << 6 | (str[x+3] & 0x3F);
            x+=4;
        }

        printf("%d ", value);
    }



}



void is_animal_emoji(char str[])
{printf("\nAnimal emojis: ");
int value = 0;
    for (int x = 0; str[x] != '\0'; ) {

       // printf("Character %d: ", x);

        // Calculate the length of the UTF-8 character
        unsigned char first_byte = str[x];
        int char_length = 0;

        if ((first_byte & 0x80) == 0) {
            char_length = 1; // 1-b
        } else if ((first_byte & 0xE0) == 0xC0) {
            char_length = 2; // 2-b
        } else if ((first_byte & 0xF0) == 0xE0) {
            char_length = 3; // 3-
        } else if ((first_byte & 0xF8) == 0xF0) {
            char_length = 4; // 4-b
        value = (first_byte & 0x07) << 18 | (str[x+1] & 0x3F) << 12 | (str[x+2] & 0x3F) << 6 | (str[x+3] & 0x3F);       
        }

        // Print the character
        if (value >= 128000 && value <=128063 || value>= 129408 && 129454<=value)
        {
            for (int j = 0; j < char_length; j++) {
            printf("%c", str[x + j]);
        }
        }
        value = 0;
      //  printf("\n");

        // Move to the next character
        x += char_length;
    }

}

                    // string , an index, returns the result 
void next_utf8_char(char str[], __int32_t cpi, char result[])
{


    int x = codepoint_index_to_byte_index(str,cpi);
   // printf("\n%d",x);

        unsigned char byte = str[x];
        int value = 0;

        
    if ((byte & 0x80) == 0) {
        // 1-byte character
        value = byte;

    } else if ((byte & 0xE0) == 0xC0) {
                                //0b00011111
        value = (byte & 0x1F) << 6 | (str[x+1] & 0x3F);
    } else if ((byte & 0xF0) == 0xE0) {

         value = (byte & 0x0F) << 12 | (str[x+1] & 0x3F) << 6 | (str[x+2] & 0x3F);

    }
        else if((byte & 0xF0) == 0xF0){
            value = (byte & 0x07) << 18 | (str[x+1] & 0x3F) << 12 | (str[x+2] & 0x3F) << 6 | (str[x+3] & 0x3F);
        }

       // printf("\n%d ", value);
    
    value = value+1;
    if (value <= 0x7F) {

        result[0] = value;
        result[1] = '\0';
    } else if (value <= 0x7FF) {

        result[0] = 0xC0 | ((value >> 6) & 0x1F);
        result[1] = 0b10000000 | (value & 0x3F);
        result[2] = '\0';
    } else if (value <= 0xFFFF) {

        result[0] = 0xE0 | ((value >> 12) & 0x0F);
        result[1] = 0b10000000  | ((value >> 6) & 0x3F);
        result[2] = 0b10000000  | (value & 0x3F);
        result[3] = '\0';
    } else if (value <= 0x10FFFF) {

        result[0] = 0xF0 | ((value >> 18) & 0x07);
        result[1] = 0b10000000  | ((value >> 12) & 0x3F);
        result[2] = 0b10000000  | ((value >> 6) & 0x3F);
        result[3] = 0b10000000  | (value & 0x3F);
        result[4] = '\0';
    }  
       int length = utf8_strlen(str);
       if(length < 4)
       {
        result[0] = '\0';
       }

    printf("\nNext Character of Codepoint at Index 3: %s", result); // Print the UTF-8 encoded string
    
    
}






void analyze(char str[])
{
  
    char hold[strlen(str)];
    strcpy(hold, str);
    // printf("Hold the string: %s", hold);
    //Valid ASCII:
    int ch = 0;
    ch =  is_ascii(str);
    if(ch==1)
    {printf("\nValid ASCII: true");}
    else
    {printf("\nValid ASCII: false");}

    //Uppercased ASCII:
    __int32_t ret = 0;
    ret = capitalize_ascii(str);
    printf("\nUppercased ASCII: %s", str);

    //Length in bytes:
    printf("\nLength in bytes: %ld ", (strlen(str)));
    
    //Number of code points: 
    int length = utf8_strlen(str);
    printf("\nNumber of code points: %d ", (length));

    //Bytes per code point:
      //BUG IN THE CODE ADDS AN EXTRA 1
    printf("\n");
    Bytes_per_code_point(str);



    //Gets the first 6 code points of the string as a substring
    int index = 6;
    int checker = codepoint_index_to_byte_index(str, index);
    char result[checker];
    //Substring of the first 6 code points: 
    utf8_6chars(hold, result);
    char quotations = '"';
    printf("\nSubstring of the first 6 code points: ");
    printf("%c%s%c\n",quotations,result,quotations);
    printf("Code points as decimal numbers: ");
    codepoint_to_decimal(hold);
    is_animal_emoji(hold);

    char result1[100];
    __int32_t idx = 3;

    next_utf8_char(hold,idx,result1);

    printf("\n");
}







int main() 
{

    char str[100];
    printf("Enter a UTF-8 encoded string: ");
    fgets(str,99,stdin);
   // printf("\nYour string: %s ", str);
    analyze(str);


    //==

}