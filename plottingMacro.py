from ROOT import TFile,TH1F,TH2F,TCanvas

path = '/lstore/calo/aluisa/'
fname = 'outputNtupleTileFCC.root'

f = TFile.Open(path+fname)
tree = f.Get("eventTree")

c1 = TCanvas()
h_hit_2d = TH2F() 
tree.Draw("HitY:HitZ>>h_hit_2d","HitY!=-999 && HitZ!=-999","colz")
c1.SaveAs("test.png")
