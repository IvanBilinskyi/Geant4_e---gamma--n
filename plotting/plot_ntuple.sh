TH2D *hxy = new TH2D("hxy", ";y [mm];z [mm]", 100, -10, 10, 100, -10, 10)
Tracks->Draw("z:y>>hxy", "name==\"neutron\"&&status==\"plate5\"", "colz")

double size = 10
TH2D *hxy = new TH2D("hxy", ";y [mm];z [mm]", 100, -size, size, 100, -size, size)
Tracks->Draw("y:x>>hxy_quartz", "name==\"neutron\"&&status==\"quartz\"", "colz")

# gammas
TH2D *hxy_gamma = new TH2D("hxy_gamma", ";x [mm];y [mm]", 100, -size, size, 100, -size, size)
Tracks->Draw("y:x>>hxy_gamma", "name==\"gamma\"&&status==\"quartz\"", "colz")

# electrons
TH2D *hxy_electron = new TH2D("hxy_electron", ";x [mm];y [mm]", 100, -size, size, 100, -size, size)
Tracks->Draw("y:x>>hxy_electron", "name==\"e-\"&&status==\"quartz\"", "colz")

TH2D *hxy = new TH2D("hxy", ";y [mm];z [mm]", 100, -10, 10, 100, -10, 10)
Tracks->Draw("y:x>>hxy", "status!=\"quartz\"&&", "colz")


