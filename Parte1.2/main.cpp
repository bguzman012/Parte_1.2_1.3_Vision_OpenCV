#include "Imagen.hpp"

using namespace std;

int main(int argc, char *argv[])
{

    unsigned t0, t1, t2, t3, t4, t5;

    Imagen imagen;

    string rutaImagenes, rutaImagenes2, rutaImagenes3, rutaTestMonkey, rutaTestFeline, rutaTestMarinos;

    rutaImagenes = "/home/bryam/Documents/Materias/Vision/DeberImagenes/Train/monkey";
    rutaImagenes2 = "/home/bryam/Documents/Materias/Vision/DeberImagenes/Train/feline";
    rutaImagenes3 = "/home/bryam/Documents/Materias/Vision/DeberImagenes/Train/marine_animals";

    rutaTestMonkey = "/home/bryam/Documents/Materias/Vision/DeberImagenes/Test/monkey";
    rutaTestFeline = "/home/bryam/Documents/Materias/Vision/DeberImagenes/Test/feline";
    rutaTestMarinos = "/home/bryam/Documents/Materias/Vision/DeberImagenes/Test/marine_animals";

    vector<string> listadoMonkey = imagen.leerDirectorios(rutaImagenes);
    vector<string> listadoFelina = imagen.leerDirectorios(rutaImagenes2);
    vector<string> listadoMarinos = imagen.leerDirectorios(rutaImagenes3);

    vector<string> listadoMonkeyT = imagen.leerDirectorios(rutaTestMonkey);
    vector<string> listadoFelinaT = imagen.leerDirectorios(rutaTestFeline);
    vector<string> listadoMarinosT = imagen.leerDirectorios(rutaTestMarinos);

    vector<Mat> imagenesMonkey, imagenesFeline, imagenesMarinos, imagenesTestMonkey, imagenesTestMarine, imagenesTestFeline,
    histogramasMonkeyTrain, histogramasFelineTrain,histogramasMarinoTrain, histogramasMonkeyTest, histogramasFelineTest, 
    histogramasMarineTest;

    imagenesMonkey = imagen.readImagenes(listadoMonkey, rutaImagenes);
    imagenesFeline = imagen.readImagenes(listadoFelina, rutaImagenes2);
    imagenesMarinos = imagen.readImagenes(listadoMarinos, rutaImagenes3);
    imagenesTestMonkey = imagen.readImagenes(listadoMonkeyT, rutaTestMonkey);
    imagenesTestFeline = imagen.readImagenes(listadoFelinaT, rutaTestFeline);
    imagenesTestMarine = imagen.readImagenes(listadoMarinosT, rutaTestMarinos);

    t0 = clock();

    histogramasMonkeyTrain = imagen.calcularHistogramas(imagenesMonkey);
    histogramasFelineTrain = imagen.calcularHistogramas(imagenesFeline);
    histogramasMarinoTrain = imagen.calcularHistogramas(imagenesMarinos);
    histogramasMonkeyTest = imagen.calcularHistogramas(imagenesTestMonkey);
    histogramasFelineTest = imagen.calcularHistogramas(imagenesTestFeline);
    histogramasMarineTest = imagen.calcularHistogramas(imagenesTestMarine);



    vector<int> listaResultadosMonkey, listaResultadosFeline, listaResultadosMarine, listaPrecisionMonkey, 
    listaPrecisionFeline, listaPrecisionMarine;

    cout << "Histo test: " << histogramasMonkeyTest.size() << endl;
    
    listaResultadosMonkey = imagen.clasificarImagenes(histogramasMonkeyTrain, histogramasMarinoTrain, histogramasFelineTrain, 
    histogramasMonkeyTest);
    listaResultadosFeline = imagen.clasificarImagenes(histogramasMonkeyTrain, histogramasMarinoTrain, histogramasFelineTrain, 
    histogramasFelineTest);
    listaResultadosMarine = imagen.clasificarImagenes(histogramasMonkeyTrain, histogramasMarinoTrain, histogramasFelineTrain, 
    histogramasMarineTest);

    //0 ---> Etiqueta Monkey
    //1 ---> Etiqueta Feline
    //2 ---> Etiqueta Marine

    listaPrecisionMonkey = imagen.getPrecision(listaResultadosMonkey, 0);
    listaPrecisionFeline = imagen.getPrecision(listaResultadosFeline, 1);
    listaPrecisionMarine = imagen.getPrecision(listaResultadosMarine, 2);

    float porcentajeMonkey, porcentajeFeline, porcentajeMarine;

    porcentajeMonkey = imagen.getPorcentajePrecision(listaPrecisionMonkey);
    porcentajeFeline = imagen.getPorcentajePrecision(listaPrecisionFeline);
    porcentajeMarine = imagen.getPorcentajePrecision(listaPrecisionMarine);

    cout << "Porcentaje de etiqueta Monkey: " << porcentajeMonkey << "%" << endl;
    cout << "Porcentaje de etiqueta Feline: " << porcentajeFeline << "%" << endl;
    cout << "Porcentaje de etiqueta Marine_Animl: " << porcentajeMarine << "%" << endl;

    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Tiempo BGR: " << time << endl; 
    //*****************Proceso escala grises************

    vector<Mat> imagenesGrisMonkey, imagenesGrisFelines, imagenesGrisMarinos, imagenesGrisTestMonkey, 
    imagenesGrisTestFelines, imagenesGrisTestMarine;

    t2 = clock();

    imagenesGrisMonkey = imagen.convertirEscalaGris(imagenesMonkey);
    imagenesGrisFelines = imagen.convertirEscalaGris(imagenesFeline);
    imagenesGrisMarinos = imagen.convertirEscalaGris(imagenesMarinos);
    imagenesGrisTestMonkey = imagen.convertirEscalaGris(imagenesTestMonkey);
    imagenesGrisTestFelines = imagen.convertirEscalaGris(imagenesTestFeline);
    imagenesGrisTestMarine = imagen.convertirEscalaGris(imagenesTestMarine);

    vector<Mat> histogramasGrisMonkey, histogramasGrisFelines, histogramasGrisMarinos, histogramasGrisTestMonkey, 
    histogramasGrisTestFelines, histogramasGrisTestMarine;

    histogramasGrisMonkey = imagen.calcularHistogramasGrises(imagenesGrisMonkey);
    histogramasGrisFelines = imagen.calcularHistogramasGrises(imagenesGrisFelines); 
    histogramasGrisMarinos = imagen.calcularHistogramasGrises(imagenesGrisMarinos);
    histogramasGrisTestMonkey = imagen.calcularHistogramasGrises(imagenesGrisTestMonkey); 
    histogramasGrisTestFelines = imagen.calcularHistogramasGrises(imagenesGrisTestFelines);
    histogramasGrisTestMarine = imagen.calcularHistogramasGrises(imagenesGrisTestMarine);

    vector<int> listaResultadosGrisMonkey, listaResultadosGrisFeline, listaResultadosGrisMarine, listaPrecisionGrisMonkey, 
    listaPrecisionGrisFeline, listaPrecisionGrisMarine;
    
    listaResultadosGrisMonkey = imagen.clasificarImagenesGrises(histogramasGrisMonkey, histogramasGrisMarinos, histogramasGrisFelines, 
    histogramasGrisTestMonkey);
    listaResultadosGrisFeline = imagen.clasificarImagenesGrises(histogramasGrisMonkey, histogramasGrisMarinos, histogramasGrisFelines, 
    histogramasGrisTestFelines);
    listaResultadosGrisMarine = imagen.clasificarImagenesGrises(histogramasGrisMonkey, histogramasGrisMarinos, histogramasGrisFelines, 
    histogramasGrisTestMarine);

    cout << "Histoggf test: " << histogramasGrisTestMonkey.size() << endl;

    //0 ---> Etiqueta Monkey
    //1 ---> Etiqueta Feline
    //2 ---> Etiqueta Marine

    listaPrecisionGrisMonkey = imagen.getPrecision(listaResultadosGrisMonkey, 0);
    listaPrecisionGrisFeline = imagen.getPrecision(listaResultadosGrisFeline, 1);
    listaPrecisionGrisMarine = imagen.getPrecision(listaResultadosGrisMarine, 2);

    float porcentajeGrisMonkey, porcentajeGrisFeline, porcentajeGrisMarine;

    porcentajeGrisMonkey = imagen.getPorcentajePrecision(listaPrecisionGrisMonkey);
    porcentajeGrisFeline = imagen.getPorcentajePrecision(listaPrecisionGrisFeline);
    porcentajeGrisMarine = imagen.getPorcentajePrecision(listaPrecisionGrisMarine);

    cout << "Porcentaje de etiqueta Monkey(Gris): " << porcentajeGrisMonkey << "%" << endl;
    cout << "Porcentaje de etiqueta Feline(Gris): " << porcentajeGrisFeline << "%" << endl;
    cout << "Porcentaje de etiqueta Marine_Animals(Gris): " << porcentajeGrisMarine << "%" << endl;

    t3 = clock();

    double time2 = (double(t3-t2)/CLOCKS_PER_SEC);
    cout << "Tiempo GRAYSCALE: " << time2 << endl; 

    //*************HSV

    vector<Mat> imagenesHSVMonkey, imagenesHSVFelines, imagenesHSVMarinos, imagenesHSVTestMonkey, 
    imagenesHSVTestFelines, imagenesHSVTestMarine;

    t4 = clock();

    imagenesHSVMonkey = imagen.convertirHSV(imagenesMonkey);
    imagenesHSVFelines = imagen.convertirHSV(imagenesFeline);
    imagenesHSVMarinos = imagen.convertirHSV(imagenesMarinos);
    imagenesHSVTestMonkey = imagen.convertirHSV(imagenesTestMonkey);
    imagenesHSVTestFelines = imagen.convertirHSV(imagenesTestFeline);
    imagenesHSVTestMarine = imagen.convertirHSV(imagenesTestMarine);

    vector<Mat> histogramasHSVMonkey, histogramasHSVFelines, histogramasHSVMarinos, histogramasHSVTestMonkey, 
    histogramasHSVTestFelines, histogramasHSVTestMarine;

    
    histogramasHSVMonkey = imagen.calcularHistogramas(imagenesHSVMonkey);
    histogramasHSVFelines = imagen.calcularHistogramas(imagenesHSVFelines);
    histogramasHSVMarinos = imagen.calcularHistogramas(imagenesHSVMarinos);
    histogramasHSVTestMonkey = imagen.calcularHistogramas(imagenesHSVTestMonkey);
    histogramasHSVTestFelines = imagen.calcularHistogramas(imagenesHSVTestFelines);
    histogramasHSVTestMarine = imagen.calcularHistogramas(imagenesHSVTestMarine);



    vector<int> listaResultadosHSVMonkey, listaResultadosHSVFeline, listaResultadosHSVMarine, 
    listaPrecisionHSVMonkey, listaPrecisionHSVFeline, listaPrecisionHSVMarine;
    
    listaResultadosHSVMonkey = imagen.clasificarImagenes(histogramasHSVMonkey, histogramasHSVMarinos, histogramasHSVFelines, 
    histogramasHSVTestMonkey);
    listaResultadosHSVFeline = imagen.clasificarImagenes(histogramasHSVMonkey, histogramasHSVMarinos, histogramasHSVFelines, 
    histogramasHSVTestFelines);
    listaResultadosHSVMarine = imagen.clasificarImagenes(histogramasHSVMonkey, histogramasHSVMarinos, histogramasHSVFelines, 
    histogramasHSVTestMarine);

    //0 ---> Etiqueta Monkey
    //1 ---> Etiqueta Feline
    //2 ---> Etiqueta Marine

    listaPrecisionHSVMonkey = imagen.getPrecision(listaResultadosHSVMonkey, 0);
    listaPrecisionHSVFeline = imagen.getPrecision(listaResultadosHSVFeline, 1);
    listaPrecisionHSVMarine = imagen.getPrecision(listaResultadosHSVMarine, 2);

    float porcentajeHSVMonkey, porcentajeHSVFeline, porcentajeHSVMarine;

    porcentajeHSVMonkey = imagen.getPorcentajePrecision(listaPrecisionHSVMonkey);
    porcentajeHSVFeline = imagen.getPorcentajePrecision(listaPrecisionHSVFeline);
    porcentajeHSVMarine = imagen.getPorcentajePrecision(listaPrecisionHSVMarine);

    cout << "Porcentaje de etiqueta Monkey(HSV): " << porcentajeHSVMonkey << "%" << endl;
    cout << "Porcentaje de etiqueta Feline(HSV): " << porcentajeHSVFeline << "%" << endl;
    cout << "Porcentaje de etiqueta Marine_Animals(HSV): " << porcentajeHSVMarine << "%" << endl;

    t5 = clock();

    double time3 = (double(t5-t4)/CLOCKS_PER_SEC);
    cout << "Tiempo HSV: " << time3 << endl; 
};
