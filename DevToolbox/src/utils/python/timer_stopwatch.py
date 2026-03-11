import time 

class TimerStopwatch:

    def stopwatch(self):
        start_time = None
        elapsed_time = 0

        while True:
            command = input("Enter command (start, stop, reset, exit): ").strip().lower()

            if command == "start":
                if start_time is None:
                    start_time = time.time()
                    print("Stopwatch started.")
                else:
                    print("Stopwatch is already running.")
            elif command == "stop":
                if start_time is not None:
                    elapsed_time += time.time() - start_time
                    start_time = None
                    print(f"Stopwatch stopped. Elapsed time: {elapsed_time:.2f} seconds.")
                else:
                    print("Stopwatch is not running.")
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
    
    