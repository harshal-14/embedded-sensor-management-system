// Approach: unordered_map<string, vector<string>> messages;  // Store field types
// unordered_map<string, int> type_sizes;           // Primitive sizes
// unordered_map<string, int> cache;                // Memoization

// parse function:
// Read line by line
// If line starts with "Message" -> new message
// Otherwise -> add field type to current message

// get_size function:
// 1. Check if primitive -> return size
// 2. Check cache -> return cached size
// 3. Check if type exists -> throw error if not
// 4. Check for cycles -> throw error if found
// 5. Recursively sum field sizes
// 6. Cache and return

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>

using namespace std;

class MessageParser {
private:
    // message_name -> list of field types
    unordered_map<string, vector<string>> messages;
    
    // type -> size in bytes
    unordered_map<string, int> type_sizes = {
        {"float", 4},
        {"int", 4},
        {"string", 256}
    };
    
    // Cache for calculated sizes
    unordered_map<string, int> cache;
    
public:
    void parse(const string& input) {
        istringstream stream(input); // Use istringstream to read from the input string, what is istringstream? its a stream class to operate on strings, what is stream from istringstream? stream is an object of istringstream class
        string line, current_msg;
        
        while (getline(stream, line)) {
            istringstream iss(line); // what is iss? iss is an object of istringstream class to read from line string
            string first, second;
            iss >> first >> second; // Read first two words from line, what is this line meaning? it means read first word into first variable and second word into second variable
            
            // Skip empty lines and comments
            if (first.empty() || first == "//") continue;
            
            if (first == "Message") {
                current_msg = second; // what are we doing here? we are setting current_msg to the name of the message
                messages[current_msg] = {}; 
            }
            else if (!current_msg.empty()) {
                messages[current_msg].push_back(first);  // first is the type
            }
        }
        cache.clear(); 
    }
    
    int get_size(const string& type) {
        return get_size_helper(type, unordered_set<string>());
    }
    
private:
    int get_size_helper(const string& type, unordered_set<string> visiting) {
        // Check primitives

        if (type_sizes.count(type)) {
            return type_sizes[type];//this will return the size of primitive, eg, float -> 4
        }
        
        // Check cache
        if (cache.count(type)) {
            return cache[type]; //return cached size, what does that mean? it means if we have already calculated size of this type, return it directly
        }
        
        // Check if type exists
        if (!messages.count(type)) {
            throw runtime_error("Unknown type: " + type); //throw error if type not found
        }
        
        // Check for circular dependency
        if (visiting.count(type)) {
            throw runtime_error("Circular dependency: " + type); //throw error if circular dependency found, what does circular dependency mean? it means a message contains itself directly or indirectly
        }
        
        visiting.insert(type);
        
        // Calculate size
        int total = 0;
        for (const string& field_type : messages[type]) {
            total += get_size_helper(field_type, visiting);
        }
        
        cache[type] = total;
        return total;
    }
};

int main() {
    MessageParser parser;
    
    // Part 1
    string input1 = R"(
Message Vehicle
float x_position
float y_position
float velocity
float acceleration
int num_wheels
string name

Message Vector2d
float x_position
float y_position
)";
    
    parser.parse(input1);
    cout << "Part 1:\n";
    cout << "Vehicle: " << parser.get_size("Vehicle") << "\n";      // 276
    cout << "Vector2d: " << parser.get_size("Vector2d") << "\n";    // 8
    cout << "float: " << parser.get_size("float") << "\n\n";        // 4
    
    // Part 2
    string input2 = R"(
Message Vehicle
Pose pose
float velocity
float acceleration
int num_wheels
string name

Message Pose
Vector2d Position
float yaw

Message Vector2d
float px
float py
)";
    
    parser.parse(input2);
    cout << "Part 2:\n";
    cout << "Vector2d: " << parser.get_size("Vector2d") << "\n";   // 8
    cout << "Pose: " << parser.get_size("Pose") << "\n";           // 12
    cout << "Vehicle: " << parser.get_size("Vehicle") << "\n";     // 280
    
    return 0;
}