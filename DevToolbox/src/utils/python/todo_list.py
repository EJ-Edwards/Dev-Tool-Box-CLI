import json
import os

SAVE_FILE = os.path.join(os.path.dirname(__file__), "todo_data.json")


def _load_tasks():
    if os.path.exists(SAVE_FILE):
        with open(SAVE_FILE, "r") as f:
            return json.load(f)
    return []


def _save_tasks(tasks):
    with open(SAVE_FILE, "w") as f:
        json.dump(tasks, f, indent=2)


def _get_task_num(prompt, tasks):
    try:
        num = int(input(prompt))
    except ValueError:
        print("Please enter a valid number.")
        return None
    if 1 <= num <= len(tasks):
        return num
    print("Invalid task number.")
    return None


def todolist():
    tasks = _load_tasks()

    while True:
        print("\nDevToolbox - To-Do List")
        print("1. Add Task")
        print("2. View Tasks")
        print("3. Toggle Complete")
        print("4. Edit Task")
        print("5. Delete Task")
        print("6. Exit")
        choice = input("Enter your choice: ")

        if choice == "1":
            task_name = input("Enter the task: ").strip()
            if task_name:
                tasks.append({"name": task_name, "done": False})
                _save_tasks(tasks)
                print(f"Task added: {task_name}")
            else:
                print("Task cannot be empty.")

        elif choice == "2":
            if not tasks:
                print("\nNo tasks yet. Add one!")
            else:
                print("\nTasks:")
                for i, t in enumerate(tasks, 1):
                    status = "[x]" if t["done"] else "[ ]"
                    print(f"  {i}. {status} {t['name']}")
                done = sum(1 for t in tasks if t["done"])
                print(f"\n  {done}/{len(tasks)} completed")

        elif choice == "3":
            if not tasks:
                print("No tasks to toggle.")
                continue
            num = _get_task_num("Enter the task number to toggle: ", tasks)
            if num is not None:
                tasks[num - 1]["done"] = not tasks[num - 1]["done"]
                state = "complete" if tasks[num - 1]["done"] else "incomplete"
                print(f"Marked '{tasks[num - 1]['name']}' as {state}.")
                _save_tasks(tasks)

        elif choice == "4":
            if not tasks:
                print("No tasks to edit.")
                continue
            num = _get_task_num("Enter the task number to edit: ", tasks)
            if num is not None:
                new_name = input("Enter the new task name: ").strip()
                if new_name:
                    tasks[num - 1]["name"] = new_name
                    _save_tasks(tasks)
                    print("Task updated.")
                else:
                    print("Task name cannot be empty.")

        elif choice == "5":
            if not tasks:
                print("No tasks to delete.")
                continue
            num = _get_task_num("Enter the task number to delete: ", tasks)
            if num is not None:
                removed = tasks.pop(num - 1)
                _save_tasks(tasks)
                print(f"Deleted: {removed['name']}")

        elif choice == "6":
            break

        else:
            print("Invalid choice. Please try again.")
