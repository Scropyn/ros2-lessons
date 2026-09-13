/*
--Node description: 
for hw lesson custom message: sends out int and name every 3 seconds

in terminal to listen: ros2 topic echo /the_answer

*/ 

/*
--Software changes:
one line per change 
(1) created 31.3.2025: developer-Tilmann Koster reviewer(s)-Niek Ottens 
(2) changed 01.4.2025: xxx functionality added ... : developer-Tilmann Koster reviewer(s)-Niek Ottens 
...
*/


//-- tester: Sander Gieling



//--general includes 
#include <cstdlib>
#include "rclcpp/rclcpp.hpp"
#include <rclcpp/clock.hpp>
#include <rclcpp/time.hpp>
#include "interface_pkg/msg/name.hpp"

//--custom includes 
//...

//--using 
//...


//--Node class 

class Template_General : public rclcpp::Node
{
	public:
	//-- constuctor: 
	Template_General() : Node("template_general_node")
	{
	 //--communication and timer objects: 
	 //see templates for subcribers, action server ... 
	 //...  
	 publisher_theanswer_ = this->create_publisher<interface_pkg::msg::Name>("the_answer",10);
	 timer_template_= this->create_wall_timer(std::chrono::seconds(3),std::bind(&Template_General::custom_example,this));
	 
	 //--customs functions:
		custom_example();
	 //... 
	 
	}

	//-- communication and timer functions 
	//... 

	//--customs functions:
	void custom_example()
	{   
		name_.my_int = 32;
		name_.name = "Sara";

		publisher_theanswer_ ->publish(name_);
		

		/*your custom example code */
		 //RCLCPP_INFO(this->get_logger() ,"My name: %s, my age: %d", name_.name.c_str(), name_.my_int); //code example


	}

	//--custom variables: 

	private:

	//--rclcpp variables:
	rclcpp::Publisher<interface_pkg::msg::Name>::SharedPtr publisher_theanswer_;
	rclcpp::TimerBase::SharedPtr timer_template_;
	rclcpp ::Time my_time_;
	rclcpp ::Clock my_clock_;
	interface_pkg::msg::Name name_;
		
	//--custom variables:
	//...

};


int main(int argc,char *argv[])
{
rclcpp::init(argc,argv)	;

auto node = std::make_shared<Template_General>();


rclcpp::spin(node);

rclcpp::shutdown();

return 0;

}