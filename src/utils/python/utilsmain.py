from .todo_list import todolist
from .timer_stopwatch import TimerStopwatch
from .password_generator import password_generator

def main():
    # This keeps showing the utilities menu until the user exits.
    while True:
        print("\nUtilities Menu:")
        print("1. To-do list")
        print("2. TimerStopwatch")
        print("3. Password generator")
        print("0. Exit")

        # This asks which utility the user wants to run.
        choice = input("Choose an option: ")
        # This starts the utility that matches the user's choice.
        if choice == "1":
            todolist()
        elif choice == "2":
            stopwatch = TimerStopwatch()
            stopwatch.stopwatch()
        elif choice == "3":
            password_generator()
        elif choice == "0":
            break
        else:
            print("Invalid choice. Try again.")


if __name__ == "__main__":
    main()