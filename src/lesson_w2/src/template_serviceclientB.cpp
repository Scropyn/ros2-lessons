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
    
    //--customs functions:
    process();
    
		//...
  }
   

 
//-- communication and timer functions   

  int callTemplateS(std::string name)  // calling service method with the value you like 
  {
    int res =0;
    while (!template_serviceclient_ -> wait_for_service(std::chrono::seconds(1)))  //waiting for the server node
      {
        RCLCPP_WARN(this->get_logger() , "Watiting for the server ...");
      }

    auto request = std::make_shared<TemplateS::Request>();//define request

    request->sname = name; // value of request 
    auto result_future_ = template_serviceclient_ ->async_send_request(request); 

    if (rclcpp::spin_until_future_complete(this->get_node_base_interface(),result_future_) ==
    rclcpp::FutureReturnCode::SUCCESS)
    {
      auto response = result_future_.get();
      RCLCPP_INFO(this->get_logger(),"The number we want to know is: %ld",response->snumber);  
      res = response->snumber;
    } 
    else 
    {
      RCLCPP_ERROR(this->get_logger(), "Failed to get number");
    }
    
    return res;
  };
// note format of res has to be defined now it is integer

  void process()
  {
    int service_return ;
    service_return = callTemplateS("Tilmann");
    RCLCPP_INFO(this->get_logger(),"The number we want is x1: %d",service_return);  
    service_return = callTemplateS("Wessel");
    RCLCPP_INFO(this->get_logger(),"The number we want is x2: %d",service_return);
  }  

//--customs functions:
//...




private :


//--rclcpp variables:
rclcpp::Client<TemplateS>::SharedPtr template_serviceclient_; // do not forget to declare this pointer 

//--custom variables:
//...
// custom process using custom servicecall 


};




int main(int argc, char * argv[])
{
  
  rclcpp::init(argc, argv);

  auto node = std::make_shared<TemplateServiceClient>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
