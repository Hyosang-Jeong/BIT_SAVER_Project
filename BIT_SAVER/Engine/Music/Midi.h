#pragma once
#include <vector>
#include <map>
#include <iostream>
class MidiEvent {
public:
    MidiEvent() {}


    ~MidiEvent() {}

    int        tick;     // delta or absolute MIDI ticks
    int        track;    // [original] track number of event in MIDI file
    double     seconds;  // calculated time in sec. (after doTimeAnalysis())
    int        seq;      // sorting sequence number of event
 //   for (int = 0; i < track - 1; i++)
 //   {
	//for (int j = 0; j < (tranck)->배열.size; j++)
	//{
	//    Treestump.dt = 배열[j];
	//}
 //   }
    std::vector<MidiEvent> m_events;


    //MidiEvent* m_eventlink;  // used to match note-ons and note-offs
    std::map<int,std::vector<long double>> MidiSetUp(std::string filename);

    unsigned long       readVLValue(std::istream& inputfile);
    unsigned long       unpackVLV(unsigned char a = 0, unsigned char b = 0, unsigned char c = 0, unsigned char d = 0, unsigned char e = 0);
    unsigned char              readByte(std::istream& input);

    int         extractMidiData(std::istream& inputfile, std::vector<unsigned char>& array, unsigned char& runningCommand);
};

