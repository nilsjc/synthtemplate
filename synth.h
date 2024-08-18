#ifndef SYNTH_H
#define SYNTH_H
namespace softsynth
{
    class Synth
    {
        public:
        // synth control
            void SetOscFrequency(int f);
            float OscResult = 0.0f;

        // internal stuff
            void ClickHi();
            void ClickLo();
            void InitVars();

        private:
            float oscillatorFreq = 200.0;
            float UpdateWithLinearInterpolation(float frequency);
            void createHarmonics(int start, int length, int harmonic);
    };
}
#endif