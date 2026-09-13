/*
--Node description: 
...what the node is doing (functionally)... 
When node is created a timer is activated that will print every second a number. 
The next number is always a the old number plus one 
further it does nothing more than being alive
*/ 

/*
--Software changes:
one line per change 
(1) created 31.3.2025: developer-Tilmann Koster reviewer(s)-Niek Ottens 
(2) changed 01.4.2025: xxx functionality added ... : developer-Tilmann Koster reviewer(s)-Niek Ottens 
...
*/



//--general includes 
#include <cstdlib>
#include <cmath>
#include "rclcpp/rclcpp.hpp"
#include <rclcpp/clock.hpp>
#include <rclcpp/time.hpp>

//--custom includes 
//...

//--using 
//...

class Template_Walltimer : public rclcpp::Node 
{
 public: 
    //-- constuctor: 
    Template_Walltimer() : Node("template_walltimer_node")   /*constructor = multiple inheritance*/ 
    {
        //--communication and timer objects: 
        timer_template_= this->create_wall_timer(std::chrono::seconds(3),std::bind(&Template_Walltimer::timer_template_function,this));
        //--customs functions:
        //... 

    }
    
    //-- communication and timer functions 
	//... 
	

    /*function binded to timer_ ...executed by timer */ 
    void timer_template_function()          
    { 

            my_function_ = (std::cos(t_+ (h_ / counter_)) - std::cos(t_)) / (h_ / counter_);
            counter_++;

            //error calculation
            my_function_2_ = (std::cos(t_+ (h_ / counter_)) - std::cos(t_ - (h_ / counter_))) / (2 *(h_ / counter_));

            //error rate
            error_rate_ = (my_function_ - my_function_2_);


        RCLCPP_INFO(this->get_logger() ,"\n The derivative of : %f \n Function 2 gives: %f \n error rate: %f", my_function_, my_function_2_, error_rate_); //example code  

 
    }

    //--customs functions:

private:
    //--rclcpp varabiables:
    rclcpp::TimerBase::SharedPtr timer_template_;
    //--custom variables
    int counter_ = 0;   // example parameter 
    rclcpp :: Time my_time_;
	rclcpp :: Clock my_clock_;
    float my_function_ ;
    float my_function_2_ ;
    float error_rate_;
    float t_ = 1.5;
    float h_ = 0.5;

    
};


int main(int argc,char *argv[])
{

rclcpp::init(argc,argv);

auto node = std::make_shared<Template_Walltimer>();
rclcpp::spin(node);
rclcpp::shutdown();

return 0;
}
