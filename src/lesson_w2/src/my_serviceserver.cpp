/*
Node description: starts service server with request of vector and returns the length with .2 decimals
to call in terminal: ros2 service call /templateserviceserver interface_pkg/srv/MyVector "{my_vector: {x: 1, y: 0, z: 3}}"
*/ 


/*
Software changes (one line by change):
(1) 31.3.2025 created by Tilmann Koster 
(2) 12.09.2026 developer- Sara Sotomayor: altered template for the exercise of lesson 6
*/



//--general includes 
#include "rclcpp/rclcpp.hpp" // altijd nodig 
//--custom includes  
#include "interface_pkg/srv/my_vector.hpp" 
#include <cmath>

//--using 
using MyVector = interface_pkg::srv::MyVector;

using namespace std::placeholders;

//--Node class 
class TemplateServiceServer : public rclcpp::Node
{
  public :
  //-- constuctor: 
  TemplateServiceServer() : Node("templateserviceserver_node")
  {
     //--communication and timer objects: 
    template_serviceserver_ = this -> create_service<MyVector>("templateserviceserver",
                                      std::bind(&TemplateServiceServer::callBackMyVector,this,_1,_2));
    RCLCPP_INFO(this->get_logger(), "Servcie Server started");
     //--customs functions:
  }

  //-- communication and timer functions 
  void callBackMyVector(const MyVector::Request::SharedPtr request, const MyVector::Response::SharedPtr response)
  {
    
    // your code   
    if(request->my_vector.x != 0 || 
      request-> my_vector.y != 0 || 
      request-> my_vector.z != 0) 
      { response->l = std::sqrt(
        std::pow(request->my_vector.x,2) + 
        std::pow(request->my_vector.y,2) +
        std::pow(request->my_vector.z,2));}
    else 
      {
       response -> l = 0; 
      }
    //your code
};

//--customs functions:
//... 

private :
//--rclcpp variables:
rclcpp::Service<MyVector>::SharedPtr template_serviceserver_; 

};




int main(int argc, char * argv[])
{
  
  rclcpp::init(argc, argv);

  auto node = std::make_shared<TemplateServiceServer>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
