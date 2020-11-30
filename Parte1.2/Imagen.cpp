#include <iostream>
#include "Imagen.hpp"

vector<string> Imagen::leerDirectorios(string dir)
{
    vector<string> lista;
    DIR *pDir = opendir(dir.c_str());
    struct dirent *entrada;
    while ((entrada = readdir(pDir)) != NULL)
    {
        //cout << entrada->d_name << endl;
        // entrada->d_type;
        lista.push_back(string(entrada->d_name)); //String a = new String("abc");
        // String a = "abc";
    }
    closedir(pDir);
    return lista;
}

vector<Mat> Imagen::readImagenes(vector<string> vectorImagenes, string rutaImagenes)
{
    vector<Mat> imagenesLeidas;

    for (int i = 0; i < vectorImagenes.size(); i++)
    {

        Mat imagen = imread(rutaImagenes + "/" + vectorImagenes[i]);

        if (imagen.cols != 0)
        {
            imagenesLeidas.push_back(imagen);
        }
    };

    return imagenesLeidas;
}

vector<Mat> Imagen::calcularHistogramas(vector<Mat> vectorImagenes)
{
    vector<Mat> listadoHistogramas;

    for (int i = 0; i < vectorImagenes.size(); i++)
    {
        float rango[] = {0, 256};

        const float *rangoHistograma = {rango};

        vector<Mat> canales;
        Mat imagenTemporal;

        imagenTemporal = vectorImagenes[i];

        split(imagenTemporal, canales);
        Mat histo1;
        Mat histo2;
        Mat histo3;
        int tam = 256;
        calcHist(&canales[0], 1, 0, Mat(), histo1, 1, &tam, &rangoHistograma, true, false);
        calcHist(&canales[1], 1, 0, Mat(), histo2, 1, &tam, &rangoHistograma, true, false);
        calcHist(&canales[2], 1, 0, Mat(), histo3, 1, &tam, &rangoHistograma, true, false);
        listadoHistogramas.push_back(histo1);
        listadoHistogramas.push_back(histo2);
        listadoHistogramas.push_back(histo3);
    }

    return listadoHistogramas;
}

float Imagen::calcularDistancia(vector<Mat> histogramas, vector<Mat> histogramasTest)
{
    float auxiliarTemporal = 0.0;

    for (int i = 0; i + 3 < histogramas.size(); i += 3)
    {

        Mat canal1;
        Mat canal2;
        Mat canal3;

        canal1 = histogramas[i];
        canal2 = histogramas[i + 1];
        canal3 = histogramas[i + 2];

        float resultado1;
        float resultado2;
        float resultado3;

        resultado1 = 0.0;
        resultado2 = 0.0;
        resultado3 = 0.0;

        for (int j = 0; j < 256; j++)
        {
            float var = canal1.at<float>(j, 0) - histogramasTest[0].at<float>(j, 0);
            resultado1 = resultado1 + pow(var, 2);
            float var2 = canal2.at<float>(j, 0) - histogramasTest[1].at<float>(j, 0);
            resultado2 = resultado2 + pow(var2, 2);
            float var3 = canal3.at<float>(j, 0) - histogramasTest[2].at<float>(j, 0);
            resultado3 = resultado3 + pow(var3, 2);
        }

        float raiz = sqrt(resultado1);
        float raiz2 = sqrt(resultado2);
        float raiz3 = sqrt(resultado3);

        float sumaTotal = 0.0;

        sumaTotal = raiz + raiz2 + raiz3;

        if (auxiliarTemporal == 0.0)
        {
            auxiliarTemporal = sumaTotal;
        }
        else if (auxiliarTemporal > sumaTotal)
        {
            auxiliarTemporal = sumaTotal;
        }
    }

    return auxiliarTemporal;
}

vector<int> Imagen::clasificarImagenes(vector<Mat> histogramasTrainMonkey, vector<Mat> histogramasTrainMarino,
                                       vector<Mat> histogramasTrainFelina, vector<Mat> histogramasTest)
{
    vector<int> listaResultados;

    for (size_t i = 0; i + 3 < histogramasTest.size(); i += 3)
    {
        float resOne = 0.0;
        float resDos = 0.0;
        float resTres = 0.0;

        vector<Mat> listaTemp;

        listaTemp.push_back(histogramasTest[i]);
        listaTemp.push_back(histogramasTest[i + 2]);
        listaTemp.push_back(histogramasTest[i + 3]);

        resOne = calcularDistancia(histogramasTrainMonkey, listaTemp);
        resDos = calcularDistancia(histogramasTrainFelina, listaTemp);
        resTres = calcularDistancia(histogramasTrainMarino, listaTemp);

        if ((resOne < resDos) && (resOne < resTres))
        {
            listaResultados.push_back(0);
        }
        else if ((resDos < resOne) && (resDos < resTres))
        {
            listaResultados.push_back(1);
        }
        else
        {
            listaResultados.push_back(2);
        }
    }

    return listaResultados;
}

vector<int> Imagen::getPrecision(vector<int> resultados, int etiqueta)
{
    vector<int> listaPrecision;

    //Si el resultados es igual a la etiqueta pasada como parametro entonces va a ser 1, caso contrario, 0

    for (size_t i = 0; i < resultados.size(); i++)
    {
        if (resultados[i] == etiqueta)
        {
            listaPrecision.push_back(1);
        }
        else
        {
            listaPrecision.push_back(0);
        }
    }
    return listaPrecision;
}

float Imagen::getPorcentajePrecision(vector<int> listaAciertos)
{
    float porcentaje;
    int numAciertos;
    numAciertos = 0;
    for (size_t i = 0; i < listaAciertos.size(); i++)
    {
        if (listaAciertos[i] == 1)
        {
            numAciertos += 1;
        }
    }

    cout << numAciertos << endl;
    cout << listaAciertos.size();

    porcentaje = (numAciertos * 100) / listaAciertos.size();
    return porcentaje;
}

vector<Mat> Imagen::convertirEscalaGris(vector<Mat> listaImagenes)
{
    vector<Mat> listaGrises;
    for (size_t i = 0; i < listaImagenes.size(); i++)
    {
        Mat gris;
        cvtColor(listaImagenes[i], gris, COLOR_BGR2GRAY);
        listaGrises.push_back(gris);
    }
    return listaGrises;
}

vector<Mat> Imagen::calcularHistogramasGrises(vector<Mat> vectorImagenes)
{
    vector<Mat> listadoHistogramas;

    for (int i = 0; i < vectorImagenes.size(); i++)
    {
        float rango[] = {0, 256};

        const float *rangoHistograma = {rango};

        Mat imagenTemporal;

        imagenTemporal = vectorImagenes[i];

        Mat histoGris;

        int tam = 256;
        calcHist(&imagenTemporal, 1, 0, Mat(), histoGris, 1, &tam, &rangoHistograma, true, false);
        listadoHistogramas.push_back(histoGris);
    }

    return listadoHistogramas;
}

float Imagen::calcularDistanciaGrises(vector<Mat> histogramas, vector<Mat> histogramaTest)
{
    float auxiliarTemporal = 0.0;

    for (int i = 0; i < histogramas.size(); i++)
    {

        Mat histoGris;

        histoGris = histogramas[i];

        float resultado1;

        resultado1 = 0.0;

        for (int j = 0; j < 256; j++)
        {
            float var = histoGris.at<float>(j, 0) - histogramaTest[0].at<float>(j, 0);
            resultado1 = resultado1 + pow(var, 2);
        }

        float raiz = sqrt(resultado1);

        float sumaTotal = 0.0;

        sumaTotal = raiz;

        if (auxiliarTemporal == 0.0)
        {
            auxiliarTemporal = sumaTotal;
        }
        else if (auxiliarTemporal > sumaTotal)
        {
            auxiliarTemporal = sumaTotal;
        }
    }

    return auxiliarTemporal;
}

vector<int> Imagen::clasificarImagenesGrises(vector<Mat> histogramasTrainMonkey, vector<Mat> histogramasTrainMarino,
                                             vector<Mat> histogramasTrainFelina, vector<Mat> histogramasTest)
{
    vector<int> listaResultados;

    for (size_t i = 0; i < histogramasTest.size(); i++)
    {
        float resOne = 0.0;
        float resDos = 0.0;
        float resTres = 0.0;

        vector<Mat> matTemp;
        matTemp.push_back(histogramasTest[i]);

        resOne = calcularDistanciaGrises(histogramasTrainMonkey, matTemp);
        resDos = calcularDistanciaGrises(histogramasTrainFelina, matTemp);
        resTres = calcularDistanciaGrises(histogramasTrainMarino, matTemp);

        if ((resOne < resDos) && (resOne < resTres))
        {
            listaResultados.push_back(0);
        }
        else if ((resDos < resOne) && (resDos < resTres))
        {
            listaResultados.push_back(1);
        }
        else
        {
            listaResultados.push_back(2);
        }

        
    }

    return listaResultados;
}

vector<Mat> Imagen::convertirHSV(vector<Mat> listaImagenes)
{
    vector<Mat> listaHSV;
    for (size_t i = 0; i < listaImagenes.size(); i++)
    {
        Mat hsv;
        cvtColor(listaImagenes[i], hsv, COLOR_BGR2HSV);
        listaHSV.push_back(hsv);
    }
    return listaHSV;
}