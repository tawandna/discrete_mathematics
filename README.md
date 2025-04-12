# discrete_mathematics

Simply include it in your project

Use the *_exercise() function (where * is the task number, e.g., first_exercise() or second_exercise())

This will launch console input and data processing.

To run tests directly:

Place main in the same directory as the header

Compile

Run with --exercise* arguments (where * is the task number, e.g., ./a.out --exercise1 or ./a.out --exercise2). In this case, the program will automatically execute the solution function for the selected task number.

Key features:

Header-only design - just include and use

Each task has its own *_exercise() function

Supports both interactive console input and direct testing via command-line arguments

Simple execution: ./program --exercise1 runs the first task's solution