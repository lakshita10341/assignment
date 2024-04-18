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

   virtual int give_choices() const = 0;

   string get_current_date()
   {
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
         int count = 0;
         while (getline(file, line))
         {
            if (count > 3)
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

   virtual int give_choices() const override
   {
      cout << "Choose an action:" << endl;
      cout << "1. Submit assignment" << endl;
      cout << "2. View assignment status" << endl;
      cout << "3. Submit for recheck" << endl;

      int choice;
      cin >> choice;

      return choice;
   }

   void submit_for_recheck(string s_name, string date)
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
         int recheck=0;
         int r=0;
         bool assignmentFound = false;
         while (getline(file, line))
         {
               if(recheck){
                   tempFile << "Suggested iteration done "
                        << " on " << date << endl;
              
               recheck=0;
               r=1;
               }

            tempFile << line << endl;
            if (line.find(assignment) != string::npos)
            {     if(line.find("Review")!=string::npos){
               recheck=1;

            }
               assignmentFound = true;
            }
         }

         file.close();
         tempFile.close();

         if (assignmentFound)
         {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
            if(r==1){ 
               cout << "Submitted\n";
            }else{
               cout<<"Assignment not reviewed\n";
            }
            
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
               tempFile << "Assignment submitted "
                        << " on " << date << endl;
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

   virtual int give_choices() const override
   {
      cout << "Choose an action:" << endl;
      cout << "1. See assignment status" << endl;
      cout << "2. Give review" << endl;
      cout << "3. Add a new student" << endl;
      cout << "4. See personal info" << endl;
      cout << "5. Add an assignment" << endl;
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

         bool assignmentFound = false;
         int found = 0;
         int r = 0;
         while (getline(file, line))
         {

            if (found)
            {
               if (line.find("submitted") != string::npos)
               {
                  string review;
                  cout << "Enter the review: ";
                  cin.ignore();
                  getline(cin, review);
                  tempFile << "Review: " << review << " on " << date << endl;
               }
               else
               {  
               
                  tempFile<<"Reminder: Submit your assignment before deadline\n";
                  cout << "Assignment not submitted yet! You can't give review\n";
                  cout<<"Reminder sent!\n";
                  

               }
               found = 0;
            }
            tempFile << line << endl;
            if (line.find(assignment) != string::npos)
            {
               found++;

               assignmentFound = true;
            }
         }

         file.close();
         tempFile.close();

         if (assignmentFound)
         {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
            remove("temp.txt");
            if (r = 0)
            {
               cout << "Review added successfully\n";
            }
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

      system("./find.sh");
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
      string line;
      ifstream assignment("ASSIGNMENT.txt");
      if (file.is_open() && assignment.is_open())
      {
         while (getline(assignment, line))
         {
            file << line << endl;
         }
      }
      assignment.close();
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
            count++;
         }
      }
      else
      {
         cout << "Error: no such student exists\n";
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
   cout << "************************************\n";
   cout << "Welcome " << name << "!\n";

   if (role == 1)
   {
      Reviewer *r_one = new Reviewer(name);
      string date = r_one->get_current_date();

      string s_name;
      char num;
      do
      {

         int choice = r_one->give_choices();

         if (choice == 5)
         {
            r_one->add_assignment(s_name, date);
         }
         else
         {

            cout << "Enter the name of student\n";
            cin >> s_name;
            if (choice == 1)
            {

               r_one->view_assignment_status(s_name);
            }
            else if (choice == 2)
            {

               r_one->give_review(s_name, date);
            }
            else if (choice == 3)
            {

               r_one->add_student(s_name);
            }
            else if (choice == 4)
            {

               r_one->personal_info(s_name);
            }

            else
            {
               cout << "OOPs!!!wrong choice\n";
            }
         }

         cout << "press 1 to exit or any other key to continue\n";
         cin >> num;
      } while (num != 49);
      delete r_one;
   }
   else if (role == 2)
   {

      Student *s_one = new Student(name);
      char num;
      do
      {

         int choice = s_one->give_choices();
         string date = s_one->get_current_date();

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
         cout << "press 1 to exit or any other key to continue\n";
         cin >> num;
      } while (num != 49);
      delete s_one;
   }

   else
   {
      cout << "Invalid role\n";
   }
}
