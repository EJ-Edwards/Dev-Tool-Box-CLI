import time 


# This class is the start for the simple stopwatch
class TimerStopwatch:

    # This function is for the stopwatch, it will start and stop the timer
    def stopwatch(self):
        start_time = None
        elapsed_time = 0

        # A while true loop was used to keep the stop watch going until the user decides to stop the program
        while True:
            command = input("Enter command (start, stop, reset, exit): ").strip().lower()

            # the if statement is used to see if the user wants to start
            if command == "start":
                if start_time is None:
                    start_time = time.time()
                    print("Stopwatch started.")
                # The else statment is used to see if the user already started the stopwatch and if they have it will print out that the stopwatch is already running
                else:
                    print("Stopwatch is already running.")
           # The elif statmenet is used to see if the user wanted to stop the stopwatch and if they did it will print out the elapsed time
            elif command == "stop":
                if start_time is not None:
                    # This line of code is used to calculate the time that has elapsed since it was started and it will print out the elapsed time
                    elapsed_time += time.time() - start_time
                    start_time = None
                    print(f"Stopwatch stopped. Elapsed time: {elapsed_time:.2f} seconds.")
                else:
                    print("Stopwatch is not running.")
            # This statment is used to reset the stop watch and it will reset it to 0 and print out that the stopwatch has been reset
            elif command == "reset":
                start_time = None
                elapsed_time = 0
                print("Stopwatch reset.")
            elif command == "exit":
                print("Exiting stopwatch.")
                break
            else:
                print("Invalid command. Please try again.")
    print("Simple Stopwatch")
    print("Commands: 'start', 'stop', 'reset', 'exit'")
    
    