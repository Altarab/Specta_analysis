#include <cstdlib>
#include <string>
#include <stdlib.h> 
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "stdlib.h"
#include "TString.h"

    

using namespace std;

bool startsWith(string mainStr, string toMatch)
{
    // std::string::find returns 0 if toMatch is found at starting
    if(mainStr.find(toMatch) == 0)
        return true;
    else
        return false;
}

void execute_g4cuore(const char *dirname, const char *ext=".root")
{
   TSystemDirectory dir(dirname, dirname);
   TList *files = dir.GetListOfFiles();
   if (files) {
      TSystemFile *file;
      TString fname;
      TIter next(files);
      while ((file=(TSystemFile*)next())) {
         fname = file->GetName();
         if (!file->IsDirectory() && fname.EndsWith(ext) && startsWith(fname.Data(),"g4") == false) {
	    string filename = fname.Data(); 
            string str ="g4cuore -I root -i "+filename+" -o g4_"+filename+" -r1 -R1 -D0.000005";
            system((str).c_str());
         }
      }
   }
}

void move_output(const char *dirname, const char *ext=".root")
{
   TSystemDirectory dir(dirname, dirname);
   TList *files = dir.GetListOfFiles();
   if (files) {
      TSystemFile *file;
      TString fname;
      TIter next(files);
      while ((file=(TSystemFile*)next())) {
         fname = file->GetName();
         if (!file->IsDirectory() && fname.EndsWith(ext) && startsWith(fname.Data(),"g4") == true) {
	    string filename = fname.Data(); 
            string str ="mv "+filename+" dir";
            system((str).c_str());
         }
      }
   }
}


void g4_execute()
 {
   char *working_dir_path = realpath(".", NULL);
   execute_g4cuore(working_dir_path);
   system("mkdir dir");
   move_output(working_dir_path);
 }

