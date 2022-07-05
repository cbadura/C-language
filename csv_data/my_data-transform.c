/* Data prep exercise: our CSV is composed of 3 columns: Email - Age - Order At.
For the email, we will consider the provider.
For the age column, we consider a group from [1->20] - [21->40] - [41->65] - [66->99]
For the Order at column, we consider a group for [morning => 06:00am -> 11:59am] - [afternoon => 12:00pm -> 5:59pm] - [evening => 6:00pm -> 11:59pm]
You will have to create a function which will replace the value in each of these columns with the correct actionable data.
(ex: if the age is between 21 and 40, replace by "21->40") */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_ARRAY_SIZE 1024

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array {
    int size;
    char **array;
} string_array;
#endif

string_array *my_data_transform(char *csv);
char *split_and_convert(char *str);
char *email(char *str);
char *age(char *str);
char *order_at(char *str);
string_array *my_split(char *str, char *sep);
char *my_strstr(char *haystack, char *needle);
char* my_strrchr(char* str, char c);
int find_str_num(char *str, char *sep);
char *my_join(string_array *strings, char *separator);
int get_length_of_strings(string_array *strings);
int my_strlen(char *string);
int my_strcmp(char *s1, char *s2);

int main(void)
{
    char buffer[MAX_ARRAY_SIZE];
    int readBytes;
    int fd;

    if ((fd = open("coffee_shop.csv", O_RDONLY)) == -1)
    {
        printf("Error!");
        return -1;
    }

    while ((readBytes = read(fd, buffer, 1000)) > 0)
        buffer[readBytes] = '\0';
    /* printf("%s", buffer);
    printf("\n"); */

    string_array* result = my_data_transform(buffer);

    for (int i = 0; i < result->size-1; i++)
        printf("result is: %s\n", result->array[i]);

    free(result);
    return 0;
}

string_array *my_data_transform(char *csv)
{   
    /// 1. setup the return array
    string_array *arr = malloc(sizeof(string_array));
    // string_array *retArr = malloc(sizeof(string_array));

    // compute size of arr
    /* int size = 0;
    for (int i = 0; csv[i] != '\0'; i++)
        if (csv[i] == '\\') size++;
    retArr->size = size + 1; // for last string which must be NULL (5 + 1)
    char **strings = (char**)malloc(sizeof(char*) * size);
    retArr->array = strings;    */ 
    // retArr->array[size - 1] = NULL;   // 6 - 1: arr->array[5] is correct

    // split the large string into several entries
    arr = my_split(csv, "dummy");
    // put first line into first string of retArr

    printf("str: %s\n", arr->array[0]);
    // printf("str: %s\n", arr->array[1]);

    /// 2. find Email, Age, and Order At fields & convert into fitting content
    for (int i = 1; i < arr->size-1; i++)  // from 1 because first line is for the column names
        arr->array[i] = split_and_convert(arr->array[i]);
    
    // free(strings);
    return arr;
}

string_array *my_split(char *str, char *sep)
{
    // set up the struct that will be returned
    // string_array strStruct = { 0 };    
    string_array *structPtr;
    structPtr = malloc(sizeof(string_array));
    if (structPtr == NULL)
        printf("Error\n");

    // find how many separated strings there will be
    int size = 0;
    if (*sep == ',')
        size = 10;
    else
        size = 6;
    structPtr->size = size + 1;
    structPtr->array = (char**)malloc(sizeof(char*) * size);

    // if input is empty
    if (*str == '\0' && *sep == '\0')
    {
        structPtr->size = 1;
        structPtr->array[0] = str;
        return structPtr;
    }    

    int j;
    int strCount = 0;
    int len = my_strlen(str) + 1;
    // go through input string, malloc space for each output string and assign chars till sep is hit
    if (*sep == ',')
    { 
        for (int i = 0; str[i] != '\0'; i++)
        {   
            structPtr->array[strCount] = (char*)malloc(sizeof(char) * len);
            for (j = 0; str[i] != *sep && str[i] != '\0'; j++)
            {
                structPtr->array[strCount][j] = str[i];
                // printf("string: %c\n", structPtr->array[strCount][j]);
                i++;
            }
            structPtr->array[strCount][j] = '\0';
            strCount++;
            if (strCount == size) break; // because the first split also cut the \n at the end?
        }
    } else
    {
        for (int i = 0; str[i] != '\0'; i++)
        {   
            structPtr->array[strCount] = (char*)malloc(sizeof(char) * len);
            for (j = 0; str[i] != 92 && str[i] != '\0'; j++)
            {
                if (j == 0 && str[i] == 'n')
                    i++;
                structPtr->array[strCount][j] = str[i];
                // printf("string: %c\n", structPtr->array[strCount][j]);
                i++;
            }
            structPtr->array[strCount][j] = '\0';
            strCount++;
            if (strCount == size) break; // because the first split also cut the \n at the end?
        }
    }
    return structPtr;
}

char *split_and_convert(char *str)
{
    // set up return str and new str arr for indiv fields
    int len = my_strlen(str) + 1;
    char *result = malloc(sizeof(char) * len);

    string_array *innerArr = malloc(sizeof(string_array));
    /* int size = 10;
    innerArr->size = size + 1;
    char **innerStrings = (char**)malloc(sizeof(char*) * size);
    innerArr->array = innerStrings;    
    innerArr->array[size - 1] = NULL; */
    // split the large string into several entries
    innerArr = my_split(str, ",");

    // assign mail, age, order at
    // (email is field 5 (after 4th comma), age is field 6 (after 5th), order at is 10 (after 9th))
    char* mail = NULL;
    mail = email(innerArr->array[4]);
    innerArr->array[4] = mail;

    char* ageVal = NULL;
    ageVal = age(innerArr->array[5]);
    innerArr->array[5] = ageVal;
    
    char* order = NULL;
    order = order_at(innerArr->array[9]);
    innerArr->array[9] = order;

    // put all the fields back together into a str
    result = my_join(innerArr, ",");

    // free(innerStrings);
    // free(innerArr);

    return result;
}

char *email(char *str)
{
    int len = my_strlen(str) + 1;
    char* mail = malloc(sizeof(char) * len);

    mail = my_strstr(str, "yahoo.com");
    if (mail == NULL)
        mail = "hotmail.com";
    return mail;
}

char *age(char *str)
{
    // convert field to int for determining the value
    int nbr = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        nbr = nbr * 10;    // multipliation by 10 is for always keeping 1st digit on the left pos of result 
        nbr = nbr + str[i] - '0';   // take ASCII character of corresponding digit in str and subtract '0' to get numerical value
    }
    // find age span and return the string
    char* age = malloc(sizeof(char) * 6);
    if (nbr >= 1 && nbr <= 20) 
        age = "1->20";
    if (nbr >= 21 && nbr <= 40) 
        age = "21->40";
    if (nbr >= 41 && nbr <= 65)     
        age = "41->65";
    if (nbr >= 66 && nbr <= 99) 
        age = "66->99";
    return age;
}

char *order_at(char *str)
{
    str = my_strrchr(str, ' '); // cuts str from last occurrence of space, i.e. before the time

    int nbr = 0;
    for(int i = 1; str[i] != ':'; i++) // only looks at the hour value
    {
        nbr = nbr * 10;    // multipliation by 10 is for always keeping 1st digit on the left pos of result 
        nbr = nbr + str[i] - '0';   // take ASCII character of corresponding digit in str and subtract '0' to get numerical value
    }

    char* order = malloc(sizeof(char) * 10);
    if (nbr >= 6 && nbr <= 11)
        order = "morning";
    if (nbr >= 12 && nbr <= 17)
        order = "afternoon";
    if (nbr >= 18 && nbr <= 23)
        order = "evening";
    return order;
}

char *my_strstr(char *haystack, char *needle)
{
    if(!needle || *needle == '\0')   // check if str exists, then if it's empty; mine: if needle is empty, just return haystack; strlen isn't protected  (not checking if NULL or not, so it will crash)
        return haystack;
    
    if(my_strlen(needle) > my_strlen(haystack))   // if needle is longer str than haystack, return null
        return NULL;

    int i = 0;
    int j = 0;
    int n;
    
    while(haystack[i])
    {
        n = i;
        while(needle[j])
        {
            if(haystack[n] != needle[j])
                break;
            j++;
            n++;
        }
        if(needle[j] == '\0')
            return &haystack[i];    
        i++;
        j = 0;
    }
    return NULL;
}

char* my_strrchr(char* str, char c)
{
    int counter, length;
    length = my_strlen(str);

    for(counter = 0; counter < length - 1; counter++)
        str++;                      //puts the pointer to the address of last char in str
    
    for(int i = 0; i < length - 1; i++) {
		if(*str == c)
			return str;
		str--;
	}
	return NULL; 
}

int find_str_num(char *str, char *sep)
{
    int strNum = 0;
    if (str && *str != '\0')
        strNum = 1;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == *sep && str[i + 1] != '\0')
            strNum++;
    }
    return strNum;
}

char *my_join(string_array *strings, char *separator)
{
    int /* lenStrings, sizeOfJoined, */ counter;
    char *joined = NULL;

    
    if (strings->size == 0 && my_strcmp(separator, " ") == 0) return NULL;

    // lenStrings = get_length_of_strings(strings);
    // printf("lenStrings: %d\n", lenStrings);
    // sizeOfJoined = lenStrings + (strings->size - 1) + 1;
    joined = (char*)malloc(sizeof(char) * 100);

    counter = 0;
    for (int i = 0; i < strings->size-1; i++)
    {
        for (int j = 0; j < my_strlen(strings->array[i]); j++)
        { 
            joined[counter] = strings->array[i][j];
            counter++;
        }

        if(i != strings->size - 1)
        {
            for(int h = 0; h < my_strlen(separator); h++)
            {
                joined[counter] = separator[h];
                counter++;
            }
        }
    }
    joined[counter-1] = '\0';

    return joined;
}

int get_length_of_strings(string_array *strings)
{
    int lengthOfStrings = 0;
    int j;

    for (int i = 0; i < strings->size; i++)
    {    
        j = 0;
        while (strings->array[i][j] != '\0')
        {
            j++;
            lengthOfStrings++;
        }
    }
    return lengthOfStrings;
}

int my_strlen(char *string)
{
    int counter = 0;
    while (string[counter] != '\0')
        counter++;
    return counter;
}

int my_strcmp(char *s1, char *s2)
{
    while (*s1 != '\0' && *s1 == *s2)   // check if 1st str has reached the end & char of 1st str matches char of 2nd
    {
        s1++;                           // if they do, increment both addresses of the strings
        s2++;
    }
    return *s1 - *s2;                   // if all chars match, ASCII values of last matching chars will be subtracted --> 0       
}

char *my_strcpy(char *dst, char *src)
{
    int i = 0;
    while(src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = src[i]; // just to copy the '\0' as well
    return dst;
}