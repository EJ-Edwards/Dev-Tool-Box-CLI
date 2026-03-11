import random
import textwrap


# ---------------------------------------------------------------------------
# Data: rooms, items, enemies
# ---------------------------------------------------------------------------

ROOMS = {
    "entrance": {
        "name": "Dungeon Entrance",
        "description": (
            "You stand at the mouth of a dark dungeon carved into the "
            "mountainside. Cold air drifts from within. Torchlight flickers "
            "against damp stone walls."
        ),
        "exits": {"north": "hallway"},
        "items": ["torch"],
        "enemy": None,
    },
    "hallway": {
        "name": "Dim Hallway",
        "description": (
            "A long corridor stretches before you. The walls are lined with "
            "faded tapestries and the floor is slick with moisture. You hear "
            "faint growling to the east."
        ),
        "exits": {"south": "entrance", "north": "armory", "east": "goblin_den", "west": "library"},
        "items": [],
        "enemy": None,
    },
    "armory": {
        "name": "Old Armory",
        "description": (
            "Rusted weapons hang on the walls. Most are useless, but a sturdy "
            "sword gleams in the corner — someone maintained it."
        ),
        "exits": {"south": "hallway"},
        "items": ["sword"],
        "enemy": None,
    },
    "goblin_den": {
        "name": "Goblin Den",
        "description": (
            "The stench hits you first. Bones and scraps litter the ground. "
            "A goblin snarls at you from across the room, clutching a rusty dagger."
        ),
        "exits": {"west": "hallway", "east": "treasure_room"},
        "items": [],
        "enemy": {"name": "Goblin", "hp": 20, "attack": 5},
    },
    "library": {
        "name": "Dusty Library",
        "description": (
            "Shelves of crumbling books line every wall. A faint magical glow "
            "emanates from a potion sitting on the reading desk."
        ),
        "exits": {"east": "hallway", "north": "puzzle_room"},
        "items": ["health_potion"],
        "enemy": None,
    },
    "puzzle_room": {
        "name": "Puzzle Chamber",
        "description": (
            "The door slams shut behind you. An inscription on the wall reads:\n"
            '  "I speak without a mouth and hear without ears.\n'
            '   I have no body, but I come alive with the wind.\n'
            '   What am I?"'
        ),
        "exits": {},  # locked until puzzle solved
        "items": ["magic_shield"],
        "enemy": None,
        "puzzle": {
            "answer": "echo",
            "solved": False,
            "success_msg": "The wall rumbles open, revealing a passage south and a gleaming shield!",
            "fail_msg": "Nothing happens. The walls feel like they're closing in...",
            "unlock_exits": {"south": "library", "east": "dragon_lair"},
        },
    },
    "treasure_room": {
        "name": "Treasure Vault",
        "description": (
            "Gold coins and jewels are piled high. A locked chest sits in the "
            "center — it needs a key."
        ),
        "exits": {"west": "goblin_den"},
        "items": ["gold_key"],
        "enemy": {"name": "Skeleton Guard", "hp": 30, "attack": 8},
    },
    "dragon_lair": {
        "name": "Dragon's Lair",
        "description": (
            "Heat blasts your face as you enter an enormous cavern. A dragon "
            "sits coiled around a mountain of treasure, one eye fixed on you."
        ),
        "exits": {"west": "puzzle_room", "north": "exit"},
        "items": [],
        "enemy": {"name": "Dragon", "hp": 50, "attack": 15},
    },
    "exit": {
        "name": "Sunlit Exit",
        "description": (
            "Daylight streams through a wide opening. You've made it through "
            "the dungeon alive! Birds sing outside and fresh air fills your lungs."
        ),
        "exits": {},
        "items": [],
        "enemy": None,
        "victory": True,
    },
}

ITEM_DESCRIPTIONS = {
    "torch": "A burning torch. Lights your way.",
    "sword": "A sharp steel sword. +10 attack damage.",
    "health_potion": "A glowing red potion. Restores 30 HP.",
    "magic_shield": "An enchanted shield. Halves incoming damage.",
    "gold_key": "A small golden key. Might open something...",
}


# ---------------------------------------------------------------------------
# Player state
# ---------------------------------------------------------------------------

def new_player():
    return {
        "hp": 100,
        "max_hp": 100,
        "attack": 5,
        "inventory": [],
        "location": "entrance",
        "has_shield": False,
    }


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def wrap(text):
    print(textwrap.fill(text, width=70))


def show_status(player):
    room = ROOMS[player["location"]]
    print(f"\n{'=' * 50}")
    print(f"  {room['name']}     HP: {player['hp']}/{player['max_hp']}")
    print(f"{'=' * 50}")
    wrap(room["description"])

    if room["items"]:
        print(f"\n  Items here: {', '.join(room['items'])}")

    exits = room.get("exits", {})
    if exits:
        print(f"  Exits: {', '.join(exits.keys())}")

    if room.get("enemy"):
        e = room["enemy"]
        print(f"\n  !! A {e['name']} blocks your path! (HP: {e['hp']}) !!")


def show_help():
    print("""
  Commands:
    go <direction>   - Move (north, south, east, west)
    look             - Look around the room again
    take <item>      - Pick up an item
    use <item>       - Use an item (e.g. health_potion)
    inventory / inv  - Show your inventory
    attack           - Attack an enemy in the room
    answer <text>    - Answer a puzzle
    status           - Show HP and stats
    help             - Show this help
    quit             - Quit the game
""")


# ---------------------------------------------------------------------------
# Actions
# ---------------------------------------------------------------------------

def do_go(player, direction):
    room = ROOMS[player["location"]]
    exits = room.get("exits", {})

    if room.get("enemy"):
        print("  You can't leave — there's an enemy blocking the way! Fight or flee isn't an option.")
        return

    if direction not in exits:
        print(f"  You can't go {direction}.")
        return

    player["location"] = exits[direction]
    show_status(player)


def do_take(player, item_name):
    room = ROOMS[player["location"]]
    if item_name in room["items"]:
        room["items"].remove(item_name)
        player["inventory"].append(item_name)
        desc = ITEM_DESCRIPTIONS.get(item_name, "")
        print(f"  Picked up: {item_name}. {desc}")

        if item_name == "sword":
            player["attack"] += 10
            print("  Your attack power increased!")
        elif item_name == "magic_shield":
            player["has_shield"] = True
            print("  You equip the shield — incoming damage halved!")
    else:
        print(f"  There's no '{item_name}' here.")


def do_use(player, item_name):
    if item_name not in player["inventory"]:
        print(f"  You don't have '{item_name}'.")
        return

    if item_name == "health_potion":
        heal = min(30, player["max_hp"] - player["hp"])
        player["hp"] += heal
        player["inventory"].remove(item_name)
        print(f"  You drink the potion and recover {heal} HP. (HP: {player['hp']}/{player['max_hp']})")
    else:
        print(f"  You can't use '{item_name}' right now.")


def do_attack(player):
    room = ROOMS[player["location"]]
    enemy = room.get("enemy")
    if not enemy:
        print("  There's nothing to attack here.")
        return

    # Player attacks
    damage = player["attack"] + random.randint(0, 5)
    enemy["hp"] -= damage
    print(f"  You strike the {enemy['name']} for {damage} damage!")

    if enemy["hp"] <= 0:
        print(f"  The {enemy['name']} is defeated!")
        room["enemy"] = None
        return

    # Enemy attacks back
    incoming = enemy["attack"] + random.randint(0, 3)
    if player["has_shield"]:
        incoming //= 2
        print(f"  Your shield absorbs some of the blow!")
    player["hp"] -= incoming
    print(f"  The {enemy['name']} hits you for {incoming} damage! (HP: {player['hp']}/{player['max_hp']})")


def do_answer(player, text):
    room = ROOMS[player["location"]]
    puzzle = room.get("puzzle")
    if not puzzle:
        print("  There's no puzzle here.")
        return
    if puzzle["solved"]:
        print("  You already solved this puzzle.")
        return

    if text.strip().lower() == puzzle["answer"]:
        puzzle["solved"] = True
        room["exits"].update(puzzle["unlock_exits"])
        print(f"  {puzzle['success_msg']}")
    else:
        # Wrong answer costs a bit of HP
        player["hp"] -= 5
        print(f"  {puzzle['fail_msg']} (-5 HP, now {player['hp']}/{player['max_hp']})")


def do_inventory(player):
    if not player["inventory"]:
        print("  Your inventory is empty.")
    else:
        print("  Inventory:")
        for item in player["inventory"]:
            desc = ITEM_DESCRIPTIONS.get(item, "")
            print(f"    - {item}: {desc}")


# ---------------------------------------------------------------------------
# Reset rooms for a new game (enemies & items respawn)
# ---------------------------------------------------------------------------

_ORIGINAL_ROOMS = None

def _snapshot_rooms():
    """Deep-copy room state so we can reset between games."""
    import copy
    global _ORIGINAL_ROOMS
    _ORIGINAL_ROOMS = copy.deepcopy(ROOMS)

def _reset_rooms():
    import copy
    for key in ROOMS:
        ROOMS[key] = copy.deepcopy(_ORIGINAL_ROOMS[key])


# ---------------------------------------------------------------------------
# Main game loop
# ---------------------------------------------------------------------------

def text_adventure():
    _snapshot_rooms()

    print("\n" + "=" * 50)
    print("   DUNGEON CRAWLER — A Text Adventure")
    print("=" * 50)
    wrap(
        "You are an adventurer who has heard tales of a dungeon filled with "
        "treasure and danger. Armed with nothing but your wits, you step "
        "inside..."
    )
    print("\n  Type 'help' for a list of commands.\n")

    player = new_player()
    show_status(player)

    while True:
        raw = input("\n  > ").strip().lower()
        if not raw:
            continue

        parts = raw.split(maxsplit=1)
        cmd = parts[0]
        arg = parts[1] if len(parts) > 1 else ""

        if cmd == "quit":
            print("  Thanks for playing!")
            break
        elif cmd == "help":
            show_help()
        elif cmd == "look":
            show_status(player)
        elif cmd == "go":
            if not arg:
                print("  Go where? (north, south, east, west)")
            else:
                do_go(player, arg)
        elif cmd in ("north", "south", "east", "west"):
            do_go(player, cmd)
        elif cmd == "take":
            if not arg:
                print("  Take what?")
            else:
                do_take(player, arg)
        elif cmd == "use":
            if not arg:
                print("  Use what?")
            else:
                do_use(player, arg)
        elif cmd == "attack":
            do_attack(player)
        elif cmd == "answer":
            if not arg:
                print("  Answer what? Usage: answer <your guess>")
            else:
                do_answer(player, arg)
        elif cmd in ("inventory", "inv", "i"):
            do_inventory(player)
        elif cmd == "status":
            print(f"  HP: {player['hp']}/{player['max_hp']}  ATK: {player['attack']}  Shield: {'Yes' if player['has_shield'] else 'No'}")
        else:
            print("  Unknown command. Type 'help' for options.")

        # Check death
        if player["hp"] <= 0:
            print("\n  You have fallen... Game Over.")
            print("  Type 'retry' to try again or anything else to quit.")
            if input("  > ").strip().lower() == "retry":
                _reset_rooms()
                player = new_player()
                print("\n  Starting over...\n")
                show_status(player)
                continue
            else:
                break

        # Check victory
        room = ROOMS[player["location"]]
        if room.get("victory"):
            print("\n  *** CONGRATULATIONS! You conquered the dungeon! ***\n")
            break
