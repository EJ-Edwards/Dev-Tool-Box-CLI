import os
import json
import sys



def write_note_to_file(note, filename):
    try:
        with open(filename, 'w') as f:
            json.dump(note, f)
        print(f"Note saved to {filename}")
    except Exception as e:
        print(f"Error writing note to file: {e}")
        