#include "SynthManager.h"

float softsynth::Manager::OutLeft()
{
    float synthAu = synth.OscResult * synthLevel;
    return synthAu;
}

float softsynth::Manager::OutRight()
{
    float synthAu = synth.OscResult * synthLevel;
    return synthAu;
}

void softsynth::Manager::Input(float *in)
{
    //reverb.Input(synth.OscResult);
}

void softsynth::Manager::Tick()
{
    synth.ClickHi();
}

void softsynth::Manager::LoTick()
{
    synth.ClickLo();
}

void softsynth::Manager::Init()
{
    synth.InitVars();
}

void softsynth::Manager::SetFrequency(int f)
{
    synth.SetOscFrequency(f);
}

void softsynth::Manager::SetSynthVol(float v)
{
    synthLevel = v;
}
