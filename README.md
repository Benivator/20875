<<<<<<< HEAD
# Homework 0: `git` and `make` and `gcc`, Oh My!

### Due 8/31 at 11:59pm

## Goals

This homework serves several purposes:

1. Get you familiar with the homework submission system, which uses `git`
2. Get you familiar with using `make` to build, run, and test your programs
3. Get you familiar with some `gcc` options including conditional compilation

## Background

### Unix environments

The build and test environments that the course staff will use when grading your homeworks are Unix-based. In particular, we will be building and testing your code on `ecegrid` machines, which you can `ssh` to using the following command:

```
> ssh ecegrid.ecn.purdue.edu
```

> **See below for details on SSH**

You can also use ThinLinc to access the `ecegrid` machines. Through your web browser, you can go to [https://ecegrid.ecn.purdue.edu/main/](https://ecegrid.ecn.purdue.edu/main/), or you can download the desktop client.

If you are using Linux or macOS, you already have access to a Unix-like environment, which will let you develop your code in an environment similar to the test environment. If you are using Windows, we recommend installing the [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

> Note that these environments do not have exactly the same versions of compilers, etc., that 
>`ecegrid` does. For the kinds of programs we are developing in this class, it should not matter. 
>Nevertheless, you are responsible for making sure that your code runs properly in our test environment.

### ssh

You will be using the tool `ssh` (Secure Shell) in a couple of different ways in this class. You may be using it to connect remotely to `ecegrid`. You may (should) also be using it to connect to GitHub to develop and submit assignments. If you have a Unix environment set up, you will also have `ssh` installed, so you can use it immediately. You may also choose to install a tool like [https://www.putty.org](https://www.putty.org).

### git and GitHub

Our homework submission system is built around [GitHub Classroom](https://classroom.github.com). What this means is that your homeworks will be distributed as *git repositories*, and you will submit your homework by ``push''ing your code to GitHub. Part of the goal of this homework is to familiarize yourself with this process.

But even if we weren't using Github classroom, you should *still* use *version control* like git. Version control, especially backed by a cloud provider like GitHub gives you several benefits:

1. Being able to reverse changes you've made to a program if you made a mistake
2. Having a backed-up version of your program in case your computer crashes or storage fails
3. Being able to collaborate with other people [this one doesn't matter so much for this course]

The key feature of version control is that it maintains multiple *versions* of each file you have in your "repository." When you make a change to a file, like `foo.c`, you can tell `git` that you want to track the changes to the file:

```
> git add foo.c
```

You can add multiple changed files to a version:

```
> git add bar.c
```

And when you ready to "commit" the new version, you can tell `git` to do so:

```
> git commit -m "some message describing the changes"
```

Note that until you run `git commit`, there is no "new" version of either `foo.c` or `bar.c` created.

If you then make more changes to `foo.c`, *git remembers the old version, too*, and you can get back to it by either reverting the changes you've made, or explicitly "checking out" the older versions. If you're interested in the details of `git`, we recommend the guides at either [GitHub](https://guides.github.com/) or [Atlassian](https://www.atlassian.com/git). 

> Those of you that really want to dig into how `git` manages versions might find Atlassian's pages on (the three trees of git)[https://www.atlassian.com/git/tutorials/undoing-changes/git-reset] and (the different ways of managing versions)[https://www.atlassian.com/git/tutorials/resetting-checking-out-and-reverting]

You can create as many versions of your code as you want. We recommend `add`ing and `commit`ing your changes fairly frequently -- whenver you figure out one part of your code, for example -- to make sure that you don't lose work or accidentally delete important changes.

If your repository has a version stored *remotely*, like at GitHub, then you can further take advantage of `git`'s ability to manage copies of code in multiple places. You can get a copy (a "clone") of the repository by running:

```
> git clone [url]
```

Then you can manage versions using `add` and `commit` like above. When you're ready to update the remote copy of your code, you can "push" your local changes to GitHub using:

```
> git push
```

This syncs up your local repository with GitHub, which means that your code is now safely on the cloud. We recommend `push`ing often -- certainly whenever you get one part of the assignment "solved."

Note that if there are updates to your assignment code on GitHub that you don't have on your local copy (say, if you're working on multiple computers), you can update your *local* repository by typing:

```
> git pull
```

One of the ways that `git` and `ssh` interact is that you can use *SSH keypairs* to authenticate with GitHub (in fact, as of this August, you cannot use a regular password to authenticate `push`es and `pull`s). You can see instructions for setting up SSH authentication [here](https://docs.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh).

### gcc

A compiler is the tool that translates the source code you write (the C program) into the machine code your computer understands. You will be getting very familiar with compilers in this course (and you should take ECE 46800 if you want to learn more!)

While to a large extent the code we write will not depend hugely on *which* C compiler you use, the compiler we will use to build and test your code is `gcc`. (Other popular compilers include `llvm` and Microsoft Visual C, or `msvc`.)

gcc takes one or several `.c` files as input. If you want to specify the output file's name add `-o name`
If you do not specify the name, the default output file is called `a.out`.

If you read the manual (also called the "man page") of `gcc`, you can find many options. In this class, you should always use `gcc` in the following way.

`> gcc -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror`

* `-std=c99` means using the C standard announced in 1999
* `-g` means enabling debugging
* `-Wall` means enable warning messages
* `-Wshadow` means detect the use of shadow variables
* `-pedantic` means restricting standard C
* `-Wvla` means detecting the use of variable length arrays
* `-Werror` means treating warnings as errors (so your program will not compile)

These warnings are your first "line of defense" in writing good programs. There have been many cases when students forgot to use these options, failed to detect these problems early, and spent many hours debugging.

Here are some common warning messages:

* Creating a variable but never using it (most likely it is mistyped)
* Creating a function but never using it (most likely it is mistyped)
* Reading  a variable before a value is assigned (C does not initialize variables. If a variable is not assigned, its value is garbage, not necessarily zero)
* Writing code that can never be reached
* Assigning a value to a wrong type
* Creating two variables that have overlapping scopes (called shadow variables)

While many of these issues are not necessarily going to break your code, when they arise they are usually the results of mistakes. It is better to let the compiler catch these issues for you then let them mess up your program.

### Compiling multiple files

We will often compile programs that use multiple files. For example, `foo.c` may contain a `main` function that you want to run, but it will invoke a function defined in `bar.c`. When dealing with multi-file projects, we need to make sure of a few things:

1. Files can see the necessary function *declarations* --- if I invoke a function in `foo.c` that is defined in `bar.c`, the compiler needs to know the *signature* of the function: how many arguments it has, what its name is, what its return type is. This information is contained in a function *declaration* that needs to be in `foo.c` even though the function itself is in `bar.c`. The way we usually do this is by putting the function declaration in a *header* file, `bar.h` that is *included* in `foo.c` using the directive `#include "bar.h"`
2. We compile each source file. You can do this by running `gcc -c foo.c`, which will create an output file called `foo.o`. This output file is *not* an executable. It an *object file* that contains the compiled code that was in `foo.c`.
3. We *link* the object files together into an executable, by running `gcc foo.o bar.o -o out`, which will combine the two object files into an executable called `out`.

Note that there are other ways to combine code from multiple files into an executable (such as statically and dynamically linked libraries), but they are beyond the scope of this course.

### Conditional compilation

In some cases, you want to turn on or off sections of code. For example, you may want to print debug messages showing the progress and states of your programs, such as:

`printf("The value of x is %d\n", x);`

Once you're done with your program, deleting these debug messages can be tedious. (And you might miss some, or accidentally delete the wrong line!)

Fortunately, *conditional compilation* can come to our rescue. The following code:

`#ifdef DEBUG`
`printf("The value of x is %d\n", x);`
`#endif`

will only execute if the symbol `DEBUG` is defined somwhere earlier in the program:

`#define DEBUG`

If that symbol is not defined, then everything between `#ifdef` and `#endif` is ignored by the compiler. We can also define symbols on the command line, by using the `-D` flag:

`gcc -c foo.c -DDEBUG`

means to compile `foo.c` with the symbol `DEBUG` defined. As you can imagine, this can make it easier to add debugging code to your program.

We will make heavy use of conditional compilation to test your code---it will allow us to turn off different parts of your code and substitute our own implementations to test.

> You might notice that `#ifdef`, `#define`, `#endif` and `#include` all start with the `#` symbol. These are examples of *preprocessor directives* that the **C preprocessor** uses to rewrite your C file into a different C file that `gcc` will ultimately compile. The ins and outs of the preprocessor are beyond the scope of this course, though we might discuss some tricks in class.

You can define multiple symbols. For example, if you want to test two different solutions of the same function, you can do the following:

```
#ifdef SOLUTION1
void func(....) // solution 1
{
    ....
}
#endif

#ifdef SOLUTION2
void func(....) // solution 2
{
    ....
}
#endif
```

If you have `-DSOLUTION1` after `gcc`, the first solution is included. If you have `-DSOLUTION2` after `gcc`, the second solution is included.

Just like you can check for whether a symbol is defined, you can also check to see if it is undefined, using `#ifndef`. You can also create an "if-then-else" setup:

```
#ifdef SYMBOL
...
#else
...
#endif
```

(See `main.c` in the included files for an example of this construction)


### make and Makefiles

*Makefiles* let you define complicated sets of commands to build your projects.

Makefiles consist of a series of rules:

```
[target] : [dependences] 
	[command 1]
	[command 2] ...
```

A *rule target* is the name of the rule. The dependences are the files the rule depends on. The commands are what to do when the rule is “fired.” Note: there *must* be a tab before each command.

A rule is fired in one of two ways: (i) it is directly invoked (by calling “make [target]”) or (ii) it is invoked by another rule that is fired.

When a rule is fired, it goes through the following process:

1. If a dependence has a rule in the Makefile, fire that rule (using this same process)
2. Once all dependences have been fired, check to see if `target` is “out of date”: interpret `target` as a filename, and see if the timestamp on the file is older than the time stamp on any of its dependences. If it is, the target is “out of date.” If there is no file named `target`, the target is always assumed to be out of date. If there are no dependences and `target` exists, `target` is assumed to be up to date.
3. If the target is out of date, execute the list of commands

You can use Makefiles to orchestrate complicated build processes.

If you type `make` without a target, make will fire the first rule in the Makefile. Otherwise, if you type `make [target]`, it will fire the rule named `target`.

We usually define a target called `clean` whose job it is to clean up any intermediate files generated during the build process. This can also be used to remove all generated targets to force recompiling everything.

We can also use Makefiles to test our code. For example, we might want to run a number of tests after building the project:

```
test : all
	./a.out testfile1
	./a.out testfile2
```

Running `make test` will build the target `all` (compiling your project), followed by running the commands to test your code. (Note that because there is no file named `all`, `make` assmes that the target is out of date and runs it every time.)

Makefiles also let you define macros to reuse the same commands over and over. For example, we can define GCC as a macro that invokes gcc the way we want:

```
DEBUG = -DDEBUG
CFLAGS = CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS) $(DEBUG)
```

Note that we use `$(MACRO_NAME)` to insert the macro into other places, including commands.

There are some "recipes" for making files that you may want to use over and over again. For example, to create  `foo.o`  from a `foo.c` file, you might write the rule:

```
foo.o : foo.c
	gcc -c foo.c -o foo.o
```

And similarly to create `bar.o` from `bar.c`, you might write:

```
bar.o : bar.c
   gcc -c bar.c -o bar.o
```

Which looks pretty redundant! You can instead use a *pattern rule* to create a generic recipe that follows this pattern:

```
%.o : %.c
	gcc -c $< -o $@
```

Makefiles can get much more complicated than this, but their full power is beyond the scope of this course.

## Tasks

In this homework, you will need to do the following:

1. Write a selectin sort routine
2. Use conditional compilation so that the selection sort routine can sort ascending or descending based on a compiler flag
3. Write a new make target to generate code that sorts in ascending order
4. Learn to submit your code

## What you need to do

### 1. Set up your GitHub account and repository

To submit code in this class, you need to have a GitHub account so that you can clone repositories and submit homeworks. If you do not already have a GitHub account, please create one at [https://www.github.com].

Once you have a GitHub username, let us know what it is so we can link your submissions to your Purdue account. To do so, fill out [this form](https://forms.gle/AE6aTFzrNAw6ydfP8). **If you do not fill out this form, we will not be able to assign your grades properly.**

Then, create your HW0 repository. To do this, click on the link provided in Brightspace. This will set up a repository containing this README as well as starter code for HW0.

### 2. Clone your repository

To set up your repository on your local machine to write the code we want, you'll have to do the following:

```
> git clone git@github.com:PurdueECE264/hw0-<username>.git
```

Then you can `add`, `commit`, and `push` as described above.

The starter files in your repository are:

1. `main.c`: a file that contains the `main` function that reads an array of integers from a file. It also contains some helper functions to print an array or tell if an array is sorted. You do not have to alter this file in this homework. Though it can be helpful to look
2. `sort.c`: a file that contains an implementation of selection sort that sorts an array in descending order.
3. `sort.h`: a header file with the declaration of the selection sort routine.
4. `Makefile`: a Makefile that builds the project.

### 3. Implement selection sort

The routine `ssort` in `sort.c` is intended to use selection sort to sort elements in descending order. We will discuss selection sort in class, and you may also find the [Wikipedia article](https://en.wikipedia.org/wiki/Selection_sort) helpful. 

In a nutshell, selection sort works by scanning the entire array for the minimum element, then swapping it into location 1, then scanning the entire array *except for the first element* for the smallest element and swapping it into location 2, and so on. In this way, it builds up the sorted list from left to right, constantly looking for the smallest element in the *rest* of the list to put at the end of the sorted section.

> Selection sort is *not* the fastest way to build a sorting routine. Later in class, we will discuss other, faster sorting routines like merge sort and quicksort.

Your task is to implement `ssort.c` so it can sort the array in *descending* order. If you run `make test` and see sorted arrays in *descending order* when you are done, then you will have gotten this step right.

### 4. Add conditional compilation

We now want to add conditional compilation to your code. If you pass the flag `-DASCENDING` during compilation, you should generate a version of the project that sorts the array in *ascending* order instead.

You should thus do two things:

1. Modify `sort.c` to add conditional compilation flags that will compile a version of selection sort that sorts in ascending order if the symbol `ASCENDING` is defined. (You can look at `main.c` for some inspiration). You should be able to do this by only modifying a line or two of code from step 3, but we will not penalize you for doing more work.
2. Add a new compilation target to `Makefile` called `ascending`. When you type `make ascending`, it should set up compilation so the ascending version of selection sort is used. When you type `make` or `make all`, it should generate the default descending version of selection sort.

Note that the make target `test-ascending` will use the same test cases as `test` to check that your selection sort routine correctly sorts numbers into ascending order.

### 5. Submit your code!

As you develop your code, do not forget to use version control. As you solve parts of the problem, use `git add` and `git commit` to preserve the latest version of the code. Periodically use `git push` to sync your code with your GitHub repository.

When you are ready to submit your code for grading, you need to *tag* the version you want us to grade. A tag is a way of assigning a name to a particular version of code. We look for the tag `final_ver` to decide what to grade.

1. Tag your local code: `> git tag final_ver`
2. Push the tag to GitHub: `> git push origin final_ver`

If you later decide you want to update the version you submit, you can tag a different version:

1. Update the tag: `> git tag final_ver -f`
2. Push the tag to GitHub: `git push origin final_ver -f`

We will grade whichever version has the `final_ver` tag at the due date.

## Good luck!

Good luck
=======
# Homework 1

## Due on: Friday, 01/21/2022 at 11:59 pm ET. 

Welcome to ECE 20875, Python for Data Science! In this class, you will learn the basics of various topics in data science, and, along the way, learn how to write code in Python.

## Goals

This homework has several objectives:

1. Get familiar with git and GitHub: cloning, committing, tagging, etc.
2. Get familiar with the GitHub Classroom submission system.
3. Write a simple Python script demonstrating Python fundamentals.

## Grading

1. 30% of the homework corresponds to committing and pushing (submitting) the homework. If you were able to commit and push the homework, we assume you know the basic Git commands.
2. 35% - Problem 1 
3. 35% - Problem 2

## Background

### Version Control

Git is a version control tool. What is version control? It is a means of retaining
organized versions of your code as you work on a project. This is especially important 
in industry for code organization, collaborative projects, and large projects spanning many files.
Further information on how GitHub might be used in collaborative projects can be found at https://guides.github.com/ 
if interested. You will not be concerned with branches in this class.

When working with repositories for this class, there are three main parts to working with git: 
1. The remote repository (on GitHub) 
2. The local repository (on your device/ Scholar account) 
3. Your working files (on your device/ Scholar account) 

Note: Git is the tool you use to do version control. GitHub is where your remote repository is hosted.

When you do a `git add` followed by `git commit`, you are updating your local repository.
When you do a `git push`, you are updating the remote repository on GitHub (supervisors or collaborators can now see your changes).

The key commands you will need to use in this assignment (and at other times) are:

1. `git clone <url>`: This sets up a local repository on your machine by "cloning" (copying) a remote repository; in this case, a repository is set up on GitHub.
2. `git add <filename>`: When you have changed a file, you can "stage" it for the next version (i.e., tell git that you want the changes in this file to appear in the next version) using this command. (Note, when you want to just add/stage changes made to all files in a directory, consider "git add --all". Changes may include deletion of certain files.)
3. `git commit -m "<message>"`: Creates a new version of your code. This new version contains all changes staged in the previous version of the code. This new version only exists in your local repository.
4. `git push`: Updates the remote repository (on GitHub) with all the changes that you have `commit`ted to your local repository. Note that uncommitted changes will not appear on GitHub.
5. `git pull`: Updates your local repository with any remote changes that are on GitHub and have not yet been reflected in your local repository. Note that there may be some conflicts between what GitHub knows about a file and what your local repository knows, and this command will notify you if that happens (fixing those conflicts requires more work). You should always run `git pull` and resolve any conflicts before running `git push`.
6. `git status`: This shows you the status of any files in your local repository. In particular, it shows you any files that you have modified, but not yet `add`ed, and any files that you have `add`ed but not yet `commit`ted.

We will be using the latest version of your code (files present after your most recent push) at 11:59pm on the submission deadline for grading.

Push your code to GitHub often. Not only does that prevent you from
losing any code if you accidentally delete anything, it helps us help you
debug, by giving us access to your latest code.

NOTE: You should verify that your code files are showing up correctly on GitHub once you have `push`ed them from your local machine.

### Python

Familiarize yourself with basic python scripting from the lecture notes. The Python language documentation is online at https://docs.python.org/3/

This assignment has the potential to involve:
1. Initializing variables. Recall that unlike C, C++, etc., Python does not require a data type declaration.
2. Arithmetic (+, -, \*, /, %, **, //), logical (`and`, `or`, `not`), and comparison (<, >, <=, >=, ==, !=) operations.
3. Control flow (if, elif, else) structures.
4. A basic understanding of lists and how to index them.

A caution: DO NOT use `&` and `|` as logical operators. They are for bitwise operations, which should not be used for conditional statements. Using them could lead to very hard bugs to find. As an example, `2 & 1` will give `0`, which will be read as `False` whereas `2 and 1` gives `1`, which is read as `True`. Instead of `&` and `|` you should use `and` and `or` in Python. 

Remember that indentation is Python's inherent way of organizing code blocks.

Ex:

```
if True:
    print('HW1 is truly fantastic.')
print('I concur.')
```



## Getting Started

Clone your HW1 repository by clicking on the GitHub classroom link distributed through Piazza. This will create a repository on GitHub with your username. Use `git clone` to clone that repository locally. If you face issues with this, then you might want to look into using 'ssh key' to clone (directions at the end of this README). 

There should be three files in your repository when you begin:

1. This README file.
2. `Problem1.py`, a python file with one line of code, which contains a single number.
3. `Problem2.py`, a python file with one line of code, which contains a single number.

## Instructions

After completing the 'Getting Started' section above, you will complete 'Problem1.py', 'Problem2.py' and verify it works using the provided test cases. You may then submit your code to GitHub using the git commands above and following the 'What to Submit and How' section below.

### Problem 1

Modify Problem1.py by adding additional lines of code so that it solves the following problem:

Determine whether a given number is even _and_ part of the Fibonacci Sequence. The Fibonacci Sequence is as follows 0, 1, 1, 2, 3, 5, 8, 13.... 
For more information about Fibonacci sequences Click [here](https://www.geeksforgeeks.org/program-for-nth-fibonacci-number/)
The sequence is comprised exclusively of positive integers.

Hint 1: A positive number, n, is part of the Fibonacci sequence if either (5n^2 + 4) or (5n^2 - 4) is a perfect square. That is, if the square root of either (5n^2 + 4) or (5n^2 - 4) is a whole number, then n is a perfect square, and thus a Fibonacci number.

Hint 2: Recall that multiple conditions can be checked in one statement. For example, 
```
if (condition 1) and (condition 2) and (condition 3):
    # do some action 
```

If a number is even, positive, and part of the Fibonacci sequence, your code should print "Yes". If any one of these conditions is not met, your code should print "No".
If your input is number = 2 or 34 or 144, the output should be "Yes".
If your input if number = 4 or 1 or 5 or -8, the output should be "No". Note that 1 and 5 in this example are part of the Fibonacci Sequence but they're not even. Additionally, negative numbers, e.g., -8, can *not* be part of the Fibonacci Sequence.

You may change the variable "number" to any number you want to check your code against, be sure to change it back to "100" before submitting.

### Problem 2

Modify Problem2.py by adding additional lines of code so that it solves the following problem:

Determine whether a given day of January 2022 is a 'Weekend' or a 'Weekday'.  We will consider a Weekend as Saturday or Sunday. 
For example, if the input is n = 21 the your code should print "Weekday".

The input `n` is limited to being in the range of [1, 31] (inclusive). If the number is not valid (e.g. 35) then your code should print "Not valid".

Hint: You can solve this problem in multiple ways, feel free to consider your own approach. One existing approach is to use the Zeller formula Click [here](https://www.geeksforgeeks.org/zellers-congruence-find-day-date/).

You may change the variable n to any number you want to check your code against, be sure to change it back to "21" before submitting.

## What to Submit and How

The only files you need to modify for this homework are `Problem1.py` and `Problem2.py`.

Once you have a version of your code (that you have `commit`ted using `git commit` and `push`ed using `git push`) that you are happy with, you are done! Do not make changes to code that has been provided to you except where specified.

**NOTE: You should verify that your code files are showing up correctly on GitHub once you have `push`ed them from your local machine.**

You might want to try using the ssh key if you face issues while submitting homework1, see the final section of the README for information on this.

## Resubmitting:
If you want to update your submission before the deadline then re-commit and re-push your files. Ensure that you do both `git commit` and `git push` on your updated files so that they appear on GitHub. 


## SSH key (if needed)
Directions for adding ssh key on GitHub:
Here is a link to instructions if you need more help: https://help.github.com/en/github/authenticating-to-github/adding-a-new-ssh-key-to-your-github-account

You may want to use ssh keys to clone your repository if cloning using https gives you problems. To do this, you need to first generate an ssh key pair on your local machine. On your local machine, open a terminal and type:

1. ssh-keygen -t rsa -C "your_email@example.com"
   make sure "your_email@example.com" is the same email used on GitHub

2. Press "Enter" when prompted where to store keys. This will result is saving the keys to a default location.

3. Enter a secure pass phrase that you will remember. 

4. That's it! Keys will be saved in .ssh/

Now, you must enter your public key on GitHub. To do this, type 'cd .ssh/' on your local machine and then copy your PUBLIC key. Then, login to your GitHub repo, click on your profile picture in the upper right hand corner, click on Settings, click on SSH and GPG Keys, click New SSH Key, create a title so you will know which computer the ssh key corresponds to, paste the PUBLIC key, and finally click Add SSH Key. 
>>>>>>> f228fb38e37068481cdeb9ead3fbcf9cf544e57b
