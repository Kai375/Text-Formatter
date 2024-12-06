# Text-Formatter
**Receive a text string, and format it into shape.**

This program reads from the standard input a text consisting of characters (ASCII codes). 

The number of characters in the input is *not known* in advance and is *not blocked*. 

The program will only end the reading when an EOF condition is detected in the input. 

After reading **all the text** (all characters), the program will print the text to the standard output, in lines of fixed length of 60 characters.

The text is stored in the program's memory, in a dynamic data structure - a structure that can be expanded as needed.

If the input is very long, and there is no more space in memory to expand the data structure, then we will stop the input, print 

the text that has been stored so far in the 

data structure, and issue a clear error message.


The program's data structure is implemented by two different methods, with the user being prompted to choose one of them at the beginning 

of the current run.


# Description of the methods:

 

1. **Buffer:**
   
   A single buffer containing all the text, and will be allocated using the standard library function *calloc*.

   If the buffer runs out of space while inputting, then the buffer will be increased using the standard library function *realloc*.

   The initial size of the buffer is defined as **fixed** in the program, and its size is at least 60 bytes.

    Any increase in the buffer will add another number of bytes to the initial size.



3. **Linked-list:**

   A linked list of elements, where each element is a **fixed-size** buffer, containing a piece of text.
   
    The size of the buffers will be defined as fixed in the program, and will be at least 60 bytes.
   
    Any increase in the buffer will add another number of bytes to the initial size.

   The initial allocation is of a list with one element.
   
    If the current element (buffer) runs out of space during input, then another element will be allocated

   using the *calloc* function, and added to the linked list.




# Functions:


   1.  **ReadText-** Reads the text from the standard input and stores it in the data structure.
   
        The function accepts as parameters the type of the selected data structure (one of the two implementations above),
      
        and a pointer to the data structure (initial allocation of the data structure will be performed in the main program).
   
        The function increases the data structure as needed during input.
   
        If no more memory can be obtained using call/malloc, then the function stops the input and returns an error code.

        The text that has already been input remains in the data structure.
   
       The function **does not perform** any output.
      



   3.  **Print text-** A function that is executed after the input is complete, and prints to the standard output all the text in the data structure.
   
       The function accepts as parameters the type of the data structure and a pointer to the structure.
   
       The output lines will be of a **uniform length** of 60 characters (except perhaps the last line).



# The main program's flow is as follows:
  
  The program asks the user to choose the implementation method of the data structure, then 
  
  allocates the selected data structure, **with the initial size**. 
  
  Next, the program asks the user to start passing the text. 
  
  And calls the ReadText function to read the text from the input, and then the PrintText function (each function will be called **once** only). 
  
  Finally, if the PrintText function returned an error code, then the main program will print a clear error message (after printing the text).


# Additional requirements:

The length of the input line, and the number of lines in the input, are not known in advance and are not restricted.

The text in the input can contain all ASCII codes, except the character `\0` (we can assume that the input is valid).

All characters from the input will be stored in the data structure, except the character `\n`, which must be **skipped** every time it appears 

**and not inserted** into the structure.
    
