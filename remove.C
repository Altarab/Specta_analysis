#include <cstdlib>
#include <string>
#include <stdlib.h> 
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "stdlib.h"
#include "TString.h"


void execute_remove(const char *dirname, const char *ext=".root")
{
   TSystemDirectory dir(dirname, dirname);
   TList *files = dir.GetListOfFiles();
   if (files) {
      TSystemFile *file;
      TString fname;
      TIter next(files);
      while ((file=(TSystemFile*)next())) {
         fname = file->GetName();
         if (!file->IsDirectory() && fname.EndsWith(ext)) {
	    string filename = fname.Data(); 
            string str ="rm "+filename;
            system((str).c_str());
         }
      }
   }
}


void remove()
 {
   char *working_dir_path = realpath(".", NULL);
   execute_remove(working_dir_path);
 }

