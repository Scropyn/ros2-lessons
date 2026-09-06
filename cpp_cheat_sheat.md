# C++ + ROS2 Syntax Cheatsheet

### Embedded Systems — Period 1

---

## 1. Basic C++ Structure

```cpp
#include <iostream>
#include <string>
#include <memory>
#include <vector>

int main() {
    // code
    return 0;
}
```

### Comments

```cpp
// Single line

/*
   Multiple lines
*/
```

---

# 2. Variables & Data Types

```cpp
int age = 20;
float temperature = 21.5f;
double distance = 10.25;
bool active = true;
char letter = 'A';
std::string name = "Robot";
size_t count = 0;
```

### Constants

```cpp
const int MAX_SPEED = 100;
constexpr int BUFFER_SIZE = 256;
```

### Type inference

```cpp
auto speed = 10;
auto name = std::string("Robot");
```

---

# 3. Operators

### Arithmetic

```cpp
a + b
a - b
a * b
a / b
a % b
```

### Comparison

```cpp
a == b
a != b
a < b
a > b
a <= b
a >= b
```

### Logical

```cpp
&&      // AND
||      // OR
!       // NOT
```

### Assignment

```cpp
x = 10;
x += 5;
x -= 5;
x *= 2;
x /= 2;
x++;
x--;
```

---

# 4. If / Else

```cpp
if (temperature > 30) {
    // code
}
else if (temperature > 20) {
    // code
}
else {
    // code
}
```

### Ternary operator

```cpp
int max = (a > b) ? a : b;
```

---

# 5. Switch

```cpp
switch (state) {
    case 0:
        // code
        break;

    case 1:
        // code
        break;

    default:
        // code
        break;
}
```

---

# 6. Loops

### For

```cpp
for (int i = 0; i < 10; i++) {
    // code
}
```

### Range-based for

```cpp
for (const auto& value : values) {
    // code
}
```

### While

```cpp
while (condition) {
    // code
}
```

### Do-while

```cpp
do {
    // code
} while (condition);
```

### Loop control

```cpp
break;
continue;
```

---

# 7. Functions

### Declaration

```cpp
int add(int a, int b);
```

### Definition

```cpp
int add(int a, int b) {
    return a + b;
}
```

### Void

```cpp
void print_message() {
    // code
}
```

### Default argument

```cpp
void set_speed(int speed = 10);
```

---

# 8. References

### Reference

```cpp
int value = 10;

int& ref = value;

ref = 20;
```

### Function reference

```cpp
void modify(int& value) {
    value = 100;
}
```

### Const reference

```cpp
void print(const std::string& text) {
    // read only
}
```

**Common pattern:**

```cpp
const auto& value
```

---

# 9. Pointers

### Raw pointer

```cpp
int value = 10;

int* ptr = &value;

*ptr = 20;
```

### Address

```cpp
&value
```

### Dereference

```cpp
*ptr
```

### Null pointer

```cpp
int* ptr = nullptr;
```

---

# 10. Smart Pointers

### Unique pointer

```cpp
std::unique_ptr<int> ptr =
    std::make_unique<int>(10);
```

### Shared pointer

```cpp
std::shared_ptr<int> ptr =
    std::make_shared<int>(10);
```

### Access

```cpp
ptr->function();
ptr.get();
```

### Move ownership

```cpp
auto ptr2 = std::move(ptr);
```

After:

```cpp
ptr == nullptr;
```

---

# 11. Arrays

### C-style array

```cpp
int values[5] = {1, 2, 3, 4, 5};
```

### `std::array`

```cpp
std::array<int, 5> values = {
    1, 2, 3, 4, 5
};
```

### Access

```cpp
values[0];
values.at(0);
```

---

# 12. `std::vector`

```cpp
std::vector<int> values;
```

### Add

```cpp
values.push_back(10);
```

### Remove last

```cpp
values.pop_back();
```

### Size

```cpp
values.size();
```

### Empty?

```cpp
values.empty();
```

### Access

```cpp
values[0];
values.at(0);
```

### Loop

```cpp
for (const auto& value : values) {
    // code
}
```

---

# 13. Struct

```cpp
struct RobotState {
    double x;
    double y;
    double velocity;
};
```

### Create

```cpp
RobotState state;

state.x = 10.0;
state.y = 5.0;
```

### Initialization

```cpp
RobotState state{
    10.0,
    5.0,
    2.0
};
```

---

# 14. Classes

```cpp
class Robot {
public:
    Robot();

    void move();

private:
    double speed_;
};
```

### Constructor

```cpp
Robot::Robot()
    : speed_(0.0)
{
}
```

### Member function

```cpp
void Robot::move() {
    speed_ = 10.0;
}
```

### Object

```cpp
Robot robot;

robot.move();
```

---

# 15. Class Inheritance

```cpp
class MyNode : public rclcpp::Node {
public:
    MyNode()
        : Node("my_node")
    {
    }

private:
    // members
};
```

---

# 16. Constructors & Initializer Lists

```cpp
class Robot {
public:
    Robot(int speed, bool active)
        : speed_(speed),
          active_(active)
    {
    }

private:
    int speed_;
    bool active_;
};
```

**Prefer:**

```cpp
Robot(int x)
    : x_(x)
{
}
```

over assigning inside the constructor.

---

# 17. `const`

### Const variable

```cpp
const int value = 10;
```

### Const function

```cpp
int get_speed() const {
    return speed_;
}
```

### Const reference

```cpp
void process(const Message& msg);
```

### Const pointer

```cpp
const int* ptr;
```

---

# 18. `static`

```cpp
static int counter = 0;
```

### Static class member

```cpp
class Robot {
public:
    static int count;
};
```

---

# 19. `enum`

```cpp
enum class State {
    IDLE,
    RUNNING,
    ERROR
};
```

### Usage

```cpp
State state = State::IDLE;

if (state == State::ERROR) {
    // ...
}
```

---

# 20. Lambda Functions

### Basic

```cpp
auto function = []() {
    // code
};
```

### Parameter

```cpp
auto add = [](int a, int b) {
    return a + b;
};
```

### Capture `this`

```cpp
auto callback = [this]() {
    this->do_something();
};
```

### Capture variable

```cpp
int x = 10;

auto function = [x]() {
    // x available
};
```

### Capture by reference

```cpp
auto function = [&x]() {
    x++;
};
```

---

# 21. Templates

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}
```

### ROS2 example

```cpp
create_publisher<std_msgs::msg::String>(
    "topic",
    10
);
```

---

# 22. Namespaces

```cpp
std::string
std::vector<int>
std::unique_ptr<int>
```

### Using

```cpp
using namespace std::chrono_literals;
```

Then:

```cpp
500ms
1s
100us
```

---

# 23. `std::move`

```cpp
auto msg = std::make_unique<Message>();

publisher_->publish(std::move(msg));
```

Used to **transfer ownership** instead of copying.

---

# 24. `std::string`

```cpp
std::string name = "Robot";
```

### Concatenate

```cpp
std::string result =
    "Speed: " + std::to_string(speed);
```

### Length

```cpp
name.size();
```

### C-style string

```cpp
name.c_str();
```

---

# 25. `std::pair`

```cpp
std::pair<int, double> data{
    10,
    2.5
};
```

Access:

```cpp
data.first;
data.second;
```

---

# 26. `auto`

```cpp
auto x = 10;
auto name = std::string("Robot");

auto& ref = value;
const auto& ref = value;
```

Common ROS2 pattern:

```cpp
auto message = std_msgs::msg::String();
```

---

# 27. `nullptr`

```cpp
std::unique_ptr<int> ptr = nullptr;

if (ptr == nullptr) {
    // no object
}
```

---

# 28. Exceptions

```cpp
try {
    // risky code
}
catch (const std::exception& e) {
    std::cout << e.what();
}
```

Throw:

```cpp
throw std::runtime_error("Error");
```

---

# 29. ROS2 Node Structure

```cpp
#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node {
public:

    MyNode()
        : Node("my_node")
    {
        // publishers
        // subscribers
        // timers
    }

private:

    // ROS2 objects
};
```

---

# 30. ROS2 Publisher

```cpp
rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
```

Create:

```cpp
publisher_ =
    this->create_publisher<std_msgs::msg::String>(
        "topic",
        10
    );
```

Publish:

```cpp
auto message = std_msgs::msg::String();

message.data = "Hello";

publisher_->publish(message);
```

---

# 31. ROS2 Subscriber

```cpp
rclcpp::Subscription<std_msgs::msg::String>::SharedPtr
    subscription_;
```

Create:

```cpp
subscription_ =
    this->create_subscription<std_msgs::msg::String>(
        "topic",
        10,
        [this](const std_msgs::msg::String::SharedPtr msg) {
            this->callback(msg);
        }
    );
```

Callback:

```cpp
void callback(
    const std_msgs::msg::String::SharedPtr msg)
{
    RCLCPP_INFO(
        this->get_logger(),
        "%s",
        msg->data.c_str()
    );
}
```

---

# 32. ROS2 Timer

```cpp
rclcpp::TimerBase::SharedPtr timer_;
```

Create:

```cpp
timer_ = this->create_wall_timer(
    500ms,
    [this]() {
        this->timer_callback();
    }
);
```

---

# 33. ROS2 Logging

```cpp
RCLCPP_INFO(
    this->get_logger(),
    "Value: %d",
    value
);
```

```cpp
RCLCPP_WARN(
    this->get_logger(),
    "Warning!"
);
```

```cpp
RCLCPP_ERROR(
    this->get_logger(),
    "Error!"
);
```

---

# 34. ROS2 Main

```cpp
int main(int argc, char* argv[]) {

    rclcpp::init(argc, argv);

    rclcpp::spin(
        std::make_shared<MyNode>()
    );

    rclcpp::shutdown();

    return 0;
}
```

---

# 35. ROS2 Message Pointer Aliases

```cpp
std_msgs::msg::String::SharedPtr

std_msgs::msg::String::ConstSharedPtr

std_msgs::msg::String::UniquePtr
```

Common callback:

```cpp
void callback(
    const std_msgs::msg::String::SharedPtr msg)
{
}
```

---

# 36. Chrono

```cpp
#include <chrono>

using namespace std::chrono_literals;
```

```cpp
100us
1ms
10ms
100ms
1s
5s
```

Example:

```cpp
timer_ = this->create_wall_timer(
    100ms,
    callback
);
```

---

# 37. Common ROS2 Message Types

```cpp
std_msgs::msg::String
std_msgs::msg::Bool
std_msgs::msg::Int32
std_msgs::msg::Float64

geometry_msgs::msg::Twist

sensor_msgs::msg::LaserScan
sensor_msgs::msg::Image
sensor_msgs::msg::Imu

nav_msgs::msg::Odometry
```

---

# 38. Common Access Syntax

### Object

```cpp
object.member;
```

### Pointer

```cpp
pointer->member;
```

### Reference

```cpp
reference.member;
```

### ROS2 message

```cpp
msg->data;
msg->ranges;
msg->linear.x;
msg->angular.z;
```

---

# 39. `&&` vs `&`

### Reference

```cpp
void function(const Message& msg);
```

### Rvalue reference

```cpp
void function(Message&& msg);
```

### Move

```cpp
function(std::move(message));
```

---

# 40. Most Important Syntax to Memorize

```cpp
// Variable
int x = 10;

// Function
int add(int a, int b) {
    return a + b;
}

// Reference
const auto& x = value;

// Pointer
auto* ptr = &value;

// Smart pointer
auto ptr = std::make_shared<MyClass>();

// Class
class MyClass {
public:
    MyClass();

private:
    int value_;
};

// Lambda
auto callback = [this]() {
    // code
};

// If
if (condition) {
}

// For
for (int i = 0; i < 10; i++) {
}

// Vector
std::vector<int> values;

// Struct
struct Data {
    int value;
};

// Enum
enum class State {
    IDLE,
    RUNNING
};

// Move
std::move(object);

// ROS2 node
class MyNode : public rclcpp::Node {
public:
    MyNode() : Node("my_node") {}
};

// ROS2 timer
timer_ = this->create_wall_timer(
    100ms,
    [this]() {}
);

// ROS2 publisher
publisher_->publish(message);

// ROS2 logging
RCLCPP_INFO(
    this->get_logger(),
    "Value: %d",
    value
);
```

---

# ⚡ Exam Mini-Cheat Sheet

```text
.       → object member
->      → pointer member
&       → address / reference
*       → pointer / dereference
::      → namespace / class scope
< >     → template
()      → function call
{}      → block / initialization
[]      → array / lambda capture
=       → assignment
==      → comparison
&&      → AND
||      → OR
!       → NOT

const   → cannot modify
auto    → compiler deduces type
static  → shared/static lifetime
nullptr → empty pointer
std::move() → transfer ownership

public:     → accessible from outside
private:    → only accessible inside class
protected:  → class + derived classes

SharedPtr   → shared ownership
UniquePtr   → exclusive ownership
```

## ROS2 Must-Know

```cpp
rclcpp::Node
rclcpp::Publisher
rclcpp::Subscription
rclcpp::TimerBase

create_publisher<T>()
create_subscription<T>()
create_wall_timer()

publisher_->publish(msg);

RCLCPP_INFO(...)
RCLCPP_WARN(...)
RCLCPP_ERROR(...)

rclcpp::init(...)
rclcpp::spin(...)
rclcpp::shutdown(...)
```
