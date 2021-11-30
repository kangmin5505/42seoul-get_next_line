# 42seoul-get_next_line
## Common Instructions
- Norm
- No error(segmentation falut, bus error, double free, etc)
- No leak
- Submit Makefile which will compile your source files
  - Flags -Wall, -Wextra and -Werror
  - Use cc(compiler)
  - No relink
  - Least contain $(NAME), all, clean, fclean, re
- To turn in bonuses to your project, you must include a rule bonus to your Makefile, which will add all the various headers, libraries or functions that are forbidden on the main part of the project.\
Bonuses must be in a different file _bonus.{c/h}.
- If your project allows you to use your libft, you must copy its sources and its associated Makefile in a libft folder with its associated Makefile. Your project's Makefile must compile the library by using its Makefile, then compile the project.

## Mandatory Part
![image](https://user-images.githubusercontent.com/74703501/143185646-01e671d9-62d7-49ab-bc9e-838746b12262.png)
- Calling your function get_next_line in a loop will then allow you to read the text available on the file descriptor one line at a time until the end of it.
- Your function should return the line that has just been read. If there is nothing else to read or if an error has occurred it should return NULL.
- Make sure that your function behaves well when it reads from a file and when it reads from the standard input.
- libft is not allowed for this project. You must add a get_next_line_utils.c file which will contain the functions that are needed for your get_next_line to work.
- Your program must compile with the flag -D BUFFER_SIZE=xx which will be used as the buffer size for the read calls in your get_next_line. This value will be modified by your evaluators and by the moulinette.
- The program will be compiled in this way:
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \<files>.c.
- Your read must use the BUFFER_SIZE defined during compilation to read from a file or from stdin. This value will be modified during the evaluation for testing purposes.
- In the header file get_next_line.h you must have at least the prototype of the function get_next_line.
- lseek is not an allowed function. File reading must be done only once.
- We consider that get_next_line has undefined behavior if, between two calls, the same file descriptor switches to a different file before reading everything from the first fd.
- Finally we consider that get_next_line has undefined behavior when reading from a binary file. However, if you wish, you can make this behavior coherent.
- Global variables are forbidden.
- Important: The returned line should include the '\n', except if you have reached the end of file and there is no '\n'.

![image](https://user-images.githubusercontent.com/74703501/143991904-d387107e-9419-45cf-bb97-bc76fd664890.png)
![image](https://user-images.githubusercontent.com/74703501/143992016-643a8ab8-22bc-4dd1-8e82-995073fa0436.png)
![image](https://user-images.githubusercontent.com/74703501/143992066-89465e2c-3cd7-4dad-a212-b8eff5f58480.png)

## Bonus part
- Turn-in all 3 mandatory files ending by _bonus.[c\h] for this part.
- To succeed get_next_line with a single static variable.
- To be able to manage multiple file descriptors with your get_next_line. For example, if the file descriptors, 3, 4 and 5 are accessible for reading, the you can call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without losing the reading thread on each of the descriptors.

## Concepts
### Static variable
In computr programming, a static variable is a variale that has been allocaed "statically", meaning that its lifetime (or "extent") is the entire run of the program.\
This is in contrast to shorter-lived automatic variables, whose storage is stack allocated and deallocated on the call stack; and in contrast to objects, whose storage is dynamically allocated and deallocated in heap memory.\
\
Variable lifetime is contrasted with scope (where a variable can be used): "global" and "local" refer to scope, not lifetime, but scope often implies lifetime. In many languages, global variables are always static, but in some languages they are dynamic, while local variables are generally automatic, but may be static.\
\
In general, static memory allocation is the allocation of memory at compile time, before the associated program is executed, unlike dynamic memory allocation or automatic memory allocation where memory is allocated as required at run time.

### Addressing
The absolute address addressing mode can only be used with static variables, because those are the only kinds of variables whose location is known by the compiler at compile time.\
When the program (executable or library) is loaded into memory, static variables are stored in the data segment of the program's address space (if initialized), or the BSS segment (if uninitialized), and are stored in corresponding sections of object files prior to loading.

### Scope
In terms of scope and extent, static variables have extent the entire run of the program, but may have more limited scope./
A basic distinction is between a static global variable, which has global scope and thus is in context throughout the program, and a static local variable, which has local scope./
A static local variable is different from a local variable as a static local variable is initialized only once no matter how many times the function in which it resides is called and its value is retained and accessible through many calls to the function in which it is declared, e.g. to be used as a count variable./
A static variable may also have module scope or some variant, shuch as internal linkage in C, which is a form of file scope or module scope.

### Object-oriented programming
In object-oriented programming, there is also the concept of a static member variable, which is a "class variable" of a statically defined class, i.e., a member variable of a given class which is shared across all instances (objects), and is accessible as a member variable of these objects./
A class variable of a dynamically defined class, in languages where classes can be defined at run time, is allocated when the class is defined and is not static./
/
Object constants known at compile-time, such as string literals, are usually allocated statically./
In object-oriented programming, the virtual method tables of classes are usually allocated statically./
A statically defined value can also be global in its scope ensuring the same immutable value is used throughout a run for consistency.

## What I Learned
1. File descriptor
2. Exception
3. Memory

### General Reviews
get_next_line 과제에서는 file descriptor를 인자로 받아서 file을 읽고, 한 줄을 출력하는 함수를 구현했다.\
file descriptor란 file을 다루기 위한 정보가 들어 있는 변수로, 이를 사용해서 file을 읽었다.\
그 다음 개행문자를 기준으로 한 문장을 반환했다.\
이 과제를 하며 가장 어려웠던 부분은 메모리 할당과 메모리 반환이었다.\
왜 사람들이 c와 c++언어를 공부하며, 메모리 관련해서 곯머리를 앓는지 이 과제를 통해 잠시나마 느꼈다.\
분명 나는 메모리를 할당하고 반환했다고 생각했는데 프로그램이 실행시켜보면, 메모리 누수나 double free가 났다.\
다음 과제들도 메모리를 사용할 거 같은데, 이 부분을 중점으로 메모리 관련 에러를 최소화 하도록 코드를 짜야겠다.G
