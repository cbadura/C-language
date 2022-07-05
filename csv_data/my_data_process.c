/* Here is our second step: data transformation. This exercise follows step one.
You will receive the output of your function my_data_transform.
Our function will group the data and it will become a Hash of hash. (Wow.)
Example:
"{'Gender': {'Male': 22, 'Female': 21}, 'Email': {'yahoo.com': 3, 'hotmail.com': 2}, ...}"
We will discard the columns FirstName, LastName, UserName and Coffee Quantity from our output.

The function will take a string array which is the output of your function my_data_transform,
it will return a json string of hash of hash following this format:

{COLUMN: {Value1: nbr_of_occurence_of_value_1, Value2: nbr_of_occurence_of_value_2, ...}, ...}

Order of Column will be the order which is in the header of the CSV (Gender first then Email, etc).
Order of the Value will be the order which appears in each line from top left. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array {
    int size;
    char **array;
} string_array;
#endif

#ifndef STRUCT_DATA_ENTRY
#define STRUCT_DATA_ENTRY
typedef struct s_data_entry {
    int *value;
    char **array;
} entry;
#endif

#ifndef STRUCT_DATA_OBJECT
#define STRUCT_DATA_OBJECT
typedef struct s_data_object {
    int size;
    entry *array;
} data_object;
#endif

char *my_data_process(string_array* input);
entry *gender(string_array* input);
entry *email(string_array* input);
entry *age(string_array* input);
entry *city(string_array* input);
entry *device(string_array* input);
entry *order_at(string_array* input);
char *csv_str_maker(string_array *input, int field);
char *my_strcat(char *dest, char *src);
char *my_strcpy(char *dst, char *src);
int my_strlen(char *string);

int main(void)
{
    char *input[6] = {
        "Gender,FirstName,LastName,UserName,Email,Age,City,Device,Coffee Quantity,Order At",
        "Male,Carl,Wilderman,carl,yahoo.com,21->40,Seattle,Safari iPhone,2,afternoon",
        "Male,Marvin,Lind,marvin,hotmail.com,66->99,Detroit,Chrome Android,2,afternoon",
        "Female,Shanelle,Marquardt,shanelle,hotmail.com,21->40,Las Vegas,Chrome,1,afternoon",
        "Female,Lavonne,Romaguera,lavonne,yahoo.com,66->99,Seattle,Chrome,2,morning",
        "Male,Derick,McLaughlin,derick,hotmail.com,41->65,Chicago,Chrome Android,1,afternoon"
    };
    
    string_array *arr = malloc(sizeof(string_array));
    arr->size = 6;
    arr->array = input;

    for (int i = 0; i < arr->size; i++)
        printf("str: %s\n", arr->array[i]);

    char *output = my_data_process(arr);
    printf("output: %s\n", output);

    return 0;
}

char *my_data_process(string_array* input)
{
    // set up the return string
    int len = 0;
    for (int i = 0; i < input->size; i++)
        len = len + my_strlen(input->array[i]);

    char *output = malloc(sizeof(char) * len);

    // create one data obj struct with necessary amount of entry structs
    // discard FirstName (field 1), LastName (field 2), UserName (field 3), Coffee Quantity (field 8) - after n-1th comma
    data_object *data = malloc(sizeof(data_object));
    data->size = 6;

    // create entry structs, put them inside data obj to enable search of all data at once
    entry *genderVal = gender(input);
    entry *emailVal = email(input);
    entry *ageVal = age(input);
    entry *cityVal = city(input);
    entry *deviceVal = device(input);
    entry *orderVal = order_at(input);

    output = my_strcpy(output, "{\"");
    printf("str: %s\n", output);

    char *temp = csv_str_maker(input, 2);
    printf("temp: %s\n", temp);
    my_strcat(output, temp);
    printf("str: %s\n", output);
    my_strcat(output, "\":{\"");
    printf("str: %s\n", output);

    // "{\"Gender\":{\"Male\":3,\"Female\":2},\"Email\":{\"yahoo.com\":2,\"hotmail.com\":3},\"Age\":{\"21->40\":2,\"66->99\":2,\"41->65\":1},\"City\":{\"Seattle\":2,\"Detroit\":1,\"Las Vegas\":1,\"Chicago\":1},\"Device\":{\"Safari iPhone\":1,\"Chrome Android\":2,\"Chrome\":2},\"Order At\":{\"afternoon\":4,\"morning\":1}}\0";

    output[0] = '\0';
    return output;
}

entry *gender(string_array *input)
{   
    // set up the entry and the str array
    entry *retEntry = malloc(sizeof(entry));
    retEntry->value = (int*)malloc(sizeof(int) * 2);
    char *genderNames[2] = { "Male", "Female" };
    retEntry->array = genderNames;

    // copy first field, then compare and increase value in the entry
    for (int i = 1; i < input->size; i++)
    {    
        // it's the 1st field, nothing to do but looking at first char
        if (input->array[i][0] == genderNames[0][0])
            retEntry->value[0]++;
        else
            retEntry->value[1]++;
    }
    return retEntry;
} 

entry *email(string_array *input)
{
    entry *email = malloc(sizeof(entry));
    return email;
} 

entry *age(string_array *input)
{
    entry *age = malloc(sizeof(entry));
    return age;   
}

entry *city(string_array *input)
{
    entry *city = malloc(sizeof(entry));
    return city;
} 

entry *device(string_array *input)
{
    entry *device = malloc(sizeof(entry));
    return device;
} 

entry *order_at(string_array *input)
{
    entry *order_at = malloc(sizeof(entry));
    return order_at;
} 

char *csv_str_maker(string_array *input, int field)
{
    // find len of category str by finding right field, skipping over necessary amount of commas
    int len = 0;
    int i = 0;
    while (field > 0)
    {
        if (input->array[0][i] != ',') field--;
        i++;
    }
    // then count len
    for (; input->array[0][i] != ','; i++)
        len++;
    printf("len: %d\n", len);

    char *temp = malloc(sizeof(char) * 7);
    i = 0;
    while (field > 0)
    {
        if (input->array[0][i] != ',') field--;
        i++;
    }
    for (; input->array[0][i] != ','; i++)
        temp[i] = input->array[0][i];
    temp[i++] = '\0';
    return temp;
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

char *my_strcat(char *dest, char *src)
{
    while(*dest) dest++;
    while((*dest++ = *src++));
    return --dest;
}

int my_strlen(char *string)
{
    int counter = 0;
    while (string[counter] != '\0')
        counter++;
    return counter;
}