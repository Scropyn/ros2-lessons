/*
--Node description: 
...what the node is doing (functionally)... 
When node is created it wil receive all messages with the topic "the_answer"
and wil print it on the terminal using Logger giving the points back and point minus one.

used in week 2 but for easy use put in this folder
*/ 

/*
--Software changes:
one line per change 
(1) created 31.3.2025: developer-Tilmann Koster reviewer(s)-Niek Ottens 
(2) changed 10.09.2026 developer-Sara Sotomayor
...
*/




//--general includes 
#include <cstdlib>
#include "rclcpp/rclcpp.hpp"
#include <geometry_msgs/msg/point.hpp>

//--custom includes 
#include "std_msgs/msg/int32.hpp"  

//--using 
using namespace std::placeholders;

//--Node class 
class TemplateSubscriber : public rclcpp::Node
{
  public:
  //-- constuctor: 
  TemplateSubscriber(): Node("templatesubscriber_node")
  {
     //--communication and timer objects: 
    subscriber_theanswer_ = this->create_subscription<geometry_msgs::msg::Point>(
      "the_answer", 10,
      std::bind(&TemplateSubscriber::subscriber_theanswer_callback, this, _1)); //_1 isplaceholder
  }


  //-- communication and timer functions 
  void subscriber_theanswer_callback(const geometry_msgs::msg::Point::SharedPtr msg)
  { 
    /* your code */
    answer_to_all_    = msg->x; //gets the message data (field name data!)
    answer_min_one_    = msg->x - 1; 
    RCLCPP_INFO(this->get_logger() ,"\nHello subscriber the answer is: %d \nThe answer minus one: %d",answer_to_all_, answer_min_one_); //example code  
   /* your code */
    
  }
  
  //--customs functions:
  //--custom variables: 
private:
  //--rclcpp variables:
  rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscriber_theanswer_;
  //--custom variables:
  int answer_to_all_  = 0;
  int answer_min_one_ = 0;
  
};

int main(int argc, char * argv[])
{
  
rclcpp::init(argc, argv);

auto node = std::make_shared<TemplateSubscriber>();

rclcpp::spin(node);

rclcpp::shutdown();
return 0;
}
