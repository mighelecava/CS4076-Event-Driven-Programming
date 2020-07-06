#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<sstream>
#include<ctime>

using namespace std;

/** Converts strings from UPPERCASE or MiXedCasE to lowercase. */
string tolower(string &s)
{
    string ns;
    for (auto c : s) {
        ns += tolower(c);
    }
    return ns;
}

// EventListener.h
/** Parent class of all listeners. (It is abstract and can't be instantiated) */
class EventListener
{
public:
    // "void *" is a generic pointer to anything!
    // 10x worse than regular pointers in potential problems
    virtual void run(void *args) = 0;
};

// EventManager.h (Implemented as a Singleton)
/** This class manages the event loop and all the event calls */
struct EventManager // Structs in C++ are the same as classes, but default to "public" instead of "private".
{
    // static inside a class or struct works exactly like in java
    // Only one instance per class.
    static EventManager &getInstance(); // Gets an instance of the class (an object)

    // Making sure I can't have copies of this instance.
    EventManager(EventManager const& copy);            // Not Implemented (Copy constructor)
    EventManager& operator=(EventManager const& copy); // Not Implemented (Assignment operator)

    // Registers an event.
    void listen(string event_name, EventListener *listener);

    // Emits an event
    // "void *" is a generic pointer to anything.
    // !!! Highly unsafe, please don't do this at home without the presence of your parents !!!
    void trigger(string event_name, void *args = nullptr);

    // Returns true if still running
    bool is_running();

    // Stops the event loop
    void stop();

    // Reads the input and calls an input event
    void check_events();

    // constantly checks for new inputs until the program ends.
    void event_loop();

private:
    // True if running
    bool running;

    // map<K, V> is a collection of V's indexed by S.
    // In this case, we have lists/vectors of events indexed by their names.
    map<string, vector<EventListener*> > registeredEvents;

    // Only EventManager can call the constructor, so the only way to get an instance
    // is by calling getInstance.
    EventManager();
};

// InputListener
class Game;

// A listener that gets called when a new input is received.
struct InputListener : EventListener // Structs default to public even in inheritance.
{
    InputListener(Game *game);
    void run(void *args) override;

private:
    // We store a game pointer for easy access.
    Game *game;
    vector<string> args;
};

class Game;

// A listener for the Go command
class GoListener : public EventListener
{
public:
    GoListener(Game *game);
    void run(void *args) override;
private:
    Game  *game;
    string direction;
};

class Game;

// A listener for the Teleport command
class TeleportListener : public EventListener
{
public:
    TeleportListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

class Game;

// A listener for the good ending
class EnterRoomListener : public EventListener
{
public:
    EnterRoomListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

class Game;

// A listener for the bad ending
class CharacterDeathListener : public EventListener
{
public:
    CharacterDeathListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

class Game;

// A listener for the good ending
class RestartListener : public EventListener
{
public:
    RestartListener(Game *game);
    void run(void *args) override;
private:
   Game *game;
};

// VictoryListener.h
class Game;

// A listener for the good ending
class VictoryListener : public EventListener
{
public:
    VictoryListener(Game *game);
    void run(void *args) override;
private:
   Game *game;
};

// DefeatListener.h
class Game;

// A listener for the bad ending
class DefeatListener : public EventListener
{
public:
    DefeatListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

class Game;

// A listener for the exit command
class ExitListener : public EventListener
{
public:
    ExitListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

class Game;

// A listener for the exit command
class MapListener : public EventListener
{
public:
    MapListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

class Game;

class InfoListener : public EventListener
{
public:
    InfoListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

class PureVirtualClass
{
    public:
//8) Abstract classes and pure virtual functions */
        virtual void virtualExample() = 0;
};

//2) Inheritance */
class Items : public PureVirtualClass
{
    private:
        string description;
    public:
        void virtualExample();
        Items();
        Items(string description);
        string getDescription();
};

class Room
{
public:

//6) Friends */
    friend class Character;

    Room(string name);
    string getName();

    void setExits(Room *north, Room *east, Room *south, Room *west);
    Room *getExit(string direction);
    
    void removeItem(Items *item);
    void addItem(Items *item);
    
    vector<Items> getItems();

    string displayItems();

    bool isItemInRoom(string location);
    int amountOfItems();

    vector<Items> itemList;

private:
    string name;
    map<string, Room *> exits;
};

//7) Virtual functions and polymorphism */
class VirtualClass
{
    public:
        virtual void check()
        {
            cout << "Printing from the virtual class" << endl;
        }

        void change()
        {
            cout << "This is from the virtual class" << endl;
        }
};

// No need to include room since we're only working with pointers.
// This is how we tell the compiler "there will be a room eventually".
// This is called a "forward declaration".
class Room;
//2) Inheritance */
class Character : public VirtualClass 
{
public:
    Character(string n, int h, int s);
    Character(string name);
    Character();
    ~Character();

    void check();
    void change();

    vector<Items> itemsInventory;
    
    string getName();
    int    getHealth();
    double getStamina();
    Room  *getCurrentRoom();

    void addItem(Items item);
    void addItemEnemy(Items item);
    void removeItem(int location);
    bool isItemInCharacter(string str);

    Items* getItem(int location);
    vector<Items> getItems();
    
    void setName(string name);
    void setHealth(int setHealth);

//3) Template */
    template <typename T> void setStamina(T stamina)
    {
        if (stamina <= 0) 
        {
            this->stamina = 0;
            EventManager::getInstance().trigger("characterDeath", this);
        }  
        this->stamina = stamina;
    }

    void setCurrentRoom(Room *next);

 //5) Binary operator overloading */
    vector<Items> operator + (Character a)
    {
        Character temp("test"); 
        for(int i = 0; i < a.itemsInventory.size(); i++){
            temp.itemsInventory.push_back(a.itemsInventory[i]);
            cout<<"You killed the "<< a.getName() << ", and picked up it's Items -> " << a.itemsInventory[i].getDescription() << endl;
        }
        return temp.itemsInventory;
    }

 //4) Unary operator overloading */
    int operator ++ ()
    {
        health = health + 10;
        return health;
    }

private:
    string name;
    int health;
    double stamina;
    Room *currentRoom;
};

class Game
{
public:
    Game();
    void reset(bool show_update = true);

    void map();
    void info();
    void go(string direction);
    void teleport();

    void update_screen();
    void take(string item);
    void attack(string name);
    Character &getPlayer();
    void setOver(bool over);
    bool is_over();
    void setCurrentRoom(Room *next);

private:
    PureVirtualClass *pvc;
    VirtualClass *vc;
    vector <string> roomLetter;
    string displayItems();
    void makeItems();
    Character      testChar;
    Character      player;
    Character      enemy1;
    Character      enemy2;
    vector<Room *> rooms;
    bool           gameOver;
};

class Game;

// A listener for the good ending
class HurtListener : public EventListener
{
public:
    HurtListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

class Game;

// A listener for the good ending
class AttackListener: public EventListener
{
public:
    AttackListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

class Game;

class TakeListener : public EventListener
{
    public:
        TakeListener(Game *game);
        void run(void *args) override;
    private:
        Game *game;
};

//CPP FILES

EventManager::EventManager()
{
    running = true;
}

EventManager &EventManager::getInstance()
{
    // static inside functions creates an instance of this variable for all the calls of this function, 
    //and initializes only once.
    static EventManager instance;
    return instance;
}

void EventManager::listen(string event_name, EventListener *listener)
{
    registeredEvents[tolower(event_name)].push_back(listener);
}

void EventManager::trigger(string event_name, void *args)
{
    for (auto listener : registeredEvents[tolower(event_name)]) {
        listener->run(args);
    }
}

bool EventManager::is_running()
{
    return running;
}

void EventManager::stop()
{
    running = false;
}

void EventManager::check_events()
{
    string buffer;
    vector<string> words;

    cout << "> ";               // print prompt
    getline(cin, buffer, '\n');	// read a line from cin to "buffer"
    buffer = tolower(buffer);

    string::size_type pos = 0, last_pos = 0;

    // Break "buffer" up by spaces
    bool finished = false;
    while (!finished) {
        pos = buffer.find_first_of(' ', last_pos);	// find and remember first space.
        if (pos == string::npos ) {			// if we found the last word,
            words.push_back(buffer.substr(last_pos));	// add it to vector "words"
            finished = true;				// and finish searching.
        } else {					// otherwise add to vector and move on to next word.
            words.push_back(buffer.substr(last_pos, pos - last_pos));
            last_pos = pos + 1;
        }
    }

    trigger("input", &words);
}

void EventManager::event_loop()
{
    EventManager &eventManager = EventManager::getInstance();

    while (eventManager.is_running()) {
        eventManager.check_events();
    }
}

InputListener::InputListener(Game *game)
{
    this->game = game;
}

void InputListener::run(void *args_ptr)
{
    // Let's make this thing a bit safer by "translating" the pointer back to what we expect
    // This is exactly what makes this "void *" pointer dangerous.
    vector<string> *args = (vector<string> *) args_ptr;

    EventManager &eventManager = EventManager::getInstance();

    if (args->size() > 0) {
        // If arg[0] is "input", we are going to ignore the input.
        // If we do not ignore the input, it's an infinite loop.
        if (args->at(0) == "input") {
            return;
        }

        eventManager.trigger(args->at(0), args);

        if (eventManager.is_running()) {
            game->update_screen();
        }
    } else {
        eventManager.trigger("no_command", nullptr);
    }
}

TeleportListener::TeleportListener(Game *game)
{
    this->game = game;
}

void TeleportListener::run(void *)
{
    if (game->is_over()) {
        return;
    }

    this->game->teleport();
}

RestartListener::RestartListener(Game *game)
{
    this->game = game;
}

void RestartListener::run(void *)
{
    game->reset(false);
}

TakeListener::TakeListener(Game *game)
{
    this->game = game;
}

void TakeListener::run(void *args_ptr)
{
    if (game->is_over()) {
        return;
    }

    vector<string> *args = (vector<string> *) args_ptr;

    if (args->size() > 1) {
        game->take(args->at(1));
    } else {
        cout << "Need an Item name" << endl;
    }
}


EnterRoomListener::EnterRoomListener(Game *game)
{
    this->game = game;
}

void EnterRoomListener::run(void *args)
{
    if (game->is_over()) {
        return;
    }

    Room *room = (Room *) args;

    if (room->getName() == "J") {
        EventManager::getInstance().trigger("victory");
    }
}

CharacterDeathListener::CharacterDeathListener(Game *game)
{
    this->game = game;
}

void CharacterDeathListener::run(void *args)
{
    if (game->is_over()) {
        return;
    }

    Character *character = (Character *) args;

    if (character->getName() == game->getPlayer().getName()) {
        EventManager::getInstance().trigger("defeat");
    }
}

GoListener::GoListener(Game *game)
{
    this->game = game;
    direction  = "";
}

void GoListener::run(void *args_ptr)
{
    if (game->is_over()) {
        return;
    }

    vector<string> *args = (vector<string> *) args_ptr;

    if (args->size() > 1) {
        game->go(args->at(1));
    } else {
        cout << "Need a direction!" << endl;
    }
}

VictoryListener::VictoryListener(Game *game)
{
    this->game = game;
}

void VictoryListener::run(void *)
{
    cout << endl;
    cout << "Victory!" << endl;
    game->setOver(true);
}

// DefeatListener.cpp
DefeatListener::DefeatListener(Game *game)
{
    this->game = game;
}

void DefeatListener::run(void *)
{
    cout << endl;
    cout << "Defeat!" << endl;
    game->setOver(true);
}


MapListener::MapListener(Game *game)
{
    this->game = game;
}

void MapListener::run(void *)
{
    game->map();
}

InfoListener::InfoListener(Game *game)
{
    this->game = game;
}

void InfoListener::run(void *)
{
    game->info();
}

ExitListener::ExitListener(Game *game)
{
    this->game = game;
}

void ExitListener::run(void *)
{
    EventManager::getInstance().stop();
}

HurtListener::HurtListener(Game *game)
{
    this->game = game;
}

void HurtListener::run(void *args)
{
    if (game->is_over()) {
        return;
    }

    Character *player = (Character *) args;
    int health = player->getHealth();
    int newHealth = health - 10;
    player->setHealth(newHealth);
}

AttackListener::AttackListener(Game *game)
{
    this->game = game;
}

void AttackListener::run(void *args_ptr)
{
    if (game->is_over()) {
        return;
    }

    vector<string> *args = (vector<string> *) args_ptr;

    if (args->size() > 1) {
        game->attack(args->at(1));
    } else {
        cout << "Enter enemy name" << endl;
    }
}

Items::Items(){
    description = "";
}

Items:: Items(string description)
{
    this->description = description;   
}

string Items::getDescription()
{
    return description;
}

//8) Abstract classes and pure virtual functions */
void Items::virtualExample() {
        cout<< "Pure Virtual Function example from the Items class" << endl;
    }


//2) cascading constructors */
Character::Character(){
    name = "";
    health = 100;
    stamina = 100;
    currentRoom = nullptr;
}

Character::Character(string name)
{
// We need to use "this->" to differentiate between the "name" argument and the "name" from the class.
    this->name  = name;
    health      = 100;
    stamina     = 100;
    currentRoom = nullptr;
}

//9) Initializer list */
Character::Character(string n, int h, int s) : name(n), health(h), stamina(s){}


//1) Destructor */
Character::~Character(){
    cout << "Character has been destructed" << endl;
}

string Character::getName()
{
    return name;
}

int Character::getHealth()
{
    return health;
}

double Character::getStamina()
{
    return stamina;
}

Room *Character::getCurrentRoom()
{
    return currentRoom;
}

void Character::setName(string name)
{
    this->name = name;
}

void Character::setHealth(int health)
{
    if (health <= 0) {
        health = 0;
        EventManager::getInstance().trigger("characterDeath", this);
    }
    this->health = health;
}


void Character::setCurrentRoom(Room *next)
{
    currentRoom = next;
}

void Character::addItem(Items item)
{
    cout << "Added " << item.getDescription() << " to your inventory." << endl;
    itemsInventory.push_back(item);
}

void Character::addItemEnemy(Items item)
{
    itemsInventory.push_back(item);
}

bool Character::isItemInCharacter(string description)
{
    bool answer = false;
    for(int i = 0; i < itemsInventory.size(); i++){
        if(description.compare(itemsInventory[i].getDescription()) == 0)
        answer = true;
    }
    return answer;
}

Items* Character::getItem(int loaction){
    return &itemsInventory[loaction];
}

void Character::removeItem(int location){
    itemsInventory.erase(itemsInventory.begin()+location);
}

vector<Items> Character::getItems()
{
    return itemsInventory;
}

//7) Virtual functions and polymorphism */
void Character::check()
{
    cout << "Printing from the Character class" << endl;
}

//7) Virtual functions and polymorphism */
void Character::change()
{
    cout << "This is from the Character class" << endl;
}

Room::Room(string name) :
    name(name)
{
    exits["north"] = nullptr;
    exits["east"]  = nullptr;
    exits["south"] = nullptr;
    exits["west"]  = nullptr;
}

string Room::getName()
{
    return name;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
    exits["north"] = north;
    exits["east"]  = east;
    exits["south"] = south;
    exits["west"]  = west;
}

Room *Room::getExit(string direction)
{
    return exits[direction];
}

void Room::addItem(Items *item)
{
    itemList.push_back(*item);
}

string Room::displayItems()
{
    string message = "";
    int size = (itemList.size());
    if(size < 1){
        message = message + "There are no items in this room.";
    }else{
        message = "The items in this room are: ";
        int a = 0;
        for(int i = size; i > 0; i--){
            message = message + itemList[a].getDescription() + " ";
            a++;
        }
    }
    return message;
} 

int Room::amountOfItems()
{
    return itemList.size();
}

bool Room::isItemInRoom(string str) 
{
    int size = itemList.size();
    if(size > 0){
        for(int i = 0; i < size; i++){
            if(str.compare(itemList.at(i).getDescription()) == 0) {
                return true;
            }
        }
    }
    return false;
}

void Room::removeItem(Items *item)
{
    for(int i = 0; i < itemList.size(); i++){
        if(item->getDescription().compare(itemList.at(i).getDescription()) == 0){
            itemList.erase(itemList.begin() + i);
        }
    }
}

vector<Items> Room::getItems()
{
    return itemList;
}

Game::Game() :
    player("Hero"),
//9) Initializer list */
    enemy1("zombie", 20, 100),
    testChar("testChar"),
    enemy2("ghost")

{
    srand(time(nullptr));

    // Commands 
    EventManager::getInstance().listen("go",        new GoListener(this));
    EventManager::getInstance().listen("map",       new MapListener(this));
    EventManager::getInstance().listen("info",      new InfoListener(this));
    EventManager::getInstance().listen("restart",   new RestartListener(this));
    EventManager::getInstance().listen("teleport",  new TeleportListener(this));
    EventManager::getInstance().listen("take",      new TakeListener(this));
    EventManager::getInstance().listen("attack",    new AttackListener(this));
    EventManager::getInstance().listen("exit",      new ExitListener(this));

    // State changes
    EventManager::getInstance().listen("characterDeath", new CharacterDeathListener(this));
    EventManager::getInstance().listen("enterRoom",      new EnterRoomListener(this));
    EventManager::getInstance().listen("hurt",           new HurtListener(this));
    EventManager::getInstance().listen("victory",        new VictoryListener(this));
    EventManager::getInstance().listen("defeat",         new DefeatListener(this));

    rooms.push_back(new Room("A")); // 0
    rooms.push_back(new Room("B")); // 1
    rooms.push_back(new Room("C")); // 2
    rooms.push_back(new Room("D")); // 3
    rooms.push_back(new Room("E")); // 4
    rooms.push_back(new Room("F")); // 5
    rooms.push_back(new Room("G")); // 6
    rooms.push_back(new Room("H")); // 7
    rooms.push_back(new Room("I")); // 8
    rooms.push_back(new Room("J")); // 9

    //                 N         E         S         W
    rooms[0]->setExits(rooms[4], rooms[2], rooms[7], rooms[1]);
    rooms[1]->setExits(nullptr,  rooms[0], nullptr,  nullptr);
    rooms[2]->setExits(nullptr,  nullptr,  nullptr,  rooms[0]);
    rooms[3]->setExits(nullptr,  rooms[4], nullptr,  nullptr);
    rooms[4]->setExits(nullptr,  rooms[5], rooms[0], rooms[3]);
    rooms[5]->setExits(nullptr,  nullptr,  nullptr,  rooms[4]);
    rooms[6]->setExits(nullptr,  rooms[7], nullptr,  nullptr);
    rooms[7]->setExits(rooms[0], rooms[8], rooms[9], rooms[6]);
    rooms[8]->setExits(nullptr,  nullptr,  nullptr,  rooms[7]);
    rooms[9]->setExits(rooms[7], nullptr,  nullptr,  nullptr);

    reset();
}
 
void Game::reset(bool show_update)
{
    gameOver = false;

    rooms[0]->itemList.clear();
    rooms[2]->itemList.clear();

    rooms[0]->addItem(new Items("cursed_book"));
    rooms[2]->addItem(new Items("potion"));

    player.itemsInventory.clear();

    player.setCurrentRoom(rooms[0]);
    player.setHealth(100);
    player.setStamina<int>(100);

    enemy1.setCurrentRoom(rooms[7]);
    Items *key = new Items("key");
    enemy1.addItemEnemy(*key);
    enemy1.setHealth(100);
    enemy1.setStamina<int>(100);

    enemy2.setCurrentRoom(rooms[3]);
    enemy2.setHealth(100);
    enemy2.setStamina<int>(100);

    cout << "Welcome to Zork!" << endl;
    if (show_update) {
        update_screen();
    }
}

void Game::setOver(bool over)
{
    this->gameOver = over;
}

void Game::map()
{
    Room *playerRoom = player.getCurrentRoom();
    Room *enemy1Room = enemy1.getCurrentRoom();
    Room *enemy2Room = enemy2.getCurrentRoom();

    string A = "A";
    string B = "B";
    string C = "C";
    string D = "D";
    string E = "E";
    string F = "F";
    string G = "G";
    string H = "H";
    string I = "I";
    string J = "J";

    
    if(playerRoom == rooms[0]){
        A = "[A]";
    }else if(playerRoom == rooms[1]){
        B = "[B]";
    }else if(playerRoom == rooms[2]){
        C = "[C]";
    }else if(playerRoom == rooms[3]){
        D = "[D]";
    }else if(playerRoom == rooms[4]){
        E = "[E]";
    }else if(playerRoom == rooms[5]){
        F = "[F]";
    }else if(playerRoom == rooms[6]){
        G = "[G]";
    }else if(playerRoom == rooms[7]){
        H = "[H]";
    }else if(playerRoom == rooms[8]){
        I = "[I]";
    }else if (playerRoom == rooms[9]){
        J = "[J]";
    }
    
    if(enemy1Room == rooms[0]){
       A = "!A!";
   }else if(enemy1Room == rooms[1] && enemy1.getHealth() > 0){
       B = "!B!";
   }else if(enemy1Room == rooms[2] && enemy1.getHealth() > 0){
       C = "!C!";
   }else if(enemy1Room == rooms[3] && enemy1.getHealth() > 0){
       D = "!D!";
   }else if(enemy1Room == rooms[4] && enemy1.getHealth() > 0){
       E = "!E!";
   }else if(enemy1Room == rooms[5] && enemy1.getHealth() > 0){
       F = "!F!";
   }else if(enemy1Room == rooms[6] && enemy1.getHealth() > 0){
       G = "!G!";
   }else if(enemy1Room == rooms[7] && enemy1.getHealth() > 0){
       H = "!H!";
   }else if(enemy1Room == rooms[8] && enemy1.getHealth() > 0){
       I = "!I!";
   }else if (enemy1Room == rooms[9] && enemy1.getHealth() > 0){
       J = "!J!";
   }
 
      if(enemy2Room == rooms[0] && enemy2.getHealth() > 0){
       A = "!A!";
   }else if(enemy2Room == rooms[1] && enemy2.getHealth() > 0){
       B = "!B!";
   }else if(enemy2Room == rooms[2] && enemy2.getHealth() > 0){
       C = "!C!";
   }else if(enemy2Room == rooms[3] && enemy2.getHealth() > 0){
       D = "!D!";
   }else if(enemy2Room == rooms[4] && enemy2.getHealth() > 0){
       E = "!E!";
   }else if(enemy2Room == rooms[5] && enemy2.getHealth() > 0){
       F = "!F!";
   }else if(enemy2Room == rooms[6] && enemy2.getHealth() > 0){
       G = "!G!";
   }else if(enemy2Room == rooms[7] && enemy2.getHealth() > 0){
       H = "!H!";
   }else if(enemy2Room == rooms[8] && enemy2.getHealth() > 0){
       I = "!I!";
   }else if (enemy2Room == rooms[9] && enemy2.getHealth() > 0){
       J = "!J!";
   }

    cout << "\n" << endl;
    cout << D << " -- " << E << " -- " << F << endl;
    cout << "     |    " << endl;
    cout << B << " -- " << A << " -- " << C << endl;
    cout << "     |    " << endl;
    cout << G << " -- " << H << " -- " << I << endl;
    cout << "     |    " << endl;
    cout << "     " << J <<  endl;
}

void Game::info()
{
    cout << "Available commands:" << endl;
    cout << " - take <Item name>" << endl;
    cout << " - attack          " << endl;
    cout << " - go <direction>"   << endl;
    cout << " - teleport"         << endl;
    cout << " - map"              << endl;
    cout << " - info"             << endl;
}

void Game::take(string item)
{
    Room *currentRoom = player.getCurrentRoom();
    bool isItem = currentRoom->isItemInRoom(item);

    if(isItem == false){
        cout << "Item is not in this Room" << endl;
    }else if(isItem){
        Items *newItem = new Items(item);
        player.addItem(*newItem);
        currentRoom->removeItem(newItem);
        cout << "Item " << item << " has been picked up" << endl;
        if(newItem->getDescription() == "cursed_book"){
            cout<< "You have opened a cursed book, you lose 10 health." << endl;
            EventManager::getInstance().trigger("hurt", &player);
        }

        if(player.isItemInCharacter("potion")){
            int health = player.getHealth();
            if(health == 100){
                cout << "Health is Full" << endl;
            }else if(health > 90){
                cout << "Health is too high" << endl;
            }else{
//4) Unary operator overloading */
                ++player;
            }
        }
    }
}

void Game::attack(string name)
{
    Room *playerRoom = player.getCurrentRoom();
    Room *enemy2Room = enemy2.getCurrentRoom();
    Room *enemy1Room = enemy1.getCurrentRoom();

    if(playerRoom != enemy1Room && playerRoom != enemy2Room){
        cout << "\nNo enemy in the room to attack" << endl;
    }
    if(playerRoom == enemy1Room && name == enemy1.getName()){
            if(enemy1.getHealth() <= 0){
                cout << "\nNo enemy in the room to attack" << endl;
         }else{
              cout << "\n""Attacking " << enemy1.getName() <<endl;
              int health = enemy1.getHealth();
              int newHealth = health - 20;
//5) Binary operator overloading */
                if(newHealth == 0){
                    player.itemsInventory = player + enemy1;
                }
                enemy1.setHealth(newHealth);
            }
        }

    if(playerRoom == enemy2Room && name == enemy2.getName()){
        if(enemy2.getHealth() <= 0){
            cout << "\nNo enemy in the room to attack" << endl;
        }else{
            int health = enemy2.getHealth();
            cout << "Attacking " << enemy2.getName() <<endl;
            int newHealth = health - 10;
            enemy2.setHealth(newHealth);
        }
    }
}

void Game::go(string direction)
{
    Room *playerRoom = player.getCurrentRoom();
    Room *enemy1Room = enemy1.getCurrentRoom();
    Room *enemy2Room = enemy2.getCurrentRoom();
    Room *next = player.getCurrentRoom()->getExit(direction);

    if(playerRoom != enemy2Room){
        int random = rand() % 9 + 1;
        enemy2.setCurrentRoom(rooms[random]);
    }

    if (next != nullptr) {
        if(player.isItemInCharacter("key")) {
            player.setCurrentRoom(next);
            player.setStamina<double>(player.getStamina() - 1.5);
            EventManager::getInstance().trigger("enterRoom", next);
        }else if(next->getName() == "J") {
            cout << "Cannot enter room, it is locked." << endl;
        }else if(playerRoom == enemy1Room || playerRoom == enemy2Room){
            EventManager::getInstance().trigger("hurt", &player);
            cout << "You must kill the enemy before you can leave the room." << endl;
        }else {
            player.setCurrentRoom(next);
//3) Template */
            player.setStamina<double>(player.getStamina() - 1.5);
            EventManager::getInstance().trigger("enterRoom", next);
        }
    } else {
            cout << "You hit a wall" << endl;
    }
}

void Game::teleport()
{
    int selected = rand() % rooms.size();
    player.setCurrentRoom(rooms[selected]);
//3) Template */
    player.setStamina <int> (player.getStamina() - 50);
    EventManager::getInstance().trigger("enterRoom", rooms[selected]);
}

bool Game::is_over()
{
    return gameOver;
}

Character &Game::getPlayer()
{
    return player;
}

void Game::update_screen()
{
    if (!gameOver) {
        Room *enemy1Room = enemy1.getCurrentRoom();
        Room *enemy2Room = enemy2.getCurrentRoom();
        Room *currentRoom = player.getCurrentRoom();

        cout << endl;
        cout << "You are in " << currentRoom->getName() << endl;

        cout << "Exits:";
        if (currentRoom->getExit("north") != nullptr) { cout << " north"; }
        if (currentRoom->getExit("east")  != nullptr) { cout << " east";  }
        if (currentRoom->getExit("south") != nullptr) { cout << " south"; }
        if (currentRoom->getExit("west")  != nullptr) { cout << " west";  }
        cout << endl;

        
        if(enemy1Room == currentRoom && enemy1.getHealth() > 0){
//10) Static dispatch */
           cout << "You have met a " << enemy1.getName() << " in this Room." << endl;
           cout << "Player: " << player.getName() << " HP: " << player.getHealth() << " ST: " << player.getStamina() << endl;
           cout << "Enemy: " << enemy1.getName() << " HP: " << enemy1.getHealth() << " ST: " << enemy1.getStamina() << endl;
           cout << currentRoom->displayItems() << endl;
       }else if(enemy2Room == currentRoom && enemy2.getHealth() > 0){
           cout << "You have met a " << enemy2.getName() << " in this Room." << endl;
           cout << "Player: " << player.getName() << " HP: " << player.getHealth() << " ST: " << player.getStamina() << endl;
           cout << "Enemy: " << enemy2.getName() << " HP: " << enemy2.getHealth() << " ST: " << enemy2.getStamina() << endl;
           cout << currentRoom->displayItems() << endl;
       }else if( enemy1Room == enemy2Room && enemy1Room == currentRoom && enemy1.getHealth() > 0 && enemy2.getHealth() > 0){
           cout << "You have met a " << enemy1.getName() << " in this Room." << endl;
           cout << "You have met a " << enemy2.getName() << " in this Room." << endl;
           cout << "Player: " << player.getName() << " HP: " << player.getHealth() << " ST: " << player.getStamina() << endl;
           cout << "Enemy: " << enemy1.getName() << " HP: " << enemy1.getHealth() << " ST: " << enemy1.getStamina() << endl;
           cout << "Enemy: " << enemy2.getName() << " HP: " << enemy2.getHealth() << " ST: " << enemy2.getStamina() << endl;
           cout << currentRoom->displayItems() << endl;
       }else {
           cout << "HP: " << player.getHealth() << " ST: " << player.getStamina() << endl;
           cout << currentRoom->displayItems() << endl;
       }
   }else{
//10) Dynamic dispatch */
            Items *newItem = new Items("testItem");
            pvc = newItem;
            pvc->virtualExample();
            
            vc = &testChar;
            vc->check();
            vc->change();
            
            cout << "Type \"restart\" or \"exit\"." << endl;
   }
}

int main()
{
    Game game;
    EventManager::getInstance().listen("input", new InputListener(&game));
    EventManager::getInstance().event_loop();
    return EXIT_SUCCESS;
}
