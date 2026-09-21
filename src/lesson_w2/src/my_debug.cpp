/*
--Node description: 
...what the node is doing (functionally)... 
When node is created the node prints the 5 levels of logging
in terminal: ros2 run lesson_w2 my_debug --ros-args --log-level DEBUG
and for log file: ls -lt ~/.ros/log/ | head
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
	 
	 //--customs functions:
		custom_example();
	 //... 
	 
	}

	//--customs functions:
	void custom_example()
	{   
		RCLCPP_DEBUG(this->get_logger(), "This is DEBUG\n");
		RCLCPP_INFO(this->get_logger(), "This is INFO");
		RCLCPP_WARN(this->get_logger(), "This is WARN");
		RCLCPP_ERROR(this->get_logger(), "This is ERROR");
		RCLCPP_FATAL(this->get_logger(), "This is FATAL");

	}

	private:

};


int main(int argc,char *argv[])
{

rclcpp::init(argc,argv)	;
auto node = std::make_shared<Template_General>();
rclcpp::spin(node);
rclcpp::shutdown();

return 0;

}