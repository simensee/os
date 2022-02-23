# Operativsystemer

## Øvinger TDT4186

In this practical exercise we are going to implement an alarm clock program in C.

### Run the code

To compile the code, you have to:

```
gcc -o alarmclock alarmclock.c
```

To run the code:

```
./alarmclock
```

### g. Test case documentation

Design four test cases that not only test a single functionality (like scheduling an alarm), but combination of functions of your program.

Describe each test case: what do you do to test this case, what does the test do, what is the expected result?

Are we supposed to write cases for usability tests?

#### First Test Case

The user wants to schedule an alarm and check if the alarm is added to the list and wait for it to go off.

1. What do you do to test this case?

2. What does the test do?
   The test tests if scheduling the alarm is working, by writing 's' in the input field and expecting tje

3. What is the expected result?
   The expected result is that the user successfully schedules an alarm that goes off to the right time, and is in the list of the other alarms as well.

#### Second Test Case

Schedule alarm, cancels and exit the program.

1. What do you do to test this case?
2. What does the test do?
3. What is the expected result?

#### Third Test Case

1. What do you do to test this case?
2. What does the test do?
3. What is the expected result?
