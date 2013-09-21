#include "GeoModel.h"
//------------------------------------------------------------------------------
GeoModel::GeoModel()
{
    modset = new Mset();
    dane = new GeoDat();
    cube = new GeoCube(modset->start,modset->sp,modset->grid);
    curVariogram = NULL;
    this->raport_add("nowy model \n");
}
GeoModel::~GeoModel()
{
    delete modset;
    delete dane;
    delete cube;
    if (curVariogram) delete curVariogram;
}
//------------------------------------------------------------------------------
void GeoModel::wczytaj_dane(string fileName, string sep, bool nowe, bool sred)
{
    if(!dane) dane = new GeoDat();
    else if (nowe) dane->usun();

    wektor3d w;

    dane->wczytaj_plik(fileName,sep, sred);
    modset->start = dane->get_min_zakres();
    w = dane->get_wymiary();

    double d = std::max(w.x, w.y);
    d =std::max(d, w.z);
    double s= std::ceil(d/50);

    modset->wym =w;
    modset->name = fileName;

    modset->sp=s;
    modset->grid = wektor3i((int)(w.x/s+2),(int)(w.y/s+2),(int)(w.z/s+2));

    updateModel();

    nowy_variogram(last_set.rozmiar_klasy);
    modset->cutoff = dane->get_min_value().x+
            0.5 * (dane->get_max_value().x-dane->get_min_value().x);

    this->raport_add("wczytany plik "+fileName);
}
//------------------------------------------------------------------------------
void GeoModel::wczytaj_proj(Mset _modset, Set_interpolacja _interp)
{
    delete modset;
    delete dane;
    delete cube;
    if (curVariogram)
    {
        delete curVariogram;
        curVariogram = NULL;
    }
    modset = new Mset();
    *modset=_modset;
    dane = new GeoDat; 
    cube = new GeoCube(modset->start,modset->sp,modset->grid);
    dane->wczytaj_plik(modset->name);
    last_set = _interp;
    nowy_variogram(last_set.rozmiar_klasy);
}
//------------------------------------------------------------------------------
void GeoModel::updateModel()
{
    if(cube) delete cube;
    cube = new GeoCube(modset->start,modset->sp,modset->grid);
}
//------------------------------------------------------------------------------
void GeoModel::resetModel()
{
    delete modset;
    delete dane;
    delete cube;
    if (curVariogram) delete curVariogram;
    modset = new Mset();
    dane = new GeoDat;
    cube = new GeoCube(modset->start,modset->sp,modset->grid);
    curVariogram = NULL;
    this->raport_add("nowy model \n");
}
//------------------------------------------------------------------------------
bool GeoModel::interpolacja(Set_interpolacja ust, METODA metod)
{
    if(metod == INVDIST)
    {
        calc_invdist(ust);
        return true;
    }
    else if (metod == OKRIGING)
    {
        calc_okriging(ust);
        return true;
    }
    else return false;
}
//------------------------------------------------------------------------------
void GeoModel::calc_invdist(Set_interpolacja ustaw)
{
    cube->reset_min_max();
    progres.pmax = cube->size();
    progres.pmin = progres.pcur = 0;
    for(int a=0; a<cube->size_x();++a)
        for(int b=0; b<cube->size_y();++b)
            for(int c=0; c<cube->size_z();++c)
            {
                wektor3d tmp = inv_dist(this->lok2glob(wektor3d(a,b,c)),
                                        ustaw.promien,ustaw.potega);
                cube->setRekLok(wektor3i(a,b,c),tmp);
                progres.pcur=progres.pcur+1;
            }
    last_set=ustaw;
    this->raport_add("\nodwrotne odległości ");
    modset->min_val=cube->get_min();
    modset->max_val=cube->get_max();
    this->raport_add(cos2str(cube->get_min())+"\n");
    this->raport_add(cos2str(cube->get_max())+"\n");
}
//------------------------------------------------------------------------------
void GeoModel::calc_okriging(Set_interpolacja ustaw)
{
    cube->reset_min_max();
    GeoKriging gek(ustaw);
    std::vector<geo3d> otocz;
    progres.pmax = cube->size();
    progres.pmin = progres.pcur = 0;
    for(int a=0; a<cube->size_x();++a)
        for(int b=0; b<cube->size_y();++b)
            for(int c=0; c<cube->size_z();++c)
            {
               dane->wypisz_dat(otocz,this->lok2glob(wektor3d(a,b,c)),ustaw.promien);
               wektor3d tmp = gek.o_kriging(this->lok2glob(wektor3d(a,b,c)),otocz);
               cube->setRekLok(wektor3i(a,b,c),tmp);
               progres.pcur = progres.pcur+1;
            }
    last_set = ustaw;
    this->raport_add("\nkriging ");
    this->raport_add(last_set.toString());

    modset->min_val=cube->get_min();
    modset->max_val=cube->get_max();
    this->raport_add(cos2str(cube->get_min())+"\n");
    this->raport_add(cos2str(cube->get_max())+"\n");
}
//------------------------------------------------------------------------------
wektor3d GeoModel::policzZasoby()
{
    GeoZasoby gZasoby(modset,cube);
    return gZasoby.get_zasoby();
}
//------------------------------------------------------------------------------
std::vector<geo3d> GeoModel::analizaZasoby(int _ileKlas)
{
    GeoZasoby gZasoby(modset,cube);
    vector<geo3d> analiza = gZasoby.analiza_zasoby(_ileKlas);
    return analiza;
}
//------------------------------------------------------------------------------
void GeoModel::wypiszXYZdane(ostream &os)
{
    dane->wypisz_xyz(os);
}
//------------------------------------------------------------------------------
void GeoModel::wypiszXYZmodel(ostream &os, bool tylkoZasoby)
{
    if (tylkoZasoby) cube->wypiszGlo(os,true, modset->cutoff);
    else cube->wypiszGlo(os,true, -1);
}
//------------------------------------------------------------------------------
void GeoModel::get_xyz_dane(std::vector<wektor3d> &vec, bool cen)
{
    wektor3d ofset;
    if(cen) ofset = (modset->wym/2)+modset->start;
    dane->wypisz_xyz(vec,ofset);
}
//------------------------------------------------------------------------------
void GeoModel::get_xyz_model(std::vector<wektor3d> &vec,bool cen, bool zasoby)
{
    wektor3d ofset;
    if(cen) ofset = (modset->wym/2)+modset->start;
    if(zasoby) cube->wypiszGlo(vec,modset->cutoff, ofset);
    else cube->wypiszGlo(vec,-1,ofset);
}
//------------------------------------------------------------------------------
void GeoModel::wypisz_dane(string fileName, string sep)
{
    ofstream of(fileName.c_str());
    if(of.is_open())
    {
        dane->wypisz(of,sep);
        of.close();
    }
}
//------------------------------------------------------------------------------
void GeoModel::wypisz_model(string fileName, string sep)
{
    ofstream of(fileName.c_str());
    if(of.is_open())
    {
        cube->wypiszGlo(of,false,-1);
        of.close();
    }
    ofstream ofs((fileName+".set").c_str());

    modset->name=fileName;
    if(ofs.is_open())
    {
        ofs << *modset;

        ofs.close();
    }
}
//------------------------------------------------------------------------------
void GeoModel::wypisz_zasoby(string fileName, string sep)
{
    ofstream of(fileName.c_str());
    if(of.is_open())
    {
        cube->wypiszGlo(of,false,modset->cutoff);
        of.close();
    }
}
//------------------------------------------------------------------------------
void GeoModel::wypisz_raport(string fileName)
{
    ofstream of(fileName.c_str());
    if(of.is_open())
    {
        of << strRaport;
        of.close();
    }
}
//------------------------------------------------------------------------------
wektor3d GeoModel::glob2lok(wektor3d wsp)
{
    return (wsp - modset->start)/modset->sp;
}
//------------------------------------------------------------------------------
wektor3d GeoModel::lok2glob(wektor3d wsp)
{
    return wsp*modset->sp+modset->start;
}
//------------------------------------------------------------------------------
wektor3d GeoModel::inv_dist(const wektor3d& pkt, double promien, float potega)
{
    wektor3d x,r, wsp2;
    double val(0.0), waga(0.0), odl(0.0), suma1(0.0), suma2(0.0);

    for (GeoMapa::iterator it = dane->get_begin(); it !=dane->get_end(); ++it)
    {
        x = it->first;
        r = it->second;
        wsp2 = wektor3d(x.x,x.y,x.z);
        odl = dist(pkt,wsp2);

        if (odl<promien)
        {
            val = r.x;
            waga = 1 / (pow(odl,potega));
            suma1 += val*waga;
            suma2 += waga;
        }
    }
    if (suma2)
    return wektor3d( suma1/suma2, 2.5, waga);
    else
    return wektor3d( 0.0, 2.5, 0.0);
}
//------------------------------------------------------------------------------
 void GeoModel::nowy_variogram(double rozmiar_klasy)
 {
     if(curVariogram) delete curVariogram;
     curVariogram = new GeoVariogram(dane,rozmiar_klasy);
     raport_add(curVariogram->get_raport());
 }
//------------------------------------------------------------------------------
 void GeoModel::calc_variogram(double rozmiar_klasy)
 {
     if(curVariogram) curVariogram->recalc(rozmiar_klasy);
 }
//------------------------------------------------------------------------------