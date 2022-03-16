# CS 50 - Notes

<br>

## Class 1:
  - ### _Summary and Lecture_:
    - __C language__: data types, loops, branches, functions (returning, declaration X assigignment), variables, consts, I/O;

    - __Lecture__: [CS-50: Class 1](https://video.cs50.io/Na2wiHOnzXU?screen=sqgyiZCQ6Y8);

  <br>
  
  * ### _To run C source code_:

    - <strong>It is <u>mandatory</u> to install cs50 library (lcs50)</strong>: 
      
      - [CS 50: lib for C <cs50.h> - Installation Doc](https://cs50.readthedocs.io/libraries/cs50/c/)
      
      <br>
    - <strong>(_Troubleshooting_) To compile on <u>Ubuntu</u>:</strong>
      - Instead of __make__, in case of any errors, add following script in a file in your home directory (`~`), named as, let's say, `run` :

        ```(bash)
        #!/usr/bin/env bash

        gcc ./$1 -o b -lcs50 && ./b && rm b"
        ```

      * Now allow it to execute:
        ```
        chmod u+x ~/run
        ```
      * **Done!** Now you can run directly from source, in any directory, without remaining binaries, by running:
        
        * Using relative path (from current directory): 
        ```
        ~/run ../relative/path/to/file_name.c
        ```

        * Or any source code in the current directory:
        ```
        ~/run file_name.c
        ```

<br>

## Class 2: