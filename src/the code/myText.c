#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Declare the max size of the buffer array and link list.*/

#define MAX_SIZE 61
#define FAIL -1

typedef struct node *ptr;

/*Create link list data structure.*/

struct node 
{
    char text[MAX_SIZE];

    ptr link;
};

/*Declaration of functions.*/

int readText(int, void **);

void printText(int index, void *selectedMethod);

void freeList(ptr *);

/*The main method.*/

int main()
{
    ptr head = NULL;

    char *buffer = NULL;

    int index;

    printf("\nChoose a method for text procssing: (1). via linked list, (2). via buffer, (0). to abort.\n");

    /*The users are to choose between two data structures for text handling, or to terminate the program.*/

    scanf("%d", &index);
    
    /*Index 0 is for program termination.*/

    if(index == 0) 
    {
        return 0;
    }
    /*Index 1 is for link list data structure.*/

    if(index == 1)
    {
        printf("\nEnter your text here:\n");

        head = calloc(1, sizeof(struct node));

        if(!head)
        {
            puts("Error, memory allocation failed.");
        }

        /* We cast head to void ** to call it by reference. If we fail to realloc, readText will return the FAIL constant, the program will print what ever the data structure holds, free it, print an error message and terminate itself*/

        if(readText(index,(void **) &head) == FAIL)
        {
            printText(index, head);

            freeList(&head);

            puts("Could not allocate anymore memory.");

            exit(1);      
        }

        printText(index, head);

        freeList(&head);
    }

    /*Index 2 is for buffer data structure.*/

    if(index == 2)
    {
        printf("\nEnter your text here:\n");

        buffer = calloc(1, MAX_SIZE);

        if(!buffer)
        {
            puts("Error, memory allocation failed.");
        }

        /*We cast the buffer to void ** so we can call it by reference. If we fail to realloc, readText will return the FAIL constant, the program will print what ever the data structure holds, free it, print an error message and terminate itself.*/

        if(readText(index, (void **) &buffer) == FAIL)
        {
            printText(index, buffer);

            free(buffer);

            buffer = NULL; 

            puts("Could not allocate anymore memory.");

            exit(1);      
        }

        printText(index, buffer);

        free(buffer);

        buffer = NULL;
    }
    return 0;

    /*End of main method.*/
}

/*The print text method will receive a void pointer to the choosen method and the correspondig index.*/

void printText(int index, void *selectedMethod)
{
    ptr temp;

    char *temp2;

    int i = 0;

    int counter = 1;

    /*If the link list has been choosen, the methood will act accordingly, and the program will print what ever the linked list holds.*/

    puts("\t\t\t\t\t\t\t\t\t Block capacity check:");

    if(index == 1)
    {
        temp = (ptr) selectedMethod;

        while(temp != NULL)
        {
            printf("%s\t\t --->%ld\n", temp -> text, strlen(temp->text));

            temp = temp -> link;
        }
    }

    /*If the buffer has been choosen, the method will act accordingly as well, and the program will print what ever the buffer holds. Every 60 chars, it will continue in a new line.*/

    if(index == 2)
    {
        temp2 = (char *) selectedMethod;

        while(temp2[i] != '\0')
        {
            printf("%c", temp2[i]);

            i++;

            if(i == counter * (MAX_SIZE-1))
            {
                printf("\t\t   --- >  %d\n", i);

                counter++;
            }
        }

        printf("\t\t --- >  %d\n", i);
    }
}

/*The read text method is divided into two block, each of which is responsible for heandling a different approach.*/

int readText(int index, void **selectedMethod)
{
    char *temp2;

    ptr temp;

    char input;

    int i = 0;

    int counter = 1;

    /*The block that responsible for the link list management.*/

    if(index == 1)
    {
        temp = (ptr) *selectedMethod;

        while((input = getchar()) != EOF)
        {
            if(input != '\n')
            {
                temp -> text[i] = input;

                i++;
            }

            /* Every 60 characters, the program will allocate a new node to the linked list and continue reading the input, untill it is done or can not allocate anymore memory.*/

            if(i == MAX_SIZE)
            {
                temp -> text[MAX_SIZE-1] = '\0';

                i = 0;

                temp -> link = calloc(1,sizeof(struct node));

                if(!(temp -> link))
                {
                    return FAIL;
                }

                temp = temp -> link;
            }
        }
    }

    /*The block that responsible for the buffer management.*/

    if(index == 2)
    {
        temp2 = (char *) *selectedMethod;

        while((input = getchar()) != EOF)
        {
            if(input != '\n')
            {
                temp2[i] = input;

                i++;
            }

            /* Every 60 characters, the program will reallocate more memory to the buffer and continue reading the input, untill it is done or can not allocate anymore memory. Counter is used to keep track of the size of the current memory block.*/

            if(i == counter * (MAX_SIZE-1))
            {
                counter++;

                temp2 = realloc(temp2, counter * MAX_SIZE);

                if (!(temp2))
                {
                    return FAIL;
                }
            }
        }
    }

    return 1;
}

/*This method is responsible for clearing the linked list after the program has finished printing.*/

void freeList(ptr *cleaner)
{
    ptr pointer;

    while(*cleaner)
    {
        pointer = *cleaner;

        *cleaner = pointer -> link;

        free(pointer);
    }

    *cleaner = NULL;
}