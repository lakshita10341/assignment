#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class IMG_Member
{

protected:
   string name;
   string role;
 
public:
   IMG_Member(string name, string role) : name(name), role(role) {}
   
  virtual int give_choices()const =0;
  

  string get_current_date(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
     string date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
     return date;
  }
     
 void view_assignment_status(string &s_name)
   {
      string line;
      string filename = s_name + ".txt";
      ifstream file(filename);
      if (file.is_open())
      {
         int count=0;
         while (getline(file, line))
         {
            if(count>3)
               cout << line << endl;
            count++;
         }
         file.close();
      }
      else
      {
         cout << "Error: no such student exists.\n";
      }
   }

  

};

class Student : public IMG_Member

{

public:
   Student(string name) : IMG_Member(name, "Student") {}

   virtual int give_choices() const override{
            cout << "Choose an action:" << endl;
cout << "1. Submit assignment" << endl;
cout << "2. View assignment status" << endl;
cout << "3. Submit for recheck" << endl;

      int choice;
      cin >> choice;

      return choice;
   }


   

void submit_for_recheck(string s_name, string date){
    string line;
    string filename = s_name + ".txt";
    ifstream file(filename);
    ofstream tempFile("temp.txt");

    if (file.is_open() && tempFile.is_open())
    {
        string assignment;
        cout << "Enter the name of the assignment: ";
        cin.ignore();
        getline(cin, assignment);

      

        bool assignmentFound = false;
        while (getline(file, line))
        {
            tempFile << line << endl;
            if (line.find(assignment) != string::npos)
            {
                tempFile << "Suggested iteration done " <<" on "<< date << endl;
                assignmentFound = true;
            }
        }

        file.close();
        tempFile.close();

        if (assignmentFound)
        {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
            cout << "Submitted\n";
        }
        else
        {
            remove("temp.txt");
            cout << "Assignment not found\n";
        }
    }
    else
    {
        cout << "Error: Unable to open file\n";
    }
}
  
   void submit_assignment(string s_name, string date)
   {


       string line;
    string filename = s_name + ".txt";
    ifstream file(filename);
    ofstream tempFile("temp.txt");

    if (file.is_open() && tempFile.is_open())
    {
        string assignment;
        cout << "Enter the name of the assignment: ";
        cin.ignore();
        getline(cin, assignment);

      

        bool assignmentFound = false;
        while (getline(file, line))
        {
            tempFile << line << endl;
            if (line.find(assignment) != string::npos)
            {
                tempFile << "Assignment submitted " <<" on "<< date << endl;
                assignmentFound = true;
            }
        }

        file.close();
        tempFile.close();

        if (assignmentFound)
        {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
            cout << "Submitted\n";
        }
        else
        {
            remove("temp.txt");
            cout << "Assignment not found\n";
        }
    }
    else
    {
        cout << "Error: Unable to open file\n";
    }
   }
};

class Reviewer : public IMG_Member
{




public:
   Reviewer(string name) : IMG_Member(name, "Reviewer") {}

    virtual int give_choices() const override{
   cout << "Choose an action:" << endl;
cout << "1. See assignment status" << endl;
cout << "2. Give review" << endl;
cout << "3. Add a new student" << endl;
cout << "4. See personal info" << endl;
cout<<"5. Add an assignment"<<endl;
int choice;
      cin >> choice;

      return choice;
 }



  void give_review(string &s_name, string date) const
{
    string line;
    string filename = s_name + ".txt";
    ifstream file(filename);
    ofstream tempFile("temp.txt");

    if (file.is_open() && tempFile.is_open())
    {
        string assignment;
        cout << "Enter the name of the assignment: ";
        cin.ignore();
        getline(cin, assignment);

        string review;
        cout << "Enter the review: ";
        getline(cin, review);

        bool assignmentFound = false;
        while (getline(file, line))
        {
            tempFile << line << endl;
            if (line.find(assignment) != string::npos)
            {
                tempFile << "Review: " << review <<" on "<<date<< endl;
                assignmentFound = true;
            }
        }

        file.close();
        tempFile.close();

        if (assignmentFound)
        {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
            cout << "Review added successfully\n";
        }
        else
        {
            remove("temp.txt");
            cout << "Assignment not found\n";
        }
    }
    else
    {
        cout << "Error: Unable to open file\n";
    }
}

void add_assignment(const string &s_name, const string &date)
{
    string filename = s_name + ".txt";
    ifstream checkFile(filename);
    
    // Check if the file already exists (i.e., student exists)
    if (checkFile)
    {
        cout << "Enter the name of assignment: ";
        string assignment;
        cin.ignore();
        getline(cin, assignment);
        
        cout << "Enter Deadline: ";
        string deadline;
        getline(cin, deadline);
        
        
        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            file << "Assignment: " << assignment << " pending on " << date << endl;
            file << "Deadline: " << deadline << endl;
            cout << "Assignment added successfully\n";
            file.close();
        }
        else
        {
            cout << "Error: Unable to open file\n";
        }
    }
    else
    {
        cout << "Error: Student not found\n";
    }
}


   void add_student(string &s_name)
   {
      string filename = s_name + ".txt";
      ofstream file(filename);
      file << "Name : " << s_name << endl;
      cout << "press 1 if student is developer or 2 if designer\n";
      int choice;
      cin >> choice;
      do
      {
         if (choice == 1)
         {
            file << "Developer\n";
         }
         else if (choice == 2)
         {
            file << "Designer\n";
         }
         else
         {
            cout << "please enter valid choice";
         }
      } while (!(choice == 1 || choice == 2));
      file << "1st year\n";
      file << "----------------------------\n";

      file.close();
   }


   void personal_info(string &s_name)
   {
      string filename = s_name + ".txt";
      ifstream file(filename);
      if (file.is_open())
      {
         string line;
         int count = 0;
         while (getline(file, line) && count < 3)
         {
            cout << line << endl;
         }
      }else{
         cout<<"Error: no such student exists\n";
      }
   }
};

int main()
{

   string name;
   int role;


cout << "Choose your role:" << endl;
cout << "1. Reviewer" << endl;
cout << "2. Student" << endl;

   cin >> role;
   cout << "Enter your name" << endl;
   cin >> name;
   cout<<"************************************\n";
   cout<<"Welcome "<<name<<"!\n";

   if (role == 1)
   {
      Reviewer *r_one = new Reviewer(name);
      string date = r_one->get_current_date();
     
      string s_name;
      char num;
      do{ 

         int choice=r_one->give_choices();

       
      cout << "Enter the name of student\n";
      cin >> s_name;
      if (choice == 1)
      {
         r_one->view_assignment_status(s_name);
      }
      else if (choice == 2)
      {
         r_one->give_review(s_name,date);
      }
      else if (choice == 3)
      {
         r_one->add_student(s_name);
      }else if(choice == 4){
         r_one->personal_info(s_name);
      }else if(choice==5){
         r_one->add_assignment(s_name,date);
      }
      else
      {
         cout << "OOPs!!!wrong choice\n";
      }
      cout<<"press 1 to exit or any other key to continue\n";
      cin>>num;
      }while(num!=49);
      delete r_one;
   }
   else if (role == 2)
   {

      Student *s_one = new Student(name);
       char num;
       do{ 


      int choice=s_one->give_choices();
     string date=s_one->get_current_date();
     
      
      if (choice == 1)
      {
         s_one->submit_assignment(name, date);
      }
      else if (choice == 2)
      {
         s_one->view_assignment_status(name);
      }
      else if (choice == 3)
      {
         s_one->submit_for_recheck(name, date);
      }
      else
      {
         cout << "Sorry!!! wrong choice\n";
      }
      cout<<"press 1 to exit or any other key to continue\n";
      cin>>num;
      }while(num!=49);
      delete s_one;
   }
   
   else
   {
      cout << "Invalid role\n";
   }
}

