#ifndef MANAGER_H
#define MANAGER_H
#include "synth.h"
#include <iostream>
namespace softsynth
{
    class Manager
    {
        public:
            float OutLeft();
            float OutRight();
            void Input(float* in);
            void Tick();
            void LoTick();
            void SetFrequency(int f);
            void SetSynthVol(float v);
            void Init();

        private:
            softsynth::Synth synth;
            float synthLevel;
            float reverbLevel;

    };
}

#endif