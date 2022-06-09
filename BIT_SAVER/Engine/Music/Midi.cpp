/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Midi.cpp
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang ,  Sunwoo Lee

-----------------------------------------------------------------*/
#include "Midi.h"
#include <fstream>
#include "..\Engine.h"
#include "Sound_Num.h"
int m_ticksPerQuarterNote = 120; //set default

std::map<int,std::vector<info>> MidiEvent::MidiSetUp(int music_num)
{
    const char* midi_filename = " ";
    switch (music_num)
    {
    case SOUND_NUM::OFFSET:
        midi_filename = "../MIDI/offset.mid";
        break;
    case SOUND_NUM::TUTORIAL:
        midi_filename = "../MIDI/tutorial_offset.mid";
        break;
    case SOUND_NUM::DISCO:
        midi_filename = "../MIDI/disco_edit.mid";
        break;
    case SOUND_NUM::REWIND:
        midi_filename = "../MIDI/rewind_edit.mid";
        break;
    case SOUND_NUM::DIOMA:
        midi_filename = "../MIDI/dioma_edit.mid";
        break;
    case SOUND_NUM::ENERGY:
        midi_filename = "../MIDI/energy_edit.mid";
        break;
    default:
        break;
    }
    //open the midi file
    std::ifstream input{ midi_filename, std::ios::binary };
    if (!input)
    {
        Engine::GetLogger().LogError("MIDI file cannot open!");
        exit(EXIT_FAILURE);
    }
    int        character;//for extract MThd or Mtrk
    character = input.get();//'M'
    character = input.get();//'T'
    character = input.get();//'h'
    character = input.get();//'d'

    unsigned long  longdata;
    unsigned char buffer[4] = { 0 };
    input.read((char*)buffer, 4);
    if (input.eof())
    {
        Engine::GetLogger().LogError("Error: unexpected end of the file.");
        exit(EXIT_FAILURE);
    }
    longdata = buffer[3] | (buffer[2] << 8) | (buffer[1] << 16) | (buffer[0] << 24);

    //checking format
    int type = 0;
    unsigned short  shortdata;
    buffer[2] = { 0 };
    input.read((char*)buffer, 2);
    shortdata = buffer[1] | (buffer[0] << 8);

    switch (shortdata) 
    {//To know the type
    case 0:
        type = 0;
        break;
    case 1:
        type = 1;
        break;
    case 2:
        //There maybe not type 2.
    default:
        std::cerr << "Error: can't handle a type-" << shortdata << " MIDI file" << std::endl;
    }

    //checking track count
    int tracks = 0;
    buffer[2] = { 0 };
    input.read((char*)buffer, 2);
    shortdata = buffer[1] | (buffer[0] << 8);

    if (type == 0 && shortdata != 1)
    {
        std::cerr << "Error!: Type 0 MIDI file can only have one track" << std::endl;
        std::cerr << "Instead track count is: " << shortdata << std::endl;
    }
    else
    {
        tracks = shortdata;
    }

    // Ticks per quarter note 
    buffer[2] = { 0 };
    input.read((char*)buffer, 2);
    shortdata = buffer[1] | (buffer[0] << 8);

    if (shortdata >= 0x8000)
    {
        int framespersecond = 255 - ((shortdata >> 8) & 0x00ff) + 1;
        int subframes = shortdata & 0x00ff;
        switch (framespersecond)
        {
        case 25:
            framespersecond = 25;
            break;
        case 24:
            framespersecond = 24;
            break;
        case 29:
            framespersecond = 29;
            break;
        case 30:
            framespersecond = 30;
            break;
        default:
            std::cerr << "Warning: unknown FPS: " << framespersecond << std::endl;
            std::cerr << "Using non-standard FPS: " << framespersecond << std::endl;
        }
        m_ticksPerQuarterNote = framespersecond * subframes;
    }
    else
    {
        m_ticksPerQuarterNote = shortdata;
    }
    //================================================================================================= Track Start
    unsigned char runCommand;
    MidiEvent event;
    std::vector<unsigned char> bytes;
    unsigned long tempo_data = 0;
    long double one_tick_per_tempo = 0;
    for (int i = 0; i < tracks; i++) 
    {
        runCommand = 0;

        character = input.get();//'M'
        character = input.get();//'T'
        character = input.get();//'r'
        character = input.get();//'k'

        input.read((char*)buffer, 4);
        if (input.eof())
        {
            Engine::GetLogger().LogError("Error! : unexpected end of file.");
            exit(EXIT_FAILURE);
        }
        longdata = buffer[3] | (buffer[2] << 8) | (buffer[1] << 16) | (buffer[0] << 24);

        // Read MIDI events in the track
        int absolute_ticks = 0;
        while (!input.eof())
        {
            longdata = event.readDtValue(input);
            absolute_ticks += longdata;
            event.extractMidi(input, bytes, runCommand);

            if (bytes[0] == 0xff && bytes[1] == 0x51)
            {
                for (int j = 0; j < bytes[2]; j++)
                {
                    tempo_data = tempo_data | (bytes[bytes.size() - 1 - j] << 8 * j);
                }
            }
            event.tick = absolute_ticks;
            event.track = 0;

            //Get velocity to know what function implement
            //if (bytes[0] == 0x64 && bytes[1] == 0x51)
            //{
            //    for (int j = 0; j < bytes[2]; j++)
            //    {
            //        tempo_data = tempo_data | (bytes[bytes.size() - 1 - j] << 8 * j);
            //    }
            //}

            if ((bytes[0] & 0xf0) == 0x90 && bytes[bytes.size() - 1] != 0)
            {
                event.track = i + 1;
                event.movement = static_cast<int>(bytes[bytes.size() - 1]);
                /*if (music_num == SOUND_NUM::OFFSET)
                {
                    event.track = 1;
                }
                else if (music_num == SOUND_NUM::DISCO)
                {
                    event.track = i + 1;
                }
                else if (music_num == SOUND_NUM::REWIND)
                {
                    event.track = 1;
                }
                else if (music_num == SOUND_NUM::DIOMA)
                {
                    event.track = i + 1;
                }
                else if (music_num == SOUND_NUM::ENERGY)
                {
                    event.track = 1;
                }
                else
                {
                    event.track = (bytes[0] & 0x0f) + 1;
                }*/
                m_events.push_back(event);
                
            }
            else if (bytes[0] == 0xff && bytes[1] == 0x2f) 
            {
                // end-of-track message
                break;
            }
        }
    }

    //make seconds from dt and ticks
    one_tick_per_tempo = (tempo_data * 0.000001) / m_ticksPerQuarterNote;
    //std::map<int, std::vector<long double>> track_seconds_;
    std::map<int,std::vector<info>> dt_to_seconds;
    int trackFrom = 0;
    int trackTo = 0;
    switch (music_num)
    {
    case SOUND_NUM::OFFSET:
        trackFrom = 1;
        trackTo = 1;
        break;
    case SOUND_NUM::TUTORIAL:
        trackFrom = 1;
        trackTo = 3;
        break;
    case SOUND_NUM::DISCO:
        trackFrom = 1;
        trackTo = 3;
        break;
    case SOUND_NUM::REWIND:
        trackFrom = 1;
        trackTo = 3;
        break;
    case SOUND_NUM::DIOMA:
        trackFrom = 1;
        trackTo = 3;
        break;
    case SOUND_NUM::ENERGY:
        trackFrom = 1;
        trackTo = 3;
        break;
    default:
        trackFrom = 1;
        trackTo = 1;
        {
            Engine::GetLogger().LogError("Error! :There are not track info(midi.cppLine241)");
            exit(EXIT_FAILURE);
        }
        break;
    }
    for (int i = trackFrom; i <= trackTo; i++)
    {
        for (auto& m : m_events)
        {
            if (m.track == i)
            {
                //dt_to_seconds[i].push_back(info(m.tick * one_tick_per_tempo, m.tick* one_tick_per_tempo));put movement info(velocity)
                dt_to_seconds[i].push_back(info(m.tick* one_tick_per_tempo, m.movement));
            }
        }
    }
    input.close();

    /*return track_seconds_;*/
    return dt_to_seconds;
}

//read Bytes
unsigned char MidiEvent::readBytes(std::istream& input) {
    unsigned char buffer[1] = { 0 };
    input.read((char*)buffer, 1);
    if (input.eof())
    {
        std::cerr << "Error! : unexpected end of file." << std::endl;
        return 0;
    }
    return buffer[0];
}

//take dt information, if that is more than 0x7f next byte also means dt information(from 0x80)
//there are maybe no music which has more than 5 bytes dt information
//so we use 5
unsigned long MidiEvent::openDtInformation(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e) {
    unsigned char bytes[5] = { a, b, c, d, e };
    int count = 0;
    while ((count < 5) && (bytes[count] > 0x7f))
    {
        count++;
    }
    count++;
    if (count >= 6)
    {
        std::cerr << "Dt number is too large" << std::endl;
        return 0;
    }

    unsigned long output = 0;
    for (int i = 0; i < count; i++)
    {
        output = output << 7;
        output = output | (bytes[i] & 0x7f);
    }
    return output;
}

//read dt Value.
unsigned long MidiEvent::readDtValue(std::istream& input) {
    unsigned char b[5] = { 0 };

    for (int i = 0; i < 5; i++)
    {
        b[i] = readBytes(input);
        if (b[i] < 0x80)
        {
            break;
        }
    }

    return openDtInformation(b[0], b[1], b[2], b[3], b[4]);
}

//interpret the mid file
int MidiEvent::extractMidi(std::istream& input, std::vector<unsigned char>& array, unsigned char& runningCommand)
{
    int character;
    unsigned char byte;
    array.clear();
    int runningQ;

    //get value
    character = input.get();

    //if value is the end of file, go return 0
    if (character == EOF)
    {
        std::cerr << "Error! : unexpected end of file." << std::endl;
        return 0;
    }
    else
    {
        byte = (unsigned char)character;
    }


    if (byte < 0x80)
    {
        runningQ = 1;
        if (runningCommand == 0)
        {
            std::cerr << "Error! : running command with no previous command" << std::endl;
            return 0;
        }
        if (runningCommand >= 0xf0)
        {
            std::cerr << "Error! : running status not permitted with meta"
                << " event" << std::endl;
            std::cerr << "Byte is 0x" << std::hex << (int)byte << std::dec << std::endl;
            return 0;
        }
    }
    else
    {
        runningCommand = byte;
        runningQ = 0;
    }
    array.push_back(runningCommand);

    if (runningQ)
    {
        array.push_back(byte);
    }

    switch (runningCommand & 0xf0)
    {
    case 0x80:        // note off (2 more bytes)
    case 0x90:        // note on (2 more bytes)
    case 0xA0:        // extract other thing
    case 0xB0:        // extract other thing
    case 0xE0:        // extract other thing
        byte = readBytes(input);
        if (byte > 0x7f)
        {
            std::cerr << "MIDI data byte is too large: " << (int)byte << std::endl;
        }
        array.push_back(byte);
        if (!runningQ)
        {
            byte = readBytes(input);
            if (byte > 0x7f)
            {
                std::cerr << "MIDI data byte is too large: " << (int)byte << std::endl;

            }
            array.push_back(byte);
        }
        break;

    case 0xC0:        // patch change (1 more byte)
    case 0xD0:        // channel pressure (1 more byte)
        if (!runningQ)
        {
            byte = readBytes(input);
            if (byte > 0x7f)
            {
                std::cerr << "MIDI data byte is too large: " << (int)byte << std::endl;
            }
            array.push_back(byte);
        }
        break;

    case 0xF0:
        switch (runningCommand)
        {
            // meta event start//
        case 0xff:
        {
            if (!runningQ)
            {
                byte = readBytes(input); // meta type
                array.push_back(byte);
            }
            unsigned long length = 0;
            unsigned char byte1 = 0;
            unsigned char byte2 = 0;
            unsigned char byte3 = 0;
            unsigned char byte4 = 0;
            byte1 = readBytes(input);

            //push back to array
            //for byte 1,2,3,4,5
            array.push_back(byte1);
            if (byte1 >= 0x80)
            {
                byte2 = readBytes(input);
                array.push_back(byte2);
                if (byte2 > 0x80)
                {
                    byte3 = readBytes(input);
                    array.push_back(byte3);
                    if (byte3 >= 0x80)
                    {
                        byte4 = readBytes(input);
                        array.push_back(byte4);
                        if (byte4 >= 0x80)
                        {
                            std::cerr << "Error: can't handle large VLVs" << std::endl;
                        }
                        else
                        {
                            length = openDtInformation(byte1, byte2, byte3, byte4);
                        }
                    }
                    else
                    {
                        length = openDtInformation(byte1, byte2, byte3);
                    }
                }
                else
                {
                    length = openDtInformation(byte1, byte2);
                }
            }
            else
            {
                length = byte1;
            }
            for (int j = 0; j < (int)length; j++)
            {
                byte = readBytes(input); // meta type
                array.push_back(byte);
            }
        }
        break;

        case 0xf7:// extract
        case 0xf0:// System Exclusive message
        {         // (complete, or start of message)
            int length = (int)readDtValue(input);
            for (int i = 0; i < length; i++)
            {
                byte = readBytes(input);
                array.push_back(byte);
            }
        }
        break;
        }
        break;
    default:
        std::cout << "Error! :can't reading midifile" << std::endl;
        std::cout << "Command byte was " << (int)runningCommand << std::endl;
        return 0;
    }
    return 1;
}
