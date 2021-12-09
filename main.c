#include "includes.h"

string readFirstRowSaveInArr(string fileName)
{
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("File is not exist");
        fclose(fp);
        exit(1);
    }

    char buffer[256] = {0};

    fscanf(fp, "%s", buffer);

    string array = (string)malloc(strlen(buffer) + 1);
    strcpy(array, buffer);
    if (array == NULL)
    {
        fclose(fp);
        printf(" -- Out of memory -- ");
        exit(1);
    }
    fclose(fp);
    return array;
}

int fileRows(string fileName)
{

    char buffer[256] = {0};
    fp = fopen(fileName, "r");
    string fileGets = fgets(buffer, 256, fp);
    int count = 0;
    while (fileGets != NULL)
    {
        fileGets = fgets(buffer, 256, fp);
        count++;
    }
    fclose(fp);
    return count;
}

t_alpha *putFileInArrOfStructs(string fileName)
{
    t_alpha *arrOfStructs = (t_alpha *)calloc(fileRows(fileName) - 1, sizeof(t_alpha));

    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf(" file dont exist");
        exit(1);
    }

    char *currCode[100];
    int currChar = 0;

    if (arrOfStructs == NULL)
    {
        printf("WTF");
        exit(2);
    }

    char buffer[256] = {0};

    fseek(fp, 0, SEEK_SET);

    string fileGets = fgets(buffer, 256, fp);

    if (fileGets == NULL)
    {
        printf(" FILE IS NULL ");
        exit(0);
    }

    int currCol = 0;

    for (int i = 0; fileGets != NULL; i++)
    {
        fileGets = fgets(buffer, 256, fp);

        currCol = 0;

        string token = strtok(buffer, " ");

        while (token != NULL)
        {
            switch (currCol)
            {
            case 0:
                strcpy(arrOfStructs[i].alpha, token);
                break;
            case 1:
                token[strlen(token) - 1] = '\0';
                strcpy(arrOfStructs[i].code, token);
                break;
            default:
                break;
            }
            token = strtok(NULL, " ");
            currCol++;
        }
    }

    fclose(fp);
    return arrOfStructs;
}

void compareStringsFromHash(t_alpha *arrOfStructs, string myCode)
{
    int i = 0;
    char buffer[32];
    int currCount = 0;
    while (i < strlen(myCode))
    {
        buffer[currCount++] = myCode[i];
        if (myCode[i] == '0')
        {

            buffer[currCount - 1] = '\0';

            currCount = 0;
            for (int j = 0; j < fileRows(HASH_FILE) - 1; j++)
            {
                if (strcmp(arrOfStructs[j].code, buffer) == 0)
                {
                    printf("%s", arrOfStructs[j].alpha);
                }
            }
        }

        i++;
    }
}

void printStructs(t_alpha *arrOfStructs, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s ", arrOfStructs[i].alpha);
        printf("%s\n", arrOfStructs[i].code);
    }
}

int main(int argc, char const *argv[])
{
    string myCode = readFirstRowSaveInArr(HASH_FILE);

    t_alpha *arrOfStructs = putFileInArrOfStructs(HASH_FILE);

    system("clear");

    printStructs(arrOfStructs, fileRows(HASH_FILE) - 1);

    compareStringsFromHash(arrOfStructs, myCode);

    free(myCode);
    free(arrOfStructs);

    return 0;
}
