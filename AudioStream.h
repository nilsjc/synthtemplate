#ifndef AUDIOSTREAM_H
#define AUDIOSTREAM_H
#include "portaudio.h"
#include "SynthManager.h"
namespace softsynth
{

    class Runner
    {
        public:
            int Sample_Rate = 44100;
            int Frames_Per_Buffer = 512;
            void SetManager(softsynth::Manager* managerA);
            softsynth::Manager* manager;
            int paUserCallback( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags);
            void Open();
            void Terminate();

            ~Runner(){ delete manager;}

            /*STATIC*/
            static int paCallback( const void *inputBuffer, void *outputBuffer,
                unsigned long framesPerBuffer,
                const PaStreamCallbackTimeInfo* timeInfo,
                PaStreamCallbackFlags statusFlags,
                void *userData )
            {
                return ((softsynth::Runner*)userData)->paUserCallback(
                    inputBuffer, 
                    outputBuffer,
                    framesPerBuffer,
                    timeInfo,
                    statusFlags);
            }

        private:
            PaStream *stream;
        
        
    };

}


#endif