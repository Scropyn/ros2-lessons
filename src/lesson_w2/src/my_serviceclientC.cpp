/*
Node description: what is the node doing 
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
#include "rclcpp/rclcpp.hpp" // altijd nodig 
#include <chrono>
#include <thread>
//--custom includes 
//#include "interface_pkg/srv/template_s.hpp"  // your own service interface =small letter, CAPs is translated to _ 
#include "interface_pkg/srv/my_vector.hpp"
//--using 
//using TemplateS = interface_pkg::srv::TemplateS ;
using MyVector = interface_pkg::srv::MyVector;
using namespace std::placeholders;



class TemplateServiceClient : public rclcpp::Node
{

  public : 
  
//-- constuctor: 
  TemplateServiceClient() : Node("templateserviceclient_node")
  {
    //--communication and timer objects: 
    template_serviceclient_ = this -> create_client<MyVector>("templateserviceserver");// name of serviceserver
    
    request_timer_ = this->
                        create_wall_timer(std::chrono::seconds(2),std::bind(&TemplateServiceClient::callTemplateS,this)); 
    process_timer_ = this->
                        create_wall_timer(std::chrono::seconds(1),std::bind(&TemplateServiceClient::process,this));
    //--customs functions:
    process();
    
		//...
  }
   

//-- communication and timer functions   
  void callTemplateS()  // calling service method with the value you like 
  {
    while (!template_serviceclient_ -> wait_for_service(std::chrono::seconds(1)))  //waiting for the server node
      {
        RCLCPP_WARN(this->get_logger() , "Watiting for the server ...");
      }

    auto request = std::make_shared<MyVector::Request>();//define request
    point_x_ += 1;

    request->my_vector.x = point_x_;
    request->my_vector.y = point_y_;
    request->my_vector.z = point_z_;
    template_serviceclient_ ->async_send_request(request,std::bind(&TemplateServiceClient::callbackTemplateSResponse,this,_1)); 
    
  };



void callbackTemplateSResponse(rclcpp::Client<MyVector>::SharedFuture future)
{
auto response = future.get();
// do something the the response
//RCLCPP_INFO(this->get_logger(),"The lenght is: %d",(int)response->l);
last_number_ = response->l;
new_received_= true;
}

//--customs functions:
//...
void process()
{ 
  if(!new_received_)  
  { return; }

  
  RCLCPP_INFO(this->get_logger(),"the lenght  is: %f", last_number_);
  RCLCPP_INFO(this->get_logger(),"the number we processed is: %f, %f, %f",point_x_, point_y_, point_z_);


  new_received_ = false;
    
  }  

 
private :
float point_x_ = 0;
float point_y_ = 0;
float point_z_ = 0;
float last_number_ ;
bool new_received_ = false ;
//--rclcpp variables:
rclcpp::TimerBase::SharedPtr request_timer_;
rclcpp::TimerBase::SharedPtr process_timer_;
rclcpp::Client<MyVector>::SharedPtr template_serviceclient_;// do not forget to declare this pointer 
//--custom variables:
//...
};


int main(int argc, char * argv[])
{
  
  rclcpp::init(argc, argv);

  auto node = std::make_shared<TemplateServiceClient>();
  
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}