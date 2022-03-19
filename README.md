# CS 50 - Notes

<br>

## Class 1:
  - ### _Summary and Lecture_:
    - __C language__: data types, loops, branches (if/else), functions (returning values, declaration X assignment), variables, consts, I/O;

    - __Lecture__: [CS-50: Class 1](https://cs50.harvard.edu/x/2022/weeks/1/);

    - __File `calculator.c` implements all points mentioned in this class, also `mario.c` is an important example for loop__

  <br>
  
  * ### _To run C source code_:

    - <strong>It is <u>mandatory</u> to install cs50 library (lcs50)</strong>: 
      
      - [CS 50: lib for C <cs50.h> - Installation Doc](https://cs50.readthedocs.io/libraries/cs50/c/)
      
      <br>
    - <strong>(_Troubleshooting_) To compile on <u>Ubuntu</u>:</strong>

      1. Instead of __make, <u>in case of any errors</u>,__ add following script in a file in your user directory (`~`), named as, let's say, `run` :

          * 
            ```(bash)
            #!/usr/bin/env bash

            gcc ./$1 -o b -lcs50 && ./b && rm b
            ```

            > _It compiles based on source code filename informed as first argument of the script, ensures it will use cs50 lib in the process, then execute it and finally, after execution, it removes the (executable) binary_ 

      </br>

      2. Now allow it to execute:

          *
            ```
            chmod u+x ~/run
            ```

      3. **Done!** Now you can run directly from source code, in any directory, without remaining binaries, by running like examples below:
      
          * Using relative path (from current directory): 
          
            ```
            ~/run ../relative/path/to/file_name.c
            ```

          * Or any source code in the current directory:

            ```
            ~/run file_name.c
            ```
</br>

## Class 2:
