#include <iostream>
#include "../../GeoModel.h"

const string fileIn = "dane.txt";
const string fileOut= "dane_model.txt";

int main()
{
    GeoModel *model = new GeoModel();

    std::cout << "MGEOSTAT CONSOLE" << std::endl;

    model->wczytaj_dane(fileIn);

    Mset *ustawienia = model->ptr_mset();

    std::cout << *ustawienia << std::endl;

    //ustawienia - po zmianie rozmiaru updateModel()
    //model->updateModel();

    Set_interpolacja interpolacja;

    interpolacja.vario = SPHERICAL;
    interpolacja.nuget_c0 = 0.0;
    interpolacja.sill_c1 = 0.1;
    interpolacja.range_a = 50.0;
    interpolacja.potega = 2.0;
    interpolacja.promien = 50.0;
    interpolacja.min_ilosc = 1.0;
    interpolacja.min_ilosc = 64.0;

    std::cout << "working" << std::endl;

    model->calc_okriging(interpolacja);

    //ustawienia->cutoff = 3.0;

    cout << model->recreate_rapor("dzisiejsza data");

    model->wypisz_model(fileOut);

    delete model;

    return 0;
}

