# To-Do List

## A simplified, command-line To-Do list / Task Manager.

Welcome to my first project (ever). This was built primarily for practice, also serving as a hands-on way for me to delve deeper into the C programming language (and Makefile!). 
At its core, this to-do list provides you with a simple list tracking your tasks, using file I/O.
More specific, you can:

* Add a task to the list,
* Remove a task from the list,
* Update the task's status (mark DONE), or its description,
* Print the whole list,
* Undo/takeback last action

## Usage example

Here are some screenshots showcasing the functionality of the project:

1. Main menu

![Screenshot 2024-04-17 152321](https://github.com/ConXan/To-Do-List/assets/146641298/c477807e-7ad1-4fde-9c93-79b47c024402)

 ㅤ

2. Random list, with the third task completed

![Screenshot 2024-04-17 151908](https://github.com/ConXan/To-Do-List/assets/146641298/23145d9f-39f5-4dce-9bd9-da179bdafe4f)

ㅤ

3. Deletion of the 2nd task from the previous example

![Screenshot 2024-04-17 153121](https://github.com/ConXan/To-Do-List/assets/146641298/a97ee101-7d01-4483-807c-b892a1f41d8f)

![Screenshot 2024-04-17 153242](https://github.com/ConXan/To-Do-List/assets/146641298/68709d88-3258-41a2-89c7-dc04d947a202)

## Installation

### Prerequisites

Having installed the GNU C Compiler (gcc) is obligatory. If you haven't installed it yet, you can download it from the official GNU website or install it via your package manager.
Also having downloaded Makefile and Git will make the whole process way more straightforward.

### Linux 

**Clone the Repository**
```bash
git clone https://github.com/ConXan/To-Do-List.git
```

**Navigate to the corresponding directory**
```bash
cd To-Do-List
```

**Compile with Makefile**
```bash
make
```

*OR* (if you don't have Makefile installed)
```bash
gcc -Iinclude -c -o obj/fun1.o src/fun1.c
gcc -Iinclude -c -o obj/fun2.o src/fun2.c
gcc -Iinclude -c -o obj/main.o src/main.c
gcc -o task obj/fun1.o obj/fun2.o obj/main.o
```
**Run the program**
```bash
./task
```
Done! Now you can use **./task** (while in the directory) whenever you want to use the program.

### 2. Windows
Not entirely supported on Windows yet (found some minor issues), however you can still install the project following the aforementioned instructions, or first download it as a ZIP, extract the contents, navigate to the corresponding directories and compile manually with the commands above. 

## Contributing

Contributions, feedback, and bug reports are welcome and greatly appreciated! If you have ideas for new features, enhancements, or bug fixes, please feel free to open an issue or submit a pull request.
If you encounter any issues while using the software please let me know.

## Notes about the project 

### Files
main.txt is the file in which the list is stored, and prev.txt stores the previous status of a list (after an action occurs). 

back.txt and count.txt are both first initialized with 0 and are auxiliary files in the project. 

temp.txt is a temporary file that assists some functionalities during the runtime of the program 

### Misc
In general, sscanf() and snprintf() are used a lot.
The former, to extract the individual components of a string, such as its rank in the list, or its description for further manipulation, and the latter to construct the desired string and safely (no buffer overflow:) store the string.

The task's description can be up to 100 characters long. If you input more than that, it won't necessarily oveflow, it will just write up to 100 characters plus the NULL terminator.

The addition of the Task struct is just for practice reasons only, the same result could have been achieved without its use, however it provides the overall project with clarity.
