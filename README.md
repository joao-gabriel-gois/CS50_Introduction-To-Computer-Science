# CS 50 - Notes

### **Harvard's introduction to Computer Science course with solved and submitted exercises.**

<br>

<u>From its oficial website:</u>

> _Introduction to the intellectual enterprises of computer science and the art of programming. This course teaches students how to think algorithmically and solve problems efficiently_.
>
> * _**Topics include abstraction, algorithms, data structures, encapsulation, resource management, security, software engineering, and web programming.**_
>
> * _**Languages include C, Python, and SQL plus HTML, CSS, and JavaScript.**_
>
> * _**Problem sets inspired by the arts, humanities, social sciences, and sciences.**_
>
> * _**Course culminates in a final project.**_
>
>
> *Designed for concentrators and non-concentrators alike, with or without prior programming experience. Two thirds of CS50 students have never taken CS before.*
>
> *Among the overarching goals of this course are to inspire students to explore unfamiliar waters, without fear of failure, create an intensive, shared experience, accessible to all students, and build community among students.*
>
>
<br>

 ### ⚠️ **This repo main goal is to share my version of Course's exercises**

## 📑 **Details: <u>[CS50 Official Website](https://cs50.harvard.edu/x/2022)</u>**
<br>

___
<br>

### ***[Optional]***: Check bellow info in order to study locally:
 * ### _To run C source code locally_:
    - <strong>It is <u>mandatory</u> to install cs50 library (lcs50)</strong>: 
      
      - [CS 50: lib for C <cs50.h> - Installation Doc](https://cs50.readthedocs.io/libraries/cs50/c/)
      
      <br>
    - <strong> To compile on <u>Linux / Unix</u> based OS using GCC:</strong>

      1. Instead of __make, <u>in case of any errors</u>,__ add script called `run` in a file in your user directory (`~`) - You can refer to [`_scripts/run`](_scripts/run) in this repo.

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
