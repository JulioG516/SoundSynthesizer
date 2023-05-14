// SoundSynthesizer.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>

using namespace std;
#include "olcNoiseMaker.h"

double dFrequencyOutput = 0.0;

double MakeNoise(double dTime) 
{
    double dOutput = 1.0 * (sin(dFrequencyOutput * 2 * 3.14159 * dTime) + sin((dFrequencyOutput + 20.0) * 2 * 3.14159 * dTime));
    
    return dOutput * 0.5;

//    if (dOutput > 0.0)
//        return 0.2;
//    else
//        return -0.2;

}

int main()
{

    // get all sound from hardware
    vector <wstring> devices = olcNoiseMaker<short>::Enumerate();

    // Display findings
    for (auto d : devices) wcout << "Found output devices:" << d << endl;

    // create sound machine 16 bit         frequency latency
    olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

    // Link noise function with sound machine
    sound.SetUserFunction(MakeNoise);

    double dOctaveBaseFrequency = 110.0; // A2
    double d12thRootOf2 = pow(2.0, 1.0 / 12.0);

    while (1)
    {
        // add a keyboard like a piano

        bool bKeyPressed = false;
        for (int k = 0; k < 15; k++) {
            if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe"[k])) & 0x8000)
            {
                dFrequencyOutput = dOctaveBaseFrequency * pow(d12thRootOf2, k);
                bKeyPressed = true;
            }
        }
        
        if (!bKeyPressed)
        {
            dFrequencyOutput = 0.0;
        }
    }

    return 0;
}
