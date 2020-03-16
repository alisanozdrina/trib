// Main Function
void ev_rate(){
  	TFile* fin = new TFile("ara02_2015_2017.root", "OPEN");
  	TTree* t= (TTree*) fin->Get("SNvaltree"); //tree name
  	Int_t runno, evenum;
  	Double_t tstamp, utime;
    Double_t current_hour, current_ev;
  	t->SetBranchAddress("runno", &runno);
  	t->SetBranchAddress("evenum", &evenum);
  	t->SetBranchAddress("tstamp", &tstamp);
    t->SetBranchAddress("utime",&utime);
  	std::ofstream fout ("rate_ara2_2017.txt");
  	Int_t nEntries;
    Double_t ev_num =0;
    nEntries = t->GetEntries();
    cout << "nEntries " << nEntries << endl;
    Double_t prev_hour = 394782;
    Double_t prev_ev = 0;
    Double_t ev_rate = 0;

    for (int i=0; i<nEntries; i++){
      if (!(i%100000)) cout << "Processing event " << i << ", " << Int_t(100.*i/nEntries) << "% completed" << endl;
      t->GetEntry(i);
      current_hour = int(utime / (60*60));
      cout.precision(17);
      fout.precision(17);
             fout  << runno << " " << evenum << " " << ev_rate << " " << utime << endl;
      if (current_hour == prev_hour){
        ev_num++; 

        }
      if (current_hour != prev_hour){
        ev_rate = ev_num/(60*60);
        prev_hour = current_hour;
        ev_num=0;
      }
    }
    fout.close();  

}	