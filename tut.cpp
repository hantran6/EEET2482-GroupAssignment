#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*class Staff needs to use class Department. But class Department has not been fully
defined yet. Therefore, forward declaration for class Department needs to be done first.*/
class Department;

class Staff{
    private:
        string name;
        string departmentName; //using departmentName only to store department name
                                //doesn't have to store department object
    
    public:
        Staff(string name="", string departmentName="")
            :name(name), departmentName(departmentName){}

        string getName(){
            return name;
        }

        //These two methods will be defined later because class Department has not been fully defined
        void joinDept(Department &department);
        void leaveDept(Department &department);

        void showInfo(){
            cout << "Staff name: " << name << "\n";
            cout << "Department: " << departmentName << "\n\n";
        }
};

class Department{
    protected:
        string name;
        string location;
        vector<Staff*> staffList;
    
    public:
        Department(string name = "", string location = "", vector<Staff*> staffList = {})
            :name(name), location(location), staffList(staffList){}

        friend class Staff;  //friend class to grant access    

        void showInfo(){
            cout << "Department name: " << name << endl;
            cout << "Location: " << location << endl;
            cout << "Staff list: ";
            
            if(staffList.empty()){
                cout << "None.\n";
            }else{
                cout << "\n";
                
                for(Staff* i : staffList){
                    cout << i->getName() << endl;
                }
            }
        }
};

//Academic department - derived class of Department
class Academic : public Department{
    private:
        int numOfCourses;
    
    public:
        Academic(int numOfCourses=0, string name="", string location="", vector<Staff*> staffList={})
            :numOfCourses(numOfCourses), Department(name, location, staffList){}

        void showInfo(){
            Department::showInfo();
            cout << "Number of courses: " << numOfCourses << "\n\n";
        }
};

//NonAcademic department - derived class of Department
class NonAcademic : public Department{
    private:
        int numOfServices;
    
    public:
        NonAcademic(int numOfServices=0, string name="", string location="", vector<Staff*> staffList={})
            :numOfServices(numOfServices), Department(name, location, staffList){}

        void showInfo(){
            Department::showInfo();
            cout << "Number of services: " << numOfServices << "\n\n";
        }

};

void Staff::joinDept(Department &department){
    if(departmentName != ""){
        leaveDept(department);
    }
    departmentName = department.name;
    department.staffList.push_back(this);
}

void Staff::leaveDept(Department &department){
    //find and remove current staff from the list
    for (int i = 0; i < department.staffList.size(); i++) {
        if (department.staffList[i] == this) {
            department.staffList.erase(department.staffList.begin() + i);
            departmentName = ""; //set the staff department name to empty string
        }
    }
}

int main()
{
    Staff st1("Ling Huo Chong", ""), st2("Michael John", ""), st3("Ali Baba", ""); 

    Academic dept1(20, "SSET", "Building 2, 4th floor", vector<Staff*>{});
    NonAcademic dept2(30, "ITS", "Building 1, Gnd floor", vector<Staff *>{});

    st1.joinDept(dept1);
    st2.joinDept(dept1);
    st3.joinDept(dept2);
    
    st1.showInfo();
    st2.showInfo();
    st3.showInfo();

    dept1.showInfo();
    dept2.showInfo();

    //movement of staff
    st1.leaveDept(dept1);
    st1.joinDept(dept2);

    cout << "After movement of staff\n";
    st1.showInfo();
    st2.showInfo();
    st3.showInfo();

    dept1.showInfo();
    dept2.showInfo();

    return 0;
}