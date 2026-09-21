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
#include "interface_pkg/srv/template_s.hpp"  // your own service interface =small letter, CAPs is translated to _ 
//--using 
using TemplateS = interface_pkg::srv::TemplateS ;
using namespace std::placeholders;



class TemplateServiceClient : public rclcpp::Node
{

  public : 
  
//-- constuctor: 
  TemplateServiceClient() : Node("templateserviceclient_node")
  {
    //--communication and timer objects: 
    template_serviceclient_ = this -> create_client<TemplateS>("templateserviceserver");// name of serviceserver
    
    request_timer_ = this->
                        create_wall_timer(std::chrono::seconds(1),std::bind(&TemplateServiceClient::callTemplateS,this)); 
    process_timer_ = this->
                        create_wall_timer(std::chrono::seconds(2),std::bind(&TemplateServiceClient::process,this));
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

    auto request = std::make_shared<TemplateS::Request>();//define request

    request->sname = name_; // value of request 
    template_serviceclient_ ->async_send_request(request,std::bind(&TemplateServiceClient::callbackTemplateSResponse,this,_1)); 
    
  };



void callbackTemplateSResponse(rclcpp::Client<TemplateS>::SharedFuture future)
{
auto response = future.get();
// do something the the response
RCLCPP_INFO(this->get_logger(),"The number we got is: %d",(int)response->snumber);
last_number_ = response->snumber;
new_received_= true;
}

//--customs functions:
//...
void process()
{ 
  if(!new_received_)  
  { return; }

  
  RCLCPP_INFO(this->get_logger(),"the name  is: %s",name_.c_str());
  RCLCPP_INFO(this->get_logger(),"the number we processed is: %d",last_number_);
  //name_ = "Kamiel";

  if (name_ == "Kamiel") name_ = "Tilmann";
  else if (name_ == "Tilmann") name_ = "Kamiel";


  new_received_ = false;
    
  }  

 
private :
std::string name_ = "Tilmann" ;
int last_number_ ;
bool new_received_ = false ;
//--rclcpp variables:
rclcpp::TimerBase::SharedPtr request_timer_;
rclcpp::TimerBase::SharedPtr process_timer_;
rclcpp::Client<TemplateS>::SharedPtr template_serviceclient_;// do not forget to declare this pointer 
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