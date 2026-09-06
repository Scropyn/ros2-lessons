# C++ Core Fundamentals for ROS2: The Minor Embedded Systems Cheatsheet (Period 1)

This cheatsheet serves as a foundational guide for developing robust, industry-standard ROS2 nodes using Modern C++. By mastering these core concepts, you move beyond simple scripting and into the realm of professional robotic software engineering.

---

## 1. The ROS2 Paradigm: Object-Oriented Node Design

In professional ROS2 development, the industry-standard approach is the **Class-Based Node Architecture**. Rather than writing procedural code with global variables—which leads to "global state pollution" and makes debugging a nightmare—you define your robot's logic within a class that inherits from `rclcpp::Node`.

### Basic Node Skeleton

```cpp
#include "rclcpp/rclcpp.hpp"

// Class inheritance avoids global state pollution and ensures modularity
class MyRobotNode : public rclcpp::Node {
public:
  // The constructor names the node and initializes internal state
  MyRobotNode() : Node("my_robot_node") {
    // Initialize publishers, subscribers, and timers here
  }

private:
  // State Encapsulation: Protects the robot's state from external corruption.
  // By keeping communication primitives private, you ensure only the node's
  // internal logic can modify its data.
};
```

### Key Insight: The "So What?" of Encapsulation

In embedded systems, maintaining architectural integrity is vital. By declaring your data buffers and communication objects as `private` members, you prevent external functions from accidentally corrupting the robot's state.

This encapsulation ensures your software is:

* Modular
* Easier to unit test
* Highly maintainable
* Less vulnerable to unintended state changes

This is significantly more robust than relying on procedural scripts and global variables.

> **Transition:** Having established a secure node structure, we must manage the data flowing through it using modern memory tools.

---

## 2. Smart Pointers: Memory Management without the Headaches

Modern ROS2 development strictly avoids raw pointers (`new` and `delete`) to prevent memory leaks and ensure safe memory management across asynchronous callbacks.

| Pointer Type      | Ownership Model                                                               | ROS2 Use Case — The "Why"                                                                                                       |
| ----------------- | ----------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| `std::shared_ptr` | **Shared ownership:** Resource is deleted only when the last pointer is gone. | **Default choice:** Used for nodes and publishers because they are managed asynchronously by executors across multiple threads. |
| `std::unique_ptr` | **Exclusive ownership:** Only one pointer can own the resource.               | **High Performance:** Essential for "Zero-copy" transfers. Moving a unique pointer is faster than copying large data buffers.   |

### Technical Requirement: Zero-Copy Performance

For high-bandwidth data like **LiDAR or camera streams**, publishing a `std::unique_ptr` is a high-performance requirement.

By using:

```cpp
std::move(msg_ptr)
```

the node transfers ownership of the memory directly to a subscriber in the same process.

This can bypass the overhead of unnecessary serialization and copying, which is critical for meeting real-time constraints in embedded hardware.

### Common ROS2 Type Aliases

ROS2 generates convenient aliases within message headers. Use these to maintain professional syntax:

```cpp
std_msgs::msg::String::SharedPtr
sensor_msgs::msg::LaserScan::UniquePtr
nav_msgs::msg::Odometry::ConstSharedPtr
```

> **Transition:** Having secured our memory with smart pointers, we now define the execution logic through callbacks.

---

## 3. Mastering Callbacks: Lambdas vs. `std::bind`

A callback is a function triggered by an event. While traditional ROS2 code used `std::bind`, Modern C++ lambdas are now the preferred standard.

### Traditional: `std::bind`

```cpp
// Requires complex placeholder syntax and extra headers
subscription_ = this->create_subscription<std_msgs::msg::String>(
  "topic", 10, std::bind(&MyNode::callback, this, std::placeholders::_1));
```

### Modern: Capturing Lambdas

```cpp
// Cleaner, inline definition with automatic template deduction
subscription_ = this->create_subscription<std_msgs::msg::String>(
  "topic", 10, [this](const auto msg) { 
    this->handle_message(msg); 
  });
```

### Why Lambdas are Preferred

1. **Readability:**
   The logic is defined inline where it is used, making the code's intent immediately clear.

2. **No Placeholders:**
   Avoids the confusing `std::placeholders::_1` syntax, which can become difficult to manage when callbacks have multiple arguments.

3. **Template Deduction:**
   Using `(const auto msg)` allows the compiler to automatically deduce the message type. This can reduce verbosity and avoid rigid callback declarations.

> **Transition:** These callbacks are made robust through C++ templates and type-safe time units.

---

## 4. Type Safety and Time: Templates, Namespaces, and Chrono

### C++ Templates & Compile-Time Safety

ROS2 uses templates to create generic communication primitives. You must specify the message type in angle brackets `< >`:

```cpp
this->create_publisher<std_msgs::msg::String>(...)
```

### The Professional Edge

Using templates allows the compiler to catch type mismatches at **compile-time** rather than **run-time**.

In embedded systems, catching a bug during compilation is far safer than having a node crash while the robot is in motion.

### Chrono Literals

Using `std::chrono_literals` provides human-readable, type-safe time durations.

Examples:

```cpp
500ms
1s
100us
```

#### Safety Insight

This is safer and clearer than passing raw numbers such as:

```cpp
0.5
```

The compiler understands the time unit, helping prevent timing mistakes in high-frequency rate controllers.

### Essential Namespaces

| Namespace              | Purpose                                                     |
| ---------------------- | ----------------------------------------------------------- |
| `rclcpp::`             | Core ROS2 C++ functionality                                 |
| `std_msgs::msg::`      | Standard message structures                                 |
| `std::chrono_literals` | Provides readable time suffixes such as `ms`, `s`, and `us` |

To use chrono literals:

```cpp
using namespace std::chrono_literals;
```

---

## 5. Production-Ready Template: Minimal Publisher

The following example demonstrates a professional-grade node incorporating the concepts discussed above.

```cpp
#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

// Section 1: OOP Architecture - Inheriting from Node avoids global state
class MinimalPublisher : public rclcpp::Node {
public:
  MinimalPublisher() : Node("minimal_publisher"), count_(0) {

    // Section 4: Templates - Explicitly defining MsgType for compile-time safety
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);

    // Section 3: Modern Lambda - Capturing 'this' to access private members
    auto timer_callback = [this]() -> void {
      auto message = std_msgs::msg::String();

      message.data =
        "Data Packet: " + std::to_string(this->count_++);

      RCLCPP_INFO(
        this->get_logger(),
        "Publishing: '%s'",
        message.data.c_str()
      );

      this->publisher_->publish(message);
    };

    // Section 4: Chrono - Type-safe duration prevents timing logic errors
    timer_ = this->create_wall_timer(500ms, timer_callback);
  }

private:

  // Section 2: Smart Pointers - SharedPtr ensures the timer and publisher
  // remain managed by the node's lifecycle.
  rclcpp::TimerBase::SharedPtr timer_;

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

  size_t count_;
};

int main(int argc, char * argv[]) {

  rclcpp::init(argc, argv);

  // Use make_shared to manage the Node's lifecycle safely
  rclcpp::spin(std::make_shared<MinimalPublisher>());

  // Ensure clean resource cleanup
  rclcpp::shutdown();

  return 0;
}
```

---

## 6. Mapping to the Grading Rubric: "The Professional Edge"

To achieve a high grade, you must demonstrate that your C++ choices are intentional and geared toward production-grade reliability.

| Concept             | What to Demonstrate                                        | Professional Benefit                   |
| ------------------- | ---------------------------------------------------------- | -------------------------------------- |
| **Encapsulation**   | Private members + class inheritance                        | Modularity and reduced global state    |
| **Smart Pointers**  | `std::shared_ptr`, `std::unique_ptr`, ROS2 pointer aliases | Memory safety and controlled ownership |
| **Modern Lambdas**  | Lambdas instead of `std::bind`                             | Readability and maintainability        |
| **Zero-Copy Logic** | `std::unique_ptr` + `std::move()`                          | Real-time efficiency for large data    |
| **Type Safety**     | Templates + `std::chrono_literals`                         | Compile-time safety and robustness     |

### 1. Encapsulation — Modularity

Using private members and class inheritance earns marks for **software quality**.

It proves you can build modular systems that avoid global state pollution.

### 2. Smart Pointers — Memory Safety

Utilizing `std::shared_ptr` and specific `Message::SharedPtr` aliases demonstrates an understanding of modern memory management and ownership in asynchronous ROS2 systems.

### 3. Modern Lambdas — Readability

Choosing lambdas over `std::bind` shows a commitment to modern C++ standards.

It also reduces code complexity and improves **maintainability**.

### 4. Zero-Copy Logic — Performance

Utilizing `std::unique_ptr` and `std::move()` for large data such as LiDAR messages demonstrates an understanding of **real-time efficiency** and optimization for embedded hardware.

### 5. Type Safety — Robustness

Explicit template parameters and `std::chrono_literals` demonstrate that you are writing code designed to catch errors early and reduce run-time failures.

This is a key characteristic of professional **software architecture**.

---

## Quick Exam Checklist

Before submitting a ROS2 C++ node, check:

* [ ] Is the node implemented as a class inheriting from `rclcpp::Node`?
* [ ] Are internal members declared `private`?
* [ ] Are raw `new`/`delete` operations avoided?
* [ ] Are appropriate smart pointers used?
* [ ] Are ROS2 message types explicitly specified in templates?
* [ ] Are lambdas used where they improve readability?
* [ ] Is `std::chrono_literals` used for timer durations?
* [ ] Is `std::move()` used where ownership transfer is appropriate?
* [ ] Have global variables been avoided?
* [ ] Is the code structured for maintainability and testing?
* [ ] Are performance considerations taken into account for high-bandwidth messages?
