#include <string>
#include <iostream>
#include <vector>

using namespace std;
 
class WheelAntiSkidding;
class EngineTempmonitoring;
class BodyTauchmonitoring;
class CarInitModule;
 
// interface to all CarInitModule 'parts'
struct CarElementModuleInterface 
{
  virtual void visitNodeForCarMonitoring(WheelAntiSkidding& WheelAntiSkidding) const = 0;
  virtual void visitNodeForCarMonitoring(EngineTempmonitoring& EngineTempmonitoring) const = 0;
  virtual void visitNodeForCarMonitoring(BodyTauchmonitoring& BodyTauchmonitoring) const = 0;
 
  virtual void visitCar(CarInitModule& CarInitModule) const = 0;
  virtual ~CarElementModuleInterface() {};
};
 
// interface to one part
struct CarElementInterfaceVisitor 
{
  virtual void accept(const CarElementModuleInterface& visitor) = 0;
  virtual ~CarElementInterfaceVisitor() {}
};
 
// WheelAntiSkidding element, there are four wheels with unique names
class WheelAntiSkidding : public CarElementInterfaceVisitor
{
public:
  explicit WheelAntiSkidding (const string& name) :
    name_(name)
  {
  }
  const string& getName() const 
  {
    return name_;
  }
  void accept(const CarElementModuleInterface& visitor)  
  {
    visitor.visitNodeForCarMonitoring(*this);
  }
private:
    string name_;
};
 
// EngineTempmonitoring
class EngineTempmonitoring : public CarElementInterfaceVisitor
{
public:
  void accept(const CarElementModuleInterface& visitor) 
  {
    visitor.visitNodeForCarMonitoring(*this);
  }
};
 
// BodyTauchmonitoring
class BodyTauchmonitoring : public CarElementInterfaceVisitor
{
public:
  void accept(const CarElementModuleInterface& visitor) 
  {
    visitor.visitNodeForCarMonitoring(*this);
  }
};
 
// CarInitModule, all CarInitModule elements(parts) together
class CarInitModule 
{
public:
  vector<CarElementInterfaceVisitor*>& getElements()
  {
    return elements_;
  }
  CarInitModule() 
  {
    // assume that neither push_back nor WheelAntiSkidding(const string&) may throw
    elements_.push_back( new WheelAntiSkidding("front left") );
    elements_.push_back( new WheelAntiSkidding("front right") );
    elements_.push_back( new WheelAntiSkidding("back left") );
    elements_.push_back( new WheelAntiSkidding("back right") );
    elements_.push_back( new BodyTauchmonitoring() );
    elements_.push_back( new EngineTempmonitoring() );
  }
  ~CarInitModule()
  {
    for(vector<CarElementInterfaceVisitor*>::iterator it = elements_.begin(); 
      it != elements_.end(); ++it)
    {
      delete *it;
    }
  }
private:
  vector<CarElementInterfaceVisitor*> elements_;
};
 
// PrintVisitor and DoVisitor show by using a different implementation the CarInitModule class is unchanged
// even though the algorithm is different in PrintVisitor and DoVisitor.
class CarElementViewVisitor : public CarElementModuleInterface 
{
public:
  void visitNodeForCarMonitoring(WheelAntiSkidding& WheelAntiSkidding) const
  { 
    cout << "Visiting " << WheelAntiSkidding.getName() << " WheelAntiSkidding" << endl;
  }
  void visitNodeForCarMonitoring(EngineTempmonitoring& EngineTempmonitoring) const
  {
    cout << "Visiting EngineTempmonitoring" << endl;
  }
  void visitNodeForCarMonitoring(BodyTauchmonitoring& BodyTauchmonitoring) const
  {
    cout << "Visiting BodyTauchmonitoring" << endl;
  }
  void visitCar(CarInitModule& CarInitModule) const
  {
    cout << endl << "Visiting CarInitModule" << endl;
    vector<CarElementInterfaceVisitor*>& elems = CarInitModule.getElements();
    for(vector<CarElementInterfaceVisitor*>::iterator it = elems.begin();
      it != elems.end(); ++it )
    {
      (*it)->accept(*this);	// this issues the callback i.e. to this from the element  
    }
    cout << "Visited CarInitModule" << endl;
  }
};
 
class CarElementDoVisitor : public CarElementModuleInterface 
{
public:
  // these are specific implementations added to the original object without modifying the original struct
  void visitNodeForCarMonitoring(WheelAntiSkidding& WheelAntiSkidding) const
  {
    cout << "Kicking my " << WheelAntiSkidding.getName() << " WheelAntiSkidding" << endl;
  }
  void visitNodeForCarMonitoring(EngineTempmonitoring& EngineTempmonitoring) const
  {
    cout << "Starting my EngineTempmonitoring" << endl;
  }
  void visitNodeForCarMonitoring(BodyTauchmonitoring& BodyTauchmonitoring) const
  {
    cout << "Moving my BodyTauchmonitoring" << endl;
  }
  void visitCar(CarInitModule& CarInitModule) const
  {
    cout << endl << "Starting my CarInitModule" << endl;
    vector<CarElementInterfaceVisitor*>& elems = CarInitModule.getElements();
    for(vector<CarElementInterfaceVisitor*>::iterator it = elems.begin();
      it != elems.end(); ++it )
    {
      (*it)->accept(*this);	// this issues the callback i.e. to this from the element  
    }
    cout << "Stopped CarInitModule" << endl;
  }
};
 
int main()
{
  CarInitModule CarInitModule;
  CarElementViewVisitor printVisitor;
  CarElementDoVisitor doVisitor;
  
  printVisitor.visitCar(CarInitModule);
  doVisitor.visitCar(CarInitModule);

  return 0;
}