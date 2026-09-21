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
    int my_result = 0;
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
  void callTemplateS(std::string name)  // calling service method with the value you like 
  {
 
    while (!template_serviceclient_ -> wait_for_service(std::chrono::seconds(1)))  //waiting for the server node
      {
        RCLCPP_WARN(this->get_logger() , "Watiting for the server ...");
      }

    auto request = std::make_shared<TemplateS::Request>();//define request

    request->sname = name; // value of request 
    template_serviceclient_ ->async_send_request(request,std::bind(&TemplateServiceClient::callbackTemplateSResponse,this,_1)); 
  };



void callbackTemplateSResponse(rclcpp::Client<TemplateS>::SharedFuture future)
{
auto response = future.get();
my_result = (int)response->snumber;
// do something the the response
RCLCPP_INFO(this->get_logger(),"The number we want to know is: %d",(int)response->snumber); //laat dit erin anders doet hij het niet
}
//--customs functions:
//...
void process()
  {
    RCLCPP_INFO(this->get_logger(),"The class variable my_result is: %d",my_result);
    callTemplateS("Tilmann");
    RCLCPP_INFO(this->get_logger(),"The class variable my_result is: %d",my_result);
    callTemplateS("Kamiel");
    RCLCPP_INFO(this->get_logger(),"The class variable my_result is: %d",my_result);
  }  



private :
//--rclcpp variables:
rclcpp::Client<TemplateS>::SharedPtr template_serviceclient_; // do not forget to declare this pointer 
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